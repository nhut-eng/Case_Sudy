#include <iostream>
#include <string>

using namespace std;

// 1. Định nghĩa Node cho Danh sách liên kết
struct Node {
    int batDau;
    int ketThuc;
    Node* next; 

    // Constructor tạo Node nhanh
    Node(int b, int k) : batDau(b), ketThuc(k), next(nullptr) {}
};

// 2. Class Quản lý danh sách liên kết
class QuanLyLichLinkedList {
private:
    Node* head; 
    string tenBacSi;

public:
    QuanLyLichLinkedList(string ten) : tenBacSi(ten), head(nullptr) {}

    // Destructor: Giải phóng bộ nhớ khi chương trình kết thúc
    ~QuanLyLichLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        cout << "Da don dep bo nho cua Linked List." << endl;
    }

    // --- THUẬT TOÁN KIỂM TRA TRÙNG (Duyệt từ đầu đến cuối) ---
    bool kiemTraTrong(int gioBatDau, int gioKetThuc) {
        Node* current = head;
        while (current != nullptr) {

            if (!(current->ketThuc <= gioBatDau || current->batDau >= gioKetThuc)) {
                return false; // Bị trùng
            }
            current = current->next;
        }
        return true; // Không trùng ai cả
    }

    // --- THUẬT TOÁN CHÈN CÓ SẮP XẾP (Sorted Insert) ---
    void dangKyLich(int gioBatDau, int gioKetThuc) {
        // B1: Kiểm tra tính hợp lệ
        if (gioBatDau >= gioKetThuc) {
            cout << "-> [LOI] Gio ket thuc phai lon hon gio bat dau!" << endl;
            return;
        }

        // B2: Kiểm tra trùng lịch
        if (!kiemTraTrong(gioBatDau, gioKetThuc)) {
            cout << "-> [THAT BAI] Trung lich voi ca da co!" << endl;
            return;
        }

        // B3: Tạo Node mới
        Node* newNode = new Node(gioBatDau, gioKetThuc);

        // B4: Tìm vị trí chèn (Để danh sách luôn tăng dần theo giờ)
        
        // Trường hợp 1: Chèn vào đầu (Danh sách rỗng hoặc ca mới sớm hơn ca đầu tiên)
        if (head == nullptr || head->batDau >= newNode->batDau) {
            newNode->next = head;
            head = newNode;
        } 
        // Trường hợp 2: Chèn vào giữa hoặc cuối
        else {
            Node* current = head;
            // Duyệt để tìm vị trí mà ca tiếp theo có giờ bắt đầu lớn hơn ca mới
            while (current->next != nullptr && current->next->batDau < newNode->batDau) {
                current = current->next;
            }
            // Chèn newNode vào sau current
            newNode->next = current->next;
            current->next = newNode;
        }

        cout << "-> [THANH CONG] Da them lich: " << gioBatDau << " - " << gioKetThuc << endl;
    }

    // Hiển thị danh sách
    void hienThi() {
        cout << "\n--- Lich trinh (Linked List) cua BS " << tenBacSi << " ---" << endl;
        if (head == nullptr) {
            cout << "Danh sach trong (Ranh ca ngay)." << endl;
        } else {
            Node* current = head;
            int count = 1;
            while (current != nullptr) {
                cout << count++ << ". Ban: " << current->batDau << " -> " << current->ketThuc << endl;
                current = current->next;
            }
        }
        cout << "---------------------------------------" << endl;
    }
};

int main() {
    string ten;
    cout << "--- HE THONG QUAN LY LICH (LINKED LIST) ---" << endl;
    cout << "Nhap Ten Bac si: ";
    getline(cin, ten);

    QuanLyLichLinkedList ds(ten);

    int luaChon;
    while (true) {
        cout << "\n1. Them lich kham" << endl;
        cout << "2. Xem danh sach" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon: ";
        cin >> luaChon;

        if (luaChon == 0) break;

        if (luaChon == 1) {
            int s, e;
            cout << "Nhap gio Bat dau (VD 800): "; cin >> s;
            cout << "Nhap gio Ket thuc (VD 900): "; cin >> e;
            ds.dangKyLich(s, e);
        } 
        else if (luaChon == 2) {
            ds.hienThi();
        }
    }

    return 0;
}