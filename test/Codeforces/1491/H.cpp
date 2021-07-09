/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2021年03月05日 星期五 11时38分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q, a[maxn], block, belong[maxn], anc[maxn], num[maxn], Max[maxn];
pii p[maxn];

inline void Rebuild(int x)
{
	Max[x] = 0;
	REP(i, p[x].first, p[x].second)
	{
		if ( a[i] < p[x].first ) anc[i] = a[i]; else anc[i] = anc[a[i]];	
		Max[x] = max(Max[x], a[i]);	
	}
}

inline int Get1(int x) { return max(1ll, anc[x] - num[belong[x]]); }
inline int Get2(int x) { return max(1ll, a[x] - num[belong[x]]); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &q); block = sqrt(n);
	REP(i, 2, n) scanf("%lld", &a[i]);
	for ( int l = 1, r = block; l <= n; l += block, r = min(r + block, n) )
	{
		++ m; REP(i, l, r) belong[i] = m; p[m] = pii(l, r);
		REP(i, l, r) 
		{
			if ( a[i] < l ) anc[i] = a[i]; else anc[i] = anc[a[i]]; 
			Max[m] = max(Max[m], a[i]);
		}
	}
	while ( q -- ) 
	{
		int op; scanf("%lld", &op);
		if ( op == 1 ) 
		{
			int l, r, x; scanf("%lld%lld%lld", &l, &r, &x);
			if ( belong[l] + 1 >= belong[r] ) 	
			{
				REP(i, l, r) a[i] = max(1ll, a[i] - x);
				Rebuild(belong[l]); if ( belong[l] != belong[r] ) Rebuild(belong[r]);
			}
			else
			{
				REP(i, l, p[belong[l]].second) a[i] = max(1ll, a[i] - x); Rebuild(belong[l]);
				REP(i, p[belong[r]].first, r) a[i] = max(1ll, a[i] - x); Rebuild(belong[r]);
				REP(i, belong[l] + 1, belong[r] - 1)
					if ( Max[i] < p[i].first ) num[i] += x;
					else { REP(j, p[i].first, p[i].second) a[j] = max(1ll, a[j] - x); Rebuild(i); }
			}
		}
		else
		{
			int u, v; scanf("%lld%lld", &u, &v);
			while ( Get1(u) != Get1(v) ) { if ( Get1(u) < Get1(v) ) swap(u, v); u = Get1(u); }
			while ( Get2(u) != Get2(v) ) { if ( Get2(u) < Get2(v) ) swap(u, v); u = Get2(u); }
			if ( u == v ) printf("%lld\n", u);
			else printf("%lld\n", Get2(u));
		}
	}
    return 0;
}
