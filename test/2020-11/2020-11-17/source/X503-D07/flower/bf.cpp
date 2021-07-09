/***************************************************************
	File name: flower.cpp
	Author: ljfcnyali
	Create time: 2020年11月17日 星期二 09时21分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn];

int main()
{
    freopen("flower.in", "r", stdin);
    freopen("flower1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m)
    {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        int Max = 0;
        REP(j, l, r) Max = max(Max, a[j] % k);
        printf("%d\n", Max);
    }
    return 0;
}
