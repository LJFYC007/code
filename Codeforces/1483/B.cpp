/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn], nxt[maxn];
vector<int> ans;
bool vis[maxn];
queue<pii> Q;

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- )
	{
		scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
		REP(i, 1, n) { nxt[i] = i == n ? 1 : i + 1; vis[i] = false; } 
		int lst = 1, num = 0;
		REP(i, 2, n) if ( !vis[i] && __gcd(a[i], a[i + 1]) == 1 ) { vis[i] = true; Q.push(pii(i - 1, i)); lst = i; }
		if ( __gcd(a[1], a[n]) == 1 && !vis[1] && !vis[n] ) { vis[1] = true; Q.push(pii(n, 1));  } 
		while ( !Q.empty() ) 
		{
			pii u = Q.front(); Q.pop(); ans.push_back(u.second);
			++ num; if ( num == n ) break ; 
			while ( vis[nxt[u.y]] || vis[
		}
		printf("%d ", ans.size()); for ( auto it : ans ) printf("%d ", it); puts("");
	}
    return 0;
}
