// #include <iostream>
// #include <cstdio>
#include <bitset>
#include <array>
#include <vector>
#include <set>

struct compareBitset {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return lhs.to_ulong() > rhs.to_ulong();
	}
};

class Broad{
public :
	struct compare{
		bool operator()(const Broad& lhs, const Broad& rhs) const {
			return (lhs.white^rhs.white).any()||(lhs.block^rhs.block).any();
		}
	};
	
	std::bitset<625> white;
	std::bitset<625> block;
	
	Broad(){
		white.flip();
	}
	
	char unitspace(bool white, bool block) const {
		if(white&&!block){
			return '.' ;
		}
		else if(!white&&!block){
			return '0' ;
		}
		else if(block&&white){
			return '1' ;
		}
		else{
			return '%' ;
		}
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Broad& broad);
};

std::ostream& operator<<(std::ostream& os, const Broad& broad) {  
    os << " white : " << &broad << '\n';
	for(int i=0; i<25; i++){
		for(int j=0; j<25; j++){
			os << " " << broad.unitspace(broad.white[25*i+j], broad.block[25*i+j]);
		}
		os << '\n';
	}
    return os;  
}  

class Nonogram{
	std::array<std::vector<int>, 25> ConditionsOfRow;
	std::array<std::vector<int>, 25> ConditionsOfCol;
	std::array<std::set<std::bitset<25>, compareBitset>, 25> possibleSetArrayOfRow;
	std::array<std::set<std::bitset<25>, compareBitset>, 25> possibleSetArrayOfCol;
	
public :
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
		this->ConditionsOfRow = ConditionsOfRow;
		this->ConditionsOfCol = ConditionsOfCol;
		for(int i=0; i<25; i++){
			possibleSetArrayOfRow[i] = possible(ConditionsOfRow[i]);
			possibleSetArrayOfCol[i] = possible(ConditionsOfCol[i]);
		}
	}
	
	std::set<std::bitset<25>, compareBitset> possible(std::vector<int> ns){
		std::set<std::bitset<25>, compareBitset> resultSet;
		int n = ns.size();
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
	
	// std::set<Broad, Broad::compare> solve(Broad initBroad = Broad()){
		// std::set<Broad, Broad::compare> ans;
		// return ans;
	// }
};