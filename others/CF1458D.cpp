/***************************************************************
	File name: CF1458D.cpp
	Author: ljfcnyali
	Create time: 2021年01月04日 星期一 10时09分11秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;
const int Delta = 500000;

int T, n, a[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%s", s + 1); n = str(s + 1);
        REP(i, 0, n + n) a[i] = 0;
        int sum = Delta;
        REP(i, 1, n) if ( s[i] == '1' ) ++ a[sum ++]; else ++ a[-- sum];
        int now = Delta;
        REP(i, 1, n)
            if ( a[now - 1] && (!a[now] || a[now - 1] > 1) ) { printf("0"); -- a[-- now]; }
            else { printf("1"); -- a[now ++]; }
        puts("");
    }
    return 0;
}
