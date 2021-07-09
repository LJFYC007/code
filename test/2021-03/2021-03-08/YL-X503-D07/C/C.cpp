#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 5010;
const int Mod = 998244353;

int n, m, r[maxn], c[maxn], ans, p[maxn], b[maxn];
vector<int> a[maxn];

inline int lowbit(int x) { return x & -x; } 

inline void add(int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) b[i] = max(b[i], val); } 

inline int query(int pos) { int ret = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) ret = max(ret, b[i]); return ret; } 

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); p[0] = 1; REP(i, 1, m) p[i] = p[i - 1] * 233 % Mod;
	REP(i, 1, n) scanf("%lld", &r[i]);
	REP(i, 1, m) scanf("%lld", &c[i]);
	for ( int i = n; i >= 1; -- i ) REP(j, 1, m) if ( r[i] == c[j] ) a[j].push_back(i);
	REP(x, 1, m)
	{
		REP(i, 1, n) b[i] = 0; ans = 0;
		REP(i, x, m)
		{
			for ( auto it : a[i] ) 
			{
				int x = query(it - 1);
				add(it, x + 1);		
			}
			ans = (ans + p[i - x] * query(n)) % Mod;
		}
		printf("%lld ", (ans + Mod) % Mod);
	}
	return 0;
}
