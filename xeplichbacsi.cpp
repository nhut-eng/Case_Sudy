#include <iostream>
#include <string>

using namespace std;

// ===== BÁC SĨ (LINKED LIST) =====
struct Doctor {
    int id;
    int freeTime;
    Doctor* next;
};

// ===== BỆNH NHÂN (LINKED LIST) =====
struct Patient {
    int id;
    int arrivalTime;
    int duration;
    Patient* next;
};

// Thêm bác sĩ
void addDoctor(Doctor*& head, int id) {
    Doctor* newNode = new Doctor{id, 0, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        Doctor* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Thêm bệnh nhân
void addPatient(Patient*& head, int id, int arrival, int duration) {
    Patient* newNode = new Patient{id, arrival, duration, nullptr};
    if (head == nullptr) {
        head = newNode;
    } else {
        Patient* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Tìm bác sĩ rảnh sớm nhất
Doctor* findBestDoctor(Doctor* head) {
    Doctor* best = head;
    Doctor* temp = head->next;

    while (temp != nullptr) {
        if (temp->freeTime < best->freeTime)
            best = temp;
        temp = temp->next;
    }
    return best;
}

int main() {
    Doctor* listDoctors = nullptr;
    Patient* listPatients = nullptr;

    int nDoctor, nPatient;

    // ===== NHẬP BÁC SĨ =====
    cout << "Nhap so bac si: ";
    cin >> nDoctor;

    for (int i = 0; i < nDoctor; i++) {
        int id;
        cout << "Nhap ID bac si thu " << i + 1 << ": ";
        cin >> id;
        addDoctor(listDoctors, id);
    }

    // ===== NHẬP BỆNH NHÂN =====
    cout << "\nNhap so benh nhan: ";
    cin >> nPatient;

    for (int i = 0; i < nPatient; i++) {
        int id, arrival, duration;
        cout << "\nBenh nhan thu " << i + 1 << endl;
        cout << "  ID: ";
        cin >> id;
        cout << "  Thoi diem den: ";
        cin >> arrival;
        cout << "  Thoi gian kham: ";
        cin >> duration;

        addPatient(listPatients, id, arrival, duration);
    }

    // ===== XẾP LỊCH =====
    cout << "\n=== LICH KHAM BENH ===\n";

    Patient* currP = listPatients;
    while (currP != nullptr) {

        Doctor* bestDoc = findBestDoctor(listDoctors);

        int startTime = (currP->arrivalTime > bestDoc->freeTime)
                        ? currP->arrivalTime
                        : bestDoc->freeTime;

        int endTime = startTime + currP->duration;

        cout << "Benh nhan " << currP->id
             << " -> Bac si " << bestDoc->id
             << " (Tu " << startTime
             << " den " << endTime << ")\n";

        bestDoc->freeTime = endTime;
        currP = currP->next;
    }

    return 0;
}
