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

#ifndef _AIPD_H_
#define _AIPD_H_

#include <vector>

namespace PWTools
{
	// Forward declarations
	class AITriggerData;

	class AIPolicyData
	{
	public:
		// Initiate member variables
		AIPolicyData();
		AIPolicyData(const AIPolicyData&);
		AIPolicyData& operator=(const AIPolicyData&);

		// Initiazlie DataConverter and call readData()
		void ReadData(char *buffer, std::size_t buffer_size);

		// Cleanup
		~AIPolicyData();

	private:
		// Start reading data from buffer
		void readData();
		// Initialize trigger_data
		void initTriggerData();
		// Read elements into trigger_data
		AITriggerData* readTriggerData();


		// 4 bytes: Delimiter? Must be less than or equal to 1
		unsigned signature;
		// 4 bytes: PolicyData ID
		unsigned policy_data_id;
		// 4 bytes: Number of trigger data objects in total
		std::size_t trigger_data_count;
		// Array of AITriggerData with length trigger_data_count
		std::vector<AITriggerData *> *trigger_data;
	};

}

#endif
