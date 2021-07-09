/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2020年01月17日 星期五 15时27分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 11;

int a[maxn][maxn], sum[maxn][maxn];

int main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    REP(i, 1, 10) REP(j, 1, 10) a[i][j] = 1;
    REP(k, 1, 10)
    {
        REP(i, 1, 10) REP(j, 1, 10) a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];     
        REP(i, 1, 10) REP(j, 1, 10) sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        REP(i, 1, 10) { REP(j, 1, 10) printf("%5d ", sum[i][j]); puts(""); }
        puts("");
    }
    return 0;
}
