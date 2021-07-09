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
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510 * 510;

int n, m, b[maxn], a[maxn], ret;
multiset<int> Set;
vector<int> ans[maxn];

int main()
{
    freopen("telegram.in", "r", stdin);
    freopen("telegram.out", "w", stdout);
    scanf("%d", &n); m = n * (n - 1) / 2;
    REP(i, 1, m) scanf("%d", &b[i]);
    sort(b + 1, b + m + 1);
    for ( int j = b[1] / 2; j >= 1; -- j )
    {
        a[1] = j; Set.clear();
        REP(i, 1, m) Set.insert(b[i]);
        REP(i, 2, n)
        {
            a[i] = *Set.begin() - a[1];
            REP(k, 1, i - 1) 
            {
                auto it = Set.lower_bound(a[k] + a[i]);
                if ( *it != a[k] + a[i] ) goto Next ;
                Set.erase(it);
            }
        }
        REP(i, 2, n) if ( a[i - 1] > a[i] ) goto Next ;
        ++ ret; REP(i, 1, n) ans[ret].push_back(a[i]);
Next : ; 
    }
    printf("%d\n", ret);
    REP(i, 1, ret) { for ( auto j : ans[i] ) printf("%d ", j); puts(""); }
    return 0;
}
