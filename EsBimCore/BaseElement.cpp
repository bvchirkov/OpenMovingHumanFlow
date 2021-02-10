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

#include "BaseElement.hpp"

void BaseElement::addItemToPath(const GpUUID &aQueueName, const std::vector<GpUUID> aItems)
{
    pathesToExits.emplace(aQueueName, aItems);
}

std::vector<GpUUID> &BaseElement::getPathToExit(const GpUUID &aQueueName)
{
    return pathesToExits.at(aQueueName);
}

BaseElement::BaseElement(const BaseElement &aBaseElement) :
    Base(aBaseElement),
    distanceToExit(aBaseElement.distanceToExit),
    pathesToExits(aBaseElement.pathesToExits),
    numOfPeople(aBaseElement.numOfPeople),
    potential(aBaseElement.potential)
{}

void BaseElement::setDistanceToExit(const GpUUID& aQueueName, double aDistance)
{
    if (distanceToExit.count(aQueueName) == 0)
    {
        distanceToExit.emplace(aQueueName, aDistance);
    } else
    {
        THROW_GP_EXCEPTION("Из очереди "_sv + aQueueName.ToString() + " уже заходили в помещение"_sv);
    }
}

double BaseElement::getDistanceToExit(const GpUUID& aQueueName) const
{
    return distanceToExit.at(aQueueName);
}
