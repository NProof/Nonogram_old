#include <iostream>
#include <algorithm>
#include <bitset>
#include <set>
#include <vector>

using namespace std;

struct BitsetCmp {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return lhs.to_ulong() > rhs.to_ulong();
	}
};

class Line{
public :
	std::vector<int> ns;
	std::bitset<25> each0;
	std::bitset<25> each1;
	std::set<std::bitset<25>, BitsetCmp> possibleSet;
	
	Line(int *, int);
	bool reducePossible(const std::bitset<25>, const std::bitset<25>, std::bitset<25> *, std::bitset<25> *);
	bool allPossible(std::bitset<25> &, std::bitset<25> &);
	std::set<std::bitset<25>, BitsetCmp> possible();
};