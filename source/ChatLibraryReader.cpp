#include "ChatLibraryReader.h"
#include <algorithm>
#include <sstream>

CharacterReader::CharacterReader(const std::string& filename)
	: IStreamStrReader<CharacterReader>(filename) {}

std::vector<std::pair<uint16_t, std::string>> CharacterReader::initDataImpl() const
{
	return std::vector<std::pair<uint16_t, std::string>>();
}

void CharacterReader::handleTokenImpl(const std::string& token, std::vector<std::pair<uint16_t, std::string>>& data) const
{
	uint16_t num;
	std::stringstream ss;
	auto pos = token.rfind('\t');
	ss << std::hex << token.substr(0, pos);
	ss >> num;
	data.emplace_back(std::make_pair(num, token.substr(pos + 1)));
}

ChatLibraryReader::ChatLibraryReader(const std::string& chat_path, const std::string& icon_path)
	: m_chat_reader(chat_path), m_icon_reader(icon_path) {}

ChatLibrary ChatLibraryReader::readImpl()
{
	auto characters = m_chat_reader.readData();
	auto icons = m_icon_reader.readData();
	std::sort(characters.begin(), characters.end(),
		[](const auto& zPair1, const auto& zPair2) { return zPair1.first < zPair2.first; });
	std::sort(icons.begin(), icons.end(),
		[](const auto& zPair1, const auto& zPair2) { return zPair1.first < zPair2.first; });
	ChatLibrary library(std::move(characters), std::move(icons));
	return library;
}