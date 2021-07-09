#include <bits/stdc++.h>
#include "travel.h"

void solve(int n,int limA,int limB){
	int Size=find(1,2);
	std::vector<int>h(0);h.push_back(2);
	int op=check(1,2,h);
	for(int i=1;i<n;i++) report(i,i+1);
}
