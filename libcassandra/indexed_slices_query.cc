/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <map>
#include <tr1/memory>

#include "libgenthrift/Cassandra.h"

#include "libcassandra/cassandra.h"
#include "libcassandra/cassandra_host.h"
#include "libcassandra/indexed_slices_query.h"
#include "libcassandra/util_functions.h"

using namespace std;
using namespace libcassandra;
using namespace org::apache::cassandra;


IndexedSlicesQuery::IndexedSlicesQuery()
  :
    keyspace(),
    column_family(),
    start_key(),
    start_column(),
    end_column(),
    column_names(),
    column_reversed(false),
    count(100),
    level(ConsistencyLevel::QUORUM),
    index_clause()
{}


void IndexedSlicesQuery::addEqualsExpression(const string& column, const string& value)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= IndexOperator::EQ;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::addGtExpression(const string& column, const string& value)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= IndexOperator::GT;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::addGtEqualsExpression(const string& column, const string& value)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= IndexOperator::GTE;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::addLtExpression(const string& column, const string& value)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= IndexOperator::LT;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::addLtEqualsExpression(const string& column, const string& value)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= IndexOperator::LT;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::addIndexExpression(const string& column, 
                                            const string& value,
                                            IndexOperator::type op_type)
{
  IndexExpression new_expr;
  new_expr.column_name.assign(column);
  new_expr.value.assign(value);
  new_expr.op= op_type;
  index_clause.expressions.push_back(new_expr);
}


void IndexedSlicesQuery::setColumns(vector<string>& columns)
{
  for (vector<string>::iterator it= columns.begin();
       it != columns.end();
       ++it)
  {
    column_names.push_back(*it);
  }
}


vector<string> IndexedSlicesQuery::getColumns() const
{
  return column_names;
}


bool IndexedSlicesQuery::isColumnsSet() const
{
  return (! column_names.empty());
}


void IndexedSlicesQuery::setColumnFamily(const string& column_family_name)
{
  column_family.assign(column_family_name);
}


string IndexedSlicesQuery::getColumnFamily() const
{
  return column_family;
}


void IndexedSlicesQuery::setStartKey(const string& new_start_key)
{
  index_clause.start_key.assign(new_start_key);
}


void IndexedSlicesQuery::setRowCount(int32_t new_count)
{
  count= new_count;
  index_clause.count= new_count;
}


int32_t IndexedSlicesQuery::getRowCount() const
{
  return count;
}


IndexClause IndexedSlicesQuery::getIndexClause() const
{
  return index_clause;
}


void IndexedSlicesQuery::setReverseColumns(bool to_reverse)
{
  column_reversed= to_reverse;
}


bool IndexedSlicesQuery::getReverseColumns() const
{
  return column_reversed;
}


void IndexedSlicesQuery::setRange(const string& start,
                                  const string& end,
                                  bool reversed,
                                  int32_t range_count)
{
  start_column.assign(start);
  end_column.assign(end);
  column_reversed= reversed;
  count= range_count;
}


bool IndexedSlicesQuery::isRangeSet() const
{
  return ((! start_column.empty()) && (! end_column.empty()));
}


string IndexedSlicesQuery::getStartColumn() const
{
  return start_column;
}


string IndexedSlicesQuery::getEndColumn() const
{
  return end_column;
}


void IndexedSlicesQuery::setConsistencyLevel(ConsistencyLevel::type new_level)
{
  level= new_level;
}


ConsistencyLevel::type IndexedSlicesQuery::getConsistencyLevel() const
{
  return level;
}

