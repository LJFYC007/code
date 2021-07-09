/***************************************************************
	File name: 1821.cpp
	Author: ljfcnyali
	Create time: 2019年06月26日 星期三 20时08分33秒
***************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 30010;

// f[i][j] = max(f[i - 1][k] + p[i] * (j - k) | j - l[i] <= k <= s[i] - 1)
// f[i][j] = p[i] * j + max(f[i - 1][k] - p[i] * k)

struct node
{
    int l, p, s;
} a[maxn];

deque<int> Q;
int n, m, f[110][maxn];

inline int cmp(node a, node b)
{
    return a.s < b.s;
}

inline int js(int i, int k)
{
    return f[i - 1][k] - a[i].p * k;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    REP(i, 1, n) scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s);
    sort(a + 1, a + n + 1, cmp);
    REP(i, 1, n)
    {
        Q.clear();
        REP(k, max(0, a[i].s - a[i].l), a[i].s - 1)
        {
            while ( !Q.empty() && js(i, Q.back()) <= js(i, k) ) Q.pop_back();
            Q.push_back(k);
        }
        REP(j, 1, m)
        {
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if ( j >= a[i].s ) 
            {
                while ( !Q.empty() && Q.front() < j - a[i].l ) Q.pop_front();
                if ( !Q.empty() ) f[i][j] = max(f[i][j], js(i, Q.front()) + a[i].p * j);
            }
        }
    }
    printf("%d\n", f[n][m]);
    return 0;
}
