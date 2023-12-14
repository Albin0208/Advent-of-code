#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

int main()
{
    std::ifstream file("input.txt");
    std::stringstream buffer;
    file >> buffer.rdbuf();

    std::istringstream iss(buffer.str());

    std::string direction;

    std::string const start{"AAA"};
    std::string const end{"ZZZ"};

    iss >> direction;

    std::unordered_map<std::string, std::pair<std::string, std::string>> dir_map;

    while (iss)
    {
	    std::string line;
		std::getline(iss, line);
        std::istringstream ss(line);

        std::string key;
        ss >> key;

        while (ss)
        {
	        std::string word;
			ss >> word;

            if (word[0] == '(')
            {
                std::string pair1{ word.substr(1, word.length() - 2)}; // remove the parenthesis and , from the string
				
                ss >> word;
                std::string pair2{ word.substr(0, word.length() - 1) }; // remove the parenthesis

                dir_map[key] = { pair1, pair2 };
			}
		}

	}

    int count{};
    int dir_pointer{};

    std::string next{ start };
    while (next != end)
    {
	    auto [left, right] = dir_map[next];

        // Reset dir pointer if we have reached the end of the direction string
        if (dir_pointer == direction.length())
			dir_pointer = 0;

	    if (char dir{ direction[dir_pointer++] }; dir == 'L')
			next = left;
		else
			next = right;

		++count;
    }

    std::cout << "Part 1: " << count << '\n';
}
