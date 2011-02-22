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
#include <set>
#include <sstream>

#include "libgenthrift/Cassandra.h"

#include "libcassandra/cassandra.h"
#include "libcassandra/exception.h"
#include "libcassandra/keyspace.h"
#include "libcassandra/keyspace_definition.h"
#include "libcassandra/util_functions.h"

using namespace std;
using namespace org::apache::cassandra;
using namespace libcassandra;

/* utility functions */

template<class T>
inline string toString(const T &tt)
{
  stringstream ss;
  ss << tt;
  return ss.str();
}


Cassandra::Cassandra()
  :
    thrift_client(NULL),
	host(),
	port(0),
	cluster_name(),
	server_version(),
	current_keyspace(),
	key_spaces(),
	token_map()
{
}


Cassandra::Cassandra(CassandraClient *in_thrift_client,
                     const string &in_host,
                     int in_port)
  :
    thrift_client(in_thrift_client),
    host(in_host),
    port(in_port),
    cluster_name(),
    server_version(),
    current_keyspace(),
    key_spaces(),
    token_map()
{}


Cassandra::Cassandra(CassandraClient *in_thrift_client,
                     const string &in_host,
                     int in_port,
                     const string& keyspace)
  :
    thrift_client(in_thrift_client),
    host(in_host),
    port(in_port),
    cluster_name(),
    server_version(),
    current_keyspace(keyspace),
    key_spaces(),
    token_map()
{}


Cassandra::~Cassandra()
{
  delete thrift_client;
}


CassandraClient *Cassandra::getCassandra()
{
  return thrift_client;
}


void Cassandra::login(const string& user, const string& password)
{
  AuthenticationRequest req;
  req.credentials["username"]= user;
  req.credentials["password"]= password;
  thrift_client->login(req);
}


void Cassandra::setKeyspace(const string& ks_name)
{
  current_keyspace.assign(ks_name);
  thrift_client->set_keyspace(ks_name);
}


string Cassandra::getCurrentKeyspace() const
{
  return current_keyspace;
}


void Cassandra::insertColumn(const string& key,
                             const string& column_family,
                             const string& super_column_name,
                             const string& column_name,
                             const string& value,
                             ConsistencyLevel::type level,
			     int32_t ttl)
{
  ColumnParent col_parent;
  col_parent.column_family.assign(column_family);
  if (! super_column_name.empty()) 
  {
    col_parent.super_column.assign(super_column_name);
    col_parent.__isset.super_column= true;
  }
  Column col;
  col.name.assign(column_name);
  col.value.assign(value);
  col.timestamp= createTimestamp();
  col.ttl=ttl;
  /* 
   * actually perform the insert 
   * TODO - validate the ColumnParent before the insert
   */
  thrift_client->insert(key, col_parent, col, level);
}


void Cassandra::insertColumn(const string& key,
                             const string& column_family,
                             const string& super_column_name,
                             const string& column_name,
                             const string& value)
{
  insertColumn(key, column_family, super_column_name, column_name, value, ConsistencyLevel::QUORUM);
}


void Cassandra::insertColumn(const string& key,
                             const string& column_family,
                             const string& column_name,
                             const string& value)
{
  insertColumn(key, column_family, "", column_name, value, ConsistencyLevel::QUORUM);
}


void Cassandra::remove(const string &key,
                      const ColumnPath &col_path,
                      ConsistencyLevel::type level)
{
  thrift_client->remove(key, col_path, createTimestamp(), level);
}


void Cassandra::remove(const string &key,
                      const ColumnPath &col_path)
{
  thrift_client->remove(key, col_path, createTimestamp(), ConsistencyLevel::QUORUM);
}


void Cassandra::remove(const string& key,
                       const string& column_family,
                       const string& super_column_name,
                       const string& column_name)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  if (! super_column_name.empty()) 
  {
    col_path.super_column.assign(super_column_name);
    col_path.__isset.super_column= true;
  }
  if (! column_name.empty()) 
  {
    col_path.column.assign(column_name);
    col_path.__isset.column= true;
  }
  remove(key, col_path);
}


void Cassandra::removeColumn(const string& key,
                             const string& column_family,
                             const string& super_column_name,
                             const string& column_name)
{
  remove(key, column_family, super_column_name, column_name);
}


void Cassandra::removeSuperColumn(const string& key,
                                  const string& column_family,
                                  const string& super_column_name)
{
  remove(key, column_family, super_column_name, "");
}


