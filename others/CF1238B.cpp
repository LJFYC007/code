/***************************************************************
	File name: CF1238B.cpp
	Author: ljfcnyali
	Create time: 2019年10月10日 星期四 19时10分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int T, n, r, a[maxn], ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &r);
        REP(i, 1, n) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        int sum = 0; ans = 0;
        for ( int i = n; i >= 1; -- i ) 
        {
            if ( a[i] <= sum ) break ; 
            while ( a[i - 1] == a[i] ) -- i;
            ++ ans; sum += r;
        }
        printf("%d\n", ans);
    }
    return 0;
}
