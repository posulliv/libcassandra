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
#include "libcassandra/column_family_defintion.h"

using namespace libcassandra;
using namespace std;
using namespace org::apache::cassandra;


KeyspaceDefinition::KeyspaceDefinition()
  :
    name(),
    strategy_class(),
    strategy_options(),
    replication_factor(),
    col_family_defs()
{}


KeyspaceDefinition::KeyspaceDefinition(const string& in_name,
                                       const string& in_strategy_class,
                                       const map<string, string>& in_strategy_options,
                                       const int32_t in_replication_factor,
                                       const vector<CfDef>& in_cf_defs)
  :
    name(in_name),
    strategy_class(in_strategy_class),
    strategy_options(in_strategy_options),
    replication_factor(in_replication_factor),
    col_family_defs()
{
  for (vector<CfDef>::iterator it= in_cf_defs.begin();
       it != in_cf_defs.end();
       ++it)
  {
    CfDef thrift_entry= *it;
    ColumnFamilyDefinition entry(thrift_entry.keyspace,
                                 thrift_entry.name,
                                 thrift_entry.column_type,
                                 thrift_entry.comparator_type,
                                 thrift_entry.subcomparator_type,
                                 thrift_entry.comment,
                                 thrift_entry.row_cache_size,
                                 thrift_entry.key_cache_size,
                                 thrift_entry.read_repair_chance,
                                 thrift_entry.column_metadata,
                                 thrift_entry.gc_grace_seconds,
                                 thrift_entry.default_validation_class,
                                 thrift_entry.id,
                                 thrift_entry.min_compaction_threshold,
                                 thrift_entry.max_compaction_threshold,
                                 thrift_entry.row_cache_save_period_in_seconds,
                                 thrift_entry.key_cache_save_period_in_seconds,
                                 thrift_entry.memtable_flush_after_mins,
                                 thrift_entry.memtable_throughput_in_mb,
                                 thrift_entry.memtable_operations_in_millions);
    col_family_defs.push_back(entry);
  }
}


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
