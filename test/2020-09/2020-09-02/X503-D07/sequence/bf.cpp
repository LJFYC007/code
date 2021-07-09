/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 19时14分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;

inline int f(int x)
{
    int ret = 0;
    while ( x ) { ++ ret; x /= 10; }
    return ret;
}

int main()
{
    freopen("sequence.in", "r", stdin);
    freopen("sequence1.out", "w", stdout);
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) REP(j, i + 1, n) ans += f(a[i] + a[j]);
    printf("%d\n", ans);
    return 0;
}
