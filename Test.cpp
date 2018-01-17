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
	std::cout << ans.size() << std::endl;
	return 0;
}
