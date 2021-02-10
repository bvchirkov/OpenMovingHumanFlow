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
// Класс описания полей помещения. Расширяет базовый класс.
// UUID 9a9d5f7b-bd3d-433e-80ee-25403e857896 должен быть записан
// для каждого элемента с типом Room в структуре json
//

#pragma once

#include "BimBaseElement.hpp"

class BimRoomElement : public BimBaseElement
{
GP_DECLARE_REFLECTABLE_B(BimRoomElement, BimBaseElement)

private:
    int SignScenario    = -1;  // [deprecated] Наличие сценария в данном помещении
    int NumPeople       = -1;  // Количество людей в помещении
    int Type            = -1;  // Тип пожарной нагрузки

public:
    using SP    = GpSharedPtr<BimRoomElement>;
    using CSP   = GpSharedConstPtr<BimRoomElement>;
    using VecSP = GpVector<SP>;

public:
    BimRoomElement()                    = default;
    BimRoomElement(const BimRoomElement& aBimRoomElement);
    virtual ~BimRoomElement() override  = default;

public:
    int getSignScenario()   const { return SignScenario; }
    int getNumberOfPeople() const { return NumPeople; }
    int getType()           const { return Type; }
};
