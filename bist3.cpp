#include<iostream>
using namespace std;
class node{
	public:
		int data;
		//children
		node* parent;
		node* left;
		node* right;
		
		//default constructor;
		node(int val){
			data=val;
			parent=NULL;
			left=NULL;
			right=NULL;
			;
		}
};

class bist{
	public:
		node* root;
		int count;
		//default;
		bist(){
			count=0;
			root=NULL;
		}
		void insertHelper(node* curr, int value){
			
			//current NULL, insert
			if (curr==NULL){
				curr=new node(value);
				count++;
				if (root==NULL){
					root=curr;
				}
				
				return;
			}
			//else compare and go to left or right
			else{
				if(curr->data>value){
					if (curr->left==NULL){
						curr->left=new node(value);
						count++;
						curr->left->parent=curr;
					}
					else insertHelper(curr->left, value);
				}
				else{
					if (curr->right==NULL){
						curr->right=new node(value);
						count++;
						curr->right->parent=curr;
					}
					else insertHelper(curr->right, value);
				}
			}
			//value < current->data   ...   move left  recurse
			//else   ...   move right  recuse
			
		}
		void insert(int value){
			insertHelper(root, value);
		}
		void display2(node* curr){
			//base condition
			if (curr==NULL)return;
			else{
				display2(curr->left);
				cout<<curr->data<<", ";
				display2(curr->right);
			}
		}
		
		void display(){
			display2(root);
			cout<<endl;
		}
		
		void print2DUtil(node *root, int space)  
    {  
        // Base case  
        if (root == NULL)  
            return;  
        // Increase distance between levels  
        space += 5;  
        // Process right child first  
        print2DUtil(root->right, space);  
    
        // Print current node after space  
        // count  
        cout<<endl;  
        for (int i = 5; i < space; i++)  
            cout<<" ";  
        cout<<root->data<<"\n";  
    
        // Process left child  
        print2DUtil(root->left, space);  
    }  
  
    // Wrapper over print2DUtil()  
    void print2D()  
    {  
        cout << "******************************" << endl;
        // Pass initial space count as 0  
        print2DUtil(root, 0);  
        cout << "******************************" << endl;
        
    }

		node* search_helper(node* curr,int value){
			if (curr==NULL||curr->data==value){
				return curr;
			}
			else if(curr->data>value){
				return search_helper(curr->left,value);
			}
			else{
				return search_helper(curr->right,value);
			}
		}
		
		node* search(int value){
			search_helper(root,value);
		}
		
		//find_min(node* curr)
		node* min_help(node* curr){
			while(curr->left!=NULL){
				curr=curr->left;
			}
			return curr;
		}
		node* find_min(int value){
			if (search(value)!=NULL) min_help(search(value));
			else cout<<"there is no such number\n";
		}
		//count_old
		void f_count_old(){
			cout<<count<<endl;
		}
		//void replace_At_Parent(Node * A, Node *B)
		void replace_At_Parent(node* par, node* chi){
			if(par!=root){
				//this code executes when the parent is not root
				chi->parent=par->parent;	//the child's parent is being updated here
				if(par->parent->left==par){	//if par is the left child of its parent
					par->parent->left=chi;	
				}
				else{						//if par is the right child of its parent
					par->parent->right=chi;
				}
				delete par;					//memory dealocation??
			}
			else{							//par is the root
				root=chi;					//root update
				delete par;					//memory dealocation
			}
		}
		
		// void deleteNode(int value)
		//helper
		void deleteHelper(node* curr){
			//case1: when curr is leaf -- 0 child
			if(curr->left==NULL && curr->right==NULL){
				if(curr!=root){
					if(curr->parent->left==curr){	//if curr is the left child of its parent
						curr->parent->left=NULL;	
					}
					else{							//if curr is the right child of its parent
						curr->parent->right=NULL;
					}
				}
				else{
					root=NULL;
				}
			}
			//case2: when curr has one right child
			else if(curr->left==NULL && curr->right!=NULL){
				replace_At_Parent(curr, curr->right);
			}
			//case3: when curr has one left child
			else if(curr->left!=NULL && curr->right==NULL){
				replace_At_Parent(curr, curr->left);
			}
			//case4: when curr has two child
			else{
				node* ptr=min_help(curr->right);
				curr->data=ptr->data;
				deleteHelper(min_help(curr->right));
			}
		}
		//local driver
		void deleteNode(int value){
			if(search(value)!=NULL){
				deleteHelper(search(value));
		 	}
		 	else{
		 		cout<<"the value is not present in the tree.\n";
		 	}
		}
		 
