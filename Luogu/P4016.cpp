/***************************************************************
	File name: P4016.cpp
	Author: ljfcnyali
	Create time: 2019年07月15日 星期一 19时21分51秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1010;

int n, a[maxn], s[maxn], sum, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; }
    sum /= n;
    REP(i, 1, n) { a[i] -= sum; s[i] = s[i - 1] + a[i]; }
    sort(s + 1, s + n + 1);
    REP(i, 1, n) ans += abs(s[n / 2 + 1] - s[i]);
    printf("%d\n", ans);
    return 0;
}
