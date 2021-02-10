//
// Created by boris on 21.01.19.
//

#include "BimDoorElement.hpp"

GP_IMPL_REFLECTABLE(BimDoorElement,
                    "39baaad1-3bea-4220-ac34-70e3021e4cc8"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimDoorElement::BimDoorElement() = default;

BimDoorElement::~BimDoorElement() = default;

void BimDoorElement::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    /*GP_REFLECT_REGISTER_PROP(BimDoorElement, SignScenario);*/

    GP_WARNING_POP()
}

void	BimDoorElement::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimDoorElement::BimDoorElement(const BimDoorElement &aBimDoorElement)
{

}
