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

#include <libgenthrift/Cassandra.h>

#include "cassandra.h"
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

CassandraFactory::~CassandraFactory() {}


tr1::shared_ptr<Cassandra> CassandraFactory::create()
{
  CassandraClient *thrift_client= createThriftClient(host, port);
  tr1::shared_ptr<Cassandra> ret(new Cassandra(thrift_client, host, port));
  return ret;
}


CassandraClient *CassandraFactory::createThriftClient(const string &in_host,
                                                      int in_port)
{
  boost::shared_ptr<TTransport> socket(new TSocket(in_host, in_port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new(std::nothrow) CassandraClient(protocol);

  transport->open(); /* throws an exception */

  return client;
}

