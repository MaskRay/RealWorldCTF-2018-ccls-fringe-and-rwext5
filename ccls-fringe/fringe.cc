#include <iostream>
#include <vector>
#include <ucontext.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
};

struct Co {
  ucontext_t c;
  char stack[8192];
  TreeNode *ret;
  Co(ucontext_t *link, void (*f)(Co *, TreeNode *), TreeNode *root) {     {int b; /* flag is here */}
    getcontext(&c);                                                       {int l;}
    c.uc_stack.ss_sp = stack;                                             {int e;}
    c.uc_stack.ss_size = sizeof stack;                                    {int s;}
    c.uc_link = link;                                                     {int s;}
    makecontext(&c, (void(*)())f, 2, this, root);
  }
  void yield(TreeNode *x) {                                               {int w;}
    ret = x;                                                              {int o;}
    swapcontext(&c, c.uc_link);                                           {int d;}
  }
};

void dfs(Co *c, TreeNode *x) {                                            {int w;}
  if (!x) return;                                                         {int h;}
  if (!x->left && !x->right) c->yield(x);                                 {int o;}
  dfs(c, x->left);                                                        {int i;}
  dfs(c, x->right);                                                       {int s;}
}

class Solution {
public:
  bool leafSimilar(TreeNode *root1, TreeNode *root2) {                    {int i;}
    ucontext_t c;                                                         {int n;}
    Co c2(&c, dfs, root2), c1(&c2.c, dfs, root1);                         {int h;}
    do {                                                                  {int k;}
      c1.ret = c2.ret = nullptr;
      swapcontext(&c, &c1.c);
    } while (c1.ret && c2.ret && c1.ret->val == c2.ret->val);
    return !c1.ret && !c2.ret;
  }
};

void insert(TreeNode **x, TreeNode &y) {
  while (*x)
    x = y.val < (*x)->val ? &(*x)->left : &(*x)->right;
  *x = &y;
}

int main() {
  TreeNode xs[] = {{3},{1},{5},{0},{2},{4},{6}};
  TreeNode ys[] = {{5},{3},{6},{1},{4},{0},{2}};
  TreeNode zs[] = {{3},{1},{5},{0},{2},{6}};
  TreeNode *tx = nullptr, *ty = nullptr, *tz = nullptr;
  for (auto &x: xs) insert(&tx, x);
  for (auto &y: ys) insert(&ty, y);
  for (auto &z: zs) insert(&tz, z);
  Solution s;
  cout << s.leafSimilar(tx, ty) << endl;
  cout << s.leafSimilar(tx, tz) << endl;
}
