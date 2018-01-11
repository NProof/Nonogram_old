// bitset::set
#include <iostream>       // std::cout
#include <algorithm>
#include <bitset>         // std::bitset
#include <set>
#include "Line.h"

using namespace std;

int main ()
{
	int ms[3]{10, 11, 1};
	Line line0(ms, 3);
	cout << line0.each0 << endl;
	cout << line0.each1 << endl;
	for (std::vector<int>::iterator it = line0.ns.begin(); it !=  line0.ns.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	cout << endl;
	std::set<std::bitset<25>, BitsetCmp> possibleSet = line0.possible();
	bitset<25> all1, all0;
	all1.flip();
	line0.allPossible(all0, all1);
	cout << all1 << " and 0 : " << all0 << endl;
	return 0;
}
