#include <iostream>
#include <algorithm>
using namespace std;
struct node
{
    int phone;
    int age;
    int id;
    string name;
    string email;

    node *next;
};
node *head = nullptr;
int current_id = 0; // متغير لتتبع آخر ID مستخدم

void add_customer(int phone, int age, string name, string email)
{

    node *newnode = new node();
    newnode->phone = phone;
    newnode->age = age;
    newnode->name = name;
    newnode->email = email;
    current_id += 1;          // زوّد العدد
    newnode->id = current_id; // دي الـ ID الجديدة
    newnode->next = head;
    head = newnode;
}
void display()
{
    node *temp = head;
    while (temp != nullptr)
    {
        cout << "ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Phone: " << temp->phone << endl;
        cout << "Email: " << temp->email << endl;
        cout << "---------------------" << endl;
        temp = temp->next;
    }
}
int remove_customer(int id)
{
    node *temp = head;
    node *prev = nullptr;

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            if (temp == head)
            {
                head = head->next;
            }
            else
            {

                prev->next = temp->next;
            }
            delete temp;
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}
void sort_customers_byid()
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }
    node *ptr1;
    node *ptr2;
    for (ptr1 = head; ptr1->next != NULL; ptr1 = ptr1->next)
    {
        for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next)
        {
            if (ptr1->id > ptr2->id)
            {
                swap(ptr1->id, ptr2->id);
                swap(ptr1->name, ptr2->name);
                swap(ptr1->age, ptr2->age);
                swap(ptr1->phone, ptr2->phone);
                swap(ptr1->email, ptr2->email);
            }
        }
    }
}


class LoanNode
{
public:
    string loanName; // اسم القرض اللي العميل قدمه
    LoanNode *next;  // بيوصل للنود اللي بعدها في الصف (Queue)

    LoanNode(string name)
    {
        loanName = name;
        next = NULL; // أول ما النود تتعمل، ملهاش اللي بعدها لسه
    }
};

// Queue class: الصف الكامل اللي بنضيف ونشيل منه
class LoanQueue
{
private:
    LoanNode *front; // أول حد مقدم طلب قرض
    LoanNode *rear;  // آخر حد في الصف

public:
    LoanQueue()
    {
        front = rear = NULL; // الصف فاضي في البداية
    }

    // enqueueLoan(): إضافة طلب قرض جديد للصف
    void enqueueLoan(string name)
    {
        LoanNode *newNode = new LoanNode(name); // نعمل نود جديدة

        if (rear == NULL)
        {                           // لو الصف كان فاضي
            front = rear = newNode; // أول نود تبقى هي الفرونت والريا
        }
        else
        {
            rear->next = newNode; // نربط آخر نود بالنود الجديدة
            rear = newNode;       // نخلي الريار هو النود الجديدة
        }

        cout << "[QUEUE] Loan request added: " << name << endl;
    }

    // dequeueLoan(): معالجة الطلب اللي واقف أول واحد في الصف
    void dequeueLoan()
    {
        if (front == NULL)
        { // لو الصف فاضي
            cout << "[QUEUE] No loan requests to process!" << endl;
            return;
        }

        LoanNode *temp = front; // نخزن أول نود قبل ما نحذفها
        cout << "[QUEUE] Processing loan request: " << temp->loanName << endl;

        front = front->next; // نزحلق الفرونت للنود اللي بعدها

        if (front == NULL) // لو الصف فاضي بعد الحذف
            rear = NULL;

        delete temp; // نحذف أول نود
    }

    // Display queue contents (مش مطلوب لكنه مفيد للتست)
    void displayLoans()
    {
        LoanNode *cur = front;
        cout << "Current Loan Queue: ";

        while (cur)
        {
            cout << cur->loanName << " -> ";
            cur = cur->next;
        }

        cout << "NULL" << endl;
    }
};

// Stack node: يمثل طلب خدمة واحد من العميل
class ReqNode
{
public:
    string req;    // نص الطلب نفسه
    ReqNode *next; // النود اللي تحتها في ال Stack

