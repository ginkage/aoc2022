#include <iostream>
#include <cstring>
#include <regex>
#include <unordered_map>

using namespace std;

struct blueprint {
	int8_t id;
	uint8_t ore_ore;
	uint8_t clay_ore;
	uint8_t obs_ore;
	uint8_t obs_clay;
	uint8_t geo_ore;
	uint8_t geo_obs;
	uint8_t more;
};

struct state {
	int8_t time;
	uint16_t ore;
	uint16_t clay;
	uint16_t obs;
	uint16_t geo;
	uint8_t ore_rate;
	uint8_t clay_rate;
	uint8_t obs_rate;
	uint8_t geo_rate;
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

uint16_t dfs(uint16_t best, state s, const blueprint &b) {
	auto it = memo.find(s);
	if (it != memo.end())
		return it->second;

	state s0 = s;
	s.time++;
	s.ore += s.ore_rate;
	s.clay += s.clay_rate;
	s.obs += s.obs_rate;
	s.geo += s.geo_rate;

	if (s.time < 32) {
		bool build = false, save = false;

		if (s0.ore >= b.geo_ore && s0.obs >= b.geo_obs) {
			state s1 = s;
			s1.ore -= b.geo_ore;
			s1.obs -= b.geo_obs;
			s1.geo_rate++;
			best = max(best, dfs(best, s1, b));
			build = true;
		}
		else if (s.obs_rate > 0) save = true;

		if (s0.obs_rate < b.geo_obs) {
			if (s0.ore >= b.obs_ore && s0.clay >= b.obs_clay) {
				state s1 = s;
				s1.ore -= b.obs_ore;
				s1.clay -= b.obs_clay;
				s1.obs_rate++;
				best = max(best, dfs(best, s1, b));
				build = true;
			}
			else if (s.clay_rate > 0) save = true;
		}

		if (s0.clay_rate < b.obs_clay) {
			if (s0.ore >= b.clay_ore) {
				state s1 = s;
				s1.ore -= b.clay_ore;
				s1.clay_rate++;
				best = max(best, dfs(best, s1, b));
				build = true;
			}
			else save = true;
		}

		if (s0.ore_rate < b.more) {
			if (s0.ore >= b.ore_ore) {
				state s1 = s;
				s1.ore -= b.ore_ore;
				s1.ore_rate++;
				best = max(best, dfs(best, s1, b));
				build = true;
			}
			else save = true;
		}

		if (!build || save)
			best = max(best, dfs(best, s, b));
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
			b.more = max(max(b.ore_ore, b.clay_ore), max(b.obs_ore, b.geo_ore));
			blues.push_back(b);
		}
	}

	int idx = 0;
	long result = 1;
	for (const blueprint &b : blues) {
		state s;
		memset(&s, 0, sizeof(s));
		s.ore_rate = 1;

		int best = dfs(0, s, b);
		cout << best << endl;

		result *= best;

		unordered_map<state, int> tmp;
		swap(memo, tmp);

		if (++idx == 3) break;
	}

	cout << result << endl;

	return 0;
}

