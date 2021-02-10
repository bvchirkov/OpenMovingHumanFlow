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
// Класс, который описывает поля, которые свойственны всем элементам: комнатам, дверям, лестницам.
//

#pragma once

#include "BimElementSign.hpp"
#include "BimPolygonRing.hpp"

class BimBaseElement : public GpReflectable
{
GP_DECLARE_REFLECTABLE(BimBaseElement)

private:
    GpUUID                              Id;         // UUID объекта
    std::string                         Name;       // Имя
    BimElementSign                      Sign;       // Тип элемента (DoorWay, DoorWayOut, DoorWayInt, Room, Staircase, Outside)
    std::vector<GpUUID>                 Output;     // Соседние элементы в формате UUID
    BimPolygonRing::VecSP               XY;         // Список координат точек полигона
    double                              SizeZ = -1; // Высота элемента

public:
    using SP    = GpSharedPtr<BimBaseElement>;
    using CSP   = GpSharedConstPtr<BimBaseElement>;
    using VecSP = GpVector<SP>;

public:
    BimBaseElement();
    BimBaseElement(const BimBaseElement& aBimBaseElement);
    virtual                    ~BimBaseElement() override;

public:
    const GpUUID&                           getId()             const { return Id; }
          std::string_view                  getName()           const { return Name; }
          BimElementSign                    getSign()           const { return Sign; }
    const std::vector<GpUUID>&              getOutputs()        const { return Output; }
    const BimPolygonRing::VecSP&            getPolygonRings()   const { return XY; }
          double                            getHeight()         const { return SizeZ; }
};
