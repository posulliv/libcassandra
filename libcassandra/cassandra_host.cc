/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>

#include "cassandra.h"
#include "cassandra_host.h"

using namespace libcassandra;
using namespace std;


CassandraHost::CassandraHost(const string &)
  :
    name(),
    host(),
    ip_address(),
    url(),
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


int CassandraHost::getPort() const
{
  return port;
}
