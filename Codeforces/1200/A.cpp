/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年08月11日 星期日 20时28分03秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 11;

int n, ans[maxn];
char c;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); getchar();
    REP(i, 1, n)
    {
        c = getchar();
        if ( c == 'L' ) { REP(j, 0, 9) if ( !ans[j] ) { ans[j] = 1; break ; } }
        else if ( c == 'R' ) { for ( int j = 9; j >= 0; -- j ) if ( !ans[j] ) { ans[j] = 1; break ; } }
        else ans[c - '0'] = 0;
    }
    REP(i, 0, 9) printf("%d", ans[i]); puts("");
    return 0;
}
