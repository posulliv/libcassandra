
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
  EXPECT_EQ(0, c.getPort());
  EXPECT_EQ(url, c.getURL());
  EXPECT_STREQ(url.c_str(), c.getURL().c_str());
}


TEST(CassandraHost, parsePortFromURL)
{
  const string url("localhost:9160");
  const CassandraHost c;
  int port = c.parsePortFromURL(url);
  EXPECT_EQ(9160, port);
}


TEST(CassandraHost, parseHostFromURL)
{
  const string url("localhost:9160");
  const CassandraHost c;
  string host = c.parseHostFromURL(url);
  EXPECT_STREQ("localhost", host.c_str());
}
