/* Name: Owen Campbell
 * Purpose: Phase 2 of CS201 Project, Treap Maintanence.
 * Made with C++ Templates in order to manipulate various datatypes: ints, floats, chars, strings
 * Progress: Started out with two classes, then did one Treap class, but now seeing two classes 
 * (one for the treap and one fopr the nodes) is necessary for our required impementation
*/
//May need, struct for nodes, random etc
#include <bits/stdc++.h>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>

using  namespace std;

template <class T>
class TreapNode{
    public:
    T key;
    float priority;
    TreapNode *left, *right;
    int subtreeSize;

    TreapNode(){
       // key = "c";
        priority = 0.0;
        left = nullptr;
        right = nullptr;
        subtreeSize = 0; // helps with rank();
    }

};


template <class T>
class Treap{
    
    public:
     TreapNode<T> *root;  

    //default constructor for empty tree
        Treap(){
           root = nullptr; // helps with rank();
        }

    //constructor for node, used in insert function
    //insert should add random float from 0.0 to 1.0 if no priority is given
        Treap(T val, float p){
            root = newNode(val, p);   
        }

    //Constructor that builds tree with the given keys from k[], and priorities from p[]
        Treap(T k[], float p[], int s){
            root = newNode(k[0],p[0]);
            for(int i=1; i<s; i++){
               insert( k[i],p[i]);
            }
        }

        const Treap<T>& operator=(const Treap<T>& otherTree){ 
            
            if(this != &otherTree) //avoid self-copy
            {
                if(root != NULL)  //if the binary tree is not empty, 
                                //destroy the binary tree
                    deleteTree(root);

                if(otherTree.root == NULL) //otherTree is empty
                    root = NULL;
                else
                    copyTree(root, otherTree.root);
            }//end else

            return *this; 
        }

    //copy constructor
        Treap(const Treap<T>& otherTree){
            if(otherTree.root == NULL) //otherTree is empty
                root = NULL;
            else
                copyTree(root, otherTree.root);
        }

    //copy constructor
        void copyTree(TreapNode<T>* &copiedTreeRoot, TreapNode<T>* otherTreeRoot){
            if(otherTreeRoot == NULL)
                copiedTreeRoot = NULL;
            else{
                copiedTreeRoot = new TreapNode<T>;
                copiedTreeRoot->key = otherTreeRoot->key;
                copiedTreeRoot->priority = otherTreeRoot->priority;
                copyTree(copiedTreeRoot->left, otherTreeRoot->left);
                copyTree(copiedTreeRoot->right, otherTreeRoot->right);
            }
        } //end copyTree

    //most useful constructor for node, used in insert function
    //insert should add random float from 0.0 to 1.0 if no priority is given
        TreapNode<T>* newNode(T val, float p=(float)rand()/(float)RAND_MAX){
            TreapNode<T>* temp = new TreapNode<T>;
            temp->key = val;
            temp->priority = p; 
            temp->left = nullptr;
            temp->right = nullptr;
            temp->subtreeSize = getSubtreeSize(temp); 
            return temp;
        }

        //Returns subtree size = left + right + 1;
        //Had to make this function because initilizing null children caused issues
        int getSubtreeSize(TreapNode<T>* node){
            int size = 0;
            if(node->left){
                size += node->left->subtreeSize;
            }
            if(node->right){
                size += node->right->subtreeSize;
            }
            size++;
            return size;
        }
    
    //destructor for class
        ~Treap(){
            deleteTree(root);
        }
    
    //search, returns priority of key.. if key isnt stored, return -1 with helper function
        float search(T key){ 
           return helpSearch(root,key);
        }
   
    //Inserts the node with key k and priority p into the treap.
        void insert(T userKey, float p){ 
            root = insert(root, userKey,p); //could have used default parameter for root tpo not needd helper?
        }

    //Calls Insert function with key and root, updates root using helper function
        void insert(T userKey){ 
            root = insert(root, userKey);
        }
   
