/***************************************************************
	File name: AGC030C.cpp
	Author: ljfcnyali
	Create time: 2021年01月27日 星期三 16时39分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int K, a[maxn][maxn], n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &K);
    // if ( !K ) 
    if ( K <= 500 ) 
    {
        n = K;
        REP(i, 1, n) REP(j, 1, n) a[i][j] = (i + j - 2) % K + 1;
    }
    else
    {
        n = ((K - 1) / 4 + 1) * 2;
        REP(i, 1, n) REP(j, 1, n) a[i][j] = (i + j - 2) % n + 1 + (i & 1 ? 0 : n);
        REP(i, 1, n) REP(j, 1, n) if ( a[i][j] > K ) a[i][j] -= n; 
    }
    printf("%d\n", n);
    REP(i, 1, n) { REP(j, 1, n) printf("%d ", a[i][j]); puts(""); }
    return 0;
}
