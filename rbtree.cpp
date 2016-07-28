/* 

rbtree.cpp performs all the red black tree operations
such as insert,find,delete and print.
All the algorithms for rbtree operations are referred
from cormen.
 
by : Kshitija Karkar 
*/
#include <iostream>
#include <iomanip>
#include "rbtree.h"
#include<vector>

using std::cout;
using std::setw;
using std::endl;

/********************************************************************
RBTree() to assign nil node and initialise root node to nil
and its parent to nil
Set color to black.
********************************************************************/

RBTree::RBTree()
{
   nil = new Node();
   root = nil;
   root->parent  = nil;
   root->parent->color = 'B';
}

/********************************************************************
~RBTree() to delete all the nodes when program ends.

********************************************************************/

RBTree::~RBTree()
{
   postOrder_tree_walk(root); 
   delete nil;
}
/********************************************************************
postOrder_tree_walk() traverse all the nodes in postorder() way
and delete node. This function is used in ~RBTree() to traverse
abd delete all nodes.
IN : Node *
OUT : N.A.
********************************************************************/

void RBTree::postOrder_tree_walk(Node *x)
{ 
   if(x != nil)
   {
      postOrder_tree_walk(x->left);
      postOrder_tree_walk(x->right);
      delete x;
   }  
}

/********************************************************************
parameterized Node() to insert key and value into the node.
IN : String k,v and Node*
OUT :N.A.
********************************************************************/

RBTree::Node::Node(const string &k, const string &v, Node *x)
{
   this->key = new string(k);
   this->value = new string(v);
   this->left = x;
   this->right = x;
   this->parent = x;
}

/********************************************************************
Node() to set left,right,parent pointers to nil and color to
black.
********************************************************************/

RBTree::Node::Node()
{
   this->left = NULL;
   this->right = NULL;
   this->parent = NULL;
   color = 'B';
}


/********************************************************************
~Node() deletes data inside the node.

********************************************************************/
RBTree::Node::~Node()
{
   delete key;
   delete value;
}

/********************************************************************
rbInsert() calls Node() to pass key and value that needs to be 
inserted.
IN : string key and value
OUT : N.A.
********************************************************************/

void RBTree::rbInsert(const string& key, const string& value)
{
   Node *z = NULL;
   z = new Node(key,value,nil);
   rbInsert(z);
}

/********************************************************************
rbInsert() inserts the node thus formed into the rbtree.
IN : Node
OUT :N.A.
********************************************************************/

void RBTree::rbInsert(Node *z)
{
   Node *x;
   Node *y;
   y = nil;
   x = root;
   while(x != nil) //traverse
   {
      y = x;
      if(*(z->key) < *(x->key))
         x = x->left;
      else
         x = x->right;
   }
   z->parent = y;
   if(y == nil)  //first node
     root = z;
   else if(*(z->key) < *(y->key))  //new node has less value
     y->left = z;
   else
     y->right = z;
   z->left = nil;    //set the pointers
   z->right = nil;
   z->color = 'R';
   rbInsertFixup(z); // to balance tree.
}

/********************************************************************
rbInsertFixup() to balance the unbalanced tree. It calls left or
right rotate accordingly.
IN : Node *
OUT : N.A.
********************************************************************/

void RBTree:: rbInsertFixup(Node *z)
{
   Node *y;
   while(z->parent->color=='R')
   {
      if(z->parent==z->parent->parent->left)
      {
          y=z->parent->parent->right;
          if(y->color=='R')                 //case 1
          {
             z->parent->color='B';
             y->color='B';
             z->parent->parent->color='R';
             z=z->parent->parent;
          }
          else                             //case 2
          {
             if(z==z->parent->right)
             {
                z=z->parent;
                leftRotate(z);
             }
             z->parent->color='B';           //case 3
             z->parent->parent->color='R';
             rightRotate(z->parent->parent);
          }
      }
      else
      {
          y=z->parent->parent->left;
          if(y->color=='R')
          {
             z->parent->color='B';
             y->color='B';
             z->parent->parent->color='R';
             z=z->parent->parent;
          }
          else 
          {
             if(z==z->parent->left)
             {
                z=z->parent;
                rightRotate(z);
             }
             z->parent->color='B';
             z->parent->parent->color='R';
             leftRotate(z->parent->parent);
           }
       }
   }
   root->color='B';
}

/********************************************************************
rbFind() to find all nodes with multiple key occurrences.
IN : String key
OUT : vector containing all nodes with same key
********************************************************************/

