/***************************************************************
	File name: HaHa
	Author: ljfcnyali
	Create time: 2019年11月06日 19时53分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, k, ans, f[maxn];
vector<int> p;

int main()
{
    scanf("%d%d", &n, &k);    
    REP(i, 1, n) 
    { 
        int x; scanf("%d", &x); 
        if ( !f[x % k] ) { p.push_back(x % k); f[x % k] = 1; }
    }
    ans = k;
    for ( auto i : p ) ans = __gcd(ans, i);
    printf("%d\n", k / ans);
    if ( ans == k ) puts("0");
    else { for ( int i = 0; i < k; i += ans ) printf("%d ", i); puts(""); }
    return 0;
}