Column Cassandra::getColumn(const string& key,
                            const string& column_family,
                            const string& super_column_name,
                            const string& column_name,
                            ConsistencyLevel::type level)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  if (! super_column_name.empty()) 
  {
    col_path.super_column.assign(super_column_name);
    col_path.__isset.super_column= true;
  }
  col_path.column.assign(column_name);
  col_path.__isset.column= true;
  ColumnOrSuperColumn cosc;
  /* TODO - validate column path */
  thrift_client->get(cosc, key, col_path, level);
  if (cosc.column.name.empty())
  {
    /* throw an exception */
    throw(InvalidRequestException());
  }
  return cosc.column;
}


Column Cassandra::getColumn(const string& key,
                            const string& column_family,
                            const string& super_column_name,
                            const string& column_name)
{
  return getColumn(key, column_family, super_column_name, column_name, ConsistencyLevel::QUORUM);
}

Column Cassandra::getColumn(const string& key,
                            const string& column_family,
                            const string& column_name)
{
  return getColumn(key, column_family, "", column_name, ConsistencyLevel::QUORUM);
}


string Cassandra::getColumnValue(const string& key,
                                 const string& column_family,
                                 const string& super_column_name,
                                 const string& column_name)
{
  return getColumn(key, column_family, super_column_name, column_name).value;
}


string Cassandra::getColumnValue(const string& key,
                                 const string& column_family,
                                 const string& column_name)
{
	return getColumn(key, column_family, column_name).value;
}


SuperColumn Cassandra::getSuperColumn(const string& key,
                                      const string& column_family,
                                      const string& super_column_name,
                                      ConsistencyLevel::type level)
{
  ColumnPath col_path;
  col_path.column_family.assign(column_family);
  col_path.super_column.assign(super_column_name);
  /* this is ugly but thanks to thrift is needed */
  col_path.__isset.super_column= true;
  ColumnOrSuperColumn cosc;
  /* TODO - validate super column path */
  thrift_client->get(cosc, key, col_path, level);
  if (cosc.super_column.name.empty())
  {
    /* throw an exception */
    throw(InvalidRequestException());
  }
  return cosc.super_column;
}


SuperColumn Cassandra::getSuperColumn(const string& key,
                                      const string& column_family,
                                      const string& super_column_name)
{
  return getSuperColumn(key, column_family, super_column_name, ConsistencyLevel::QUORUM);
}


