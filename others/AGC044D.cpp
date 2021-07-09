/***************************************************************
	File name: AGC044D.cpp
	Author: ljfcnyali
	Create time: 2021年07月06日 星期二 21时07分47秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int M = 128;

int len, a[maxn], pos, val, num;
char c[maxn], ans[maxn]; bool vis[maxn];

/*
string S;
inline int ask(string s)
{
	++ num;
	int sum = 0;
	REP(i, 0, M - 1) if ( s[i] != S[i] ) ++ sum;
	return sum;
}
*/

inline int ask(string s)
{
	cout << "? " << s << endl; fflush(stdout);
	int x; scanf("%d", &x); return x;
}

inline int Check(int l, int r, int x)
{
	int sum = 0;
	REP(i, l, r) if ( ans[i] != ' ' ) ++ sum;
	if ( sum == r - l + 1 ) return 0;
	string s;
	REP(i, 1, len) 
		if ( i < l || i > r || vis[i] ) s = s + c[pos];
		else s = s + c[x];
	return val - ask(s);
}

inline void Solve(int l, int r, int x, int w)
{
	if ( !w ) return ;
	if ( l == r ) { ans[l] = c[x]; return ; } 
	int Mid = l + r >> 1;

	if ( rand() % 2 == 0 )
	{
		int ttt = Check(Mid + 1, r, x);
		Solve(Mid + 1, r, x, ttt);
		Solve(l, Mid, x, w - ttt);
	}
	else 
	{
		int ttt = Check(l, Mid, x);
		Solve(l, Mid, x, ttt); 
		Solve(Mid + 1, r, x, w - ttt);
	}
}

int main()
{
	// freopen("input.txt", "r", stdin); cin >> S;
	REP(i, 0, 25) c[i] = i + 'a';
	REP(i, 0, 25) c[26 + i] = i + 'A';
	REP(i, 0, 9) c[26 + 26 + i] = i + '0';

	REP(o, 0, 61)
	{
		string s; REP(i, 1, M) s = s + c[o];
		a[o] = M - ask(s); len += a[o];
		if ( a[o] > a[pos] ) pos = o;
	}
	
	REP(i, 1, len) ans[i] = ' ';
	val = len - a[0 == pos ? 1 : 0];
	REP(o, 1, len)
	{
		string s; 
		REP(i, 1, len) 
			if ( i != o ) s = s + c[0 == pos ? 1 : 0];
			else s = s + c[pos];
		if ( ask(s) < val ) { vis[o] = true; ans[o] = c[pos]; }
	}

	val = len - a[pos];
	REP(i, 0, 61) if ( i != pos ) Solve(1, len, i, a[i]);
	printf("! %s\n", ans + 1); fflush(stdout);
	// cerr << num << endl;
    return 0;
}
