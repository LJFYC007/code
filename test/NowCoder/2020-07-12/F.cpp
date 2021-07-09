/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 12时11分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

char s[maxn], t[maxn];
int n, m, a[maxn], b[maxn];
bool vis[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%s", s + 1) )
    {
        n = str(s + 1); scanf("%s", t + 1); m = str(t + 1);
        bool flag = false;
        if ( n < m ) { swap(n, m); swap(s, t); flag = true; }
        REP(i, 1, n) s[i + n] = s[i]; n *= 2;
        REP(i, 1, n) vis[i] = a[i] = b[i] = 0;
        int L = 0, R = 0;
        a[1] = m;
        REP(i, 2, m)
        {
            if ( i <= R ) a[i] = min(R - i + 1, a[i - L + 1]);
            while ( i + a[i] <= m && t[a[i] + 1] == t[i + a[i]] ) ++ a[i];
            if ( i + a[i] - 1 > R ) { L = i; R = i + a[i] - 1; }
        }
        L = R = 0;
        REP(i, 1, n)
        {
            if ( i <= R ) b[i] = min(R - i + 1, a[i - L + 1]);
            while ( i + b[i] <= n && t[b[i] + 1] == s[i + b[i]] ) ++ b[i];
            if ( i + b[i] - 1 > R ) { L = i; R = i + b[i] - 1; }
        }

        int now = 1;     
        while ( 1 ) 
        {
            if ( vis[now] ) { puts("="); goto Finish; } vis[now] = true;
            int x = b[now];
            if ( x == m ) now = (now + m - 1) % (n / 2) + 1;
            else 
            {
                if ( s[now + x] < t[x + 1] ) 
                {
                    if ( !flag ) puts("<");
                    else puts(">");
                }
                else 
                {
                    if ( !flag ) puts(">");
                    else puts("<");
                }
                goto Finish; 
            }
        }
Finish : ; 
    }
    return 0;
}
