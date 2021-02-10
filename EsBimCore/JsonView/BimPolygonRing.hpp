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
// Описывает кольца полигона элмента набором точек BimPolygonPoint
// Для двери и лестницы может быть только одно кольцо.
// Помещение может иметь внутренние кольца - пустоты.
//

#pragma once

#include "BimPolygonPoint.hpp"

class BimPolygonRing : public GpReflectable
{
GP_DECLARE_REFLECTABLE(BimPolygonRing)

private:
    BimPolygonPoint::VecSP     points;  // Список точек кольца

public:
    using SP    = GpSharedPtr<BimPolygonRing>;
    using CSP   = GpSharedConstPtr<BimPolygonRing>;
    using VecSP = GpVector<SP>;

public:
    BimPolygonRing();
    BimPolygonRing(const BimPolygonRing& aBimPolygonRing);
    virtual                    ~BimPolygonRing() override final;

public:
    const BimPolygonPoint::VecSP& getPoints() const { return points; }
};
