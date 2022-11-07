#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

FILE *fin,*fout,*fans,*res;
int n, a[maxn], b[maxn], c[maxn], ans;

void quit(int s){
	fprintf(res,"%d",s);
	exit(0);
}

int main(int argc,char* argv[]){
	fin=fopen(argv[1],"r");
	fout=fopen(argv[2],"r");
	fans=fopen(argv[3],"r");
	res=fopen(argv[5],"w");

	fscanf(fin, "%d", &n);
	REP(i, 1, n) fscanf(fin, "%d", &a[i]);
	sort(a + 1, a + n + 1);

	fscanf(fans, "%d", &ans);
	REP(i, 1, n) fscanf(fout, "%d", &b[i]);
	REP(i, 1, n) c[i] = b[i];
	sort(c + 1, c + n + 1);

	REP(i, 1, n) if ( a[i] != c[i] ) quit(0); 
	int ret = 2147483647;
	REP(i, 1, n - 1) ret = min(ret, abs(b[i] - b[i + 1]));
	if ( ans != ret ) quit(0); else quit(10);
	return 0;
}
