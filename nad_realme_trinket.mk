#
# Copyright (C) 2019 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

$(call inherit-product, device/realme/realme_trinket/device.mk)

# Inherit some common Nusantara stuff.
$(call inherit-product, vendor/nusantara/config/common_full_phone.mk)

TARGET_BOOT_ANIMATION_RES := 1080

# Nusantara Properties
NAD_BUILD_TYPE := OFFICIAL

# Device identifier. This must come after all inclusions.
PRODUCT_BRAND := Realme
PRODUCT_DEVICE := realme_trinket
PRODUCT_MANUFACTURER := Realme
PRODUCT_NAME := nad_realme_trinket

BUILD_FINGERPRINT := "trinket-user-10-QKQ1.200209.002--release-keys"

PRODUCT_GMS_CLIENTID_BASE := android-realme
