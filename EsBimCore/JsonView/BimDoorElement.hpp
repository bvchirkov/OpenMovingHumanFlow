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
// Класс, описывающий элемент Дверь
// Все поля описаны в базовом классе
// UUID 39baaad1-3bea-4220-ac34-70e3021e4cc8 должен быть записан
// для каждого элемента c типом DoorWay, DoorWayInt, DoorWayOut в структуре json
//

#pragma once

#include "BimBaseElement.hpp"

class BimDoorElement : public BimBaseElement
{
GP_DECLARE_REFLECTABLE_B(BimDoorElement, BimBaseElement)

public:
    using SP    = GpSharedPtr<BimDoorElement>;
    using CSP   = GpSharedConstPtr<BimDoorElement>;
    using VecSP = GpVector<SP>;

public:
    BimDoorElement();
    BimDoorElement(const BimDoorElement& aBimDoorElement);
    virtual         ~BimDoorElement() override;

};

