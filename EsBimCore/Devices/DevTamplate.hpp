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

// File created 04.07.2019

#pragma once

#include "BimDevBase.hpp"

template<typename E>
class DevTamplate : public BimDevBase
{
    E           value;

public:
    using SP    = GpSharedPtr<DevTamplate>;
    using CSP   = GpSharedConstPtr<DevTamplate>;

public:
    explicit DevTamplate(const E &aValue) : value(aValue) {}
    DevTamplate(const DevTamplate &aDevTamplate) :
        BimDevBase(aDevTamplate),
        value(aDevTamplate.value)
    {}
    virtual ~DevTamplate() = default;

public:
    const GpUUID&                   getDevId()			const override { return value.VCn().getDevId(); }
    const std::string_view          getDevName()		const override { return value.VCn().getDevName(); }
    const BimDevicesTypes           getDevSign()		const override { return value.VCn().getDevSign(); }
          uint                      getDevAddr()		const override { return value.VCn().getDevAddr(); }
    const BimPolygonPoint::SP&		getDevPosition()	const override { return value.VCn().getDevPosition(); }
    const GpUUID&					getDevOwner()		const override { return value.VCn().getDevOwner(); }

};
