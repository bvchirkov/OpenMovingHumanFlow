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

//
// Класс, описывающий элемент Лестница
// Все поля описаны в базовом классе BimBaseElement и классе BimRoomElement
// UUID ffef2dae-a46c-42b7-aa4f-86507d7f8acc должен быть записан
// для каждого элемента c типом Staircase в структуре json
//

#pragma once

#include "BimRoomElement.hpp"

class BimStairElement : public BimRoomElement
{
GP_DECLARE_REFLECTABLE_B(BimStairElement, BimRoomElement)

public:
    using SP    = GpSharedPtr<BimStairElement>;
    using CSP   = GpSharedConstPtr<BimStairElement>;
    using VecSP = GpVector<SP>;

public:
    BimStairElement() = default;
    BimStairElement(const BimStairElement& aBimStairElement);
    virtual                    ~BimStairElement() override final;
};


