/* net.c - KNoT Application Client */

/*
 * Copyright (c) 2019, CESAR. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * The knot client application is acting as a client that is run in Zephyr OS,
 * The client sends sensor data encapsulated using KNoT netcol.
 */


#include <zephyr.h>
#include <net/net_core.h>
#include <logging/log.h>

#include "knot.h"
#include <knot/knot_types.h>
#include <knot/knot_protocol.h>

LOG_MODULE_REGISTER(plate, LOG_LEVEL_DBG);

/* Tracked value */
static char plate[] = "KNT0000";

int random_plate(int id)
{
	int num;

	num = (sys_rand32_get() % 7);
	plate[3] = '0' + num;
	plate[4] = '1' + num;
	plate[5] = '2' + num;
	plate[6] = '3' + num;

	return KNOT_CALLBACK_SUCCESS;
}

void setup(void)
{
	bool success;

	/* PLATE - Sent every 10 seconds */
	if (knot_data_register(0, "PLATE", KNOT_TYPE_ID_NONE,
			       KNOT_VALUE_TYPE_RAW, KNOT_UNIT_NOT_APPLICABLE,
			       &plate, sizeof(plate),
			       NULL, random_plate) < 0) {
		LOG_ERR("PLATE failed to register");
	}
	success = knot_data_config(0, KNOT_EVT_FLAG_TIME, 10, NULL);
	if (!success)
		LOG_ERR("PLATE failed to configure");
}

void loop(void)
{
}
