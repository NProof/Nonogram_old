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
	std::array<std::set<std::bitset<25>, compareBitset>, 25> *possibleSetArrayOfRow;
	std::array<std::set<std::bitset<25>, compareBitset>, 25> *possibleSetArrayOfCol;
public :
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
		
	}
	
	std::set<Broad, Broad::compare> solve(){
		return std::set<Broad, Broad::compare>();
	}
	
	std::set<std::bitset<25>, compareBitset> possible(std::vector<int> ns){
		std::set<std::bitset<25>, compareBitset> resultSet;
		int n = ns.size();
		if(n==0)
			return resultSet;
		int sum = 0;
		for(int i=0; i<n; i++)
		sum += ns[i];
		int n0 = 25-sum+1;
		for(int i=0; i<(1<<n0); i++){
			std::bitset<25> bitCombition(i);
			if(bitCombition.count()==n){
				int comb = 0;
				int j=0;
				while(!bitCombition[j++])
					comb++;
				int addBlock[n]{comb}, indexAB = 0;
				comb += ns[indexAB++]+1;
				for(; j<n0; j++){
					if(bitCombition[j]){
						addBlock[indexAB] = comb;
						comb += ns[indexAB]+1;
						indexAB++;
					}
					else comb++;
				}
				bitCombition.reset();
				for(j=0; j<n; j++){
					bitCombition |= ((1<<ns[j])-1)<<(25-addBlock[j]-ns[j]);
				}
				resultSet.insert(bitCombition);
			}
		}
		return resultSet;
	}
};