#include<bits/stdc++.h>
using namespace std;

struct suffix
{
    int index;
    char *suff;
};

int compare(struct suffix a, struct suffix b)
{
    return strcmp(a.suff, b.suff) < 0? 1 : 0;
}

int *build(char *txt, int n)
{
    struct suffix suffix1[n];

    for(int i=0;i<n;i++)
    {
        suffix1[i].index=i;
        suffix1[i].suff=(txt+i);
    }

    sort(suffix1,suffix1+n,compare);

    int *suffiix_arr=new int[n];
    for(int i=0;i<n;i++)
        suffiix_arr[i]=suffix1[i].index;

    return suffiix_arr;
}

void match(char *pat, char *txt, int *suffArr, int n)
{
    int m=strlen(pat);

    int l=0,r=n-1;
    while(l<=r)
    {
        int mid=l+(r-l)/2;
        int res=strncmp(pat, txt+suffArr[mid], m);

        if(res==0)
        {
            cout<<"Pattern found at index "<<suffArr[mid];
            return;
        }

        if(res<0) 
            r=mid-1;
        else
            l=mid+1;
    }
    cout<<"Pattern not found";
}

void display(int arr[], int n, char *txt)
{
    for(int i=0;i<n;i++)
    {
        cout<<arr[i]<<" --> ";
        for(int j=arr[i];j<n;j++)
            cout<<*(txt+j);
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    char txt[100];
    char pat[100];
    
    cout<<"Enter String: ";
    cin>>txt;
    
    cout<<"Enter pattern: ";
    cin>>pat;

    int n=strlen(txt);
    int *suffiix_arr=build(txt, n);

    cout<<"\nFollowing is suffix array for "<<txt<<endl;
    display(suffiix_arr,n,txt);

    match(pat,txt,suffiix_arr,n);
    return 0;
}