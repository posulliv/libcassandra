/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <vector>

#include "cassandra.h"

using namespace std;
using namespace libcassandra;

CassandraClient::CassandraClient(thrift_client,
                                 keyspace_factory,
                                 const string &url,
                                 uint32_t port,
                                 client_pool)
{}

~CassandraClient::CassandraClient() {}
