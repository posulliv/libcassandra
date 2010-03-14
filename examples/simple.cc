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

using namespace std;
using namespace libcassandra;

static string host("127.0.0.1");
static int port= 9160;

int main()
{
  CassandraFactory factory(host, port);
  Cassandra *client= factory.create();

  string clus_name= client->getClusterName();
  cout << "cluster name: " << clus_name << endl;

  set<string> key_out= client->getKeyspaces();
  for (set<string>::iterator it = key_out.begin(); it != key_out.end(); ++it)
  {
    cout << "keyspace: " << *it << endl;
  }

  map<string, string> tokens= client->getTokenMap(false);
  for (map<string, string>::iterator it= tokens.begin();
       it != tokens.end();
       ++it)
  {
    cout << it->first << " : " << it->second << endl;
  }

  Keyspace *key_space= client->getKeyspace("drizzle");
  /* insert data */
  try
  {
    key_space->insertColumn("sarah", "Data", "third", "this is data being inserted!");
    /* retrieve that data */
    string res= key_space->getColumnValue("sarah", "Data", "third");
    cout << "Value in column retrieved is: " << res << endl;
  }
  catch (org::apache::cassandra::InvalidRequestException &ire)
  {
    cout << ire.why << endl;
    delete client;
    delete key_space;
    return 1;
  }

  delete client;
  delete key_space;

  return 0;
}
