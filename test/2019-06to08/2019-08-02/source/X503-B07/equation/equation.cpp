/***************************************************************
	File name: equation.cpp
	Author: ljfcnyali
	Create time: 2019年08月02日 星期五 09时44分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 10;
const int Mod = 1e9 + 7;

int c[maxn], a[maxn], n, k, ans;
bool flag;

inline void DFS1(int x, int sum, int m)
{
    sum %= m;
    if ( sum == 1 ) { flag = true; return ; }
    if ( x == n + 1 ) return ;
    REP(i, 0, m - 1) DFS1(x + 1, sum + i * c[x], m);
}

inline bool pd(int m)
{
    flag = false;
    DFS1(1, 0, m);
    return flag;
}

inline void DFS(int x, int m)
{
    if ( x == n + 1 ) { if ( pd(m) ) ++ ans; ans %= Mod; return ; }
    if ( c[x] == -1 ) { REP(i, 0, m - 1) { c[x] = i; DFS(x + 1, m); } c[x] = -1; }
    else DFS(x + 1, m);
}

int main()
{
    freopen("equation.in", "r", stdin);
    freopen("equation.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &c[i]);
    ans = 1;
    REP(i, 2, k) DFS(1, i);
    printf("%d\n", ans);
    return 0;
}
