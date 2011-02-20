/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_CASSANDRA_FACTORY_H
#define __LIBCASSANDRA_CASSANDRA_FACTORY_H

#include <string>
#include <vector>
#include <tr1/memory>

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

class Cassandra;

class CassandraFactory
{

public:

  CassandraFactory(const std::string &server_list);
  CassandraFactory(const std::string &in_host, int in_port);
  ~CassandraFactory();

  /**
   * @return a shared ptr which points to a Cassandra client
   */
  std::tr1::shared_ptr<Cassandra> create();

  int getPort() const;
  const std::string &getHost() const;
  const std::string &getURL() const;

private:

  org::apache::cassandra::CassandraClient *createThriftClient(const std::string &host,
                                                              int port);

  std::string url;

  std::string host;

  int port;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_FACTORY_H */
