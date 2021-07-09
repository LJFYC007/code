#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int main()
{
	freopen("slayer.in", "w", stdout);
	int n = 10000, m = rand() % 3000 + n; printf("%d %d\n" ,n, m);
	REP(i, 1, n) printf("%d ", rand() % Mod); puts("");
	REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1); 
	REP(i, 1, m)
	{
		int op = rand() % 2 + 1;
		if ( op == 1 ) printf("1 %d %d\n", rand() % n + 1, rand() % Mod);
		else printf("2 %d\n" ,rand() % n + 1);
	}
	return 0;
}
