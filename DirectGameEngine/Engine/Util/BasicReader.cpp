#include "BasicReader.h"

BasicReader::BasicReader()
{
}


BasicReader::~BasicReader()
{
}

std::vector<uint8_t> BasicReader::ReadData(std::string filename)
{
	std::vector<uint8_t> data;

	std::ifstream fs;
	fs.open(filename, std::ifstream::in | std::ifstream::binary);
	if (fs.good())
	{
		auto size = FileSize(filename);
		// TODO: check here if size is more than size_t
		data.resize(static_cast<size_t>(size));
		fs.seekg(0, std::ios::beg);
		fs.read(reinterpret_cast<char*>(&data[0]), size);
		fs.close();
	}
	return data;
}

uintmax_t BasicReader::FileSize(std::string filename)
{
	std::tr2::sys::path p(filename);
	if (std::tr2::sys::exists(p) && std::tr2::sys::is_regular_file(p))
		return std::tr2::sys::file_size(p);
	return 0;
}