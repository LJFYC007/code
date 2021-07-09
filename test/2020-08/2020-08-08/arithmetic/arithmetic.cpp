/***************************************************************
	File name: arithmetic.cpp
	Author: ljfcnyali
	Create time: 2020年08月08日 星期六 11时02分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 150;

int n, m, a[maxn], ans[15], num;

inline void Solve(int x)
{
    int pos = 1;
    REP(i, 1, m) if ( a[i] * 3 > x ) pos = i;
    if ( x <= a[pos] ) 
    {
        ++ num;
        printf("(%d", a[pos]);
        x = a[pos] - x;
        if ( x ) { printf("-"); Solve(x); }
    }
    if ( x < a[pos] * 2 ) 
    {
    }
}

int main()
{
    freopen("arithmetic.in", "r", stdin);
    freopen("arithmetic.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    ans[1] = 1; REP(i, 2, 14) ans[i] = ans[i - 1] * 4;
    m = 14; printf("%d\n", m);
    REP(i, 1, m) printf("%d ", ans[i]); puts("");
    REP(i, 1, n)
    {
        num = 0;
        Solve(a[i]);
        REP(j, 1, num) printf(")");
        puts("");
    }
    return 0;
}
