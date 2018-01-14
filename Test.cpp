#include <iostream>
// #include <cstdio>
#include "main.h"

using namespace std;

// Broad
// Nonogram

int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	Broad broad = Broad();
	std::cout << broad << std::endl;
	return 0;
}
