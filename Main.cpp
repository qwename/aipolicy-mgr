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

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include "AIPolicyDataManager.h"

int main(int argc, char *argv[])
{
	using std::string;
	using std::ifstream;

	// Speed up?
	std::ios::sync_with_stdio(false);

	// Declare variables
	string path = "";
	char *buffer = 0;
	std::size_t buffer_size = 0;
	PWTools::AIPolicyDataManager *a = nullptr;
	std::ifstream in;

	for (int i = 1; i < argc; ++i)
    {

    path = argv[i];
	in.open(path, std::ifstream::binary | std::ifstream::ate);

	if (in.is_open())
	{
		buffer_size = in.tellg();
		if (buffer_size)
		{
			buffer = new char[buffer_size];
			in.seekg(in.beg).read(buffer, buffer_size);
			buffer_size = in.gcount();
		}
		std::cout << "File size: " << buffer_size << " bytes\n";
	}
	else
		std::cerr << "Failed to open file for reading.";
	in.close();

	if (buffer_size)
	{
		(a = new PWTools::AIPolicyDataManager())->ReadData(buffer, buffer_size);
		std::cout << *a->GetInfo();
	}

	if (buffer)
		delete [] buffer;
	if (a)
		delete a;
    buffer_size = 0;

    }
	std::cin.get();
	return 0;
}
