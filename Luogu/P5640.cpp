/***************************************************************
	File name: P5640.cpp
	Author: ljfcnyali
	Create time: 2019年11月10日 星期日 19时27分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1000010;

int n, m, s[maxn], ans;
vector<int> a, b;

inline int get(int x)
{
    if ( x <= b.size() ) return b[b.size() - x];
    return a[x - b.size()];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &s[i]);
    a.push_back(0);
    REP(len, 1, m)
    {
        int opt, c; scanf("%d%d", &opt, &c);
        if ( opt == 1 ) a.push_back(c);
        else b.push_back(c);
        int L = 0, R = len + 1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( get(Mid) == s[Mid] ) { ans = len - Mid; L = Mid + 1; }
            else R = Mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
