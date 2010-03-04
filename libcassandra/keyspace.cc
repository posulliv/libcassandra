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
                      const ColumnPath &col_path,
                      const string &value)
{
  /* validate the column path */
  validateColumnPath(col_path);
  client->getCassandra()->insert(name, key, col_path, value, createTimestamp(), level);
}


void Keyspace::remove(const string &key,
                      const ColumnPath &col_path)
{
  client->getCassandra()->remove(name, key, col_path, createTimestamp(), level);
}


Column Keyspace::getColumn(const string &key, const ColumnPath &col_path)
{
  validateColumnPath(col_path);
  ColumnOrSuperColumn cosc;
  client->getCassandra()->get(cosc, name, key, col_path, level);
  if (cosc.column.name.empty())
  {
    /* throw an exception */
  }
  return cosc.column;
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
