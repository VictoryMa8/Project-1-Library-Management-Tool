#include <iostream>
#include <string>
using namespace std;

// CS 221 Final Project
// Team 2: Rachel, Victor, Anh

// The library will be implemented as a Linked list, with each node be a book
struct Book {

    // content of a book
    string title;
    string author;
    long int isbn;
    int num_copies;
    Book* next;

    Book(string t, string a, long int i) { // Constructor for book, default num_copies is 1
        title = t;
        author = a;
        isbn = i;
        num_copies = 1; 
        next = nullptr;
    }
};

class Library {

    private:
        Book* head;

    public:
        Library() {
            head = nullptr;
        }

        // function for adding
        int addBooks(string t, string a, long int i, int j){
            Book* book = new Book(t, a, i);// create a num book with given information
            book->num_copies = j;
            Book* temp = head;
            if (head == NULL){// if there's nothing in library, set the head as the book
                head = book;
                return 0;
            }
            while (temp->next != nullptr){ // if the library is not empty, find the last book and set the next one be the new book
                if (temp->title == t){
                    temp->num_copies += j;
                    return 0;
                }
                temp = temp->next;
            }
            temp->next = book;
            return 0;
        }

        // function for removing
        void removeBooks(string t, int num){
            Book* temp = head;
            int index = 0;
            while (temp->next != nullptr){ // Find the book from the libary
                if (temp->title == t){ // when the book is found
                    temp->num_copies = temp->num_copies - num;// Decrease num_copies with given number
                    if (temp->num_copies < 1){ // If there's no more copy, delete the node
                        Book* temp2 = temp->next;
                        temp = head;
                        for (int i = 0; i < index; ++i){
                            temp = temp->next;
                        }
                        temp->next = temp2;
                    }
                }
                index = index + 1;
                temp = temp->next;
            }
        }

        // function for searching
        bool searchBook(string title) {
            // initalize temp
            Book* temp;
            Book* prev = NULL;
            temp = head;
            // traverse through the entire library
            while (temp != nullptr) {
                // if the title does not match, go to the next
                if (temp->title != title) {
                    prev = temp;
                    temp = temp->next;
                }
                // if title matches, display amount of copies and author
                else {
                    cout << "Book found with " << temp->num_copies << " copies and it was wrote by " << temp->author << endl; 
                    return true;
                }
            }
            // cout if book not found in library
            cout << "Book not found" << endl;
            return false;
        }

        // function for sorting displaying -> use bubble sort to sort from most available to least available 
        // might need to do sth to not make 2 different function for 2 ways of sorting
        void sortAvailable() {
            // we compare two nodes by the 
            if ((head != NULL) && (head->next != NULL)) {
                bool done = false;
                bool hasSwap; // check if in a loop there is a swap
                // when you swap 2 nodes, you need to consider the before and the node after these 2 nodes (4 nodes) 
                // for case of smaller than 4 nodes, you can use 2 dummy at the beginning and the end of the linked list
                Book* dummy_begin = new Book("temp", "temp", -1);
                Book* dummy_end = new Book("temp", "temp", -1);
                // make dummy_begin and dummy_end the beginning and end of the linked list 
                dummy_begin->next = head;
                head = dummy_begin;
                // get the end node
                Book* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = dummy_end;
                // note: there must be no element with value = -1
                while (!done) {
                    hasSwap = false;
                    // now we have a linked list of length n + 2 (n >= 2), 
                    // so we can swap the middle node in all cases without having to think about if there is node before or after
                    Book* curr = head;
                    // we start at new head
                    // the compare head->next and head->next->next
                    while (curr->next->next->next != NULL) {
                        Book* temp1 = curr->next;
                        Book* temp2 = curr->next->next;
                        Book* temp3 = curr->next->next->next;
                        if (temp1->num_copies <= temp2->num_copies) {
                            curr->next = temp2;
                            temp2->next = temp1;
                            temp1->next = temp3;
                            hasSwap = true;
                        }
                        curr = curr->next;
                    }
                    if (!hasSwap) {
                        done = true;
                    }
                }
                // remove the two dummy node;
                head = head->next;
                temp = head;
                while (temp->next->isbn != -1) {
                    temp = temp->next;
                }
                temp->next = NULL;
                // remove dynamic memory after used
                delete dummy_begin;
                delete dummy_end;
            }
        }

