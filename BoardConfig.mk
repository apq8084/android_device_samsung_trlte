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

# inherit from common trlte
-include device/samsung/trlte-common/BoardConfigCommon.mk

TARGET_OTA_ASSERT_DEVICE := trlte,trltedt,trltecan,trltespr,trltetmo,trlteusc,trltevzw,trltexx

# Camera
TARGET_FIXUP_PREVIEW := true

# Fingerprint
BUILD_FINGERPRINT := samsung/trltexx/trlte:6.0.1/MMB29M/N910FXXS1DQH9:user/release-keys

# Kernel
TARGET_KERNEL_VARIANT_CONFIG := apq8084_sec_trlte_eur_defconfig

# Init
TARGET_INIT_VENDOR_LIB := libinit_trlte
TARGET_RECOVERY_DEVICE_MODULES := libinit_trlte

# Partitions
BOARD_FLASH_BLOCK_SIZE := 262144
BOARD_BOOTIMAGE_PARTITION_SIZE := 17825792
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 524288000
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 19922944
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 3774873600
BOARD_USERDATAIMAGE_PARTITION_SIZE := 26558296064 # 26558312448 - 16384 (footer)

# Releasetools
TARGET_RELEASETOOLS_EXTENSIONS := device/samsung/trlte-common/releasetools

# Radio/RIL
include $(COMMON_PATH)/radio/single/board.mk

# inherit from the proprietary version
-include vendor/samsung/trlte/BoardConfigVendor.mk
