#include<iostream>
using namespace std;

float alpha;

class mystack{
    int top,capacity;
    int *st;

    public:
    mystack(int n){
        st=new int[n];
        capacity=n;
        top=-1;
    }

    void resize(){
        int temp[top+1],t;
        t=top+1;
        for(int i=0;i<=top;i++)
            temp[i]=st[i];

        cout<<"\nThresold reached !! \nNow, new capacity of your stack is:- "<<2*capacity<<endl;

        capacity=2*capacity;
        st=new int[capacity];

        for(int i=0;i<t;i++)
            st[i]=temp[i];
    }

    void mypush(int x){
        if(top+1>=capacity*alpha)
            resize();

        st[++top]=x;
        cout<<"\nSuccessfully Done :)"<<endl;
    }

    void mypop(){
        if(top==-1)
            cout<<"\nSorry, your stack is empty! :("<<endl;
        else
        {
            top--;
            cout<<"\nSuccessfully Done :)"<<endl;
        }
    }

    void mytop(){
        if(top==-1)
            cout<<"\nSorry, your stack is empty! :("<<endl;
        else
            cout<<"\nTop element is: "<<st[top]<<endl;
    }
};


int main()
{
    int n,c,x;

    cout<<"Enter the initial capacity of the stack: ";
    cin>>n;
    cout<<"Enter the value of alpha: ";
    cin>>alpha;

    mystack stc(n);

    while(1)
    {
        cout<<"\nWhat you want to do:-"<<endl;
        cout<<"1) PUSH      2) POP      3) TOP OF STACK      4) EXIT"<<endl;
        cout<<"\nEnter your choice:- ";
        cin>>c;

        if(c==1)
        {
            cout<<"\nEnter the element that you want to push: ";
            cin>>x;
            stc.mypush(x);
        }

        else if(c==2)
            stc.mypop();

        else if(c==3)
            stc.mytop();

        else if(c==4)
            break;
        
        else
            cout<<"\nInvalid Input! :("<<endl;

        cout<<"\n--------------------------------------------------"<<endl;
    }
}