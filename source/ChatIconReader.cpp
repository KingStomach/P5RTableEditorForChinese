#pragma once
#include "ChatIconReader.h"

ChatIconReader::ChatIconReader(const std::string& filename)
	: IReader(filename, std::ios::in | std::ios::binary) {}

void ChatIconReader::read()
{
	char buffer[2];
	getReader().seekg(48);
	while (!getReader().eof())
	{
		//getReader() >> buffer;
		getReader().read(buffer, sizeof(buffer));
		m_data.emplace_back(buffer[1]);
	}
}