    ReqNode(string r)
    {
        req = r;
        next = NULL;
    }
};

// Stack class: بنضيف فوق ونشيل من فوق بس (LIFO)
class RequestStack
{
private:
    ReqNode *top; // آخر طلب دخل (أحدث طلب)

public:
    RequestStack()
    {
        top = NULL; // الستاك فاضي
    }

    // pushRequest(): إضافة طلب جديد فوق الستاك
    void pushRequest(string r)
    {
        ReqNode *newNode = new ReqNode(r); // نود جديدة

        newNode->next = top; // تربطها بالنود اللي كانت فوق
        top = newNode;       // نخلي التوب هو النود دي

        cout << "[STACK] Service request added: " << r << endl;
    }

    // popRequest(): معالجة أحدث طلب (اللي فوق)
    void popRequest()
    {
        if (top == NULL)
        { // لو الستاك فاضي
            cout << "[STACK] No service requests to process!" << endl;
            return;
        }

        ReqNode *temp = top; // مسكنا النود اللي هتتشال
        cout << "[STACK] Processing request: " << temp->req << endl;

        top = top->next; // نزحلق التوب اللي تحت
        delete temp;     // delete النود القديمة
    }

    // Display contents of stack (اختياري للتست)
    void displayRequests()
    {
        ReqNode *cur = top;
        cout << "Current Service Request Stack: ";

        while (cur)
        {
            cout << cur->req << " -> ";
            cur = cur->next;
        }

        cout << "NULL" << endl;
    }
};



// Node بتمثل كل Transaction في الـ Doubly Linked List
struct Transaction
{
    int id;        // رقم العملية
    string type;   // نوع العملية (deposit / withdrawal / transfer)
    double amount; // قيمة العملية

    Transaction *next; // بوينتر على العنصر اللي بعده
    Transaction *prev; // بوينتر على العنصر اللي قبله
};

Transaction *head1 = NULL; // أول عنصر في الليست
Transaction *tail = NULL; // آخر عنصر في الليست

// addTransaction(): إضافة عملية جديدة
void addTransaction(int id, string type, double amount)
{
    Transaction *newNode = new Transaction; // إنشاء Node جديدة
    newNode->id = id;                       // تخزين الـ ID
    newNode->type = type;                   // تخزين نوع العملية
    newNode->amount = amount;               // تخزين المبلغ
    newNode->next = NULL;                   // مفيش عنصر بعده دلوقتي
    newNode->prev = NULL;                   // مفيش عنصر قبله دلوقتي

    if (head1 == NULL)
    {                          // لو الليست فاضية
        head1 = tail = newNode; // أول وآخر عنصر هو نفسه
    }
    else
    {
        tail->next = newNode; // ربط آخر عنصر بالجديد
        newNode->prev = tail; // ربط الجديد بآخر عنصر
        tail = newNode;       // تحديث الـ tail
    }
}

// findTransaction(): البحث عن عملية بالـ ID
void findTransaction(int id)
{
    Transaction *temp = head1; // نبدأ من أول الليست

    while (temp != NULL)
    { // نلف على الليست
        if (temp->id == id)
        { // لو لقينا الـ ID
            cout << "Found Transaction: ";
            cout << temp->id << " " << temp->type << " " << temp->amount << endl;
            return; // نخرج من الفانكشن
        }
        temp = temp->next; // نروح للي بعده
    }

    cout << "Transaction not found" << endl; // لو ملقيناش حاجة
}

// viewTransactions(): عرض كل العمليات
void viewTransactions()
{
    Transaction *temp = head1; // نبدأ من أول الليست

    while (temp != NULL)
    { // نلف على كل العناصر
        cout << temp->id << " " << temp->type << " " << temp->amount << endl;
        temp = temp->next; // نروح للي بعده
    }
}

