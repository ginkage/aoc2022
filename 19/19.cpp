#include <iostream>
#include <cstring>
#include <regex>
#include <unordered_map>

using namespace std;

struct blueprint {
	int id;
	int ore_ore;
	int clay_ore;
	int obs_ore;
	int obs_clay;
	int geo_ore;
	int geo_obs;
};

struct state {
	int time;
	int ore;
	int clay;
	int obs;
	int geo;
	int ore_rate;
	int clay_rate;
	int obs_rate;
	int geo_rate;
};

static uint32_t crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

template <> class std::hash<state>
{
public:
    size_t operator()(const state& st) const
    {
		int n = sizeof(state);
		char *s = (char *)&st;
		unsigned long crc = ~0L;
		for (int i = 0; i < n; i++) {
			int tbl_idx = crc ^ (s[i] >> (0 * 4));
			crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);
			tbl_idx = crc ^ (s[i] >> (1 * 4));
			crc = crc_table[tbl_idx & 0x0f] ^ (crc >> 4);
		}
		return ~crc;
    }
};

bool operator ==(const state &s1, const state &s2) {
	return (memcmp(&s1, &s2, sizeof(state)) == 0);
}

unordered_map<state, int> memo;

int dfs(int best, state s, const blueprint &b) {
	auto it = memo.find(s);
	if (it != memo.end())
		return it->second;

	state s0 = s;
	s.time++;
	s.ore += s.ore_rate;
	s.clay += s.clay_rate;
	s.obs += s.obs_rate;
	s.geo += s.geo_rate;

	if (s.time < 24) {
		best = max(best, dfs(best, s, b));

		if (s0.ore >= b.ore_ore) {
			state s1 = s;
			s1.ore -= b.ore_ore;
			s1.ore_rate++;
			best = max(best, dfs(best, s1, b));
		}

		if (s0.ore >= b.clay_ore) {
			state s1 = s;
			s1.ore -= b.clay_ore;
			s1.clay_rate++;
			best = max(best, dfs(best, s1, b));
		}

		if (s0.ore >= b.obs_ore && s0.clay >= b.obs_clay) {
			state s1 = s;
			s1.ore -= b.obs_ore;
			s1.clay -= b.obs_clay;
			s1.obs_rate++;
			best = max(best, dfs(best, s1, b));
		}

		if (s0.ore >= b.geo_ore && s0.obs >= b.geo_obs) {
			state s1 = s;
			s1.ore -= b.geo_ore;
			s1.obs -= b.geo_obs;
			s1.geo_rate++;
			best = max(best, dfs(best, s1, b));
		}
	}
	else
		best = max(best, s.geo);

	memo[s0] = best;
	return best;
}

int main() {
	vector<blueprint> blues;
	while (cin) {
		string s;
		getline(cin, s);
		smatch match;
		const regex rex("Blueprint (.*): Each ore robot costs (.*) ore. Each clay robot costs (.*) ore. Each obsidian robot costs (.*) ore and (.*) clay. Each geode robot costs (.*) ore and (.*) obsidian.");
		if (regex_match(s, match, rex) && match.size() == 8) {
			blueprint b;
			b.id = stoi(match[1].str());
			b.ore_ore = stoi(match[2].str());
			b.clay_ore = stoi(match[3].str());
			b.obs_ore = stoi(match[4].str());
			b.obs_clay = stoi(match[5].str());
			b.geo_ore = stoi(match[6].str());
			b.geo_obs = stoi(match[7].str());
			blues.push_back(b);
		}
	}

	long result = 0;
	for (const blueprint &b : blues) {
		state s;
		memset(&s, 0, sizeof(s));
		s.ore_rate = 1;

		int best = dfs(0, s, b);
		cout << best << endl;

		result += best * b.id;

		unordered_map<state, int> tmp;
		swap(memo, tmp);
	}

	cout << result << endl;

	return 0;
}