		 /*
		 Given a Binary Search Tree (BST), write a code for: 
			(7) int count(Node *) -> counting all the nodes in the BST 
			(8) int rangeSearch(int k1, int k2) ->range search: given two values k1 and k2, 
				print all the elements (or keys) x in the BST such that k1 <= x <= k2. 
				Also count the number of elements in the range from k1 to k2 and returns it. 
			(9) int height(Node *) -> Finds the height of the BST.
		 */
		 
		 //count function
		 //helper
		
    		int count_helper(node* curr){  
        		if (curr==NULL) 
            			return 0;
        		else    
            			return ( 1 + count_helper(curr->left) + count_helper(curr->right));  
    		}

		 //main driver
		 int countx(node* curr){
		 	return count_helper(curr);
		 }
		 //rangeSearch
		 //helper
		 int ranger(int k1,int k2,node* curr){
		 	if (curr==NULL)
		 		return 0;
		 	else{
				if(curr->data>=k1&&curr->data<=k2){
					cout<<curr->data<<", ";
					return (1+ranger(k1,k2,curr->left)+ranger(k1,k2,curr->right));
				}
				else if(curr->data<k1){
					return (ranger(k1,k2,curr->right));
				}
				else
					return (ranger(k1,k2,curr->left));
		 	}
		 }
		 //main driver
		 int rangeSearch(int k1, int k2){
		 	if(k1>k2){
		 		int temp=k1;
		 		k1=k2;
		 		k2=temp;
		 	}
		 	return ranger(k1, k2,root);
		 }
		 
		 //height
		 //max func
		 int max(int a,int b){
		 	if(a<b)return b;
		 	else return a;
		 }
		 //helper
		 int hyt_help(node* curr){
		 	if(curr==NULL){
		 		return 0;
		 	}
		 	else{
		 		return(1+max(hyt_help(curr->left),hyt_help(curr->right)));
		 	}
		 }
		 //driver
		 int height(node * curr){
		 	return hyt_help(curr)-1;
		 }
};
/*
int main(){
	bist b1;
	//cout<<b1.find_min(5)->data<<endl;
	b1.insert(10);
	b1.insert(5);
	b1.insert(-1);
	b1.insert(100);
	b1.insert(7);
	b1.display();
	if(b1.search(5)!=NULL){
		cout<<"found\n";
	}
	else{
		cout<<"Invalid input\n";
	}
	cout<<b1.find_min(5)->data<<endl;
	b1.f_count();
	return 0;
}
*/

int main(){
    
    bist bst1;
    bst1.insert(4);
    bst1.insert(2);
    bst1.insert(3);
    bst1.insert(1);
    bst1.insert(6);
    bst1.insert(5);
    bst1.insert(7);
    bst1.insert(8);
    bst1.display();
    cout<<"number of nodes is "<<bst1.countx(bst1.root)<<endl;
    cout<<bst1.rangeSearch(6, 3)<<endl;
    cout<<"height is "<<bst1.height(bst1.root)<<endl;
    /*
    if(bst1.search(3) != NULL){
        cout << endl << bst1.search(3)->data << endl;
    }*/
    bst1.print2D();
    /*
    bst1.deleteNode(6);
    bst1.print2D();
    bst1.deleteNode(5);
    bst1.print2D();
    cout << "Deleting 2" << endl;
    bst1.deleteNode(2);
    bst1.print2D();
    bst1.deleteNode(4);
    bst1.print2D();
    bst1.deleteNode(7);
    bst1.print2D();
    bst1.deleteNode(8);
    bst1.print2D();
    bst1.deleteNode(3);
    bst1.print2D();
    bst1.deleteNode(1);
    bst1.print2D();
    bst1.deleteNode(1);
    bst1.print2D();
*/
}
