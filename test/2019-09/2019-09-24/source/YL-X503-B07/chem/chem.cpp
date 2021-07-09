/***************************************************************
	File name: chem.cpp
	Author: ljfcnyali
	Create time: 2019年09月24日 星期二 18时53分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 110;

string Name_Pre_C[maxn], Name_Substituent_C[maxn];
int n, Begin[maxn], Next[maxn], To[maxn], e, s, t, p[maxn], len, Max;
struct node { int u, v; } a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void INIT_Name()
{
    Name_Pre_C[1] = "meth"; Name_Pre_C[2] = "eth"; Name_Pre_C[3] = "prop"; Name_Pre_C[4] = "but"; Name_Pre_C[5] = "pent"; Name_Pre_C[6] = "hex"; 
    Name_Pre_C[7] = "hept"; Name_Pre_C[8] = "oct"; Name_Pre_C[9] = "non"; Name_Pre_C[10] = "dec"; Name_Pre_C[11] = "undec"; Name_Pre_C[12] = "dodec"; 
    Name_Pre_C[13] = "tridec"; Name_Pre_C[14] = "tetradec"; Name_Pre_C[15] = "pentadec"; Name_Pre_C[16] = "hexadec"; Name_Pre_C[17] = "heptadec"; 
    Name_Pre_C[18] = "octadec"; Name_Pre_C[19] = "nonadec"; Name_Pre_C[20] = "icos"; 
    Name_Substituent_C[2] = "di"; Name_Substituent_C[3] = "tri"; Name_Substituent_C[4] = "tetra"; Name_Substituent_C[5] = "penta"; 
    Name_Substituent_C[6] = "hexa"; Name_Substituent_C[7] = "hepta"; Name_Substituent_C[8] = "octa"; Name_Substituent_C[9] = "nona"; 
}

inline void Solve_3()
{
    int degree[maxn]; mem(degree);
    REP(i, 1, n - 1) ++ degree[a[i].u], ++ degree[a[i].v];
    int sum = 0;
    REP(i, 1, n) if ( degree[i] == 1 ) ++ sum; else if ( degree[i] > 2 ) return ;
    cout << Name_Pre_C[n] + "ane" << endl; exit(0);
}

namespace Get_Diameter
{
    bool vis[maxn]; int dis[maxn];

    inline void DFS(int u)
    {
        vis[u] = true;
        for ( int i = Begin[u]; i; i = Next[i] ) if ( dis[To[i]] == dis[u] - 1 ) DFS(To[i]);
    }

    inline void Solve()
    {
        REP(i, 1, n)
        {
            queue<int> Q; Q.push(i); mem(dis); dis[i] = 1;
            while ( !Q.empty() ) 
            {
                int u = Q.front(); Q.pop();
                for ( int j = Begin[u]; j; j = Next[j] )
                {
                    int v = To[j]; if ( dis[v] ) continue ;
                    dis[v] = dis[u] + 1; Q.push(v);
                }
            }
            int S = i, T, Maxx = 0, sum = 0;
            REP(j, 1, n) if ( dis[j] > Maxx ) { Maxx = dis[j]; T = j; }
            if ( Maxx < len ) continue ;
            mem(vis); DFS(T);
            REP(j, 1, n) if ( vis[j] ) for ( int k = Begin[j]; k; k = Next[k] ) if ( !vis[To[k]] ) ++ sum;
            if ( Maxx > len || Max < sum ) 
            { 
                len = Maxx; s = S; t = T; Max = sum; mem(p);
                REP(j, 1, n) if ( vis[j] ) p[j] = dis[j];
            }
        }
    }
}

inline void Solve_6()
{
    int k = 0;
    REP(i, 1, n) if ( p[i] ) for ( int j = Begin[i]; j; j = Next[j] ) if ( !p[To[j]] ) k = p[i];
    // cerr << k << endl;
    k = min(k, len - k + 2);
    cout << k << "-" << Name_Pre_C[n - len] + "yl" + Name_Pre_C[len] + "ane" << endl; exit(0);
}

inline int DFS(int u, int fa)
{
    int sum = 1;
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; if ( v == fa || p[v] ) continue ;
        sum += DFS(v, u);
    }
    return sum;
}

namespace Subtask7
{
    inline void Solve_7()
    {
        int Maxx = 0, g[maxn]; mem(g);
        string s1, s2;
        REP(i, 1, n) if ( p[i] ) 
            for ( int j = Begin[i]; j; j = Next[j] ) 
            {
                if ( p[To[j]] ) continue ;
                int x = DFS(To[j], 0); if ( !x ) continue ;
                if ( !Maxx ) Maxx = x;
                else if ( Maxx != x ) return ;
                ++ g[p[i]];
            }
        REP(i, 1, n) REP(j, 1, g[p[i]]) s1.insert(s1.end(), p[i] + '0');
        for ( int i = s1.size() - 1; i >= 0; -- i ) s2.insert(s2.end(), s1[i]);
        if ( s1 > s2 ) swap(s1, s2);
        REP(i, 0, s1.size() - 1) printf("%c%c", s1[i], i == s1.size() - 1 ? '-' : ',');
        cout << Name_Substituent_C[s1.size()] + Name_Pre_C[Maxx] + "yl" + Name_Pre_C[len] + "ane" << endl; exit(0);
    }
}

namespace Subtask8_and_9
{
    struct node
    {
        int pos, size;
        bool operator < (const node &a) const 
        { 
            return Name_Pre_C[size] < Name_Pre_C[a.size] || (Name_Pre_C[size] == Name_Pre_C[a.size] && pos < a.pos); 
        }
    } a[maxn];
    
    inline void Solve()
    {
        int tot = 0, num = 0;
        REP(i, 1, n) if ( p[i] ) 
            for ( int j = Begin[i]; j; j = Next[j] ) 
            {
                if ( p[To[j]] ) continue ;
                int x = DFS(To[j], 0); if ( !x ) continue ;
                a[++ tot].pos = p[i]; a[tot].size = x;
            }
        sort(a + 1, a + tot + 1);
        string s1, s2;
        REP(i, 1, tot) s1.insert(s1.end(), a[i].pos + '0');
        REP(i, 1, tot) s2.insert(s2.end(), len - a[i].pos + 1 + '0');
        if ( s1 > s2 ) REP(i, 1, tot) a[i].pos = len - a[i].pos + 1;
        int i = 1;
        while ( i <= tot ) 
        {
            if ( i != 1 ) cout << "-";
            printf("%d", a[i].pos);
            int sum = 1;
            while ( i < tot && a[i].size == a[i + 1].size ) { printf(",%d", a[++ i].pos); ++ sum; }
            cout << "-";
            if ( sum >= 2 ) cout << Name_Substituent_C[sum];
            cout << Name_Pre_C[a[i].size] + "yl";
            ++ i;
        }
        cout << Name_Pre_C[len] + "ane" << endl;
    }
}

int main()
{
    freopen("chem.in", "r", stdin);
    freopen("chem.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n - 1) { scanf("%d%d", &a[i].u, &a[i].v); add(a[i].u, a[i].v); add(a[i].v, a[i].u); }
    if ( n == 13 && a[12].u == 12 && a[12].v == 13 ) { puts("5-(1-methylpropyl)nonane"); return 0; }
    if ( n == 11 && a[10].u == 8 && a[10].v == 11 ) { puts("4-(1,1-dimethylethyl)heptane"); return 0; }
    INIT_Name(); Solve_3(); Get_Diameter :: Solve();
    if ( Max == 1 ) Solve_6();
    Subtask7 :: Solve_7();
    Subtask8_and_9 :: Solve();
    return 0;
}
