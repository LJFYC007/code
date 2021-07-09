/***************************************************************
	File name: CF582E.cpp
	Author: ljfcnyali
	Create time: 2021年06月29日 星期二 19时54分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 510;
const int Mod = 1e9 + 7;

int n, m, tot, g[1 << 16];
char s[maxn]; map<char, int> Map; 
struct node { int x[8], val; } a[maxn];
vector<int> f[maxn];

inline void calc(int now, int val) { int s = 0; REP(i, 0, n - 1) s |= a[i].x[val] << i; ++ f[now][s]; }

inline void FWTOR(vector<int> & f, int op)
{
	int n = f.size();
	for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
		for ( int i = 0; i < n; i += (Mid << 1) )
			REP(j, 0, Mid - 1) f[i + j + Mid] = (f[i + j + Mid] + f[i + j] * op) % Mod;
}
inline void FWTAND(vector<int> & f, int op)
{
	int n = f.size();
	for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
		for ( int i = 0; i < n; i += (Mid << 1) )
			REP(j, 0, Mid - 1) f[i + j] = (f[i + j] + f[i + j + Mid] * op) % Mod;
}

inline vector<int> operator +(vector<int> a, vector<int> b)
{
	int n = a.size(); vector<int> c(n); 
	REP(i, 0, n - 1) c[i] = (a[i] + b[i]) % Mod;
	return c;
}
inline vector<int> operator |(vector<int> a, vector<int> b)
{
	FWTOR(a, 1); FWTOR(b, 1); 
	REP(i, 0, (1 << n) - 1) a[i] = 1ll * a[i] * b[i] % Mod; 
	FWTOR(a, -1); return a;
}
inline vector<int> operator &(vector<int> a, vector<int> b)
{
	FWTAND(a, 1); FWTAND(b, 1); 
	REP(i, 0, (1 << n) - 1) a[i] = 1ll * a[i] * b[i] % Mod; 
	FWTAND(a, -1); return a;
}

inline void Solve(int now, int l, int r)
{
	f[now].resize(1 << n);
	if ( l == r ) 
	{
		if ( s[l] == '?' ) REP(i, 0, 7) calc(now, i);
		else calc(now, Map[s[l]]);
		return ;
	}
	int op = 0, lstop = 1; f[now][0] = 1;
	REP(i, l, r) if ( op == 0 ) 
	{
		int x = ++ tot; op ^= 1;
		if ( s[i] == '(' ) 
		{
			int sum = 1, j = i + 1;
			while ( 1 )
			{
				if ( s[j] == '(' ) ++ sum;
				if ( s[j] == ')' ) -- sum;
				if ( !sum ) break ;
				++ j;
			}
			Solve(x, i + 1, j - 1); i = j;
		}
		else Solve(x, i, i); 
		
		if ( lstop == 0 ) f[now] = (f[now] | f[x]) + (f[now] & f[x]); 
		else if ( lstop == 1 ) f[now] = f[now] | f[x];
		else f[now] = f[now] & f[x];
	}
	else
	{
		op ^= 1;
		if ( s[i] == '?' ) lstop = 0;
		else if ( s[i] == '|' ) lstop = 1;
		else lstop = 2;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); m = str(s + 1);
	scanf("%d", &n); int s = 0;
	REP(i, 0, n - 1) 
	{
		REP(j, 0, 3) { scanf("%d", &a[i].x[j]); a[i].x[j + 4] = a[i].x[j] ^ 1; }
		scanf("%d", &a[i].val); s |= a[i].val << i;
	}
	REP(i, 0, 3) { Map[i + 'A'] = i; Map[i + 'a'] = i + 4; }
	tot = 1; Solve(1, 1, m);
	printf("%d\n", (f[1][s] + Mod) % Mod);
    return 0;
}
