#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <iomanip>   
#include <fstream>   
#include <cmath>

using namespace std;

// Chuyen doi 7.30 (7h30) -> 450 phut
int doiSangPhut(double gioThapPhan) {
    int gio = (int)gioThapPhan;
    int phut = (int)((gioThapPhan - gio) * 100 + 0.5); // +0.5 de lam tron so thuc
    return gio * 60 + phut;
}

// Chuyen doi 450 phut -> 7.30
double doiSangGio(int tongPhut) {
    int gio = tongPhut / 60;
    int phut = tongPhut % 60;
    return gio + (phut / 100.0);
}

string formatGio(double gioThapPhan) {
    int gio = (int)gioThapPhan;
    int phut = (int)((gioThapPhan - gio) * 100 + 0.5);
    string phutStr = (phut < 10) ? "0" + to_string(phut) : to_string(phut);
    return to_string(gio) + "h" + phutStr;
}

string convertString(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}

struct SlotKham {
    double gioBatDau;   
    int thoiLuong;      
    string tenBacSi;    
    bool daDung;        

    SlotKham(double gio, int tl, string name)
        : gioBatDau(gio), thoiLuong(tl), tenBacSi(name), daDung(false) {
    }
};

struct BacSi {
    string ten;
    string chuyenKhoa;  
    vector<SlotKham> slots;

    BacSi(string t, string ck) : ten(t), chuyenKhoa(ck) {}

    void themSlot(double gio, int thoiLuong) { 
        slots.push_back(SlotKham(gio, thoiLuong, ten));
        sort(slots.begin(), slots.end(), [](const SlotKham& a, const SlotKham& b) {
            return a.gioBatDau < b.gioBatDau;
        });
    }
};

struct BenhNhan {
    string ten;
    string chuyenKhoaCan;   
    int mucDoKhanCap;       
    double gioDen;          

    BenhNhan(string t, string ck, int md, double gd)
        : ten(t), chuyenKhoaCan(ck), mucDoKhanCap(md), gioDen(gd) {
    }
};

struct DongHienThi {
    string tenBn;       
    string khoa;
    string loaiUuTien;  
    double gioDenBn;    
    string tenBs;       
    double gio;
    int thoiLuong;      
};


void nhapDuLieuBacSi(vector<BacSi>& dsBacSi) {
    int soLuongBs;
    cout << "=== NHAP THOI GIAN LAM VIEC CUA BAC SI ===" << endl;
    cout << "Luu y: Nhap gio theo dinh dang thap phan (VD: 7h30 la 7.30)" << endl; 
    cout << "Nhap so luong bac si: ";
    while (!(cin >> soLuongBs)) {
        cout << "Loi: Vui long nhap so! Nhap lai: ";
        cin.clear(); cin.ignore(1000, '\n');
    }

    for (int i = 0; i < soLuongBs; ++i) {
        string ten, khoa;
        cout << "\n--- Bac si thu " << i + 1 << " ---" << endl;
        cout << "Ten bac si: "; cin.ignore(); getline(cin, ten);
        
        while (true) {
            cout << "Chuyen khoa (NOI/NGOAI): "; 
            cin >> khoa;
            khoa = convertString(khoa);
            if (khoa == "NOI" || khoa == "NGOAI") break; 
            cout << "Chi chap nhan 'noi/NOI' hoac 'ngoai/NGOAI'. Vui long nhap lai!" << endl;
        }

        BacSi bs(ten, khoa);

        int soCa;
        cout << "So ca lam viec trong ngay : ";
        cin >> soCa;

        int tongSlot = 0;
        for (int k = 0; k < soCa; ++k) {
            double gioBd, gioKt, tl;
            cout << "  > Ca thu " << k + 1 << ":" << endl;
            cout << "    - Gio bat dau: "; cin >> gioBd;
            cout << "    - Gio ket thuc: "; cin >> gioKt;
            cout << "    - Thoi luong moi ca tham kham: "; cin >> tl;

            int phutHienTai = doiSangPhut(gioBd);
            int phutKetThuc = doiSangPhut(gioKt);
            int thoiLuongPhut = (int)tl;

            while (phutHienTai + thoiLuongPhut <= phutKetThuc) {
                bs.themSlot(doiSangGio(phutHienTai), thoiLuongPhut);
                
                phutHienTai += thoiLuongPhut;
                tongSlot++;
            }
        }
        dsBacSi.push_back(bs);
    }
}

