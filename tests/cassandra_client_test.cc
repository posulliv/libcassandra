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
#include <libcassandra/column_family_definition.h>
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
  /* we assume the test server only has 1 keyspace: system */
  EXPECT_EQ(1, keyspaces.size());
}


TEST_F(ClientTest, InsertColumn)
{
  const string mock_data("this is mock data being inserted...");
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("padraig");
  cf_def.setKeyspaceName(ks_def.getName());
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->insertColumn("sarah", "padraig", "third", mock_data);
  string res= c->getColumnValue("sarah", "padraig", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
  c->dropColumnFamily("padraig");
  c->dropKeyspace("unittest");
}


TEST_F(ClientTest, DeleteColumn)
{
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("padraig");
  cf_def.setKeyspaceName(ks_def.getName());
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->removeColumn("sarah", "padraig", "", "third");
  ASSERT_THROW(c->getColumnValue("sarah", "padraig", "third"), org::apache::cassandra::NotFoundException);
  c->dropColumnFamily("padraig");
  c->dropKeyspace("unittest");
}


TEST_F(ClientTest, DeleteEntireRow)
{
  const string mock_data("this is mock data being inserted...");
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("padraig");
  cf_def.setKeyspaceName(ks_def.getName());
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->insertColumn("sarah", "padraig", "third", mock_data);
  string res= c->getColumnValue("sarah", "padraig", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
  c->remove("sarah", "padraig", "", "");
  ASSERT_THROW(c->getColumnValue("sarah", "padraig", "third"), org::apache::cassandra::NotFoundException);
  c->dropColumnFamily("padraig");
  c->dropKeyspace("unittest");
}


TEST_F(ClientTest, InsertSuperColumn)
{
  const string mock_data("this is mock data being inserted...");
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("Super1");
  cf_def.setColumnType("Super");
  cf_def.setKeyspaceName(ks_def.getName());
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->insertColumn("teeny", "Super1", "padraig", "third", mock_data);
  string res= c->getColumnValue("teeny", "Super1", "padraig", "third");
  EXPECT_EQ(mock_data, res);
  EXPECT_STREQ(mock_data.c_str(), res.c_str());
  c->dropColumnFamily("Super1");
  c->dropKeyspace("unittest");
}


TEST_F(ClientTest, DeleteSuperColumn)
{
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("Super1");
  cf_def.setColumnType("Super");
  cf_def.setKeyspaceName(ks_def.getName());
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->removeSuperColumn("teeny", "Super1", "padraig");
  ASSERT_THROW(c->getColumnValue("teeny", "Super1", "padraig", "third"), org::apache::cassandra::NotFoundException);
  c->dropColumnFamily("Super1");
  c->dropKeyspace("unittest");
}
