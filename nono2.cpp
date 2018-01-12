#include <iostream>
#include <cstdio>
#include <algorithm> 
#include <array>
#include <vector>
#include <bitset>
#include <set>
#include <stack>
#include <ctime>

using namespace std;

struct BitsetCmp {
	bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return lhs.to_ulong() > rhs.to_ulong();
	}
};

class Line{
public :
	std::vector<int> ns;
	std::bitset<25> all_0;
	std::bitset<25> all_1;
	std::set<std::bitset<25>, BitsetCmp> possibleSet;
	
	Line(std::vector<int> ms){
		ns = ms;
		possibleSet = possible();
		allIn();
		// cout << '\n' << all_0 << '\n' << all_1 << endl;
	}
	
	std::set<std::bitset<25>, BitsetCmp> possible(){
		std::set<std::bitset<25>, BitsetCmp> resultSet;
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
	
	void allIn(){
		all_0.reset();
		all_1.set();
		for (std::set<std::bitset<25>, BitsetCmp>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
			all_1 &= *it;
			all_0 |= *it;
		}
	}
	
	bool reducePossible(const std::bitset<25> c0, const std::bitset<25> c1){
		std::set<std::bitset<25>, BitsetCmp> reduceSet;
		for (std::set<std::bitset<25>, BitsetCmp>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
			if(((*it^c0)&~c0).any() || ((*it^c1)&c1).any()){
				reduceSet.insert(*it);
			}
		}
		for (std::set<std::bitset<25>, BitsetCmp>::iterator it=reduceSet.begin(); it!=reduceSet.end(); ++it){
			possibleSet.erase(*it);
		}
		// cout << " possibleSet.size() : " << possibleSet.size() << endl;
		return !possibleSet.empty();
	}
	
};

// enum class Solved { SOLVED=1, CONFIG=2, UNKWOKE=3 };

char unitspace(int white, int block){
	if(white==1&&block==0){
		return '.' ;
	}
	else if(white==0&&block==0){
		return '0' ;
	}
	else if(block==1&&white==1){
		return '1' ;
	}
	else{
		return '%' ;
	}
}

class Broad{
public :
	Line **rows;
	Line **cols;
	std::bitset<25> uniRows;
	std::bitset<25> uniCols;
	
	~Broad(){
		for(int i=0; i<25; i++){
			delete rows[i];
		}
		for(int j=0; j<25; j++){
			delete cols[j];
		}
	}
	
	Broad(std::array<std::vector<int>, 25> rowConditions, std::array<std::vector<int>, 25> colConditions){
		rows = (Line**) malloc(25*sizeof(Line*));
		cols = (Line**) malloc(25*sizeof(Line*));
		for(int i=0; i<25; i++){
			rows[i] = new Line(rowConditions[i]);
		}
		for(int j=0; j<25; j++){
			cols[j] = new Line(colConditions[j]);
		}
	}
	
	void printBroad(){
		
		cout << "\t \tBroad ( R ) : 0\n\n" ;
		for(int i=0; i<25; i++){
			for(int j=0; j<25; j++){
				int white = rows[i]->all_0[24-j];
				int block = rows[i]->all_1[24-j];
				cout << " " << unitspace(white, block);
			}
			cout << endl;
		}
		
		cout << "\t \tBroad ( C ) : 1\n\n" ;
		for(int i=0; i<25; i++){
			for(int j=0; j<25; j++){
				int white = cols[j]->all_0[24-i];
				int block = cols[j]->all_1[24-i];
				cout << " " << unitspace(white, block);
			}
			cout << endl;
		}
	}
	
