#include <cstring>
#include <iostream>
using namespace std;

const int maxnm = 52, maxn = 102, maxp = 12;

struct node {
  bool danger;
  int son[maxnm], suffix, fa;
};

typedef int int128[maxn + 2];

node trie[maxnm * maxp];
char a[maxnm], data[maxp];
int s[maxp][maxp], queue[maxp * maxnm], i, j, k, l, n, m, p, q, cl, op, total,
    now;
int128 f[maxnm][maxnm * maxp], ans;

void init() {
  cin >> n >> m >> p;
  // scanf("%d%d%d\n",&n,&m,&p);
  cin >> (a + 1);
  /*
  for(i=1;i<=n;i++)
          scanf("%c",&a[i]);
  */
  for (i = 1; i <= p; i++) {
    cin >> data;
    // scanf("\n%s",data);
    s[i][0] = strlen(data);
    for (j = 0; j < s[i][0]; j++)
      for (k = 1; k <= n; k++)
        if (data[j] == a[k]) {
          s[i][j + 1] = k;
          break;
        }
  }
}

void build_trie() {
  total = 1;
  for (i = 1; i <= n; i++) trie[0].son[i] = 1;

  for (i = 1; i <= p; i++) {
    now = 1;
    for (j = 1; j <= s[i][0]; j++) {
      if (trie[now].son[s[i][j]] == 0) {
        trie[now].son[s[i][j]] = ++total;
        trie[trie[now].son[s[i][j]]].fa = now;
      }
      now = trie[now].son[s[i][j]];
    }
    trie[now].danger = true;
  }
}

void build_graph() {
  cl = 1;
  trie[1].suffix = 1;
  for (i = 1; i <= n; i++)
    if (trie[1].son[i] == 0)
      trie[1].son[i] = 1;
    else {
      queue[++op] = trie[1].son[i];
      trie[trie[1].son[i]].suffix = 1;
    }
  if (op == 0) return;
  do {
    k = queue[cl];
    for (i = 1; i <= n; i++)
      if (trie[k].son[i] != 0) {
        queue[++op] = trie[k].son[i];
        trie[trie[k].son[i]].suffix = trie[trie[k].suffix].son[i];
        trie[trie[k].son[i]].danger = trie[trie[k].son[i]].danger ||
                                      trie[trie[trie[k].son[i]].suffix].danger;
      } else
        trie[k].son[i] = trie[trie[k].suffix].son[i];
    cl++;
  } while (cl <= op);
}

void jia(int128 a, int128 b, int128 &c) {
  int i;
  c[maxn + 1] = 0;
  for (i = 1; i <= maxn; i++) c[i] = a[i] + b[i];
  for (i = maxn; i >= 1; i--) {
    c[i] += c[i + 1] / 100000000;
    c[i + 1] %= 100000000;
  }
}

void dp() {
  f[0][1][maxn] = 1;

  for (i = 0; i < m; i++)
    for (j = 1; j <= total; j++)
      for (k = 1; k <= n; k++)
        if (trie[trie[j].son[k]].danger == false)
          jia(f[i + 1][trie[j].son[k]], f[i][j], f[i + 1][trie[j].son[k]]);

  for (i = 1; i <= total; i++) jia(ans, f[m][i], ans);
}

void work() {
  build_trie();
  build_graph();
  dp();
}

void print() {
  for (i = 1; i <= maxn; i++)
    if (ans[i] != 0) break;
  printf("%d", ans[i]);
  for (i = i + 1; i <= maxn; i++) {
    if (ans[i] < 10000000) printf("0");
    if (ans[i] < 1000000) printf("0");
    if (ans[i] < 100000) printf("0");
    if (ans[i] < 10000) printf("0");
    if (ans[i] < 1000) printf("0");
    if (ans[i] < 100) printf("0");
    if (ans[i] < 10) printf("0");
    printf("%d", ans[i]);
  }
  printf("\n");
}

int main() {
  init();
  work();
  print();
  return 0;
}
