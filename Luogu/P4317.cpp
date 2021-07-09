/***************************************************************
	File name: P4317.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 15时15分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3010;
const int Mod = 10000007;

int tmp[maxn], tot, n, f[maxn][maxn], ans;

inline int power(int a, int b) 
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

inline int DFS(int x, int sum, int num, bool opt)
{
    if ( !x ) return sum == num; 
    if ( !opt && f[x][num - sum] != -1 ) return f[x][num - sum];
    int dim = opt ? tmp[x] : 1, ret = 0;
    REP(i, 0, dim) ret += DFS(x - 1, sum + (i == 1), num, opt & (i == dim));
    if ( !opt ) f[x][num - sum] = ret;
    return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    while ( n ) { tmp[++ tot] = n % 2; n /= 2; }
    memset(f, -1, sizeof(f));
    ans = 1;
    REP(i, 1, tot) ans = (ans * power(i, DFS(tot, 0, i, 1))) % Mod;
    printf("%lld\n", ans);
    return 0;
}
