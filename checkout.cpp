// HoungHuy Hourt (Kai)
// Section #3

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

// You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {
    int id;
    string title;
    string authur;
    string catego;
    Book * bookptr = new Book(id,title, authur, catego);
    ifstream infile;
    infile.open("books.txt");

    while (infile >> id) {
        getline(infile, title);
        getline(infile, authur);
        getline(infile, catego);
        myBooks.push_back(bookptr);
    }
    infile.close();
    return ;
};

int readPersons(vector<Person *> & myCardholders) {
    int cardid;
    bool act;
    string firstn;
    string lastn;

    ifstream infile;
    infile.open("persons.txt");
    while(infile >> cardid >> act >> firstn >> lastn){
        myCardholders.push_back(new Person(cardid, act, firstn, lastn));
    }
    infile.close();
    int num =0;
    for (int i = 0; i < myCardholders.size(); i++){
        if (num < myCardholders.at(i)->getId()){
            num = myCardholders.at(i)->getId();
        }
    }

    return num + 1;
};

Person * searchPerson(vector<Person *> & myCardholders, int id){
    for (int i=0; i<myCardholders.size(); i++){
        if (id == myCardholders.at(i)->getId()){
            return myCardholders.at(i);
        }
    }
    return nullptr;
}

Book * searchBook(vector<Book *> &myBooks, int id) {
    for(int i=0; i<myBooks.size(); i++){
        if (id == myBooks.at(i)->getId())
            return myBooks.at(i); 
    }
    return nullptr;
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    int rbook;
    int card;
    Book * bptr;
    Person * pptr;
    
    ifstream infile;
    infile.open("RENTAL.txt");
    while(infile >> rbook >> card){
        bptr = searchBook(myBooks,rbook);
        pptr = searchPerson(myCardholders, card);
        bptr->setPersonPtr(pptr);
       // myBooks.push_back(renbookptr);   // search book ***
       // myCardholders.push_back(renpersonptr); search car ***
       // set personpter to the card id/name ***
    }
    return;
}

void openCard(vector<Person *> & myCardholders, int num) {
    string firstname = "";
    string lastname = "";
    string fullname = "";
    bool found = false;
    Person* ptr;

    cout << "Please enter the first name: ";
    cin >> firstname;
    cout << "Please enter the last name: ";
    cin >> lastname;
    fullname = firstname + " " + lastname;
    //check if fullname is equal to any existing name if no, create new one
    for( int i = 0; i < myCardholders.size(); i++){
        if(fullname == myCardholders.at(i)->fullName()){
            myCardholders.at(i)->setActive(1);
            found = true;
        }  
    }
    if (!found){
        int active=1;
        myCardholders.push_back(new Person(num, active, firstname, lastname));
        ofstream outfile;
        outfile.open("persons.txt");
        while (outfile.eof()) {
            outfile << num << " " << active  << " " << firstname << " " << lastname << endl;
        }
        outfile.close();
        ptr = searchPerson(myCardholders, num); // does this work
        cout << "Card ID " << ptr->getId() << " Active" << endl;
        cout << "CardHolder: " << ptr->getLastName() << " " <<ptr->getLastName();
    }
    return; // void funct. 
}



void deletePerson(vector<Person *> & myCardHolders, vector<Book *> & myBooks){
    string deact;
    string y;
    int id;
    Person* pptr;

    cout << "\nPlease enter the card ID: ";
    cin >> id;
    pptr = searchPerson(myCardHolders, id);
    if (pptr == nullptr){
        cout << "\nCard ID not found"; 
        return ;
    }
    else if (pptr->isActive() == 0){
        cout << "\nCardholders: " << pptr->fullName(); 
        cout << "\nCard ID is already inactive";
        return; 
    }
    else {
        cout << "\nAre you sure you want to deactivate card (y/n)? ";
        cin >> deact;
        if(deact == y ){
            for (int i = 0; i < myBooks.size(); i++){
                if(myBooks.at(i)->getPersonPtr() == pptr){
                    cout << "\nThere is book that haven't return";
                    return ; 
                }
            }
            pptr->setActive(0);
            cout << "\nCard ID Deactivated";
            return ;
        }
        else {
            return ;
        }
    }
}

