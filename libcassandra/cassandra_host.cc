/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <sstream>

#include "cassandra.h"
#include "cassandra_host.h"

using namespace libcassandra;
using namespace std;



CassandraHost::CassandraHost()
  :
    name(),
    host(),
    ip_address(),
    url(),
    port(0)
{
}


CassandraHost::CassandraHost(const string &in_url)
  :
    name(),
    host(),
    ip_address(),
    url(in_url),
    port(0)
{
}


CassandraHost::CassandraHost(const string &, int )
  :
    name(),
    host(),
    ip_address(),
    url(),
    port(0)
{}


CassandraHost::~CassandraHost() {}


const string &CassandraHost::getName() const
{
  return name;
}


const string &CassandraHost::getHost() const
{
  return host;
}


const string &CassandraHost::getIPAddress() const
{
  return ip_address;
}


const string &CassandraHost::getURL() const
{
  return url;
}


int CassandraHost::getPort() const
{
  return port;
}


int CassandraHost::parsePortFromURL(const string &in_url) const
{
  size_t pos= in_url.find_first_of(":");
  int found_port= DEFAULT_PORT;
  if (pos == string::npos)
  {
    return found_port;
  }
  istringstream port_stream(in_url.substr(pos + 1));
  port_stream >> found_port;
  return found_port;
}


string CassandraHost::parseHostFromURL(const string &in_url) const
{
  size_t pos= in_url.find_first_of(":");
  if (pos == string::npos)
  {
    return in_url;
  }
  return in_url.substr(0, pos);
}