void nhapDuLieuBenhNhan(vector<BenhNhan>& dsBenhNhan) {
    int soLuongBn;
    cout << "\n=== NHAP LICH KHAM HOM NAY CUA BENH NHAN ===" << endl;
    cout << "Nhap so luong benh nhan: "; cin >> soLuongBn;
    for (int i = 0; i < soLuongBn; ++i) {
        string ten, khoa; int md; double gd;
        cout << "\n--- Benh nhan thu " << i + 1 << " ---" << endl;
        cout << "Ten benh nhan: "; cin.ignore(); getline(cin, ten);
        cout << "Khoa can kham (VD: Noi/Ngoai): "; cin >> khoa;
        khoa = convertString(khoa);
        cout << "Muc do (Thuong = 1, Khan cap = 2): "; cin >> md;
        cout << "Gio den benh vien: "; cin >> gd;
        dsBenhNhan.push_back(BenhNhan(ten, khoa, md, gd));
    }
}

vector<DongHienThi> xuLyXepLich(vector<BacSi>& dsBacSi, vector<BenhNhan>& dsBenhNhan) {
    vector<BenhNhan> dsXuLy = dsBenhNhan; 

    sort(dsXuLy.begin(), dsXuLy.end(), [](const BenhNhan& a, const BenhNhan& b) {
        if (a.mucDoKhanCap != b.mucDoKhanCap)
            return a.mucDoKhanCap > b.mucDoKhanCap;
        return a.gioDen < b.gioDen;
    });

    vector<DongHienThi> ketQuaCuoi;
    for (auto& bn : dsXuLy) {
        vector<SlotKham*> slotPhuHop;
        for (auto& bs : dsBacSi) {
            if (bs.chuyenKhoa == bn.chuyenKhoaCan) {
                for (auto& slot : bs.slots) {
                    if (!slot.daDung && slot.gioBatDau >= bn.gioDen) {
                        slotPhuHop.push_back(&slot);
                    }
                }
            }
        }
        if (!slotPhuHop.empty()) {
            sort(slotPhuHop.begin(), slotPhuHop.end(), [](SlotKham* a, SlotKham* b) {
                return a->gioBatDau < b->gioBatDau;
            });
            SlotKham* slotChon = slotPhuHop[0];
            slotChon->daDung = true;
            DongHienThi kq;
            kq.tenBn = bn.ten; kq.khoa = bn.chuyenKhoaCan;
            kq.loaiUuTien = (bn.mucDoKhanCap == 2) ? "KHAN CAP" : "Thuong";
            kq.gioDenBn = bn.gioDen; kq.tenBs = slotChon->tenBacSi;
            kq.gio = slotChon->gioBatDau; 
            kq.thoiLuong = slotChon->thoiLuong;
            ketQuaCuoi.push_back(kq);
        }
    }
    sort(ketQuaCuoi.begin(), ketQuaCuoi.end(), [](const DongHienThi& a, const DongHienThi& b) {
        return a.gio < b.gio;
    });
    return ketQuaCuoi;
}

void xuatDsBenhNhanFile(const vector<BenhNhan>& ds, string tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) return;

    f << "================ DANH SACH BENH NHAN DA TIEP NHAN ================" << endl;
    f << left << setw(20) << "HO TEN" 
      << left << setw(15) << "KHOA" 
      << left << setw(15) << "MUC DO" 
      << "GIO DEN" << endl;
    f << "------------------------------------------------------------------" << endl;
    string gioDen;
    for (const auto& bn : ds) {
        gioDen = formatGio(bn.gioDen);
        f << left << setw(20) << bn.ten
          << left << setw(15) << bn.chuyenKhoaCan
          << left << setw(15) << (bn.mucDoKhanCap == 2 ? "Khan cap" : "Thuong")
          << fixed << setprecision(1) <<  gioDen << endl;
    }
    f.close();
    cout << " -> Da xuat file: " << tenFile << endl;
}

