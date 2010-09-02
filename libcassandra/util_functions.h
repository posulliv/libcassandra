/*
 * LibCassandra
 * Copyright (C) 2010 Padraig O'Sullivan
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license. See
 * the COPYING file in the parent directory for full text.
 */

#ifndef __LIBCASSANDRA_UTIL_FUNCTIONS_H
#define __LIBCASSANDRA_UTIL_FUNCTIONS_H

#include <string>


namespace libcassandra
{


/**
 * @param[in] url to parse
 * @return the port number from the given url
 */
int parsePortFromURL(const std::string &url);


/**
 * @param[in] url to parse
 * @return the host namefrom the given url
 */
std::string parseHostFromURL(const std::string &url);


} /* end namespace libcassandra */

#endif /* __LIBCASSANDRA_UTIL_FUNCTIONS_H */
