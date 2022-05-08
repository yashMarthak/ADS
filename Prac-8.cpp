#include <bits/stdc++.h>
using namespace std;
vector <int> pr;

int find_op(int x)
{
    return pr[x]==-1?x:find_op(pr[x]);
}

void union_op(int a,int b)
{
    int xset = find_op(a);
    int yset = find_op(b);
    if(xset!=yset)
    {
        pr[xset]=yset;
    }
}

int main()
{
    int n,e;
    cout<<"Enter the value of n: ";
    cin>>n;
    cout<<"Enter the value of e: ";
    cin>>e;

    pr.resize(n+1,-1);
    cout<<"\nEnter the edges:-"<<endl;
    for(int i=1;i<=e;i++)
    {
        int a,b;
        cin>>a>>b;
        union_op(a, b);
    }

    map <int,vector <int>> sets;
    for(int i=1;i<=n;i++)
    {
        int group = find_op(i);
        sets[group].push_back(i);
    }

    cout<<"\nTotal no of sets : "<<sets.size()<<"\n\n";
    for(auto [groupno,elements]:sets)
    {
        cout<<"Leader of selected set is : "<<groupno<<endl;
        cout<<"Elements are : ";
        for(int i:elements)
            cout<<i<<" ";
        cout<<"\n\n";
    }
}