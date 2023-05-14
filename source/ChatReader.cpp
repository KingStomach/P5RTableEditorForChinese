#include "ChatReader.h"

ChatReader::ChatReader(const std::string& name_path, const std::string icon_path, const ChatLibrary& library)
	: m_name_reader(name_path), m_icon_reader(icon_path), m_library(library) {}

std::vector<P5RChat> ChatReader::readImpl()
{
	auto names = m_name_reader.readData();
	auto icons = m_icon_reader.readData();
	std::vector<P5RChat> data;
	size_t size = std::min(names.size(), icons.size());
	for (size_t i = 0; i < size; i++)
	{
		data.emplace_back(m_library.decode(names[i], icons[i]));
	}
	return data;
}