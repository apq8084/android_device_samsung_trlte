#
# Copyright (C) 2017 The LineageOS Project
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
#

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# Get non-open-source specific aspects
$(call inherit-product, vendor/samsung/trlte/trlte-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += device/samsung/trlte/overlay

# Variant blobs script
PRODUCT_COPY_FILES += \
    device/samsung/trlte/releasetools/variant_blobs_hook.sh:install/bin/variant_blobs_hook.sh \
    device/samsung/trlte-common/releasetools/variant_blobs.sh:install/bin/variant_blobs.sh

# mixer_paths.xml workaround
PRODUCT_COPY_FILES += \
    device/samsung/trlte/releasetools/mixer_paths_eur.sh:install/bin/mixer_paths_eur.sh \
    device/samsung/trlte-common/audio/mixer_paths_eur.xml:install/bin/mixer_paths_eur.xml

# common trlte
$(call inherit-product, device/samsung/trlte-common/trlte.mk)
