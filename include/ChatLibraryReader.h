#pragma once
#include "ChatLibrary.h"
#include "IReader.h"
#include <fstream>
#include <vector>

class CharacterReader final : public IStreamStrReader<CharacterReader>
{
public:
	CharacterReader(const std::string& filename);
	~CharacterReader() = default;

private:
	std::vector<std::pair<uint16_t, std::string>> initDataImpl() const;
	void handleTokenImpl(const std::string& token, std::vector<std::pair<uint16_t, std::string>>& data) const;

	friend class IStreamStrReader<CharacterReader>;
};


class ChatLibraryReader final : public IReader<ChatLibraryReader>
{
public:
	ChatLibraryReader(const std::string& chat_path, const std::string& icon_path);
	~ChatLibraryReader() = default;

private:
	ChatLibrary readImpl();

	CharacterReader m_chat_reader;
	CharacterReader m_icon_reader;

	friend class IReader<ChatLibraryReader>;
};