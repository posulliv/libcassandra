/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>

#include <gtest/gtest.h>

#include <libcassandra/cassandra.h>
#include <libcassandra/cassandra_factory.h>

using namespace std;
using namespace libcassandra;


TEST(CassandraFactory, ConstructorFromURL)
{
  const string url("localhost:9160");
  const CassandraFactory cf(url);
  EXPECT_EQ(9160, cf.getPort());
  EXPECT_STREQ("localhost", cf.getHost().c_str());
  EXPECT_STREQ("localhost:9160", cf.getURL().c_str());
}


TEST(CassandraFactory, ConsructorFromHostAndPort)
{
  const string host("localhost");
  int port= 9160;
  const CassandraFactory cf(host, port);
  EXPECT_EQ(9160, cf.getPort());
  EXPECT_EQ(host, cf.getHost());
  EXPECT_STREQ("localhost:9160", cf.getURL().c_str());
}


TEST(CassandraFactory, CreateClientNoServer)
{
  const string url("localhost:9161");
  CassandraFactory cf(url);
  ASSERT_THROW(cf.create(), apache::thrift::transport::TTransportException);
}


TEST(CassandraFactory, CreateClientWithServer)
{
  const string url("localhost:9160");
  CassandraFactory cf(url);
  tr1::shared_ptr<Cassandra> client= cf.create();
}