vector<const string*> RBTree::rbFind(const string& key)
{
   vector <const string *> mul;
   Node *y;
   Node *w;
   Node *z;
   y = rbTreeSearch(root,key);
   if(y != nil)
      mul.push_back((y->value)); //store in vector
   z = y;
   w = y;
   if((y->left) != nil || (y->right)!=nil)
   {
     while(z!=nil )
     {
        z = rbTreeSuccessor(z);
        if(z!= nil && *(z->key)==key)
           mul.push_back((z->value));
     }
     while(w!=nil)
     {
        w = rbTreePredecessor(w);
        if(w!=nil&&*(w->key)==key)
           mul.push_back((w->value));
     }
   }
   return mul;
}

/********************************************************************
rbTreeSuccessor() to find the node that should be replaced when 
a node is deleted.
IN : Node *
OUT : node that is to be replace
********************************************************************/

RBTree::Node* RBTree::rbTreeSuccessor(Node *x)
{
   Node *y;
   if(x->right != nil) //traverse to left
      return (rbTreeMinimum(x->right));
   y = x->parent;
   while(y != nil && x == y->right)
   {
      x = y; //set the node in place of node to be deleted
      y = y->parent;
   }
   return y;
}


/********************************************************************
rbTreeMinimum() to find the successor of given node
IN : Node
OUT : Node that is the successor.
********************************************************************/

RBTree::Node* RBTree::rbTreeMinimum(Node *x)
{
   while(x->left != nil)
      x = x->left; 
   return x;
}

/********************************************************************
rbTreePredecessor()to find the node that should be replaced when 
a node is deleted.
IN : Node
OUT : node that is to be replace
********************************************************************/

RBTree::Node* RBTree::rbTreePredecessor(Node *x)
{
   Node *y;
   if(x->left != nil)
      return (rbTreeMaximum(x->left));
   y = x->parent;
   while(y != nil && x == y->left)
   {
      x = y;
      y = y->parent;
   }
   return y;
}

/********************************************************************
rbTreeMaximum() to find the predecessor of given node
IN : Node
OUT : Node that is the predecessor.
********************************************************************/

RBTree::Node* RBTree::rbTreeMaximum(Node *x)
{
   while(x->right != nil)
      x = x->right;
   return x;

}

/********************************************************************
rbTreeSearch() to search the node
IN : Node and key that is to be searched
OUT : recurrsive calls to left and right tree to find the node
********************************************************************/

RBTree ::Node* RBTree::rbTreeSearch(Node *x, const string &k)
{
   if(x==nil || *(x->key) == k)
      return x;
   if(k < *(x->key))
      return (rbTreeSearch(x->left,k));
   else
      return (rbTreeSearch(x->right,k));
}   

/********************************************************************
leftRotate() to balance the tree. Rotates tree to left.
IN : Node
OUT N.A.
********************************************************************/


void RBTree:: leftRotate(Node *x)
{
   Node *y;
   y = x->right;
   x->right = y->left; //turn y's subtree into x's subtree
   if(y->left != nil)
      y->left->parent=x;
   y->parent = x->parent;  //link x's parent to y
   if(x->parent == nil)
     root = y;
   else if(x == x->parent->left)
     x->parent->left=y;
   else
     x->parent->right = y;
   y->left = x;          //put x on y's left
   x->parent = y;
}

/********************************************************************
rightRotate() to balance the tree. Rotates tree to right.
IN : Node
OUT N.A.
********************************************************************/

void RBTree:: rightRotate(Node *x)
{
   Node *y;
   y = x->left;
   x->left = y->right; //turn x's subtree into y's subtree
   if(y->right != nil)
      y->right->parent=x;
   y->parent = x->parent;  //link y's parent to x
   if(x->parent == nil)
      root = y;
   else if(x == x->parent->right)
      x->parent->right=y;
   else
      x->parent->left = y;
   y->right = x;  //put y on x's right
   x->parent = y;
}

