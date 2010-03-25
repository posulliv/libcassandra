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

/*
 * This is a small simple example of how to access data that goes in the drizzle keyspace. The idea
 * with the drizzle storage engine is that all the data for that engine will go in one keyspace
 * named drizzle. Each column family within that keyspace will correspond to a table in drizzle.
 * This file is going to be used for illustration purposes. I know what data I am going to put in a
 * drizzle table so I can retrieve it here and show how I can get data from cassandra using C++ and
 * using the drizzle CLI as well. Might as well show it using the cassandra CLI too.
 */
int main()
{
  CassandraFactory factory(host, port);
  tr1::shared_ptr<Cassandra> client(factory.create());


  Keyspace *key_space= client->getKeyspace("drizzle");
  /* get inserted data */
  try
  {
    string column_data= key_space->getColumnValue("data:my_key:sarah", "data", "hobby");
    /* retrieve that data */
    cout << "Value in column retrieved is: " << column_data << endl;
    /* now try inserting some data */
    key_space->insertColumn("data:my_key:domhnall", "data", "my_key", "domhnall");
    key_space->insertColumn("data:my_key:domhnall", "data", "hobby", "guitar");
    key_space->insertColumn("data:my_key:domhnall", "data", "home", "ireland");
  }
  catch (org::apache::cassandra::InvalidRequestException &ire)
  {
    cout << ire.why << endl;
    delete key_space;
    return 1;
  }

  delete key_space;

  return 0;
}
