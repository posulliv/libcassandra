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
#include <iostream>
#include <sstream>

#include <protocol/TBinaryProtocol.h>
#include <transport/TSocket.h>
#include <transport/TTransportUtils.h>

#include <gtest/gtest.h>

#include <libgenthrift/Cassandra.h>
#include <libcassandra/cassandra.h>
#include <libcassandra/cassandra_factory.h>
#include <libcassandra/keyspace.h>
#include <libcassandra/keyspace_definition.h>

using namespace std;
using namespace libcassandra;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace org::apache::cassandra;
using namespace boost;


class ClientTest : public testing::Test
{
protected:
  virtual void SetUp()
  {
    const string host("localhost");
    int port= 9160;
    cf= tr1::shared_ptr<CassandraFactory>(new CassandraFactory(host, port));
    c= tr1::shared_ptr<Cassandra>(cf->create());
  }

  tr1::shared_ptr<CassandraFactory> cf;
  tr1::shared_ptr<Cassandra> c;
};


TEST(Cassandra, DefaultConstructor)
{
  const Cassandra c;
  EXPECT_EQ(0, c.getPort());
}


TEST(Cassandra, ConsructorFromHostAndPort)
{
  const string host("localhost");
  int port= 9160;
  boost::shared_ptr<TTransport> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new CassandraClient(protocol);
  transport->open();
  Cassandra c(client, host, port);
  EXPECT_EQ(client, c.getCassandra());
  EXPECT_EQ(host, c.getHost());
  EXPECT_EQ(port, c.getPort());
  EXPECT_STREQ("localhost", c.getHost().c_str());
}


TEST(Cassandra, GetServerVersion)
{
  const string host("localhost");
  int port= 9160;
  boost::shared_ptr<TTransport> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new CassandraClient(protocol);
  transport->open();
  Cassandra c(client, host, port);
  const string version("19.4.0");
  EXPECT_EQ(version, c.getServerVersion());
  EXPECT_STREQ(version.c_str(), c.getServerVersion().c_str());
}


TEST(Cassandra, GetClusterName)
{
  const string host("localhost");
  int port= 9160;
  boost::shared_ptr<TTransport> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new CassandraClient(protocol);
  transport->open();
  Cassandra c(client, host, port);
  const string name("Test Cluster");
  EXPECT_EQ(name, c.getClusterName());
  EXPECT_STREQ(name.c_str(), c.getClusterName().c_str());
}


TEST(Cassandra, GetKeyspaces)
{
  const string host("localhost");
  int port= 9160;
  boost::shared_ptr<TTransport> socket(new TSocket(host, port));
  boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  CassandraClient *client= new CassandraClient(protocol);
  transport->open();
  Cassandra c(client, host, port);
  vector<KeyspaceDefinition> keyspaces= c.getKeyspaces();
  /* we assume the test server only has 2 keyspaces: system and default */
  EXPECT_EQ(2, keyspaces.size());
}


TEST(Cassandra, GetSpecificKeyspace)
{
  const string host("localhost");
  int port= 9160;
  CassandraFactory cf(host, port);
  tr1::shared_ptr<Cassandra> c(cf.create());
  const string ks_name("system");
  tr1::shared_ptr<Keyspace> ks= c->getKeyspace(ks_name);
  EXPECT_EQ(ks_name, ks->getName());
  EXPECT_STREQ(ks_name.c_str(), ks->getName().c_str());
}


TEST_F(ClientTest, InsertColumn)
{
  const string mock_data("this is mock data being inserted...");
  c->insertColumn("sarah", "Standard1", "third", mock_data);
  string res= c->getColumnValue("sarah", "Standard1", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
}


TEST_F(ClientTest, DeleteColumn)
{
  c->removeColumn("sarah", "Standard1", "", "third");
  ASSERT_THROW(c->getColumnValue("sarah", "Standard1", "third"), org::apache::cassandra::NotFoundException);
}


TEST_F(ClientTest, DeleteEntireRow)
{
  const string mock_data("this is mock data being inserted...");
  c->insertColumn("sarah", "Standard1", "third", mock_data);
  string res= c->getColumnValue("sarah", "Standard1", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
  c->remove("sarah", "Standard1", "", "");
  ASSERT_THROW(c->getColumnValue("sarah", "Standard1", "third"), org::apache::cassandra::NotFoundException);
}


TEST_F(ClientTest, InsertSuperColumn)
{
  const string mock_data("this is mock data being inserted...");
  c->insertColumn("teeny", "Super1", "padraig", "third", mock_data);
  string res= c->getColumnValue("teeny", "Super1", "padraig", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
}


TEST_F(ClientTest, DeleteSuperColumn)
{
  c->removeSuperColumn("teeny", "Super1", "padraig");
  ASSERT_THROW(c->getColumnValue("teeny", "Super1", "padraig", "third"), org::apache::cassandra::NotFoundException);
}
