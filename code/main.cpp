#include <iostream>
#include "MySTL.h"
#include "HashMap.h"
#include "BinarySearchTree.h"
using namespace std;
 
int main()
{
    MyStack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
 
    MyQueue<int> q;
    q.enqueue(11);
    q.enqueue(12);
    q.enqueue(13);
    cout << q.front() << endl;
    q.dequeue();
    cout << q.front() << endl;
 
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.insert(1, 15);
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    v.erase(1);
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
    cout << v.front() << endl;
    cout << v.back() << endl;
    v.pop_back();
    cout << v.size() << endl;
 
    MyLinkedList<int> L;
    L.push_back(100);
    L.push_back(200);
    L.push_back(300);
    L.push_front(50);
    cout << L.size() << endl;
    for (int x : L)
        cout << x << " ";
    cout << endl;
    L.erase(1);
    for (int x : L)
        cout << x << " ";
    cout << endl;
    cout << L.front() << endl;
    cout << L.back() << endl;
    L.pop_front();
    cout << L.size() << endl;

    cout << "HashMap\n\n";

    HashMap map;
    map.insert("Ayesha", 25);
    map.insert("Wania",  30);
    map.insert("Hadia",  22);
    map.display();

    cout << "Get Ayesha: " << map.get("Ayesha") << "\n";
    cout << "Get Zara:   " << map.get("Zara")   << " (not found)\n\n";

    map.insert("Wania", 99);
    cout << "Wania updated: " << map.get("Wania") << "\n\n";

    map.remove("Hadia");
    map.remove("Zara");
    map.display();

    cout << "Binary Search Tree\n\n";

    BinarySearchTree bst;
    for (int val : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(val);

    cout << "\n";
    bst.printInOrder();
    bst.printPreOrder();
    bst.printPostOrder();

    cout << "\nSearch 40: " << (bst.search(40) ? "Found" : "Not found") << "\n";
    cout << "Search 99: " << (bst.search(99) ? "Found" : "Not found") << "\n\n";

    bst.remove(20);
    bst.remove(30);
    bst.remove(50);
    bst.printInOrder();
 
    return 0;
}
