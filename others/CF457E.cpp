/***************************************************************
	File name: s.cpp
	Author: ljfcnyali
	Create time: 2021年04月06日 星期二 11时18分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4e5 + 10;

int n, m, a[maxn], f[maxn], val, size[maxn];
set<pii> Set[maxn];
multiset<int> ans;

inline int find(int x) { return x == f[x] ? x : find(f[x]); } 
inline int Get(int x) { return (*(-- Set[x].end())).first - (*Set[x].begin()).first; }
inline void Erase(int x) { ans.erase(ans.find(Get(x))); }
inline void Insert(int x) { ans.insert(Get(x)); }
inline bool fuck(int x, int y) { auto it = Set[x].lower_bound(pii(y, 0)); return it != Set[x].end() && (*it).first == y; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) { f[i] = i; size[i] = 1; Set[i].insert(pii(0, i)); } 
	REP(i, 2, n - 1) ans.insert(0);
	REP(i, 1, m) 
	{
		int s, t, v, w; scanf("%lld%lld%lld%lld", &s, &t, &v, &w);

		int x = find(s), y = find(t), W = a[s] - a[t] + v * w;;
		if ( x == y )
		{
			if ( a[s] + v * w != a[t] ) { printf("BAD %lld\n", i); return 0 ; } 
			continue ; 
		}
		if ( x != find(1) && x != find(n) ) Erase(x);
		if ( y != find(1) && y != find(n) ) Erase(y);
		
		if ( size[x] < size[y] ) 
		{
			for ( auto it : Set[x] ) { Set[y].insert(pii(it.first - W, it.second)); a[it.second] -= W; }
			f[x] = y; size[y] += size[x];
		}
		else
		{
			for ( auto it : Set[y] ) { Set[x].insert(pii(it.first + W, it.second)); a[it.second] += W; }
			f[y] = x; size[x] += size[y];
		}
		int pos = find(s);
		if ( pos != find(1) && pos != find(n) ) Insert(pos);
		if ( find(n) == find(1) ) val = Get(find(1));
		if ( val && ans.lower_bound(val) != ans.end() ) { printf("BAD %lld\n", i); return 0; } 

		if ( pos == find(1) && (-- Set[pos].upper_bound(pii(a[1], n + 1))) != Set[pos].begin() ) { printf("BAD %lld\n", i); return 0; } 
		if ( pos == find(n) && Set[pos].lower_bound(pii(a[n], 0)) != (-- Set[pos].end()) ) { printf("BAD %lld\n", i); return 0; } 
	}
	if ( !val ) puts("UNKNOWN"); else printf("%lld\n", val);
    return 0;
}
