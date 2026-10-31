#include<bits/stdc++.h>
#define ll long long
#define dbl double long
#define pb push_back
#define in insert
#define fi first
#define se second
#define MASK(i) (1LL << (i))
#define c_bit(i) __builtin_popcountll(i)
#define bit(x, i) ((x) & MASK(i))
#define on(x, i) ((x) |(1LL<<i))
#define off(x, i) ((x) & ~MASK(i))
#define task "code"
using namespace std;
const ll N=1e5+20;
const ll M=1LL<<20;
const ll GH=2e5+2;
const ll MOD=1e9+7;
const ll base=521;
const ll LOG=30;
struct segment{
	struct Node{
		ll val=0;
		ll lazy=0;
	};
	Node st[4*N];
	void build(ll id,ll l,ll r,ll a[]){
		if(l==r){
			st[id].val=a[l];
			return ;
		}
		ll mid=(l+r)/2;
		build(id*2,l,mid,a);
		build(id*2+1,mid+1,r,a);
		st[id].val=max(st[id*2].val,st[id*2+1].val);
	}
	void down(ll id,ll l,ll r){
		if(l==r){
			return ;
		}
		ll t=st[id].lazy;
		st[id*2].lazy+=t;
		st[id*2].val+=t;
		st[id*2+1].lazy+=t;
		st[id*2+1].val+=t;
        st[id].lazy=0;
	}
	void update(ll id,ll l,ll r,ll u,ll v,ll val){
		down(id,l,r);
        if(v<l||r<u){
        	return;
		}
        if(u<=l&&r<=v){
			st[id].val+=val;
			st[id].lazy+=val;
            return;
        }
        ll mid=(l+r)/2;
        update(id*2,l,mid,u,v,val);
        update(id*2+1,mid+1,r,u,v,val);
        st[id].val=max(st[id*2].val,st[id*2+1].val);
    }
    ll get(ll id,ll l,ll r,ll u,ll v){
		down(id,l,r);
        if (v<l||u>r){
        	return -1e18;
		}
        if(u<=l&&r<=v){
			return st[id].val;
		}
        ll mid=(l+r)/2;
        
        return max(get(id*2+1,mid+1,r,u,v),get(id*2,l,mid,u,v));
 
    }
} st;
struct query{
    ll l,r,val;
};
void solve()
{
    ll n,q;
    cin>>n>>q;
    vector<query> v;
    for(ll i=1;i<=q;i++)
    {
        query x;
        cin>>x.l>>x.r>>x.val;
        v.pb(x);
        st.update(1,1,n,x.l,x.r,x.val);
    }
    ll ans=1e18;
    for(ll i=0;i<v.size();i++)
    {
        st.update(1,1,n,v[i].l,v[i].r,0-v[i].val);
        ans=min(ans,st.get(1,1,n,1,n));
        st.update(1,1,n,v[i].l,v[i].r,v[i].val);
    }    
    cout<<ans;
}
signed main(){

    if(fopen("SEQGAME.INP", "r")){
        freopen("SEQGAME.INP", "r", stdin);
        freopen("SEQGAME.OUT", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    t=1;
    while(t--)
    {

        solve();
    }

}
//
