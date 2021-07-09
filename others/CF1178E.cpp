/***************************************************************
	File name: CF1178E.cpp
	Author: ljfcnyali
	Create time: 2019年10月16日 星期三 20时30分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int ans = 0, n, tot1, tot2;
char s[maxn], ans1[maxn], ans2[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1);
    n = str(s + 1);
    int L = 1, R = n;
    if ( n == 2 ) { cout << s[1] << endl; return 0; }
    while ( L <= R ) 
    {
        if ( s[L] == s[R] ) 
        {
            ans1[++ tot1] = s[L];
            if ( L < R ) ans2[++ tot2] = s[R];
            ++ L; -- R; ans += L < R ? 2 : 1;
        }
        else if ( s[L] == s[R - 1] ) 
        {
            ans1[++ tot1] = s[L];
            if ( L != R - 1 ) ans2[++ tot2] = s[R - 1];
            ++ L; R = R - 2; ans += 2;
        }
        else if ( s[L + 1] == s[R] ) 
        {
            ans1[++ tot1] = s[L + 1];
            if ( L + 1 != R ) ans2[++ tot2] = s[R];
            L = L + 2; -- R; ans += 2;
        }
        else { ++ L; -- R; }
    }
    REP(i, 1, tot1) printf("%c", ans1[i]);
    for ( int i = tot2; i >= 1; -- i ) printf("%c", ans1[i]); puts("");
    return 0;
}
