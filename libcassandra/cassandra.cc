/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <set>
#include <sstream>

#include "libgenthrift/Cassandra.h"

#include "libcassandra/cassandra.h"
#include "libcassandra/exception.h"
#include "libcassandra/keyspace.h"
#include "libcassandra/keyspace_definition.h"

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
	config_file(),
	key_spaces(),
	token_map(),
	keyspace_map()
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
    config_file(),
    key_spaces(),
    token_map(),
    keyspace_map()
{}


Cassandra::~Cassandra()
{
  delete thrift_client;
}


CassandraClient *Cassandra::getCassandra()
{
  return thrift_client;
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


tr1::shared_ptr<Keyspace> Cassandra::getKeyspace(const string& name)
{
  return getKeyspace(name, ConsistencyLevel::LOCAL_QUORUM);
}


tr1::shared_ptr<Keyspace> Cassandra::getKeyspace(const string& name,
                                                 ConsistencyLevel::type level)
{
  string keymap_name= buildKeyspaceMapName(name, level);
  map<string, tr1::shared_ptr<Keyspace> >::iterator key_it= keyspace_map.find(keymap_name);
  if (key_it == keyspace_map.end())
  {
    getKeyspaces();
    if (findKeyspace(name))
    {
      /* TODO: the keyspace description can be returned in the findKeyspace function */
      KsDef ks_def;
      thrift_client->describe_keyspace(ks_def, name);
      KeyspaceDefinition ks_desc(ks_def.name,
                                 ks_def.strategy_class,
                                 ks_def.strategy_options,
                                 ks_def.replication_factor,
                                 ks_def.cf_defs);
      tr1::shared_ptr<Keyspace> ret(new Keyspace(this, name, ks_desc, level));
      keyspace_map[keymap_name]= ret;
    }
    else
    {
      /* throw an exception */
      throw(NotFoundException());
    }
  }
  return keyspace_map[keymap_name];
}


void Cassandra::removeKeyspace(tr1::shared_ptr<Keyspace> k)
{
  string keymap_name= buildKeyspaceMapName(k->getName(), k->getConsistencyLevel());
  keyspace_map.erase(keymap_name);
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
