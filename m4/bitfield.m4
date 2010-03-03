AC_DEFUN([DETECT_BITFIELD],
[
    AC_CACHE_CHECK([for working bitfield],[ac_cv_have_bitfield],[
    AC_LANG_PUSH([C])
    save_CFLAGS="${CFLAGS}"
    CFLAGS="${AM_CFLAGS} ${NO_WERROR}"

    AC_RUN_IFELSE([
       AC_LANG_PROGRAM([[
#include <stdbool.h>
       ]],[[
   struct flags { bool b0:1; bool b1:1; bool b2:1; bool b3:1;
                  bool b4:1; bool b5:1; bool b6:1; bool b7:1;
   } f = { .b0 = false, .b1 = false, .b2 = false, .b3 = false,
           .b4 = false, .b5 = false, .b6 = false, .b7 = false };

   f.b0 = true;
   f.b1 = false;
   f.b2 = true;
   f.b3 = false;
   f.b4 = true;
   f.b5 = false;
   f.b6 = true;
   f.b7 = false;

   if (f.b0 && !f.b1 && f.b2 && !f.b3 && f.b4 && !f.b5 && f.b6 && !f.b7) {
      return 0;
   }

   return 1;
       ]])
    ], [
      ac_cv_have_bitfield=yes
    ],[
      ac_cv_have_bitfield=no
    ])])

    CFLAGS=${save_CFLAGS}
    AS_IF([test "x$ac_cv_have_bitfield" = "xyes"],
          [
	    MEMCACHED_BITFIELD="#define MEMCACHED_BITFIELD :1"
	    HASHKIT_BITFIELD="#define HASHKIT_BITFIELD :1"
	  ],
          [
	    MEMCACHED_BITFIELD="#define MEMCACHED_BITFIELD"
	    HASHKIT_BITFIELD="#define HASHKIT_BITFIELD"
	  ])
    AC_SUBST([MEMCACHED_BITFIELD])
    AC_SUBST([HASHKIT_BITFIELD])
    AC_LANG_POP()
])
