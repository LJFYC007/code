/***************************************************************
	File name: P2562.cpp
	Author: ljfcnyali
	Create time: 2019年06月09日 星期日 09时56分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

char s[maxn], ans[maxn];
int n, sum;

inline void Solve(int l, int r)
{
    bool flag1 = true, flag2 = true;
    REP(i, l, r) if ( s[i] == '0' ) flag2 = false; else flag1 = false;
    if ( flag1 == true ) ans[++ sum] = 'A';
    if ( flag2 == true ) ans[++ sum] = 'B';
    if ( flag1 == true || flag2 == true ) return ;
    ans[++ sum] = 'C';
    int Mid = (l + r) / 2;
    Solve(l, Mid);
    Solve(Mid + 1, r);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s);
    n = str(s);
    Solve(0, n - 1);
    REP(i, 1, sum) printf("%c", ans[i]); puts("");
    return 0;
}
