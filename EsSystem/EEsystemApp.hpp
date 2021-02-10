#pragma once

#include "EEsystemAppConfig.hpp"
#include "EEsystemAppTask.hpp"

class EEsystemApp: public GpApp
{
public:
                        EEsystemApp		(const int              aArgc,
                                         const char**           aArgv,
                                         const EEsystemAppConfig& aConfig);
	virtual				~EEsystemApp	(void) override;

protected:
	virtual GpTask::SP	OnAppStart		(void) override;
	virtual void		OnAppError		(std::string_view aMessage) noexcept override;
	virtual void		OnAppClose		(void) noexcept override;
};
