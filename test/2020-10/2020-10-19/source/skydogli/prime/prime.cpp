#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int fh=1,a=0;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*fh;
}
#define pii pair<int,int>
#define piii pair<int ,pii >
#define mp make_pair
#define x first
#define y second
#define MN 200005
const int N=5000*10000;
int pr[N/10+5],cnt;
bool vis[N+5],fk[MN];
void INIT(){
	vis[0]=vis[1]=1;
	for(int i=2;i<=N;++i){
		if(!vis[i]){pr[++cnt]=i;}
		for(int j=1;pr[j]*i<=N;++j){
			vis[pr[j]*i]=1;
			if(i%pr[j]==0)break;
		}
	}
}
pii operator +(pii a,pii b){return mp(a.x+b.x,a.y+b.y);}
pii operator -(pii a,pii b){return mp(a.x-b.x,a.y-b.y);}
pii operator *(pii a,pii b){
	return mp(a.x*b.x-a.y*b.y,a.x*b.y+b.x*a.y);
}
int Len(pii a){return a.x*a.x+a.y*a.y;}
int n,q;
pii a[MN];
int rev[MN<<2],rtag[MN<<2],clear[MN<<2];
#define Ls (x<<1)
#define Rs (x<<1|1)
#define mid ((l+r)>>1)
struct smt{
	int sum[MN<<2][5],tag[MN<<2][5];
	void pushup(int x){
		for(int i=0;i<4;++i){
			sum[x][i]=sum[Ls][i]+sum[Rs][i];
		}
	}
	void build(int x,int l,int r){
	/*	for(int x=1,l=1;x<=n;++x,++l){	
			sum[x][0]=(!a[l].y&&a[l].x>0&&!vis[a[l].x]);
			sum[x][1]=(!a[l].x&&a[l].y>0&&!vis[a[l].y]);
			sum[x][2]=(!a[l].y&&a[l].x<0&&!vis[-a[l].x]);
			sum[x][3]=(!a[l].x&&a[l].y<0&&!vis[-a[l].y]);
	//	cerr<<x<<": "<<sum[x][0]<<" "<<sum[x][2]<<endl;
		}
		
			
		return;*/
		for(int i=0;i<4;++i)tag[x][i]=-1;
		rev[x]=0;
		if(l==r){
			sum[x][0]=(!a[l].y&&a[l].x>0&&!vis[a[l].x]);
			sum[x][1]=(!a[l].x&&a[l].y>0&&!vis[a[l].y]);
			sum[x][2]=(!a[l].y&&a[l].x<0&&!vis[-a[l].x]);
			sum[x][3]=(!a[l].x&&a[l].y<0&&!vis[-a[l].y]);
			return;
		}
		build(Ls,l,mid);
		build(Rs,mid+1,r);
		pushup(x);
	}
	int tmp[4],tagtmp[4];
	void rotate(int x,int arc){
		assert(arc<=4);
		if(!arc)return;
	//	cerr<<"ROTATE: "<<x<<endl;
	//	cerr<<"rotate: "<<x<<" "<<arc<<endl;
		for(int i=0;i<4;++i)tmp[i]=sum[x][i],tagtmp[i]=tag[x][i];
		for(int i=0;i<4;++i){
			sum[x][(i+arc)&3]=tmp[i];
			tag[x][(i+arc)&3]=tagtmp[i];
		}
		rev[x]=(rev[x]+arc)&3;
		rtag[x]=(rtag[x]+arc)&3;
	}
	void ptag(int x,int op,int l,int r,int v){
		for(int i=0;i<4;++i)sum[x][i]=0,tag[x][i]=0;
		tag[x][op]=v;
		sum[x][op]=v*(r-l+1);
		if(rev[x])rotate(x,rev[x]);
	}
	void pushdown(int x,int l,int r){
		if(clear[x]){
			rotate(Ls,(4-rev[Ls])%4);
			rotate(Rs,(4-rev[Rs])%4);
			rtag[Ls]=rtag[Rs]=0;
			clear[Ls]=clear[Rs]=1;
			clear[x]=0;
		}
		if(rtag[x]){
			rotate(Ls,rtag[x]);
			rotate(Rs,rtag[x]);
			rtag[x]=0;
		}
		if(tag[x][0]!=-1){
			int p=0;
			for(int j=1;j<4;++j)
				if(tag[x][j])p=j;
			ptag(Ls,p,l,mid,tag[x][p]);
			ptag(Rs,p,mid+1,r,tag[x][p]);
			rotate(Ls,(4-rev[x])%4);
			rotate(Rs,(4-rev[x])%4);
			for(int j=0;j<4;++j)
				tag[x][j]=-1;
		}
		else for(int j=1;j<4;++j)assert(tag[x][j]==-1);
	//	cerr<<"WUHU "<<sum[Ls][0]<<" "<<tag[Ls][0]<<endl;
	}
	void change(int x,int op,int l,int r,int b,int e,int v){	
	/*	for(int i=b;i<=e;++i){
			for(int j=0;j<4;++j)sum[i][j]=0;
			sum[i][op]=v;
			rotate(i,rev[i]);
		}

		return;*/
		if(b<=l&&r<=e){	
			ptag(x,op,l,r,v);
			return;
		}
		if(l>e||r<b)return;
		pushdown(x,l,r);
		if(b<=mid)change(Ls,op,l,mid,b,e,v);
		if(e>mid)change(Rs,op,mid+1,r,b,e,v);
		pushup(x);
	}
	void rotate(int x,int l,int r,int b,int e,int arc){
		
		if(b<=l&&r<=e){rotate(x,arc);return;}
		pushdown(x,l,r);
		if(b<=mid)rotate(Ls,l,mid,b,e,arc);
		if(e>mid) rotate(Rs,mid+1,r,b,e,arc);
		pushup(x);
	}
	void clear_rotate(int x,int l,int r,int b,int e){

	/*		for(int i=b;i<=e;++i){
				int tmp=(4-rev[i])%4;
				rotate(i,tmp);
				rev[i]=0;
			}
		
		return;*/
		if(b<=l&&r<=e){
			//rev[x]=0;
	//		assert(!sum[x][0]&&!sum[x][1]&&!sum[x][2]&&!sum[x][3]);
			rotate(x,(4-rev[x])%4);
			rtag[x]=0;
			clear[x]=1;
			return;
		}
		if(l>e||r<b)return;
		pushdown(x,l,r);
		if(b<=mid)clear_rotate(Ls,l,mid,b,e);
		if(e>mid) clear_rotate(Rs,mid+1,r,b,e);
		pushup(x);
	}
	int ask(int x,int op,int l,int r,int b,int e){
		
		int res=0;
		if(b<=l&&r<=e){
			return sum[x][op];
		}
		pushdown(x,l,r);
		 res=0;
		if(b<=mid)res=ask(Ls,op,l,mid,b,e);
		if(e>mid)res+=ask(Rs,op,mid+1,r,b,e);
		return res;
	}
}Tree;
struct odt{
	int l;
	mutable int r,op;//op:有无用
	mutable pii w;
	odt(int L=0,int R=0,int O=0,pii W=mp(0,0)){
		l=L;r=R;op=O;w=W;
	}
	bool friend operator<(odt a,odt b){
	//	if(a.l==b.l&&a.r==b.r)return a.w<b.w;
		if(a.l==b.l)return a.r<b.r;
		return a.l<b.l;
	}
};
#define itset multiset<odt>::iterator
multiset<odt>S;
const pii py[4]={mp(1,0),mp(0,1),mp(-1,0),mp(0,-1)};
void split(int pos){
	itset it=S.upper_bound(odt(pos,1e9));
	if(it!=S.end()&&(*it).l==pos+1)return;
	assert(it!=S.begin());
	it--;

	odt l=odt((*it).l,pos,(*it).op,(*it).w),r=odt(pos+1,(*it).r,(*it).op,(*it).w);


	S.erase(it);
	if(l.l<=l.r)S.insert(l);

	if(r.l<=r.r)S.insert(r);
}
const double eps=1e-5;
bool chk(pii w){//可能有用
	if(abs(w.x)>N||abs(w.y)>N)return 0;
	if(Len(w)==1)return 1;
	if(Len(w)==0)return 0;
	if(Len(w)<=N&&!vis[Len(w)])return 1;
	int tmp=sqrt(eps+Len(w));
	if(Len(w)>1&&tmp<=N&&tmp*tmp==Len(w)&&(!w.x||!w.y)&&!vis[tmp])return 1;
	return 0;
}
bool chkpr(pii w){
	if(abs(w.x)>N||abs(w.y)>N)return 0;
	int tmp=sqrt(eps+Len(w));
	return Len(w)>1&&tmp<=N&&tmp*tmp==Len(w)&&(!w.x||!w.y)&&!vis[tmp];
}
int getfx(pii w){
	int fx=0;
//	if(!w.x)assert(!vis[abs(w.y)]||abs(w.y)==1);
//	if(!w.y)assert(!vis[abs(w.x)]||abs(w.x)==1);
	if(!w.x)fx=(w.y>0)?1:3;
	else fx=(w.x>0)?0:2;
	return fx;
}
void cover(int l,int r,pii w){
	split(l-1);split(l);split(r-1);split(r);
	itset it=S.lower_bound(odt(l));
	assert((*it).l==l);
	while((*it).l!=r+1&&it!=S.end()){
		assert((*it).l<=r);
		it=S.erase(it);
	}
	Tree.clear_rotate(1,1,n,l,r);
	int op=1;
	if(!chk(w))op=0;
	S.insert(odt(l,r,op,w));
	if(chkpr(w)){
		Tree.change(1,getfx(w),1,n,l,r,1);
	}
	else Tree.change(1,0,1,n,l,r,0);
}
itset Mergerub(itset it){
	if(it!=S.begin()){
		itset il=it;il--;
		assert((*il).r==(*it).l-1);
		if(!(*il).op&&!(*it).op){
			(*il).r=(*it).r;
			return  S.erase(it);
		}
	}
	return ++it;
}
void mul(int l,int r,pii w){
	split(l-1);split(l);split(r-1);split(r);
	if(Len(w)==1){
		Tree.rotate(1,1,n,l,r,getfx(w));
		return;
	}
	bool ok=chk(w),GG=0;
	itset it=S.lower_bound(odt(l));
	assert((*it).l==l);
	while((*it).l!=r+1&&it!=S.end()){
		assert((*it).l<=r);
		assert(!(!(*it).w.x&&!(*it).w.y&&(*it).op));
		if(ok&&(*it).op){
			int flag=0;
			if((*it).op&&chkpr((*it).w)){
				flag=1;
			}	
			if(chkpr((*it).w*w)){
				assert(!flag);
				(*it).w=(*it).w*w;
				Tree.change(1,getfx((*it).w),1,n,(*it).l,(*it).r,1);
				++it;
			}
			else if(chk((*it).w*w)){
				assert(!flag);
				(*it).w=(*it).w*w;
				assert(!chkpr((*it).w));
				++it;
			}
			else {
				if((*it).op)
					Tree.change(1,0,1,n,(*it).l,(*it).r,0);
				(*it).op=0;
				it=Mergerub(it);
			}
		}
		else {
//			if((*it).op)Tree.change(1,0,1,n,(*it).l,(*it).r,0);
			(*it).op=0;
			it=Mergerub(it);
		}
	}
	if(!ok)Tree.change(1,0,1,n,l,r,0);
}
void check(){
	itset lst=S.begin(),it=lst;
//	assert(Tree.getrev(1,0,1,n,(*it).l)==Tree.getrev(1,0,1,n,(*it).r));
	for(++it;it!=S.end();++it){
//		assert(Tree.getrev(1,0,1,n,(*it).l)==Tree.getrev(1,0,1,n,(*it).r));
		assert((*lst).r==(*it).l-1);
		lst=it;
	}
}
signed main(){
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	INIT();
	n=read();q=read();
//	cerr<<"n&q: "<<n<<" "<<q<<endl;
//	S.insert(odt(1,n,0,mp(0,0)));
	for(int i=1;i<=n;++i){
		a[i].x=read(),a[i].y=read();
//		cover(i,i,a[i]);
		int op=chk(a[i]);
		S.insert(odt(i,i,op,a[i]));
	}
//	cerr<<"done"<<endl;
	int cas=0;
	Tree.build(1,1,n);
	for(int i=1;i<=q;++i){
		int op=read();
//		if(i%1000==0)cerr<<"i: "<<i<<" "<<op<<" "<<S.size()<<endl;
		if(op==1||op==2){
			int l=read(),r=read(),x=read(),y=read();
		//	cerr<<"? "<<op<<" "<<l<<" "<<r<<" "<<x<<" "<<y<<endl;
			if(op==1){
				cover(l,r,mp(x,y));
			}
			else {
				mul(l,r,mp(x,y));
			}
		}
		else{
			int l=read(),r=read();
	//		cerr<<"? "<<op<<" "<<l<<" "<<r<<endl;
			printf("%lld\n",Tree.ask(1,0,1,n,l,r));
			cas++;
		}
	//	check();
	}
	return 0;
}
