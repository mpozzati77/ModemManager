/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * libmm -- Access modem status & information from glib applications
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * Author: Aleksander Morgado <aleksander@lanedo.com>
 */

#ifndef _MM_MANAGER_H_
#define _MM_MANAGER_H_

#include <ModemManager.h>
#include <mm-gdbus-modem.h>

G_BEGIN_DECLS

#define MM_TYPE_MANAGER            (mm_manager_get_type ())
#define MM_MANAGER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), MM_TYPE_MANAGER, MMManager))
#define MM_MANAGER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), MM_TYPE_MANAGER, MMManagerClass))
#define MM_IS_MANAGER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MM_TYPE_MANAGER))
#define MM_IS_MANAGER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((obj), MM_TYPE_MANAGER))
#define MM_MANAGER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), MM_TYPE_MANAGER, MMManagerClass))

typedef struct _MMManagerPrivate MMManagerPrivate;

typedef struct {
    /*< private >*/
    MmGdbusObjectManagerClient parent;
    MMManagerPrivate *priv;
} MMManager;

typedef struct {
    /*< private >*/
    MmGdbusObjectManagerClientClass parent;
} MMManagerClass;

GType mm_manager_get_type (void);

void mm_manager_new (
    GDBusConnection               *connection,
    GDBusObjectManagerClientFlags  flags,
    GCancellable                  *cancellable,
    GAsyncReadyCallback            callback,
    gpointer                       user_data);
MMManager *mm_manager_new_finish (
    GAsyncResult  *res,
    GError       **error);
MMManager *mm_manager_new_sync (
    GDBusConnection                *connection,
    GDBusObjectManagerClientFlags   flags,
    GCancellable                   *cancellable,
    GError                        **error);

void mm_manager_set_logging (MMManager           *manager,
                             const gchar         *level,
                             GCancellable        *cancellable,
                             GAsyncReadyCallback  callback,
                             gpointer             user_data);
gboolean mm_manager_set_logging_finish (MMManager     *manager,
                                        GAsyncResult  *res,
                                        GError       **error);
gboolean mm_manager_set_logging_sync (MMManager     *manager,
                                      const gchar   *level,
                                      GCancellable  *cancellable,
                                      GError       **error);

void mm_manager_scan_devices (MMManager           *manager,
                              GCancellable        *cancellable,
                              GAsyncReadyCallback  callback,
                              gpointer             user_data);
gboolean mm_manager_scan_devices_finish (MMManager     *manager,
                                         GAsyncResult  *res,
                                         GError       **error);
gboolean mm_manager_scan_devices_sync (MMManager     *manager,
                                       GCancellable  *cancellable,
                                       GError       **error);

G_END_DECLS

#endif /* _MM_MANAGER_H_ */