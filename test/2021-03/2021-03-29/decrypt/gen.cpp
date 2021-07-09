#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
	freopen("decrypt.in", "w", stdout);
	srand(time(0));
	int n = 5000, k = rand() % 100 + 1; printf("%d %d\n", n, k);
	REP(i, 1, n) printf("%d ", rand() % 2); puts("");
	return 0;
}
