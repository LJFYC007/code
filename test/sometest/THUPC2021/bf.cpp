/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2020年12月12日 星期六 15时25分47秒
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

int T, n, ans;

inline void Build(int l, int r)
{
    if ( l == r ) { ans = (ans + l * (n - r + 1)) % Mod; return ; }
    int Mid = l + r >> 1; Build(l, Mid); Build(Mid + 1, r);
    ans = (ans - l * (n - r + 1)) % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n); ans = 0;        
        Build(1, n);
        printf("%lld\n", (ans + Mod) % Mod);
    }
    return 0;
}
