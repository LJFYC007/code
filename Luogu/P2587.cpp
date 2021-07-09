/***************************************************************
	File name: P2587.cpp
	Author: ljfcnyali
	Create time: 2019年06月27日 星期四 14时25分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int a[maxn], b[maxn], n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n) scanf("%d", &b[i]);
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    int l1 = 1, l2 = 1, r1 = n, r2 = n;
    while ( l1 <= r1 && l2 <= r2 ) 
    {
        if ( a[l1] > b[l2] ) { ans += 2; ++ l1; ++ l2; }
        else if ( a[r1] > b[r2] ) { ans += 2; -- r1; -- r2; }
        else { ans += a[l1] == b[r2]; ++ l1; -- r2; }
    }
    printf("%d ", ans);
    ans = 0;
    l1 = 1, l2 = 1, r1 = n, r2 = n;
    while ( l1 <= r1 && l2 <= r2 ) 
    {
        if ( b[l1] > a[l2] ) { ans += 2; ++ l1; ++ l2; }
        else if ( b[r1] > a[r2] ) { ans += 2; -- r1; -- r2; }
        else { ans += b[l1] == a[r2]; ++ l1; -- r2; }
    }
    printf("%d\n", 2 * n - ans);
    return 0;
}