    //Removes the node with key k and returns 1. If the node containing key k has more than one child,
    // replace the key k and priority by the key and priority of the predecessor. The If key k is not
    // found then remove should return 0.
        int remove(T key){
           // if(deleteNode(root, key)!=1) return 0;
            return deleteNode(root,key);
        }

    //Returns the rank of the key k in the tree. Returns 0 if the key k is not found. The smallest item in
    //the tree is rank 1. Rank = "if tree was sorted, what pos would this val be"
       /* int rank(T key){
            int rank = 0;
            return rank;
        }*/
        int rank(T key){
            return rank(root,key);
        }
    
    //Order Statistics. Returns the key of the node at position pos in the tree. Calling with pos = 1
    //should return the smallest key in the tree, pos = n should return the largest.
        T select(int pos){
            return select(root, pos);
        }
    
    //Returns the key after k in the tree. 
       T successor(T key){ 
           return successor(key, root, root->key);
       }

    //Returns the key before k in the tree.
    //traverse from root left once then as far right as possible to 
    //get to the rightmost value of the left subtree 
        T predecessor(T key){ 
            return predecessor(key, root, root->key);
        }

    //returns the number of nodes in the tree.
        int size(){
            return root->subtreeSize;
        }

    //Prints the keys of the tree in a preorder traversal using a helepr function
        void preorder(){ 
            preorderPrint(root);
            cout<<endl;
        }
    //Prints the keys of the tree in an inorder traversal using a helper function
        void inorder(){ 
            inorderPrint(root);
            cout<<endl;
        }

    //Prints the keys of the tree in a postorder traversal.
        void postorder(){
            postorderPrint(root);
            cout<<endl;
        }
        void inorderTest(){
            inorderTest(root);
            cout<<endl;
        }

        void printMe(){
            printTreap(root);
        }
        void inorderTest(TreapNode<T>* rootNode){
            if (rootNode==nullptr) {
                //cout<<"its still null"<<endl;
                return;
            }
            inorderTest(rootNode->left);
            cout << rootNode->key <<" rank: "<< rank(rootNode->key)<<endl;
            inorderTest(rootNode->right);
        }
        void testInt(){ 
            int size = 10;
            //float P[10] = {0.2,0.95,0.7,0.4,0.5,0.3,0.8,0.1,0.9,0.6};
            float* priorities = new float[size]();
            for (int i=size;i>=0;i--){
                priorities[i] = rand()/(1.0 * RAND_MAX);
                root = insert(root,i,priorities[i]);
            }
            for(int i = 0; i<size; i+=2){
                cout<< "removing node: "<<i<<endl;
                remove(i);
                
                printMe();
            }
           /* for(int i=0; i<10; i++){
                root = insert(root,i+1,P[i]);   
            }*/
            inorder(); 
            cout<<"Search is: "<< search(3)<<endl; 
            cout<<"Predecessor is: "<< predecessor(5)<< endl;
            cout<<"Successor is: "<< successor(5)<< endl;
           // printMe();

        }
        void testChar(){ 
            float P[10] = {0.2,0.95,0.7,0.4,0.5,0.3,0.8,0.1};
            int key = 65; // A
            char nextKey =0;
            for(int i=0; i<8; i++){
                nextKey = (char)key;
                root = insert(root,nextKey,P[i]);
                key++;   
            }
            inorder();
            //char newKey ="C";
            cout<<"Search is: "<< search('C')<<endl; //0.7
            cout<<"Predecessor is: "<< predecessor('B')<< endl; //A
            cout<<"Successor is: "<< successor('E')<< endl; //F
            //printMe();
        }
        void testStr(){ 
            float P[10] = {0.2,0.95,0.7,0.4,0.5,0.3,0.8,0.1,0.9,0.6};
            string K[10] = {"A","AB","ABC","ABCD","ABCDE","ABCDEF","ABCDEFG","ABCDEFGH","ABCDEFGHI","ABCDEFGHIK"};
            for(int i=0; i<10; i++){
                root = insert(root,K[i],P[i]);  
            }
            inorder();
            //char newKey ="C";
            cout<<"Search is: "<< search("ABCDEFGHI")<<endl; 
            cout<<"Predecessor is: "<< predecessor("AB")<< endl;
            cout<<"Successor is: "<< successor("AB")<< endl;
            printMe();
        }
        //Returns LEFT subtree size = left
            //Had to make this function because initilizing null children caused issues
        int getRSubtreeSize(TreapNode<T>* node){
            int size = 0;
            if(node->right){
                size += node->right->subtreeSize;
            }
            return size;
        }
    //Mostly Helper Functions,
    private:

