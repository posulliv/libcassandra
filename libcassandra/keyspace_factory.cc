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
#include "keyspace.h"
#include "keyspace_factory.h"

using namespace libcassandra;
using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace org::apache::cassandra;
using namespace boost;


KeyspaceFactory::KeyspaceFactory() {}

KeyspaceFactory::~KeyspaceFactory() {}


tr1::shared_ptr<keyspace> KeyspaceFactory::create(Cassandra *client,
                                                  const string &name,
                                                  const map< string, map<string, string> > &descrip,
                                                  ConsistencyLevel level)
{
  tr1::shared_ptr<Keyspace> ret(new Keyspace(client, name, descrip, level));
  return ret;
}

