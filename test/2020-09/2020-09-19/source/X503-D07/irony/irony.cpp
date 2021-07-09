/***************************************************************
	File name: irony.cpp
	Author: ljfcnyali
	Create time: 2020年09月20日 星期日 15时50分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e6 + 1;
const int INF = 0x3f3f3f3f;

int n, m, ans, ret, sum, f[maxn];
struct node 
{ 
    int x, y; 
    node ( int a = 0, int b = 0 ) { x = a; y = b; }
} a[maxn];
vector<int> A[maxn], B[maxn];

bool operator < (node a, node b) { return (a.x < a.y ? INF - a.x : a.y) < (b.x < b.y ? INF - b.x : b.y); }

inline int find(int x) 
{ 
    if ( f[x] == -1 ) return -1;
    return x == f[x] ? x : f[x] = find(f[x]); 
}

int main()
{
    freopen("irony.in", "r", stdin);
    freopen("irony.out", "w", stdout);

    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        sum = ans = ret = 0; 
        scanf("%d%d", &n, &m); 
        REP(i, 1, n + m) f[i] = i;
        getchar(); REP(i, 1, n) { char c = getchar(); a[i] = c == '(' ? node(0, 1) : node(1, 0); }
        getchar(); REP(i, n + 1, n + m) { char c = getchar(); a[i] = c == '(' ? node(0, 1) : node(1, 0); }

        REP(i, 1, n + m) 
            if ( a[i].x < a[i].y ) A[a[i].x].push_back(i);
            else B[a[i].y].push_back(i);
        
        REP(i, 0, n + m)
        {
            for ( int j = 0; j < A[i].size(); ++ j )
            {
                int id = A[i][j]; node u = node(i, a[id].y);
                    if ( u.x != a[id].x || find(id) != id ) continue ;

                int x = find(id - 1);
                if ( id == 1 || id == n + 1 || x == -1 ) 
                {
                    sum -= u.x; ret = min(ret, sum); sum += u.y; 
                    f[id] = -1; continue ;
                }
                f[id] = x; 

                a[x].y -= u.x;
                if ( a[x].y < 0 ) { a[x].x -= a[x].y; a[x].y = 0; }
                a[x].y += u.y;
                if ( a[x].x <= a[x].y ) A[a[x].x].push_back(x);
                else B[a[x].y].push_back(x);
            }
            A[i].clear();
        }

        for ( int i = n + m; i >= 0; -- i ) 
        {
            for ( int j = 0; j < B[i].size(); ++ j )
            {
                int id = B[i][j]; node u = node(a[id].x, i);
                if ( u.y != a[id].y || find(id) != id ) continue ;

                int x = find(id - 1);
                if ( id == 1 || id == n + 1 || x == -1 ) 
                {
                    sum -= u.x; ret = min(ret, sum); sum += u.y; 
                    f[id] = -1; continue ;
                }
                f[id] = x; 

                a[x].y -= u.x;
                if ( a[x].y < 0 ) { a[x].x -= a[x].y; a[x].y = 0; }
                a[x].y += u.y;
                B[a[x].y].push_back(x);
            }
            B[i].clear();
        }
        
        ans -= ret;
        if ( sum + ans > 0 ) ans += sum + ans; 
        printf("%d\n", ans);
    }
    return 0;
}
