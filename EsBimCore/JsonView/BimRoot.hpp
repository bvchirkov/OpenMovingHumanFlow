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

/******************************************************************************
* Вершина дерева структуры прострнственно-информационной модели здания.
******************************************************************************/
#pragma once

#include "../BimCore.hpp"
#include "BimLevels.hpp"
#include "BimAddrInfo.hpp"
#include "BimDevices.hpp"

class BimRoot : public GpReflectable
{
GP_DECLARE_REFLECTABLE(BimRoot)

private:
    std::string         NameBuilding;   // Название объекта
    BimAddrInfo::SP     Address;        // Информация о местоположении
    BimLevels::VecSP    Level;          // Список уровней, на которых расположены элементы
    BimDevices::VecSP   Devs;           // Список устройств, размещенных в здани

public:
    using SP    = GpSharedPtr<BimRoot>;
    using CSP   = GpSharedConstPtr<BimRoot>;

public:
    BimRoot();
	BimRoot(const BimRoot& aBimRoot);
    virtual                    ~BimRoot() override final;

public:
		  std::string         getNameBuilding()			{ return NameBuilding; }
		  BimAddrInfo::SP     getAddressInfo()			{ return Address; }
		  BimLevels::VecSP &  getLevelsBuilding()		{ return Level; }

	const BimDevices::VecSP & getDevicesList()	const	{ return Devs; }
};
