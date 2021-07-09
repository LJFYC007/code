/***************************************************************
	File name: CF698D.cpp
	Author: ljfcnyali
	Create time: 2020年10月06日 星期二 19时59分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
#define int long long
typedef long long LL;

const int maxn = 1010;

int n, k, pre[10][maxn], ans, per[10];
pii a[maxn], b[maxn];
inline int operator *(pii a, pii b) { return a.x * b.y - a.y * b.x; }
struct node 
{ 
    pii x; int id; 
    bool operator < (const node &a) const 
    {
        if ( x.y < 0 && a.x.y > 0 ) return false;
        if ( x * a.x == 0 ) return abs(x.x) < abs(a.x.x);
        return x * a.x > 0;
    }
} c[maxn];
deque<int> p;
vector<int> Vis;
bool vis[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &k, &n);
    REP(i, 1, k) scanf("%lld%lld", &a[i].x, &a[i].y);
    REP(i, 1, n) scanf("%lld%lld", &b[i].x, &b[i].y);

    REP(i, 1, k)
    {
        REP(j, 1, n)
        {
            c[j].x = pii(b[j].x - a[i].x, b[j].y - a[i].y); 
            c[j].id = j;
        }
        sort(c + 1, c + n + 1);
        REP(j, 2, n) 
            if ( c[j].x.x * c[j - 1].x.x >= 0 && c[j].x.y * c[j - 1].x.y >= 0 && 
                 c[j].x * c[j - 1].x == 0 ) 
                pre[i][c[j].id] = c[j - 1].id;
    }

    REP(i, 1, n)
    {
        REP(j, 1, k) per[j] = j;
        do
        {
            p.clear(); Vis.clear(); p.push_back(i); Vis.push_back(i); vis[i] = true;
            REP(j, 1, k)
            {
                // while ( !p.empty() && vis[p.front()] ) p.pop_front();
                if ( !p.size() ) break ; 
                int t = p.front(); p.pop_front();
                while ( pre[per[j]][t] ) 
                { 
                    t = pre[per[j]][t]; 
                    if ( !vis[t] ) { p.push_back(t); vis[t] = true; Vis.push_back(t); }
                    if ( p.size() > 2 * k ) goto Next ; 
                }
            }
Next : ;
            for ( auto it : Vis ) vis[it] = false;
            if ( !p.size() ) { ++ ans; break ; }
        } while ( next_permutation(per + 1, per + k + 1) );
    }
    printf("%lld\n", ans);
    return 0;
}
