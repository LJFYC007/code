/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 19时58分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int n, k, sum, m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &m);
    REP(i, 1, n - 1) { int x; scanf("%d", &x); sum += x; }
    m = m * n - sum;
    if ( m > k ) puts("-1");
    else if ( m < 0 ) puts("0");
    else printf("%d\n", m);
    return 0;
}
