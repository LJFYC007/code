#include "testlib.h"
int vis[20];
int main() {
	registerValidation();
	int n = inf.readInt(1,15,"n"); inf.readSpace();
	int m = inf.readInt(1,500,"m"); inf.readEoln();
	for(int i=1;i<=n;++i){
		int x = inf.readInt(1,n,"a_i");
		ensuref(!vis[x],"It must be a permutation");
		vis[x] = 1;
		if(i == n) inf.readEoln();
		else inf.readSpace();
	}
	inf.readEof();
	return 0;
}


