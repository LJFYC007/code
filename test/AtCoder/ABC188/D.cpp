/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 20时08分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e6 + 10;

int n, C, c[maxn], p[maxn], m, ans;
map<int, int> Map;
struct node 
{ 
    int l, r, w;
} a[maxn];

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val) { for ( int i = pos; i <= m; i += lowbit(i) ) c[i] += val; }

inline int get(int pos) { int sum = 0; for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i]; return sum; } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &C);
    REP(i, 1, n) 
    {
        scanf("%lld%lld%lld", &a[i].l, &a[i].r, &a[i].w);
        ++ a[i].r; Map[a[i].l] = Map[a[i].r] = true;
    }
    for ( auto it : Map ) { Map[it.first] = ++ m; p[m] = it.first; } 
    REP(i, 1, n) { add(Map[a[i].l], a[i].w); add(Map[a[i].r], -a[i].w); }
    REP(i, 1, m - 1)
    {
        int val = min(get(i), C);
        ans += val * (p[i + 1] - p[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
