/*
 * Splay tree: a binary search tree with nice amortized time guarantees.
 * Annoying to code because of pointers and shit.
 */
#include <cstdio>
#include <ctime>
#include <cstdlib>
const int NTRIES = 100100, MOD = 10000007;

struct node {
    int val;
    int size;
    node *ch[2];
    node *par;

    node(int val) : val{val}, size{1}, ch{NULL,NULL}, par{NULL} { }
    ~node() {
        //printf("deleting %p (val = %d)\n", this, val);
        delete ch[0]; delete ch[1];
    }
};
node *ROOT = NULL;

#define side(a) int(a && a->par && (a->par->ch[1] == a))
inline void link(node *dad, node* kid, int dir) {
    if(kid) kid->par = dad;
    if(dad) dad->ch[dir] = kid;
}

inline void update(node *a) {;}

void rotate(node *kid) {
    int   dir = side(kid);
    node *dad = kid->par;
    node *dog = kid->ch[!dir];

    link(dad->par, kid, side(dad));
    link(kid,      dad, !dir);
    link(dad,      dog, dir);

    update(dad);
}

void splay(node* kid, node *gf = NULL) {
    //printf("splaying %p (val = %d)\n", kid, kid->val);
    while(kid->par != gf) {
        node *dad = kid->par;
        if(dad->par != gf) {
            if(side(kid) == side(dad)) rotate(dad);
            else rotate(kid);
        }
        rotate(kid);
    }

    update(kid);
    ROOT = kid;
}

node *succ(node *curr) {
    //leftmost node in right subtree of curr
    curr = curr->ch[1];
    while(curr->ch[0] != NULL)
        curr = curr->ch[0];
    //printf("succ is %d\n", curr->val);
    return curr;
}

node *find(int val, node *curr = ROOT) {
    if (curr == NULL)    return NULL;
    if (val < curr->val) return find(val, curr->ch[0]);
    if (val > curr->val) return find(val, curr->ch[1]);

    //printf("found %d at %p!\n", val, curr);
    splay(curr);
    return curr;
}

void erase(node *curr) {
    if(curr == NULL) return;
    //printf("erasing %d\n", curr->val);

    node *lchild = curr->ch[0];
    node *rchild = curr->ch[1];

    //two children
    if(lchild && rchild) {
        node *next = succ(curr);
        next->val = curr->val;
        erase(next); //guaranteed only one child
        return;
    }

    //one or zero children
    node *kid = NULL;
    if(lchild) kid = lchild;
    if(rchild) kid = rchild;

    link(curr->par, kid, side(curr));
    splay(curr->par);

    *curr = node(-1);
    delete curr;
}

node *insert(int val) {
    if(find(val)) 
        return find(val);

    //find insertion point
    node *curr = ROOT, *next = ROOT;
    int dir = 0;
    while(curr != NULL && next != NULL) {
        curr = next;
        dir = val > curr->val; 
        next = curr->ch[dir];
    }

    next = new node(val);
    link(curr, next, dir);
    splay(next);
    //printf("inserting %d at %p\n", val, next);
    return next;
}

void test() {
    srand(time(NULL));

    printf("here we go!\n");
    for(int i = 0; i < NTRIES; i++) {
        int val = rand() % MOD;
        insert(val);
    }

    printf("inserted %d values...\n", NTRIES);
    printf("attempting to start erases...\n");

    for(int i = 0; i < 10*NTRIES; i++) {
        int val = rand() % MOD;
        erase(find(val));
    }

    printf("\ncleaning up...\n");
    delete ROOT;

    printf("done!\n");
}

int main() {
    if(fopen("splay.in", "r")) {
        freopen("splay.in", "r", stdin);
        freopen("splay.out", "w", stdout);
    }
    setbuf(stdout, NULL);

    test();
    return 0;
}
