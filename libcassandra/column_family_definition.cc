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
#include "libcassandra/column_definition.h"

using namespace libcassandra;
using namespace std;
using namespace org::apache::cassandra;


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
    memtable_operations_in_millions(0.0),
    column_metadata()
{}


ColumnFamilyDefinition::ColumnFamilyDefinition(const string& in_keyspace_name,
                                               const string& in_name,
                                               const string& in_column_type,
                                               const string& in_comparator_type,
                                               const string& in_sub_comparator_type,
                                               const string& in_comment,
                                               const double in_row_cache_size,
                                               const double in_key_cache_size,
                                               const double in_read_repair_chance,
                                               vector<ColumnDef>& in_column_metadata,
                                               const int32_t in_gc_grace_seconds,
                                               const string& in_default_validation_class,
                                               const int32_t in_id,
                                               const int32_t in_min_compaction_threshold,
                                               const int32_t in_max_compaction_threshold,
                                               const int32_t in_row_cache_save_period_in_seconds,
                                               const int32_t in_key_cache_save_period_in_seconds,
                                               const int32_t in_memtable_flush_after_mins,
                                               const int32_t in_memtable_throughput_in_mb,
                                               const double in_memtable_operations_in_millions)
  :
    keyspace_name(in_keyspace_name),
    name(in_name),
    column_type(in_column_type),
    comparator_type(in_comparator_type),
    sub_comparator_type(in_sub_comparator_type),
    comment(in_comment),
    row_cache_size(in_row_cache_size),
    key_cache_size(in_key_cache_size),
    read_repair_chance(in_read_repair_chance),
    gc_grace_seconds(in_gc_grace_seconds),
    default_validation_class(in_default_validation_class),
    id(in_id),
    min_compaction_threshold(in_min_compaction_threshold),
    max_compaction_threshold(in_max_compaction_threshold),
    row_cache_save_period_in_seconds(in_row_cache_save_period_in_seconds),
    key_cache_save_period_in_seconds(in_key_cache_save_period_in_seconds),
    memtable_flush_after_mins(in_memtable_flush_after_mins),
    memtable_throughput_in_mb(in_memtable_throughput_in_mb),
    memtable_operations_in_millions(in_memtable_operations_in_millions),
    column_metadata()
{
  for (vector<ColumnDef>::iterator it= in_column_metadata.begin();
       it != in_column_metadata.end();
       ++it)
  {
    ColumnDef thrift_entry= *it;
    ColumnDefinition entry(thrift_entry.name,
                           thrift_entry.validation_class,
                           thrift_entry.index_type,
                           thrift_entry.index_name);
    column_metadata.push_back(entry);
  }
}


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


int32_t ColumnFamilyDefinition::getMemtableFlushAfterMins() const
{
  return memtable_flush_after_mins;
}


double ColumnFamilyDefinition::getMemtableOperationsInMillions() const
{
  return memtable_operations_in_millions;
}


int32_t ColumnFamilyDefinition::getMemtableThroughputInMb() const
{
  return memtable_throughput_in_mb;
}
