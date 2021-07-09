/***************************************************************
	File name: HDU1028.cpp
	Author: ljfcnyali
	Create time: 2019年12月17日 星期二 10时50分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 150;

int f[maxn], g[maxn], a[maxn], n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        REP(i, 0, n) f[i] = 1;
        REP(i, 2, n)
        {
            REP(j, 0, n) if ( j % i == 0 ) g[j] = 1; else g[j] = 0;
            mem(a);
            REP(j, 0, n) REP(k, 0, n - j) a[j + k] += f[j] * g[k];
            REP(j, 0, n) f[j] = a[j];
        }
        printf("%d\n", f[n]);
    }
    return 0;
}
