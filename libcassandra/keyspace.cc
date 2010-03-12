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


void Keyspace::insertColumn(const string &key,
                            const string &column_family,
                            const string &column_name,
                            const string &value)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.column.assign(column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.column= true;
  /* validate the column path */
  validateColumnPath(col_path);
  /* actually perform the insert */
  client->getCassandra()->insert(name, key, col_path, value, createTimestamp(), level);
}


void Keyspace::insertSuperColumn(const string &key,
                                 const string &column_family,
                                 const string &column_name,
                                 const string &value)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.column.assign(column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.super_column= true;
  /* validate the column path */
  validateSuperColumnPath(col_path);
  /* actually perform the insert */
  client->getCassandra()->insert(name, key, col_path, value, createTimestamp(), level);
}


void Keyspace::remove(const string &key,
                      const ColumnPath &col_path)
{
  client->getCassandra()->remove(name, key, col_path, createTimestamp(), level);
}


Column Keyspace::getColumn(const string &key, 
                           const string &column_family,
                           const string &column_name)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.column.assign(column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.column= true;
  validateColumnPath(col_path);
  ColumnOrSuperColumn cosc;
  client->getCassandra()->get(cosc, name, key, col_path, level);
  if (cosc.column.name.empty())
  {
    /* throw an exception */
  }
  return cosc.column;
}


string Keyspace::getColumnValue(const string &key, 
                                const string &column_family,
                                const string &column_name)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.column.assign(column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.column= true;
  validateColumnPath(col_path);
  ColumnOrSuperColumn cosc;
  client->getCassandra()->get(cosc, name, key, col_path, level);
  if (cosc.column.name.empty())
  {
    /* throw an exception */
  }
  return cosc.column.value;
}


SuperColumn Keyspace::getSuperColumn(const string &key, 
                                     const string &column_family,
                                     const string &super_column_name)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.super_column.assign(super_column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.super_column= true;
  validateSuperColumnPath(col_path);
  ColumnOrSuperColumn cosc;
  client->getCassandra()->get(cosc, name, key, col_path, level);
  if (cosc.super_column.name.empty())
  {
    /* throw an exception */
  }
  return cosc.super_column;
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


map<string, vector<Column> > Keyspace::getRangeSlice(const ColumnParent &col_parent,
                                                     const SlicePredicate &pred,
                                                     const string &start,
                                                     const string &finish,
                                                     const int32_t row_count)
{
  map<string, vector<Column> > ret;
  vector<KeySlice> key_slices;
  client->getCassandra()->get_range_slice(key_slices, 
                                          name, 
                                          col_parent, 
                                          pred, 
                                          start, 
                                          finish,
                                          row_count,
                                          level);
  if (! key_slices.empty())
  {
    for (vector<KeySlice>::iterator it= key_slices.begin();
         it != key_slices.end();
         ++it)
    {
      ret.insert(make_pair((*it).key, getColumnList((*it).columns)));
    }
  }
  return ret;
}


map<string, vector<SuperColumn> > Keyspace::getSuperRangeSlice(const ColumnParent &col_parent,
                                                               const SlicePredicate &pred,
                                                               const string &start,
                                                               const string &finish,
                                                               const int32_t row_count)
{
  map<string, vector<SuperColumn> > ret;
  vector<KeySlice> key_slices;
  client->getCassandra()->get_range_slice(key_slices, 
                                          name, 
                                          col_parent, 
                                          pred, 
                                          start, 
                                          finish,
                                          row_count,
                                          level);
  if (! key_slices.empty())
  {
    for (vector<KeySlice>::iterator it= key_slices.begin();
         it != key_slices.end();
         ++it)
    {
      ret.insert(make_pair((*it).key, getSuperColumnList((*it).columns)));
    }
  }
  return ret;
}


vector<Column> Keyspace::getColumnList(vector<ColumnOrSuperColumn> &cols)
{
  vector<Column> ret(cols.size());
  for (vector<ColumnOrSuperColumn>::iterator it= cols.begin();
       it != cols.end();
       ++it)
  {
    ret.push_back((*it).column);
  }
  return ret;
}


vector<SuperColumn> Keyspace::getSuperColumnList(vector<ColumnOrSuperColumn> &cols)
{
  vector<SuperColumn> ret(cols.size());
  for (vector<ColumnOrSuperColumn>::iterator it= cols.begin();
       it != cols.end();
       ++it)
  {
    ret.push_back((*it).super_column);
  }
  return ret;
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
