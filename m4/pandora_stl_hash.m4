# We check two things: where the include file is for hash_map, and
# what namespace hash_map lives in within that include file.  We
# include AC_COMPILE_IFELSE for all the combinations we've seen in the
# wild.  We define one of HAVE_HASH_MAP or HAVE_EXT_HASH_MAP depending
# on location, and HASH_NAMESPACE to be the namespace hash_map is
# defined in.
#
# Ideally we'd use AC_CACHE_CHECK, but that only lets us store one value
# at a time, and we need to store two (filename and namespace).
# prints messages itself, so we have to do the message-printing ourselves
# via AC_MSG_CHECKING + AC_MSG_RESULT.  (TODO(csilvers): can we cache?)

AC_DEFUN([PANDORA_CXX_STL_HASH],
  [AC_MSG_CHECKING(the location of hash_map)
   save_CXXFLAGS="${CXXFLAGS}"
   CXXFLAGS="${AM_CXXFLAGS} ${CXXFLAGS}"
   AC_LANG_PUSH(C++)
   ac_cv_cxx_hash_map=""
   for location in "" "ext/" "tr1/" ; do
     for namespace in __gnu_cxx "" std stdext; do
       for classprefix in unordered hash; do
         if test -z "$ac_cv_cxx_hash_map"; then
           AC_COMPILE_IFELSE(
             [AC_LANG_PROGRAM([[#include <${location}${classprefix}_map>]],
                           [[${namespace}::${classprefix}_map<int, int> t]])],
             [ac_cv_cxx_hash_map="<${location}${classprefix}_map>";
              ac_cv_cxx_hash_set="<${location}${classprefix}_set>";
              ac_cv_cxx_hash_namespace="$namespace";
              ac_cv_cxx_hash_map_class="${classprefix}_map";
              ac_cv_cxx_hash_set_class="${classprefix}_set"])

         fi
       done
     done
   done

   if test -n "$ac_cv_cxx_hash_map"; then
      AC_DEFINE(HAVE_HASH_MAP, 1, [define if the compiler has hash_map])
      AC_DEFINE(HAVE_HASH_SET, 1, [define if the compiler has hash_set])
      AC_DEFINE_UNQUOTED(HASH_MAP_H,$ac_cv_cxx_hash_map,
                         [the location of <hash_map>])
      AC_DEFINE_UNQUOTED(HASH_SET_H,$ac_cv_cxx_hash_set,
                         [the location of <hash_set>])
      AC_DEFINE_UNQUOTED(HASH_NAMESPACE,$ac_cv_cxx_hash_namespace,
                         [the namespace of hash_map/hash_set])
      AC_DEFINE_UNQUOTED(HASH_MAP_CLASS,$ac_cv_cxx_hash_map_class,
                         [the classname of hash_map])
      AC_DEFINE_UNQUOTED(HASH_SET_CLASS,$ac_cv_cxx_hash_set_class,
                         [the classname of hash_set])
      AC_MSG_RESULT([$ac_cv_cxx_hash_map])
   else
      AC_MSG_RESULT()
      AC_MSG_WARN([could not find an STL hash_map])
   fi
   AC_CACHE_CHECK(
     [whether hash_map has rehash method],
     [ac_cv_hash_map_has_rehash],
     [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[
#include HASH_MAP_H
using namespace HASH_NAMESPACE;
       ]],[[
HASH_MAP_CLASS<int, int> test_hash;
test_hash.rehash(100);
          ]])],
       [ac_cv_hash_map_has_rehash=yes],
       [ac_cv_hash_map_has_rehash=no])])
   AS_IF([test $ac_cv_hash_map_has_rehash = yes],[
      AC_DEFINE(HASH_MAP_HAS_REHASH, 1, [if hash_map<> hash rehash method])
   ])
   AC_CACHE_CHECK(
     [whether hash_map has resize method],
     [ac_cv_hash_map_has_resize],
     [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[
#include HASH_MAP_H
using namespace HASH_NAMESPACE;
       ]],[[
HASH_MAP_CLASS<int, int> test_hash;
test_hash.resize(100);
          ]])],
       [ac_cv_hash_map_has_resize=yes],
       [ac_cv_hash_map_has_resize=no])])
   AS_IF([test $ac_cv_hash_map_has_resize = yes],[
      AC_DEFINE(HASH_MAP_HAS_RESIZE, 1, [if hash_map<> hash resize method])
   ])
   AC_CACHE_CHECK(
     [whether to redefine hash<string>],
     [ac_cv_redefine_hash_string],
     [AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM([[
#include HASH_SET_H
#include <string>
using namespace HASH_NAMESPACE;
using namespace std;
          ]],[[
string teststr("test");
HASH_SET_CLASS<string> test_hash;
HASH_SET_CLASS<string>::iterator iter= test_hash.find(teststr);
if (iter != test_hash.end())
  return 1;
          ]])],
       [ac_cv_redefine_hash_string=no],
       [ac_cv_redefine_hash_string=yes])])
   AS_IF([test $ac_cv_redefine_hash_string = yes],[
      AC_DEFINE(REDEFINE_HASH_STRING, 1, [if hash<string> needs to be defined])
   ])
   CXXFLAGS="${save_CXXFLAGS}"
   AC_LANG_POP()
])
