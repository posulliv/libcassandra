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

#include <libgenthrift/Cassandra.h>

#include "cassandra.h"

using namespace std;
using namespace org::apache::cassandra;
using namespace libcassandra;

Cassandra::Cassandra(CassandraClient *in_thrift_client,
                     const string &in_host,
                     int in_port)
  :
    thrift_client(in_thrift_client),
    host(in_host),
    port(in_port),
    cluster_name(),
    server_version()
{}


Cassandra::~Cassandra()
{
  delete thrift_client;
}


CassandraClient *Cassandra::getCassandra()
{
  return thrift_client;
}


void Cassandra::getKeyspaces(set<string> &key_spaces)
{
  thrift_client->describe_keyspaces(key_spaces);
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


void Cassandra::getStringProperty(string &return_val, const string &property)
{
  thrift_client->get_string_property(return_val, property);
}
