# Copyright 2017 The Fuchsia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

ifeq ($(ARCH),x86)

LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_TYPE := driver

MODULE_SRCS := $(LOCAL_DIR)/i8042.c

MODULE_STATIC_LIBS := ulib/ddk ulib/hid

MODULE_LIBS := ulib/driver ulib/magenta ulib/c

include make/module.mk

endif