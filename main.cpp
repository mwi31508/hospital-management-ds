#include <iostream>
#include <string>
using namespace std;

#define MAX 10

// -------------------- QUEUE (Waiting Patients) --------------------
class PatientQueue {
public:
    int front, rear;
    string patients[MAX];

    PatientQueue() {
        front = rear = -1;
    }

    bool isEmpty() {
        return front == -1;
    }

    bool isFull() {
        return rear == MAX - 1;
    }

    // Insert patient into queue
    void addPatient(string name) {
        if (isFull()) {
            cout << "\nWaiting list is full.\n";
            return;
        }
        if (isEmpty())
            front = 0;

        patients[++rear] = name;
        cout << "\nPatient added to waiting list.\n";
    }

    // Remove patient from queue (Treat)
    string treatPatient() {
        if (isEmpty())
            return "";

        string name = patients[front];

        if (front == rear)
            front = rear = -1;
        else
            front++;

        return name;
    }

    // Search patient in waiting queue
    bool searchPatient(string name) {
        if (isEmpty())
            return false;

        for (int i = front; i <= rear; i++) {
            if (patients[i] == name)
                return true;
        }
        return false;
    }

    // Update patient name in queue
    bool updatePatient(string oldName, string newName) {
        if (isEmpty())
            return false;

        for (int i = front; i <= rear; i++) {
            if (patients[i] == oldName) {
                patients[i] = newName;
                return true;
            }
        }
        return false;
    }

    // Display waiting patients
    void display() {
        if (isEmpty()) {
            cout << "\nNo patients waiting.\n";
            return;
        }

        cout << "\nWaiting Patients:\n";
        for (int i = front; i <= rear; i++) {
            cout << patients[i] << endl;
        }
    }
};

// -------------------- STACK (Treated Patients) --------------------
class TreatedStack {
public:
    int top;
    string treated[MAX];

    TreatedStack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    // Push treated patient
    void push(string name) {
        if (isFull())
            return;

        treated[++top] = name;
    }

    // Search patient in treated stack
    bool searchPatient(string name) {
        for (int i = top; i >= 0; i--) {
            if (treated[i] == name)
                return true;
        }
        return false;
    }

    // Display treated patients
    void display() {
        if (isEmpty()) {
            cout << "\nNo treated patients.\n";
            return;
        }

        cout << "\nTreated Patients (Recent First):\n";
        for (int i = top; i >= 0; i--) {
            cout << treated[i] << endl;
        }
    }
};

// -------------------- MAIN FUNCTION --------------------
int main() {
    PatientQueue queue;
    TreatedStack stack;

    int choice;
    string name, newName;

    do {
        cout << "\n===== HOSPITAL MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Patient";
        cout << "\n2. Treat Patient";
        cout << "\n3. Show Waiting Patients";
        cout << "\n4. Show Treated Patients";
        cout << "\n5. Search Patient";
        cout << "\n6. Update Patient Name";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter patient name: ";
            getline(cin, name);
            queue.addPatient(name);
            break;

        case 2:
            name = queue.treatPatient();
            if (name == "") {
                cout << "\nNo patients to treat.\n";
            } else {
                cout << "\nPatient treated: " << name << endl;
                stack.push(name);
            }
            break;

        case 3:
            queue.display();
            break;

        case 4:
            stack.display();
            break;

        case 5:
            cout << "Enter patient name to search: ";
            getline(cin, name);

            if (queue.searchPatient(name))
                cout << "\nPatient found in waiting list.\n";
            else if (stack.searchPatient(name))
                cout << "\nPatient found in treated records.\n";
            else
                cout << "\nPatient not found.\n";
            break;

        case 6:
            cout << "Enter old patient name: ";
            getline(cin, name);
            cout << "Enter new patient name: ";
            getline(cin, newName);

            if (queue.updatePatient(name, newName))
                cout << "\nPatient name updated successfully.\n";
            else
                cout << "\nPatient not found in waiting list.\n";
            break;

        case 7:
            cout << "\nExiting system...\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
