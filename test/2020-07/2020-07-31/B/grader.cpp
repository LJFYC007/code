#include <bits/stdc++.h>
#include "perm.h"
#define pb push_back
using namespace std;
namespace workspace {
	const string verdict[]={"Wrong Answer","OK"};
	vector<int> p; int n,qcnt;
	int abs_int(int x){ return x<0?-x:x;}
	void ensure(bool f){ if(!f) printf("Invalid Query"),exit(0); }
	vector<int> query(vector<int> q){
        for ( auto i : q ) printf("%d ", i); puts("");
		++qcnt; vector<int> P(n+1),Q(n+1),R; int u=0; ensure(q.size()==n);
		for(int i=0;i<n;++i) ensure(1<=q[i]&&q[i]<=n),P[p[i]]=i+1,Q[q[i]]=i+1;
		for(int i=1;i<=n;++i) ensure(Q[i]!=0),R.pb(abs_int(P[i]-Q[i]));
		sort(R.begin(),R.end());
		return R;
	}
	void main(){
		cin>>n;
		for(int i=1,x;i<=n;++i) cin>>x,p.pb(x);
		vector<int> q=guess(n);
		printf("%s\n%d\n",verdict[q==p].c_str(),qcnt);
	}
}
vector<int> query(vector<int> q){ return workspace::query(q); }
int main()
{ 
    freopen("perm.in", "r", stdin);
    workspace::main(); 
}
