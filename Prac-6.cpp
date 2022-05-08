#include<bits/stdc++.h>
using namespace std;

void build_tree(vector<int> &a,int x,int lo,int hi,vector<int> &sg)
{
    if(lo==hi)
    {
        sg[x]=a[lo];
        return;
    }

    int mid=(lo+hi)/2;
    build_tree(a,2*x+1,lo,mid,sg);
    build_tree(a,2*x+2,mid+1,hi,sg);
    sg[x]=sg[2*x+1]+sg[2*x+2];
}

int solve(vector<int> &sg,int ind,int l,int r,int lo,int hi)
{
    if(lo>=l && hi<=r)
        return sg[ind];
    if(hi<l || lo>r)
        return 0;
    
    int mid=(lo+hi)/2;
    return solve(sg,2*ind+1,l,r,lo,mid)+solve(sg,2*ind+2,l,r,mid+1,hi);
}

int main()
{
    int n,q,i;
    cout<<"\nEnter the number of elements: ";
    cin>>n;

    vector<int> a(n);
    cout<<"\nEnter Elements:- "<<endl;
    for(i=0;i<n;i++)
        cin>>a[i];

    vector<int> sg(4*n,0);
    build_tree(a,0,0,n-1,sg);

    cout<<"\nEnter the number of queries: ";
    cin>>q;

    while(q--)
    {
        int l,r;
        cout<<"\nEnter range: ";
        cin>>l>>r;

        cout<<"Sum is:- "<<solve(sg,0,l,r,0,n-1)<<endl;
    }
}