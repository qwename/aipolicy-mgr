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

#ifndef _AITD_H_
#define _AITD_H_


namespace PWTools
{

	class AITriggerData
	{
	public:
		// Initialize member variables
		AITriggerData();
		AITriggerData(const AITriggerData&);
		AITriggerData& operator=(const AITriggerData&);

		// Initiazlize DataConverter and call readData()
		void ReadData(char *buffer, std::size_t buffer_size);

		// Cleanup
		~AITriggerData();

	private:
		// Start reading data from buffer
		void readData();


		// 4 bytes: TriggerData Version
		unsigned trigger_data_version;
		// 4 bytes: TriggerData ID
		unsigned trigger_data_id;
		// 3 bytes: Flags
		// char *trigger_data_flags;
		char trigger_data_IsActive;
		char trigger_data_IsRun;
		char trigger_data_OnlyAttackValid;
		// 128 bytes: Name?
		char *trigger_data_name;

	};

}

#endif
