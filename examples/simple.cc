#include <string.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <string>
#include <stdio.h>

#include <libcassandra/cassandra_factory.h>
#include <libcassandra/cassandra.h>
#include <libcassandra/keyspace.h>

#include <libgenthrift/Cassandra.h>

using namespace std;
using namespace libcassandra;

static string host("127.0.0.1");
static int port= 9160;

int main()
{
  CassandraFactory factory(host, port);
  Cassandra *client= factory.create();

  string clus_name= client->getClusterName();
  printf("cluster name: %s\n", clus_name.c_str());

  set<string> key_out= client->getKeyspaces();
  for (set<string>::iterator it = key_out.begin(); it != key_out.end(); ++it)
  {
    printf("keyspace: %s\n", (*it).c_str());
  }

  map<string, string> tokens= client->getTokenMap(false);
  for (map<string, string>::iterator it= tokens.begin();
       it != tokens.end();
       ++it)
  {
    printf("%s : %s\n", it->first.c_str(), it->second.c_str());
  }

  Keyspace *key_space= client->getKeyspace("drizzle");
  org::apache::cassandra::ColumnPath col_path;
  col_path.column_family.assign("Data");
  col_path.column.assign("second");
  org::apache::cassandra::Column res= key_space->getColumn("padraig", col_path);

  printf("Value in column retrieved is: %s\n", res.value.c_str());

  delete client;
  delete key_space;

  return 0;
}
