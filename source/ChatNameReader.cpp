#include "ChatNameReader.h"

ChatNameReader::ChatNameReader(const std::string& filename, std::map<uint16_t, std::string>&& characters)
	: IReader(filename, std::ios::in | std::ios::binary), m_characters(std::move(characters)) {}

void ChatNameReader::read()
{
	char buffer[64];
	getReader().seekg(48);
	while (!getReader().eof())
	{
		getReader().read(buffer, sizeof(buffer));
		std::string name;
		for (int i = 0; i < 64; i += 2)
		{
			if (buffer[i] == 0)
				break;
			uint16_t key = (static_cast<uint16_t>(buffer[i]) << 8) + static_cast<unsigned char>(buffer[i + 1]);
			auto iter = m_characters.find(key);
			if (iter != m_characters.end())
				name += iter->second;
			else
			{
				name.push_back(buffer[i]);
				if (buffer[i + 1]) name.push_back(buffer[i + 1]);
			}
		}
		m_data.emplace_back(std::move(name));
	}
}