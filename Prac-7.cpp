#include <bits/stdc++.h>
using namespace std;
#define nospace 10

class lfnode
{
    public:
        int el;
        lfnode *left;
        lfnode *right;
        int npl;
        lfnode(int num, lfnode *lt=NULL,lfnode *rt=NULL, int np=0)
        {
            el=num;
            right=rt;
            left=lt,
            npl=np;
        }
};

class lfheap
{
    public:
        lfheap()
        {
            root=NULL;
        }
        
        lfheap(lfheap &rhs)
        {
            root=NULL;
            *this=rhs;
        }
        
        ~lfheap()
        {
            makeEmpty( );
        }
        
        void Merge(lfheap &rhs)
        {
            if (this==&rhs)
                return;
            root=Merge(root,rhs.root);
            rhs.root=NULL;
        }
        
        lfnode *Merge(lfnode *h1, lfnode *h2)
        {
            if (h1==NULL)
                return h2;
            if (h2==NULL)
                return h1;
            if (h1->el<h2->el)
                return Merge1(h1,h2);
            else
                return Merge1(h2,h1);
        }
        
        lfnode *Merge1(lfnode *h1, lfnode *h2)
        {
            if (h1->left==NULL)
                h1->left=h2;
            else
            {
                h1->right=Merge(h1->right,h2);
                if (h1->left->npl<h1->right->npl)
                    swapch(h1);
                h1->npl=h1->right->npl+1;
            }
            return h1;
        }
        
        void swapch(lfnode *t)
        {
            lfnode *tmp=t->left;
            t->left=t->right;
            t->right=tmp;
        }
        
        void Insert(int &x)
        {
            root=Merge(new lfnode(x),root);
        }
        
        int &findMin()
        {
            return root->el;
        }
        
        void deleteMin()
        {
            lfnode *oldRoot=root;
            root=Merge(root->left,root->right);
            delete oldRoot;
        }
        
        void deleteMin(int &minItem)
        {
            if (isEmpty())
            {
                cout<<"Heap is Empty"<<endl;
                return;
            }
            minItem=findMin();
            deleteMin();
        }
        
        bool isEmpty()
        {
            return root==NULL;
        }
        
        bool isFull()
        {
            return false;
        }
        
        void makeEmpty()
        {
            reclaimMemory(root);
            root=NULL;
        }

        lfheap &operator=(lfheap &rhs)
        {
            if (this!=&rhs)
            {
                makeEmpty();
                root=clone(rhs.root);
            }
            return *this;
        }

        void reclaimMemory(lfnode *t)
        {
            if (t!=NULL)
            {
                reclaimMemory(t->left);
                reclaimMemory(t->right);
                delete t;
            }
        }
      
        void display(lfnode *t,int space)
        {
            if (t==NULL)
                return;

            space+=nospace;  
            display(t->right,space);
            cout<<endl;

            for(int i=nospace;i<space;i++) 
                cout<<" ";
            cout<<t->el<<"\n";
            display(t->left,space);
        }
        
        void display_heap()
        {
            display(root,0);
        }

        lfnode *clone(lfnode *t)
        {
            if (t==NULL)
                return NULL;
            else
                return new lfnode(t->el,clone(t->left),clone(t->right),t->npl);
        }
    private:
        lfnode *root;
};
 
int main()
{
    lfheap h;
    lfheap h1;
    lfheap h2;

    int val;
    int choice;
    
    do
    {
        cout<<"\nWhat you want to do: \n";
        cout<<"1. Insert an Element"<<endl;
        cout<<"2. Merge heaps"<<endl;
        cout<<"3. Print Minimum"<<endl;
        cout<<"4. Extract Minimum"<<endl;
        cout<<"5. Display"<<endl;
        cout<<"6. Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
            {
                int ch=1;
                cout<<"\nEnter in which heap you want to insert: "<<endl;
                cin>>ch;
                cout<<"Enter Element: ";
                cin>>val;
                
                if(ch==1)
                    h1.Insert(val);
                else
                    h2.Insert(val);
                break;
            }
            case 2:
                h1.Merge(h2);
                h=h1;
                break;
            case 3 :
                cout<<"\nMinimum Element is : "<<h.findMin()<<endl;
                break;
            case 4:
                cout<<"\nMinimum Element is deleted."<<endl;
                h.deleteMin();
                break;
            case 5 :
                h.display_heap();
                break;
            case 6:
                break;
        }
    cout<<"\nx--x--x--x--x--x--x--x--x--x--x--x--x--x--x"<<endl;
    }while(choice!=6);

    return 0;
}