// deleteTransaction(): حذف عملية بالـ ID
void deleteTransaction(int id)
{
    Transaction *temp = head1; // نبدأ من أول الليست

    while (temp != NULL)
    {
        if (temp->id == id)
        {                     // لو لقينا العنصر
            if (temp == head1) // لو هو أول عنصر
                head1 = temp->next;

            if (temp == tail) // لو هو آخر عنصر
                tail = temp->prev;

            if (temp->prev != NULL) // ربط اللي قبله باللي بعده
                temp->prev->next = temp->next;

            if (temp->next != NULL) // ربط اللي بعده باللي قبله
                temp->next->prev = temp->prev;

            delete temp; // مسح العنصر من الذاكرة
            cout << "Transaction deleted" << endl;
            return;
        }
        temp = temp->next; // نكمل لف
    }

    cout << "Transaction not found" << endl; // لو ملقيناش الـ ID
}

// Bubble Sort لترتيب العمليات حسب ID
void bubbleSortTransactions()
{
    if (head1 == NULL)
        return; // لو الليست فاضية

    bool swapped;      // متغير نعرف بيه هل حصل تبديل ولا لا
    Transaction *ptr1; // بوينتر للمقارنة

    do
    {
        swapped = false; // في البداية مفيش تبديل
        ptr1 = head1;     // نبدأ من أول عنصر

        while (ptr1->next != NULL)
        { // نلف لحد قبل آخر عنصر
            if (ptr1->id > ptr1->next->id)
            { // لو الترتيب غلط
                // swap البيانات (مش الـ nodes)
                swap(ptr1->id, ptr1->next->id);
                swap(ptr1->type, ptr1->next->type);
                swap(ptr1->amount, ptr1->next->amount);

                swapped = true; // حصل تبديل
            }
            ptr1 = ptr1->next; // نروح للي بعده
        }
    } while (swapped); // نكرر لو حصل تبديل
}


struct Branch
{                    // تعريف struct اسمها Branch (فرع)
    int id;          // رقم الفرع
    string name;     // اسم الفرع
    string location; // مكان الفرع
    Branch *left;    // مؤشر للفرع اللي على الشمال
    Branch *right;   // مؤشر للفرع اللي على اليمين
};

Branch *createBranch(int id, string name, string location)
{
    Branch *newBranch = new Branch; // إنشاء فرع جديد في الذاكرة
    newBranch->id = id;             // تخزين الـ ID
    newBranch->name = name;         // تخزين اسم الفرع
    newBranch->location = location; // تخزين مكان الفرع
    newBranch->left = NULL;         // مفيش فرع شمال
    newBranch->right = NULL;        // مفيش فرع يمين
    return newBranch;               // رجوع بالفرع الجديد
}

Branch *addBranch(Branch *root, int id, string name, string location)
{
    if (root == NULL)
    {                                            // لو الشجرة فاضية
        return createBranch(id, name, location); // نضيف أول فرع
    }

    if (id < root->id)
    {                                                           // لو الـ ID أصغر من الجذر
        root->left = addBranch(root->left, id, name, location); // نضيف شمال
    }
    else if (id > root->id)
    {                                                             // لو الـ ID أكبر من الجذر
        root->right = addBranch(root->right, id, name, location); // نضيف يمين
    }

    return root; // نرجع الجذر
}

Branch *searchBranch(Branch *root, int id)
{
    if (root == NULL)
    {                // لو الشجرة فاضية
        return NULL; // مش لاقيين حاجة
    }

    if (root->id == id)
    {                // لو لقينا الـ ID
        return root; // نرجع الفرع
    }

    if (id < root->id)
    {                                        // لو الـ ID أصغر
        return searchBranch(root->left, id); // نبحث شمال
    }
    else
    {
        return searchBranch(root->right, id); // نبحث يمين
    }
}

Branch *findMin(Branch *root)
{
    while (root->left != NULL)
    {                      // نفضل نتحرك شمال
        root = root->left; // لحد ما نوصل لأصغر ID
    }
    return root; // نرجع أصغر فرع
}

