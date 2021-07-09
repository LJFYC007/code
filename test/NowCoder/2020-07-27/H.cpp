/***************************************************************
	File name: H.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 13时44分10秒
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
const int Delta = 1000;

int n, f[110][2100][2][2];
char s[maxn];

inline int DFS(int x, int sum, int op1, int op2)
{
    if ( x == n + 1 ) return sum > 0;
    if ( ~f[x][sum + Delta][op1][op2] ) return f[x][sum + Delta][op1][op2];
    int ret = 0; 
    REP(i, 0, 9) REP(j, 0, 9)
    {
        if ( op2 == 1 && j > s[x] - '0' ) continue ;
        if ( op1 == 1 && i > j ) continue ;
        ret += DFS(x + 1, sum + i - j, op1 & (i == j), op2 & (j == s[x] - '0'));
    }
    ret %= Mod;
    f[x][sum + Delta][op1][op2] = ret; return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    memset(f, -1, sizeof(f));
    scanf("%s", s + 1); n = str(s + 1);
    printf("%lld\n", (DFS(1, 0, 1, 1) + Mod) % Mod);
    return 0;
}
