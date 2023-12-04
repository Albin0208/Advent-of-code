#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

int main()
{
	std::ifstream file("input.txt");
	std::string line;

	std::vector<std::string> points;

	while (file >> line)
	{
		points.push_back(line);
	}

	std::set<std::pair<int, int>> number_start;
	for (int y{}; y < points.size(); ++y)
	{
		auto const& curr_line = points[y];
		for (int x{}; x < curr_line.size(); ++x)
		{
			if (std::isdigit(curr_line[x]) || curr_line[x] == '.')
				continue;

			for (int i : {y - 1, y, y + 1})
				for (int j : {x - 1, x, x + 1})
				{
					if (i < 0 || i >= points.size() || j < 0 || j >= curr_line.size() || !std::isdigit(points[i][j]))
						continue;

					while (j > 0 && std::isdigit(points[i][j - 1]))
						--j;

					number_start.emplace(j, i);
				}
		}
	}

	// Part 1
	int sum{};
	for (auto const& p : number_start)
	{
		std::string number_string;
		auto const& curr_line = points[p.second];
		int x = p.first;
		while (x < curr_line.size() && std::isdigit(curr_line[x]))
		{
			number_string += curr_line[x];
			x++;
		}
		sum += std::stoi(number_string);
	}
	std::cout << "Sum: " << sum << std::endl;

	sum = 0;

	// Part 2, find all * where 2 numbers are adjacent
	for (int y{}; y < points.size(); ++y)
	{
		auto const& curr_line = points[y];
		for (int x{}; x < curr_line.size(); ++x)
		{
			// Skip none gears
			if (curr_line[x] != '*')
				continue;

			number_start.clear();

			// If gear check if two numbers are adjacent to it
			for (int i : {y - 1, y, y + 1})
				for (int j : {x - 1, x, x + 1})
				{
					if (i < 0 || i >= points.size() || j < 0 || j >= curr_line.size() || !std::isdigit(points[i][j]))
						continue;

					while (j > 0 && std::isdigit(points[i][j - 1]))
						--j;

					number_start.emplace(j, i);
				}

			if (number_start.size() > 1)
			{
				int s{1};
				for (auto const& p : number_start)
				{
					std::string number_string;
					auto const& curr_line = points[p.second];
					int x = p.first;
					while (x < curr_line.size() && std::isdigit(curr_line[x]))
					{
						number_string += curr_line[x];
						x++;
					}
					s *= std::stoi(number_string);
				}

				sum += s;
			}
		}
	}

	std::cout << "Sum: " << sum << std::endl;
}