    //Rotate left child to right, becomes parent, shifts former right child 
    //over to become left child of former parent and updates subtree values
        TreapNode<T> *rightRotate(TreapNode<T> *parent){
            TreapNode<T> *rotateNode = parent->left,  *switchChild = rotateNode->right;

            int size = rotateNode->subtreeSize;
            parent->subtreeSize -= size; //take off left subtree val
        
            // Perform rotation
            rotateNode->right = parent;
            parent->left = switchChild;
            if(switchChild){
                parent->subtreeSize += switchChild->subtreeSize; // add new child value
                rotateNode->subtreeSize-= switchChild->subtreeSize; // take of child value given away
            }
            rotateNode->subtreeSize += parent->subtreeSize;// add new child size

            // Return new root
            return rotateNode;
        }


     //Rotate right child to left, becomes parent, shifts former left child 
    //over to become right child of former parent and updates subtree values
        TreapNode<T> *leftRotate(TreapNode<T> *parent){
            TreapNode<T> *rotateNode2 = parent->right,  *switchChild = rotateNode2->left;

            int size = rotateNode2->subtreeSize; //sub size of right childs subtree
            parent->subtreeSize -= size; //take off right subtree val

            // Perform rotation
            rotateNode2->left = parent;
            parent->right = switchChild;

            if(switchChild){
                parent->subtreeSize += switchChild->subtreeSize;  // add new child value
                rotateNode2->subtreeSize-= switchChild->subtreeSize; // take of child value given away
            }
            rotateNode2->subtreeSize += parent->subtreeSize;//getSubtreeSize(switchChild);
            // Return new root
            return rotateNode2;
        }

            /* This function traverses tree
        in post order to delete each
        and every node of the tree */
        void deleteTree(TreapNode<T>* node)
        {
            if (node == NULL) return;
        
            /* first delete both subtrees */
            deleteTree(node->left);
            deleteTree(node->right);
            
            /* then delete the node */
           // cout << "\n Deleting node: " << node->key;
            delete node;
        }
        
                // Recursive function to delete a key from a given treap
        int deleteNode(TreapNode<T>* &root, T key, int val=0){
            //cout<< "made it top"<<endl;
            
            // base case: the key is not found in the tree
            if (root == nullptr) {
                return val;
            }
        
            // if the key is less than the root node, recur for the left subtree
            if (key < root->key) {
                root->subtreeSize--;
               return val = deleteNode(root->left, key,val);
               //subsize --1;
            }
        
            // if the key is more than the root node, recur for the right subtree
            else if (key > root->key) {
                root->subtreeSize--;
                return val = deleteNode(root->right, key,val);
                //subsize --1
            }
        
            // if the key is found
            else {
                val = 1;
                // Case 1: node to be deleted has no children (it is a leaf node)
                if (root->left == nullptr && root->right == nullptr)
                {
                    // deallocate the memory and update root to null
                    delete(root);
                    root = nullptr;
                }
        
                // Case 2: node to be deleted has two children
                else if (root->left && root->right)
                {
                    // if the left child has greater priority than the right child
                    if (root->left->priority > root->right->priority)
                    {
                        // call `rotateLeft()` on the root
                        root = leftRotate(root);
                        root->subtreeSize--;
        
                        // recursively delete the left child
                        return val = deleteNode(root->left, key,val);
                    }
                    else {
                        // call `rotateRight()` on the root
                        root = rightRotate(root);
                        root->subtreeSize--;
        
                        // recursively delete the right child
                      return val = deleteNode(root->right, key,val);
                    }
                }
        
                // Case 3: node to be deleted has only one child
                else {
                    // choose a child node
                    //cout<< "made it here"<<endl;
                    TreapNode<T>* child = (root->left)? root->left: root->right;
                    TreapNode<T>* curr = root;
        
                    root = child;
        
                    // deallocate the memory
                    delete (curr);
                }
            }
            return val;
        }
 
