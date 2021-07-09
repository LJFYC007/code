/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 10时50分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 2e6 + 10;
const int N = 2e6;

int n, m, a[maxn], c[maxn][1], ans, p[maxn], sum1, sum2;
string s;
struct node { int sum, size; } Tree[maxn << 2];

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); }
}

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int opt)
{
    for ( int i = pos; i <= N; i += lowbit(i) ) c[i][opt] += val;
}

inline int query(int pos, int opt)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i][opt];
    return sum;
}

inline void Modify(int root, int l, int r, int pos, int val)
{
    Tree[root].size += val; Tree[root].sum += pos;
    if ( l == r ) return ;
    int Mid = l + r >> 1;
    if ( pos <= Mid ) Modify(lson, l, Mid, pos, val);
    else Modify(rson, Mid + 1, r, pos, val);
}

inline void Query(int root, int l, int r, int L, int R)
{
    if ( L <= l && r <= R ) 
    {
        sum1 += Tree[root].sum;
        sum2 += Tree[root].size;
        return ;
    }
    int Mid = l + r >> 1;
    if ( L <= Mid ) Query(lson, l, Mid, L, R);
    if ( Mid < R ) Query(rson, Mid + 1, r, L, R);
}

namespace Subtask1
{
    inline int main()
    {
        REP(i, 1, n)
        {
            p[i] = query(a[i] - 1, 0);  
            Modify(1, 1, N, p[i], 1);
            add(a[i], 1, 0);
        }
        while ( m -- ) 
        {
            int k; cin >> s >> k;
            if ( s == "A" ) 
            {
                a[++ n] = k;
                p[n] = query(a[n] - 1, 0);
                Modify(1, 1, N, p[n], 1);
                add(a[n], 1, 0);
            }
            else
            {
                sum1 = sum2 = 0;
                Query(1, 1, N, 1, k);
                int ret = sum1 + k * (n - sum2);
                ans ^= ret;
            }
        }
        printf("%lld\n", ans);
        return 0;
    }
}

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) read(a[i]);
    reverse(a + 1, a + n + 1);
    scanf("%lld", &m);
    // if ( m <= 1000 ) 
        return Subtask1 :: main();
    return 0;
}
