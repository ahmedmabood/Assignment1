#include<iostream>
#include<string>
#include <cstdlib>  
#include <ctime>    
#include<vector>

using namespace std;
// Node class to store chunks of 64-bit integer
class Node
{
public:
    long long int val;
    Node *next;

    Node( long long int val)
    {
        this->val = val;
        this->next = NULL;
    }
};

class Linked // this will represent whole 1024-bit-integer
{
public:
    Node *head;
    Linked()
    {
        head = NULL;
    }
    void insert_64_bit_integer( long long int val) // inserting the chunk of 64 bit integer in linked list
    {
        Node *new_node = new Node(val);
        if(head==NULL){
            head=new_node;
        }
        else{
        Node* temp = head;
        while (temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new_node;}
        
    }

    long long int random_16_digits() {  // it generates random 15 digits which is 64 bit integer
    long long int number = 0;
    for (int i = 0; i < 16; i++) {
        number = number * 10 + (rand() % 10);
    }
    return number;
    }

    void print(){  // it prints the whole 1024 bit integer
        Node* temp = head;
        while (temp!=NULL)
        {
            cout<<temp->val;
            temp=temp->next;
        }
        
    }

    int is_prime(int num){ // checking the primality of number
      Node* temp=head;
      int remainder=0;
      while(temp!=NULL){
      string combine=to_string(remainder)+to_string(temp->val);  // combining remainder of one node value with next node vaue
      long long int number=stoll(combine); // convert string back to integer datat type
      remainder=number%num;  // generating remainder by taking modulus of single node value with smaller prime number
      temp=temp->next;
      }
          return remainder; 
    }
    ~Linked(){ // free the memory space
        Node *current = head;
        while (current != NULL)
        {
            Node *nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = NULL;
    }
};

int main(){
    srand(static_cast<unsigned int>(time(0)));
    Linked l1;
    int total_digits=309;
    int number_of_chunks=total_digits/16;

    // inserting random chunks of 64-bit integer in linked list and as a whole represents 1024-bit integer
    for(int i=0;i<number_of_chunks;i++){  
        long long int random_16_digits = l1.random_16_digits();  // it will produce 304 digit number
        l1.insert_64_bit_integer(random_16_digits);
    }

    // to insert last 5 digits to make it 309 digit number
        int last_five_digits =  (rand() % 100000);
        l1.insert_64_bit_integer(last_five_digits);

     
    cout<<"A 1024-bit number represented as: ";
    l1.print();
    cout<<endl<<endl;

     vector<int> smallerPrimes={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 
     109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 
     269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 
     439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499};  // vector of smaller primes between 1 and 500

     int size=smallerPrimes.size();
     cout<<"The smaller primes are between 1 and 500 are :"<<endl;
      for (int i = 0; i < size; i++)  // displaying smaller primes
    {
       cout<<smallerPrimes[i]<<" ";
    }

    bool isPrime=true; // flag variable
    
    for (int i = 0; i < size; i++)
    {
       int remainder= l1.is_prime(smallerPrimes[i]); // The isPrime returns the final remainder after checking divisiblity by smaller primes one by one
       if (remainder==0)    // condition of composite number if remainder is 0 it means it is not prime number                          
       {
        isPrime=false;
        break;
       }
       
    }
    
    if(isPrime){  // printing based on flag variable isPrime
        cout<<"\n\nOUTPUT: TRUE\nIt is probably a prime number";
    }
    else{
        cout<<"\n\nOUTPUT: FALSE\nIt is probably not a prime";
    }

    return 0;
}