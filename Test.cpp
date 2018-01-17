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

void case2(){
	Broad broad;
	cout << broad << endl;
}

int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	case2();
	return 0;
}
