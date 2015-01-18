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

#include <sstream>
#include "DataConverter.h"
#include "AIPolicyData.h"
#include "AIPolicyDataManager.h"

namespace PWTools
{

	// Public Functions

	AIPolicyDataManager::AIPolicyDataManager() : signature(0), policy_data_count(0), policy_data(nullptr)
	{
	}

	AIPolicyDataManager::AIPolicyDataManager(const AIPolicyDataManager& a) : signature(a.signature), policy_data_count(a.policy_data_count), policy_data(nullptr)
	{
	    if (policy_data_count)
        {
            policy_data = new std::vector<AIPolicyData *>(policy_data_count);
            *policy_data = *a.policy_data;
        }
        else
            policy_data = nullptr;
	}

	AIPolicyDataManager& AIPolicyDataManager::operator=(const AIPolicyDataManager& a)
	{
	    signature = a.signature;
	    policy_data_count = a.policy_data_count;
	    if (policy_data_count)
        {
            policy_data = new std::vector<AIPolicyData *>(policy_data_count);
            *policy_data = *a.policy_data;
        }
        else
            policy_data = nullptr;
	    return *this;
	}

	void AIPolicyDataManager::ReadData(char *buffer, const std::size_t buffer_size)
	{
		DataConverter::Init(buffer, buffer_size);

		readData();
	}

	std::string* AIPolicyDataManager::GetInfo()
	{
		// Use stringstream to make life easier
		std::stringstream s;
		s	<< "File signature: " << signature << std::endl
			<< "Policy data count: " << policy_data_count << std::endl;
		return new std::string(s.str());
	}

	AIPolicyDataManager::~AIPolicyDataManager()
	{
		if (policy_data_count)
		{
			for (std::size_t i = 0; i < policy_data_count; ++i)
				delete policy_data->at(i);
			delete policy_data;
		}
	}

	// Private Functions

	void AIPolicyDataManager::readData()
	{
		DataConverter::ReadT(signature);
		initPolicyData();
	}

	void AIPolicyDataManager::initPolicyData()
	{
		DataConverter::ReadT(policy_data_count);
		if (policy_data_count)
		{
			policy_data = new std::vector<AIPolicyData *>(policy_data_count);
			for (std::size_t i = 0; i < policy_data_count; ++i)
				(policy_data->at(i) = new AIPolicyData())->ReadData(DataConverter::GetBuffer(), DataConverter::GetBufferLeft());
		}
	}

}
