/*
Copyright 2015 Yixin Zhang

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SWF file decompression support is provided by the zlib 1.2.8 library,
distributed under zlib license 1.2.8, and the LZMA SDK version 9.20, which is placed
in the public domain.
*/

#include "DataConverter.h"
#include "AITriggerData.h"

namespace PWTools
{

	// Public Functions

	AITriggerData::AITriggerData() : trigger_data_version(0), trigger_data_id(0), trigger_data_IsActive(0), trigger_data_IsRun(0), trigger_data_OnlyAttackValid(0), trigger_data_name(nullptr)
	{
	}

	AITriggerData::AITriggerData(const AITriggerData& a) : trigger_data_version(a.trigger_data_version), trigger_data_id(a.trigger_data_id), trigger_data_IsActive(a.trigger_data_IsActive), trigger_data_IsRun(a.trigger_data_IsRun), trigger_data_OnlyAttackValid(a.trigger_data_OnlyAttackValid), trigger_data_name(nullptr)
	{
	    if (a.trigger_data_name)
        {
            trigger_data_name = new char[128];
            memcpy(trigger_data_name, a.trigger_data_name, 128);
        }
        else
            trigger_data_name = nullptr;
	}

	AITriggerData& AITriggerData::operator=(const AITriggerData& a)
	{
	    trigger_data_version = a.trigger_data_version;
	    trigger_data_id = a.trigger_data_id;
	    trigger_data_IsActive = a.trigger_data_IsActive;
	    trigger_data_IsRun = a.trigger_data_IsRun;
	    trigger_data_OnlyAttackValid = a.trigger_data_OnlyAttackValid;
	    if (a.trigger_data_name)
        {
            trigger_data_name = new char[128];
            memcpy(trigger_data_name, a.trigger_data_name, 128);
        }
        else
            trigger_data_name = nullptr;
        return *this;
	}

	void AITriggerData::ReadData(char *buffer, std::size_t buffer_size)
	{
		DataConverter::Init(buffer, buffer_size);

		readData();
	}

	AITriggerData::~AITriggerData()
	{

	}

	// Private Functions

	void AITriggerData::readData()
	{
		DataConverter::ReadT(trigger_data_version);
		DataConverter::ReadT(trigger_data_id);
		DataConverter::ReadT(trigger_data_IsActive);
		DataConverter::ReadT(trigger_data_IsRun);
		DataConverter::ReadT(trigger_data_OnlyAttackValid);
		DataConverter::ReadBytes(trigger_data_name = new char[128], 128);
	}

}
