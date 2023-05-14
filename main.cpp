#include "ChatLibraryReader.h"
#include "ChatReader.h"

const std::string character_path("character.txt");
const std::string icon_path("icon.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");


int main(int argc, char* argv[])
{
	auto library = ChatLibraryReader(character_path, icon_path).readData();
	auto chats = ChatReader(chat_titleName_table, chat_data_table, library).readData();
	std::ofstream out;
	out.open("out.txt", std::ios::out);
	for (auto& chat : chats)
	{
		out << chat.name << '\t' << chat.icon << '\n';
	}
	out.close();
	return 0;
}