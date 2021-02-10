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

#include "JsonView/BimStairElement.hpp"
#include "BaseElementTamplate.hpp"
#include "BaseElement.hpp"

class Stair : public BaseElementTamplate<BimStairElement::SP>
{

public:
    using SP    = GpSharedPtr<Stair>;
    using CSP   = GpSharedConstPtr<Stair>;

private:
    GpUUID              upOutput;
    GpUUID              downOutput;

public:
    explicit Stair(BimStairElement::SP aBse) : BaseElementTamplate(aBse) {setNumOfPeople(getNumberOfPeople());}
    Stair(const Stair& aStair) :
        BaseElementTamplate(aStair),
        upOutput(aStair.upOutput),
        downOutput(aStair.downOutput)
    {}
    ~Stair() final = default;

public:
    const GpUUID&       getUpOutput() const { return upOutput; }
    const GpUUID&       getDownOutput() const { return downOutput; }

    void                setUpOutput(const GpUUID aUpOutput) { upOutput = aUpOutput; }
    void                setDownOutput(const GpUUID aDownOutput) { downOutput = aDownOutput; }
};


