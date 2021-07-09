/***************************************************************
	File name: P1638.cpp
	Author: ljfcnyali
	Create time: 2019年06月11日 星期二 08时16分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 2010;

int num[maxn], n, m, ans1, ans2, ans = 0x3f3f3f3f, sum;
int a[1000010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    int l = 1, r = 0;
    while ( 1 ) 
    {
        while ( sum < m && r <= n ) { scanf("%d", &a[++ r]); ++ num[a[r]]; if ( num[a[r]] == 1 ) ++ sum; }
        if ( r > n ) break ;
        if ( r - l + 1 < ans ) { ans = r - l + 1; ans1 = l; ans2 = r; }
        -- num[a[l]];
        while ( num[a[l]] != 0 ) 
        {
            -- num[a[++ l]]; 
            if ( r - l + 1 < ans ) { ans = r - l + 1; ans1 = l; ans2 = r; }
        }
        -- sum; ++ l;
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}
