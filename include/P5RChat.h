#pragma once
#include <string>

struct P5RChat
{
	std::string name;
	std::string icon;

	P5RChat(const std::string& name, const std::string& icon) : name(name), icon(icon) {}
	P5RChat(std::string&& name, std::string&& icon) : name(std::move(name)), icon(std::move(icon)) {}
};