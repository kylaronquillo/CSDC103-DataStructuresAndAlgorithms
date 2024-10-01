#include <iostream>

using namespace std;

const int sizeOfArray = 10; 
int stack[sizeOfArray], topOfArray = -1;

bool isEmpty() {
    return topOfArray == -1; 
}

int peek() {
    if (!isEmpty()) {
        return stack[topOfArray];
    } else {
        exit(1);
    }
}

void push(int value) {
    if (topOfArray >= (sizeOfArray - 1))
        cout << "Stack Overflow" << endl;
    else {
        topOfArray++;
        stack[topOfArray] = value;
        cout << "Push: " << stack[topOfArray] << endl;
    }
}

void pop() {
    if (topOfArray <= -1)
        cout << "Stack Underflow" << endl;
    else {
        cout << "Pop: " << stack[topOfArray] << endl;
        topOfArray--;
    }
}


bool isFull() {
    return topOfArray == sizeOfArray - 1; 
}


int top(){
    peek();
    return stack[topOfArray];
}


int main() {
    int value;

    //cout << peek()
    push(5); peek();
    push(6); peek(); 
    push(7); peek(); 
    push(8); peek(); 
    push(10); peek();
    cout << "The Top of the Array: " << top() << endl;
    pop(); peek();
    pop(); peek();
    if (isEmpty()){
        cout << "Array is Empty\n";
    }
    else{
        cout << "Array is NOT Empty.\n";
    }
    push(90); peek(); 
    push(81); peek(); 
    push(110); peek();
    pop(); peek();
    cout << "The Top of the Array: " << top() << endl;
    if(isFull()){
        cout << "Array is Full\n";
    }
    else{
        cout << "Array is NOT Full.\n";

    }

    return 0;
}
