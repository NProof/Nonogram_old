#include <iostream>
#include <cstdio>
#include <algorithm> 
#include <vector>
#include <bitset>
#include <set>

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
	
	Line(std::vector<int> ms){
		each0.flip();
		ns = ms;
		possibleSet = possible();
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
	
	bool allIn(std::bitset<25> &all_0, std::bitset<25> &all_1){
		for (std::set<std::bitset<25>, BitsetCmp>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
			all_1 &= *it;
			all_0 |= *it;
		}
		return true;
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
		cout << possibleSet.size() << endl;
		return false;
	}
	
};

enum class Solved { SOLVED=1, CONFIG=2, UNKWOKE=3 };

class Broad{
public :
	Line *rows;
	Line *cols;
	
	Broad(std::vector<int> *rowConditions, std::vector<int> *colConditions){
		rows = (Line*) malloc(25*sizeof(Line));
		cols = (Line*) malloc(25*sizeof(Line));
		for(int i=0; i<25; i++){
			rows[i] = Line(rowConditions[i]);
		}
		for(int j=0; j<25; j++){
			cols[j] = Line(colConditions[j]);
		}
	}
  
  //Solved solve(){
    return Solved::SOLVED;
  }
};

int main (int argc, char** argv)
{
  freopen("run.out", "w", stdout);
  if(argc>1){
    int f = 1;
    while(f<argc){
      FILE * inputFile;
      inputFile = fopen(argv[f], "r");
      while(1){
        int qn, ch;
        if(fscanf(inputFile, "$%d", &qn)!=1)
          break;
        cout << "$" << qn << endl;
        std::vector<int> rows[25]; 
        std::vector<int> cols[25];
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
        Broad nonogram(rows, cols);  
        cout << nonogram.solve() << endl;
      }
      f++;   
    }
  }
	return 0;
}
