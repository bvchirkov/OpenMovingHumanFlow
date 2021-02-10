//
// Created by boris on 21.01.19.
//

#include "BimRoomElement.hpp"

GP_IMPL_REFLECTABLE(BimRoomElement,
                    "9a9d5f7b-bd3d-433e-80ee-25403e857896"_sv,
                    GpReflectInheritanceState::HERITABLE,
                    1);

void BimRoomElement::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimRoomElement, SignScenario,
                             "af813d9c-c8ab-4b62-83c4-592377e823ea"_sv, "SignScenario"_sv);
    GP_REFLECT_REGISTER_PROP(BimRoomElement, Type,
                             "26315070-0201-43ef-9113-7d961085d5b4"_sv, "Type"_sv);
    GP_REFLECT_REGISTER_PROP(BimRoomElement, NumPeople,
                             "6c3fd2da-7920-40b1-a903-502a90a42b20"_sv, "NumPeople"_sv);

    GP_WARNING_POP()
}

void	BimRoomElement::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimRoomElement::BimRoomElement(const BimRoomElement &aBimRoomElement) :
    SignScenario(aBimRoomElement.SignScenario),
    NumPeople(aBimRoomElement.NumPeople),
    Type(aBimRoomElement.Type)
{

}
