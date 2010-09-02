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

#include "cassandra_host.h"
#include "util_functions.h"

using namespace std;

namespace libcassandra
{

int parsePortFromURL(const string &url)
{
  size_t pos= url.find_first_of(":");
  int found_port= CassandraHost::DEFAULT_PORT;
  if (pos == string::npos)
  {
    return found_port;
  }
  istringstream port_stream(url.substr(pos + 1));
  port_stream >> found_port;
  return found_port;
}


string parseHostFromURL(const string &url)
{
  size_t pos= url.find_first_of(":");
  if (pos == string::npos)
  {
    return url;
  }
  return url.substr(0, pos);
}

} /* end namespace libcassandra */
