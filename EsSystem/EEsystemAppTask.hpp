#pragma once

#include "EEsystemAppConfig.hpp"

#include "./utils/tools/EsBimBinding.hpp"
#include "./utils/tools/EsBimTools.hpp"
#include "./utils/tools/EsDevicesBinding.hpp"

class EEsystemAppTask : public GpTaskCoroutine
{
public:
	using SP	= GpSharedPtr<EEsystemAppTask>;
	using CSP	= GpSharedConstPtr<EEsystemAppTask>;

    static GpQueueLF<EsBlockingMonitor::SP> sMessageQueue;
    static std::time_t                      sUnixTime;

public:
							EEsystemAppTask		(void);
	virtual					~EEsystemAppTask	(void) override final;

protected:
    virtual void			ExecuteCoroTask	(void) override final;
    virtual void			OnTaskEnd		(void) noexcept override final;

private:
    void                    ProvidePathsToPeople    (EsBimBinding::SP &aBim, EsDevicesBinding::SP &aDevs);
    void                    GetBlockedElements      (GpUUID &blockedElementUuid, EsDevicesBinding::SP &aDevs);

    void                    DeviceBinding           (EsDevicesBinding::SP &devs);
};

