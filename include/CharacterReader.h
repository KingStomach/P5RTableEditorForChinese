#pragma once
#include "IReader.h"
#include <map>

class CharacterReader : public IReader
{
public:
	CharacterReader(const std::string& filename);
	~CharacterReader() = default;

	void read() override;
	auto& getData()& { return m_data; }
	auto getData()&& { return std::move(m_data); }
private:
	std::map<uint16_t, std::string> m_data;
};