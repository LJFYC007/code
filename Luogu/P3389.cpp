/***************************************************************
	File name: P3389.cpp
	Author: ljfcnyali
	Create time: 2019年08月28日 星期三 14时20分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

int n;
double a[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) REP(j, 1, n + 1) scanf("%lf", &a[i][j]);
    REP(i, 1, n)
    {
        int Max = i;
        REP(j, i + 1, n) if ( abs(a[j][i]) > abs(a[Max][i]) ) Max = j;
        REP(j, 1, n + 1) swap(a[i][j], a[Max][j]);
        if ( !a[i][i] ) { puts("No Solution"); return 0; }
        REP(j, 1, n) if ( j != i ) REP(k, i + 1, n + 1) a[j][k] -= a[j][i] * a[i][k] / a[i][i];
    }
    REP(i, 1, n) printf("%.2lf\n", a[i][n + 1] / a[i][i]);
    return 0;
}
