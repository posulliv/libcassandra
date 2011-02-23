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

#include "libcassandra/cassandra_host.h"

using namespace std;
using namespace org::apache::cassandra;


IndexedSlicesQuery::IndexedSlicesQuery()
  :
    keyspace(),
    column_family(),
    start_key(),
    count(0),
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


void IndexedSlicesQuery::setColumnFamily(const string& column_family_name)
{
  column_family.assign(column_family_name);
}


void IndexedSlicesQuery::setStartKey(const string& new_start_key)
{
  index_clause.start_key.assign(new_start_key);
}


void IndexedSlicesQuery::setCount(int32_t new_count)
{
  index_clause.count= new_count;
}

