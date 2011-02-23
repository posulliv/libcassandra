/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <vector>
#include <map>

#include "libcassandra/column_definition.h"

using namespace libcassandra;
using namespace std;
using namespace org::apache::cassandra;


ColumnDefinition::ColumnDefinition()
  :
    name(),
    validation_class(),
    index_type(),
    is_index_type_set(false),
    index_name()
{}


ColumnDefinition::ColumnDefinition(const string& in_name,
                                   const string& in_validation_class,
                                   const IndexType::type in_index_type,
                                   const string& in_index_name)
  :
    name(in_name),
    validation_class(in_validation_class),
    index_type(in_index_type),
    is_index_type_set(true),
    index_name(in_index_name)
{}


string ColumnDefinition::getName() const
{
  return name;
}


void ColumnDefinition::setName(const string& new_name)
{
  name.assign(new_name);
}


string ColumnDefinition::getValidationClass() const
{
  return validation_class;
}


void ColumnDefinition::setValidationClass(const string& class_name)
{
  validation_class.assign(class_name);
}


IndexType::type ColumnDefinition::getIndexType() const
{
  return index_type;
}


void ColumnDefinition::setIndexType(IndexType::type new_type)
{
  index_type= new_type;
  is_index_type_set= true;
}


bool ColumnDefinition::isIndexTypeSet() const
{
  return is_index_type_set;
}


string ColumnDefinition::getIndexName() const
{
  return index_name;
}


void ColumnDefinition::setIndexName(const string& new_name)
{
  index_name.assign(new_name);
}


bool ColumnDefinition::isIndexNameSet() const
{
  return (! index_name.empty());
}
