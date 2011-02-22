/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <iostream>

#include <boost/asio.hpp>

#include <gtest/gtest.h>

#include <libcassandra/cassandra_util.h>

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char **argv)
{
  /*
   * If a cassandra server is not running on port 9160 on localhost then we
   * do not run the unit tests. A hard requirement for the unit tests is
   * that a cassandra server is up and running. The unit test framework does
   * not take responsibility for starting the cassandra server at the
   * moment. This may be added at a later stage time permitting.
   */
  bool up= libcassandra::util::pingCassandraServer("localhost", 9160);
  if (! up)
  {
    cerr << "Cassandra service is not running on localhost port 9160" << endl;
    return EXIT_FAILURE;
  }

  /* we have a running server, lets go with the unit tests */
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
