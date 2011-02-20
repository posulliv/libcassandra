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
  /* 
   * keyspace name and cf name are required 
   * TODO - throw an exception if these are not present
   */
  thrift_cf_def.keyspace.assign(cf_def.getKeyspaceName());
  thrift_cf_def.name.assign(cf_def.getName());
  /* everything else associated with a column family is optional */
  if (cf_def.isColumnTypeSet())
  {
    thrift_cf_def.column_type.assign(cf_def.getColumnType());
    thrift_cf_def.__isset.column_type= true;
  }
  if (cf_def.isComparatorTypeSet())
  {
    thrift_cf_def.comparator_type.assign(cf_def.getComparatorType());
    thrift_cf_def.__isset.comparator_type= true;
  }
  if (cf_def.isSubComparatorTypeSet())
  {
    thrift_cf_def.subcomparator_type.assign(cf_def.getSubComparatorType());
    thrift_cf_def.__isset.subcomparator_type= true;
  }
  if (cf_def.isCommentSet())
  {
    thrift_cf_def.comment.assign(cf_def.getComment());
    thrift_cf_def.__isset.comment= true;
  }
  return thrift_cf_def;
}

} /* end namespace libcassandra */
