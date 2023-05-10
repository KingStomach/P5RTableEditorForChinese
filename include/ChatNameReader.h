#pragma once
#include "IReader.h"
#include <map>
#include <vector>

class ChatNameReader : public IReader
{
public:
	ChatNameReader(const std::string& filename, std::map<uint16_t, std::string>&& characters);
	~ChatNameReader() = default;

	void read() override;
	auto& getData()& { return m_data; }
	auto getData()&& { return std::move(m_data); }
private:
	std::map<uint16_t, std::string> m_characters;
	std::vector<std::string> m_data;
};