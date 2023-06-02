#pragma once
#include "ChatLibrary.h"
#include <format>

ChatLibrary::ChatLibrary(std::vector<std::pair<uint16_t, std::string>>&& characters, std::vector<std::pair<uint16_t, std::string>>&& icons)
	//: m_characters(characters), m_icons(icons) {}
	: m_characters(std::move(characters)), m_icons(std::move(icons)) {}

P5RChat ChatLibrary::decode(const std::vector<uint8_t>& encode_name, const std::vector<uint8_t>& encode_icon) const
{
	std::string decode_name;
	std::string decode_icon;

	int i = 0;
	while (i < encode_name.size())
	{
		if (encode_name[i] == 0)
			break;
		if (isascii(encode_name[i]))
			decode_name += encode_name[i++];
		else
		{
			uint16_t key = (static_cast<uint16_t>(encode_name[i]) << 8) + static_cast<unsigned char>(encode_name[i + 1]);
			i += 2;
			auto iter = std::lower_bound(m_characters.cbegin(), m_characters.cend(), key,
				[](const auto& zPair, auto key) { return zPair.first < key; });
			if (iter != m_characters.end() && iter->first == key)
				decode_name += iter->second;
			else
				decode_name += std::format("{:x}", key);
		}
	}

	auto iter = std::lower_bound(m_icons.cbegin(), m_icons.cend(), encode_icon[1],
		[](const auto& zPair, auto key) { return zPair.first < key; });
	decode_icon += iter->second;

	return P5RChat(std::move(decode_name), std::move(decode_icon));
}