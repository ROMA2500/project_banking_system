#include <iostream>
#include <string>
using namespace std;

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

int main()
{
    cout << "--- Testing Nour's Queue & Stack ---" << endl;

    LoanQueue q;    // كيو القروض
    RequestStack s; // ستاك الطلبات

    // تجارب بسيطة
    q.enqueueLoan("Loan#1");
    q.enqueueLoan("Loan#2");
    q.displayLoans();

    q.dequeueLoan();
    q.displayLoans();

    s.pushRequest("Open Account");
    s.pushRequest("Change Email");
    s.displayRequests();

    s.popRequest();
    s.displayRequests();

    return 0;
}