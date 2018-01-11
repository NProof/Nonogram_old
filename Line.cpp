#include <iostream>
#include <bitset>
#include <set>
#include <vector>
#include "Line.h"

using namespace std;

Line::Line(int *ms, int n){
	each0.flip();
	for(int i=0; i<n; i++)
		ns.push_back(ms[i]);
	possibleSet = possible();
}

std::set<std::bitset<25>, BitsetCmp> Line::possible(){
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

bool Line::allPossible(std::bitset<25> &all_0, std::bitset<25> &all_1){
	for (std::set<std::bitset<25>, BitsetCmp>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
		all_1 &= *it;
		all_0 |= *it;
	}
	return true;
}

// bool reducePossible(const std::bitset<25> c0, const std::bitset<25> c1, std::bitset<25> *r0, std::bitset<25> *r1){
	// for (std::set<std::bitset<25>, BitsetCmp>::iterator it=possibleSet.begin(); it!=possibleSet.end(); ++it){
		// if(((*it^c0)&~c0).any()){
			
		// }
	// }
// }