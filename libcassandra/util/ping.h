/*
 * LibCassandra
 * Copyright (C) 2010-2011 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_UTIL_PING_H
#define __LIBCASSANDRA_UTIL_PING_H

namespace libcassandra
{

namespace util
{

bool pingCassandraServer(const std::string& hostname,
                         int port);

} /* end namespace util */

} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_UTIL_PING_H */
