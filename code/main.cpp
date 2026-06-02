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
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Top element: " << s.top() << endl;

    s.pop();

    cout << "After pop(), top element: " << s.top() << endl;


    cout << "\n================ QUEUE ================\n";

    MyQueue<int> q;
    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);

    cout << "Front element: " << q.front() << endl;

    q.dequeue();

    cout << "After dequeue(), front element: "
        << q.front() << endl;


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

    v.erase(1);

    cout << "After erase(1): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    cout << "Front element: " << v.front() << endl;
    cout << "Back element : " << v.back() << endl;

    v.pop_back();

    cout << "After pop_back(): ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    cout << "Current size: " << v.size() << endl;


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

    L.erase(1);

    cout << "After erase(1): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    cout << "Front element: " << L.front() << endl;
    cout << "Back element : " << L.back() << endl;

    L.pop_front();

    cout << "After pop_front(): ";
    for (int x : L)
        cout << x << " ";
    cout << endl;

    cout << "Current size: " << L.size() << endl;


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
    cout << "\nCustom Stack      : Push O(1), Pop O(1)";
    cout << "\nSTL Stack         : Push O(1), Pop O(1)\n";
    cout << "\nQUEUE";
    cout << "\nCustom Queue      : Enqueue O(1), Dequeue O(1)";
    cout << "\nSTL Queue         : Push O(1), Pop O(1)\n";
    cout << "\nVECTOR";
    cout << "\nCustom Vector     : Push_Back O(1)*, Insert O(n), Erase O(n)";
    cout << "\nSTL Vector        : Push_Back O(1)*, Insert O(n), Erase O(n)\n";
    cout << "\nLINKED LIST";
    cout << "\nCustom LinkedList : Push_Front O(1), Push_Back O(1), Erase O(n)";
    cout << "\nSTL List          : Push_Front O(1), Push_Back O(1), Erase O(n)\n";
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
