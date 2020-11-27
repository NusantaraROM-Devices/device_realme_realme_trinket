/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <vector>
#include <string>
#include <fstream>

#include <android-base/logging.h>
#include <android-base/properties.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[],
    char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void load_RMX1911() {
    property_override("ro.product.model", "Realme 5");
    property_override("ro.build.product", "RMX1911");
    property_override("ro.product.device", "RMX1911");
}

void load_RMX1927(){
    property_override("ro.product.model", "Realme 5 NFC");
    property_override("ro.build.product", "RMX1927");
    property_override("ro.product.device", "RMX1927");
    property_set("persist.sys.nfc.disPowerSave", "1");
    property_set("persist.sys.nfc.default", "on");
    property_set("persist.sys.nfc.aid_overflow", "true");
    property_set("ro.product.cuptsm", "OPPO|ESE|01|02");
    property_set("persist.sys.nfc.antenna_area", "bottom");
}

void load_RMX2030() {
    property_override("ro.product.model", "Realme 5i");
    property_override("ro.build.product", "RMX2030");
    property_override("ro.product.device", "RMX2030");
}

void vendor_load_properties() {
    std::ifstream infile("/proc/oppoVersion/prjVersion");
    std::string prjName;
    getline(infile, prjName);

    if (prjName == "19631") {
        load_RMX1911();
    } else if (prjName == "19632") {
        load_RMX1927();
    } else if (prjName == "19743") {
        load_RMX2030();
    } else {
        LOG(ERROR) << __func__ << ": unexcepted prjVersion!";
    }


    property_override("ro.control_privapp_permissions", "log");
    property_override("ro.build.description", "coral-user 11 RP1A.201105.002-6869500-release-keys");
    property_override("ro.vendor.build.fingerprint", "google/coral/coral:11/RP1A.201105.002/6869500:user/release-keys");
    property_override("ro.build.fingerprint", "google/coral/coral:11/RP1A.201105.002/6869500:user/release-keys");
}