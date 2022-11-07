/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int n, m, k, f[maxn], ans = 1, a[maxn];
vector<int> p;

inline int find(int x)
{
	if ( f[x] < 0 ) return x;
	if ( f[x] == 0 ) return 0;
	return f[x] = find(f[x]);
}

inline void Modify(int x, int y)
{
	if ( f[y] > 0 ) f[x] = f[y];
	else f[x] = y;
}

inline bool Insert(pii t)
{
	if ( t.first == t.second ) t.x = t.y = 0;
	if ( !t.first && !t.second ) return false;
	if ( t.first > t.second && t.second ) swap(t.first, t.second);
	if ( f[t.x] == -1 ) { Modify(t.x, t.y); return true; }
	else return Insert(pii(t.y, find(t.x)));
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); REP(i, 1, m) f[i] = -1;
	REP(i, 1, n)
	{
		int k; scanf("%lld", &k);
		pii t = pii(0, 0); scanf("%lld", &t.first);
		if ( k == 2 ) scanf("%lld", &t.second);
		if ( Insert(t) ) { ans = ans * 2 % Mod; p.push_back(i); }
	}
	printf("%lld %d\n", ans, p.size());
	for ( int i = 0; i < p.size(); ++ i ) printf("%lld ", p[i]); puts("");
    return 0;
}
