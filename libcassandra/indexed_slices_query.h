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

  void addIndexExpression(const std::string& column,
                          const std::string& value,
                          org::apache::cassandra::IndexOperator::type op_type);

  void setColumns(std::vector<std::string>& columns);

  std::vector<std::string> getColumns() const;

  bool isColumnsSet() const;

  bool isRangeSet() const;

  void setColumnFamily(const std::string& column_family_name);

  std::string getColumnFamily() const;

  void setStartKey(const std::string& new_start_key);

  void setRowCount(int32_t new_count);

  int32_t getRowCount() const;

  void setConsistencyLevel(org::apache::cassandra::ConsistencyLevel::type new_level);

  org::apache::cassandra::ConsistencyLevel::type getConsistencyLevel() const;

  void setReverseColumns(bool to_reverse);

  bool getReverseColumns() const;

  void setRange(const std::string& start,
                const std::string& end,
                bool reversed,
                int32_t range_count);

  std::string getStartColumn() const;

  std::string getEndColumn() const;

  org::apache::cassandra::IndexClause getIndexClause() const;

private:

  std::string keyspace;

  std::string column_family;

  std::string start_key;

  std::string start_column;

  std::string end_column;

  std::vector<std::string> column_names;

  bool column_reversed;

  int32_t count;

  org::apache::cassandra::ConsistencyLevel::type level;

  org::apache::cassandra::IndexClause index_clause;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_INDEXED_SLICES_QUERY_H */
