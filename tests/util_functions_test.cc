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

#include <libcassandra/util_functions.h>

using namespace std;
using namespace libcassandra;


TEST(UtilFunctions, parsePortFromURL)
{
  const string url("localhost:9160");
  int port = parsePortFromURL(url);
  EXPECT_EQ(9160, port);
}


TEST(UtilFunctions, parseHostFromURL)
{
  const string url("localhost:9160");
  string host = parseHostFromURL(url);
  EXPECT_STREQ("localhost", host.c_str());
}
