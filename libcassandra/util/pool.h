/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_UTIL_POOL_H
#define __LIBCASSANDRA_UTIL_POOL_H

#include <string>
#include <vector>
#include <set>
#include <tr1/memory>

#include "libcassandra/cassandra.h"

namespace libcassandra
{

namespace util
{

class CassandraPool
{

  CassandraPool(const std::string& hostname,
                int port,
                uint32_t initial,
                uint32_t max);
  ~CassandraPool() {}

  /**
   * Add a connection for the given connection parameters
   * to the connection pool
   * @param[in] host the hostname of a cassandra server
   * @param[in] port the port number of a cassandra server
   * @param[in] count number of instances of this server to add to the pool
   * @return true if server was added to pool successfully; false otherwise
   */
  bool addServer(const std::string& hostname, int port, uint32_t count);

  /**
   * Add the given client to the connection pool
   * @param[in] client an instance of a Cassandra client
   * @return true on sucess; false otherwise
   */
  bool addConnection(tr1::shared_ptr<Cassandra> client);

  /**
   * This function returns a Cassandra connection object
   * and removes it from the pool of connections
   * @return a connection from the pool of connections
   */
  tr1::shared_ptr<Cassandra> getConnection();

private:

  uint32_t max_size;

  uint32_t current_size;

  std::set<std::string> unique_hosts;

  std::vector<tr1::shared_ptr<Cassandra> > clients;

};

} /* end namespace util */

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_UTIL_POOL_H */
