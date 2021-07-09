/***************************************************************
	File name: telegram.cpp
	Author: ljfcnyali
	Create time: 2020年10月04日 星期日 08时55分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510 * 510;

int n, m, b[maxn], a[maxn], ret, sum = 0;
multiset<int> Set;
vector<int> ans[maxn];
map<int, bool> Map;

inline void Check(int x)
{
    if ( x <= 0 || Map.count(x) ) return ; Map[x] = true;
    a[1] = x; Set.clear();
    REP(i, 1, m) Set.insert(b[i]);
    REP(i, 2, n)
    {
        a[i] = *Set.begin() - a[1];
        REP(k, 1, i - 1)
        {
            auto it = Set.lower_bound(a[k] + a[i]);
            if ( *it != a[k] + a[i] ) return ;
            Set.erase(it);
        }
    }
    REP(i, 2, n) if ( a[i - 1] > a[i] ) return ;
    ++ ret; REP(i, 1, n) ans[ret].push_back(a[i]);
}

signed main()
{
    freopen("telegram.in", "r", stdin);
    freopen("telegram.out", "w", stdout);
    scanf("%lld", &n); m = n * (n - 1) / 2;
    REP(i, 1, m) scanf("%lld", &b[i]);
    sort(b + 1, b + m + 1);
    REP(i, 3, n) Check((b[1] + b[2] - b[i]) / 2);
    printf("%lld\n", ret);
    REP(i, 1, ret) { for ( auto j : ans[i] ) printf("%lld ", j); puts(""); }
    return 0;
}
