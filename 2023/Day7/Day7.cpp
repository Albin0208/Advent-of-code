#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

std::unordered_map<char, int> count_suit(std::string const& first)
{
	std::unordered_map<char, int> suit_count;
	for (char c : first)
	{
		suit_count[c]++;
	}
	return suit_count;
}

int get_hand(std::string const& first)
{
	std::unordered_map<char, int> suit_count{ count_suit(first) };

	std::unordered_map<int, int> count_count;

	for (auto const& [suit, count] : suit_count)
	{
		count_count[count]++;
	}

	if (count_count[5] == 1)
		return 7;

	if (count_count[4] == 1)
		return 6;

	if (count_count[3] == 1 && count_count[2] == 1)
		return 5;

	if (count_count[3] == 1)
		return 4;

	if (count_count[2] == 2)
		return 3;

	if (count_count[2] == 1)
		return 2;

	return 1;
}

int main()
{
	std::ifstream file("input.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::istringstream iss{ buffer.str() };

	std::unordered_map<std::string, int> const map{
		{"A", 14},
		{"K", 13},
		{"Q", 12},
		{"J", 11},
		{"T", 10}
	};

	std::string line;

	std::vector<std::pair<std::string, int>> cards;

	while (iss >> line)
	{
		std::string card{ line };
		iss >> line;
		int bet{ std::stoi(line)};

		cards.emplace_back(card, bet);
	}

	std::ranges::sort(cards.begin(), cards.end(), [&map](auto const& lhs, auto const& rhs)
	{
		int c1{ get_hand(lhs.first) };
		int c2{ get_hand(rhs.first) };

		// if same rank check each card
		if (c1 == c2)
		{
			for (int i{ }; i < lhs.first.length(); ++i)
			{
				std::string const a { lhs.first[i] };
				std::string const b { rhs.first[i] };

				if (a == b)
					continue;

				auto search = map.find(a);
				int l = search != map.end() ? search->second : std::stoi(a);

				search = map.find(b);
				int r = search != map.end() ? search->second : std::stoi(b);

				return l < r;
			}
		}

		return c1 < c2;
	});

	int rank{ 1 };
	int sum{};
	for (auto const& card : cards)
	{
		sum += card.second * rank++;
	}

	std::cout << sum << '\n';
}
