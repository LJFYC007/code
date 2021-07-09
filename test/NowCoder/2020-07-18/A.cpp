/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年07月18日 星期六 12时31分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;

int T, n, num1, num2, ans;
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
        scanf("%d", &n); ans = num1 = num2 = 0;
        scanf("%s", s + 1);
        REP(i, 1, n) 
        {
            if ( s[i] == '2' || s[i] == '3' ) ++ ans;
            else if ( s[i] == '0' ) ++ num1;
            else ++ num2;
        }
        
        int val = 0;
        REP(i, 1, n)
        {
            if ( s[i] == '2' || s[i] == '3' ) continue ;
            if ( !num1 ) break ;
            if ( s[i] == '0' ) 
            {
                if ( val ) -- val;
                else -- num1;
            }
            else { ++ val; -- num1; -- num2; ++ ans; }
        }
        ans += num2 / 2;
        printf("%d\n", ans);
    }
    return 0;
}
