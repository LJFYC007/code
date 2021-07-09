/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2021年01月05日 星期二 09时03分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n;
vector<pii> ans;

inline void Build(int now, int k)
{
    -- k; if ( k == 1 ) return ; 
    vector<int> p; p.clear();   
    for ( int i = 2; i * i <= k; ++ i ) while ( k % i == 0 ) { p.push_back(i); k /= i; } 
    if ( k > 1 ) p.push_back(k);

    for ( int i = 0; i < p.size(); ++ i ) 
    {
        ++ n; ans.push_back(pii(n, now));
        Build(n, p[i]);
    }
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int k;
    while ( ~scanf("%d", &k) ) 
    {
        ans.clear();
        n = 1; Build(1, k + 1);
        printf("%d\n", n);
        for ( int i = 0; i < ans.size(); ++ i ) printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
