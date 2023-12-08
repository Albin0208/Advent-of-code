#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
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

long long find_min_location(long long const seed, std::vector<std::vector<RangePair>> const& mappings)
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

	return next;
}

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
    mappings.reserve(7);

    // Read the seeds part 1
    std::getline(iss, line);
    std::istringstream seed_input(line.substr(7));
    while (seed_input >> line)
    {
        seeds.push_back(std::stoll(line));
  //      long long seed_start{ std::stoll(line) };

  //      seed_input >> line;
  //      long long seed_end{ std::stoll(line) + seed_start };

		//Range seed{ seed_start, seed_end };
		//seeds.push_back(seed);

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

    //int numThreads = std::thread::hardware_concurrency();

    //while (seeds.size() < numThreads)
    //{

    //}


    //long long min{ INT64_MAX };

    std::vector<long long> mins;
    mins.reserve(seeds.size());
    // Iterate through the seeds and find foreach seed, find the mapping

    for (auto const& seed : seeds)
    {
	    mins.push_back(find_min_location(seed, mappings));
    }


    std::cout << *std::min_element(mins.begin(), mins.end()) << '\n';
}
