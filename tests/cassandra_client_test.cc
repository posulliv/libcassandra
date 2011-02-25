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
#include <libcassandra/indexed_slices_query.h>
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


/**
 * This unit test uses the blog post from data stax as its basis
 * http://www.datastax.com/dev/blog/whats-new-cassandra-07-secondary-indexes
 */
TEST_F(ClientTest, SecondaryIndexes)
{
  KeyspaceDefinition ks_def;
  ks_def.setName("unittest");
  c->createKeyspace(ks_def);
  ColumnFamilyDefinition cf_def;
  cf_def.setName("users");
  cf_def.setKeyspaceName(ks_def.getName());
  ColumnDefinition name_col;
  name_col.setName("full_name");
  name_col.setValidationClass("UTF8Type");
  ColumnDefinition sec_col;
  sec_col.setName("birth_date");
  sec_col.setValidationClass("LongType");
  sec_col.setIndexType(IndexType::KEYS);
  ColumnDefinition third_col;
  third_col.setName("state");
  third_col.setValidationClass("UTF8Type");
  third_col.setIndexType(IndexType::KEYS);
  cf_def.addColumnMetadata(name_col);
  cf_def.addColumnMetadata(sec_col);
  cf_def.addColumnMetadata(third_col);
  c->setKeyspace(ks_def.getName());
  c->createColumnFamily(cf_def);
  c->insertColumn("bsanderson", cf_def.getName(), "full_name", "Brandon Sanderson");
  c->insertColumn("bsanderson", cf_def.getName(), "birth_date", "00001975");
  c->insertColumn("bsanderson", cf_def.getName(), "state", "UT");
  c->insertColumn("prothfuss", cf_def.getName(), "full_name", "Patrick Rothfuss");
  c->insertColumn("prothfuss", cf_def.getName(), "birth_date", "00001973");
  c->insertColumn("prothfuss", cf_def.getName(), "state", "WI");
  c->insertColumn("htayler", cf_def.getName(), "full_name", "Howard Tayler");
  c->insertColumn("htayler", cf_def.getName(), "birth_date", "00001968");
  c->insertColumn("htayler", cf_def.getName(), "state", "UT");
  IndexedSlicesQuery query;
  vector<string> column_names;
  column_names.push_back("full_name");
  column_names.push_back("birth_date");
  column_names.push_back("state");
  query.setColumns(column_names);
  query.addGtExpression("birth_date", "00001970");
  query.addEqualsExpression("state", "UT");
  query.setColumnFamily("users");
  map<string, map<string, string> > res= c->getIndexedSlices(query);
  EXPECT_EQ(1, res.size());
  for (map<string, map<string, string> >::iterator it= res.begin();
       it != res.end();
       ++it)
  {
    EXPECT_EQ("bsanderson", it->first);
  }
  c->dropColumnFamily("users");
  c->dropKeyspace("unittest");
}
