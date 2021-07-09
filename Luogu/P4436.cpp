/***************************************************************
	File name: P4436.cpp
	Author: ljfcnyali
	Create time: 2019年09月03日 星期二 20时01分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1000010;

int n, m, q, s[maxn], L[maxn], R[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &q);
    REP(i, 1, m)
    {
        int x, y; scanf("%d%d", &x, &y);
        s[x] = y;
    }
    for ( int i = n; i >= 1; -- i )
    {
        int l = i, r = i;
        while ( 1 ) 
        {
            while ( l > 1 && (!s[l - 1] || (l <= s[l - 1] && s[l - 1] <= r)) ) -- l;
            while ( r < n && (!s[r] || (l <= s[r] && s[r] <= r)) ) 
            {
                ++ r; l = min(l, L[r]);
                r = R[r];
            }
            if ( l == 1 || (l > s[l - 1] || s[l - 1] > r) ) break ;
        }
        L[i] = l; R[i] = r;
    }
    REP(i, 1, q)
    {
        int s, t; scanf("%d%d", &s, &t);
        if ( s == t || (s < t && R[s] >= t) || (s > t && L[s] <= t) ) puts("YES");
        else puts("NO");
    }
    return 0;
}
