/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月09日 星期二 08时14分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;
const int INF = 0x3f3f3f3f;

int n, a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(m, 1, n)
    {
        sort(a + 1, a + m + 1);
        int x = 0;
        REP(i, 1, m) 
        {
            if ( a[i] > x ) ++ x;
            else if ( a[i] < x ) -- x;
        }
        printf("%d\n", x);
    }
    return 0;
}
