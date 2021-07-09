/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 08时18分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3010;

int n, m, a[maxn][maxn], b[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m); m = min(m, 14);
    int tot = 0;
    REP(i, 0, (1 << m) - 1)
    {
        int ret = 0; REP(j, 1, m) if ( (i >> j - 1) & 1 ) ++ ret;
        if ( ret == m / 2 ) b[++ tot] = i;
    }
    REP(i, 2, n) 
    {
        scanf("%s", s + 1);
        REP(j, 1, i - 1) 
            if ( s[j] == '1' ) 
            {
                REP(k, 1, m) 
                    if ( ((b[i] >> k - 1) & 1) && !((b[j] >> k - 1) & 1) ) { printf("%c", 'a' + k - 1); break ; }
            }
            else
            {
                REP(k, 1, m) 
                    if ( !((b[i] >> k - 1) & 1) && ((b[j] >> k - 1) & 1) ) { printf("%c", 'a' + k - 1); break ; }
            }
        puts("");
    }
    return 0;
}
