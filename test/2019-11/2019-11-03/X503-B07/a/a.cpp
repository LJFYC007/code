/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年11月03日 星期日 08时18分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;
const int INF = 2147483647;

int n, m, a[maxn][maxn], b[maxn][maxn];

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 0, n + 1) REP(j, 0, m + 1) a[i][j] = b[i][j] = INF;
    REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]); 
    for ( int i = n; i >= 1; -- i ) REP(j, 1, m) a[i][j] = min(a[i][j], a[i + 1][j]);
    REP(i, 1, n) for ( int j = m; j >= 1; -- j ) 
    {
        b[i][j] = a[i][j];
        if ( i > 1 ) b[i][j] = min(b[i][j], b[i - 1][j + 1]);
        else b[i][j] = min(b[i][j], b[i][j + 1]);
    }
    REP(i, 1, n) REP(j, 1, m) printf("%d%c", b[i][j], j == m ? '\n' : ' '); 
    return 0;
}
