/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年10月31日 星期六 20时07分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, K, a[60][60], ans = 1, num, val;
bool vis[2][60], Edge[2][60][60];

inline void DFS(int op, int u)
{
    REP(i, 1, n)
    {
        if ( u == i || vis[op][i] || !Edge[op][u][i] ) continue ;
        vis[op][i] = true; ++ num; val = val * num % Mod;
        DFS(op, i);
    }
}

inline void Solve(int op)
{
    int sum = 1;
    REP(i, 1, n) if ( !vis[op][i] ) 
    { 
        num = 1; val = 1; 
        vis[op][i] = true; 
        DFS(op, i);
        sum = sum * val % Mod;
    }
    ans = ans * sum % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &K);
    REP(i, 1, n) REP(j, 1, n) scanf("%lld", &a[i][j]);
    REP(j, 1, n) REP(k, j + 1, n) 
    {
        bool flag = true;
        REP(i, 1, n) if ( a[i][j] + a[i][k] > K ) flag = false;
        if ( flag ) Edge[0][j][k] = Edge[0][k][j] = true;
    }
    REP(j, 1, n) REP(k, j + 1, n) 
    {
        bool flag = true;
        REP(i, 1, n) if ( a[j][i] + a[k][i] > K ) flag = false;
        if ( flag ) Edge[1][j][k] = Edge[1][k][j] = true;
    }
    Solve(0); Solve(1);
    printf("%lld\n", ans);
    return 0;
}