            //Inserts the node with key k, and optional p, checks to left and right down the tree,
    //inserts in correct spot then checks heap violations
        TreapNode<T>* insert(TreapNode<T>* rootNode, T userKey,float p=(float)rand()/(float)RAND_MAX){ 
                    
            if (root==nullptr){    // Insert the first node, if root is NULL. unecessary..
                root = newNode(userKey,p);
                return root;
            }
            if (rootNode==nullptr){    // Insert the new node, if location is NULL.
                rootNode = newNode(userKey,p);
                return rootNode;
            }
        
            if (userKey >= rootNode->key){    // Insert right node key, if the userKey >= root
                rootNode->subtreeSize++;     //Inc subtree size going down
                rootNode->right = insert(rootNode->right, userKey , p);

                if(rootNode->right->priority < rootNode->priority){ //fix heap violations
                     rootNode = leftRotate(rootNode);
                }
            }
            else{   // Insert left node data, if the val is less than current key
                rootNode->subtreeSize++;  //Inc subtree size going down
                rootNode->left = insert(rootNode->left, userKey, p);

                if(rootNode->left->priority < rootNode->priority){  //fix heap violations
                     rootNode = rightRotate(rootNode);
                }      
            }
            // Return 'root' node, after insertion.
            return rootNode;
        }
        

    // Utility function to print two-dimensional view of a treap using
    // reverse inorder traversal - not required for grading
    //source: https://www.techiedelight.com/implementation-treap-data-structure-cpp-java-insert-search-delete/
        void printTreap(TreapNode<T> *root, int space = 0, int height = 10)
        {
            // Base case
            if (root == nullptr) {
                return;
            }
        
            // increase distance between levels
            space += height;
        
            // print the right child first
            printTreap(root->right, space);
            cout << endl;
        
            // print the current node after padding with spaces
            for (int i = height; i < space; i++) {
                cout << ' ';
            }
            cout << root->key << "(" << root->priority << ") "<< root->subtreeSize<< "\n";
        
            // print the left child
            cout << endl;
            printTreap(root->left, space);
        }


    //Prints the keys of the tree in an inorder traversal.
        void inorderPrint(TreapNode<T>* rootNode){
            if (rootNode==nullptr) {
                //cout<<"its still null"<<endl;
                return;
            }
            inorderPrint(rootNode->left);
            cout << rootNode->key <<" ";
            inorderPrint(rootNode->right);
        }
        

    //Prints the keys of the tree in an preorder traversal.
        void preorderPrint(TreapNode<T>* rootNode){
                if (rootNode==nullptr) {
                    //cout<<"its still null"<<endl;
                    return;
                }
                cout << rootNode->key <<" ";
                preorderPrint(rootNode->left);
                preorderPrint(rootNode->right);
            }

    //Prints the keys of the tree in a post order traversal
        void postorderPrint(TreapNode<T>* rootNode){
            if (rootNode == NULL)
            return;
        
            postorderPrint(rootNode->left);
            postorderPrint(rootNode->right);
            cout << rootNode->key << " ";
        }

    //returns successor of given key or key
         T successor(T key, TreapNode<T>* node , T bestValue){
           
            // if we reach null, return key or successor
            if (node==nullptr) {
                if(bestValue <= key) //successor should never be lower than key
                    return key;
                else{
                     return bestValue;
                }
            }
            
            if(key < node->key){ //ex 6 < @10 Go Left
                bestValue = node->key;
                return successor( key, node->left, bestValue);
            }
            else if(key > node->key){ //ex 6 > 3 Go Right  
                return successor( key, node->right, bestValue);
            }
             // If at node of key, go right
            return successor( key, node->right, bestValue);   
        }


