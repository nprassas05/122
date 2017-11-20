/*
 * Binary search tree without balancing
 * 
 * 15-122 Principles of Imperative Computation
 * Frank Pfenning
 */

/**************************/
/* Library implementation */
/**************************/

#include <stdlib.h>
#include <stdbool.h>
#include "bst-client.h"
#include "bst.h"
#include "lib/contracts.h"
#include "lib/xalloc.h"

struct tree_node {
  elem data;
  struct tree_node *left;
  struct tree_node *right;
};
typedef struct tree_node tree;

struct bst_header {
  tree *root;
  key (*elem_key)(elem e);
  int (*key_compare)(key k1, key k2);
  void (*elem_free)(elem e);
};

static inline key elemkey(bst B, elem e) {
  return (*B->elem_key)(e);
}

static inline int keycompare(bst B, key k1, key k2) {
  return (*B->key_compare)(k1, k2);
}

/* is_ordered(T, lower, upper) checks if all elements in T
 * are strictly in the interval (elem_key(lower),elem_key(kupper)).
 * lower = NULL represents -infinity; upper = NULL represents +infinity
 */
bool is_ordered(tree *T,
                elem lower,
                elem upper,
                elem (*elemkey)(elem e),
                int (*keycompare)(key k1, key k2)) {
  if (T == NULL) return true;
  if (T->data == NULL) return false;
  key k = (*elemkey)(T->data);
  if (!(lower == NULL || (*keycompare)(elemkey(lower),k) < 0))
    return false;
  if (!(upper == NULL || (*keycompare)(k,elemkey(upper)) < 0))
    return false;
  return is_ordered(T->left, lower, T->data, elemkey, keycompare)
    && is_ordered(T->right, T->data, upper, elemkey, keycompare);
}

bool is_ordtree(tree *T,
                elem (*elemkey)(elem e),
                int (*keycompare)(key k1, key k2)) {
  /* initially, we have no bounds - pass in NULL */
  return is_ordered(T, NULL, NULL, elemkey, keycompare);
}

bool is_bst(bst B) {
  if (B == NULL) return false;
  return is_ordtree(B->root, B->elem_key, B->key_compare);
}

bst bst_new(int (*key_compare)(key k1, key k2),
            key (*elem_key)(elem e),
            void (*elem_free)(elem e)) {
  bst B = xmalloc(sizeof(struct bst_header));
  B->root = NULL;
  ENSURES(is_bst(B));

  /* set the function pointers of the BST to those passed in */
  B->key_compare = key_compare;
  B->elem_key = elem_key;
  B->elem_free = elem_free;

  return B;
}

elem tree_lookup(tree *T,
                 key k,
                 int (*keycompare)(key k1, key k2),
                 key (*elemkey)(key k)
                 )
//@requires is_ordtree(T);
//@ensures \result == NULL || key_compare(elem_key(\result), k) == 0;
{
  REQUIRES(is_ordtree(bst B, T));
  if (T == NULL) return NULL;
  int r = keycompare(k, elemkey(T->data));
  elem retval;

  if (r == 0)
    retval = T->data;
  else if (r < 0)
    retval = tree_lookup(T->left, k, keycompare, elemkey);
  else {
    //@assert r > 0;
    ASSERT(r > 0);
    retval = tree_lookup(T->right, k, keycompare, elemkey);
  }
  ENSURES(retval == NULL || (*keycompare)(B, (*elemkey)(B, retval), k) == 0);
  return retval;
}

elem bst_lookup(bst B, key k)
//@requires is_bst(B);
//@ensures \result == NULL || key_compare(elem_key(\result), k) == 0;
{
  REQUIRES(is_bst(B));
  elem retval = tree_lookup(B->root, k, B->key_compare, B->elem_key);
  ENSURES(retval == NULL || keycompare(elemkey(B, retval), k) == 0);
  return retval;
}

/* tree_insert(T, e) returns the modified tree
 * this avoids some complications in case T = NULL
 */
tree *tree_insert(tree *T,
                  elem e,
                  int (*keycompare)(key k1, key k2),
                  key (*elemkey)(key k),
                  void (*elemfree)(elem e))
//@requires is_ordtree(T);
//@requires e != NULL;
//@ensures is_ordtree(\result);
{
  REQUIRES(is_ordtree(T));
  REQUIRES(e != NULL);
  if (T == NULL) {
    /* create new node and return it */
    T = xmalloc(sizeof(struct tree_node));
    T->data = e;
    T->left = NULL; T->right = NULL;
    ENSURES(is_ordtree(T));
    return T;
  }
  int r = keycompare(elemkey(e), elemkey(T->data));
  if (r == 0) {
    (*elemfree)(T->data);
    T->data = e;		/* modify in place */
  }
  else if (r < 0)
    T->left = tree_insert(T->left, e, keycompare, elemkey, elemfree);
  else //@assert r > 0;
    T->right = tree_insert(T->right, e, keycompare, elemkey, elemfree);

  ENSURES(is_ordtree(T));
  return T;
}

void bst_insert(bst B, elem e)
//@requires is_bst(B);
//@requires e != NULL;
//@ensures is_bst(B);
{
  REQUIRES(is_bst(B));
  REQUIRES(e != NULL);
  B->root = tree_insert(B->root, e, B->key_compare, B->elem_key, B->elem_free);
  ENSURES(is_bst(B));
  return;
}

void tree_free(tree *T, void (*elemfree)(elem e)) {
  REQUIRES(is_ordtree(T));
  if(T != NULL) {
    (*elemfree)(T->data);
    tree_free(T->left, elemfree);
    tree_free(T->right, elemfree);
    free(T);
  }
  return;
}

void bst_free(bst B) {
  REQUIRES(is_bst(B));
  tree_free(B->root, B->elem_free);
  free(B);
  return;
}