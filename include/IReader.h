#pragma once
#include <array>
#include <fstream>
#include <type_traits>
#include <string>
#include <vector>
#include "Chat.h"
#include "CTD.h"

template <class IStream>
std::vector<std::string> readByWord(IStream&& stream)
{
	std::vector<std::string> res;
	for (std::string word; stream >> word;)
		res.emplace_back(word);
	return res;
}

template <class IStream, class Fn>
std::vector<typename std::invoke_result<Fn, std::string>::type> readByWord(IStream&& stream, Fn&& fn)
{
	decltype(readByWord(stream, fn)) res;
	std::string word;
	while (stream >> word)
		res.emplace_back(fn(word));
	return res;
}

template <class IStream>
std::vector<std::string> readByLine(IStream&& stream)
{
	std::vector<std::string> res;
	for (std::string line; std::getline(stream, line);)
		res.emplace_back(line);
	return res;
}

template <class IStream, class Fn>
std::vector<typename std::invoke_result<Fn, std::string>::type> readByLine(IStream&& stream, Fn&& fn)
{
	decltype(readByWord(stream, fn)) res;
	std::string line;
	for (std::string line; std::getline(stream, line);)
		res.emplace_back(fn(line));
	return res;
}

class ChatLibraryReader final
{
public:
	ChatLibraryReader() = delete;

	template <class IStream>
	static ChatLibrary read(IStream&& nameStream, IStream&& iconStream)
	{
		auto characters = readByLine(nameStream, [](const std::string& token)
			{
				uint16_t num;
				std::stringstream ss;
				auto pos = token.rfind('\t');
				ss << std::hex << token.substr(0, pos);
				ss >> num;
				uint32_t ch = 0;
				token.copy(reinterpret_cast<char*>(&ch), token.length() - pos, pos + 1);
				return std::make_pair(num, ch);
			});
		auto icons = readByLine(iconStream, [](const std::string& token)
			{
				uint16_t num;
				std::stringstream ss;
				auto pos = token.rfind('\t');
				ss << std::hex << token.substr(0, pos);
				ss >> num;
				return std::make_pair(static_cast<uint8_t>(num), token.substr(pos + 1));
			});

		return ChatLibrary(std::move(characters), std::move(icons));
	}
};

class CTDReader final
{
public:
	CTDReader() = delete;

	template <class IStream>
	static CTD read(IStream&& stream)
	{
		CTD::Head head;
		stream.read(reinterpret_cast<char*>(head.data()), head.size());

		uint32_t total_data_size = (head[36] << 24) + (head[37] << 16) + (head[38] << 8) + head[39];
		uint32_t total_num = (head[40] << 24) + (head[41] << 16) + (head[42] << 8) + head[43];

		std::vector<CTD::Data> datas;
		for (int i = 0; i < total_num; i++)
		{
			CTD::Data data(total_data_size / total_num, -1);
			if (!stream.read(reinterpret_cast<char*>(data.data()), total_data_size / total_num))
				break;
			datas.emplace_back(std::move(data));
		}

		int offset = (head[8] << 24) + (head[9] << 16) + (head[10] << 8) + head[11];
		stream.seekg(offset);
		CTD::End end;
		stream.read(reinterpret_cast<char*>(end.data()), end.size());

		return CTD(std::move(head), std::move(datas), std::move(end));
	}
};

class ChatReader
{
public:
	ChatReader() = delete;

	static std::vector<Chat> read(const CTD& nameTable, const CTD& iconTable, const ChatLibrary& library)
	{
		auto names = nameTable.decode(std::bind(&ChatLibrary::decodeName, &library, std::placeholders::_1));
		auto icons = iconTable.decode([](const auto& icon) -> uint8_t { return icon[1]; });

		std::vector<Chat> res;
		for (int i = 0; i < names.size(); i++)
		{
			res.emplace_back(Chat(std::move(names[i]), icons[i]));
		}
		return res;
	}
};