void xuatLichBacSiFile(const vector<BacSi>& ds, string tenFile) {
    ofstream f(tenFile);
    if (!f.is_open()) return;

    f << "================ LICH LAM VIEC CUA BAC SI ================" << endl;
    for (const auto& bs : ds) {
        f << "BS: " << bs.ten << " (" << bs.chuyenKhoa << ")" << endl;
        f << "Cac khung gio (" << (bs.slots.empty() ? 0 : bs.slots[0].thoiLuong) << " phut/slot) da dang ky:" << endl;
        for (const auto& slot : bs.slots) {
            int phutBatDau = doiSangPhut(slot.gioBatDau);
            int phutKetThuc = phutBatDau + slot.thoiLuong;
            
            f << "   [ " << formatGio(slot.gioBatDau) 
              << " - " << formatGio(doiSangGio(phutKetThuc)) << " ]" << endl;
        }
        f << "----------------------------------------------------------" << endl;
    }
    f.close();
    cout << " -> Da xuat file: " << tenFile << endl;
}

void xuatKetQuaFile(const vector<DongHienThi>& danhSach, string tenFile) {
    ofstream f(tenFile); 
    if (!f.is_open()) {
        cout << "!!! LOI: KHONG THE TAO FILE KET QUA." << endl;
        return;
    }

    f << "=================================================================================================" << endl;
    f << "                                KET QUA XEP LICH KHAM BENH                                       " << endl;
    f << "=================================================================================================" << endl;
    f << left << setw(20) << "BENH NHAN"
      << left << setw(12) << "KHOA"
      << left << setw(12) << "LOAI"
      << left << setw(12) << "GIO DEN"
      << left << setw(20) << "BAC SI PHU TRACH"
      << left << setw(15) << "GIO KHAM"
      << "THOI LUONG" << endl;
    f << "-------------------------------------------------------------------------------------------------" << endl;

    for (const auto& item : danhSach) {
        int phutBatDau = doiSangPhut(item.gio);
        int phutKetThuc = phutBatDau + item.thoiLuong;
        double gioKetThucSo = doiSangGio(phutKetThuc);

        string strGioDen = formatGio(item.gioDenBn);
        string strGioKham = formatGio(item.gio) + " - " + formatGio(gioKetThucSo);

        f << left << setw(20) << item.tenBn
        << left << setw(10) << item.khoa
        << left << setw(12) << item.loaiUuTien;
        
        f << left << setw(10) << strGioDen;    
        f << left << setw(20) << item.tenBs;
        f << left << setw(20) << strGioKham;   

        if (item.thoiLuong % 60 == 0) {
            f << (item.thoiLuong / 60) << " gio";
        } else {
            f << item.thoiLuong << " phut";
        }
        f << endl;
    }
    f.close();
    cout << " -> Da xuat file: " << tenFile << endl;
}

int main() {
    vector<BacSi> dsBacSi;
    vector<BenhNhan> dsBenhNhan;
    vector<DongHienThi> ketQua;    
    int lc = -1;

    while (lc != 0) {
        cout << "\n--------------MENU--------------\n";
        cout << "1. Quan ly lich bac si \n";
        cout << "2. Quan ly lich benh nhan\n";
        cout << "3. Xuat file ket qua xep lich\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> lc;

        switch (lc) {
        case 1:
            nhapDuLieuBacSi(dsBacSi);
            xuatLichBacSiFile(dsBacSi, "lichBS.txt");
            break;
        case 2:
            nhapDuLieuBenhNhan(dsBenhNhan);
            xuatDsBenhNhanFile(dsBenhNhan, "lichKhamBN.txt");
            break;
        case 3:
            ketQua = xuLyXepLich(dsBacSi, dsBenhNhan);
            xuatKetQuaFile(ketQua, "lichKham.txt");
            break;
        case 0:
            cout << "Thoat chuong trinh!\n";
            break;
        default:
            cout << "Cu phap khong hop le!\n";
        }
    }

    return 0;
}