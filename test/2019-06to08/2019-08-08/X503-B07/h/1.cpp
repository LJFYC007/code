/***************************************************************
	File name: h.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 09时25分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define lson root << 1
#define rson root << 1 | 1
typedef long long LL;

const int maxn = 200010;

int h[maxn], n, m, num, k, sum, H[maxn];

struct node
{
    int x, y;
    bool operator < (const node &a) const { return x < a.x; }
} a[maxn];

struct Node
{
    int val, Min1, Min2, lazy; 
} Tree[maxn];

struct node1
{
    int val, pos;
} p1;

int main()
{
    freopen("h.in", "r", stdin);
    freopen("h.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &h[i]);
    scanf("%d", &m);
    REP(i, 1, m) scanf("%d%d", &a[i].x, &a[i].y);
    Build(1, 1, m);
    sort(a + 1, a + m + 1);
    int now = 1;
    deque<node1> Q;
    REP(i, 1, m)
    {
        int Min = h[now];
        REP(j, now + 1, a[i].x) Min = min(Min, h[j]);
        H[i] = Min;
        now = a[i].x;
        num = a[i].y + a[i].x - a[i - 1].y - a[i - 1].x;
        int L = 1, R = i - 1, x = -1;
        while ( L <= R ) 
        {
            int Mid = L + R >> 1;
            if ( H[Mid] > Min ) { x = Mid; R = Mid - 1; } 
            else L = Mid + 1;
        }
        if ( x != -1 ) 
        {
            H[x] = Min;
            Update(1, 1, m, x, i - 1, 2 * Min);
        }
    }
    return 0;
}
