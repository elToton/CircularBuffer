#include <iostream>
#include <algorithm>
#include "buffer.h"

using namespace std;

int main()
{
    RingBuffer<double> NewRingBuffer(5);
    NewRingBuffer.printAll();
    cout << '\n';

    //pushing back 2 numbers
    NewRingBuffer.push_back(46);
    NewRingBuffer.push_back(2.6);
    NewRingBuffer.printAll();
    cout << '\n';

    //pushing to front 4 numbers
    NewRingBuffer.push_front(3.6);
    NewRingBuffer.push_front(6);
    NewRingBuffer.push_front(3.5);
    NewRingBuffer.push_front(7.3);
    NewRingBuffer.printAll();
    cout << '\n';

    //erase 3rd element via iterator
    Iterator<double> iter = NewRingBuffer.erase(NewRingBuffer.begin() + 3);
    NewRingBuffer.printAll();
    cout << "\telement after erased: " << *iter << '\n' << '\n';

    //insert 3 elements via iterator on 2nd position
    NewRingBuffer.insert(NewRingBuffer.begin() + 1, 6.2);
    NewRingBuffer.printAll();
    cout << '\n';
    NewRingBuffer.insert(NewRingBuffer.begin() + 1, 8.0);
    NewRingBuffer.printAll();
    cout << '\n';
    NewRingBuffer.insert(NewRingBuffer.begin() + 1, 10.4);
    NewRingBuffer.printAll();
    cout << '\n';

    //push back 2 zeros
    NewRingBuffer.push_back(0);
    NewRingBuffer.push_back(0);
    NewRingBuffer.printAll();
    cout << '\n';

    //inserting 3 more elements to 2nd position
    NewRingBuffer.insert(NewRingBuffer.begin() + 1, 12.0);
    NewRingBuffer.printAll();
    cout << '\n';
    NewRingBuffer.insert(NewRingBuffer.begin() + 1, 14.0);
    NewRingBuffer.printAll();
    cout << '\n';
    iter = NewRingBuffer.insert(NewRingBuffer.begin() + 1, 1.0);
    NewRingBuffer.printAll();
    cout << "\telement last inserted: " << *iter << '\n';

    cout << "Showing all elements via []: " << *iter << '\n';
    for (int i = 0; i < 5; i++) cout << NewRingBuffer[i] << ' ';
    cout << '\n';

    cout << "\nAccess to top and bottom:\n";
    cout << "\tTop: " << NewRingBuffer.top() << '\n';
    cout << "\tBottom: " << NewRingBuffer.bottom() << '\n';
    cout << '\n';

    //change buffer capacity to 10
    NewRingBuffer.ChangeCapacity(10);
    NewRingBuffer.printAll();
    cout << '\n';

    //push to it two numbers
    NewRingBuffer.push_front(666);
    NewRingBuffer.push_front(777);
    NewRingBuffer.printAll();
    cout << '\n';

    //resize capacity to 7
    NewRingBuffer.ChangeCapacity(7);
    NewRingBuffer.printAll();
    cout << '\n';

    //spin it to unwind ring and separete begin and end and sort via standard stl algorithm
    NewRingBuffer.spin();
    NewRingBuffer.printAll();
    cout << '\n';
    sort(NewRingBuffer.begin(), NewRingBuffer.end());
    NewRingBuffer.printAll();
}