/***************************************************************
	File name: P5308.cpp
	Author: ljfcnyali
	Create time: 2020年07月26日 星期日 10时36分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;
const double INF = 1e9;
const double eps = 1e-12;

int n, k;
pii f[maxn];
struct node { int l, r, x; node(int a = 0, int b = 0, int c = 0) { x = a; l = b; r = c; } } ;

inline pii max(pii a, pii b) 
{
    if ( a.x > b.x + eps ) return a;
    if ( b.x - eps <= a.x && a.x <= b.x + eps ) return a.y < b.y ? a : b;
    return b;
}

inline bool Check(int pos, int x, int y, double val)
{
    pii a = pii(f[x].x - (x * 1.0 / pos) + 1 + val, f[x].y + 1);
    pii b = pii(f[y].x - (y * 1.0 / pos) + 1 + val, f[y].y + 1);
    if ( a < b ) return true;
    return false;
}

inline pii Check(double val)
{
    deque<node> Q; Q.push_front(node(0, 1, n));
    REP(i, 1, n) 
    {
        if ( Q.front().r < i ) Q.pop_front();
        int x = Q.front().x; f[i] = pii(f[x].x - (x * 1.0 / i) + 1 + val, f[x].y + 1);
        while ( 1 ) 
        {
            if ( Q.empty() ) { Q.push_back(node(i, i + 1, n)); break ; }
            int l = Q.back().l, r = Q.back().r, pos = r + 1;
            x = Q.back().x;
            while ( l <= r ) 
            {
                int Mid = l + r >> 1;
                if ( Check(Mid, x, i, val) ) { pos = Mid; r = Mid - 1; }
                else l = Mid + 1;
            }
            if ( pos == Q.back().l ) Q.pop_back();
            else 
            {
                auto it = Q.back(); Q.pop_back();
                it.r = pos - 1; Q.push_back(it);
                Q.push_back(node(i, pos, n));
                break ; 
            }
        }
    }
    return f[n];
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    double L = -1, R = 1, ans;
    REP(i, 1, 100)
    {
        double Mid = (L + R) / 2;
        pii x = Check(Mid);
        if ( x.y <= k ) { ans = x.x - Mid * k; L = Mid; } 
        else R = Mid;
    }
    printf("%.9lf\n", ans);
    return 0;
}
