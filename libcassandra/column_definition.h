/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_COLUMN_DEFINITION_H
#define __LIBCASSANDRA_COLUMN_DEFINITION_H

#include <string>
#include <map>
#include <vector>

#include "libgenthrift/cassandra_types.h"

namespace libcassandra
{

class Cassandra;

class ColumnDefinition
{

public:

  ColumnDefinition();
  ColumnDefinition(const std::string& in_name,
                   const std::string& in_validation_class,
                   const org::apache::cassandra::IndexType::type in_index_type,
                   const std::string& in_index_name);
  ~ColumnDefinition() {}

  /**
   * @return column name
   */
  std::string getName() const;

  /**
   * @return validation class name for this keyspace
   */
  std::string getValidationClass() const;

  /**
   * @return the index type for this column
   */
  org::apache::cassandra::IndexType::type getIndexType() const;

  /**
   * @return index name
   */
  std::string getIndexName() const;

private:

  std::string name;

  std::string validation_class;

  org::apache::cassandra::IndexType::type index_type;

  std::string index_name;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_COLUMN_DEFINITION_H */
