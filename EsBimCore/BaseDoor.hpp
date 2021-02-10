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

// File created 08.04.2019

#pragma once

#include "Base.hpp"

class BaseDoor : public Base
{
    double                          passedPeople	= 0;
    double                          width			= 0;
	std::pair<GpUUID, double>       whereFromPeopleGo;

public:
	using SP    = GpSharedPtr<BaseDoor>;
	using CSP   = GpSharedConstPtr<BaseDoor>;

public:
    BaseDoor() = default;
    BaseDoor(const BaseDoor& aBaseDoor) :
        Base(aBaseDoor),
        passedPeople(aBaseDoor.passedPeople),
        width(aBaseDoor.width),
        whereFromPeopleGo(aBaseDoor.whereFromPeopleGo)
    {}
	virtual ~BaseDoor() = default;

public:
	virtual const GpUUID&                   getId()				const { THROW_NOT_IMPLEMENTED; }
    virtual       std::string_view          getName()			const { THROW_NOT_IMPLEMENTED; }
    virtual       BimElementSign            getSign()			const { THROW_NOT_IMPLEMENTED; }
	virtual const std::vector<GpUUID>&      getOutputs()		const { THROW_NOT_IMPLEMENTED; }
	virtual const BimPolygonRing::VecSP&    getPolygonRings()	const { THROW_NOT_IMPLEMENTED; }

    void                                    setPassedPeople(double aPeople) { passedPeople = aPeople; }
	double                                  getPassedPeople()	const { return passedPeople; }

	double									getWidth()			const { return width; }
    void									setWidth(double aWidth)   { width = aWidth; }

	void                                    setWhereFromPeopleGo(const GpUUID aUuid, const double aPeople) { whereFromPeopleGo = std::make_pair(aUuid, aPeople); }
	std::pair<GpUUID, double>               getWhereFromPeopleGo() const  { return whereFromPeopleGo; }
};

