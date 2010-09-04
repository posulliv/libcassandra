dnl Copyright (C) 2010 Padraig O'Sullivan
dnl This file is free software; Padraig O'Sullivan
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([_PANDORA_SEARCH_BOOST_SYSTEM],[
  AC_REQUIRE([AC_LIB_PREFIX])
  AC_REQUIRE([ACX_PTHREAD])

  dnl --------------------------------------------------------------------
  dnl  Check for boost.System
  dnl --------------------------------------------------------------------

  AC_LANG_PUSH(C++)
  AC_LIB_HAVE_LINKFLAGS(boost_system-mt,,[
    #include <boost/system/error_code.hpp>
  ],[
    boost::system::error_code ec;
  ])
  AS_IF([test "x${ac_cv_libboost_system_mt}" = "xno"],[
    AC_LIB_HAVE_LINKFLAGS(boost_system,,[
      #include <boost/system/error_code.hpp>
    ],[
      boost::system::error_code ec;
    ])
  ])
  AC_LANG_POP()

  
  AM_CONDITIONAL(HAVE_BOOST_SYSTEM,
    [test "x${ac_cv_libboost_system}" = "xyes" -o "x${ac_cv_libboost_system_mt}" = "xyes"])
  BOOST_LIBS="${BOOST_LIBS} ${LTLIBBOOST_SYSTEM_MT} ${LTLIBBOOST_SYSTEM}"
  AC_SUBST(BOOST_LIBS) 
])

AC_DEFUN([PANDORA_HAVE_BOOST_SYSTEM],[
  PANDORA_HAVE_BOOST($1)
  _PANDORA_SEARCH_BOOST_SYSTEM($1)
])

AC_DEFUN([PANDORA_REQUIRE_BOOST_SYSTEM],[
  PANDORA_REQUIRE_BOOST($1)
  _PANDORA_SEARCH_BOOST_SYSTEM($1)
  AS_IF([test "x${ac_cv_libboost_system}" = "xno" -a "x${ac_cv_libboost_system_mt}" = "xno"],
      AC_MSG_ERROR([boost.System is required for ${PACKAGE}]))
])

