#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main()
{
	std::ifstream file("input.txt");

	int constexpr red_num{ 12 };
	int constexpr green_num{ 13 };
	int constexpr blue_num{ 14 };


	std::regex const regex{R"((Game \d+)|(\d+ \w+))"};

	std::string input;
	int sum{ 0 };
	int power{ 0 };
	while (std::getline(file, input))
	{
		int max_red{ 0 };
		int max_green{ 0 };
		int max_blue{ 0 };

		bool impossible{ false };
		int game_num{ 0 };

		for (auto it = std::sregex_iterator(input.begin(), input.end(), regex); it != std::sregex_iterator(); ++it)
		{
			if (it->str().find("Game") != std::string::npos)
			{
				game_num = std::stoi(it->str().substr(5));
			}
			else
			{
				std::string const& str = it->str();
				int const num = std::stoi(str.substr(0, str.find(' ')));
				std::string const& color = str.substr(str.find(' ') + 1);

				if (color == "red" && num > red_num ||
					color == "green" && num > green_num ||
					color == "blue" && num > blue_num)
				{
					impossible = true;
					//break; // Efficiency for part 1
				}

				if (color == "red" && num > max_red)
					max_red = num;
				else if (color == "green" && num > max_green)
					max_green = num;
				else if (color == "blue" && num > max_blue)
					max_blue = num;
			}
		}

		power += max_red * max_green * max_blue;

		if (!impossible)
		{
			sum += game_num;
		}
	}

	std::cout << "Sum: " << sum << std::endl;
	std::cout << "Power: " << power << std::endl;


	file.close();
}
