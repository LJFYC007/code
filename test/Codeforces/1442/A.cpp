/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 14时48分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, a[maxn];
bool pre[maxn], suf[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &n);
        REP(i, 1, n) scanf("%d", &a[i]);
        int sum = 0; bool flag = false;
        REP(i, 2, n)
        {
            if ( sum > a[i] ) { flag = true; break ; }
            sum += max(0, a[i] - a[i - 1]);
        }
        if ( flag ) puts("NO");
        else puts("YES");
    }
    return 0;
}
