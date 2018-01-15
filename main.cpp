#include <iostream>
#include <ctime>
#include <array>
#include <vector>
#include <set>

#include "main.h"
using namespace std;

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
				// std::cout << "$" << qn << std::endl;
				std::cout << "$" << qn << endl;
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
				
				Nonogram *nonogram = new Nonogram(rows, cols);
				Solver solver = Solver(nonogram);
				std::set<Broad, Broad::compare> ans = solver.solveAll();
				if(!ans.empty())
					std::cout << *ans.begin() << std::endl;
				else
					std::cout << "No Any Broad Satisfy The Nonogram." << std::endl;
				
				// delete nonogram;
				// delete &solver;
				
				startTime = clock() - startTime;
				printf ("\tIt took %d clicks (%f seconds).\n", startTime, ((float)startTime)/CLOCKS_PER_SEC);
			}
			f++;   
		}
	}
	totalTime = clock() - totalTime;
	printf ("[ TOTAL ] %d clicks (%f seconds).\n", totalTime, ((float)totalTime)/CLOCKS_PER_SEC);
	
	return 0;
}
