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

#ifndef _AIPDM_H_
#define _AIPDM_H_

#include <string>
#include <vector>
#include <cstddef>

namespace PWTools
{
	// Forward declarations
	class AIPolicyData;

	class AIPolicyDataManager
	{
	public:
		// Instantiate class and variables
		AIPolicyDataManager();
		AIPolicyDataManager(const AIPolicyDataManager&);
		AIPolicyDataManager& operator=(const AIPolicyDataManager&);

		// Initialize DataConverter and call readData()
		void ReadData(char *buffer, const std::size_t buffer_size);

		// Returns pointer-to-string containing information about aipolicy
		std::string* GetInfo();

		// Cleanup
		~AIPolicyDataManager();

	private:
		// Start reading data from buffer
		void readData();
		// Initialize policy_data
		void initPolicyData();
		// Read elements into policy_data
		AIPolicyData* readPolicyData();


		// 4 bytes: File signature, must be 1
		int signature;
		// 4 bytes: Number of policy data objects in total
		std::size_t policy_data_count;
		// Array of AIPolicyData with length policy_data_count
		std::vector<AIPolicyData *> *policy_data;

	};

}
#endif
