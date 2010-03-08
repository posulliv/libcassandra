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

class Cassandra
{

public:

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
   * @return all the keyspace names. Populate the set passed to this method.
   */
  void getKeyspaces(std::set<std::string> &key_spaces);

  /**
   * @return the target server cluster name.
   */
  std::string getClusterName();

  /**
   * @return the server version.
   */
  std::string getServerVersion();

  /**
   * @return the configuration file.
   */
  std::string getConfigFile();

  /**
   * @return a string property from the server
   */
  void getStringProperty(std::string &return_val, const std::string &property);

private:

  org::apache::cassandra::CassandraClient *thrift_client;
  std::string host;
  int port;
  std::string cluster_name;
  std::string server_version;
  std::string config_file;

  Cassandra(const Cassandra&);
  Cassandra &operator=(const Cassandra&);

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_H */
