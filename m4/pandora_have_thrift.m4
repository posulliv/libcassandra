dnl  Copyright (C) 2010 Padraig O'Sullivan
dnl This file is free software; Padraig O'Sullivan
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([_PANDORA_SEARCH_THRIFT],[
  AC_REQUIRE([PANDORA_HAVE_PTHREAD])

  dnl --------------------------------------------------------------------
  dnl  Check for thrift
  dnl --------------------------------------------------------------------


  AC_LIB_HAVE_LINKFLAGS(thrift,,[
      #include <thrift/config.h>
    ],[
      PACKAGE_STRING
    ])
  AM_CXXFLAGS="${AM_CXXFLAGS} -I/usr/local/include/thrift" 
])

AC_DEFUN([PANDORA_HAVE_THRIFT],[
  AC_REQUIRE([_PANDORA_SEARCH_THRIFT])
])

AC_DEFUN([PANDORA_REQUIRE_THRIFT],[
  AC_REQUIRE([PANDORA_HAVE_THRIFT])
  AS_IF([test x$ac_cv_thrift= xno],
      AC_MSG_ERROR([thrift is required for building this client library]))
])

