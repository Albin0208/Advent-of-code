#include <fstream>
#include <iostream>
#include <map>
#include <queue>
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



	std::map<int, int> cards;

	int sum{};
	while (std::getline(file, line))
	{
		auto const separator_index{ line.find('|') };
		auto const card_separator{ line.find(':') };

		std::string s{line.substr(0, card_separator)};
		std::string card_num{ s.substr(s.find(' ')) };

		auto const numbers{ get_numbers(line.substr(separator_index + 1)) };

		int card_value{};
		int win_count{};
		for (auto const& number : get_numbers(line.substr(card_separator + 1, separator_index - card_separator - 1)))
			if (std::find(numbers.begin(), numbers.end(), number) != numbers.end())
			{
				card_value == 0 ? card_value++ : card_value *= 2;
				win_count++;
			}

		sum += card_value;
		cards.insert({ std::stoi(card_num), win_count });
	}

	std::cout << sum << '\n';

	std::queue<int> cards_to_process;

	for (auto const& card : cards)
	{
		cards_to_process.push(card.first);
	}

	int card_count{};

	while (!cards_to_process.empty())
	{
		card_count++;
		int current{ cards_to_process.front() };
		cards_to_process.pop();


		if (cards[current] == 0)
			continue;

		for (int i{}; i < cards[current]; ++i)
		{
			cards_to_process.push(current + i + 1);
		}
		
	}

	std::cout << card_count << '\n';

	return 0;
}
