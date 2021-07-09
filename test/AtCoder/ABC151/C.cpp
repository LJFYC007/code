/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年01月12日 星期日 19时58分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, sum1, sum2, p[maxn];
bool flag[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, m)
    {
        int x; scanf("%d %s", &x, s);
        if ( s[0] == 'A' ) 
        {
            if ( !flag[x] ) ++ sum1;
            flag[x] = true;
        }
        else
        {
            if ( !flag[x] ) ++ p[x];
        }
    }
    REP(i, 1, n) if ( flag[i] ) sum2 += p[i];
    printf("%d %d\n", sum1, sum2);
    return 0;
}
