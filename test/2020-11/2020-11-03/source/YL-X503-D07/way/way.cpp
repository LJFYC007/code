/***************************************************************
	File name: way.cpp
	Author: ljfcnyali
	Create time: 2020年11月03日 星期二 09时05分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 1e4;

int T, n, q, a[maxn];

int main()
{
    freopen("way.in", "r", stdin);
    freopen("way.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &q);
        REP(i, 0, n - 1) scanf("%d", &a[i]); 
        REP(i, n, N) a[i] = 0;
        REP(i, 0, N) REP(j, max(n, i + 1), i + a[i]) ++ a[j];
        REP(i, 0, N)
        {
            cout << a[i] - n + 1 << " ";
            if ( i % n == n - 1 ) puts("");
        }
        REP(i, 1, q) { int x; scanf("%d", &x); printf("%d ", a[x]); }
        puts("");
    }
    return 0;
}
