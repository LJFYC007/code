/***************************************************************
	File name: CF799D.cpp
	Author: ljfcnyali
	Create time: 2019年09月25日 星期三 21时25分52秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 100010;

int n, a, b, w, h, A[maxn], ans = 0x3f3f3f3f, cnt;

inline int cmp(int a, int b) { return a > b; }

inline void DFS(int x, int y, int i, int num)
{
    ++ cnt; if ( cnt > 10000000 ) return ;
    if ( num >= ans ) return ;
    if ( (x >= a && y >= b) || (x >= b && y >= a) ) { ans = num; return ; }
    if ( i > n ) return ;
    if ( y < b ) DFS(x, y * A[i], i + 1, num + 1);
    if ( x < a ) DFS(x * A[i], y, i + 1, num + 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d%d%d", &a, &b, &h, &w, &n);
    REP(i, 1, n) scanf("%d", &A[i]);
    sort(A + 1, A + n + 1, cmp);
    DFS(w, h, 1, 0);
    printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
    return 0;
}
