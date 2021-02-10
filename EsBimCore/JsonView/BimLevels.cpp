//
// Created by boris on 18.01.19.
//

#include "BimLevels.hpp"

GP_IMPL_REFLECTABLE(BimLevels,
                    "105e013c-5163-4f3c-92eb-362a054f6acb"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimLevels::BimLevels() = default;

BimLevels::~BimLevels() = default;

void BimLevels::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimLevels, NameLevel,
                             "47f44db3-2833-4079-a219-e44c8daa02ba"_sv, "NameLevel"_sv);
    GP_REFLECT_REGISTER_PROP(BimLevels, ZLevel,
                             "804d4648-e1c1-4c4e-81d1-29ba61d98e78"_sv, "ZLevel"_sv);
    GP_REFLECT_REGISTER_PROP(BimLevels, BuildElement,
                             "b8c58649-b42a-426e-a888-4e338ca92c47"_sv, "BuildElement"_sv);


    GP_WARNING_POP()
}

void	BimLevels::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimLevels::BimLevels(const BimLevels &aBimLevels) :
    NameLevel(aBimLevels.NameLevel),
    ZLevel(aBimLevels.ZLevel)
{
    BimBaseElement::SP::SDeepCopyVec(aBimLevels.BuildElement, BuildElement);
}
