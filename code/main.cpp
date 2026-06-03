#include <iostream>
#include"MyQueue.h"
#include"MyStack.h"
#include"Vector.h"
#include"LinkedList.h"
#include "HashMap.h"
#include "BST.h"

using namespace std;

int main()
{
    cout << "================ STACK ================\n";

    MyStack<int> s;


    s.push(10);
    s.push(20);
    s.push(30);
    cout << "After push(10, 20, 30):\n";
    cout << "  Top element : " << s.top() << endl;


    cout << "  Size : " << s.size() << endl;


    cout << "  Empty? : " << (s.empty() ? "Yes" : "No") << endl;


    s.pop();
    cout << "After pop():\n";
    cout << "  Top element : " << s.top() << endl;
    cout << "  Size: " << s.size() << endl;

    MyStack<int> s2(s);
    cout << "Copy of stack - Top: " << s2.top()
        << ", Size: " << s2.size() << endl;

    MyStack<int> s3;
    s3 = s;
    cout << "Assigned stack - Top: " << s3.top()
        << ", Size: " << s3.size() << endl;

    while (!s.empty())
        s.pop();
    cout << "After popping all - Empty? : " << (s.empty() ? "Yes" : "No") << endl;

    try {
        s.pop();
    }
    catch (const std::out_of_range& e)
    {
        cout << "Exception caught (pop on empty): " << e.what() << endl;
    }

    try {
        s.top();
    }
    catch (const std::out_of_range& e) {
        cout << "Exception caught (top on empty): " << e.what() << endl;
    }


    cout << "\n================ QUEUE ================\n";

    MyQueue<int> q;

    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    cout << "After enqueue(11, 12, 13):\n";
    cout << "  Front element : " << q.front() << endl;
    cout << "  Rear element  : " << q.rear() << endl;

    cout << "  Size          : " << q.size() << endl;

    cout << "  Empty?        : " << (q.empty() ? "Yes" : "No") << endl;

    q.dequeue();
    cout << "After dequeue():\n";
    cout << "  Front element : " << q.front() << endl;
    cout << "  Size          : " << q.size() << endl;

    MyQueue<int> q2(q);
    cout << "Copy of queue - Front: " << q2.front()
        << ", Size: " << q2.size() << endl;

    MyQueue<int> q3;
    q3 = q;
    cout << "Assigned queue - Front: " << q3.front()
        << ", Size: " << q3.size() << endl;

    while (!q.empty())
        q.dequeue();
    cout << "After dequeuing all - Empty? : " << (q.empty() ? "Yes" : "No") << endl;

    try {
        q.dequeue();
    }
    catch (const std::out_of_range& e) {
        cout << "Exception caught (dequeue on empty): " << e.what() << endl;
    }

    try {
        q.front();
    }
    catch (const std::out_of_range& e)
    {
        cout << "Exception caught (front on empty): " << e.what() << endl;
    }

    try {
        q.rear();
    }
    catch (const std::out_of_range& e)
    {
        cout << "Exception caught (rear on empty): " << e.what() << endl;
    }
    cout << "\n================ VECTOR ================\n";

    MyVector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    cout << "After push_back(): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    v.insert(1, 15);

    cout << "After insert(1, 15): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    cout << "\nFind 20: " << v.find(20) << endl;
    cout << "Find 999: " << v.find(999) << endl;
    cout << endl;
    v.resize(8, 99);

    cout << "After resize(8,99): ";
    for (int x : v)
        cout << x << " ";
    cout << endl;
    cout << "Capacity before shrink: "
        << v.capacity() << endl;

    v.shrink_to_fit();

    cout << "Capacity after shrink: "
        << v.capacity() << endl;
    cout << endl;

    v.erase(1);

    cout << "After erase(1): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    cout << endl;
    cout << "Is vector empty? "
        << (v.empty() ? "Yes" : "No")
        << endl;

    cout << "Front element: " << v.front() << endl;
    cout << "Back element : " << v.back() << endl;

    v.pop_back();

    cout << "After pop_back(): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    cout << "Current size: " << v.size() << endl;
    cout << endl;

    cout << "\nCapacity before reserve: "
        << v.capacity() << endl;

    v.reserve(50);

    cout << "Capacity after reserve(50): "
        << v.capacity() << endl;

    cout << "Capacity before shrink: "
        << v.capacity() << endl;

    v.shrink_to_fit();

    cout << "Capacity after shrink: "
        << v.capacity() << endl;
    MyVector<int> sortVec;

    sortVec.push_back(50);
    sortVec.push_back(10);
    sortVec.push_back(40);
    sortVec.push_back(20);
    sortVec.push_back(30);

    cout << "\nBefore sort: ";

    for (int x : sortVec)
        cout << x << " ";

    sortVec.sort();

    cout << "\nAfter sort: ";

    for (int x : sortVec)
        cout << x << " ";

    cout << endl;
    MyVector<int> copyVec(sortVec);

    cout << "\nCopied vector: ";

    for (int x : copyVec)
        cout << x << " ";

    cout << endl;
    cout << "\nElement at index 2: ";
    if (v.size() > 2)
        cout << v.at(2);
    else
        cout << "(index 2 out of range, size=" << v.size() << ")";
    cout << endl;


    cout << "\n============= LINKED LIST =============\n";

    MyLinkedList<int> L;

    L.push_back(100);
    L.push_back(200);
    L.push_back(300);
    L.push_front(50);

    cout << "After insertions: ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    L.insert(1, 150);
    cout << "\nAfter insert(1,150): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    L.reverse();

    cout << "After reverse(): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    L.erase(1);

    cout << "After erase(1): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    cout << "\nFind 99: "
        << L.find(99) << endl;
    cout << "Contains 300: "
        << (L.contains(300) ? "Yes" : "No")
        << endl;
    L.remove(150);

    cout << "\nAfter remove(150): ";

    for (int x : L)
        cout << x << " ";

    cout << endl;
    cout << endl;


    cout << "Front element: " << L.front() << endl;
    cout << "Back element : " << L.back() << endl;

    L.pop_front();

    cout << "After pop_front(): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    cout << "Current size: " << L.size() << endl;
    MyLinkedList<int> list2;

    list2.push_back(50);
    list2.push_back(10);
    list2.push_back(40);
    list2.push_back(20);
    list2.push_back(30);


    cout << "\nBefore sort: ";

    for (int x : list2)
        cout << x << " ";

    list2.sort();

    cout << "\nAfter sort: ";

    for (int x : list2)
        cout << x << " ";

    cout << endl;
    cout << endl;
    cout << "\nTesting Iterator Insert\n";

    auto it = list2.begin();
    ++it;

    cout << "Inserting 999 before value "
        << *it << endl;

    list2.insert(it, 999);

    cout << "List after insertion: ";
    for (int x : list2)
        cout << x << " ";
    cout << endl;
    cout << endl;

    cout << "\nTesting Iterator Erase\n";

    auto eraseIt = list2.begin();
    ++eraseIt;

    cout << "Erasing value "
        << *eraseIt << endl;

    list2.erase(eraseIt);

    cout << "List after erase: ";
    for (int x : list2)
        cout << x << " ";
    cout << endl;



    L.clear();

    cout << "After clear(), size = "
        << L.size()
        << endl;


    cout << "\n=============== HASH MAP ===============\n\n";

    HashMap map;

    map.insert("Ayesha", 25);
    map.insert("Wania", 30);
    map.insert("Hadia", 22);

    map.display();

    cout << "Get Ayesha: "
        << map.get("Ayesha") << endl;

    cout << "Get Zara: "
        << map.get("Zara")
        << " (not found)\n\n";

    map.insert("Wania", 99);

    cout << "Updated Wania: "
        << map.get("Wania") << endl;

    map.remove("Hadia");
    map.remove("Zara");

    cout << endl;

    map.display();


    cout << "\n=========== BINARY SEARCH TREE ==========\n\n";

    BinarySearchTree bst;

    for (int val : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(val);

    cout << endl;

    bst.printInOrder();
    bst.printPreOrder();
    bst.printPostOrder();

    cout << "\nSearch 40: "
        << (bst.search(40) ? "Found" : "Not Found")
        << endl;

    cout << "Search 99: "
        << (bst.search(99) ? "Found" : "Not Found")
        << endl;

    bst.remove(20);
    bst.remove(30);
    bst.remove(50);

    cout << "\nAfter deletions:\n";
    bst.printInOrder();

    cout << "\n\n========================================";
    cout << "\nTIME COMPLEXITY COMPARISON";
    cout << "\n========================================\n";

    cout << "\nSTACK";
    cout << "\nCustom Stack      : Push O(1), Pop O(1), Top O(1), Size O(1)";
    cout << "\nSTL Stack         : Push O(1), Pop O(1), Top O(1), Size O(1)\n";

    cout << "\nQUEUE";
    cout << "\nCustom Queue      : Enqueue O(1), Dequeue O(1), Front O(1), Size O(1)";
    cout << "\nSTL Queue         : Push O(1), Pop O(1), Front O(1), Size O(1)\n";

    cout << "\nVECTOR";
    cout << "\nCustom Vector     : [] O(1), At O(1), Front/Back O(1)";
    cout << "\n                    Push_Back O(1)*, Pop_Back O(1)";
    cout << "\n                    Insert O(n), Erase O(n)";
    cout << "\n                    Find O(n), Resize O(n)";
    cout << "\n                    Reserve O(n), Shrink_To_Fit O(n)";
    cout << "\n                    Sort O(n log n)";
    cout << "\nSTL Vector        : Same asymptotic complexities\n";

    cout << "\nLINKED LIST";
    cout << "\nCustom LinkedList : Front/Back O(1)";
    cout << "\n                    Push_Front O(1), Push_Back O(1)";
    cout << "\n                    Pop_Front O(1), Pop_Back O(1)";
    cout << "\n                    At O(n), [] O(n)";
    cout << "\n                    Insert(Index) O(n)";
    cout << "\n                    Erase(Index) O(n)";
    cout << "\n                    Insert(Iterator) O(1)";
    cout << "\n                    Erase(Iterator) O(1)";
    cout << "\n                    Find/Contains O(n)";
    cout << "\n                    Reverse O(n)";
    cout << "\n                    Sort O(n log n)";
    cout << "\nSTL List          : Same asymptotic complexities\n";

    cout << "\nHASH MAP";
    cout << "\nCustom HashMap    : Insert O(1), Search O(1), Delete O(1)";
    cout << "\nunordered_map     : Insert O(1), Search O(1), Delete O(1)\n";

    cout << "\nBINARY SEARCH TREE";
    cout << "\nCustom BST        : Insert/Search/Delete O(log n) average";
    cout << "\nstd::set          : Insert/Search/Delete O(log n)\n";

    cout << "\n* O(1) amortized";
    cout << "\n========================================\n";

    return 0;
}
