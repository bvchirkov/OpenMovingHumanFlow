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

#pragma once

#include "Base.hpp"

class BaseElement : public Base
{
public:
	using SP								= GpSharedPtr<BaseElement>;
	using CSP								= GpSharedConstPtr<BaseElement>;
	using ItemsMapT							= std::unordered_map<GpUUID, std::vector<GpUUID>>;

private:
    std::unordered_map<GpUUID, double>		distanceToExit;             // Расстояние до конкретного эвакуационного выхода
	ItemsMapT								pathesToExits;
	double									numOfPeople		= -1;
	double									potential		= std::numeric_limits<double>::max();

public:
    BaseElement() = default;
    BaseElement(const BaseElement& aBaseElement);
    virtual ~BaseElement() = default;

public:
	virtual double							getNumberOfPeople() const { THROW_NOT_IMPLEMENTED; }

    void                                    setDistanceToExit(const GpUUID& aQueueName, double aDistance);
	double                                  getDistanceToExit(const GpUUID& aQueueName) const;

    void									addItemToPath(const GpUUID& aQueueName, const std::vector<GpUUID> aItems);
	std::vector<GpUUID>&					getPathToExit(const GpUUID& aQueueName);

	double									getNumOfPeople() const { return numOfPeople; }
	void									setNumOfPeople(double aValue) { numOfPeople = aValue; }

	double									getPotential() const { return potential; }
	void									setPotential(double aPotencial) { potential = aPotencial; }
};
