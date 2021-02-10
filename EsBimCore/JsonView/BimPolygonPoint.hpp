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
// В какой то степени промежуточная структура.
// Потребовалась чтоб можно было работать обработать координаты точек полигона.
// Описывает x и y точки.
//

#pragma once

#include "../BimCore.hpp"

class BimPolygonPoint : public GpReflectable
{
GP_DECLARE_REFLECTABLE(BimPolygonPoint)

private:
    double x = -1;
    double y = -1;

public:
    using SP    = GpSharedPtr<BimPolygonPoint>;
    using CSP   = GpSharedConstPtr<BimPolygonPoint>;
    using VecSP = GpVector<SP>;

public:
    BimPolygonPoint();
    BimPolygonPoint(const BimPolygonPoint& aBimPolygonPoint);
    virtual                    ~BimPolygonPoint() override final;

public:
    double getX() const { return x; }
    double getY() const { return y; }
};