vector<Column> Cassandra::getSliceNames(const string& key,
                                        const ColumnParent& col_parent,
                                        SlicePredicate& pred,
                                        ConsistencyLevel::type level)
{
  vector<ColumnOrSuperColumn> ret_cosc;
  vector<Column> result;
  /* damn you thrift! */
  pred.__isset.column_names= true;
  thrift_client->get_slice(ret_cosc, key, col_parent, pred, level);
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


vector<Column> Cassandra::getSliceNames(const string& key,
                                        const ColumnParent& col_parent,
                                        SlicePredicate& pred)
{
  return getSliceNames(key, col_parent, pred, ConsistencyLevel::QUORUM);
}


vector<Column> Cassandra::getSliceRange(const string& key,
                                        const ColumnParent& col_parent,
                                        SlicePredicate& pred,
                                        ConsistencyLevel::type level)
{
  vector<ColumnOrSuperColumn> ret_cosc;
  vector<Column> result;
  /* damn you thrift! */
  pred.__isset.slice_range= true;
  thrift_client->get_slice(ret_cosc, key, col_parent, pred, level);
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


vector<Column> Cassandra::getSliceRange(const string& key,
                                        const ColumnParent& col_parent,
                                        SlicePredicate& pred)
{
  return getSliceRange(key, col_parent, pred, ConsistencyLevel::QUORUM);
}


map<string, vector<Column> > Cassandra::getRangeSlice(const ColumnParent& col_parent,
                                                      const SlicePredicate& pred,
                                                      const string& start,
                                                      const string& finish,
                                                      const int32_t row_count,
                                                      ConsistencyLevel::type level)
{
  map<string, vector<Column> > ret;
  vector<KeySlice> key_slices;
  KeyRange key_range;
  key_range.start_key.assign(start);
  key_range.end_key.assign(finish);
  key_range.count= row_count;
  key_range.__isset.start_key= true;
  key_range.__isset.end_key= true;
  thrift_client->get_range_slices(key_slices,
                                  col_parent,
                                  pred,
                                  key_range,
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


map<string, vector<Column> > Cassandra::getRangeSlice(const ColumnParent& col_parent,
                                                      const SlicePredicate& pred,
                                                      const string& start,
                                                      const string& finish,
                                                      const int32_t row_count)
{
  return getRangeSlice(col_parent, pred, start, finish, row_count, ConsistencyLevel::QUORUM);
}


map<string, vector<SuperColumn> > Cassandra::getSuperRangeSlice(const ColumnParent& col_parent,
                                                                const SlicePredicate& pred,
                                                                const string& start,
                                                                const string& finish,
                                                                const int32_t row_count,
                                                                ConsistencyLevel::type level)
{
  map<string, vector<SuperColumn> > ret;
  vector<KeySlice> key_slices;
  KeyRange key_range;
  key_range.start_key.assign(start);
  key_range.end_key.assign(finish);
  key_range.count= row_count;
  key_range.__isset.start_key= true;
  key_range.__isset.end_key= true;
  thrift_client->get_range_slices(key_slices,
                                  col_parent,
                                  pred,
                                  key_range,
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



map<string, vector<SuperColumn> > Cassandra::getSuperRangeSlice(const ColumnParent& col_parent,
                                                                const SlicePredicate& pred,
                                                                const string& start,
                                                                const string& finish,
                                                                const int32_t row_count)
{
  return getSuperRangeSlice(col_parent, pred, start, finish, row_count, ConsistencyLevel::QUORUM);
}


vector<Column> Cassandra::getColumnList(vector<ColumnOrSuperColumn>& cols)
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


vector<SuperColumn> Cassandra::getSuperColumnList(vector<ColumnOrSuperColumn>& cols)
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


int32_t Cassandra::getCount(const string& key, 
                            const ColumnParent& col_parent,
                            const SlicePredicate& pred,
                            ConsistencyLevel::type level)
{
  return (thrift_client->get_count(key, col_parent, pred, level));
}


int32_t Cassandra::getCount(const string& key, 
                            const ColumnParent& col_parent,
                            const SlicePredicate& pred)
{
  return (getCount(key, col_parent, pred, ConsistencyLevel::QUORUM));
}


vector<KeyspaceDefinition> Cassandra::getKeyspaces()
{
  if (key_spaces.empty())
  {
    vector<KsDef> thrift_ks_defs;
    thrift_client->describe_keyspaces(thrift_ks_defs);
    for (vector<KsDef>::iterator it= thrift_ks_defs.begin();
         it != thrift_ks_defs.end();
         ++it)
    {
      KsDef thrift_entry= *it;
      KeyspaceDefinition entry(thrift_entry.name,
                               thrift_entry.strategy_class,
                               thrift_entry.strategy_options,
                               thrift_entry.replication_factor,
                               thrift_entry.cf_defs);
      key_spaces.push_back(entry);
    }
  }
  return key_spaces;
}


string Cassandra::createColumnFamily(const ColumnFamilyDefinition& cf_def)
{
  string schema_id;
  CfDef thrift_cf_def= createCfDefObject(cf_def);
  thrift_client->system_add_column_family(schema_id, thrift_cf_def);
  return schema_id;
}


string Cassandra::dropColumnFamily(const string& cf_name)
{
  string schema_id;
  thrift_client->system_drop_column_family(schema_id, cf_name);
  return schema_id;
}


string Cassandra::createKeyspace(const KeyspaceDefinition& ks_def)
{
  string ret;
  KsDef thrift_ks_def= createKsDefObject(ks_def);
  thrift_client->system_add_keyspace(ret, thrift_ks_def);
  return ret;
}


string Cassandra::dropKeyspace(const string& ks_name)
{
  string ret;
  thrift_client->system_drop_keyspace(ret, ks_name);
  return ret;
}


string Cassandra::getClusterName()
{
  if (cluster_name.empty())
  {
    thrift_client->describe_cluster_name(cluster_name);
  }
  return cluster_name;
}


string Cassandra::getServerVersion()
{
  if (server_version.empty())
  {
    thrift_client->describe_version(server_version);
  }
  return server_version;
}


string Cassandra::getHost()
{
  return host;
}


int Cassandra::getPort() const
{
  return port;
}


string Cassandra::buildKeyspaceMapName(string keyspace, int level)
{
  keyspace.append("[");
  keyspace.append(toString(level));
  keyspace.append("]");
  return keyspace;
}


bool Cassandra::findKeyspace(const string& name)
{
  for (vector<KeyspaceDefinition>::iterator it= key_spaces.begin();
       it != key_spaces.end();
       ++it)
  {
    if (name == it->getName())
    {
      return true;
    }
  }
  return false;
}


int64_t Cassandra::createTimestamp()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (int64_t) tv.tv_sec * 1000000 + (int64_t) tv.tv_usec;
}

