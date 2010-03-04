/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <set>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "Cassandra.h"

#include "cassandra_factory.h"

using namespace libcassandra;
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace org::apache::cassandra;
using namespace boost;


CassandraFactory::CassandraFactory(const string &in_host, int in_port)
  :
    host(in_host),
    port(in_port)
{}


Cassandra *CassandraFactory::create()
{
  CassandraClient *thrift_client= createThriftClient(host, port);
  Cassandra *ret= new(std::nothrow) Cassandra(thrift_client, host, port);
}


CassandraClient *CassandraFactory::createThriftClient(const string &host,
                                                      int port)
{
  shared_ptr<TTransport> socket(new TSocket(host, port));
  shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  shared_ptr<TTransport> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new(std::nothrow) CassandraClient(protocol);

  try
  {
    transport->open();
  }

  return client;
}

