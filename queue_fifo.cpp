#include <iostream>
#include<queue>
#include<string>
using namespace std;
struct BenhNhan{
    int maBN;
    string ten;
    int tuoi;
    string benh;    
};
struct Queue {
    BenhNhan data[100];
    int front;
    int rear;
};
void initQueue(Queue &q) {
    q.front = 0;
    q.rear = -1;
}
bool isEmpty(Queue q) {
    return q.front > q.rear;
}
bool enqueue(Queue &q, BenhNhan bn) {
    if (q.rear == 100 - 1) {
        return false; 
    }
    q.rear++;
    q.data[q.rear] = bn;
    return true;
}
bool dequeue(Queue &q, BenhNhan &bn) {
    if (isEmpty(q)) {
        return false; 
    }
    bn = q.data[q.front];
    q.front++;
    return true;
}
int main() {
    Queue q;
    initQueue(q);
    enqueue(q, {1, "Nguyen Van A", 30, "cam sot"});
    enqueue(q, {2, "Tran Thi B", 22, "viem hong"});
    enqueue(q, {3, "Le Van C", 45, "benh tim"});
    cout << "Danh sach benh nhan duoc kham:\n";
    BenhNhan bn;
    while (!isEmpty(q)) {
        dequeue(q, bn);
        cout << "Ma BN: " << bn.maBN
             << " - Ten BN: " << bn.ten
             << " - Tuoi: " << bn.tuoi
             << " - Benh: " << bn.benh << endl;
    }
    return 0;
};