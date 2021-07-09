/***************************************************************
	File name: sequence.cpp
	Author: ljfcnyali
	Create time: 2019年08月05日 星期一 08时25分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5010;

int n, ans[maxn], sum, sum1, sum2, sum3, p[4][maxn];
char s1[maxn], s2[maxn];

inline void read(int &x)
{
    x = 0; char c = getchar();
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s1);
    scanf("%s", s2);
    REP(i, 1, n) 
    { 
        int x = s1[i - 1] - '0', y = s2[i - 1] - '0';
        sum += y;
        if ( x + y == 0 ) p[1][++ sum1] = i;
        if ( x + y == 1 ) p[2][++ sum2] = i;
        if ( x + y == 2 ) p[3][++ sum3] = i;
    }
    int x = n / 2;
    REP(cnt2, 0, sum2)
    {
        int cnt3 = (sum - cnt2) / 2;
        if ( cnt2 + cnt3 * 2 != sum ) continue ;
        int cnt1 = x - cnt3 - cnt2;
        if ( cnt1 > sum1 || cnt1 < 0 || cnt3 < 0 || cnt3 > sum3 || cnt1 > x || cnt2 > x || cnt3 > x ) continue ;
        int x = 0;
        REP(i, 1, cnt1) ans[++ x] = p[1][i];
        REP(i, 1, cnt2) ans[++ x] = p[2][i];
        REP(i, 1, cnt3) ans[++ x] = p[3][i];
        // REP(i, cnt1 + 1, sum1) ans[++ x] = p[1][i];
        // REP(i, cnt2 + 1, sum2) ans[++ x] = p[2][i];
        // REP(i, cnt3 + 1, sum3) ans[++ x] = p[3][i];
        REP(i, 1, n / 2) printf("%d ", ans[i]); puts(""); return 0;
    }
    puts("-1");
    return 0;
}
