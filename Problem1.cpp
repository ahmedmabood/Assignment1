#include <iostream>
#include <string>
#include<cstdlib>
#include <ctime>


using namespace std;
// nodes of circular linked list representing each process
class Process {
public:
    string id;
    int execution_time;
    int remaining_time;
    Process* next;

    Process(string id, int time) {
        this->id = id;
        this->execution_time = time;
        this->remaining_time = time;
        next = NULL;
    }
};

class CircularLinkedList {
public:
    Process* tail;

    CircularLinkedList() {
        tail = NULL;
    }
    // inserting each process at end
    void insert(string id, int time) {
        Process* new_process = new Process(id, time);
        if (tail == NULL) {
            tail = new_process;
            tail->next = tail;
        } else {
            new_process->next = tail->next;
            tail->next = new_process;
            tail = new_process;
        }
    }

   void delete_process() {
    Process* current = tail->next;
    Process* prev = tail;

    do {
        if (current->remaining_time <= 0) { // condition to check if cpu procesess has completes its execution time

            // If the CPU process now has only one process, then delete  tail to NULL
                if (tail == tail->next) {
                    delete tail;
                    tail = NULL;
                    return;
                }
            // Remove the current process from the CPU
            prev->next = current->next;

            // If the current node is the tail, update the tail pointer
            if (current == tail) {
                tail = prev;               
            }

            // Delete the current process
            Process* temp = current;
            current = prev->next;
            delete temp;

        } else {
            prev = current;
            current = current->next;
        }
    } while (current != tail->next);
}

    void cycles(int cpu_time) {
        srand(time(0));
        int random_process= rand() % 3 + 1; 
        int cycles = 0;

        do {
            if(random_process==cycles){  // to generate random processes
                insert("p4", 16);
                cout<<"New process  P4  arrives with remaining time 16 "<<endl<<endl;
            }

            Process* current = tail->next;
            cout << "Cycle " << cycles+1 << ": ";

            do {
                current->remaining_time -= cpu_time; // to reduce the remaining time, by the time schedular assigns
                if (current->remaining_time <= 0) {
                    cout << current->id << "(Completes),";
                } else {
                    cout << current->id << "(Remaining: " << current->remaining_time << "),";
                }
                current = current->next;
            } while (current != tail->next);

            cout << endl<<endl;
            cycles++;

            // Call deleteNode() after each cycle to delete process from CPU if it completes execution time
            delete_process();
        } while (tail != NULL);
    }

    void print_cpu_process() { // it prints the initial process
        if (tail == NULL) {
            cout << "No processes" << endl;
            return;
        }

        Process* temp = tail->next;
        cout << "[";
        do {
            cout << "(" << temp->id << "," << temp->execution_time << "),";
            temp = temp->next;
        } while (temp != tail->next);

        cout << "]"<<endl;
    }
};

int main() {
    CircularLinkedList processes;

    processes.insert("p1", 10);
    processes.insert("p2", 5);
    processes.insert("p3", 8);

    cout << "Initial Processes: ";
    processes.print_cpu_process();
    int cpu_time=3;

    cout << endl << "CPU Time per Process per Cycle: "<<cpu_time << endl<<endl;

    processes.cycles(cpu_time);
    cout<<"All processes completes";
    return 0;
}