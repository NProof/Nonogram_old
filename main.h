#include <bitset>
#include <array>
#include <vector>
#include <set>

struct compareBitset {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return (lhs^rhs).any();
	}
};

class Broad{
	std::bitset<625> white;
	std::bitset<625> block;
public :
	struct compare{
		bool operator()(const Broad& lhs, const Broad& rhs) const {
			return (lhs.white^rhs.white).any()||(lhs.block^rhs.block).any();
		}
	};
};

class Nonogram{
public :
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
		
	}
	
	std::set<Broad, Broad::compare> solve(){
		return std::set<Broad, Broad::compare>();
	}
};