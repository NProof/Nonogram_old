#include <iostream>
// #include <cstdio>
#include "main.h"

using namespace std;

void case1(){
	std::array<std::vector<int>, 25> rows;
	std::array<std::vector<int>, 25> cols;
	Nonogram *nonogram = new Nonogram(rows, cols);
	std::vector<int> ns;
	ns.push_back(1);
	ns.push_back(12);
	std::set<std::bitset<25>, compareBitset> ans = nonogram->possible(ns);
	nonogram->possible(ns);
	for(std::set<std::bitset<25>, compareBitset>::iterator it=ans.begin(); it!=ans.end(); ++it){
		cout << *it << endl;
	}
	cout <<  " : " << nonogram->possible(ns).size() << endl;
}

void case2(){
	Broad broad;
	broad.write(1,2,1);
	broad.write(2,2,0);
	cout << broad << endl;
	broad.clean(2,2);
	cout << broad << endl;
}

void clonetest(){
	Broad *broad1 = new Broad();
	cout << broad1 << endl;
	cout << new Broad(*broad1) << endl;
}

void getLine(){
	Broad broad = Broad();
	broad.write(1,2,1);
	broad.write(3,1,0);
	Line liner1 = broad.getLineR(1);
	Line linec1 = broad.getLineC(1);
	cout << liner1.white << " : " << liner1.block << endl;
	cout << linec1.white << " : " << linec1.block << endl;
}

int test(int argc, char **argv){
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
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
				// std::cout << "$" << qn << std::endl;
				std::cout << "$" << qn ;
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
				Broad broad;
				broad.write(1,1,1);
				broad.write(1,2,0);
				broad.write(1,4,1);
				broad.write(1,6,0);
				nonogram->solve(broad);
				cout << broad << endl;
				for(int i=0; i<25; i++){
					// cout << (*(nonogram->LinesOfRow))[i]->block << endl;
					cout << (*(nonogram->LinesOfRow))[i]->white << endl;
				}
				cout << "temp " << endl;
				for(int j=0; j<25; j++){
					// cout << (*(nonogram->LinesOfCol))[j]->block << endl;
					cout << (*(nonogram->LinesOfCol))[j]->white << endl;
				}
				
			}
			f++;   
		}
	}
	
	return 0;
}


int main (int argc, char** argv)
{
#if defined (LOCAL)
	freopen("run.out", "w", stdout);
#endif
	// case1();
	// case2();
	// clonetest();
	// getLine();
	test(argc, argv);
	return 0;
}
