/*Copyright (c) 2019 Boris Chirkov

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
THE SOFTWARE.
*/

// File created 03.07.2019

#pragma once

#include "../BimCore.hpp"
#include "../JsonView/BimDevicesTypes.hpp"
#include "../JsonView/BimPolygonPoint.hpp"

//
//  +------------+
//  | BimDevBase |
//  +----+-------+
//       ^
//       |
//       |
//  +----+--------+        +------------+
//  | DevTamplate +--------+ BimDevices |
//  +----+-----+--+        +------------+
//       ^     ^
//       |     +----------------------+
//       |                            |
//  +----+------------------+    +----+------------+
//  | DevDirectionIndicator |    | DevFireDetector |    и другие устройства
//  +-----------------------+    +-----------------+
//

class BimDevBase
{
public:
	using SP    = GpSharedPtr<BimDevBase>;
	using CSP   = GpSharedConstPtr<BimDevBase>;

public:
    BimDevBase() = default;
    BimDevBase(const BimDevBase& aBimDevBase) {}
    virtual ~BimDevBase() = default;

public:
	virtual const GpUUID&                   getDevId()			const { THROW_NOT_IMPLEMENTED; }
    virtual const std::string_view          getDevName()		const { THROW_NOT_IMPLEMENTED; }
    virtual const BimDevicesTypes           getDevSign()		const { THROW_NOT_IMPLEMENTED; }
    virtual uint                            getDevAddr()		const { THROW_NOT_IMPLEMENTED; }
	virtual const BimPolygonPoint::SP&		getDevPosition()	const { THROW_NOT_IMPLEMENTED; }
    virtual const GpUUID&					getDevOwner()		const { THROW_NOT_IMPLEMENTED; }
};
