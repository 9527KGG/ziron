# Copyright 2016 The Fuchsia Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

LOCAL_DIR := $(GET_LOCAL_DIR)

MODULE := $(LOCAL_DIR)

MODULE_TYPE := userapp

MODULE_SRCS += \
	$(LOCAL_DIR)/i2c.c

MODULE_STATIC_LIBS := ulib/ddk

MODULE_LIBS := ulib/magenta ulib/mxio ulib/c

include make/module.mk
