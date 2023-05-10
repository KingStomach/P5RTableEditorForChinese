#pragma once
#include "IReader.h"
#include <vector>

class ChatIconReader : public IReader
{
public:
	ChatIconReader(const std::string& filename);
	~ChatIconReader() = default;

	void read() override;
	auto& getData()& { return m_data; }
	auto getData()&& { return std::move(m_data); }
private:
	std::vector<char> m_data;
};