Branch *removeBranch(Branch *root, int id)
{
    if (root == NULL)
    { // لو الشجرة فاضية
        return NULL;
    }

    if (id < root->id)
    {                                              // لو الـ ID أصغر
        root->left = removeBranch(root->left, id); // نحذف من الشمال
    }
    else if (id > root->id)
    {                                                // لو الـ ID أكبر
        root->right = removeBranch(root->right, id); // نحذف من اليمين
    }
    else
    { // لو لقينا الفرع المطلوب
        if (root->left == NULL)
        {                               // لو مفيش فرع شمال
            Branch *temp = root->right; // نخزن اليمين
            delete root;                // نحذف الفرع
            return temp;                // نرجع الفرع اليمين
        }
        else if (root->right == NULL)
        {                              // لو مفيش فرع يمين
            Branch *temp = root->left; // نخزن الشمال
            delete root;               // نحذف الفرع
            return temp;               // نرجع الفرع الشمال
        }

        Branch *temp = findMin(root->right);               // أصغر فرع في اليمين
        root->id = temp->id;                               // ناخد الـ ID
        root->name = temp->name;                           // ناخد الاسم
        root->location = temp->location;                   // ناخد المكان
        root->right = removeBranch(root->right, temp->id); // نحذف المكرر
    }

    return root; // نرجع الجذر
}

void sortBranchesByID(Branch *root)
{
    if (root != NULL)
    {                                   // لو الشجرة مش فاضية
        sortBranchesByID(root->left);   // نطبع الشمال
        cout << root->id << " - "       // نطبع الـ ID
             << root->name << " - "     // نطبع الاسم
             << root->location << endl; // نطبع المكان
        sortBranchesByID(root->right);  // نطبع اليمين
    }
}

void searchCustomerOrTransaction(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    { // لف على كل العناصر
        if (arr[i] == target)
        {                                           // لو لقينا الرقم
            cout << "Found ID: " << target << endl; // نطبع لقيناه
            return;
        }
    }
    cout << "ID not found" << endl; // لو مش موجود

}
void menu()
{
    cout << "===== Customer Management System =====" << endl;
    cout << "1- Add Customer" << endl;
    cout << "2- Remove Customer" << endl;
    cout << "3- Display Customers" << endl;
    cout << "4- Sort Customers by ID" << endl;
    cout << "5- Add Loan Request" << endl;
    cout << "6- Process Loan Request" << endl;
    cout << "7- Add Service Request" << endl;
    cout << "8- Process Service Request" << endl;
    cout << "9- Branch Management System" << endl;
    cout << "10- Add Transaction" << endl;
    cout << "11- View All Transactions" << endl;
    cout << "12- Sort Transactions by ID" << endl;
    cout << "13- Search Transaction by ID" << endl;
    cout << "14- Delete Transaction by ID" << endl;
    cout << "15- Exit" << endl;}
void in_add_customer()
{
    int phone, age;
    string name, email;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Phone: ";
    cin >> phone;
    cout << "Enter Email: ";
    cin >> email;
    try
    {
        if (age <= 0)
        {
            throw invalid_argument("Age must be greater than zero.");

        }

        if (email.find('@') == string::npos || email.find('.') == string::npos)
        {
            throw invalid_argument("Invalid email format.");
        }

        if (name.empty())
        {
            throw invalid_argument("Name cannot be empty.");
        }
    }
    catch (const invalid_argument &e)
    {
        cout << "Input Error: " << e.what() << endl;
        return;
    }

    add_customer(phone, age, name, email);
    cout << "Customer added successfully!" << endl;

   
}

