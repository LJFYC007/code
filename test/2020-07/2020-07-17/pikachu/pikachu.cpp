/***************************************************************
	File name: pikachu.cpp
	Author: ljfcnyali
	Create time: 2020年07月17日 星期五 10时15分08秒
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
const int Mod = 998244353;

int T, n, tot, Rub[maxn], cnt, Time, ans, num, val;
struct Node { int pos, t, dep, x; Node(int a = 0, int b = 0, int c = 0, int d = 0) { pos = a; t = b; dep = c; x = d; } };
struct node { int Next[2], t; } Tree[maxn];
pii sum;
char s[maxn];

pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }
pii operator - (pii a, pii b) { return pii(a.first - b.first, a.second - b.second); }

inline int power(int a, int b) 
{ 
    if ( b < 0 ) return 0;
    int r = 1; 
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } 
    return r; 
}

inline int NewNode()
{
    int x; if ( cnt ) x = Rub[cnt --]; else x = ++ tot;
    REP(i, 0, 1) Tree[x].Next[i] = 0; Tree[x].t = 0;
    return x;
} 

inline pii Get(int depx, int depy, int tx, int ty)
{
    int x = ty - tx - depy + depx;
    if ( x < 0 ) return pii(0, 0);
    return pii(power(2, x) - 1, power(2, x - 1));
}

inline void Clear(int x)
{
    REP(i, 0, 1) if ( Tree[x].Next[i] ) 
    {
        Clear(Tree[x].Next[i]);
        Rub[++ cnt] = Tree[x].Next[i];
        Tree[x].Next[i] = 0;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("pikachu.in", "r", stdin);
    freopen("pikachu.out", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%lld", &n); tot = cnt = val = 0; NewNode();
        ans = num = 1; Time = 2; Tree[1].t = 1;
        while ( n -- ) 
        {
            scanf("%s", s + 1); 
            if ( s[1] == 'G' ) 
            {
                int x; scanf("%lld", &x);
                num = (num * 2 + val) % Mod; val = 0; ++ Time; ans = (ans + num + val) % Mod; 
                REP(i, 2, x) { ++ Time; num = num * 2 % Mod; ans = (ans + num) % Mod; } 
            }
            else
            {
                scanf("%s", s + 1); 
                int p = 1, m = str(s + 1), pos = 0, t = 1;
                REP(i, 1, m)
                {
                    int c = s[i] == 'L' ? 0 : 1;
                    if ( !Tree[p].Next[c] ) Tree[p].Next[c] = NewNode();
                    p = Tree[p].Next[c];
                    if ( Tree[p].t > t ) { t = Tree[p].t; pos = i; }
                }
                if ( Tree[p].t == Time ) -- val;

                sum = Get(pos, m, t, Time);
                // printf("%lld %lld\n", sum.first, sum.second);
                queue<Node> Q; Q.push(Node(p, t, m, pos));
                while ( !Q.empty() ) 
                {
                    int u = Q.front().pos, dep = Q.front().dep, x = Q.front().t, y = Q.front().x; Q.pop();
                    if ( Tree[u].t > x ) { x = Tree[u].t; y = dep; } ++ dep;
                    REP(i, 0, 1)
                    {
                        int v = Tree[u].Next[i]; if ( !v ) continue ;
                        Q.push(Node(v, x, dep, y));
                        if ( Tree[v].t ) 
                        {
                            sum = sum + pii(power(2, Time - Tree[v].t) - 1, power(2, Time - Tree[v].t - 1));
                            sum = sum - Get(y, dep, x, Time);
                            if ( Tree[v].t == Time ) -- val;
                        }
                    }
                }

                Tree[p].t = Time; ++ val;

                ans = (ans - sum.first) % Mod; num = (num - sum.second) % Mod;
                Clear(p);
            }
            // printf("%lld ", num);
            printf("%lld\n", (ans + Mod) % Mod);
        }
    }
    return 0;
}
