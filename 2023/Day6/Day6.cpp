#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
	std::ifstream file("input.txt");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();

	std::istringstream iss(buffer.str());
	std::string line;

	std::vector<long long> in_table;
	iss >> line; // Read out the Time:
	std::string s;
	while (iss >> line)
	{
		// No digit continue to next
		if (!std::isdigit(line[0]))
		{
			in_table.push_back(std::stoll(s));
			s = "";
			continue;
		}
		s += line;
	}

	in_table.push_back(std::stoll(s));
	// in_table / 2 give time from 0 to mid and distance from mid to end

	int half_table_i = in_table.size() / 2 ;

	long long sum{1};
	for (int i{}; i < half_table_i; ++i)
	{
		long long const time = in_table[i];
		long long beat_num{};
		for (int j{1}; j < time; ++j) // start at 1 since 0 gives 0 distance no need to check last since it will also move 0
			if ((time - j) * j > in_table[half_table_i + i])
				beat_num++;

		sum *= beat_num;
	}

	std::cout << "Sum: " << sum << std::endl;
}
