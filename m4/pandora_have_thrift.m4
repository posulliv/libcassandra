dnl -*- mode: m4; c-basic-offset: 2; indent-tabs-mode: nil; -*-
dnl vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
dnl   
dnl Copyright (C) 2010 Padraig O'Sullivan
dnl This file is free software; 
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl

AC_DEFUN([_PANDORA_SEARCH_THRIFT],[
  AC_REQUIRE([AC_LIB_PREFIX])
 
  dnl --------------------------------------------------------------------
  dnl  Check for thrift
  dnl --------------------------------------------------------------------
 
  AC_ARG_ENABLE([thrift],
    [AS_HELP_STRING([--disable-thrift],
      [Build with thrift support @<:@default=on@:>@])],
    [ac_enable_thrift="$enableval"],
    [ac_enable_thrift="yes"])
 
  AS_IF([test "x$ac_enable_thrift" = "xyes"],[
    AC_LANG_PUSH(C++)
    AC_LIB_HAVE_LINKFLAGS(thrift,,[
      #include <thrift/Thrift.h>
    ],[
      apache::thrift::TOutput test_output;
    ])
    AC_LANG_POP()

	 dnl Thrift's generated code as well as its own headers include thrift headers
	 dnl without a "thrift/" prefix, which means even though the above adds -I PREFIX/include
	 dnl We also need -I PREFIX/include/thrift
	 AC_LIB_APPENDTOVAR([INCTHRIFT], [-I]$LIBTHRIFT_PREFIX[/include/thrift])
	 AC_LIB_APPENDTOVAR([CPPFLAGS], [-I]$LIBTHRIFT_PREFIX[/include/thrift])

  ],[
    ac_cv_libthrift="no"
  ])
  
  AM_CONDITIONAL(HAVE_LIBTHRIFT, [test "x${ac_cv_libthrift}" = "xyes"])
  
])
 
AC_DEFUN([PANDORA_HAVE_THRIFT],[
  AC_REQUIRE([_PANDORA_SEARCH_THRIFT])
])
 
AC_DEFUN([PANDORA_REQUIRE_THRIFT],[
  AC_REQUIRE([PANDORA_HAVE_THRIFT])
  AS_IF([test "x$ac_cv_libthrift" = "xno"],[
      AC_MSG_ERROR([thrift required for ${PACKAGE}])
  ])
])
