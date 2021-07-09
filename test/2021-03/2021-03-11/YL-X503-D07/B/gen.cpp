#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int k = rand() % 100 + 1, m = rand() % 300 + 1, Mod = 23;	
	printf("%d %d %d\n", k, m, Mod);
	return 0;
}
