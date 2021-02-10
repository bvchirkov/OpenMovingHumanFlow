#include "EEsystemAppConfig.hpp"

GP_IMPL_REFLECTABLE(EEsystemAppConfig,
                    "d3ed9a2e-d681-4721-b54b-92a8983d9a4b"_sv,
                    GpReflectInheritanceState::HERITABLE,
                    1);

EEsystemAppConfig::EEsystemAppConfig (void)
{
}

EEsystemAppConfig::~EEsystemAppConfig (void)
{
}

void	EEsystemAppConfig::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
	GP_WARNING_PUSH()
	GP_WARNING_DISABLE(invalid-offsetof)

	GP_WARNING_POP()
}

void	EEsystemAppConfig::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}
