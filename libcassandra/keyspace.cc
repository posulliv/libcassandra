/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <time.h>

#include <string>
#include <map>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include <libgenthrift/Cassandra.h>

#include "cassandra.h"
#include "keyspace.h"

using namespace libcassandra;
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace org::apache::cassandra;
using namespace boost;


Keyspace::Keyspace(Cassandra *in_client,
                   const string &in_name,
                   const map< string, map<string, string> > &in_desc,
                   ConsistencyLevel in_level)
  :
    client(in_client),
    name(in_name),
    keyspace_desc(in_desc),
    level(in_level)
{}


void Keyspace::insert(const string &key,
                      ColumnPath &col_path,
                      const string &value)
{
  /* validate the column path */
  validateColumnPath(col_path);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.column= true;
  col_path.__isset.super_column= true;
  /* actually perform the insert */
  client->getCassandra()->insert(name, key, col_path, value, createTimestamp(), level);
}


void Keyspace::remove(const string &key,
                      const ColumnPath &col_path)
{
  client->getCassandra()->remove(name, key, col_path, createTimestamp(), level);
}


Column Keyspace::getColumn(const string &key, ColumnPath &col_path)
{
  validateColumnPath(col_path);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.column= true;
  ColumnOrSuperColumn cosc;
  client->getCassandra()->get(cosc, name, key, col_path, level);
  if (cosc.column.name.empty())
  {
    /* throw an exception */
  }
  return cosc.column;
}


vector<Column> Keyspace::getSlice(const string &key,
                                  const ColumnParent &col_parent,
                                  const SlicePredicate &pred)
{
  vector<ColumnOrSuperColumn> ret_cosc;
  vector<Column> result;
  client->getCassandra()->get_slice(ret_cosc, name, key, col_parent, pred, level);
  for (vector<ColumnOrSuperColumn>::iterator it= ret_cosc.begin();
       it != ret_cosc.end();
       ++it)
  {
    if (! (*it).column.name.empty())
    {
      result.push_back((*it).column);
    }
  }
  return result;
}


int32_t Keyspace::getCount(const string &key, const ColumnParent &col_parent)
{
  return (client->getCassandra()->get_count(name, key, col_parent, level));
}


string Keyspace::getName()
{
  return name;
}


ConsistencyLevel Keyspace::getConsistencyLevel() const
{
  return level;
}


int64_t Keyspace::createTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (int64_t) tv.tv_sec * 1000000 + (int64_t) tv.tv_usec;
}


void Keyspace::validateColumnPath(const ColumnPath &col_path)
{
  map<string, string> cf_define= keyspace_desc[col_path.column_family];
  if (cf_define.empty())
  {
    /* throw an exception */
  }
  string type= cf_define["Type"];
  if (! type.compare("Standard"))
  {
    if (! col_path.column.empty())
    {
      return;
    }
  }
  else if (! type.compare("Super"))
  {
    if (! col_path.super_column.empty())
    {
      return;
    }
  }
  /* if we get here, throw an exception */
}


void Keyspace::validateSuperColumnPath(const ColumnPath &col_path)
{
  map<string, string> cf_define= keyspace_desc[col_path.column_family];
  if (cf_define.empty())
  {
    /* throw an exception */
  }
  string type= cf_define["Type"];
  if (! type.compare("Super"))
  {
    if (! col_path.super_column.empty())
    {
      return;
    }
  }
  /* if we get here, throw an exception */
}
