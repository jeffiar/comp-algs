#include <cstdio>
#include <ctime>
#include <cstdlib>

struct node {
    int val;
    int size;
    node *ch[2];
    node *par;

    node(int val) : val{val}, size{1}, ch{NULL,NULL}, par{NULL} { }
    ~node() {
        printf("deleting %p (val = %d)\n", this, val);
        delete ch[0]; delete ch[1];
    }
};
node *ROOT = NULL;

#define link(p, q, d)               \
         if(q) (q)->par = (p);      \
         if(p) (p)->ch[(d)] = (q);  
#define side(a) int(a && a->par && (a->par->ch[1] == a))
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

void splay(node* kid) {
    //printf("splaying %p (val = %d)\n", kid, kid->val);
    while(kid->par) {
        node *dad = kid->par;
        if(dad->par) {
            bool same = (side(kid) == side(dad));
            rotate((same) ? dad : kid);
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
    printf("succ is %d\n", curr->val);
    return curr;
}

node *find(int val, node *curr = ROOT) {
    if (curr == NULL)    return NULL;
    if (val < curr->val) return find(val, curr->ch[0]);
    if (val > curr->val) return find(val, curr->ch[1]);

    printf("found %d at %p!\n", val, curr);
    splay(curr);
    return curr;
}

void erase(node *curr) {
    if(curr == NULL) return;
    printf("erasing %d\n", curr->val);

    node *lchild = curr->ch[0];
    node *rchild = curr->ch[1];

    if(lchild && rchild) {
        //two children
        node *next = succ(curr);
        next->val = curr->val;
        erase(next);
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
#define dir (val > curr->val)
    node *curr = ROOT;
    while(curr != NULL && curr->ch[dir] != NULL)
        curr = curr->ch[dir];
    
    node *noob = new node(val);
    link(curr, noob, dir);
    splay(noob);
    printf("inserting %d at %p\n", val, noob);
    return noob;
}

void test() {
    srand(time(NULL));

    printf("here we go!\n");
    for(int i = 0; i < 100100; i++) {
        int val = rand() % 10000007;
        insert(val);
    }

    printf("\nattempting to start erases...\n");

    for(int i = 0; i < 1000000; i++) {
        int val = rand() % 10000007;
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
