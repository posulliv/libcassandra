/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#include <string>
#include <vector>
#include <map>

#include "libcassandra/keyspace_definition.h"

using namespace libcassandra;
using namespace std;


KeyspaceDefinition::KeyspaceDefinition()
  :
    name(),
    strategy_class(),
    strategy_options(),
    replication_factor()
{}


string KeyspaceDefinition::getName() const
{
  return name;
}


string KeyspaceDefinition::getStrategyClass() const
{
  return strategy_class;
}


map<string, string> KeyspaceDefinition::getStrategyOptions() const
{
  return strategy_options;
}


int32_t KeyspaceDefinition::getReplicationFactor() const
{
  return replication_factor;
}
