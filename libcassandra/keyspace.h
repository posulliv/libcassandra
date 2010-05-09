/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_KEYSPACE_H
#define __LIBCASSANDRA_KEYSPACE_H

#include <string>
#include <map>
#include <vector>

#include <libgenthrift/cassandra_types.h>

namespace libcassandra
{

class Cassandra;

class Keyspace
{

public:

  Keyspace(Cassandra *in_client,
           const std::string &in_name,
           const std::map< std::string, std::map<std::string, std::string> > &in_desc,
           org::apache::cassandra::ConsistencyLevel in_level);
  ~Keyspace() {}

  /**
   * Insert a column, possibly inside a supercolumn
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name (optional)
   * @param[in] column_name the column name
   * @param[in] value the column value
   */
  void insertColumn(const std::string &key,
                    const std::string &column_family,
                    const std::string &super_column_name,
                    const std::string &column_name,
                    const std::string &value);

  /**
   * Insert a column, directly in a columnfamily
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] column_name the column name
   * @param[in] value the column value
   */
  void insertColumn(const std::string &key,
                    const std::string &column_family,
                    const std::string &column_name,
                    const std::string &value);

  /**
   * Removes all the columns that match the given column path
   *
   * @param[in] key the column or super column key
   * @param[in] col_path the path to the column or super column
   */
  void remove(const std::string &key,
              const org::apache::cassandra::ColumnPath &col_path);

  /**
   * Removes all the columns that match the given arguments
   * Can remove all under a column family, an individual column or supercolumn under a column family, or an individual column under a supercolumn
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name (optional)
   * @param[in] column_name the column name (optional)
   */
  void remove(const std::string &key,
              const std::string &column_family,
              const std::string &super_column_name,
              const std::string &column_name);

  /**
   * Remove a column, possibly inside a supercolumn
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name (optional)
   * @param[in] column_name the column name (optional)
   */
  void removeColumn(const std::string &key,
                    const std::string &column_family,
                    const std::string &super_column_name,
                    const std::string &column_name);


  /**
   * Remove a super column and all columns under it
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name
   */
  void removeSuperColumn(const std::string &key,
                         const std::string &column_family,
                         const std::string &super_column_name);

  /**
   * Rertieve a column.
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name (optional)
   * @param[in] column_name the column name (optional)
   * @return a column
   */
  org::apache::cassandra::Column getColumn(const std::string &key,
                                           const std::string &column_family,
                                           const std::string &super_column_name,
                                           const std::string &column_name);

  /**
   * Retrieve a column
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] column_name the column name (optional)
   * @return a column
   */
  org::apache::cassandra::Column getColumn(const std::string &key,
                                           const std::string &column_family,
                                           const std::string &column_name);

  /**
   * Retrieve a column value
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] super_column_name the super column name (optional)
   * @param[in] column_name the column name (optional)
   * @return the value for the column that corresponds to the given parameters
   */
  std::string getColumnValue(const std::string &key,
                             const std::string &column_family,
                             const std::string &super_column_name,
                             const std::string &column_name);

  /**
   * Retrieve a column value
   *
   * @param[in] key the column key
   * @param[in] column_family the column family
   * @param[in] column_name the column name (optional)
   * @return the value for the column that corresponds to the given parameters
   */
  std::string getColumnValue(const std::string &key,
                             const std::string &column_family,
                             const std::string &column_name);

  org::apache::cassandra::SuperColumn getSuperColumn(const std::string &key,
                                                     const std::string &column_family,
                                                     const std::string &super_column_name);

  std::vector<org::apache::cassandra::Column> getSliceNames(const std::string &key,
                                                            const org::apache::cassandra::ColumnParent &col_parent,
                                                            org::apache::cassandra::SlicePredicate &pred);

  std::vector<org::apache::cassandra::Column> getSliceRange(const std::string &key,
                                                            const org::apache::cassandra::ColumnParent &col_parent,
                                                            org::apache::cassandra::SlicePredicate &pred);

  std::map<std::string, std::vector<org::apache::cassandra::Column> >
  getRangeSlice(const org::apache::cassandra::ColumnParent &col_parent,
                const org::apache::cassandra::SlicePredicate &pred,
                const std::string &start,
                const std::string &finish,
                const int32_t count);

  std::map<std::string, std::vector<org::apache::cassandra::SuperColumn> >
  getSuperRangeSlice(const org::apache::cassandra::ColumnParent &col_parent,
                     const org::apache::cassandra::SlicePredicate &pred,
                     const std::string &start,
                     const std::string &finish,
                     const int32_t count);


  /**
   * @return number of columns in a row or super column
   */
  int32_t getCount(const std::string &key,
                   const org::apache::cassandra::ColumnParent &col_parent);

  /**
   * @return name of this keyspace
   */
  std::string getName();

  /**
   * @return the consistency level for this keyspace
   */
  org::apache::cassandra::ConsistencyLevel getConsistencyLevel() const;

  /**
   * @return the keyspace description
   */
  std::map< std::string, std::map<std::string, std::string> > getDescription();

private:

  /**
   * @return a timestamp in micro-seconds
   */
  int64_t createTimestamp();

  std::vector<org::apache::cassandra::Column>
  getColumnList(std::vector<org::apache::cassandra::ColumnOrSuperColumn> &cols);

  std::vector<org::apache::cassandra::SuperColumn>
  getSuperColumnList(std::vector<org::apache::cassandra::ColumnOrSuperColumn> &cols);

  void validateColumnPath(const org::apache::cassandra::ColumnPath &col_path);

  void validateSuperColumnPath(const org::apache::cassandra::ColumnPath &col_path);

  Cassandra *client;

  std::string name;

  std::map< std::string, std::map<std::string, std::string> > keyspace_desc;

  org::apache::cassandra::ConsistencyLevel level;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_KEYSPACE_H */
