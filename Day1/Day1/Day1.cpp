#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> const words_to_numbers{
	{"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
	{"8", 8}, {"9", 9}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
	{"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
};

int find_match(std::string const& word)
{
	for (auto const& pair : words_to_numbers)
		if (word.find(pair.first) != std::string::npos)
			return pair.second;

	return 0;
}

int main()
{
	std::ifstream file("input.txt");
	std::string input;
	int sum{};

	while (file >> input)
	{
		int first{};
		int last{};

		for (size_t i{}; i <= input.size(); ++i)
		{
			if (first == 0) 
				first = find_match(input.substr(0, i));
			if (last == 0) 
				last = find_match(input.substr(input.size() - i, i));

			if (first > 0 && last > 0)
				break;
		}

		sum += first * 10 + last;
	}

	std::cout << "Sum: " << sum << std::endl;

	file.close();
}
