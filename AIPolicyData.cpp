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
#include "AIPolicyData.h"

namespace PWTools
{

	// Public Functions

	AIPolicyData::AIPolicyData() : signature(0), policy_data_id(0), trigger_data_count(0), trigger_data(nullptr)
	{
	}

	AIPolicyData::AIPolicyData(const AIPolicyData& a) : signature(a.signature), policy_data_id(a.policy_data_id), trigger_data_count(a.trigger_data_count), trigger_data(nullptr)
	{
        if (trigger_data_count)
        {
            trigger_data = new std::vector<AITriggerData *>(trigger_data_count);
            *trigger_data = *a.trigger_data;
        }
        else
            trigger_data = nullptr;
	}

	AIPolicyData& AIPolicyData::operator=(const AIPolicyData& a)
	{
	    signature = a.signature;
	    policy_data_id = a.policy_data_id;
	    trigger_data_count = a.trigger_data_count;
        if (trigger_data_count)
        {
            trigger_data = new std::vector<AITriggerData *>(trigger_data_count);
            *trigger_data = *a.trigger_data;
        }
        else
            trigger_data = nullptr;
        return *this;
	}

	void AIPolicyData::ReadData(char *buffer, std::size_t buffer_size)
	{
		DataConverter::Init(buffer, buffer_size);

		readData();
	}

	AIPolicyData::~AIPolicyData()
	{
		if (trigger_data_count)
		{
			for (std::size_t i = 0; i < trigger_data_count; ++i)
				delete trigger_data->at(i);
			delete trigger_data;
		}
	}

	// Private Functions

	void AIPolicyData::readData()
	{
		DataConverter::ReadT(signature);
		DataConverter::ReadT(policy_data_id);
		initTriggerData();
	}

	void AIPolicyData::initTriggerData()
	{
		DataConverter::ReadT(trigger_data_count);
		if (trigger_data_count)
		{
			trigger_data = new std::vector<AITriggerData *>(trigger_data_count);
			for (std::size_t i = 0; i < trigger_data_count; ++i)
				(trigger_data->at(i) = new AITriggerData())->ReadData(DataConverter::GetBuffer(), DataConverter::GetBufferLeft());
		}
	}

}
