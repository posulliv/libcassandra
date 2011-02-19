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

#include <libcassandra/cassandra_host.h>

using namespace std;
using namespace libcassandra;


TEST(CassandraHost, DefaultConstructor)
{
  const CassandraHost c;
  EXPECT_EQ(0, c.getPort());
}


TEST(CassandraHost, ConstructorFromURL)
{
  const string url("localhost:9160");
  const CassandraHost c(url);
  EXPECT_EQ(9160, c.getPort());
  EXPECT_EQ(url, c.getURL());
  EXPECT_STREQ(url.c_str(), c.getURL().c_str());
}


TEST(CassandraHost, ConsructorFromHostAndPort)
{
  const string host("localhost");
  int port= 9160;
  const CassandraHost c(host, port);
  EXPECT_EQ(9160, c.getPort());
  EXPECT_EQ(host, c.getHost());
  EXPECT_STREQ("localhost:9160", c.getURL().c_str());
}
