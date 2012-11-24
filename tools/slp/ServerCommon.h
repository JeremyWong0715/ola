/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Base.h
 * Copyright (C) 2012 Simon Newton
 */

#ifndef TOOLS_SLP_SERVERCOMMON_H_
#define TOOLS_SLP_SERVERCOMMON_H_

#include <stdint.h>

namespace ola {
namespace slp {

// The default SLP port from RFC 2608
static const int DEFAULT_SLP_PORT = 427;

// These are both in seconds, values are from the RFC
static const uint32_t CONFIG_DA_BEAT = 3 * 60 * 60;
static const uint32_t CONFIG_DA_FIND = 900;
static const uint32_t CONFIG_MC_MAX  = 15;
static const uint32_t CONFIG_RETRY = 2;
static const uint32_t CONFIG_RETRY_MAX = 15;

static const char SLP_SERVICE_PREFIX[] = "service:";

static const char DIRECTORY_AGENT_SERVICE[] = "service:directory-agent";

static const char SERVICE_AGENT_SERVICE[] = "service:service-agent";
}  // slp
}  // ola
#endif  // TOOLS_SLP_SERVERCOMMON_H_
