/***************************************************************
	File name: P4127.cpp
	Author: ljfcnyali
	Create time: 2019年10月23日 星期三 20时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), -1, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;

int f[20][maxn][maxn], tmp[20], tot, num;
LL ans, a, b;

inline LL DFS(int x, int sum, int val, bool opt)
{
    if ( !x ) return sum == num && !val;
    if ( !opt && f[x][sum][val] != -1 ) return f[x][sum][val];
    int dim = opt ? tmp[x] : 9; LL ret = 0;
    REP(i, 0, dim) ret += DFS(x - 1, sum + i, (val * 10 + i) % num, opt & (i == dim));
    if ( !opt ) f[x][sum][val] = ret;
    return ret;
}

inline LL Solve(LL x)
{
    tot = 0;
    while ( x ) { tmp[++ tot] = x % 10; x /= 10; }
    return DFS(tot, 0, 0, 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &a, &b);
    REP(i, 1, 200)
    {
        num = i; mem(f);
        ans += Solve(b) - Solve(a - 1);
    }
    printf("%lld\n", ans);
    return 0;
}
