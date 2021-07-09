/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 08时53分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e7 + 10;

int T, Next[maxn], n, s[maxn], t[maxn], x;
LL a, b, ans;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%lld%lld", &a, &b); n = Next[1] = 0;
        char c = getchar(); 
        while ( c < '0' || c > '9' ) c = getchar();
        while ( (c >= '0' && c <= '9') || c == '.' ) { t[++ n] = c - '0'; c = getchar(); }
        REP(i, 1, n) 
        {
            s[i] = t[n - i + 1];
            if ( s[i] == '.' - '0' ) x = i;
        }
        ans = max(0ll, a - b);
        for ( int i = 2, j = 0; i < x; ++ i )
        {
            while ( j && s[i] != s[j + 1] ) j = Next[j];
            if ( s[i] == s[j + 1] ) ++ j;
            Next[i] = j;
            ans = max(ans, i * a - b * (i - Next[i]));
        }
        printf("%lld\n", ans);
    }
    return 0;
 }
