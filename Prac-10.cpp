#include<bits/stdc++.h>
using namespace std;
  
class Hash
{
    int size;
    list<int> *table;

    public:
        Hash(int b)
        {
            this->size=b;
            table=new list<int>[size];
        }
        
        int hash_fun(int x)
        {
            return (x%size);
        }
        
        void insert_element(int key)
        {
            int index=hash_fun(key);
            table[index].push_back(key); 
        }
        
        void delete_element(int key)
        {
            int index=hash_fun(key);

            list<int> :: iterator i;
            for(i=table[index].begin();i!=table[index].end();i++)
            {
                if(*i==key)
                    break;
            }
            
            if (i!=table[index].end())
                table[index].erase(i);
        }
        
        void display(){
            for(int i=0;i<size;i++)
            {
                cout<<i;
                for(auto x:table[i])
                    cout<<" --> "<<x;
                cout<<endl;
            }
        }
};
  
int main()
{
    int size,n,num;
    cout<<"Enter the size of the Hash Table: ";
    cin>>size;
    cout<<"Enter the number of Elements: ";
    cin>>n;

    Hash h(size);
    cout<<"\nEnter the Elements:-"<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>num;
        h.insert_element(num);
    }

    cout<<"\nHash Table:-"<<endl;
    h.display();
    
    int x;
    cout<<"\nEnter the element that you want to delete: ";
    cin>>x;
    h.delete_element(x);

    cout<<"Hash Table after deletion of element "<<x<<" : "<<endl;
    h.display();
    return 0;
}