/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年06月15日 星期六 09时58分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

char s[maxn];
int p[maxn], len, n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    char c = getchar();
    while ( c >= 'a' && c <= 'z' ) { s[len ++] = '#'; s[len ++] = c; c = getchar(); ++ n;}
    s[len ++] = '#';
    int pos = 0, MaxRight = 0;
    REP(i, 0, len - 1)
    {
        if ( i < MaxRight ) p[i] = min(p[2 * pos - i], MaxRight - i);
        else p[i] = 1;
        while ( 0 <= i - p[i] && i + p[i] < len && s[i - p[i]] == s[i + p[i]] ) ++ p[i];
        if ( i + p[i] > MaxRight )
        {
            pos = i; MaxRight = i + p[i];
        }
    }
    REP(i, 0, len - 1) -- p[i];
//    printf("%s\n", s);
//    REP(i, 0, len - 1) printf("%d", p[i]); puts("");
    int ans = 0;
    REP(i, 0, len - 1) if ( i - p[i] <= 1 ) ans = max(ans, p[i]);
    printf("%d\n", n - ans);
    return 0;
}
