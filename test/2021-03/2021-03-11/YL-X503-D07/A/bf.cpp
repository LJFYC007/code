#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int n, s[maxn], t[maxn], a[maxn], ans;

inline void DFS(int x, int sum)
{
	if ( x == n + 1 ) { ans = max(ans, sum); return ; } 
	if ( !a[s[x]] ) { a[s[x]] = 1; DFS(x + 1, sum + t[x]); a[s[x]] = 0; } 
	if ( !a[t[x]] ) { a[t[x]] = 1; DFS(x + 1, sum + s[x]); a[t[x]] = 0; } 
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d%d", &s[i], &t[i]);
	DFS(1, 0);
	printf("%d\n" ,ans);
	return 0;
}
