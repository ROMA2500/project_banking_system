#include <iostream>  // مكتبة الإدخال والإخراج (cout / cin)
using namespace std; // علشان نكتب cout بدل std::cout

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

int main()
{
    Branch *root = NULL; // الشجرة في الأول فاضية

    root = addBranch(root, 10, "Main", "Cairo");    // إضافة فرع
    root = addBranch(root, 5, "Branch A", "Giza");  // إضافة فرع
    root = addBranch(root, 20, "Branch B", "Alex"); // إضافة فرع

    cout << "All branches sorted by ID:" << endl;
    sortBranchesByID(root); // ترتيب الفروع بالـ ID

    Branch *result = searchBranch(root, 5); // البحث عن فرع
    if (result != NULL)
    { // لو لقيناه
        cout << "Found Branch: " << result->name << endl;
    }

    root = removeBranch(root, 10); // حذف فرع بالـ ID

    cout << "After deleting ID 10:" << endl;
    sortBranchesByID(root); // طباعة بعد الحذف

    int customers[5] = {1, 3, 5, 7, 9};           // Array بسيطة
    searchCustomerOrTransaction(customers, 5, 7); // بحث Linear

    return 0; // نهاية البرنامج
}