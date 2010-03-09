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
#include "keyspace.h"

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


set<string> Cassandra::getKeyspaces()
{
  if (key_spaces.empty())
  {
    thrift_client->describe_keyspaces(key_spaces);
  }
  return key_spaces;
}


Keyspace *Cassandra::getKeyspace(const string &name)
{
  Keyspace *ret= keyspace_map[name];
  if (! ret)
  {
    getKeyspaces();
  }
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


string Cassandra::getConfigFile()
{
  if (config_file.empty())
  {
    thrift_client->get_string_property(config_file, "config file");
  }
  return config_file;
}


map<string, string> Cassandra::getTokenMap(bool fresh)
{
  if (token_map.empty() || fresh)
  {
    token_map.clear();
    string str_tokens;
    thrift_client->get_string_property(str_tokens, "token map");
    /* parse the tokens which are in the form {"token1":"host1","token2":"host2"} */
    /* first remove the { brackets on either side */
    str_tokens.erase(0, 1);
    str_tokens.erase(str_tokens.length() - 1, 1);
    /* now build a vector of token pairs */
    vector<string> token_pairs;
    string::size_type last_pos= str_tokens.find_first_not_of(',', 0);
    string::size_type pos= str_tokens.find_first_of(',', last_pos);
    while (pos != string::npos || last_pos != string::npos)
    {
      token_pairs.push_back(str_tokens.substr(last_pos, pos - last_pos));
      last_pos= str_tokens.find_first_not_of(',', pos);
      pos= str_tokens.find_first_of(',', last_pos);
    }
    /* now iterate through the token pairs and populate the map */
    for (vector<string>::iterator it= token_pairs.begin();
         it != token_pairs.end();
         ++it)
    {
      string input= *it;
      pos= input.find_first_of(':', 0);
      string token= input.substr(0, pos);
      string the_host= input.substr(pos + 1);
      token.erase(0, 1);
      token.erase(token.length() - 1, 1);
      the_host.erase(0, 1);
      the_host.erase(the_host.length() - 1, 1);
      token_map[token]= the_host;
    }
  }
  return token_map;
}


void Cassandra::getStringProperty(string &return_val, const string &property)
{
  thrift_client->get_string_property(return_val, property);
}


string Cassandra::getHost()
{
  return host;
}


int Cassandra::getPort() const
{
  return port;
}


