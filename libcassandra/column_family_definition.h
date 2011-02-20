/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_COLUMN_FAMILY_DEFINITION_H
#define __LIBCASSANDRA_COLUMN_FAMILY_DEFINITION_H

#include <string>
#include <map>
#include <vector>

#include "libgenthrift/cassandra_types.h"

#include "libcassandra/column_definition.h"

namespace libcassandra
{

class Cassandra;

class ColumnFamilyDefinition
{

public:

  ColumnFamilyDefinition();
  ColumnFamilyDefinition(const std::string& in_keyspace_name,
                         const std::string& in_name,
                         const std::string& in_column_type,
                         const std::string& in_comparator_type,
                         const std::string& in_sub_comparator_type,
                         const std::string& in_comment,
                         const double in_row_cache_size,
                         const double in_key_cache_size,
                         const double in_read_repair_chance,
                         std::vector<org::apache::cassandra::ColumnDef>& in_column_metadata,
                         const int32_t in_gc_grace_seconds,
                         const std::string& in_default_validation_class,
                         const int32_t in_id,
                         const int32_t in_min_compaction_threshold,
                         const int32_t in_max_compaction_threshold,
                         const int32_t in_row_cache_save_period_in_seconds,
                         const int32_t in_key_cache_save_period_in_seconds,
                         const int32_t in_memtable_flush_after_mins,
                         const int32_t in_memtable_throughput_in_mb,
                         const double in_memtable_operations_in_millions);
  ~ColumnFamilyDefinition() {}

  /**
   * @return column family name
   */
  std::string getName() const;

  /**
   * @return keyspace name
   */
  std::string getKeyspaceName() const;

  /**
   * @return column type
   */
  std::string getColumnType() const;

  /**
   * @return comparator type
   */
  std::string getComparatorType() const;

  /**
   * @return sub-comparator type
   */
  std::string getSubComparatorType() const;

  /**
   * @return comment
   */
  std::string getComment() const;

  /**
   * @return row cache size
   */
  double getRowCacheSize() const;

  /**
   * @return row cache save period in seconds
   */
  int32_t getRowCacheSavePeriod() const;

  /**
   * @return key cache size
   */
  double getKeyCacheSize() const;

  /**
   * @return read repair chance
   */
  double getReadRepairChance() const;

  /**
   * @return garbage collection grace seconds
   */
  int32_t getGcGraceSeconds() const;

  /**
   * @return default validation class
   */
  std::string getDefaultValidationClass() const;

  /**
   * @return column family ID
   */
  int32_t getId() const;

  /**
   * @return max compaction threshold
   */
  int32_t getMaxCompactionThreshold() const;

  /**
   * @return min compaction threshold
   */
  int32_t getMinCompactionThreshold() const;

  /**
   * @return memtable flush after mins
   */
  int32_t getMemtableFlushAfterMins() const;

  /**
   * @return memtable operations in millions
   */
  double getMemtableOperationsInMillions() const;

  /**
   * @return memtable throughput in megabytes
   */
  int32_t getMemtableThroughputInMb() const;

private:

  std::string keyspace_name;

  std::string name;

  std::string column_type;

  std::string comparator_type;

  std::string sub_comparator_type;

  std::string comment;

  double row_cache_size;

  double key_cache_size;

  double read_repair_chance;

  int32_t gc_grace_seconds;

  std::string default_validation_class;

  int32_t id;

  int32_t min_compaction_threshold;

  int32_t max_compaction_threshold;

  int32_t row_cache_save_period_in_seconds;

  int32_t key_cache_save_period_in_seconds;

  int32_t memtable_flush_after_mins;

  int32_t memtable_throughput_in_mb;

  double memtable_operations_in_millions;

  std::vector<ColumnDefinition> column_metadata;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_COLUMN_FAMILY_DEFINITION_H */
