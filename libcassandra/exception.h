/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_EXCEPTION_H
#define __LIBCASSANDRA_EXCEPTION_H

#include <string>
#include <stdexcept>

namespace libcassandra
{

class Exception : public std::runtime_error
{

public:

  Exception(const std::string &msg, int in_errno)
    :
      std::runtime_error(msg),
      _errno(in_errno)
  {}

  Exception(const char *msg, int in_errno)
    :
      std::runtime_error(std::string(msg)),
      _errno(in_errno)
  {}

  virtual ~Exception() throw() {}

  int getErrno() const
  {
    return _errno;
  }

private:

  int _errno;

};

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_EXCEPTION_H */
