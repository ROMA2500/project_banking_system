#include<iostream>
#include<algorithm>
using namespace std;
struct node {
 int phone;
 int age;
 int id;
 string name;
 string email;
 
 node* next;
};
node* head=nullptr;
int current_id = 0; // متغير لتتبع آخر ID مستخدم

void add_customer(int phone, int age, string name, string email)
{

    node *newnode=new node();
    newnode->phone=phone;
    newnode->age=age;
    newnode->name=name;
    newnode->email=email;
    current_id += 1;          // زوّد العدد
    newnode->id = current_id; // دي الـ ID الجديدة
    newnode->next = head;
    head=newnode;
}
void display()
{
    node* temp=head;
    while(temp!=nullptr)
    {
        cout<<"ID: "<<temp->id<<endl;
        cout<<"Name: "<<temp->name<<endl;
        cout<<"Age: "<<temp->age<<endl;
        cout<<"Phone: "<<temp->phone<<endl;
        cout<<"Email: "<<temp->email<<endl;
        cout<<"---------------------"<<endl;
        temp=temp->next;
    }
}
int remove_customer(int id){
    node* temp=head;
    node *prev = nullptr;

    while(temp!=NULL){
        if (temp->id==id){
            if (temp==head){
                head=head->next;
            }
        else{
            
            prev->next=temp->next;


        }
        delete temp;
        return 1;
        }
        prev=temp;
        temp=temp->next;
    }
    return 0;
}
void sort_customers_byid(){
   if (head==NULL|| head->next==NULL){
    return;
   }
    node* ptr1;
    node *ptr2;
    for (ptr1=head;ptr1->next!=NULL;ptr1=ptr1->next){
        for(ptr2=ptr1->next;ptr2!=NULL;ptr2=ptr2->next){
            if (ptr1->id>ptr2->id){
                swap(ptr1->id,ptr2->id);
                swap(ptr1->name,ptr2->name);
                swap(ptr1->age,ptr2->age);
                swap(ptr1->phone,ptr2->phone);
                swap(ptr1->email,ptr2->email);
            }
        }
    }
}

int main(){
    add_customer(1234567890,25,"Alice","alice@example.com");
    add_customer(1234567891,30,"Bob","bob@example.com");
    add_customer(1234567892,28,"Charlie","charlie@example.com");

    cout << "Customers before sorting:" << endl;
    display();

    sort_customers_byid();

    cout << "Customers after sorting:" << endl;
    display();

    remove_customer(1);
    cout << "Customers after removing customer with ID 1:" << endl;
    display();

    return 0;
}
