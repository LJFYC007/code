/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2021年01月05日 星期二 09时31分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, q, tax[310][maxn], a[maxn];
char s[maxn], t[maxn];

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) a[i] = a[i - 1] + (s[i] == '1');
    REP(i, 1, 300) REP(j, i, n) ++ tax[i][a[j] - a[j - i]];
    scanf("%d", &q); 
    while ( q -- ) 
    {
        scanf("%s", t + 1); int m = str(t + 1);
        int sum = 0; REP(j, 1, m) if ( t[j] == '1' ) ++ sum;
        if ( m <= 300 ) { printf("%d\n", tax[m][sum]); continue ; } 
        int ans = 0;
        REP(j, m, n) if ( a[j] - a[j - m] == sum ) ++ ans;
        printf("%d\n", ans);
    }
    return 0;
}
