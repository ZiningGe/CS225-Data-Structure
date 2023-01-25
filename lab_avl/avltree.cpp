/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <cmath>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node*& t){
    if(t == NULL){
        return -1;
    }
    else{
        return t->height;
    }
}

template <class K, class V>
void AVLTree<K, V>::updateHeight(Node*& t){
    if(t == NULL){
        return;
    }
    if(t->left == NULL && t->right == NULL){
        t->height = 0;
    }
    else if(t->left == NULL){
        t->height = t->right->height + 1;
    }
    else if(t->right == NULL){
        t->height = t->left->height + 1;
    }
    else{
        t->height = fmax(t->left->height, t->right->height) + 1;
    }

}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* root = t->right;
    Node* left = t->right->left;
    root->left = t;
    t->right = left;
    updateHeight(t);
    updateHeight(root);
    t = root;



}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}




template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* root = t->left;
    Node* right = t->left->right;
    root->right=t;
    t->left = right;
    updateHeight(t);
    updateHeight(root);
    t = root;



}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //std::cout<<"curr line is "<<__LINE__<<std::endl;
    if (subtree == NULL){
        return;
    }
    int balancedheight = getHeight(subtree->right) - getHeight(subtree->left);
    //std::cout<<subtree->key<<" "<<balancedheight<<std::endl;
    if(balancedheight < -1){
        int left_balancedheight = getHeight(subtree->left->right) - getHeight(subtree->left->left);
        if (left_balancedheight < 0){
            rotateRight(subtree);
        }
        else{
            rotateLeftRight(subtree);
        }
    }
    else if(balancedheight > 1){
        int right_balancedheight = getHeight(subtree->right->right) - getHeight(subtree->right->left);
        if (right_balancedheight < 0){
            rotateRightLeft(subtree);
        }
        else{
            rotateLeft(subtree);
        }
    }


}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        subtree = new Node(key, value);
    }
    else if(key < subtree->key){
        insert(subtree->left, key, value);
    }
    else if(key > subtree->key){
        insert(subtree->right, key, value);
    }
    updateHeight(subtree);
    rebalance(subtree);
    

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::findIOP(Node*& t){
    Node* curr_ = t->left;
    while(curr_->right != NULL){
        curr_ = curr_->right;
    }
    return curr_;
}


template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    //std::cout<<subtree->key<<" "<<key<<std::endl;
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left,key);
        // your code here
    } else if (key > subtree->key) {
        remove(subtree->right,key);
        // your code here
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* IOP = findIOP(subtree);
            //std::cout<<IOP->key<<std::endl;
            swap(IOP,subtree);
            remove(subtree->left,key);
            

        } else {
            /* one-child remove */
            // your code here
            Node* temp = subtree;
            if(subtree->left == NULL){
                subtree = subtree->right;
            }
            else{
                subtree = subtree->left;
            }
            delete temp;
        }
        // your code here
        //updateHeight(subtree); 
    }
    
    rebalance(subtree);
}
