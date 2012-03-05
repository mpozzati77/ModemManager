/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Copyright (C) 2012 Google, Inc.
 */

#ifndef MM_IFACE_MODEM_TIME_H
#define MM_IFACE_MODEM_TIME_H

#include <glib-object.h>
#include <gio/gio.h>

#define MM_TYPE_IFACE_MODEM_TIME               (mm_iface_modem_time_get_type ())
#define MM_IFACE_MODEM_TIME(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_IFACE_MODEM_TIME, MMIfaceModemTime))
#define MM_IS_IFACE_MODEM_TIME(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_IFACE_MODEM_TIME))
#define MM_IFACE_MODEM_TIME_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), MM_TYPE_IFACE_MODEM_TIME, MMIfaceModemTime))

#define MM_IFACE_MODEM_TIME_DBUS_SKELETON "iface-modem-time-dbus-skeleton"

typedef struct _MMIfaceModemTime MMIfaceModemTime;

struct _MMIfaceModemTime {
    GTypeInterface g_iface;

    /* Check for Time support (async) */
    void (* check_support) (MMIfaceModemTime *self,
                            GAsyncReadyCallback callback,
                            gpointer user_data);
    gboolean (* check_support_finish) (MMIfaceModemTime *self,
                                       GAsyncResult *res,
                                       GError **error);

    /* Loading of the network timezone property. This method may return
     * MM_CORE_ERROR_RETRY if the timezone cannot yet be loaded, so that
     * the interface retries later. */
    void (* load_network_timezone) (MMIfaceModemTime *self,
                                    GAsyncReadyCallback callback,
                                    gpointer user_data);
    MMNetworkTimezone * (* load_network_timezone_finish) (MMIfaceModemTime *self,
                                                          GAsyncResult *res,
                                                          GError **error);
};

GType mm_iface_modem_time_get_type (void);

/* Initialize Time interface (async) */
void     mm_iface_modem_time_initialize        (MMIfaceModemTime *self,
                                                GAsyncReadyCallback callback,
                                                gpointer user_data);
gboolean mm_iface_modem_time_initialize_finish (MMIfaceModemTime *self,
                                                GAsyncResult *res,
                                                GError **error);

/* Enable Time interface (async) */
void     mm_iface_modem_time_enable        (MMIfaceModemTime *self,
                                            GAsyncReadyCallback callback,
                                            gpointer user_data);
gboolean mm_iface_modem_time_enable_finish (MMIfaceModemTime *self,
                                            GAsyncResult *res,
                                            GError **error);

/* Disable Time interface (async) */
void     mm_iface_modem_time_disable        (MMIfaceModemTime *self,
                                             GAsyncReadyCallback callback,
                                             gpointer user_data);
gboolean mm_iface_modem_time_disable_finish (MMIfaceModemTime *self,
                                             GAsyncResult *res,
                                             GError **error);

/* Shutdown Time interface */
void mm_iface_modem_time_shutdown (MMIfaceModemTime *self);

/* Bind properties for simple GetStatus() */
void mm_iface_modem_time_bind_simple_status (MMIfaceModemTime *self,
                                             MMSimpleStatus *status);

#endif /* MM_IFACE_MODEM_TIME_H */
