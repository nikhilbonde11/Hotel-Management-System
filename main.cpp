//Nikhil Bonde

// HOTEL MANAGEMENT SYSTEM


#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class hotel {
    int room_no;
    char name[30];
    char address[50];
    char phone[15];

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
    void bill(int);
};

// MAIN MENU
void hotel::main_menu() {
    int choice = 0;

    while (choice != 5) {
        cout << "\n===== HOTEL MANAGEMENT =====\n";
        cout << "1. Book Room\n";
        cout << "2. Customer Record\n";
        cout << "3. Rooms Allotted\n";
        cout << "4. Edit Record\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }
    }
}

// ADD RECORD
void hotel::add() {
    int r;
    ofstream fout("Record.dat", ios::binary | ios::app);

    cout << "\nEnter Room No: ";
    cin >> r;

    if (check(r)) {
        cout << "Room already booked!\n";
        return;
    }

    room_no = r;
    cout << "Name: ";
    cin >> name;
    cout << "Address: ";
    cin >> address;
    cout << "Phone: ";
    cin >> phone;

    fout.write((char*)this, sizeof(*this));
    cout << "Room booked successfully!\n";

    fout.close();
}

// DISPLAY PARTICULAR RECORD
void hotel::display() {
    int r, found = 0;
    ifstream fin("Record.dat", ios::binary);

    cout << "Enter room number: ";
    cin >> r;

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cout << "\nRoom No: " << room_no;
            cout << "\nName: " << name;
            cout << "\nAddress: " << address;
            cout << "\nPhone: " << phone << endl;
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Record not found!\n";

    fin.close();
}

// DISPLAY ALL ROOMS
void hotel::rooms() {
    ifstream fin("Record.dat", ios::binary);

    cout << "\nAllotted Rooms:\n";

    while (fin.read((char*)this, sizeof(*this))) {
        cout << "\nRoom No: " << room_no
             << " Name: " << name
             << " Address: " << address
             << " Phone: " << phone;
    }

    fin.close();
}

// EDIT MENU
void hotel::edit() {
    int choice, r;

    cout << "\n1. Modify\n2. Delete\n3. Bill\nChoice: ";
    cin >> choice;

    cout << "Enter room number: ";
    cin >> r;

    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        case 3: bill(r); break;
        default: cout << "Invalid\n";
    }
}

// CHECK ROOM
int hotel::check(int r) {
    ifstream fin("Record.dat", ios::binary);

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            fin.close();
            return 1;
        }
    }

    fin.close();
    return 0;
}

// MODIFY
void hotel::modify(int r) {
    fstream file("Record.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (file.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter address: ";
            cin >> address;
            cout << "Enter phone: ";
            cin >> phone;

            file.seekp(-sizeof(*this), ios::cur);
            file.write((char*)this, sizeof(*this));

            cout << "Record updated!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found!\n";

    file.close();
}

// DELETE
void hotel::delete_rec(int r) {
    ifstream fin("Record.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);

    bool found = false;

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            found = true;
            continue;
        }
        fout.write((char*)this, sizeof(*this));
    }

    fin.close();
    fout.close();

    remove("Record.dat");
    rename("temp.dat", "Record.dat");

    if (found)
        cout << "Record deleted!\n";
    else
        cout << "Record not found!\n";
}

// BILL
void hotel::bill(int r) {
    ifstream fin("Record.dat", ios::binary);
    bool found = false;

    while (fin.read((char*)this, sizeof(*this))) {
        if (room_no == r) {
            found = true;

            if (room_no <= 30)
                cout << "Bill = 2000\n";
            else if (room_no <= 45)
                cout << "Bill = 5000\n";
            else
                cout << "Bill = 7000\n";

            break;
        }
    }

    if (!found)
        cout << "Room not found!\n";

    fin.close();
}

// MAIN
int main() {
    hotel h;
    h.main_menu();
    return 0;
}
