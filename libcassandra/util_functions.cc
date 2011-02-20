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

#include "libcassandra/cassandra_host.h"
#include "libcassandra/util_functions.h"

using namespace std;
using namespace org::apache::cassandra;

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


KsDef createKsDefObject(const KeyspaceDefinition& ks_def)
{
  KsDef thrift_ks_def;
  thrift_ks_def.name.assign(ks_def.getName());
  thrift_ks_def.strategy_class.assign(ks_def.getStrategyClass());
  return thrift_ks_def;
}


CfDef createCfDefObject(const ColumnFamilyDefinition& cf_def)
{
  CfDef thrift_cf_def;
  thrift_cf_def.keyspace.assign(cf_def.getKeyspaceName());
  thrift_cf_def.name.assign(cf_def.getName());
  thrift_cf_def.column_type.assign(cf_def.getColumnType());
  return thrift_cf_def;
}

} /* end namespace libcassandra */
