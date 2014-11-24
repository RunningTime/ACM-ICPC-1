#include <bits/stdc++.h>

const int N = 100000 + 5;
const int M = 10 + 2;
const int Sqrt = 334;
int n,m,nq;
char str[N][M];
std::pair<int,int> aim[N][M];

std::pair<int,int> Find(int x,int y,int limit) {
	if (x<limit || x>=n || y<0 || y>=m)
		return std::make_pair(x,y);
	if (str[x][y] == '^') {
		if (x == limit)
			return std::make_pair(x-1,y);
		else 
			return aim[x-1][y];
	} 
	if (str[x][y] == '<') {
		if (y>0 && str[x][y-1]=='>')
			return std::make_pair(-1,-1);
		return Find(x,y-1,limit);
	}
	if (str[x][y] == '>') {
		if (y<m-1 && str[x][y+1]=='<')
			return std::make_pair(-1,-1);
		return Find(x,y+1,limit);
	}
	exit(-1);
}

void prepare(int ox) {
	for (int i = ox; i < std::min(ox+Sqrt,n); ++ i) {
		for (int j = 0; j < m; ++ j) {
			aim[i][j] = Find(i,j,ox);
		}
	}
}

void query(int x,int y) {
	while (x>=0 && x<n && y>=0 && y<m) {
		std::pair<int,int> t = aim[x][y];
		x = t.first;
		y = t.second;
	}
	if (x==-1 && y==-1) {
		printf("-1 -1\n");
		return ;
	}
	printf("%d %d\n",x+1,y+1);
}

int main() {
	scanf("%d%d%d",&n,&m,&nq);
	for (int i = 0; i < n; ++ i)
		scanf("%s",str[i]);
	for (int i = 0; i < n; i += Sqrt)
		prepare(i);
	while (nq -- ) {
		char op[2];
		int x,y;
		scanf("%s%d%d",op,&x,&y); x --; y --;
		if (op[0] == 'A') {
			query(x,y);
		} else {
			char ch[2];
			scanf("%s",ch);
			str[x][y] = ch[0];
			prepare(x/Sqrt*Sqrt);
		}
	}
	return 0;
}
