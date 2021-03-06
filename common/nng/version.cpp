/* SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 * Copyright (c) 2016-2019 Intel Corporation
 *
 * This code is subject to the terms of the BSD+Patent license.
 * See LICENSE file for more details.
 */



#include <mapf/common/config.h>
#include <mapf/common/logger.h>
#include <nng/nng.h>

MAPF_INITIALIZE_LOGGER

int main (void)
{
    printf("Current nng version: %s\n", nng_version());
	printf("Current MAPF version is %s\n", MAPF_VERSION);
    return 0;
}
