/***************************************************************
	File name: P4384.cpp
	Author: ljfcnyali
	Create time: 2020年05月29日 星期五 19时22分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m;
char s[maxn];
vector<int> p;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m); scanf("%s", s + 1);
    REP(o, 1, m)
    {
        int l, r, len, ans; scanf("%d%d", &l, &r); len = r - l + 1;
        p.clear();
        REP(i, 1, n - len + 1)
        {
            bool flag = true;
            REP(j, i, i + len - 1) if ( s[j] != s[l - i + j] ) { flag = false; break ; }
            if ( flag == true ) p.push_back(i);
        }
        ans = (n - 1) * (n - 2) / 2;
        int k = p.size();
        puts("");
        for ( auto i : p ) printf("%d ", i); puts("");
        
        if ( (len == 1) || (len == 2 && k >= 3) ) 
        {
            printf("%d\n", ans);
            continue ;
        }
        if ( len == 2 && k == 2 ) { -- ans; printf("%d\n", ans); continue ; }
        if ( k == 1 ) 
        {
            int L = n - (p[0] + len - 2) - 1, R = n - p[0] - 1;
            ans -= (L + R) * (len - 1) / 2;
            ans -= (p[0] - 1) * (len - 1);
            printf("%d\n", ans);
            continue ;
        }

        if ( p[k - 1] < p[0] + len - 1 )
            REP(i, 0, k - 1) ans -= (p[i] - (i == 0 ? 0 : p[i - 1])) * (p[i] + len - 1 - p[k - 1]);
        printf("%d\n", ans);
    }
    return 0;
}
