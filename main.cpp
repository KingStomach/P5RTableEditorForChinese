#include "CharacterReader.h"
#include "ChatNameReader.h"
#include "ChatIconReader.h"
#include <string>

const std::string character_path("character.txt");
const std::string chat_titleName_table("chatTitleName.ctd");
const std::string chat_data_table("chatDataTable.ctd");

int main(int argc, char* argv[])
{
	CharacterReader character_reader(character_path);
	character_reader.read();

	ChatNameReader chat_name_reader(chat_titleName_table, std::move(character_reader).getData());
	chat_name_reader.read();
	auto chatNames = std::move(chat_name_reader).getData();

	ChatIconReader icon_reader(chat_data_table);
	icon_reader.read();
	auto chat_icons = std::move(icon_reader).getData();

	std::ofstream out;
	out.open("icon.txt", std::ios::out);
	for (auto& icon : chat_icons)
	{
		out << std::to_string(icon) << '\n';
	}
	out.close();
	return 0;
}