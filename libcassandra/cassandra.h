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

class Cassandra
{

public:

  Cassandra(CassandraClient *in_thrift_client,
            const std::string &in_host,
            int in_port);
  ~Cassandra();

  enum FailoverPolicy
  {
    FAIL_FAST= 0,
    ON_FAIL_TRY_ONE_NEXT_AVAILABLE,
    ON_FAIL_TRY_ALL_AVAILABLE
  };

  /**
   * Return given key space, if the given key space does not exist, throw an exception.
   */
  //Keyspace getKeyspace(const std::string &keyspace_name);

  /**
   * Return a keyspace with the given consistency level.
   */
  //Keyspace getKeyspace(const std::string &keyspace_name,
   //                    int consistency_level,
    //                   FailoverPolicy failover_policy);

  /**
   * Remove the given keyspace.
   */
  //void removeKeyspace(Keyspace &key_space);

  /**
   * Return all the keyspace names. Populate the set passed to this method.
   */
  void getKeyspaces(std::set<std::string> &key_spaces);

  /**
   * Return the target server cluster name.
   */
  std::string getClusterName();

  /**
   * Return the config file content.
   */
  //std::string getConfigFile();

  /**
   * Return the server version.
   */
  std::string getServerVersion();

private:

  CassandraClient *thrift_client;
  std::string host;
  int port;
  std::string cluster_name;
  std::string server_version;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_H */
