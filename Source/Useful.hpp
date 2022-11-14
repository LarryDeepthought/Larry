#pragma once

#include "json.hpp"

#include <vector>
#include <string>
#include <iostream>


void print_string_vector(std::vector<std::string> vec)
{
	for (std::string s : vec)
	{
		std::cout << s << std::endl;
	}
}

std::string get_json_value(nlohmann::json j)
{
	std::string s = j.dump();
	return s.substr(1, s.length() - 2);
}