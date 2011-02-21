/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_UTIL_FUNCTIONS_H
#define __LIBCASSANDRA_UTIL_FUNCTIONS_H

#include <string>

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/column_family_definition.h"
#include "libcassandra/keyspace_definition.h"


namespace libcassandra
{


/**
 * @param[in] url to parse
 * @return the port number from the given url
 */
int parsePortFromURL(const std::string &url);


/**
 * @param[in] url to parse
 * @return the host namefrom the given url
 */
std::string parseHostFromURL(const std::string &url);

/**
 * Convert a KeyspaceDefinition object to the thrift 
 * equivalent - KsDef
 * @param[in] ks_def a KeyspaceDefinition object
 * @return a thrift KsDef object equivalent to the ks_def input
 */
org::apache::cassandra::KsDef createKsDefObject(const KeyspaceDefinition& ks_def);

/**
 * Convert a ColumnFamilyDefinition object to the thrift 
 * equivalent - CfDef
 * @param[in] cf_def a ColumnFamilyDefinition object
 * @return a thrift CfDef object equivalent to the cf_def input
 */
org::apache::cassandra::CfDef createCfDefObject(const ColumnFamilyDefinition& ks_def);

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_UTIL_FUNCTIONS_H */
