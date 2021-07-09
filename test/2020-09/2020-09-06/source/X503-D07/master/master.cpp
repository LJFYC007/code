/***************************************************************
	File name: master.cpp
	Author: ljfcnyali
	Create time: 2020年09月06日 星期日 14时17分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;
const int seed = 107;

int k, n, m, len[maxn], w[maxn], a1[maxn];
unordered_map<int, int> ccc;
struct node { int x1, x2; } a[maxn], b[maxn];
vector<pii> p;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline int Solve(node *a, int n)
{
    ccc.clear(); p.clear(); 
    REP(i, 1, k) 
    { 
        p.push_back(pii(a[i].x1, i)); 
        p.push_back(pii(a[i].x2, i)); 
        w[i] = rand();
    }
    p.push_back(pii(0, 0)); p.push_back(pii(n, 0));
    sort(p.begin(), p.end());
    int sum = 0, ans = 0; 
    for ( int i = 1; i < p.size(); ++ i )
    {
        ccc[sum] += p[i].first - p[i - 1].first;
        sum ^= w[p[i].second];
    }
    for ( auto i : ccc ) ans = max(ans, i.second);
    return ans;
}

signed main()
{
    freopen("master.in", "r", stdin);
    freopen("master.out", "w", stdout);
    scanf("%d%d%d", &k, &n, &m);
    REP(i, 1, k) 
        scanf("%d%d%d%d", &a[i].x1, &b[i].x1, &a[i].x2, &b[i].x2); 
    printf("%lld\n", (LL)Solve(a, n) * Solve(b, m));
    return 0;
}
