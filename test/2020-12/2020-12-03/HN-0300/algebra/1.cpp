/***************************************************************
	File name: algebra.cpp
	Author: ljfcnyali
	Create time: 2020年12月03日 星期四 08时01分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, m, k, a[200][10], cnt, ans, b[10];

inline void DFS1(int x, int num)
{
    if ( num > k || num + m - x + 1 < k ) return ;
    if ( x == m + 1 ) 
    {
        ++ cnt; REP(i, 1, m) a[cnt][i] = b[i];
        return ;
    }
    b[x] = 0; DFS1(x + 1, num);
    b[x] = 1; DFS1(x + 1, num + 1);
}

inline void DFS2(int x)
{
    REP(i, 1, m) if ( b[i] > k || b[i] + n - x + 1 < k ) return ;
    if ( x == n + 1 ) { ++ ans; return ; } 
    REP(i, 1, cnt)
    {
        REP(j, 1, m) b[j] += a[i][j];
        DFS2(x + 1);
        REP(j, 1, m) b[j] -= a[i][j];
    }
}

int main()
{
    freopen("algebra.in", "r", stdin);
    freopen("algebra.out", "w", stdout);
    // scanf("%d%d%d", &n, &m, &k);
    REP(i, 1, 6) REP(j, 1, 6) REP(o, 1, min(i, j))
    {
        n = i; m = j; k = o;
        cnt = ans = 0;
    DFS1(1, 0);
    mem(b); DFS2(1);
        if ( ans > 0 )
            printf("%d ", ans);
        if ( j == i && o == i ) puts("");
    }
    return 0;
}
