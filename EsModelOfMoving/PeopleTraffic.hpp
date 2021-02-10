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

#include "PMovingCore.hpp"
#include "./../EsBimCore/Safety.hpp"
#include "./../EsSystem/utils/tools/EsBimBinding.hpp"
#include "./../EsSystem/utils/config/EsCfgModel.hpp"

class PeopleTraffic
{
public:
    using SP                    = GpSharedPtr<PeopleTraffic>;
    using CSP                   = GpSharedConstPtr<PeopleTraffic>;
    using QE                    = std::vector<BaseElement::SP>;
    using BEMap         		= std::unordered_map<GpUUID, double>;

private:
    struct Queue {
        GpUUID                  uuid;
        double                  potential;
        QE                      elements;
    };

public:
	PeopleTraffic(EsBimBinding::SP aBim, Safety::SP aSafety, const EsCfgModel::SP aModelCfg);
    PeopleTraffic(const PeopleTraffic& aPeopleTraffic);
    virtual ~PeopleTraffic() = default;

private:
    EsBimBinding::SP            bim;
    Safety::SP                  safetyZone;
	EsCfgModel::SP              modelCfg;
    BEMap                       blockedElements;

private:
    void                        startFillQueue(std::vector<Queue>& aQueues, double& aNumOfPeople, double aTimeStep);

public:
    void                        traffic1(double &aTimeStep, double& aNumOfPeople);
    void                        traffic2(double &aTimeStep, double& aNumOfLockedUpPeople);

    void                        blockElement(const GpUUID& aElement, double aBlockedTime);
    BEMap                       getBlockedElements() const { return blockedElements; }
};
