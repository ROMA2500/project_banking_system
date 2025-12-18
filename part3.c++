#include <iostream>
using namespace std;

// Node بتمثل كل Transaction في الـ Doubly Linked List
struct Transaction
{
    int id;        // رقم العملية
    string type;   // نوع العملية (deposit / withdrawal / transfer)
    double amount; // قيمة العملية

    Transaction *next; // بوينتر على العنصر اللي بعده
    Transaction *prev; // بوينتر على العنصر اللي قبله
};

Transaction *head = NULL; // أول عنصر في الليست
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

    if (head == NULL)
    {                          // لو الليست فاضية
        head = tail = newNode; // أول وآخر عنصر هو نفسه
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
    Transaction *temp = head; // نبدأ من أول الليست

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
    Transaction *temp = head; // نبدأ من أول الليست

    while (temp != NULL)
    { // نلف على كل العناصر
        cout << temp->id << " " << temp->type << " " << temp->amount << endl;
        temp = temp->next; // نروح للي بعده
    }
}

// deleteTransaction(): حذف عملية بالـ ID
void deleteTransaction(int id)
{
    Transaction *temp = head; // نبدأ من أول الليست

    while (temp != NULL)
    {
        if (temp->id == id)
        {                     // لو لقينا العنصر
            if (temp == head) // لو هو أول عنصر
                head = temp->next;

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
    if (head == NULL)
        return; // لو الليست فاضية

    bool swapped;      // متغير نعرف بيه هل حصل تبديل ولا لا
    Transaction *ptr1; // بوينتر للمقارنة

    do
    {
        swapped = false; // في البداية مفيش تبديل
        ptr1 = head;     // نبدأ من أول عنصر

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

int main()
{
    addTransaction(3, "deposit", 500);
    addTransaction(1, "withdrawal", 200);
    addTransaction(2, "transfer", 300);

    cout << "All Transactions:\n";
    viewTransactions();

    cout << "\nAfter Bubble Sort:\n";
    bubbleSortTransactions();
    viewTransactions();

    cout << "\nSearching for ID 2:\n";
    findTransaction(2);

    cout << "\nDeleting ID 1:\n";
    deleteTransaction(1);
    viewTransactions();

    return 0;
}