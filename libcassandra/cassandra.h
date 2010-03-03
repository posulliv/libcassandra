/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_CASSANDRA_H
#define __LIBCASSANDRA_CASSANDRA_H

#include <string>
#include <vector>

namespace libcassandra
{

class CassandraClient
{
public:

  enum FailoverPolicy
  {
    FAIL_FAST= 0,
    ON_FAIL_TRY_ONE_NEXT_AVAILABLE,
    ON_FAIL_TRY_ALL_AVAILABLE
  };

  /**
   * Return given key space, if the given key space does not exist, throw an exception.
   */
  Keyspace getKeyspace(const std::string &keyspace_name);

  /**
   * Return a keyspace with the given consistency level.
   */
  Keyspace getKeyspace(const std::string &keyspace_name,
                       uint32_t consistency_level,
                       FailoverPolicy failover_policy);

  /**
   * Remove the given keyspace.
   */
  void removeKeyspace(Keyspace &key_space);

  /**
   * Return all the keyspace names. Populate the vector passed to this method.
   */
  void getKeyspaces(std::vector<std::string> &key_spaces);

  /**
   * Return the target server cluster name.
   */
  std::string getClusterName();

  /**
   * Return the config file content.
   */
  std::string getConfigFile();

  /**
   * Return the server version.
   */
  std::string getServerVersion();

private:

  /** list of known keyspaces */
  std::vector<std::string> keyspaces;
  std::string cluster_name;
  std::string config_file;
  std::string server_version;

};

} /* end namespace cassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_H */
