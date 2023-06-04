#pragma once
#include <string>

struct Chat
{
	std::string name;
	int idxIcon;

	template <class T>
	Chat(T&& t, int idx) : name(std::forward<decltype(t)>(t)), idxIcon(idx) {}
};