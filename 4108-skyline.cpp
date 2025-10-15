#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;

const int maxn = 100000 + 10;
// maxh[node]:在node對應區間內最大高度
// setnode[node]:0代表maxh[node]的值已經往下傳送；非0表示尚未傳送
int T,n,m,maxh[maxn<<1],setnode[maxn<<1],ans;  // <<1 表示*2
struct node {
    int l, r, h;  // 對應區間的左、右、高度
}a[maxn];

//左右兩個小孩 2*node 和 2*node+1 兩個之間h較高的值往父節點傳送
void pushup(int node) {
    maxh[node] = max(maxh[node<<1], maxh[node<<1|1]); 
    //node<<1|1 : 與1做OR，因為node*2一定是偶數，將最低位元設為1，等於直接+1
}
void build(int left, int right, int node) {
    int mid = (left + right) >> 1;
    maxh[node] = 0;
    setnode[node] = 0;
    if(left == right) return ;
    build(left, mid, node<<1); //建立左小孩以2*node為根節點之左子樹(區間[left..mid])
    build(mid+1, right, node<<1|1); //建立右小孩以2*node+1為根節點之右子樹(區間[mid+1..right])

}
void pushdown(int left, int right, int node) {
    if(setnode[node]) {
        setnode[node<<1] = setnode[node<<1|1] = setnode[node]; //往下傳送
        maxh[node<<1] = maxh[node<<1|1] = maxh[node];
        setnode[node] = 0;
    }
}
// L, R是輸入的值
void update(int L, int R, int h, int left, int right, int node) {
    int mid = (left + right) >> 1;
    if(setnode[node] && maxh[node] > h) return ; //高度比maxh低，不必更新
    if(L <= left && right <= R) {
        if(maxh[node] <= h) {
            maxh[node] = h;
            setnode[node] = h;
            ans += right - left + 1;
            return ;
        }
    }
    if(left == right) return ;
    if (R<left||right<L) return; 
    pushdown(left, right, node);
    if(L <= mid) update(L, R, h, left, mid, node<<1);
    if(mid < R)  update(L, R, h, mid+1, right, node<<1|1);
    pushup(node);
}
int main() {

    while(~scanf("%d",&T) && T) {
        while(T--) {
            scanf("%d",&n);
            int datamaxx = 0;
            for(int i=0;i<n;i++) {
                scanf("%d%d%d",&a[i].l, &a[i].r, &a[i].h);
                datamaxx = max(datamaxx, a[i].r);
            }
            build(1, datamaxx, 1);
            ans = 0;
            for(int i=0;i<n;i++) {
                update(a[i].l, a[i].r-1, a[i].h, 1, datamaxx, 1);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
