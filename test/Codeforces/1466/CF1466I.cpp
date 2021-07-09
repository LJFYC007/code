/***************************************************************
	File name: CF1466I.cpp
	Author: ljfcnyali
	Create time: 2021年01月07日 星期四 21时59分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

map<vector<int>, bool> Map[210];
int Real[maxn], cnt;

// #define Auto
#ifdef Auto
inline bool print(vector<int> a, int pos)
{
    ++ cnt;
    int x = 0; REP(i, 1, 7) x = x * 2 + a[i - 1];
    // printf("%d ", pos); for ( auto it : a ) printf("%d", it); puts(""); fflush(stdout);
    // if ( x < Real[pos] ) puts("yes"); else puts("no");
    if ( x < Real[pos] ) return 1;
    return 0;
}
#else 
inline bool print(vector<int> a, int pos) 
{
    if ( Map[pos].count(a) ) return Map[pos][a];
    printf("%d ", pos); for ( auto it : a ) printf("%d", it); puts(""); fflush(stdout);
    string s; cin >> s; Map[pos][a] = s == "yes"; return s == "yes";
}
#endif

inline vector<int> Decrease(vector<int> a)
{
    int n = a.size() - 1; while ( a[n] == 0 ) a[n --] = 1;
    a[n] = 0; return a; 
}

inline bool Check1(vector<int> a, int b, int pos)
{
    while ( a.size() < b ) a.push_back(1);
    return print(a, pos);
}

inline bool Check2(vector<int> a, int b, int pos, bool op)
{
    while ( a.size() < b ) a.push_back(0);
    if ( !op ) 
    {
        bool flag = false; for ( auto it : a ) if ( it == 1 ) flag = true; if ( !flag ) return false;
        a = Decrease(a); 
    }
    return !print(a, pos);
}

inline vector<int> Solve(vector<int> pre, vector<int> a, int b)
{
    // cerr << pre.size() << " " << a.size() << " " << b << endl;
    vector<int> Stack, ans, val; if ( pre.size() == b ) return pre;
    // random_shuffle(a.begin(), a.end()); 
    val = pre; int c = pre.size();
    for ( int i = 0; i < a.size(); ++ i ) 
    {
        while ( Stack.size() && Check1(val, b, a[i]) ) { val.pop_back(); Stack.pop_back(); }
        if ( val.size() == b ) continue ; 
        // if ( Check2(val, b, a[i], 0) || val.size() == b ) continue ;  
        Stack.push_back(a[i]); val.push_back(1);
        if ( Check2(val, b, a[i], 0) ) val[val.size() - 1] = 0; 
    }
    /*
    // for ( auto it : val ) cout << it; cout << " "; for ( auto it : Stack ) cout << it << " "; cout << endl;
    vector<int> nxt;
    while ( Stack.size() ) 
    {
        int it = Stack.front(); pre.push_back(val[c]); ++ c;
        if ( Stack.size() == 1 ) break ; 
        // if ( Check2(val, b, it, 1) ) { Stack.erase(Stack.begin()); continue ; }
        if ( !Check1(val, b, it) ) { nxt.push_back(it); Stack.erase(Stack.begin()); continue ; } 
        Stack.pop_back(); val.pop_back(); while ( Check1(val, b, it) ) { Stack.pop_back(); val.pop_back(); }
        for ( auto i : nxt ) Stack.push_back(i);
        return Solve(pre, Stack, b);
    }
    for ( auto i : nxt ) Stack.push_back(i);
    return Solve(pre, Stack, b);
    */
    vector<int> nxt; nxt.push_back(Stack.back()); Stack.pop_back();
    while ( Stack.size() ) 
    {
        int it = Stack.back();
        if ( Check1(val, b, it) ) return Solve(pre, Stack, b); 
        Stack.pop_back(); nxt.push_back(it);
    }
    return Solve(val, nxt, b);
}

int main()
{
#ifdef Auto
    freopen("input.txt", "r", stdin);
#endif
    int n, b; scanf("%d%d", &n, &b);
#ifdef Auto
    REP(i, 1, n)
    {
        getchar(); int x = 0;
        REP(j, 1, b) { char c = getchar(); x = x * 2 + c - '0'; }
        Real[i] = x;
    }
#endif
    vector<int> a, t; REP(i, 1, n) a.push_back(i);
    a = Solve(t, a, b); printf("0 "); for ( auto it : a ) cout << it; cout << endl;
    fflush(stdout);
#ifdef Auto
    cout << cnt << endl;
#endif
    return 0;
}
