// #include <iostream>
// #include <cstdio>
#include <bitset>
#include <array>
#include <vector>
#include <set>

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

std::ostream& operator<<(std::ostream& os, const Broad& broad)  
{  
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
public :
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
	}
	
	std::set<Broad, Broad::compare> solve(Broad initBroad = Broad()){
		std::set<Broad, Broad::compare> ans;
		return ans;
	}
};