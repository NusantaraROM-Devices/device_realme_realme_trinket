# Copyright (C) 2009 The Android Open Source Project
# Copyright (C) 2019 The Mokee Open Source Project
# Copyright (C) 2019 The LineageOS Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import common
import re

def FullOTA_Assertions(info):
  AddTrustZoneAssertion(info, info.input_zip)
  PatchVendor(info)
  OTA_InstallEnd(info, False)

def IncrementalOTA_Assertions(info):
  AddTrustZoneAssertion(info, info.target_zip)
  PatchVendor(info)
  OTA_InstallEnd(info, True)

def AddImage(info, basename, dest):
  name = basename
  data = info.input_zip.read("IMAGES/" + basename)
  common.ZipWriteStr(info.output_zip, name, data)
  info.script.AppendExtra('package_extract_file("%s", "%s");' % (name, dest))

def AddTrustZoneAssertion(info, input_zip):
  android_info = info.input_zip.read("OTA/android-info.txt")
  m = re.search(r'require\s+version-tz\s*=\s*(\S+)', android_info)
  if m:
    versions = m.group(1).split('|')
    if len(versions) and '*' not in versions:
      cmd = 'assert(realme_trinket.verify_trustzone(' + ','.join(['"%s"' % tz for tz in versions]) + ') == "1" || abort("ERROR: This package requires firmware from an Android 10 based RealmeUI build. Please upgrade firmware and retry!"););'
      info.script.AppendExtra(cmd)

def PatchVendor(info):
  info.script.AppendExtra('mount("ext4", "EMMC", "/dev/block/bootdevice/by-name/vendor", "/vendor");')
  info.script.AppendExtra('delete_recursive("/vendor/overlay/");')
  info.script.AppendExtra('unmount("/vendor");')
  return

def OTA_InstallEnd(info, incremental):
  info.script.Print("Patching firmware images...")
  AddImage(info, "dtbo.img", "/dev/block/bootdevice/by-name/dtbo")
  return
