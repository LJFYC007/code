/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2021年03月24日 星期三 21时33分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, k, a[maxn], p[maxn], dp[maxn], c[maxn], d[maxn], f[maxn], len, val, Len, Val;
set<int> Set, S;
bool vis[maxn];

inline int lowbit(int x) { return x & -x; } 
inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[i] = max(c[i], val); } 
inline int query(int pos) { int ret = -0x3f3f3f3f; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, c[i]); return ret; }
inline void ADD(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) d[i] += val; } 
inline int QUERY(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret += d[i]; return ret; }

inline bool Check(int x)
{
	mem(d); REP(i, x + 1, n) ADD(a[i], 1); bool flag = false; Len = Val = 0;
	REP(i, 1, x) if ( dp[a[i]] + QUERY(a[i]) >= k )
	{
		flag = true; Len = x; 
		Val = dp[Val] > dp[a[i]] ? Val : a[i]; 
	}
	return flag;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]] = i; } 
	if ( a[1] <= k ) 
	{
		for ( int i = k; i >= 1; -- i ) REP(j, p[i], n)
		{
			printf("%d ", a[j]);
			if ( a[j + 1] <= k ) break ; 
		}
		puts(""); return 0;
	}
	memset(c, -0x3f, sizeof(c)); dp[a[1]] = 1; add(n - a[1] + 1, 1);
	REP(i, 2, n) { dp[a[i]] = query(n - a[i] + 1) + 1; add(n - a[i] + 1, dp[a[i]]); }

	vector<int> b; REP(i, 1, n) if ( a[i + 1] < a[1] ) b.push_back(i);
	int L = 0, R = b.size() - 1;
	while ( L <= R ) 
	{
		int Mid = (L + R) >> 1; 
		if ( Check(b[Mid]) ) { len = Len; val = Val; L = Mid + 1; }
		else R = Mid - 1;
	}
	REP(i, 1, len) printf("%d ", a[i]); 
	if ( len == n ) { puts(""); return 0; } 
	REP(i, len + 2, n) if ( a[i] <= val ) Set.insert(a[i]);
	k -= dp[val] + 1; S.insert(a[len + 1]);
	while ( k ) 
	{
		int now = *(Set.begin()); Set.erase(now);
		-- k; S.insert(now);
	}
	while ( S.size() ) 
	{
		int now = *(-- S.end()); S.erase(now); now = p[now];
		while ( !vis[now] && now <= n && S.find(a[now]) == S.end() ) { printf("%d ", a[now]); vis[now] = true; ++ now; } 
	}
    return 0;
}
