//
// Created by boris on 18.01.19.
//

#include "BimAddrInfo.hpp"

GP_IMPL_REFLECTABLE(BimAddrInfo,
                    "08adbc94-54c3-4d3b-a023-95d3e93d2747"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimAddrInfo::BimAddrInfo() = default;

BimAddrInfo::~BimAddrInfo() = default;

void BimAddrInfo::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimAddrInfo, AddInfo,
                             "d90f3d5b-38c5-4779-b701-a313200cdbf2"_sv, "AddInfo"_sv);
    GP_REFLECT_REGISTER_PROP(BimAddrInfo, City,
                             "a91bb76a-2410-471e-b3e4-374d41f99954"_sv, "City"_sv);
    GP_REFLECT_REGISTER_PROP(BimAddrInfo, StreetAddress,
                             "77d1f665-23a5-4dc5-953e-acdf6115e5b4"_sv, "StreetAddress"_sv);

    GP_WARNING_POP()
}

void	BimAddrInfo::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimAddrInfo::BimAddrInfo(const BimAddrInfo &aBimAddrInfo) :
    City(aBimAddrInfo.City),
    StreetAddress(aBimAddrInfo.StreetAddress),
    AddInfo(aBimAddrInfo.AddInfo)
{

}