void add_loan_request(LoanQueue &q)
{
    string loanName;
    cout << "Enter Loan Name: ";
    cin >> loanName;
    q.enqueueLoan(loanName);
}
void add_service_request(RequestStack &s)
{
    string serviceReq;
    cout << "Enter Service Request: ";
    cin >> serviceReq;
    s.pushRequest(serviceReq);
}
void add_transaction()
{
    int id;
    string type;
    double amount;
    cout << "Enter Transaction ID: ";
    cin >> id;
    cout << "Enter Transaction Type (deposit/withdrawal/transfer): ";
    cin >> type;
    cout << "Enter Transaction Amount: ";
    cin >> amount;
    addTransaction(id, type, amount);
}
void view_all_transactions()
{
    cout << "All Transactions:" << endl;
    viewTransactions();
}
void sort_all_transactions()
{
    bubbleSortTransactions();
    cout << "Transactions sorted by ID." << endl;
}
void search_transaction_by_id()
{
    int id;
    cout << "Enter Transaction ID to search: ";
    cin >> id;
    findTransaction(id);
}
void delete_transaction_by_id()
{
    int id;
    cout << "Enter Transaction ID to delete: ";
    cin >> id;
    deleteTransaction(id);
}
void branch_management_menu()
{
    cout << "===== Branch Management System =====" << endl;
    cout << "1- Add Branch" << endl;
    cout << "2- Remove Branch" << endl;
    cout << "3- Search Branch" << endl;
    cout << "4- Display Branches Sorted by ID" << endl;
    cout << "5- Exit" << endl;
}
void in_add_branch(Branch *&root)
{
    int id;
    string name, location;
    cout << "Enter Branch ID: ";
    cin >> id;
    cout << "Enter Branch Name: ";
    cin >> name;
    cout << "Enter Branch Location: ";
    cin >> location;
    root = addBranch(root, id, name, location);
    cout << "Branch added successfully!" << endl;
}
void in_remove_branch(Branch *&root)
{
    int id;
    cout << "Enter Branch ID to remove: ";
    cin >> id;
    root = removeBranch(root, id);
    cout << "Branch removed successfully!" << endl;
}
void in_search_branch(Branch *root)
{
    int id;
    cout << "Enter Branch ID to search: ";
    cin >> id;
    Branch *found = searchBranch(root, id);
    if (found)
    {
        cout << "Branch Found: " << found->id << " - " << found->name << " - " << found->location << endl;
    }
    else
    {
        cout << "Branch not found." << endl;
    }
}
void in_display_branches(Branch *root)
{
    cout << "Branches sorted by ID:" << endl;
    sortBranchesByID(root);
}
void customer_management_system()
{
    LoanQueue q;    // كيو القروض
    RequestStack s; // ستاك الطلبات
    Branch *root = NULL;

    // جذر شجرة الفروع
    int choice;

    do
    {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            in_add_customer();
            break;
        case 2:
        {
            int id;
            cout << "Enter Customer ID to remove: ";
            cin >> id;
            if (remove_customer(id))
                cout << "Customer removed successfully!" << endl;
            else
                cout << "Customer not found!" << endl;
            break;
        }
        case 3:
            display();
            break;
        case 4:
            sort_customers_byid();
            cout << "Customers sorted by ID." << endl;
            break;
        case 5:
            add_loan_request(q);
            cout << "Loan request added." << endl;
            break;
        case 6:
            q.dequeueLoan();
            break;
        case 7:
            add_service_request(s);
            cout << "Service request added." << endl;
            break;
        case 8:
            s.popRequest();
            break;
        case 9:
            branch_management_menu();
            int branchChoice;
            cout << "Enter your choice: ";
            cin >> branchChoice;
            switch (branchChoice)
            {
            case 1:
                in_add_branch(root);
                break;
            case 2:
                in_remove_branch(root);
                break;
            case 3:
                in_search_branch(root);
                break;
            case 4:
                in_display_branches(root);
                break;
            case 5:
                cout << "Exiting Branch Management System." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            break;
        case 10:
            add_transaction();
            break;
        case 11:
            view_all_transactions();
            break;
        case 12:
            sort_all_transactions();
            break;
        case 13:
            search_transaction_by_id();
            break;
        case 14:
            delete_transaction_by_id();
            break;
        case 15:
            cout << "Exiting Banking  Management System." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 15);
}
int main (){
    
    customer_management_system();

    return 0;
}   
