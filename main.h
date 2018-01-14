// #include <iostream>
// #include <cstdio>
#include <bitset>
#include <array>
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
		// cout << resultSet.size() << endl;
		return resultSet;
	}
	
	std::array<std::set<std::bitset<25>, compareBitset>, 25> getPossibleSetArrayOfRow(){
		return std::array<std::set<std::bitset<25>, compareBitset>, 25>(possibleSetArrayOfRow);
	}
	
	std::array<std::set<std::bitset<25>, compareBitset>, 25> getPossibleSetArrayOfCol(){
		return std::array<std::set<std::bitset<25>, compareBitset>, 25>(possibleSetArrayOfCol);
	}
};

class Line{
public :
	bool satisfaction;
	bool isRow;
	int index;
	std::bitset<25> block;
	std::bitset<25> white;
	Line(std::bitset<25> bitsblock, std::bitset<25> bitswhite, bool isRow, int index){
		this->satisfaction = false;
		this->isRow = isRow;
		this->index = index;
		block = bitsblock;
		white = bitswhite;
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
	std::bitset<25> uniRows;
	std::bitset<25> uniCols;
	
	Broad(){
		white.flip();
		uniRows.flip();
		uniCols.flip();
	}
	
	Line getLine(bool isRow, int index){
		std::bitset<25> bitsblock;
		std::bitset<25> bitswhite;
		if(isRow){
			for(int i=0; i<25; i++){
				bitsblock[i] = block[25*index+24-i];
				bitswhite[i] = white[25*index+24-i];
			}
		}
		else{
			for(int i=0; i<25; i++){
				bitsblock[i] = block[25*(24-i)+(index)];
				bitswhite[i] = white[25*(24-i)+(index)];
			}
		}
		return Line(bitsblock, bitswhite, isRow, index);
	}
	
	void setLine(Line line){
		int index = line.index;
		if(line.isRow){
			uniRows.set(24-index, line.satisfaction);
			for(int i=0; i<25; i++){
				block[25*index+24-i] = line.block[i];
				white[25*index+24-i] = line.white[i];
			}
		}
		else{
			uniCols.set(24-index, line.satisfaction);
			for(int i=0; i<25; i++){
				block[25*(24-i)+(index)] = line.block[i];
				white[25*(24-i)+(index)] = line.white[i];
			}
		}
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
    os << " white : " << &broad << '\n';
	for(int i=0; i<25; i++){
		for(int j=0; j<25; j++){
			os << " " << broad.unitspace(broad.white[25*i+j], broad.block[25*i+j]);
		}
		os << '\n';
	}
    return os;  
}  

class Solver{
	Nonogram *nonogram;
	std::map<Broad*, std::array<std::set<std::bitset<25>, compareBitset>, 25>> mapRow;
	std::map<Broad*, std::array<std::set<std::bitset<25>, compareBitset>, 25>> mapCol;
public :
	Solver(Nonogram *nonogram){
		this->nonogram = nonogram;
	}
	
	std::set<Broad, Broad::compare> solve(Broad initBroad = Broad()){
		std::set<Broad, Broad::compare> ans;
		cout << solve(&initBroad);
		return ans;
	}
	
	static std::set<std::bitset<25>, compareBitset> reduceLine(const Line line, std::set<std::bitset<25>, compareBitset> &possibleSet){
		std::set<std::bitset<25>, compareBitset> changeSet;
		for (std::set<std::bitset<25>, compareBitset>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
			if(((*it^line.white)&~line.white).any() || ((*it^line.block)&line.block).any()){
				changeSet.insert(*it);
			}
		}
		for (std::set<std::bitset<25>, compareBitset>::iterator it=changeSet.begin(); it!=changeSet.end(); ++it){
			possibleSet.erase(*it);
		}
		return changeSet;
	}
	
	static bool inAll(std::set<std::bitset<25>, compareBitset> possibleSet, Line *line){
		line->white.reset();
		line->block.set();
		for (std::set<std::bitset<25>, compareBitset>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
			line->block &= *it;
			line->white |= *it;
		}
		return true;
	}
	
	static bool changeLine(Line *line, std::set<std::bitset<25>, compareBitset> *possibleSet
	,std::bitset<25> *changeW = new std::bitset<25>, std::bitset<25> *changeB = new std::bitset<25>
	){
		*changeW = line->white;
		*changeB = line->block;
		reduceLine(*line, *possibleSet);
		inAll(*possibleSet, line);
		*changeW ^= line->white;
		*changeB ^= line->block;
		return changeW->any() || changeB-> any();	
	}
	
	int solve(Broad *broad){
		std::array<std::set<std::bitset<25>, compareBitset>, 25> possibleSetArrayOfRow = nonogram->getPossibleSetArrayOfRow();
		std::array<std::set<std::bitset<25>, compareBitset>, 25> possibleSetArrayOfCol = nonogram->getPossibleSetArrayOfCol();
		
		for(int i=0; i<25; i++){
			Line line = broad->getLine(true, i);
			reduceLine(line, possibleSetArrayOfRow[i]);
			inAll(possibleSetArrayOfRow[i], &line);
			broad->setLine(line);
		}
		// cout << *broad << endl;
		// std::bitset<25> reUniCols;
		// for(int k=0; k<24; k++){
			// reUniCols[k] = broad->uniCols[24-k];
		// }
		
		for(int j=0; j<25; j++){
			Line line = broad->getLine(false, j);
			std::bitset<25> *changeW;
			std::bitset<25> *changeB;
			if(changeLine(&line, &possibleSetArrayOfCol[j], changeW, changeB)){
				broad->setLine(line);
				// cout << j << endl;
				// cout << "*changeW : " << *changeW << endl;
				// cout << "*changeB : " << *changeB << endl;
			}
		}
		// for(int i=0; i<25; i++){
			Line line = broad->getLine(true, 0);
			// std::bitset<25> *changeW;
			// std::bitset<25> *changeB;
			// if(changeLine(&line, &possibleSetArrayOfCol[i], changeW, changeB)){
				// broad->setLine(line);B : " << *changeB << endl;
			// }
		// }
		/**/
		// for(int k=0; k<24; k++){
			// broad->uniCols[k] = reUniCols[24-k];
		// }
		cout << *broad << endl;
		// mapRow[broad] = possibleSetArrayOfRow;
		// mapCol[broad] = possibleSetArrayOfCol;
		return 9;
	}
};

//