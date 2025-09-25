#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Node {
    string url;
    Node* prev;
    Node* next;
    Node(string u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;
    Node* current;
public:
    BrowserHistory() : head(nullptr), tail(nullptr), current(nullptr) {}

    void visit(string url) {
        Node* newNode = new Node(url);
        if (!head) {
            head = tail = current = newNode;
        } else {
            current->next = newNode;
            newNode->prev = current;
            tail = current = newNode;
        }
        cout << "Visited: " << url << "\n";
    }

    void deleteWebsite(string url) {
        Node* temp = head;
        while (temp) {
            if (temp->url == url) {
                if (temp == head) head = head->next;
                if (temp == tail) tail = tail->prev;
                if (temp->prev) temp->prev->next = temp->next;
                if (temp->next) temp->next->prev = temp->prev;
                if (current == temp) current = temp->prev ? temp->prev : temp->next;
                delete temp;
                cout << "Deleted: " << url << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Website not found!\n";
    }

    void display() {
        if (!head) {
            cout << "History is empty!\n";
            return;
        }
        cout << "\n--- Browser History ---\n";
        Node* temp = head;
        while (temp) {
            if (temp == current)
                cout << "> " << temp->url << " (current)\n";
            else
                cout << temp->url << "\n";
            temp = temp->next;
        }
    }

    void back() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Moved back to: " << current->url << "\n";
        } else {
            cout << "No previous history!\n";
        }
    }

    void forward() {
        if (current && current->next) {
            current = current->next;
            cout << "Moved forward to: " << current->url << "\n";
        } else {
            cout << "No forward history!\n";
        }
    }

    void clearHistory() {
        Node* temp = head;
        while (temp) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = current = nullptr;
        cout << "History cleared!\n";
    }

    void search(string url) {
        Node* temp = head;
        while (temp) {
            if (temp->url == url) {
                cout << "Found website: " << url << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Website not found!\n";
    }

    void sortHistory() {
        if (!head || !head->next) return;
        bool swapped;
        do {
            swapped = false;
            Node* temp = head;
            while (temp->next) {
                if (temp->url > temp->next->url) {
                    swap(temp->url, temp->next->url);
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
        cout << "History sorted alphabetically!\n";
    }
};

int main() {
    BrowserHistory bh;
    int choice;
    string url;

    do {
        cout << "\n========= Browser History Manager =========\n";
        cout << "1. Visit Website\n2. Delete Website\n3. Display History\n4. Back\n5. Forward\n6. Clear History\n7. Search Website\n8. Sort History\n9. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1-9.\n";
            continue;
        }

        cin.ignore(); // Clear newline character from input buffer

        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                getline(cin, url);
                bh.visit(url);
                break;
            case 2:
                cout << "Enter URL to delete: ";
                getline(cin, url);
                bh.deleteWebsite(url);
                break;
            case 3:
                bh.display();
                break;
            case 4:
                bh.back();
                break;
            case 5:
                bh.forward();
                break;
            case 6:
                bh.clearHistory();
                break;
            case 7:
                cout << "Enter URL to search: ";
                getline(cin, url);
                bh.search(url);
                break;
            case 8:
                bh.sortHistory();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please enter 1-9.\n";
        }
    } while (choice != 9);

    return 0;
}
