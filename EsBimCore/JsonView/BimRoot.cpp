//
// Created by boris on 17.01.19.
//
#include "BimRoot.hpp"

GP_IMPL_REFLECTABLE(BimRoot,
                    "c37c15ec-547a-4d16-ac82-df08fc72038a"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimRoot::BimRoot() = default;

BimRoot::~BimRoot() = default;

void BimRoot::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimRoot, NameBuilding,
                             "63e046fb-0dd2-4a69-8bc4-fbf9ecdd7ec2"_sv, "NameBuilding"_sv);
    GP_REFLECT_REGISTER_PROP(BimRoot, Level,
                             "f76e9908-ba4c-42db-aae5-9175c0cf9eee"_sv, "Level"_sv);
    GP_REFLECT_REGISTER_PROP(BimRoot, Address,
                             "0ebb4278-116b-47bb-a37b-dfda23ccc306"_sv, "Address"_sv);
    GP_REFLECT_REGISTER_PROP(BimRoot, Devs,
                             "16987c11-1b4b-4490-a134-b75004e34333"_sv, "Devs"_sv);

    GP_WARNING_POP()
}

void	BimRoot::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimRoot::BimRoot(const BimRoot &aBimRoot) :
    NameBuilding(aBimRoot.NameBuilding),
    Address(aBimRoot.Address.Clone())
{
    BimLevels::SP::SDeepCopyVec(aBimRoot.Level, Level);
    BimDevices::SP::SDeepCopyVec(aBimRoot.Devs, Devs);
}
