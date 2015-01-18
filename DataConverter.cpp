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

#include <stdexcept>
#include "DataConverter.h"

namespace PWTools
{

	// Explicitly define static member variables
	char *DataConverter::ptr = 0;
	std::size_t DataConverter::buffer_left = 0;

	// Public Functions

	void DataConverter::Init(char *buffer, const std::size_t buffer_size)
	{
		ptr = buffer;
		buffer_left = buffer_size;
	}

	template <class T>
	void DataConverter::ReadT(T &dest)
	{
		if (buffer_left >= sizeof(T))
		{
			buffer_left -= sizeof(T);
			return readT(dest);
		}
		disintegrate();
	}

	// Declare these functions so that there is no need to define template function in header
	template void DataConverter::ReadT(char &dest);
	template void DataConverter::ReadT(int &dest);
	template void DataConverter::ReadT(std::size_t &dest);

	void DataConverter::ReadBytes(char *&dest, std::size_t size)
	{
		if (buffer_left >= size)
		{
			buffer_left -= size;
			return readBytes(dest, size);
		}
		disintegrate();
	}

	void DataConverter::ReadBytes(std::size_t size)
	{
		if (buffer_left >= size)
		{
			buffer_left -= size;
			ptr += size;
		}
		else
			disintegrate();
	}

	// Private Functions

	DataConverter::DataConverter()
	{
	}

	DataConverter::~DataConverter()
	{
	}

	template <typename T>
	void DataConverter::readT(T &dest)
	{
		memcpy((void *)&dest, (ptr += sizeof(T)) - sizeof(T), sizeof(T));
	}

	void DataConverter::readBytes(char *&dest, const std::size_t &size)
	{
		memcpy(dest, (ptr += size) - size, size);
	}

	void DataConverter::disintegrate()
	{
		throw std::out_of_range("Unexpected end of file reached, unable to continue");
	}

}
