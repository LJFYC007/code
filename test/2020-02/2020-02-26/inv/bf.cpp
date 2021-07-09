#include<bits/stdc++.h>
using namespace std;
template<typename T>inline T read(){
	T x=0,f=0;char c=getchar();
	while(!isdigit(c)) f=c=='-',c=getchar();
	while(isdigit(c)) x=x*10+c-48,c=getchar();
	return f?-x:x;
}
#define int long long
namespace run{
	typedef pair<int,int> P;
	const int N=1e5+9,inf=8e8;
	int n,k,f[N], S;

	namespace KdTree{
		#define ls (tr[k].L)
		#define rs (tr[k].R)
		struct node{int mn[2],mx[2],dot[2],siz,L,R,val;}tr[N];

		int tot=0,ans;
		inline void pushup(int k){
			if(ls){
				tr[k].mn[0]=min(tr[k].mn[0],tr[ls].mn[0]);
				tr[k].mx[0]=max(tr[k].mx[0],tr[ls].mx[0]);
				tr[k].mn[1]=min(tr[k].mn[1],tr[ls].mn[1]);
				tr[k].mx[1]=max(tr[k].mx[1],tr[ls].mx[1]);
				tr[k].val=min(tr[k].val,tr[ls].val);
			}
			if(rs){
				tr[k].mn[0]=min(tr[k].mn[0],tr[rs].mn[0]);
				tr[k].mx[0]=max(tr[k].mx[0],tr[rs].mx[0]);
				tr[k].mn[1]=min(tr[k].mn[1],tr[rs].mn[1]);
				tr[k].mx[1]=max(tr[k].mx[1],tr[rs].mx[1]);
				tr[k].val=min(tr[k].val,tr[rs].val);
			}
			tr[k].siz=tr[ls].siz+tr[rs].siz+1;
		}
		inline int get(P dot,int d){return d?dot.second:dot.first;}
		inline void insert(int &k,int d,P dot){
			if(!k){
				k=++tot;
				tr[k].dot[0]=tr[k].mx[0]=tr[k].mn[0]=dot.first;
				tr[k].dot[1]=tr[k].mx[1]=tr[k].mn[1]=dot.second;
				tr[k].siz=1,tr[k].val=f[k-1];
				return;
			}
			if(get(dot,d)<=tr[k].dot[d]) insert(ls,d^1,dot);
			else insert(rs,d^1,dot);
			pushup(k);
		}
		inline int dist(P A,P B){
			int ret=(A.first-B.first)*(A.first-B.first);
			ret+=(A.second-B.second)*(A.second-B.second);
			return ret;
		}
		inline bool check(int k,P dot){
			int now=inf;
			if(dot.first>=tr[k].mn[0] && dot.first<=tr[k].mx[0]) return tr[k].val<ans;
			if(dot.second>=tr[k].mn[1] && dot.second<=tr[k].mx[1]) return tr[k].val<ans;
			now=min(now,dist(dot,P(tr[k].mn[0],tr[k].mn[1])));
			now=min(now,dist(dot,P(tr[k].mn[0],tr[k].mx[1])));
			now=min(now,dist(dot,P(tr[k].mx[0],tr[k].mn[1])));
			now=min(now,dist(dot,P(tr[k].mx[0],tr[k].mx[1])));
			return now+tr[k].val<ans;
		}
		inline void query(int k,P dot){
			++ S;
			ans=min(ans,dist(dot,P(tr[k].dot[0],tr[k].dot[1]))+f[k-1]);
			if(ls && check(ls,dot)) query(ls,dot);
			if(rs && check(rs,dot)) query(rs,dot);
		}
		inline void TEST(int k){
			cout<<"k:"<<k<<" "<<"val:"<<sqrt(tr[k].val)<<endl;
			cout<<"mn[0] & mx[0]:"<<tr[k].mn[0]<<" "<<tr[k].mx[0]<<endl;
			cout<<"mn[1] & mx[1]:"<<tr[k].mn[1]<<" "<<tr[k].mx[1]<<endl;
			if(ls) TEST(ls);
			if(rs) TEST(rs);
		}
	}using namespace KdTree;
	int rt,A[N],g[N];
	int main(){
		n=read<int>(),k=read<int>();
		if(k==1){
			for(int i=1;i<=n;i++) A[i]=read<int>(),g[i]=inf;
			for(int i=1;i<=n;i++){
				f[i]=inf;
				for(int j=0;j<A[i];j++)
					f[i]=min(f[i],g[j]+(A[i]-j)*(A[i]-j));
				g[A[i]]=min(f[i],g[A[i]]);
				printf("%.4lf\n",sqrt(f[i]));
			}
			return 0;
		}
		insert(rt,0,P(0,0));
		for(int i=1;i<=1000;i++){
		//	TEST(rt);
			P ret;ret.first=read<int>(),ret.second=read<int>();
			ans=inf,query(rt,ret),f[i]=ans,insert(rt,0,ret);
			printf("%.4lf\n",sqrt(f[i]));
		}
		cerr << S << endl;
		return 0;
	}
}
#undef int
#define my mine
int main(){
	freopen("inv.in","r",stdin);
	freopen("inv.out","w",stdout);
	return srand(19260817),run::main();
}
