#include <iostream>
// #include <cstdio>
#include "main.h"

using namespace std;

int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	
	std::set<Broad, Broad::compare> ans;
	Broad broad = Broad();
	ans.insert(broad);
	broad.white.set(1,0);
	ans.insert(broad);
	broad.white.set(1,1);
	ans.insert(broad);
	std::cout << ans.size() << std::endl;
	return 0;
}
