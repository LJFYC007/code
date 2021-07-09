/***************************************************************
	File name: P3887.cpp
	Author: ljfcnyali
	Create time: 2019年06月18日 星期二 14时27分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[5][maxn], n[5], m, sum[5];
long long ans;

inline int cmp(int x, int y)
{
    return x > y;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 1, 4) scanf("%d", &n[i]);
    REP(i, 1, 4) REP(j, 1, n[i]) scanf("%d", &a[i][j]);
    REP(i, 1, 4) sort(a[i] + 1, a[i] + n[i] + 1, cmp);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int A, B, C; scanf("%d%d%d", &A, &B, &C);
        ans = a[1][++ sum[1]];
        REP(j, 1, A) ans += a[2][++ sum[2]];
        REP(j, 1, B) ans += a[3][++ sum[3]];
        REP(j, 1, C) ans += a[4][++ sum[4]];
        printf("%.2lf\n", ans / 11.0);
    }
    return 0;
}
