#include "includes/functions.h"
#include <fstream>

// Smith, Josh, 24023949, Assignment 3, 159.234, S1, 2025

// Compiler Terminal input: g++ main.cpp includes/functions.cpp includes/classes.cpp -Iincludes -o main.exe
// Execute  Terminal input: ./main.exe
//                          (vs code)
/* CHECK LIST:
3. Example outputs and functions narrations

    1) Create a document that includes screenshots of your system-generated outputs based on the
    completed tasks of your computer store management system; and

    2) Add narratives on the document to explain the realized functions whenever necessary (please
    refer to the sample output at the end of the Assignment 2 specifications; you can use its format to
    present your work). */

/* 4. Design and Implementation Guidelines
Note: You will receive credit for correctness, completeness, least code duplication, and clear on-screen outputs.
we will grade your program using the following OOP and general software implementation
guidelines:
    1) Class design and implementation
        YES a. Appropriate Classes and associations --------- using Polymorphism this time
        N/A b. Data fields - proper use of modifiers --------- Maybe??
        YES c. Internal data not accessed by external classes --------- getters/setters
        N/A d. Appropriate methods and constructors --------- Unsure
    2) Memory management
        YES  a. Delete objects or arrays created with ‘new’ --------- NEED TO DELETE in main()
        YES b. Virtual destructors 
    3) Inheritance design and implementation
        N/A a. Reasonable class hierarchies ---------  Unsure
        YES b. Proper data fields separation in base and derived classes
        YES c. Proper methods separation/overloading/overriding in base and derived classes
        YES d. Proper use of base and derived class constructors
    4) Polymorphism and implementation
        YES a. Write generic code that targets the base class whenever possible
        YES b. Appropriate use of overriding in derived classes to realize polymorphism
    5) Information store and implementation
        YES a. Use Vector/Map and/or other C++ STL containers to store information. ---------  NEED TO CHANGE array to vector for computer objects
        YES  b. Use Iterator to enumerate elements in container class --------- change computers array to vector to use iterator, I think this is the container class?
    6) Exception handling
        NO  a. Throw an exception object when an application error occurs (e.g., when an invalid piece of data is entered)
        NO  b. Use “try/catch/finally” or “try/catch” block to handle the exception --------- haven't used for searchBy() but have for update/delete/add. Have implemented 3 try/catches but not for every case where they could've been used
*/

// MAIN -----------------------------------------------------------------------------------------------

int main(){
    cout << "program loaded" << endl;
    ifstream file("computers.txt"); //input file
    string row; //string of each row of file

    vector<Computer*> computers; // Array of pointers to computer objects (otherwise children of computers would be lost (PC/Laptop/Tablet))
    //int counter = 0; don't need for vector

    //Loop through every line until counter less than or equal to 40, create a new Computer obj every iteration
    while(getline(file,row)){
        vector<string> items = rowsplitting(row);
        Computer* newComputer = addComputer(items);
        if (newComputer != nullptr) {
            computers.push_back(newComputer); //if newComputer is not null, add newComputer to the end of computers vector<>
        }
    }
    
    //display every item (Task 2.2)
    int index =0;
    for(auto* comp : computers){
        cout << endl << "ITEM: " << index++ << endl;
        comp->displayinfo(); //calling class method
    }

    // Prompting Staff (Task 2.3a to 2.3d)
    // Search with the Array of Computer objects and it's length (counter)
    searchBy(computers); 


    // Staff Alterations (Task 2.4a to 2.4c + 2.5)
    alterations(computers); // this function just handles user inputs and calls delete/add/update functions recursively

    //Final loop to delete computers
    for(auto* comp : computers){
        delete comp;
    }

}