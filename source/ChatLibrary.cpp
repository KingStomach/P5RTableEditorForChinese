#pragma once
#include "ChatLibrary.h"
#include <format>

void ChatLibrary::mode(bool bEncode)
{
	if (bEncode)
	{
		std::sort(m_characters.begin(), m_characters.end(), [](const auto& zPair1, const auto& zPair2) { return zPair1.second < zPair2.second; });
		std::sort(m_icons.begin(), m_icons.end(), [](const auto& zPair1, const auto& zPair2) { return zPair1.second < zPair2.second; });
	}
	else
	{
		std::sort(m_characters.begin(), m_characters.end(), [](const auto& zPair1, const auto& zPair2) { return zPair1.first < zPair2.first; });
		std::sort(m_icons.begin(), m_icons.end(), [](const auto& zPair1, const auto& zPair2) { return zPair1.first < zPair2.first; });
	}
}

std::string ChatLibrary::decodeName(const std::vector<uint8_t>& encode_name) const
{
	std::string decode_name;
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
			{
				for (int i = 3; i >= 0; i--)
				{
					uint8_t ch = iter->second >> (i * 8);
					if (!ch) continue;
					decode_name.push_back(ch);
				}
			}
			else
				decode_name += std::format("{:x}", key);
		}
	}
	return decode_name;
}

std::string ChatLibrary::decodeIcon(uint8_t idxIcon) const
{
	auto iter = std::lower_bound(m_icons.cbegin(), m_icons.cend(), idxIcon,
		[](const auto& zPair, auto key) { return zPair.first < key; });
	return iter != m_icons.end() && iter->first == idxIcon ? iter->second : std::string();
}

std::vector<uint8_t> ChatLibrary::encodeName(const std::string& name) const
{
	std::vector<uint8_t> res;
	for (auto iter = name.begin(); iter != name.end(); iter++)
	{
		if (isascii(*iter))
			res.emplace_back(*iter);
		else if (iter + 1 == name.end())
			break;
		else
		{
			uint16_t key = (static_cast<uint16_t>(*iter) << 8) + static_cast<unsigned char>(*(iter + 1));
			auto iter = std::lower_bound(m_characters.cbegin(), m_characters.cend(), key,
				[](const auto& zPair, auto key) { return zPair.second < key; });
			if (iter != m_characters.end() && iter->second == key)
			{
				res.emplace_back(iter->first >> 8);
				res.emplace_back(iter->first);
			}
		}
	}
	return res;
}