        //returns predecessor of given key or key
        //Proud of these functions (pred and suc) because I figured out an algorithim myself from basic search
        //But it isnt the best, it does extra  comparisons and variable assignments both about (log(n)) that other methods
        //wouldnt have to- should run about same time as search
        T predecessor(T key, TreapNode<T>* node , T bestValue){

            // if we reach null, return key or predecessor
            if (node==nullptr) {
                if(bestValue >= key)
                    return key;
                else{
                     return bestValue;
                }
            }
            
            if(key < node->key){ //ex 6 < @10 Go Left
                return predecessor( key, node->left, bestValue);
            }
            else if(key > node->key){ //ex 6 > 3 Go Right  
                bestValue = node->key;
               return predecessor( key, node->right, bestValue);
            }
            // If at node of key, go left     
            return predecessor( key, node->left, bestValue);
        }

        //thought i needed to return an entire node for one of my functions to work, was wrong
        TreapNode<T>* predecessorSearch(T key, TreapNode<T>* currNode){

            while (currNode){
                // if we reach null, return key or predecessor
                if (currNode->right==nullptr) {
                    return currNode;
                }
                
                if(key == currNode->key ){ //ex 6 > 3 Go Right  
                    currNode = currNode->left;
                }
                else if(currNode->right != nullptr){
                    currNode = currNode->right;
                }
            }
            return currNode;
        }

     //Returns LEFT subtree size = left
        //Had to make this function because initilizing null children caused issues
    int getLSubtreeSize(TreapNode<T>* node){
        int size = 0;
        if(node->left){
            size += node->left->subtreeSize;
        }
        return size;
    }
   
//didnt use rank because i hadnt thought that out + it may mess up runtime
//element at pos xin sorted array
    T select(TreapNode<T>* currNode, int pos){
        int currNodeRank = 0;
        T keyGiven = currNode->key;
        // int rank = 0; PUT IN MAIN RANK FUNCTION
        while(currNode){  
            currNodeRank += getLSubtreeSize(currNode) + 1; //rank of currNode
            if(pos == currNodeRank){   //Found match
              //  cout<<"made it "<<endl;
                return currNode->key;
            }
            else if(pos > currNodeRank){ //node to find not in items on left
                currNode = currNode->right;
            }
            else if(pos < currNodeRank){ //root too big, go left
                currNodeRank -= getLSubtreeSize(currNode)+ 1; //rank of previousNode 
                currNode = currNode->left;
            }
        }
        return keyGiven;//
    }

    //Takes left child of root and calculates rank from there
    //pos of element x in ordered array
    int rank( TreapNode<T>* currNode, T keyToFind){ // Works!
     
        int rank = 0;
        while(currNode){  //chose -> instead of just key so be sure next node key is accesed and not main  key
            if(currNode->key == keyToFind){   //Found match
                rank+= getLSubtreeSize(currNode) + 1; //add elft subtree
                return rank;
            }
            else if(currNode->key > keyToFind){ //root too big, go left
                currNode = currNode->left; //things to right dont contribute
            }
            else if(currNode->key < keyToFind){ // root too small, go right, inc value by things to left
                rank+= getLSubtreeSize(currNode)+1;//->left->subtreeSize +1;
                currNode = currNode->right;
            }
        }
        return rank;
    }

    // Recursive function to search for a key in a given treap
    // simple algorithim I already used in insert, so I borrowed this function to save time
    // source: techiedelight
        float helpSearch(TreapNode<T>* root, T key){ 

            // if the key is not present in the tree
            if (root == nullptr) {
                return -1;
            }
        
            // if the key is found
            if (root->key == key) {
                return root->priority;
            }
        
            // if the key is less than the root node, search in the left subtree
            if (key < root->key) {
                return helpSearch(root->left, key);
            }
        
            // otherwise, search in the right subtree
            return helpSearch(root->right, key);
        }
};
