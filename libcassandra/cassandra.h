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
#include <set>
#include <map>
#include <tr1/memory>

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/keyspace_definition.h"

namespace org
{
namespace apache
{
namespace cassandra
{
class CassandraClient;
}
}
}

namespace libcassandra
{

class Keyspace;

class Cassandra
{

public:

  Cassandra();
  Cassandra(org::apache::cassandra::CassandraClient *in_thrift_client,
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
   * @return the underlying cassandra thrift client.
   */
  org::apache::cassandra::CassandraClient *getCassandra();

  /**
   * @return all the keyspace definitions.
   */
  std::vector<KeyspaceDefinition> getKeyspaces();

  /**
   * @return the keyspace with the given name.
   */
  std::tr1::shared_ptr<Keyspace> getKeyspace(const std::string &name);

  /**
   * @return the keyspace with the given name at the given consistency level.
   */
  std::tr1::shared_ptr<Keyspace> getKeyspace(const std::string &name, org::apache::cassandra::ConsistencyLevel::type level);

  /**
   * Remove the given keyspace.
   */
  void removeKeyspace(std::tr1::shared_ptr<Keyspace> k);

  /**
   * @return the target server cluster name.
   */
  std::string getClusterName();

  /**
   * @return the server version.
   */
  std::string getServerVersion();

  /**
   * @return a string property from the server
   */
  void getStringProperty(std::string &return_val, const std::string &property);

  /**
   * @return hostname
   */
  std::string getHost();

  /**
   * @return port number
   */
  int getPort() const;

private:

  /**
   * Creates a unique map name for the keyspace and its consistency level
   */
  std::string buildKeyspaceMapName(std::string keyspace, int level);

  /**
   * Finds the given keyspace in the list of keyspace definitions
   * @return true if found; false otherwise
   */
  bool findKeyspace(const std::string& name);

  org::apache::cassandra::CassandraClient *thrift_client;
  std::string host;
  int port;
  std::string cluster_name;
  std::string server_version;
  std::string config_file;
  std::vector<KeyspaceDefinition> key_spaces;
  std::map<std::string, std::string> token_map;
  std::map<std::string, std::tr1::shared_ptr<Keyspace> > keyspace_map;

  Cassandra(const Cassandra&);
  Cassandra &operator=(const Cassandra&);

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_H */
