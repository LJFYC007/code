# include <bits/stdc++.h>
using namespace std;
namespace Base{
	# define mr make_pair
	typedef long long ll;
	typedef double db;
	const int inf = 0x3f3f3f3f, INF = 0x7fffffff;
	const ll  infll = 0x3f3f3f3f3f3f3f3fll, INFll = 0x7fffffffffffffffll;
	template<typename T> void read(T &x){
    	x = 0; int fh = 1; double num = 1.0; char ch = getchar();
		while (!isdigit(ch)){ if (ch == '-') fh = -1; ch = getchar(); }
		while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
	    if (ch == '.'){
	    	ch = getchar();
	    	while (isdigit(ch)){num /= 10; x = x + num * (ch - '0'); ch = getchar();}
		}
		x = x * fh;
	}
	template<typename T> void chmax(T &x, T y){x = x < y ? y : x;}
	template<typename T> void chmin(T &x, T y){x = x > y ? y : x;}
}
using namespace Base;

int n, cnt, c, num[20], cpre[10], csuf[10];
char st[25];
int main(){
	freopen("strings.in", "r", stdin);
	freopen("strings.out", "w", stdout);
	int opt; read(opt);
	for (int op = 1; op <= opt; op++){
		read(n);
		cnt = 0, c = 0;
		memset(cpre, 0, sizeof(cpre));
		memset(csuf, 0, sizeof(csuf));
		memset(num, 0, sizeof(num));
		for (int i = 1; i <= n; i++){
			scanf("\n%s", st);
			int l = strlen(st);
			for (int j = 0; j < l - 2; j++)
				if (st[j] == 'S' && st[j + 1] == 'A' && st[j + 2] == 'D') cnt++;
			if (l == 1 && st[0] == 'A'){
				c++; continue;
			}
			int suf = 0, pre = 0;
			if (st[0] == 'D') suf = 1;
				else if (l > 1 && st[0] == 'A' && st[1] == 'D') suf = 2;
			if (st[l - 1] == 'S') pre = 1;
				else if (l > 1 && st[l - 2] == 'S' && st[l - 1] == 'A') pre = 2;
			num[pre * 3 + suf]++;
			cpre[pre]++; csuf[suf]++;
		}
		
		int oth = 0;
		for (int i = 1; i <= 2; i++){
			int t = min(cpre[i], csuf[3 - i]);
			if (t > 0 && cpre[i] == csuf[3 - i] && cpre[i] == num[i * 3 + (3 - i)]) t--;
			oth += t;
		}
		
		for (int i = 1; i <= c; i++){
			if (i > cpre[1]) break;
			int tmp = min(cpre[1] - i, csuf[2]) + min(cpre[2] + i, csuf[1]);
			oth = max(oth, tmp);
		}
		
		//if (oth > 0 && oth == n - c - num[0]) oth--;
		
		printf("%d\n", cnt + oth);
	}
	return 0;
}


