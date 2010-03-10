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

  void insertColumn(const std::string &key,
                    const std::string &column_family,
                    const std::string &column_name,
                    const std::string &value);

  void insertSuperColumn(const std::string &key,
                         const std::string &column_family,
                         const std::string &column_name,
                         const std::string &value);

  void remove(const std::string &key,
              const org::apache::cassandra::ColumnPath &col_path);

  org::apache::cassandra::Column getColumn(const std::string &key,
                                           const std::string &column_family,
                                           const std::string &column_name);

  std::string getColumnValue(const std::string &key,
                             const std::string &column_family,
                             const std::string &column_name);

  std::vector<org::apache::cassandra::Column> getSlice(const std::string &key,
                                                       const org::apache::cassandra::ColumnParent &col_parent,
                                                       const org::apache::cassandra::SlicePredicate &pred);

  int32_t getCount(const std::string &key,
                   const org::apache::cassandra::ColumnParent &col_parent);

  std::string getName();

  org::apache::cassandra::ConsistencyLevel getConsistencyLevel() const;

private:

  int64_t createTimestamp();

  void validateColumnPath(const org::apache::cassandra::ColumnPath &col_path);

  void validateSuperColumnPath(const org::apache::cassandra::ColumnPath &col_path);

  Cassandra *client;

  std::string name;

  std::map< std::string, std::map<std::string, std::string> > keyspace_desc;

  org::apache::cassandra::ConsistencyLevel level;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_KEYSPACE_H */
