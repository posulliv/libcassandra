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

  CassandraFactory(const std::string &in_host, int in_port);
  ~CassandraFactory() {}

  Cassandra *create();

private:

  org::apache::cassandra::CassandraClient *createThriftClient(const std::string &host,
                                                              int port);

  std::string host;

  int port;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_CASSANDRA_FACTORY_H */
