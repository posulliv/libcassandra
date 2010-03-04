dnl -*- mode: m4; c-basic-offset: 2; indent-tabs-mode: nil; -*-
dnl vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
dnl   
dnl Copyright (C) 2010 Padraig O'Sullivan
dnl This file is free software; 
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl

dnl --------------------------------------------------------------------
dnl  Check for Thrift
dnl --------------------------------------------------------------------

AC_DEFUN([_PANDORA_SEARCH_LIBTHRIFT],[
  AC_REQUIRE([PANDORA_HAVE_PTHREAD])

  AC_LANG_PUSH([C++])
  save_CXXFLAGS="${CXXFLAGS}"
  CXXFLAGS="${PTHREAD_CFLAGS} ${CXXFLAGS}"
  AC_LIB_HAVE_LINKFLAGS(thrift,,
    [#include <thrift/config.h>],
    [PACKAGE_STRING])
  AM_CXXFLAGS="${AM_CXXFLAGS} -I/usr/local/include/thrift"
  CXXFLAGS="${save_CXXFLAGS}"
  AC_LANG_POP()
])

AC_DEFUN([PANDORA_HAVE_LIBTHRIFT],[
  AC_REQUIRE([_PANDORA_SEARCH_LIBTHRIFT])
])

AC_DEFUN([PANDORA_REQUIRE_LIBTHRIFT],[
  AC_REQUIRE([PANDORA_HAVE_LIBTHRIFT])
  AS_IF([test x$ac_cv_libthrift = xno],
      AC_MSG_ERROR([libthrift is required for ${PACKAGE}. On Debian this can be found in libthrift-dev.]))
])

