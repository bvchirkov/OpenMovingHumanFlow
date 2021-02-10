//
// Created by boris on 05.02.19.
//

#include "BimPolygonPoint.hpp"

GP_IMPL_REFLECTABLE(BimPolygonPoint,
                    "b154cdb7-8e73-48e1-b197-30e2535d17aa"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimPolygonPoint::BimPolygonPoint() = default;

BimPolygonPoint::~BimPolygonPoint() = default;

void BimPolygonPoint::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimPolygonPoint, x,
                             "2461d5fb-81e7-44e5-9994-6ab409cfa336"_sv, "x"_sv);
    GP_REFLECT_REGISTER_PROP(BimPolygonPoint, y,
                             "782082f3-f8de-4280-91d0-aa7abf7641d6"_sv, "y"_sv);

    GP_WARNING_POP()
}

void	BimPolygonPoint::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimPolygonPoint::BimPolygonPoint(const BimPolygonPoint &aBimPolygonPoint) :
    x(aBimPolygonPoint.x),
    y(aBimPolygonPoint.y)
{

}
