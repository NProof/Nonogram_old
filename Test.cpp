#include <iostream>
// #include <cstdio>
#include "main.h"

using namespace std;

// void case1(){
	// std::array<std::vector<int>, 25> rows;
	// std::array<std::vector<int>, 25> cols;
	// Nonogram *nonogram = new Nonogram(rows, cols);
	// std::vector<int> ns;
	// ns.push_back(1);
	// ns.push_back(12);
	// std::set<std::bitset<25>, compareBitset> ans = nonogram->possible(ns);
	// nonogram->possible(ns);
	// for(std::set<std::bitset<25>, compareBitset>::iterator it=ans.begin(); it!=ans.end(); ++it){
		// cout << *it << endl;
	// }
	// cout <<  " : " << nonogram->possible(ns).size() << endl;
// }

// void case2(){
	// Broad broad;
	// broad.write(1,2,1);
	// broad.write(2,2,0);
	// cout << broad << endl;
	// broad.clean(2,2);
	// cout << broad << endl;
// }

// void clonetest(){
	// Broad *broad1 = new Broad();
	// cout << broad1 << endl;
	// cout << new Broad(*broad1) << endl;
// }

void getLine(){
	Broad broad = Broad();
	broad.write(1,2,1);
	broad.write(3,1,0);
	Line liner1 = broad.getLineR(1);
	Line linec1 = broad.getLineC(1);
	cout << liner1.white << " : " << liner1.block << endl;
	cout << linec1.white << " : " << linec1.block << endl;
}

int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	getLine();
	return 0;
}
