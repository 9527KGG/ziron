// Copyright 2018 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIB_ZXIO_INCEPTION_H_
#define LIB_ZXIO_INCEPTION_H_

#include <lib/zxio/ops.h>
#include <lib/zxs/zxs.h>
#include <threads.h>
#include <zircon/compiler.h>
#include <zircon/types.h>

// This header exposes some guts of zxio in order to transition fdio to build on
// top of zxio.

__BEGIN_CDECLS

// remote ----------------------------------------------------------------------

// A |zxio_t| backend that uses the |fuchsia.io.Node| protocol.
//
// The |control| handle is a channel that implements the |fuchsia.io.Node|. The
// |event| handle is an optional event object used with some |fuchsia.io.Node|
// servers.
//
// Will eventually be an implementation detail of zxio once fdio completes its
// transition to the zxio backend.
typedef struct zxio_remote {
    zxio_t io;
    zx_handle_t control;
    zx_handle_t event;
} zxio_remote_t;

static_assert(sizeof(zxio_remote_t) <= sizeof(zxio_storage_t),
              "zxio_remote_t must fit inside zxio_storage_t.");

zx_status_t zxio_remote_init(zxio_storage_t* remote, zx_handle_t control,
                             zx_handle_t event);

// vmofile ---------------------------------------------------------------------

typedef struct zxio_vmofile {
    zxio_t io;
    zx_handle_t control;
    zx_handle_t vmo;
    zx_off_t off;
    zx_off_t end;
    zx_off_t ptr;
    // TODO: Migrate to sync_mutex_t.
    mtx_t lock;
} zxio_vmofile_t;

static_assert(sizeof(zxio_vmofile_t) <= sizeof(zxio_storage_t),
              "zxio_vmofile_t must fit inside zxio_storage_t.");

zx_status_t zxio_vmofile_init(zxio_storage_t* file, zx_handle_t control,
                              zx_handle_t vmo, zx_off_t offset, zx_off_t length,
                              zx_off_t seek);

// pipe ------------------------------------------------------------------------

// A |zxio_t| backend that uses a Zircon socket object.
//
// The |socket| handle is a Zircon socket object.
//
// Will eventually be an implementation detail of zxio once fdio completes its
// transition to the zxio backend.
typedef struct zxio_pipe {
    zxio_t io;
    zx_handle_t socket;
} zxio_pipe_t;

static_assert(sizeof(zxio_pipe_t) <= sizeof(zxio_storage_t),
              "zxio_pipe_t must fit inside zxio_storage_t.");

zx_status_t zxio_pipe_init(zxio_storage_t* pipe, zx_handle_t socket);

// socket ----------------------------------------------------------------------

// A |zxio_t| backend that uses a zxs object.
//
// Will eventually be an implementation detail of zxio once fdio completes its
// transition to the zxio backend.
typedef struct zxio_socket {
    zxio_t io;
    zxs_socket_t socket;
} zxio_socket_t;

static_assert(sizeof(zxio_socket_t) <= sizeof(zxio_storage_t),
              "zxio_socket_t must fit inside zxio_storage_t.");

zx_status_t zxio_socket_init(zxio_storage_t* pipe, zxs_socket_t socket);

// debuglog --------------------------------------------------------------------

typedef struct zxio_debuglog_buffer zxio_debuglog_buffer_t;

// A |zxio_t| backend that uses a debuglog.
//
// The |handle| handle is a Zircon debuglog object.
typedef struct zxio_debuglog {
    zxio_t io;
    zx_handle_t handle;
    zxio_debuglog_buffer_t* buffer;
} zxio_debuglog_t;

static_assert(sizeof(zxio_debuglog_t) <= sizeof(zxio_storage_t),
              "zxio_debuglog_t must fit inside zxio_storage_t.");

// Initializes a |zxio_storage_t| to use the given |handle| for output.
//
// The |handle| should be a Zircon debuglog object.
zx_status_t zxio_debuglog_init(zxio_storage_t* storage, zx_handle_t handle);

__END_CDECLS

#endif // LIB_ZXIO_INCEPTION_H_
