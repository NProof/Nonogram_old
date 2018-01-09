// bitset::set
#include <iostream>       // std::cout
#include <algorithm>
#include <bitset>         // std::bitset
#include <set>

struct BitsetCmp {
    bool operator()(const std::bitset<25>& lhs, const std::bitset<25>& rhs) const { 
		return lhs.to_ulong() < rhs.to_ulong();
    }
};
void perm () {
  int myints[] = {1,2,3};

  std::sort (myints,myints+3);

  std::cout << "The 3! possible permutations with 3 elements:\n";
  do {
    std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
  } while ( std::next_permutation(myints,myints+3) );

  std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';

}

void com (int n, int m) {
  int myints[n], other[m];
  for(int i=0; i<n; i++)
	  myints[i] = i+1;

  std::sort (myints,myints+n);

  do {
	  bool nosame = false;
	  for(int i=0; i<m; i++){
		  if(other[i] != myints[i]){
			  nosame = true;
			  break;
		  }
	  }
	  if(nosame){
		  for(int j=0; j<m; j++){
			  // std::cout << ' ' << myints[j] ;
			   other[j] = myints[j];
		  }
		// std::cout << std::endl;
	  }
  } while ( std::next_permutation(myints,myints+n) );
  
  for(int j=0; j<n; j++){
		   std::cout << ' ' << myints[j] ;
	  }
	  std::cout << std::endl;
}

void test1(){
	
  std::bitset<25> foo;
  std::bitset<25> bar;
  
  // std::set<std::bitset<25>> non
  std::set<std::bitset<25>, BitsetCmp> non;

  foo.set(2);
  foo.set(3);
  bar.set(5);
  bar.set(7);
  std::cout << foo << '\n';
  std::cout << bar << '\n';
  
  non.insert(foo);
  non.insert(bar);
  
  for (std::set<std::bitset<25>>::iterator it=non.begin(); it!=non.end(); ++it)
    std::cout << ' ' << *it;
}

void comBit(int n, int *ms, int m){
	// n-m[]+1
	int s = 0;
	for(int i=0; i<m; i++)
		s += ms[i];
	int n0 = n-s+1;
	int myints[n0], other[m];
	for(int i=0; i<n0; i++)
		myints[i] = i+1;
	std::sort (myints,myints+n0);
	do {
		bool nosame = false;
		for(int i=0; i<m; i++){
			if(other[i] != myints[i]){
				nosame = true;
				break;
			}
		}
		if(nosame){
			for(int j=0; j<m; j++){
				std::cout << ' ' << myints[j] ;
				other[j] = myints[j];
			}
			std::cout << std::endl;
		}
	} while ( std::next_permutation(myints,myints+n0) );
}

int main ()
{
	int ms[3]{5, 13, 5};
	comBit(25,ms,3);
	return 0;
}