        void sortAlphabetically() {
            // instead of comparing two nodes by values, we will use (string1).compare(string2) function to check
            // if > 0 then string1 > string2 (string1 is before string2 alphabetically) and vice versa
            if ((head != NULL) && (head->next != NULL)) {
                bool done = false;
                bool hasSwap; // check if in a loop there is a swap
                // when you swap 2 nodes, you need to consider the before and the node after these 2 nodes (4 nodes) 
                // for case of smaller than 4 nodes, you can use 2 dummy at the beginning and the end of the linked list
                Book* dummy_begin = new Book("temp", "temp", -1);
                Book* dummy_end = new Book("temp", "temp", -1);
                // make dummy_begin and dummy_end the beginning and end of the linked list 
                dummy_begin->next = head;
                head = dummy_begin;
                // get the end node
                Book* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = dummy_end;
                // note: there must be no element with value = -1
                while (!done) {
                    hasSwap = false;
                    // now we have a linked list of length n + 2 (n >= 2), 
                    // so we can swap the middle node in all cases without having to think about if there is node before or after
                    Book* curr = head;
                    // we start at new head
                    // the compare head->next and head->next->next
                    while (curr->next->next->next != NULL) {
                        Book* temp1 = curr->next;
                        Book* temp2 = curr->next->next;
                        Book* temp3 = curr->next->next->next;
                        if ((temp1->title).compare(temp2->title) >= 0) {
                            curr->next = temp2;
                            temp2->next = temp1;
                            temp1->next = temp3;
                            hasSwap = true;
                        }
                        curr = curr->next;
                    }
                    if (!hasSwap) {
                        done = true;
                    }
                }
                // remove the two dummy node;
                head = head->next;
                temp = head;
                while (temp->next->isbn != -1) {
                    temp = temp->next;
                }
                temp->next = NULL;
                // remove dynamic memory after used
                delete dummy_begin;
                delete dummy_end;
            }

        }

        void displayAvailable() {
            sortAvailable();
            Book* temp = head;
            cout << "All available books in descending order of availability" << endl;
            cout << "Title" << " " << "Author" << " " << "ISBN" << " " << "Number of copies" << endl;
            while (temp != NULL) {
                cout << temp->title << " " << temp->author << " " << temp->isbn << " " << temp->num_copies << endl;
                temp = temp->next;
            }
            cout << endl;
        }

        void displayAlphabetically() {
            sortAlphabetically();
            Book* temp = head;
            cout << "All available books in alphabetically ascending order of title" << endl;
            cout << "Title" << " " << "Author" << " " << "ISBN" << " " << "Number of copies" << endl;
            while (temp != NULL) {
                cout << temp->title << " " << temp->author << " " << temp->isbn << " " << temp->num_copies << endl;
                temp = temp->next;
            }
            cout << endl;
        }

        bool interface(){ // menu, lots of if else statement
            int opition = 0;
            cout << "Welcome to Bookmanage system" << endl;
            cout << "Enter 1 for Add a book" << endl;
            cout << "Enter 2 for Remove a book" << endl;
            cout << "Enter 3 for Search a book" << endl;
            cout << "Enter 4 for Display books in sorted order" << endl;
            cout << "Enter 0 to stop" << endl;
            cin >> opition;
            if (opition == 1){
                string t;
                string a;
                long int i;
                int num;
                cout << "Enter the title, author, ISBN, number of books you want to add in order" << endl;
                cin >> t;
                cin >> a;
                cin >> i;
                cin >> num;
                addBooks(t, a, i, num);
            } else if (opition == 2){
                cout << "Enter the title, number of books you want to remove in order" << endl;
                string t;
                int num;
                cin >> t;
                cin >> num;
                removeBooks(t, num);
            } else if (opition == 3){
                string t;
                cout << "Enter the title of the book you want to search" << endl;
                cin >> t;
                searchBook(t);
            } else if (opition == 4){
                cout << "Would you like to Display by Available or Alphabetically?" << endl;
                cout << "Enter 1 for Avalable, 2 for Alphabetically" << endl;
                cin >> opition;
                if (opition == 1){
                    displayAvailable();
                } else if(opition == 2){
                    displayAlphabetically();
                } else{
                    cout << "Invalid input!" << endl;
                }
            } else if (opition ==0){
                return false;
            } else{
                cout << "Invalid input!" << endl;
            }
            return true;
        }
};

int main() {
    Library test_lib;
    bool a = true;
    while (a){ // when the user enter 0 to stop the function, a will be false, then the recursion is over
        a = test_lib.interface();
    }
    return 0;
}