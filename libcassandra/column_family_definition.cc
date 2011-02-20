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

#include "libcassandra/column_family_definition.h"

using namespace libcassandra;
using namespace std;


ColumnFamilyDefinition::ColumnFamilyDefinition()
  :
    keyspace_name(),
    name(),
    column_type(),
    comparator_type(),
    sub_comparator_type(),
    comment(),
    row_cache_size(0.0),
    key_cache_size(0.0),
    read_repair_chance(0.0),
    gc_grace_seconds(0),
    default_validation_class(),
    id(0),
    min_compaction_threshold(0),
    max_compaction_threshold(0),
    row_cache_save_period_in_seconds(0),
    key_cache_save_period_in_seconds(0),
    memtable_flush_after_mins(0),
    memtable_throughput_in_mb(0),
    memtable_operations_in_millions(0.0)
{}


string ColumnFamilyDefinition::getName() const
{
  return name;
}


string ColumnFamilyDefinition::getKeyspaceName() const
{
  return keyspace_name;
}


string ColumnFamilyDefinition::getColumnType() const
{
  return column_type;
}


string ColumnFamilyDefinition::getComparatorType() const
{
  return comparator_type;
}


string ColumnFamilyDefinition::getSubComparatorType() const
{
  return sub_comparator_type;
}


string ColumnFamilyDefinition::getComment() const
{
  return comment;
}


double ColumnFamilyDefinition::getRowCacheSize() const
{
  return row_cache_size;
}


int32_t ColumnFamilyDefinition::getRowCacheSavePeriod() const
{
  return row_cache_save_period_in_seconds;
}


double ColumnFamilyDefinition::getKeyCacheSize() const
{
  return key_cache_size;
}


double ColumnFamilyDefinition::getReadRepairChance() const
{
  return read_repair_chance;
}


int32_t ColumnFamilyDefinition::getGcGraceSeconds() const
{
  return gc_grace_seconds;
}


string ColumnFamilyDefinition::getDefaultValidationClass() const
{
  return default_validation_class;
}


int32_t ColumnFamilyDefinition::getId() const
{
  return id;
}


int32_t ColumnFamilyDefinition::getMaxCompactionThreshold() const
{
  return max_compaction_threshold;
}


int32_t ColumnFamilyDefinition::getMinCompactionThreshold() const
{
  return min_compaction_threshold;
}


int32_t ColumnFamilyDefinition::getMemTableFlushAfterMins() const
{
  return memtable_flush_after_mins;
}


double ColumnFamilyDefinition::getMemTableOperationsInMillions() const
{
  return memtable_operations_in_millions;
}


int32_t ColumnFamilyDefinition::getMemTableThroughputInMb() const
{
  return memtable_throughput_in_mb;
}
