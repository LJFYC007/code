/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 20时41分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;

int n, a[maxn], T, m, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d%d", &n, &m, &k);
        REP(i, 1, n) scanf("%d", &a[i]);
        REP(i, 1, n - 1)
        {
            int x = max(a[i + 1] - k, 0);
            if ( a[i] >= x ) 
            {
                m += a[i] - x;
                continue ;
            }
            if ( a[i] + m < x ) { puts("NO"); goto finish; }
            m -= x - a[i];
        }
        puts("YES");
finish : ; 
    }
    return 0;
}
