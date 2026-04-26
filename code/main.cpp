#include <iostream>
#include "MySTL.h"
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
 
    return 0;
}
