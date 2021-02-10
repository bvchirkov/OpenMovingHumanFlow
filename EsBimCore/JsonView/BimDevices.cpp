/*Copyright (c) 2019 Boris Chirkov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// File created 03.07.2019

#include "BimDevices.hpp"

GP_IMPL_REFLECTABLE(BimDevices,
                    "12acd002-218e-4d15-b5b1-cf618fe007ff"_sv,
                    GpReflectInheritanceState::FINAL,
                    1);

BimDevices::BimDevices() = default;
BimDevices::~BimDevices() = default;

void BimDevices::SRegisterProps(GpReflectRegPropsCtx &aCtx)
{
    GP_WARNING_PUSH()
    GP_WARNING_DISABLE(invalid-offsetof)

    GP_REFLECT_REGISTER_PROP(BimDevices, Addr,
                             "971bec97-f228-4096-8e4b-0aa0c1756413"_sv, "Addr"_sv);
    GP_REFLECT_REGISTER_PROP(BimDevices, Sign,
                             "80b7b51c-c29c-4962-ba52-1bd2a11c561a"_sv, "Sign"_sv);
    GP_REFLECT_REGISTER_PROP(BimDevices, Owner,
                             "c507b782-74d9-43b3-a1d2-77e4e6ae6eee"_sv, "Owner"_sv);
    GP_REFLECT_REGISTER_PROP(BimDevices, Id,
                             "2b7dac24-28cd-4078-8045-9b9cf3dbd832"_sv, "Id"_sv);
    GP_REFLECT_REGISTER_PROP(BimDevices, Name,
                             "fd68b7c8-6201-432e-a109-829db2a03a26"_sv, "Name"_sv);
    GP_REFLECT_REGISTER_PROP(BimDevices, Position,
                             "c14c856a-5c1d-413e-a11b-875b8392eb4b"_sv, "Position"_sv);

    GP_WARNING_POP()
}

void	BimDevices::SRegisterMeta (GpReflectRegMetaCtx& /*aCtx*/)
{
}

BimDevices::BimDevices(const BimDevices &aBimDevices) :
    Addr(aBimDevices.Addr),
    Sign(aBimDevices.Sign),
    Owner(aBimDevices.Owner),
    Id(aBimDevices.Id),
    Name(aBimDevices.Name),
    Position(aBimDevices.Position.Clone())
{

}
