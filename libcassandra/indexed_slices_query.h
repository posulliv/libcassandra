/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_INDEXED_SLICES_QUERY_H
#define __LIBCASSANDRA_INDEXED_SLICES_QUERY_H

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/column_family_definition.h"
#include "libcassandra/keyspace_definition.h"


namespace libcassandra
{

class IndexedSlicesQuery
{
public:

  IndexedSlicesQuery();
  ~IndexedSlicesQuery() {}

  void addEqualsExpression(const std::string& column, const std::string& value);

  void addGtExpression(const std::string& column, const std::string& value);

  void addGtEqualsExpression(const std::string& column, const std::string& value);

  void addLtExpression(const std::string& column, const std::string& value);

  void addLtEqualsExpression(const std::string& column, const std::string& value);

  void setColumnFamily(const std::string& column_family_name);

  void setStartKey(const std::string& new_start_key);

  void setRowCount(int32_t new_count);

  std::map<std::string, std::map<std::string, std::string> > execute(std::tr1::shared_ptr<Cassandra> client);

private:

  std::string keyspace;

  std::string column_family;

  std::string start_key;

  std::string start_column;

  std::string end_column;

  bool column_reversed;

  int32_t count;

  org::apache::cassandra::IndexClause index_clause;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_INDEXED_SLICES_QUERY_H */
