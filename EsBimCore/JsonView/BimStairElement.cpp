//
// Created by boris on 08.02.19.
//

#include "BimStairElement.hpp"

GP_IMPL_REFLECTABLE(BimStairElement,
                    "ffef2dae-a46c-42b7-aa4f-86507d7f8acc"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimStairElement::BimStairElement(const BimStairElement &aBimStairElement)
{}

BimStairElement::~BimStairElement() {}

void BimStairElement::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    /*GP_REFLECT_REGISTER_PROP(BimStairElement, SignScenario);*/

    GP_WARNING_POP()
}

void	BimStairElement::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}
