#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e7 + 10;

int n, k, a[maxn], ans[maxn], f[maxn];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 

inline void read(int &x)
{
	x = 0; char c = getchar();
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("decrypt.in", "r", stdin);
	freopen("decrypt.out", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) read(a[i]);
	REP(i, 1, n + k + 1) f[i] = i;
	int m = n, sum = 0, now = n;
	for ( int i = n; i >= 1; -- i ) 
	{
		if ( a[i] == 1 ) 
		{ 
			int pos = find(now);
			if ( pos <= now + k - 1 ) { f[pos] = pos + 1; ++ sum; }
			else ans[m --] = 1;
			// bool flag = false;
			//REP(j, now, now + k - 1) if ( !f[j] ) { f[j] = 1; ++ sum; flag = true; break ; } 
			//if ( !flag ) ans[m --] = 1;
			continue ; 
		} 
		if ( f[now + k] != now + k ) { ans[m --] = 1; -- sum; } 
		-- now; ans[m --] = 0; 
	}
	REP(i, 1, sum) ans[m --] = 1;
	REP(i, 1, n) printf("%d ", ans[i]); puts("");
	return 0;
}
