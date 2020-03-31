#include "avl.h"

// ----------------------------------functions to create a tree and nodes-----------------------------------------
//creates a tree
avltree * create_tree(entry* root)
{
    avltree * tree = malloc(sizeof(avltree));

    avltreenode* node = create_avl_node(root);

    if (tree != NULL) {
        tree->root = node;
    }
    return tree;
}

//creates an avltree node
avltreenode * create_avl_node(entry* item)
{   

    avltreenode * node = malloc(sizeof(avltreenode));
    if (node) {
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        node->data = item;
    }
    return node;
}


//----------------------------------functions to insert to tree and rotate if necessary---------------------------

avltreenode* insert_to_tree(avltreenode* node, entry* item) 

{
    int balance;

    if (node == NULL) {
        return(create_avl_node(item)); 
    }
  
    if (to_seconds(item->entryDate) < to_seconds(node->data->entryDate)) {
        node->left = insert_to_tree(node->left, item); 
    }
    else {
        node->right = insert_to_tree(node->right, item); 
    }
    
    
    node->height = 1 + max(get_tree_height(node->left),get_tree_height(node->right)); 
  
    balance = get_tree_balance(node); 
    
    //we check if the tree is still balanced or not
    // left left rotate
    if (balance > 1 && to_seconds(item->entryDate) < to_seconds(node->left->data->entryDate)) 
        return right_tree_rotate(node); 
  
    // Right Right rotate 
    if (balance < -1 && to_seconds(item->entryDate) > to_seconds(node->right->data->entryDate)) 
        return left_tree_rotate(node); 
  
    // Left Right rotate 
    if (balance > 1 && to_seconds(item->entryDate) > to_seconds(node->left->data->entryDate)) 
    { 
        node->left =  left_tree_rotate(node->left); 
        return right_tree_rotate(node); 
    } 
  
    // Right Left rotate
    if (balance < -1 && to_seconds(item->entryDate) < to_seconds(node->right->data->entryDate)) 
    { 
        node->right = right_tree_rotate(node->right); 
        return left_tree_rotate(node); 
    } 
    return node; 
} 


avltreenode *right_tree_rotate(avltreenode *y) 
{ 
    avltreenode *x = y->left; 
    avltreenode *subtree = x->right; 
  
    // Perform rotation 
    x->right = y; 
    y->left = subtree; 
  
    // Update heights 
    y->height = max(get_tree_height(y->left), get_tree_height(y->right))+1; 
    x->height = max(get_tree_height(x->left), get_tree_height(x->right))+1; 
  
    // Return new root 
    return x; 
} 
  
avltreenode *left_tree_rotate(avltreenode *x) 
{ 
    avltreenode *y = x->right; 
    avltreenode *subtree = y->left; 
  
    //rotation 
    y->left = x; 
    x->right = subtree; 
  
    //  Update heights 
    x->height = max(get_tree_height(x->left), get_tree_height(x->right))+1; 
    y->height = max(get_tree_height(y->left), get_tree_height(y->right))+1; 
  
    // Return new root 
    return y; 
} 

//-------------------------------------function to free the tree---------------------------------------------------

void avl_tree_free(avltreenode *root)
{
    // destroy all nodes 
     if(root!= NULL){
    
         avl_tree_free(root->left);
         avl_tree_free(root->right);
         free(root);

     }
}


// ---------------------------------------------------voithitikes-----------------------------------------
// get the height of the tree 
int get_tree_height(avltreenode* node) 
{ 
    if (node == NULL) 
        return 0; 

    return node->height; 
} 
  
int max(unsigned int  a, unsigned int b) 
{ 
    return( (a > b)? a : b ); 
} 

// balance of node 
int get_tree_balance(avltreenode* node) 
{ 
    if (node == NULL) 
        return 0; 
    return get_tree_height(node->left) - get_tree_height(node->right); 
}  