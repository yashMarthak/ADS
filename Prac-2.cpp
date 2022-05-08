#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct tree
{
    int key,height;
    char object;
    struct tree* left;
    struct tree* right;
}*root;

int getheight(struct tree* node)
{
	if(node==NULL)
		return 0;
	return node->height;
}

struct tree* rightrotate(struct tree* node)
{
	struct tree* temp1=node->left;
	struct tree* temp2=temp1->right;
	
	temp1->right=node;
	node->left=temp2;
	
	node->height=1+max(getheight(node->left),getheight(node->right));
	temp1->height=1+max(getheight(temp1->left),getheight(temp1->right));
	
	if(root==node)
		root=temp1;
	return temp1;
}

struct tree* leftrotate(struct tree* node)
{
	struct tree* temp1=node->right;
	struct tree* temp2=temp1->left;
	
	temp1->left=node;
	node->right=temp2;
	
	node->height=1+max(getheight(node->left),getheight(node->right));
	temp1->height=1+max(getheight(temp1->left),getheight(temp1->right));
	
	if(root==node)
		root=temp1;
	return temp1;
}

struct tree* insertnode(struct tree* t,int x,char y)
{
	if(t==NULL)
	{
		t=(struct tree*)malloc(sizeof(struct tree));
		t->key=x;
		t->height=1;
		t->object=y;
		t->left=NULL;
		t->right=NULL;
		
		cout<<"\nSuccessfully Inserted :)"<<endl;
		
		if(root==NULL)
			root=t;
		return t;
	}
	
	else
	{
		if(t->key>x)
			t->left=insertnode(t->left,x,y);
		else if(t->key<x)
			t->right=insertnode(t->right,x,y);
	    else
	    {
			cout<<"\n!!! Dublicate key found !!!\n";
	    	return t;
	    }
	}
	
	t->height=1+max(getheight(t->left),getheight(t->right));
	
	int check=getheight(t->left) - getheight(t->right);
	
	if(check>1 && x < t->left->key)
		return rightrotate(t);
		
	else if(check<-1 && x > t->right->key)
		return leftrotate(t);
		
	else if(check>1 && x > t->left->key)
	{
		t->left=leftrotate(t->left);
		return rightrotate(t);
	}
	
	else if(check<-1 && x < t->right->key)
	{
		t->right=rightrotate(t->right);
		return leftrotate(t);
	}
	
	return t;
}

struct tree* minval(struct tree* node)
{
	struct tree* temp=node;
	while(temp->left!=NULL)
		temp=temp->left;
	return temp;
}

struct tree* deletenode(struct tree* t,int x)
{
	if(t==NULL)
		return t;
	
	if(x<t->key)
		t->left=deletenode(t->left,x);
	else if(x>t->key)
		t->right=deletenode(t->right,x);
	else
	{
		if(t->left==NULL || t->right==NULL)
		{
			struct tree* temp = t->left ? t->left : t->right;
			
			if(temp==NULL)
			{
				temp=t;
				t=NULL;
			}
			else
				t=temp;
				
			free(temp);
			cout<<"\nSuccessfully Deleted :)";
		}
		
		else
		{
			struct tree* temp=minval(t);
			t->key=temp->key;
			t->left=deletenode(t->left,temp->key);
		}
	}
	
	if(t==NULL)
		return t;
		
	t->height=1+max(getheight(t->left),getheight(t->right));
	
	int check=getheight(t->left) - getheight(t->right);
	
	if(check>1 && (getheight(t->left->left) - getheight(t->left->right) >=0))
		return rightrotate(t);
		
	else if(check<-1 && (getheight(t->right->left) - getheight(t->right->right) <=0))
		return leftrotate(t);
		
	else if(check>1 && (getheight(t->left->left) - getheight(t->left->right) <0))
	{
		t->left=leftrotate(t->left);
		return rightrotate(t);
	}
	
	else if(check<-1 && (getheight(t->right->left) - getheight(t->right->right) >0))
	{
		t->right=rightrotate(t->right);
		return leftrotate(t);
	}
	
	return t;
}

void create()
{	
	ifstream datafile("input.txt");
    string line="";
    
    while(getline(datafile, line))
	{
        vector<string> tokens;
        stringstream temp(line);
        string intermediate;
        
        while(getline(temp, intermediate, ' '))
            tokens.push_back(intermediate);
            
        insertnode(root,stoi(tokens[0]),tokens[1][0]);
    }
    datafile.close();

    cout<<"\nSuccessfully Created Your AVL Tree. :)"<<endl;
}

void preorder(struct tree* node)
{
	if(node==NULL)
		return;
	cout<<node->key<<"->"<<node->object<<endl;
	preorder(node->left);
	preorder(node->right);
}

int main()
{
    while(true){
    int c;
    cout<<"\nWhat you want to do?:-"<<endl;
    cout<<"1) Create a new AVL tree. \n2) Insert a new node in existing AVL tree."<<endl;
    cout<<"3) Delete a node from existing AVL tree. \n4) Display AVL tree (preorder). \n5) Exit."<<endl;

    cout<<"\nEnter Your Choice: ";
    cin>>c;

    if(c==1)
        create();

    else if(c==2)
    {
        if(root==NULL)
            cout<<"\nSorry, AVL tree does not exist! :("<<endl;
        else
        {
            int x;
            char y;
            cout<<"\nEnter key for new node: ";
            cin>>x;
            cout<<"Enter object for that node: ";
            cin>>y;

            insertnode(root,x,y);
        }
    }

    else if(c==3)
    {
        if(root==NULL)
            cout<<"\nSorry, AVL tree does not exist! :("<<endl;
        else
        {
            int x;
            cout<<"\nEnter key of the node that you want to delete: ";
            cin>>x;

            root=deletenode(root,x);
        }
    }

    else if(c==4)
    {
        if(root==NULL)
            cout<<"\nSorry, AVL tree does not exist! :("<<endl;
        else
            preorder(root);
    }

    else if(c==5)
        break;
    
    else
        cout<<"\nInvalid Input! :("<<endl;

    cout<<"\n-------------------------------------------------"<<endl;
    }
    return 0;
}
