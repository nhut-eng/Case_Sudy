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

    // Khởi tạo bác sĩ
    addDoctor(listDoctors, 1);
    addDoctor(listDoctors, 2);

    // Khởi tạo bệnh nhân
    addPatient(listPatients, 1, 0, 10);
    addPatient(listPatients, 2, 2, 5);
    addPatient(listPatients, 3, 5, 8);
    addPatient(listPatients, 4, 12, 4);

    cout << "=== LICH KHAM BENH ===\n";

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
