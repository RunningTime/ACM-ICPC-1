#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1010000;
struct Node {
        int l,r,cnt;
}t[N<<2];
char s[N];
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
Node up(Node a,Node b) {
        Node ret;
        ret.cnt = a.cnt+b.cnt;
        int tmp;
        tmp = min(a.r,b.l);
        ret.cnt += tmp*2;
        ret.l = a.l+b.l-tmp;
        ret.r = b.r+a.r-tmp;
        return ret;
}
void build(int l,int r,int rt) {
        if (l==r) {
                t[rt].cnt = 0;
                if (s[l]=='(') t[rt].r = 1;
                else t[rt].l = 1;
                return ;
        }
        int mid = l+r>>1;
        build(lson);
        build(rson);
        t[rt] = up(t[rt<<1],t[rt<<1|1]);
}
Node query(int L,int R,int l,int r,int rt) {
        if (L<=l && r<=R) return t[rt];
        int mid = l+r>>1;
        Node ret = (Node) {0,0,0};
        if (L<=mid) ret = up(query(L,R,lson),ret);
        if (R>mid)  ret = up(ret,query(L,R,rson));
        return ret;
}
int main() {
        scanf("%s",s);
        int len = strlen(s);
        build(0,len-1,1);
        int nq;
        scanf("%d",&nq);
        while (nq--) {
                int l,r;
                scanf("%d%d",&l,&r);
                l --; r --;
                printf("%d\n",query(l,r,0,len-1,1).cnt);
        }
        return 0;
}
