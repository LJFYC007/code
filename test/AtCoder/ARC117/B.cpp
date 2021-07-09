/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年04月18日 星期日 20时03分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, ans = 1;
map<int, bool> Map;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) { int x; scanf("%lld", &x); Map[x] = true; }
	int lst = 0;
	for ( auto it : Map ) { ans = ans * (it.first - lst + 1) % Mod; lst = it.first; }
	printf("%lld\n", ans);
    return 0;
}
