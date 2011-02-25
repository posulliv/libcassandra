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
    column_reversed(false),
    count(100),
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


map<string, map<string, string> > IndexedSlicesQuery::execute(tr1::shared_ptr<Cassandra> client)
{
  map<string, map<string, string> > ret_map;
  vector<KeySlice> ret;

  SliceRange thrift_slice_range;
  SlicePredicate thrift_slice_pred;
  ColumnParent col_parent;
  thrift_slice_pred.slice_range= thrift_slice_range;
  thrift_slice_pred.__isset.slice_range= true;
  col_parent.column_family.assign(column_family);

  client->getCassandra()->get_indexed_slices(ret, col_parent, index_clause, thrift_slice_pred, ConsistencyLevel::QUORUM);

  for (vector<KeySlice>::iterator it= ret.begin();
       it != ret.end();
       ++it)
  {
    vector<Column> thrift_cols= getColumnList((*it).columns);
    map<string, string> rows;
    for (vector<Column>::iterator inner_it= thrift_cols.begin();
         inner_it != thrift_cols.end();
         ++inner_it)
    {
      rows.insert(make_pair((*inner_it).name, (*inner_it).value));
    }
    ret_map.insert(make_pair((*it).key, rows));
  }

  return ret_map;
}

