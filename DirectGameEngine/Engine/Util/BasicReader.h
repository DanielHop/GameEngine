#pragma once

#include <fstream>
#include <filesystem>

class BasicReader
{
public:
	BasicReader();
	~BasicReader();

	std::vector<uint8_t> ReadData(std::string filename);
	uintmax_t FileSize(std::string filename);
};

