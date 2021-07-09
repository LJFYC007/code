#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
 
const int maxn = 2000010;
 
char s1[maxn], s2[maxn];
int len1, len2, ans, last, f1[maxn], f2[maxn];
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s1 + 1); len1 = str(s1 + 1);
    scanf("%s", s2 + 1); len2 = str(s2 + 1);
    int j = 1;
    REP(i, 1, len1)
    {
        if ( s1[i] == s2[j] ) ++ j;
        if ( j == len2 + 1 ) { ans = len1 - i; break ; }
    }
    j = len2;
    for ( int i = len1; i >= 1; -- i )
    {
        if ( s1[i] == s2[j] ) -- j;
        if ( j == 0 ) { ans = max(ans, i - 1); break ; }
    }
    j = 1;
    REP(i, 1, len1)
    {
        if ( s1[i] == s2[j] ) { f1[j] = i; ++ j; }
        if ( j == len2 + 1 ) break ;
    }
    j = len2;
    for ( int i = len1; i >= 1; -- i )
    {
        if ( s1[i] == s2[j] ) { f2[j] = i; -- j; }
        if ( j == 0 ) break ;
    }
    REP(j, 0, len2) ans = max(ans, f2[j + 1] - f1[j] - 1);
    printf("%d\n", ans);
    return 0;
}
