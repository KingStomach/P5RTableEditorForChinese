#pragma once
#include <string>
#include <vector>

class ChatLibrary final
{
public:
	template <class T1, class T2>
	ChatLibrary(T1&& characters, T2&& icons) : m_characters(std::forward<decltype(characters)>(characters)),
		m_icons(std::forward<decltype(icons)>(icons)) {}

	void mode(bool bEncode);

	std::string decodeName(const std::vector<uint8_t>& encode_name) const;
	std::string decodeIcon(uint8_t idxIcon) const;

	std::vector<uint8_t> encodeName(const std::string& name) const;

	const std::vector<std::pair<uint8_t, std::string>>& getIconList() const { return m_icons; }

private:
	std::vector<std::pair<uint16_t, uint32_t>> m_characters;
	std::vector<std::pair<uint8_t, std::string>> m_icons;
};