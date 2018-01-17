#include <bitset>
#include <array>
#include <vector>
#include <set>

struct compareBitset {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return (lhs^rhs).any();
	}
};

class Line{
public :
	std::set<std::bitset<25>, compareBitset> possibleSet;
	std::bitset<25> block;
	std::bitset<25> white;
	std::bitset<25> chang;
};

class Broad{
public :
	std::bitset<625> white;
	std::bitset<625> block;
	Broad(){
		white.flip();
	}
	
	Broad(const Broad &orig){
		white = orig.white;
		block = orig.block;
	}
	
	struct compare{
		bool operator()(const Broad& lhs, const Broad& rhs) const {
			return (lhs.white^rhs.white).any()||(lhs.block^rhs.block).any();
		}
	};
	
	Line getLineR(int index){
		Line temp;
		for(int i=0; i<25; i++){
			temp.block[i] = block[25*index+24-i];
			temp.white[i] = white[25*index+24-i];
		}
		return temp;
	}
	
	Line getLineC(int index){
		Line temp;
		for(int i=0; i<25; i++){
			temp.block[i] = block[25*(24-i)+(index)];
			temp.white[i] = white[25*(24-i)+(index)];
		}
		return temp;
	}
	
	void write(int rown, int coln, bool color){
		if(color){
			block[25*(rown)+coln] = 1;
		}
		else{
			white[25*(rown)+coln] = 0;
		}
	}
	
	void clean(int rown, int coln){
		block[25*(rown)+coln] = 0;
		white[25*(rown)+coln] = 1;
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

std::ostream& operator<<(std::ostream& os, const Broad& broad){
    os << " broad : " << &broad << '\n';
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
	std::array<Line*, 25> *LinesOfRow;
	std::array<Line*, 25> *LinesOfCol;
	Nonogram(std::array<std::vector<int>, 25> ConditionsOfRow, std::array<std::vector<int>, 25> ConditionsOfCol){
		LinesOfRow = new std::array<Line*, 25>();
		LinesOfCol = new std::array<Line*, 25>();
		for(int i=0; i<25; i++){
			(*LinesOfRow)[i] = new Line();
			(*LinesOfRow)[i]->possibleSet = possible(ConditionsOfRow[i]);
			(*LinesOfCol)[i] = new Line();
			(*LinesOfCol)[i]->possibleSet = possible(ConditionsOfCol[i]);
		}
	}
	
	int solve(Broad broad){
		for(int i=0; i<25; i++){
			for(int j=0; j<25; j++){
				(*LinesOfRow)[i]->block[j] = broad.block[25*i+24-j];
				(*LinesOfRow)[i]->white[j] = broad.white[25*i+24-j];
			}
		}
		for(int j=0; j<25; j++){
			for(int i=0; i<25; i++){
				(*LinesOfCol)[j]->block[i] = broad.block[25*(24-i)+j];
				(*LinesOfCol)[j]->white[i] = broad.white[25*(24-i)+j];
			}
		}
		return 0;
	}
	
	std::set<Broad, Broad::compare> solveAll(Broad broad = Broad()){
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