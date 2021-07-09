/***************************************************************
	File name: P2375.cpp
	Author: ljfcnyali
	Create time: 2019年08月20日 星期二 11时17分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;
const LL Mod = 1e9 + 7;

int Next[maxn], T, n, num[maxn];
LL ans;
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T --  )
    {
        scanf("%s", s + 1); n = str(s + 1);
        int j = 0;
        num[1] = 1;
        REP(i, 2, n)
        {
            while ( j && s[j + 1] != s[i] ) j = Next[j];
            if ( s[j + 1] == s[i] ) ++ j;
            Next[i] = j; num[i] = num[j] + 1;
        }
        j = 0; ans = 1;
        REP(i, 2, n)
        {
            while ( j && s[j + 1] != s[i] ) j = Next[j];
            if ( s[j + 1] == s[i] ) ++ j;
            while ( j * 2 > i ) j = Next[j];
            ans = (ans * (num[j] + 1)) % Mod;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
