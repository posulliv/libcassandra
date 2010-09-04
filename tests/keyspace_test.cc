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
#include <libcassandra/keyspace.h>

using namespace std;
using namespace libcassandra;


class KeyspaceTest : public testing::Test
{
protected:
  virtual void SetUp()
  {
    const string host("localhost");
    int port= 9160;
	cf= tr1::shared_ptr<CassandraFactory>(new CassandraFactory(host, port));
	c= tr1::shared_ptr<Cassandra>(cf->create());
	ks_name.assign("Keyspace1");
  }

  tr1::shared_ptr<CassandraFactory> cf;
  tr1::shared_ptr<Cassandra> c;
  string ks_name;
};


TEST_F(KeyspaceTest, GetKeyspace)
{
  tr1::shared_ptr<Keyspace> ks= c->getKeyspace(ks_name);
  EXPECT_EQ(ks_name, ks->getName());
}

