#pragma once

#include "EEsystem_global.hpp"

class EvacAppConfigTest: public GpReflectable
{
    GP_DECLARE_REFLECTABLE(EvacAppConfigTest)

public:
	using SP	= GpSharedPtr<EvacAppConfigTest>;
	using CSP	= GpSharedConstPtr<EvacAppConfigTest>;

public:
							EvacAppConfigTest	(void);
	virtual					~EvacAppConfigTest	(void) override final;
};


/*
EvacAppConfigTest,
"84b35db9-aa57-4404-b833-42377b087d3c"_sv,
GpReflectStructInhMode::FINAL
*/
