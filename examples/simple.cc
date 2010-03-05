#include <string.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <set>
#include <stdio.h>

#include <libcassandra/cassandra_factory.h>
#include <libcassandra/cassandra.h>

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

  set<string> key_out;
  client->getKeyspaces(key_out);
  for (set<string>::iterator it = key_out.begin(); it != key_out.end(); ++it)
  {
    printf("keyspace: %s\n", (*it).c_str());
  }

  delete client;

  return 0;
}
