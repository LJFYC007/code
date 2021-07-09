/***************************************************************
	File name: qsort.cpp
	Author: ljfcnyali
	Create time: 2019年11月08日 星期五 08时50分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1000010;

int n, k, tot;
pii a[maxn];

int main()
{
    freopen("qsort.in", "r", stdin);
    freopen("qsort.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) REP(j, i + 1, n) if ( __gcd(i, j) == 1 ) a[++ tot] = pii(i, j);
    sort(a + 1, a + tot + 1, [](pii x, pii y) { return x.first * y.second < x.second * y.first; });
    printf("%d %d\n", a[k].first, a[k].second);
    return 0;
}
