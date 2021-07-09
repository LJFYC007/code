/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年06月18日 星期五 20时09分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], b[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	scanf("%d", &m);
	while ( m -- ) 
	{
		int l, r, x; scanf("%d%d%d", &l, &r, &x);
		REP(i, l, r) b[x + i - l] += a[i];
	}
	REP(i, 1, n) printf("%d\n", b[i]);
    return 0;
}
