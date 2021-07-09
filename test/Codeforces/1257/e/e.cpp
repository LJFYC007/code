#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;
 
int n1, n2, n3, ans, sum, c[maxn][2], n;
set<int> Set1, Set2, Set3;
 
inline int lowbit(int x) { return x & -x; }
 
inline void add(int pos, int val, int opt)
{
	for ( int i = pos; i <= n; i += lowbit(i) ) c[i][opt] += val;
}
 
inline int get(int pos, int opt)
{
	int ret = 0;
	for ( int i = pos; i > 0; i -= lowbit(i) ) ret += c[i][opt];
	return ret;
}
 
inline int et(int x, int opt)
{
	int ret;
	if ( opt == 0 ) ret = get(x, 1);
	else ret = Set2.size() - get(x, 0);
	return ret;
}
 
inline void Solve()
{
	if ( !Set2.size() || !Set3.size() ) { sum = 0; return ; }
    auto it = -- Set2.end();
	sum = et(*it, 0);
	it = Set3.begin();
	sum = min(sum, et(*it, 1));
}
 
int main()
{
	scanf("%d%d%d", &n1, &n2, &n3);
	n = n1 + n2 + n3;
	REP(i, 1, n1) { int x; scanf("%d", &x); Set1.insert(x); }
	REP(i, 1, n2) { int x; scanf("%d", &x); Set2.insert(x); add(x, 1, 0); }
	REP(i, 1, n3) { int x; scanf("%d", &x); Set3.insert(x); add(x, 1, 1); }
	Solve();
	auto it = Set1.begin();
	ans = n1 + sum;
	int x = 0;
	REP(i, 1, n)
	{
		if ( it != Set1.end() && *it < i ) ++ it;
		if ( it != Set1.end() && *it == i ) ++ x;
		int ret = n1 - x + i - x;
		if ( Set2.lower_bound(i) != Set2.end() && *Set2.lower_bound(i) == i ) { Set2.erase(i); add(i, -1, 0); }
		else if ( Set3.lower_bound(i) != Set3.end() && *Set3.lower_bound(i) == i ) { Set3.erase(i); add(i, -1, 1); }
		Solve();
		ans = min(ans, ret + sum);
	}
	printf("%d\n", ans);
	return 0;
}
