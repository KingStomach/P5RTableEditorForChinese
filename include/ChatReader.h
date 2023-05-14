#pragma once
#include "ChatLibrary.h"
#include "CTDReader.h"

class ChatReader final : public IReader<ChatReader>
{
public:
	ChatReader(const std::string& name_path, const std::string icon_path, const ChatLibrary& library);
	~ChatReader() = default;

private:
	CTDReader m_name_reader;
	CTDReader m_icon_reader;
	const ChatLibrary& m_library;

	std::vector<P5RChat> readImpl();

	friend class IReader<ChatReader>;
};