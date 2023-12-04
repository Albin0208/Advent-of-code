#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

// Split the numbers part on space into vector
std::vector<int> get_numbers (std::string const& numbers_part)
{
	std::vector<int> numbers;

	std::istringstream iss{ numbers_part };

	for (std::string number; std::getline(iss, number, ' ');)
	{
		if (std::isdigit(number[0]))
			numbers.push_back(std::stoi(number));
	}

	return numbers;
}

int main()
{
    std::ifstream file("input.txt");
    std::string line;

	int sum{};
    while (std::getline(file, line))
    {
        auto const separator_index{ line.find('|') };
		auto const card_separator{ line.find(':') };

        auto const numbers{ get_numbers(line.substr(separator_index + 1)) };

		int card_value{};
		for (auto const& number : get_numbers(line.substr(card_separator + 1, separator_index - card_separator - 1)))
			if (std::find(numbers.begin(), numbers.end(), number) != numbers.end())
				card_value == 0 ? card_value++ : card_value *= 2;

		sum += card_value;
	}

	std::cout << sum << '\n';

	return 0;
}