void checkout(vector<Person *> & myCardHolders, vector<Book *> & myBooks){
    int cardid, bookid;
    string cardname, title; 
    Person* cptr;
    Book* bptr;

    cout << "Please enter the card ID: ";
    cin >> cardid;
    cptr = searchPerson(myCardHolders,cardid);
    if (cptr == nullptr){
        cout << "Card ID not found" << endl;
        return ;
    }
    cout << "\nCardholder: " << cptr->fullName();
    
    cout << "\nPlease Enter Book ID: ";
    cin >> bookid;
    bptr = searchBook(myBooks, bookid);
    if (bptr == nullptr){
        cout << "Book ID not found" << endl;
        return;
    }
    if (bptr->getPersonPtr() != nullptr){
        cout << "Book already checked out" << endl;
        return;
    }
    cout << "\nTitle: ";
    cin >> title;
    bptr->setPersonPtr(cptr); 
    cout << "Rental Completed" << endl;
    return ;
}

void bookreturn(vector<Book *> & myBooks) {
    int id; 
    string title;
    Book * bptr;

    cout << "Please enter the book ID to return: ";
    cin >> id;
    bptr = searchBook(myBooks, id);
    if (bptr == nullptr){
        cout << "Books ID not found" << endl;
        return ;
    }
    cout << "\nTitle: ";
    cin >> title;
    bptr->setPersonPtr(nullptr);
    cout << "\nReturn Completed";
}

void search(vector<Book *> & myBooks){
    int id; 
    Book * bptr; 

    cout << "Book ID: ";
    cin >> id;
    bptr = searchBook(myBooks, id);
    if (bptr == nullptr || bptr->getPersonPtr() != nullptr){
        cout << "\nNo avaliable books";
        return;
    }
    cout << "\nTitle: " << bptr->getTitle();
    cout << "\nAuthor: " << bptr->getAuthor();
    cout << "\nCategory: " << bptr->getCategory();
    return;
}

void searchrental(vector<Book *> & myBooks){
    for (int i = 0; i< myBooks.size(); i++){
        if (myBooks.at(i)->getPersonPtr() != nullptr){
            cout << "\nBook ID: " << myBooks.at(i)->getId();
            cout << "\nTitle: " << myBooks.at(i)->getTitle();
            cout << "\nAuthor: " << myBooks.at(i)->getAuthor();
            cout << "\nCategory: " << myBooks.at(i)->getCategory();
            cout << endl;
        }
    }
    // need to implement the no outstanding 
    return;
}   

void viewcard(vector<Person *> & myCardHolders, vector<Book *> & myBooks){
    int cid;
    bool active = 1;
    Person* pptr;
    Book * bptr;
    bool rentbook = false;

    cout << "\nPlease Enter the card ID: " ;
    cin >> cid;
    pptr = searchPerson(myCardHolders, cid);
    if(pptr == nullptr){
        cout << "\nCard ID not found" ;
    }
    if(pptr->isActive() == active){
       for (int i= 0; i<myBooks.size(); i++){
           if(myBooks.at(i)->getPersonPtr() == pptr){
               cout << "\nBook ID: " << myBooks.at(i)->getId();
               cout << "\nBook title: " << myBooks.at(i)->getTitle();
               cout << "\nAuthor: " << myBooks.at(i)->getAuthor();
               rentbook = true;
           }
       }
       if(!rentbook){
           cout << "\nNo Books Currently checked out";
           return ;
       }
    }
    else{
        cout << "\nCard ID is inactive";
        return ;
    }

    return ;
}

int main()
{
    int nextnum;
    vector<Book *> books;
    vector<Person *> cardholders;

    nextnum =readPersons(cardholders);
    readBooks(books);
    readRentals(books,cardholders);


    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.

        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                checkout(cardholders, books);
                break;

            case 2:
                // Book return
                bookreturn(books);
                break;

            case 3:
                // View all available books
                search(books);
                break;

            case 4:
                // View all outstanding rentals
                searchrental(books);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                viewcard(cardholders,books);
                break;

            case 6:
                // Open new library card
                openCard(cardholders,nextnum);
                break;

            case 7:
                // Close library card
                deletePerson(cardholders, books);
                break;
                
            case 8:
                // Must update records in files here before exiting the program
                for (int i=0; i<books.size(); i++){
                    delete books.at(i);
                    books.at(i) = nullptr;
                }
                for (int i=0; i<cardholders.size(); i++){
                    delete cardholders.at(i);
                    cardholders.at(i) = nullptr;
                }
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}


