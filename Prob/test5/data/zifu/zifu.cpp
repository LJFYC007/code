/***************************************************************
	File name: zifu.cpp
	Author: ljfcnyali
	Create time: 2019年11月02日 星期六 15时11分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, ans, p[30];
char s[maxn];

int main()
{
    // freopen("zifu.in", "r", stdin);
    // freopen("zifu.out", "w", stdout);
    scanf("%s", s + 1); n = str(s + 1);
    REP(i, 1, n) ++ p[s[i] - 'a' + 1];
    sort(p + 1, p + 27);
    for ( int i = 26; i >= 1; -- i ) ans += p[i] * i;
    printf("%d\n", ans);
    return 0;
}
