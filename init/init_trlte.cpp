/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (c) 2017-2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::base::SetProperty;

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void gsm_properties()
{
    SetProperty("telephony.lteOnGsmDevice", "1");
    SetProperty("ro.telephony.default_network", "9");
}

void cdma_properties(char const *operator_alpha,
                     char const *operator_numeric,
                     char const *cdma_sub)
{
    /* Dynamic CDMA Properties */
    SetProperty("ro.cdma.home.operator.alpha", operator_alpha);
    SetProperty("ro.cdma.home.operator.numeric", operator_numeric);
    SetProperty("ro.telephony.default_cdma_sub", cdma_sub);

    /* Static CDMA Properties */
    SetProperty("ril.subscription.types", "NV,RUIM");
    SetProperty("ro.telephony.default_network", "10");
    SetProperty("telephony.lteOnCdmaDevice", "1");
}

void vendor_load_properties()
{
    std::string bootloader = GetProperty("ro.bootloader", "");

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    if (bootloader.find("N910F") == 0) {
        /* trltexx */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trltexx/trlte:6.0.1/MMB29M/N910FXXS1DQH9:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910F");
            set_ro_product_prop(source, "device", "trlte");
            set_ro_product_prop(source, "name", "trltexx");
        }
        property_override("ro.build.description", "trltexx-user 6.0.1 MMB29M N910FXXS1DQH9 release-keys");
        gsm_properties();
    } else if (bootloader.find("N910G") == 0) {
        /* trltedt */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trltedt/trlte:6.0.1/MMB29M/N910GDTU1DQL2:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910G");
            set_ro_product_prop(source, "device", "trlte");
            set_ro_product_prop(source, "name", "trltedt");
        }
        property_override("ro.build.description", "trltedt-user 6.0.1 MMB29M N910GDTU1DQL2 release-keys");
        gsm_properties();
    } else if (bootloader.find("N910P") == 0) {
        /* trltespr */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trltespr/trltespr:6.0.1/MMB29M/N910PVPU5DQI5:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910P");
            set_ro_product_prop(source, "device", "trltespr");
            set_ro_product_prop(source, "name", "trltespr");
        }
        property_override("ro.build.description", "trltespr-user 6.0.1 MMB29M N910PVPU5DQI5 release-keys");
        cdma_properties("Sprint", "310120", "1");
    } else if (bootloader.find("N910R4") == 0) {
        /* trlteusc */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trlteusc/trlteusc:6.0.1/MMB29M/N910R4TYS1CQC1:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910R4");
            set_ro_product_prop(source, "device", "trlteusc");
            set_ro_product_prop(source, "name", "trlteusc");
        }
        property_override("ro.build.description", "trlteusc-user 6.0.1 MMB29M N910R4TYS1CQC1 release-keys");
        cdma_properties("U.S. Cellular", "311580", "1");
    } else if (bootloader.find("N910T") == 0) {
        /* trltetmo */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trltetmo/trltetmo:6.0.1/MMB29M/N910TUVU2EQI2:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910T");
            set_ro_product_prop(source, "device", "trltetmo");
            set_ro_product_prop(source, "name", "trltetmo");
        }
        property_override("ro.build.description", "trltetmo-user 6.0.1 MMB29M N910TUVU2EQI2 release-keys");
        gsm_properties();
    } else if (bootloader.find("N910V") == 0) {
        /* trltevzw */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "Verizon/trltevzw/trltevzw:6.0.1/MMB29M/N910VVRU2CQL1:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910V");
            set_ro_product_prop(source, "device", "trltevzw");
            set_ro_product_prop(source, "name", "trltevzw");
        }
        SetProperty("ro.telephony.get_imsi_from_sim", "true");
        property_override("ro.build.description", "trltevzw-user 6.0.1 MMB29M N910VVRU2CQL1 release-keys");
        cdma_properties("Verizon", "311480", "1");
    } else if (bootloader.find("N910W8") == 0) {
        /* trltecan */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trltecan/trltecan:6.0.1/MMB29M/N910W8VLS1DQH2:user/release-keys");
            set_ro_product_prop(source, "model", "SM-N910W8");
            set_ro_product_prop(source, "device", "trltecan");
            set_ro_product_prop(source, "name", "trltecan");
        }
        property_override("ro.build.description", "trltecan-user 6.0.1 MMB29M N910W8VLS1DQH2 release-keys");
        gsm_properties();
    } else {
        gsm_properties();
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << bootloader << " setting build properties for " << device << " device" << std::endl;
}