/********************************************************************
rbDelete() deletes the node with matching key and value
IN : string key and value
OUT : N.A.
********************************************************************/
void RBTree::rbDelete(const string& key, const string& value)
{
	Node *x;
   Node *succ;
   Node *pred;
   x = rbTreeSearch(root, key);
   while(x != nil)
   {
		if(*(x->value) == value)
		{
			rbDelete(x);
			delete x;
			x = rbTreeSearch(root, key); //search again as node is deleted
		}
		pred = x;
		while(pred != nil)
		{
			pred = rbTreePredecessor(pred); //match found
			if(pred != nil && (*(pred->key) == key) && (*(pred->value) == value))
			{
				rbDelete(pred);
				delete pred;
				pred = rbTreeSearch(root, key);
			}
		}
		succ = rbTreeSearch(root, key);
      while(succ != nil)
		{
			succ = rbTreeSuccessor(succ);
			if(succ != nil && (*(succ->key) == key) && (*(succ->value) == value))
			{
				rbDelete(succ); 
				delete succ;
				succ = rbTreeSearch(root, key);
			}
		}
		x = rbTreeSearch(root, key);
		if((x != nil) && *(x->value) == value)
		{			
        	rbDelete(x);
			delete x;
			x = rbTreeSearch(root, key);
		}
		else
		{
			break;
		}
   }
}

/********************************************************************
rbDelete() deletes the node and performs transplant to re arrange
the tree
IN : Node
OUT :N.A.
********************************************************************/

void RBTree::rbDelete(Node *z)
{
   Node *x;
   Node *y;
   y = z;
   char y_original_color = y->color;
   if(z->left == nil)
   {
      x = z->right;
      rbTransplant(z,z->right);
   }
   else if(z->right == nil)
   {
      x = z->left;
      rbTransplant(z,z->left);
   }
   else
   {
       y = rbTreeMaximum(z->left); //replace with the predecessor.
       y_original_color = y->color;
       x = y->left;
       if(y->parent == z)
          x->parent = y;
       else
       {
          rbTransplant(y,y->left);
          y->left = z->left;
          y->left->parent = y; 
       } 
       rbTransplant(z,y);
       y->right = z->right;
       y->right->parent = y;
       y->color = z->color;
   }
   if(y_original_color == 'B')
      rbDeleteFixup(x);  
}

/********************************************************************
rbDeleteFixup() to restore rbtree properties
IN : N.A.
OUT : N.A.
********************************************************************/ 

void RBTree:: rbDeleteFixup(Node *x)
{
   Node *w;
   while(x != root && x->color == 'B')
   {
      if(x == x->parent->left)
      {
         w = x->parent->right;
         if(w->color == 'R')
         {
            w->color = 'B';                  //case 1
            x->parent->color = 'R';
            leftRotate(x->parent);
            w = x->parent->right;
         }
         if(w->left->color == 'B' && w->right->color == 'B')
         {
 	         w->color = 'R';                  //case 2
            x = x->parent;
         }
         else if(w->right->color == 'B')
         {     w->left->color = 'B';          //case 3
               w->color = 'R';
               rightRotate(w);
               w = x->parent->right;
         }
         else
         {
            w->color = x->parent->color;      //case 4
            x->parent->color = 'B';
            w->right->color = 'B';
            leftRotate(x->parent);
            x = root;
         }        
      }
      else
      {
         w = x->parent->left;
         if(w->color == 'R')
         {
            w->color = 'B';
            x->parent->color = 'R';
            rightRotate(x->parent);
            w = x->parent->left;
         }
         if(w->right->color == 'B' && w->left->color == 'B')
         {
 	         w->color = 'R';
            x = x->parent;
         }
         else if(w->left->color == 'B')
         {
            w->right->color = 'B';
            w->color = 'R';
            leftRotate(w);
            w = x->parent->left;
         }
         else
         {
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->left->color = 'B';
            rightRotate(x->parent);
            x = root;
         }        
      }
   }
   x->color = 'B';
}
 
/********************************************************************
rbTransplant() to replace the node and set all the links
IN : Node u and v
OUT : N.A.
********************************************************************/
void RBTree::rbTransplant(Node *u, Node *v)
{
   if(u->parent == nil)
      root = v;
   else if(u == u->parent->left)
      u->parent->left = v;
   else
      u->parent->right = v;
   v->parent = u->parent;
}

/********************************************************************
rbPrintTree() - calls reverseInorder() to print the tree
IN :N.A.
OUT :N.A.
********************************************************************/
void RBTree::rbPrintTree()
{
  Node *z;
  z = root;
  reverseInOrderPrint(z, 0);
}


/********************************************************************
reverseInOrderPrint() prints the tree in inorder fashion
IN : Node and depth
OUT : N.A.
********************************************************************/

void RBTree::reverseInOrderPrint(Node *x, int depth) {
   if ( x != nil ) {
       reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}
