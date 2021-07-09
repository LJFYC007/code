/***************************************************************
	File name: kettle.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 08时32分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, k, a[maxn], ans;

int main()
{
    freopen("kettle.in", "r", stdin);
    freopen("kettle.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) { scanf("%d", &a[i]); a[i] += a[i - 1]; }
    REP(i, 1, n) ans = max(ans, a[i] - a[max(0, i - k - 1)]);
    printf("%d\n", ans);
    return 0;
}
