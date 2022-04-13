#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(UseCustomText, bool, "Use Custom Values", true);
    CONFIG_VALUE(SoloButton, std::string, "Solo Button", "SOLO");
    CONFIG_VALUE(OnlineButton, std::string, "Multiplayer Button", "ONLINE");
    CONFIG_VALUE(CampaignButton, std::string, "Campaign Button", "CAMPAIGN");
    CONFIG_VALUE(PartyButton, std::string, "Party Button", "PARTY");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(UseCustomText);
        CONFIG_INIT_VALUE(SoloButton);
        CONFIG_INIT_VALUE(OnlineButton);
        CONFIG_INIT_VALUE(CampaignButton);
        CONFIG_INIT_VALUE(PartyButton);
    )
)