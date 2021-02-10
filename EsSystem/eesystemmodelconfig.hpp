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

// File created 24.05.2019
#pragma once

#include "EEsystem_global.hpp"
#include <iomanip>

#define MODEL_VERSION 1 //0 - old implementation, 1 - new implementation

enum DistributionTypeE
{
	DENSITY,
    NUM_OF_PEOPLE,
    NUM_OF_PEOPLE_BUILDING,
};

class EEsystemModelConfig
{
private:
    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b1_L4_v2_190701.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b2_L4_v2_190701.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b3_L3_v2_190701.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b4_L5_v2_190701.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b5_L4_v2_190702.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b6_L7_v2_190702.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/УдГУ/0_json/udsu_b7_L8_v2_190701.json"_sv;
//    const std::string_view  PathToBimSrc	= "/tmp/0new.json"_sv;
//    const std::string_view  PathToBimSrc	= "/home/boris/workspace/qgis/eesystem_segment_1/eesegment_6b.json"_sv;
//    const std::string_view  PathToBimSrc	= "/tmp/udsu_b6_L6_v2_190905.json"_sv;
//    const std::string_view  PathToBimSrc	= "/tmp/udsu_b3_L3_v2_191028.json"_sv;
    DistributionTypeE DistributionType      = NUM_OF_PEOPLE_BUILDING;
    double			  DistributionValue     = 150;

    std::unordered_map<GpUUID, double>  BlockedElements;

public:
    EEsystemModelConfig();

public:
	using SP    = GpSharedPtr<EEsystemModelConfig>;
	using CSP   = GpSharedConstPtr<EEsystemModelConfig>;

public:
    std::string_view                                getPathToBimSrc()		const;
    double                                          getDistributionValue()	const;
    DistributionTypeE                               getDistributionType()	const;
    const std::unordered_map<GpUUID, double>&       getBlockedElements()    const;
    void                                            setBlockedElements();
};

EEsystemModelConfig::EEsystemModelConfig()
{
    setBlockedElements();
}

double EEsystemModelConfig::getDistributionValue() const
{
    return DistributionValue;
}

DistributionTypeE EEsystemModelConfig::getDistributionType() const
{
	return DistributionType;
}

const std::unordered_map<GpUUID, double> &EEsystemModelConfig::getBlockedElements() const
{
    return BlockedElements;
}

void EEsystemModelConfig::setBlockedElements()
{
//    BlockedElements.emplace(static_cast<GpUUID>("3456b804-56fe-4c0e-bcf6-e7ba686c5209"_sv), 0.0);
    //BlockedElements.emplace(static_cast<GpUUID>("98d1e907-87be-4c27-9b5d-6ab10c481b8b"_sv), 2.0);
}

std::string_view EEsystemModelConfig::getPathToBimSrc() const
{
	return PathToBimSrc;
}
