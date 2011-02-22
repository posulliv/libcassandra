/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <sstream>
#include <iostream>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include "libgenthrift/Cassandra.h"

#include "libcassandra/util/ping.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace org::apache::cassandra;
using namespace boost;

namespace libcassandra
{


bool util::pingCassandraServer(const string& hostname, int port)
{
  try
  {
    boost::shared_ptr<TTransport> socket(new TSocket(hostname, port));
    boost::shared_ptr<TTransport> transport= boost::shared_ptr<TTransport>(new TFramedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    CassandraClient client(protocol);
    transport->open(); /* throws an exception */
  }
  catch (std::exception&)
  {
    return false;
  }

  return true;
}


} /* end namespace libcassandra */

