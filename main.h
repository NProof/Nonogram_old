// #include <iostream>
// #include <cstdio>
#include <bitset>
#include <array>
#include <stack>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct compareBitset {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return lhs.to_ulong() > rhs.to_ulong();
	}
};

class Nonogram{
public :
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
		
	}
};

class Broad{
public :
};
