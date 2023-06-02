#pragma once
#include "P5RChat.h"
#include <string>
#include <vector>

class ChatLibrary final
{
public:
	ChatLibrary(std::vector<std::pair<uint16_t, std::string>>&& characters, std::vector<std::pair<uint16_t, std::string>>&& icons);

	P5RChat decode(const std::vector<uint8_t>& name, const std::vector<uint8_t>& icon) const;

//private:
	std::vector<std::pair<uint16_t, std::string>> m_characters;
	std::vector<std::pair<uint16_t, std::string>> m_icons;
};