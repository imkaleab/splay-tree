//Name: Kaleab Alemu
//CSCE 3110.003/006
//Date: Oct 30 2020
#include <iostream>
#include <string.h>
#include "bstSplay.h"

using namespace std;
//Method to display menu and input choice
int menu(string make) 
{
    int x;
    cout << "+------------------------------------------+ \n";
    cout << "Enter option choice 1 - 4: \n(1) insert " << make <<" into tree\n";
    cout << "(2) remove " << make <<" from tree\n(3) print tree traversals\n";
    cout << "(4) exit program\n+------------------------------------------+\n> ";
    cin >> x;
    return x;
}


int main()
{
    string x,make;
    
    cout << "What splay tree data type (int, float, char)? ";
    cin >> x;

    if (strcmp(x.c_str(),"float")==0 || strcmp(x.c_str(),"int")==0 || strcmp(x.c_str(),"char")==0) //check if data is valid
    {
        int type = strcmp(x.c_str(),"float")==0? 2 : strcmp(x.c_str(),"char")==0? 3 : 1; //extract type, int = 1, float = 2, and char = 3
        make = strcmp(x.c_str(),"float")==0? "floating-point number" : strcmp(x.c_str(),"char")==0? "character" : "integer";
        switch (type) //call apporopriate functions according to choice
        {
            case 1 :{
                BinarySearchTree <int> bst;
                int choice;
                do {
                    choice = menu(make);
                    switch(choice){
                    case 1: {
                        int x;
                        cout << "Enter " << make << " key to insert: ";
                        cin >> x;
                        bst.insert(x);
                        cout << "Insert (" << x <<") complete\n";
                        break;
                    }
                    case 2: {
                        int x;
                        cout << "Enter " << make << " key to remove: ";
                        cin >> x;
                        bst.remove(x);
                        cout << "Remove (" << x <<") complete\n";
                        break;
                    }
                    case 3: {
                        bst.printTree();
                        cout << "Print complete\n";
                        break;
                    }
                    case(4): {
                        cout << "Terminating...\n";
                        exit(0);
                    }
                    default: {
                        cout << "Invalid choice. Try again.\n";
                        break;
                    }
                    }
                }while (choice!=4);
                break;
                }
            case 2 :{
                BinarySearchTree <float> bst;
                int choice;
                do {
                    choice = menu(make);
                    switch(choice){
                    case 1:{
                        float x;
                        cout << "Enter " << make << " key to insert: ";
                        cin >> x;
                        bst.insert(x);
                        cout << "Insert (" << x <<") complete\n";
                        break;
                        }
                    case 2:{
                        float x;
                        cout << "Enter " << make << " key to remove: ";
                        cin >> x;
                        bst.remove(x);
                        cout << "Remove (" << x <<") complete\n";
                        break;
                        }
                    case 3:{
                        bst.printTree();
                        cout << "Print complete\n";
                        break;
                        }
                    case 4:{
                        cout << "Terminating...\n";
                        exit(0);
                        }
                    default: {
                        cout << "Invalid choice. Try again.\n";
                        break;
                        }
                    }
                }while (choice!=4);
                break;
                }
            case 3:{
                BinarySearchTree <char> bst;
                int choice;
                do {
                    choice = menu(make);
                    switch(choice){
                    case 1:{
                        char x;
                        cout << "Enter " << make << " key to insert: ";
                        cin >> x;
                        bst.insert(x);
                        cout << "Insert (" << x <<") complete\n";
                        break;
                        }
                    case 2:{
                        char x;
                        cout << "Enter " << make << " key to remove: ";
                        cin >> x;
                        bst.remove(x);
                        cout << "Remove (" << x <<") complete\n";
                        break;
                        }
                    case 3:{
                        bst.printTree();
                        cout << "Print complete\n";
                        break;
                        }
                    case 4:{
                        cout << "Terminating...\n";
                        exit(0);
                        }
                    default:{ 
                        cout << "Invalid choice. Try again.\n";
                        break;
                        }
                    }
                }while (choice!=4);
                break;  
                }  
        }
    }
    else //unknown data type
    {
        cout << "Unknown data type ("<< x <<"). Terminating...\n";
    }
   

    return 0;
}
