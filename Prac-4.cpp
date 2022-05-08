#include<bits/stdc++.h>
using namespace std;

class Skiplist
{
    public:
        int val;
        Skiplist *next,*up,*down;
        Skiplist(int value)
        {
            val=value;
            next=up=down=NULL;
        }
};
Skiplist *root;

void build(Skiplist *curr)
{
    for(int i=1;i<=3;i++)
    {
        Skiplist *temp=curr,*prev=NULL;
        while(temp!=NULL)
        {
            Skiplist *extra=new Skiplist(temp->val);
            extra->down=temp;
            temp->up=extra;

            if(prev!=NULL)
                prev->next=extra;

            int skip=2;
            prev=extra;
            while(temp!=NULL && skip--)
                temp=temp->next;
        }
        curr=curr->up;
        root=curr;
    }
}

bool search(Skiplist *curr,int find)
{
    if(curr==NULL)
        return false;
    if(curr->val==find)
        return true;
    if(curr->next==NULL || curr->next->val>find)
        return search(curr->down,find);
    else
        return search(curr->next,find);
    return false;
}

void display(Skiplist *curr)
{
    cout<<"Level Wise List :- \n";
    while(curr!=NULL)
    {
        Skiplist *temp=curr;
        while(temp!=NULL)
        {
            cout<<temp->val<<" ";
            temp=temp->next;
        }
        cout<<endl;
        curr=curr->down;
    }
}

void insert(Skiplist *curr,int ele)
{
    stack<Skiplist*> path;
    while(curr!=NULL)
    {
        Skiplist *temp = curr;
        while(temp!=NULL && temp->next!=NULL && temp->next->val<ele) 
            temp=temp->next;
        path.push(temp);
        curr=curr->down;
    }
    srand(time(0));
    Skiplist *temp=path.top();
    path.pop();

    Skiplist *extra=new Skiplist(ele);
    extra->next=temp->next;
    temp->next=extra;
    Skiplist *curr1=extra;

    while(path.size())
    {
        temp=path.top();
        path.pop(); 
        int random=rand();
        if(random%2)
        {
            extra=new Skiplist(ele);
            curr1->up=extra;
            extra->down=curr1;
            extra->next=temp->next;
            temp->next=extra;
            curr1=extra;
        }
    }
    cout<<"\nElement successfully Inserted :)\n";
}

void del(Skiplist *curr,int ele)
{
    if(!search(curr,ele))
    {
        cout<<"Element Not Found\n";
        return;
    }

    stack<Skiplist*> path;
    while(curr!=NULL)
    {
        Skiplist *temp=curr;
        while(temp!=NULL && temp->next!=NULL && temp->next->val<ele)
            temp=temp->next;
        path.push(temp);
        curr=curr->down;
    }

    while(path.size())
    {
        Skiplist *temp=path.top();
        path.pop();
        Skiplist *temp1=temp->next;
        if(temp1!=NULL && temp1->val==ele)
            temp->next=temp1->next;
    }
    cout<<"\nElement Successfully Deleted :)\n";
}

int main()
{
    int n;
    cout<<"\nEnter Size: ";
    cin>>n;

    int x;
    cout<<"\nEnter Element-1: ";
    cin>>x;
    Skiplist *first=new Skiplist(x);
    Skiplist *cur=first;

    for(int i=1;i<n;i++)
    {
        cout<<"Enter Element-"<<i+1<<": ";
        cin>>x;
        Skiplist *temp=new Skiplist(x);
        cur->next=temp;
        cur=cur->next;
    }
    
    build(first);

    while(1)
    {
        int c;
        cout<<"\n----------------------------------------------"<<endl;
        cout<<"\nWhat you want to do: "<<endl;
        cout<<"1) Search \n2) Insert \n3) Delete \n4) Display \n5) Exit"<<endl;
        cout<<"Enter Your Choice :-";
        cin>>c;

        if(c==1)
        {
            cout<<"\nEnter The Element :- ";
            cin>>x;
            if(search(root,x)) 
                cout<<"Present\n";
            else cout<<"Not Present\n";
        }

        else if(c==2)
        {
            cout<<"\nEnter The Element :- ";
            cin>>x;
            insert(root,x);
        }

        else if(c==3)
        {
            cout<<"\nEnter The Element :- ";
            cin>>x;
            del(root,x);
        }

        else if(c==4)
            display(root);

        else if(c==5)
            break;
            
        else
            cout<<"\nInvalid Input! :("<<endl;
    }
    return 0;
}