	int solve(){
		std::array<std::bitset<25>, 25> transRow0;
		std::array<std::bitset<25>, 25> transRow1;
		std::array<std::bitset<25>, 25> transCol0;
		std::array<std::bitset<25>, 25> transCol1;
	{
		for(int i=0; i<25; i++){
			for(int j=0; j<25; j++){
				transRow0[i][j] = cols[24-j]->all_0[24-i];
				transRow1[i][j] = cols[24-j]->all_1[24-i];
				transCol0[i][j] = rows[24-j]->all_0[24-i];
				transCol1[i][j] = rows[24-j]->all_1[24-i];
			}
		}
		
		for(int i=0; i<25; i++){
			if((~transRow0[i]).any()||transRow1[i].any()){
				uniRows.set(i,1);
			}
			if((~transCol0[i]).any()||transCol1[i].any()){
				uniCols.set(i,1);
			}
		}
	}
		while(uniRows.any()||uniCols.any()){
			if(uniRows.any()){
				std::bitset<25> reUniCols;
				for(int k=0; k<24; k++){
					reUniCols[k] = uniCols[24-k];
				}
				for(int j=0; j<25; j++){
					if(uniRows[j]){
						std::bitset<25> change0 = rows[j]->all_0;
						std::bitset<25> change1 = rows[j]->all_1;
						
						if(!rows[j]->reducePossible(transRow0[j], transRow1[j]))
							return -1;
						rows[j]->allIn();
						
						change0 ^= rows[j]->all_0;
						change1 ^= rows[j]->all_1;
						
						uniRows.set(j,0);
						reUniCols |= change0 | change1;
					}
				}
				for(int k=0; k<24; k++){
					uniCols[k] = reUniCols[24-k];
				}
			}
			
			for(int i=0; i<25; i++){
				for(int j=0; j<25; j++){
					transCol0[i][j] = rows[24-j]->all_0[24-i];
					transCol1[i][j] = rows[24-j]->all_1[24-i];
				}
			}
			
			if(uniCols.any()){
				std::bitset<25> reUniRows;
				for(int k=0; k<24; k++){
					reUniRows[k] = uniRows[24-k];
				}
				for(int i=0; i<25; i++){
					if(uniCols[i]){
						std::bitset<25> change0 = cols[i]->all_0;
						std::bitset<25> change1 = cols[i]->all_1;
						if(!cols[i]->reducePossible(transCol0[i], transCol1[i]))
							return -1;
						cols[i]->allIn();
						change0 ^= cols[i]->all_0;
						change1 ^= cols[i]->all_1;
						uniCols.set(i,0);
						reUniRows |= change0 | change1;
					}
				}
				for(int k=0; k<24; k++){
					uniRows[k] = reUniRows[24-k];
				}
			}
			
			for(int i=0; i<25; i++){
				for(int j=0; j<25; j++){
					transRow0[i][j] = cols[24-j]->all_0[24-i];
					transRow1[i][j] = cols[24-j]->all_1[24-i];
				}
			}
		}
		
		int ans = 1;
		for(int j=0; j<25; j++){
			rows[j]->reducePossible(transRow0[j], transRow1[j]);
			ans = (rows[j]->possibleSet.size()==1) ? ans : 0;
			rows[j]->allIn();
		}
		
		// printBroad();
		return ans;
	}
	
	bool unknownOne(int *i, int *j){
		int k, l;
		for(k=0; k<25; k++){
			for(l=0; l<25; l++){
				if((rows[k]->all_0^rows[k]->all_1)[24-l]){
					*i = k;
					*j = l;
					return true;
				}
			}
		}
		return false;
	}
};

bool solveAll(Broad * nonogram){
	std::stack<Broad *> nonogramStack;
	nonogramStack.push( nonogram );
	while(!nonogramStack.empty()){
		nonogram = nonogramStack.top();
		nonogramStack.pop();
		switch(nonogram->solve()){
			case 1:
				return true;
			case 0:
				int i, j;
				nonogram->unknownOne(&i, &j);
				cout << " i = " << i << " , j = " << j << endl;
				nonogram->printBroad();
		};
	}
	return false;
}
	
int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	clock_t totalTime = clock();
	if(argc>1){
		int f = 1;
		while(f<argc){
			FILE * inputFile;
			inputFile = fopen(argv[f], "r");
			while(1){
				int qn;
				char ch;
				if(fscanf(inputFile, "$%d", &qn)!=1)
					break;
				clock_t startTime = clock();
				cout << "$" << qn << endl;
				std::array<std::vector<int>, 25> rows;
				std::array<std::vector<int>, 25> cols;
				
				for(int j=0; j<50; j++){
					int cc;     
					std::vector<int> myv;
					do{
						cc = fscanf(inputFile, "%d%c", &qn, &ch); 
						myv.push_back(qn);
					}
					while(cc==2&&ch!='\n'); 
					if(j/25){
						cols[j-25] = myv;
					}
					else{
						rows[j] = myv;
					}                   
				}
				Broad *nonogram = new Broad(rows, cols);
				solveAll(nonogram);
				delete nonogram;
				startTime = clock() - startTime;
				printf ("\t\tIt took %d clicks (%f seconds).\n", startTime, ((float)startTime)/CLOCKS_PER_SEC);
			}
			f++;   
		}
	}
	totalTime = clock() - totalTime;
	printf ("\tIt took %d clicks (%f seconds).\n", totalTime, ((float)totalTime)/CLOCKS_PER_SEC);
	
	return 0;
}
