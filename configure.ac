#!/usr/bin/env bash
# libcassandra
# Copyright (C) 2010 Padraig O'Sullivan
# All rights reserved.
#
# Use and distribution licensed under the BSD license.  See
# the COPYING file in this directory for full text.

AC_PREREQ(2.59)
AC_INIT([libcassandra],[0.1],[http://github.com/posulliv/libcassandra])
AC_CONFIG_SRCDIR([libcassandra/cassandra.cc])
AC_CONFIG_AUX_DIR(config)

PANDORA_CANONICAL_TARGET(less-warnings, warnings-always-on, require-cxx, skip-visibility)

#shared library versioning
CASSANDRA_LIBRARY_VERSION=2:0:0
#                         | | |
#                  +------+ | +---+
#                  |        |     |
#                 current:revision:age
#                  |        |     |
#                  |        |     +- increment if interfaces have been added
#                  |        |        set to zero if interfaces have been removed or changed
#                  |        +- increment if source code has changed
#                  |           set to zero if current is incremented
#                  +- increment if interfaces have been added, removed or changed
AC_SUBST(CASSANDRA_LIBRARY_VERSION)


AC_SEARCH_LIBS(getopt_long, gnugetopt)
AC_SEARCH_LIBS(gethostbyname, nsl)

AC_CHECK_FUNCS([getline])

PANDORA_REQUIRE_THRIFT

AC_LANG_PUSH(C++)
PANDORA_REQUIRE_PTHREAD
AC_LANG_POP

PANDORA_DRIZZLE_BUILD

PANDORA_HAVE_LIBGTEST

dnl Specialty checks
DETECT_BYTEORDER
SETSOCKOPT_SANITY
PANDORA_PRINT_CALLSTACK
DETECT_BITFIELD

AC_CHECK_HEADERS([atomic.h])
AS_IF([test "x$ac_cv_header_atomic_h" = "xyes"],[
      AC_CHECK_FUNCS(atomic_add_64)
      AC_CHECK_FUNCS(atomic_add_32)
      AS_IF([test "x$ac_cv_func_atomic_add_64" = "xyes" -a "x$ac_cv_func_atomic_add_32" = "xyes"],[
            AC_DEFINE([USE_ATOMIC_H],
	              [1],
                      [Define to true if you want to use functions from atomic.h])])])

AC_CONFIG_FILES([
  Makefile
  libgenthrift/configure.h
  libcassandra/configure.h
  ])
AC_OUTPUT

echo "---"
echo "Configuration summary for $PACKAGE_NAME version $VERSION"
echo ""
echo "   * Installation prefix:       $prefix"
echo "   * System type:               $host_vendor-$host_os"
echo "   * Host CPU:                  $host_cpu"
echo "   * C Compiler:                $CC_VERSION"
echo "   * C++ Compiler:              $CXX_VERSION"
echo "   * Assertions enabled:        $ac_cv_assert"
echo "   * Debug enabled:             $with_debug"
echo "   * Warnings as failure:       $ac_cv_warnings_as_errors"
echo "   * C++ cstdint location:      $ac_cv_cxx_cstdint"
echo "   * C++ hash_map location:     $ac_cv_cxx_hash_map"
echo "   * C++ hash namespace:        $ac_cv_cxx_hash_namespace"
echo "   * C++ shared_ptr namespace:  $ac_cv_shared_ptr_namespace"
echo ""
echo "---"

