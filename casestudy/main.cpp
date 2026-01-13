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
struct BenhNhan{
    string ten;
    int mucDoUuTien;
};
struct SoSanh{
    bool operator()(BenhNhan a, BenhNhan b){
        return a.mucDoUuTien < b.mucDoUuTien;
    }
};
int main()
{
    queue<BenhNhan> caThuong;
    priority_queue<BenhNhan, vector<BenhNhan>, SoSanh> caKhanCap;
    caThuong.push({"Nguyen Van A", 1});
    caThuong.push({"Le Thi B", 2});
    caKhanCap.push({"Tran Van C", 5});
    caKhanCap.push({"Pham Thi D", 4});
    cout <<"Thu tu kham benh:\n";
    while(!caThuong.empty() || !caKhanCap.empty()){
        BenhNhan bn;
        if(!caKhanCap.empty()){
            bn = caKhanCap.top();
            caKhanCap.pop();
        cout <<"Kham benh nhan KHAN CAP: "<< bn.ten << " (Muc do uu tien: " << bn.mucDoUuTien << ")\n";
        } else {
            bn = caThuong.front();
            caThuong.pop();
        cout <<"Kham benh nhan THUONG: "<< bn.ten << " (Muc do uu tien: " << bn.mucDoUuTien << ")\n";
        }
        
}
    return 0;
}