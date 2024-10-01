#include <iostream>
#include <list>


using namespace std;


// function to add element in front of list
void insertFront(list <int> &list1, int x){
        list1.push_front(x);
}


// function to add element at the back of the list
void insertBack(list <int> &list1, int x){
        list1.push_back(x);
}


// function to delete element in front of list
void deleteFront(list <int> &list1){
        list1.pop_front();
}


// function to delete element at the back of the list
void deleteBack(list <int> &list1){
        list1.pop_back();
}


// function that displays the list
void displayList(list <int> &list1){
    for ( int n : list1){
        cout << n << " ";
    }
}


int main(){
    int inputFront = 19;
    int inputBack = 20;


    list <int> list1 = {0, 1, 2, 3};


    cout << "Initial List: ";
    displayList(list1);
    cout << endl;


    cout << "List after adding front and back elements: ";
    insertFront(list1, inputFront);
    insertBack(list1, inputBack);
    displayList(list1);
    cout << endl;


    cout << "List after removing front and back elements: ";
    deleteFront(list1);
    deleteBack(list1);
    displayList(list1);
    cout << endl;




    return 0;
}
