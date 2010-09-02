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
#include "util_functions.h"

using namespace std;
using namespace libcassandra;


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
  host= parseHostFromURL(url);
  port= parsePortFromURL(url);
}


CassandraHost::CassandraHost(const string &in_host, int in_port)
  :
    name(),
    host(in_host),
    ip_address(),
    url(),
    port(in_port)
{
  url.append(host);
  url.append(":");
  ostringstream port_str;
  port_str << port;
  url.append(port_str.str());
}


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

