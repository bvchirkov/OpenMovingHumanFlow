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
// Структура уровня. Уровнем можно обзначить этаж, но это не всегда так.
// Уровень может находится между этажей.
// Все элементы располагаются на уровне. Элементов вне уровня не существует.
//

#pragma once

#include "../BimCore.hpp"
#include "BimBaseElement.hpp"
#include "BimRoomElement.hpp"

class BimLevels : public GpReflectable
{
GP_DECLARE_REFLECTABLE(BimLevels)

private:
    std::string             NameLevel;      // Имя уровня
    double                  ZLevel = -1;    // Расстояние от земли до уровня
    BimBaseElement::VecSP   BuildElement;   // Список элементов на уровне

public:
    using SP    = GpSharedPtr<BimLevels>;
    using CSP   = GpSharedConstPtr<BimLevels>;
    using VecSP = GpVector<SP>;

public:
    BimLevels();
    BimLevels(const BimLevels& aBimLevels);
    virtual                    ~BimLevels() override final;

public:
    std::string &           getNameLevel()      { return NameLevel; }
    double                  getLevelValue()     { return ZLevel; }
    BimBaseElement::VecSP & getBimElements()    { return BuildElement; }
};
