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

#ifndef _DataConv_H_
#define _DataConv_H_

#include <cstddef>
#include <cstring>

namespace PWTools
{

	class DataConverter
	{
	public:
		// Initialize variables
		static void Init(char *buffer, const std::size_t buffer_size);

		// Template function with checks to read different data types
		template <typename T>
		static void ReadT(T &dest);
		// Function with checks to read size number of bytes from src into dest
		static void ReadBytes(char *&dest, const std::size_t size);
		// Function for skipping some bytes
		static void ReadBytes(const std::size_t size);

		// getter
		static char* GetBuffer() { return ptr; }
		// getter to see how much data is left for reading
		static std::size_t GetBufferLeft() { return buffer_left; }

	private:
		// Hide contructor and destructor to prevent class instantiation
		DataConverter();
		~DataConverter();

		// Template function to read different data types
		template <typename T>
		static void readT(T &dest);
		// Function to read size number of bytes from src into dest
		static void readBytes(char *&dest, const std::size_t &size);

		// Throw out of range exception
		static void disintegrate();


		// Pointer for all reading operations
		static char *ptr;
		// To prevent reading out of range
		static std::size_t buffer_left;
	};
}

#endif
