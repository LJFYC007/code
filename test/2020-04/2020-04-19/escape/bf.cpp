/***************************************************************
	File name: escape.cpp
	Author: ljfcnyali
	Create time: 2020年04月19日 星期日 13时01分28秒
***************************************************************/
#include<bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, double>
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e9;
const double eps = 1e-12;

int n, m, A[maxn], B[maxn], C[maxn], L, R;
double W[maxn], f[maxn], Tree[maxn << 2];
deque<pii> Q; 
multiset<double, greater<double> > Set;

/*
inline double max(double x, double y) {if (x > y) return x;return y;}
inline long long max(long long x, long long y) {if (x > y) return x;return y;}
*/

inline double Query(int root, int l, int r)
{
    if ( L <= l && r <= R ) return Tree[root];
    int Mid = l + r >> 1; double ret = -INF;
    if ( L <= Mid ) ret = max(ret, Query(lson, l, Mid));
    if ( Mid < R ) ret = max(ret, Query(rson, Mid + 1, r));
    return ret;
}

inline void Modify(int root, int l, int r, int pos, double val)
{
    if ( l == r ) { Tree[root] = val; return ; }
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
    Tree[root] = max(Tree[lson], Tree[rson]);
}

double dp[21][maxn];
int Log[maxn];

inline void modify(int pos,double val){
    pos = n - pos;
    dp[0][pos]=val;
    for(int i=1;i<=20;++i)if ( pos + (1 << i - 1) <= n ) dp[i][pos]=max(dp[i-1][pos],dp[i-1][pos+(1<<i-1)]);
}

inline double query(int l,int r){
    l = n - l; r = n - r;
    swap(l, r);
    int k=Log[r-l+1];
    return max(dp[k][l],dp[k][r-(1<<k)+1]);
}

inline bool Check(double x)
{
    REP(i, 1, n) W[i] = A[i] - B[i] * x;
    REP(i, 1, n) f[i] = -INF;
    REP(i, 0, n) REP(j, 0, 20) dp[j][i] = -INF; 
    modify(0, 0);
    Q.clear(); Set.clear();
    REP(i, 1, n)
    {
        while ( !Q.empty() && i - Q.front().first >= m ) { Set.erase(Q.front().second); Q.pop_front(); }
        if ( !Q.empty() ) 
        {
            Set.erase(Q.front().second);
            L = max(0, i - m);
            R = Q.front().first - 1;
            if ( L <= R ) Q.front().second = W[Q.front().first] + query(L, R);
            Set.insert(Q.front().second);
        }
        while ( !Q.empty() && C[i] >= C[Q.back().first] ) { Set.erase(Q.back().second); Q.pop_back(); }
        L = Q.empty() ? max(0, i - m) : Q.back().first;
        R = i - 1;
        if ( L <= R ) 
        {
            pii x = make_pair(i, W[i] + query(L, R));
            Q.push_back(x);
            Set.insert(x.second);
        }

        f[i] = max(f[i], f[i - 1] + W[i]);
        if ( Set.size() ) f[i] = max(f[i], *Set.begin());
        modify(i, f[i]);
    }
    if ( f[n] >= 0 ) return true;
    return false;
}

inline void print(double x)
{
    int cnt = 0;
    while ( x >= 10 ) { ++ cnt; x /= 10; }
    while ( x < 1 ) { -- cnt; x *= 10; }
    printf("%.9lfe", x);
    if ( cnt < 0 ) printf("-00%d\n", -cnt);
    else printf("+00%d\n", cnt);
}

signed main()
{
    freopen("escape.in", "r", stdin);
    freopen("escape.out", "w", stdout);
    Log[0] = -1;
    REP(i, 1, maxn - 10) Log[i] = Log[i >> 1] + 1;
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d%d%d", &A[i], &B[i], &C[i]); 
    double l = 0, r = INF, ans = 0;
    REP(i, 1, 65)
    {
        double Mid = (l + r) / 2.0;
        if ( Check(Mid) ) { l = Mid + eps; ans = Mid; }
        else r = Mid - eps;
    }
    print(ans);
    return 0;
}
