/***************************************************************
	File name: tidati.cpp
	Author: ljfcnyali
	Create time: 2020年12月19日 星期六 10时22分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, a[maxn], ans[maxn];

int main()
{
    scanf("%d", &k); 
    a[1] = n = 1;    
    while ( a[n] + a[n] <= k ) { ++ n; a[n] = a[n - 1] + a[n - 1]; ans[n - 1] = n - 1; }
    REP(i, 1, n - 1) if ( (k >> i - 1) & 1 ) 
        ans[n ++] = i;
    printf("%d\n", n);
    REP(i, 1, n - 1) printf("%d ", ans[i]); puts("");
    return 0;
}
