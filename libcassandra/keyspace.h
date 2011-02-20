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

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/keyspace_definition.h"

namespace libcassandra
{

class Cassandra;

class Keyspace
{

public:

  Keyspace(Cassandra *in_client,
           const std::string &in_name,
           const KeyspaceDefinition& in_desc,
           org::apache::cassandra::ConsistencyLevel::type in_level);
  ~Keyspace() {}

  /**
   * @return name of this keyspace
   */
  std::string getName();

  /**
   * @return the consistency level for this keyspace
   */
  org::apache::cassandra::ConsistencyLevel::type getConsistencyLevel() const;

  /**
   * @return the keyspace definition 
   */
  KeyspaceDefinition getDefinition();

private:

  Cassandra *client;

  std::string name;

  KeyspaceDefinition keyspace_def;

  org::apache::cassandra::ConsistencyLevel::type level;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_KEYSPACE_H */
