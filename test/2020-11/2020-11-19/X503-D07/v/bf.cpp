/***************************************************************
	File name: v.cpp
	Author: ljfcnyali
	Create time: 2020年11月19日 星期四 09时19分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10; 

int n, k;
double f[maxn];
char s[maxn];

int main()
{
    freopen("v.in", "r", stdin);
    freopen("v.out", "w", stdout);
    scanf("%d%d", &n, &k); scanf("%s", s + 1);
    REP(i, 0, (1 << n) - 1)
    {
        int num = 0, sum = 0;
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) { ++ num; sum += s[j] == 'W'; }
        if ( num == k ) f[i] = sum;
    }
    for ( int i = (1 << n) - 1; i >= 0; -- i ) 
    {
        int num = 0;
        REP(j, 1, n) if ( (i >> j - 1) & 1 ) ++ num; 
        if ( num >= k ) continue ;
        int l = 1, r = n;
        REP(j, 1, n - num)
        {
            while ( (i >> l - 1) & 1 ) ++ l;
            while ( (i >> r - 1) & 1 ) -- r;
            f[i] += max(f[i | (1 << l - 1)], f[i | (1 << r - 1)]) / (n - num);
            ++ l; -- r;
        }
    }
    printf("%.6lf\n", f[0]);
    return 0;
}
