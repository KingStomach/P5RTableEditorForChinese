#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, char* argv[])
{
	std::ifstream in;
	in.open("character.txt", std::ios::in);
	if (!in.is_open())
	{
		std::cout << "character.txt" << " open failed." << std::endl;
		return 0;
	}

	std::map<uint16_t, std::string> char_map;

	while (!in.eof())
	{
		std::string word[2];
		uint16_t num;
		in >> word[0];
		in >> word[1];
		std::stringstream ss;
		ss << std::hex << word[1];
		ss >> num;
		char* t = reinterpret_cast<char*>(&num);
		std::swap(t[0], t[1]);
		char_map.emplace(std::make_pair(num, word[0]));
	}
	
	in.close();
	in.open("chatTitleName.ctd", std::ios::in | std::ios::binary);
	std::vector<std::string> chatNames;
	uint16_t buffer[32];
	in.seekg(48);
	while (!in.eof())
	{
		in.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
		std::string name;
		for (int i = 0; i < 32; i++)
		{
			if (buffer[i] == 0)
				continue;
			auto iter = char_map.find(buffer[i]);
			if (iter != char_map.end())
				name += char_map[buffer[i]];
			else
			{
				char* t = reinterpret_cast<char*>(buffer + i);
				name.push_back(t[0]);
				if (t[1]) name.push_back(t[1]);
			}
		}
		int tt = chatNames.size();
		chatNames.emplace_back(name);
	}

	std::ofstream out;
	out.open("out.txt", std::ios::out);
	for (auto& name : chatNames)
	{
		out << name << '\n';
	}
	out.close();
	return 0;
}