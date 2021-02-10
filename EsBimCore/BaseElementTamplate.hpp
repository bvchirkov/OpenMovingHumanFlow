/* Copyright (c) 2019 Boris Chirkov

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
THE SOFTWARE. */

#pragma once

#include "JsonView/BimElementSign.hpp"
#include "JsonView/BimPolygonRing.hpp"
#include "BaseElement.hpp"

template<typename E>
class BaseElementTamplate : public BaseElement
{
protected:
    E                               value;

public:
    using SP    = GpSharedPtr<BaseElementTamplate>;
    using CSP   = GpSharedConstPtr<BaseElementTamplate>;

public:
    explicit BaseElementTamplate(E aValue) : value(aValue) {}
    BaseElementTamplate(const BaseElementTamplate& aBaseElementTamplate) :
        BaseElement(aBaseElementTamplate),
        value(aBaseElementTamplate.value)
    {}
    virtual ~BaseElementTamplate() = default;

public:
    const GpUUID&                   getId()             const override { return value.VC().getId(); }
    std::string_view                getName()           const override { return value.VC().getName(); }
    BimElementSign                  getSign()           const override { return value.VC().getSign(); }
    const std::vector<GpUUID>&      getOutputs()        const override { return value.VC().getOutputs(); }
    const BimPolygonRing::VecSP&    getPolygonRings()   const override { return value.VC().getPolygonRings(); }
    double                          getNumberOfPeople() const override { return value.VC().getNumberOfPeople(); }
};
