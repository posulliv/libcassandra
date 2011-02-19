/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_KEYSPACE_DEFINITION_H
#define __LIBCASSANDRA_KEYSPACE_DEFINITION_H

#include <string>
#include <map>
#include <vector>

#include "libgenthrift/cassandra_types.h"

namespace libcassandra
{

class Cassandra;

class KeyspaceDefinition
{

public:

  KeyspaceDefinition();
  ~KeyspaceDefinition() {}

  /**
   * @return keyspace name
   */
  std::string getName() const;

  /**
   * @return strategy class name for this keyspace
   */
  std::string getStrategyClass() const;

  /**
   * @return strategy options for this keyspace
   */
  const std::map<std::string, std::string> getStrategyOptions() const;

  /**
   * @return replication factor for this keyspace
   */
  int32_t getReplicationFactor() const;

private:

  std::string name;

  std::string strategy_class;

  std::map<std::string, std::string> strategy_options;

  int32_t replication_factor;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_KEYSPACE_DEFINITION_H */
