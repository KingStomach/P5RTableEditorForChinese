#include "CharacterReader.h"
#include <sstream>

CharacterReader::CharacterReader(const std::string& filename)
	: IReader(filename, std::ios_base::in) {}

void CharacterReader::read()
{
	while (!getReader().eof())
	{
		std::string word[2];
		uint16_t num;
		getReader() >> word[0];
		getReader() >> word[1];
		std::stringstream ss;
		ss << std::hex << word[1];
		ss >> num;
		m_data.emplace(std::make_pair(num, word[0]));
	}
}