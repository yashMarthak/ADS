#include<bits/stdc++.h>
using namespace std;

class Tree
{
public:
	int key;
	char object;
    Tree *left, *right, *parent;
    
    Tree(int x,char y)
    {
        key=x;
        object=y;
        left=right=parent=NULL;
    }
};

Tree *root;
int q=0;

int getsize(Tree *node)
{
    if (node==NULL)
        return 0;
    return 1+getsize(node->left)+getsize(node->right);
}

int log32(int n)
{
    double x=2.4663034623764317;
    return (int)ceil(x*log(n));
}

Tree* rebalance(Tree **a,int i, int n)
{
    if(n==0)
    	return NULL;
    int m=n/2;
  
    a[i+m]->left=rebalance(a,i,m);
    if(a[i+m]->left != NULL)
        a[i+m]->left->parent = a[i+m];
  
    a[i+m]->right=rebalance(a,i+m+1,n-m-1);
    if (a[i+m]->right != NULL)
        a[i+m]->right->parent = a[i+m];
  
    return a[i+m];
}

int bstInsert(Tree *t)
{
    Tree *temp=root;
    if (temp==NULL)
    {
        root=t;
        q++;
        cout<<"\nSuccessfully Inserted :)"<<endl;
        return 0;
    }
  
    bool flag=false;
    int d=0;
    do
    {
        if(t->key < temp->key)
        {
            if(temp->left==NULL)
            {
                temp->left=t;
                t->parent=temp;
                flag=true;
            }
            else
                temp=temp->left;
        }
        else if(t->key > temp->key)
        {
            if(temp->right==NULL)
            {
                temp->right=t;
                t->parent=temp;
                flag=true;
            }
            else
                temp=temp->right;
        }
        else
	    {
			cout<<"\n!!! Dublicate key found !!!\n";
	    	return -1;
	    }
        d++;
    }
    while(flag==false);
  
    q++;
    cout<<"\nSuccessfully Inserted :)"<<endl;
    return d;
}

int store(Tree *temp, Tree *a[], int i)
{
    if(temp==NULL)
        return i;
  
    i=store(temp->left,a,i);
    a[i++]=temp;
    return store(temp->right,a,i);
}

void rebuild(Tree *t)
{
    int n=getsize(t);
    Tree *p=t->parent;
    
    Tree **a=new Tree* [n];
    store(t,a,0);
    
    if(p==NULL)
    {
        root=rebalance(a,0,n);
        root->parent=NULL;
    }
    else if (p->right==t)
    {
        p->right=rebalance(a,0,n);
        p->right->parent=p;
    }
    else
    {
        p->left=rebalance(a,0,n);
        p->left->parent=p;
    }
}

bool insertnode(int x,char y)
{
    Tree *node=new Tree(x,y);

    int h=bstInsert(node);
  
    if (h>log32(q))
    {
        Tree *p=node->parent;
        while(3*getsize(p)<=2*getsize(p->parent))
            p=p->parent;
  
        rebuild(p->parent);
    }
  
    return h>=0;
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
            
        insertnode(stoi(tokens[0]),tokens[1][0]);
    }
    datafile.close();

    cout<<"\nSuccessfully Created Your AVL Tree. :)"<<endl;
}

void preorder(Tree *node)
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
    cout<<"1) Create a new ScapeGoat tree. \n2) Insert a new node in existing ScapeGoat tree."<<endl;
    cout<<"3) Display ScapeGoat tree (preorder). \n4) Exit."<<endl;

    cout<<"\nEnter Your Choice: ";
    cin>>c;

    if(c==1)
        create();

    else if(c==2)
    {
        if(root==NULL)
            cout<<"\nSorry, ScapeGoat tree does not exist! :("<<endl;
        else
        {
            int x;
            char y;
            cout<<"\nEnter key for new node: ";
            cin>>x;
            cout<<"Enter object for that node: ";
            cin>>y;

            insertnode(x,y);
        }
    }

    else if(c==3)
    {
        if(root==NULL)
            cout<<"\nSorry, ScapeGoat tree does not exist! :("<<endl;
        else
            preorder(root);
    }

    else if(c==4)
        break;
    
    else
        cout<<"\nInvalid Input! :("<<endl;

    cout<<"\n-------------------------------------------------"<<endl;
    }
    return 0;
}
