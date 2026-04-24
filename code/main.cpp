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

    return 0;
}
