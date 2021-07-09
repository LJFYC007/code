#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e7 + 10;

int k, m, Mod, ans, f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	cin >> k >> m >> Mod;
	queue<pii> Q; Q.push(pii(1, 1));
	while ( !Q.empty() ) 
	{
		int x = Q.front().first, dep = Q.front().second; Q.pop();
		if ( f[x] ) continue ; f[x] = dep;
		if ( dep == m + 1 ) { ++ ans; continue ; } 
		Q.push(pii(x + 1, dep + 1));
		Q.push(pii(x * k, dep + 1));
	}
	printf("%d\n", ans % Mod);
	return 0;
}
