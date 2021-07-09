/***************************************************************
	File name: ttds.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 11时39分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 1e5;
const int Mod = 998244353;

int n, k, b, a[maxn], c[maxn];
vector<int> p[maxn];

inline bool operator <(vector<int> a, vector<int> b)
{
    int len = min(a.size(), b.size());
    REP(i, 0, len - 1) 
    {
        if ( a[i] < b[i] ) return true;
        if ( a[i] > b[i] ) return false;
    }
    return a.size() < b.size();
}

signed main()
{
    freopen("ttds.in", "r", stdin);
    freopen("ttds1.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &k, &b);
    REP(i, 1, n) scanf("%lld", &a[i]);
    if ( n > 20 ) 
    {
        int N = n; multiset<int> Fuck;
        set<pii> Set; REP(i, 1, n) { Fuck.insert(a[i]); Set.insert(pii(a[i], i)); }
        while ( n > 20 ) 
        {
            int x = *(-- Fuck.end()); Fuck.erase(Fuck.find(x));
            Set.erase(Set.lower_bound(pii(x, 0))); -- n;
        }
        for ( auto it : Set ) c[it.second] = it.first;
        n = 0; REP(i, 1, N) if ( c[i] ) a[++ n] = c[i];
    }
    REP(i, 1, (1 << n) - 1) REP(j, 1, n) if ( (i >> j - 1) & 1 ) p[i].push_back(a[j]);
    sort(p + 1, p + (1 << n));
    REP(i, 1, k)
    {
        int sum = 0;
        for ( auto it : p[i] ) sum = (sum * b + it) % Mod;
        printf("%lld\n", sum);
    }
    return 0;
}
