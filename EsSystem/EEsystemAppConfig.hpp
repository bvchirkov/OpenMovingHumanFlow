#pragma once

#include "EEsystem_global.hpp"
#include "EvacAppConfigTest.hpp"

class EEsystemAppConfig: public GpAppConfig
{
    GP_DECLARE_REFLECTABLE_B(EEsystemAppConfig, GpAppConfig)

public:
	using SP	= GpSharedPtr<EEsystemAppConfig>;
	using CSP	= GpSharedConstPtr<EEsystemAppConfig>;

public:
								EEsystemAppConfig	(void);
	virtual						~EEsystemAppConfig	(void) override final;
};
