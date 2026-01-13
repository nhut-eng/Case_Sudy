#include <iostream>
#include<queue>
#include<string>
using namespace std;
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