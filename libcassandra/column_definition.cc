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
    index_name()
{}


string ColumnDefinition::getName() const
{
  return name;
}


string ColumnDefinition::getValidationClass() const
{
  return validation_class;
}


IndexType ColumnDefinition::getIndexType() const
{
  return index_type;
}


string ColumnDefinition::getIndexName() const
{
  return index_name;
}
