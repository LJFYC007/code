/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年10月13日 星期日 16时48分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int T, n;
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
        scanf("%d", &n); scanf("%s", s + 1);
        int ans = n, sum = 0;
        REP(i, 1, n)
            if ( s[i] == '1' )
            {
                ans = max(ans, i + i);
                ans = max(ans, (n - i + 1) * 2);
                ans = max(ans, n + 1);
            }
        printf("%d\n", ans);
    }
    return 0;
}
