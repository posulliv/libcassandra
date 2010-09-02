/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_CASSANDRA_HOST_H
#define __LIBCASSANDRA_CASSANDRA_HOST_H

#include <string>

namespace libcassandra
{

/**
 * @class CassandraHost
 * @brief
 *   Encapsulates the information required for connecting to
 *   a Cassandra node.
 */
class CassandraHost
{

public:

  /**
   * default port on which we will connect.
   */
  static const int DEFAULT_PORT= 9160;

  /**
   * default maximum active clients.
   */
  static const int DEFAULT_MAX_ACTIVE = 50;

  /**
   * By default, use TSocket transport in thrift
   * This matches the default cassandra configuration
   */
  static const bool FRAMED_TRANSPORT_BY_DEFAULT = false;

  CassandraHost();
  CassandraHost(const std::string &in_url);
  CassandraHost(const std::string &in_url, int in_port);
  ~CassandraHost();

  const std::string &getName() const;

  const std::string &getHost() const;

  const std::string &getIPAddress() const;

  const std::string &getURL() const;

  int getPort() const;

private:

  std::string name;

  std::string host;

  std::string ip_address;

  std::string url;

  int port;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_HOST_H */
