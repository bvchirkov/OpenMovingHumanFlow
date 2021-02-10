//
// Created by boris on 05.02.19.
//

#include "BimPolygonRing.hpp"

GP_IMPL_REFLECTABLE(BimPolygonRing,
                    "3f5f4df8-da66-46a0-8719-3c1153bca31a"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimPolygonRing::BimPolygonRing() = default;

BimPolygonRing::~BimPolygonRing() = default;

void BimPolygonRing::SRegisterProps (GpReflectRegPropsCtx& aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimPolygonRing, points,
                             "e6a7e9e4-8f23-46e9-bafc-133fa7ad5609"_sv, "points"_sv);

    GP_WARNING_POP()
}

void	BimPolygonRing::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimPolygonRing::BimPolygonRing(const BimPolygonRing &aBimPolygonRing)
{
	BimPolygonPoint::SP::SDeepCopyVec(aBimPolygonRing.points, points);
}
