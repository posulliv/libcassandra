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
   * @param[in] new_name new column name
   */
  void setName(const std::string& new_name);

  /**
   * @return validation class name for this keyspace
   */
  std::string getValidationClass() const;

  /**
   * @param[in] class_name name of the validation class to use
   */
  void setValidationClass(const std::string& class_name);

  /**
   * @return the index type for this column
   */
  org::apache::cassandra::IndexType::type getIndexType() const;

  /**
   * @param[in] new_type index type for this column
   */
  void setIndexType(org::apache::cassandra::IndexType::type new_type);

  /**
   * @return true if index type is set; false otherwise
   */
  bool isIndexTypeSet() const;

  /**
   * @return index name
   */
  std::string getIndexName() const;

  /**
   * @param[in] new_name index name
   */
  void setIndexName(const std::string& new_name);

  /**
   * @return true if index name is set; false otherwise
   */
  bool isIndexNameSet() const;

private:

  std::string name;

  std::string validation_class;

  org::apache::cassandra::IndexType::type index_type;

  bool is_index_type_set;

  std::string index_name;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_COLUMN_DEFINITION_H */
