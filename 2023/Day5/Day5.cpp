#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Range
{
    long long start;
    long long end;
};

struct RangePair
{
	Range des;
	Range source;

    RangePair(long long des_start, long long source_start, long long inc)
        : des{ des_start, des_start + inc - 1 },
        source{ source_start, source_start + inc - 1 }
    {}
};

int main()
{
    std::ifstream file("input.txt");
    std::stringstream buff;
    buff << file.rdbuf(); // Read the file
    file.close();

    std::istringstream iss(buff.str());
    std::string line;

    std::vector<long long> seeds;
    std::vector<std::vector<RangePair>> mappings;

    // Read the seeds part 1
    std::getline(iss, line);
    std::istringstream seed_input(line.substr(7));
    while (seed_input >> line)
    {
        seeds.push_back(std::stoll(line));
	}

    // Read other input
    while (std::getline(iss, line))
    {
        // Newline means new map
        if (line.empty())
        {
	        mappings.emplace_back();
			continue;
		}

        if (std::isdigit(line[0]))
        {
	        std::istringstream range_input(line);
            long long des_start, source_start, inc;

            range_input >> des_start >> source_start >> inc;

            mappings.back().emplace_back(des_start, source_start, inc);
        }
    }
    long long min{ INT64_MAX };
    // Iterate through the seeds and find foreach seed, find the mapping
    for (auto const seed : seeds)
    {
        auto next{ seed };
        for (auto const& soil : mappings)
        {
            for (auto const& pair : soil)
            {
                if (next >= pair.source.start && next <= pair.source.end)
                {
                    long long diff{ next - pair.source.start };
                    next = diff + pair.des.start;
                    break;
                }
            }
        }

        min = std::min(min, next);
	}

    std::cout << min << std::endl;
}
