//
// Created by boris on 23.01.19.
//

#include "BimBaseElement.hpp"

GP_IMPL_REFLECTABLE(BimBaseElement,
                    "d1feec0c-3b21-45be-9c01-5ef6803a7300"_sv,
                    GpReflectInheritanceState::HERITABLE,
                    1);

BimBaseElement::BimBaseElement() = default;

BimBaseElement::~BimBaseElement() = default;

void BimBaseElement::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimBaseElement, Id,
                             "877d03c6-9daa-4b6c-b1e9-4df72b2d26c0"_sv, "Id"_sv);
    GP_REFLECT_REGISTER_PROP(BimBaseElement, Name,
                             "34ef1572-c06e-4e2e-b9c5-d03eca33ebec"_sv, "Name"_sv);
    GP_REFLECT_REGISTER_PROP(BimBaseElement, Output,
                             "fe4a7765-fd99-411e-84e9-8aa2776bcef6"_sv, "Output"_sv);
    GP_REFLECT_REGISTER_PROP(BimBaseElement, SizeZ,
                             "d6c02db8-37c2-4a90-a469-b3a9eea920f4"_sv, "SizeZ"_sv);
    GP_REFLECT_REGISTER_PROP(BimBaseElement, Sign,
                             "afb58225-4dd8-4e14-9891-e1bd462d180b"_sv, "Sign"_sv);
    GP_REFLECT_REGISTER_PROP(BimBaseElement, XY,
                             "721ec943-ceb6-4a1e-899f-c99b0a76b850"_sv, "XY"_sv);

    GP_WARNING_POP()
}

void	BimBaseElement::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimBaseElement::BimBaseElement(const BimBaseElement &aBimBaseElement) :
    Id(aBimBaseElement.Id),
    Name(aBimBaseElement.Name),
    Sign(aBimBaseElement.Sign),
    Output(aBimBaseElement.Output),
    SizeZ(aBimBaseElement.SizeZ)
{
    BimPolygonRing::SP::SDeepCopyVec(aBimBaseElement.XY, XY);
}
