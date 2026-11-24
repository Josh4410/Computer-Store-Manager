#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Smith, Josh, 240------, Assignment 3, 159.234, S1, 2025
// Compiler Terminal input: 

//
//

/* CHECK LIST:
3. Example outputs and functions narrations

    1) Create a document that includes screenshots of your system-generated outputs based on the
    completed tasks of your computer store management system; and

    2) Add narratives on the document to explain the realized functions whenever necessary (please
    refer to the sample output at the end of the Assignment 2 specifications; you can use its format to
    present your work). 

*/


/* 
4. Design and Implementation Guidelines

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




// CLASSES -----------------------------------------------------------------------------------------------

class Computer {
    //protected not private so Desktop/Laptop/Tablet can use it
    protected:
        string category;
        string type;
        string id;
        string manufacturer;
        string processor;
        int price;
    public:
        Computer(string cat, string typ, string i, string manu, string cpu, int p) : category(cat), type(typ), id(i), manufacturer(manu), processor(cpu), price(p) {}
        virtual void displayinfo() const { //virtual function so can be overriden by derived class varients
            cout << "Category: " << category << endl;
            cout << "Type: " << type << endl;
            cout << "ID: " << id<< endl;
            cout << "Manufacturer: "<< manufacturer << endl;
            cout << "CPU: " << processor <<endl;
            cout << "Price: $" << price<<endl;

        } 
        //Getters
        string getCategory() const {
            return category;
        }
        string getType() const {
            return type;
        }
        string getID() const {
            return id;
        }
        string getManufacturer() const {
            return manufacturer;
        }
        int getPrice() const {
            return price;
        }
        //Virtual Destructor! since using polymorphism to call the right destructor depending on derived class 
        virtual ~Computer() {}

};


//derived Classes
class Desktop : public Computer {
    private:
        int ram;
        int ssd;

    public:
        Desktop(string cat, string typ, string i, string manu, string cpu, int r, int s, int p) : Computer(cat,typ,i,manu,cpu,p), ram(r), ssd(s) {}

        void displayinfo() const override { //derived classes override parent computer classes displayinfo() function
            Computer::displayinfo();
            cout << "RAM: " << ram << "GB" << endl;
            cout << "SSD: " << ssd << "GB" << endl;
        }
};

class Laptop : public Computer {
    private:
        int ram;
        int ssd;
        float screen;

    public:
        Laptop(string cat, string typ, string i, string manu, string cpu, int r, int s, float scr, int p) : Computer(cat,typ,i,manu,cpu,p), ram(r), ssd(s), screen(scr) {}

        void displayinfo() const override {
            Computer::displayinfo();
            cout << "RAM: " << ram << "GB" << endl;
            cout << "SSD: " << ssd << "GB" << endl;
            cout << "Screen Size: " << screen << " inches" << endl;
        }
};

class Tablet : public Computer {
    private:
        float screen;

    public:
        Tablet(string cat, string typ, string i, string manu, string cpu, float scr, int p) : Computer(cat,typ,i,manu,cpu,p), screen(scr) {}
        
        void displayinfo() const override {
            Computer::displayinfo();
            cout << "Screen Size: " << screen << "inches" << endl;
        }
};


// FUNCTIONS -----------------------------------------------------------------------------------------------

//Converts input row (line) into a vector of strings
vector<string> rowsplitting(const string& line) {
    vector<string> parts; //Since I don't know how many parts in each line I use a vector instead of array
    string part;
    stringstream strngstrm(line); //string to an equivalent of cin

    // Loop through the row (line) and break it into individual parts in a vector list 
    while (getline(strngstrm, part, ',')) {
        if (!part.empty() && part.front() == ' ') {
            part.erase(0, 1);
        }
        parts.push_back(part); //equivalent to parts = parts + part; (just for vector)
    }
    return parts; // returns the vector storing every "part" of the line/row rowsplitting() was used on.
}

//Function takes vector of items in, returns appropriate Computer child object
Computer* addComputer(const vector<string>& items) {
    //will be in every *correctly formatted* row
    string category = items[0];
    string type = items[1];
    string id = items[2];
    string manufacturer = items[3];
    string processor = items[4];

    if(items[0] == "Desktop PC"){
        //will be in desktop rows
        int ram = stoi(items[5]);
        int ssd = stoi(items[6]);
        int itemprice = stoi(items[7]);
        //create new obj
        return new Desktop(category, type, id, manufacturer, processor, ram, ssd, itemprice);

    }
    else if(items[0] == "Laptop"){
        //will be in laptop rows
        int ram = stoi(items[5]);
        int ssd = stoi(items[6]);
        float screen = stof(items[7]);
        int itemprice = stoi(items[8]);
        //create new obj
        return new Laptop(category, type, id, manufacturer, processor, ram, ssd, screen, itemprice);

    }
    else if(items[0] == "Tablet"){
        float screen = stof(items[5]);
        int itemprice = stoi(items[6]);
        //create new obj
        return new Tablet(category, type, id, manufacturer, processor, screen, itemprice);


    } else {
        //category undefined, custom error msg to create
        cout << "ERROR " << endl;
        return nullptr; // return type is Computer* pointer, just returning null
    }
}

// Recursive Search Function
void searchBy(const vector<Computer*>& computers){ //search doesn't change vector points passed by reference so can be const
    int check = 0; // Counts the amount of items found, used as a check if no items are found

    //user entered fields
    string searchChoice;
    string searchA;
    string searchB;
    int minPrice =0;
    int maxPrice =0;

    //User decides what search method
    cout << "Enter the number of your search choice: " << endl;
    cout << "1. Search by ID: " << endl;
    cout << "2. Search by Category: " << endl;
    cout << "3. Search by Category & Type: " << endl;
    cout << "4. Search by Price Range: " << endl;
    cout << "Choice:  ";
    getline(cin, searchChoice);

    //User enters search fields based on search method
    if(searchChoice == "1"){
        cout << "Search items with ID:  ";
        getline(cin, searchA);
    } else if(searchChoice == "2"){
        cout << "Search items with Category:  ";
        getline(cin, searchA);
    } else if(searchChoice == "3"){
        cout << "Search items with Category:  ";
        getline(cin, searchA);
        cout << "Search items with Type:  ";
        getline(cin, searchB);
    } else if(searchChoice == "4"){
        cout << "Search items with Price Min:  $";
        getline(cin, searchA);
        cout << "Search items with Price Max:  $";
        getline(cin, searchB);

        minPrice = stoi(searchA);
        maxPrice = stoi(searchB);
    } 

    int i = 0;
    //Loop through Array, displayinfo() every item == to search field
    for(auto* comp : computers) {
        if(searchChoice == "1" && comp->getID() == searchA){
                cout << endl << "ITEM: " << i << endl;
                comp->displayinfo();
                check++;
        } else if(searchChoice == "2" && comp->getCategory() == searchA){  
                cout << endl << "ITEM: " << i << endl;
                comp->displayinfo();
                check++;
        } else if(searchChoice=="3" && comp->getCategory()==searchA && comp->getType()==searchB){  
                cout << endl << "ITEM: " << i << endl;
                comp->displayinfo();
                check++;
        } else if(searchChoice == "4" && comp->getPrice() >= minPrice && comp->getPrice() <= maxPrice){
                cout << endl << "ITEM: " << i << endl;
                comp->displayinfo();
                check++;
        }
        i++; 
    }

    // Display no items found OR number of items found.
    if(check==0){
        cout << endl << "No computers found with search fields " << searchA << ", " << searchB << endl;
    } else {
        cout << endl << "Number of items found: " << check  << endl;
    }

    //Prompt user to search again, even if the Search was successful.
    cout << "would you like to search again? 1=Yes, 0=No " << endl;
    cout << "Choice:  ";
    getline(cin, searchA);

    //recursion (search again)
    if(searchA == "1"){
        searchBy(computers);
        return; //was getting recursive stacking bug
    }
}

//Prompting for changes
void alterations(vector<Computer*>& computers){
    string userChoice; // stores cin of user

    //User decides what alterations to make
    cout << endl << "What would you like to change: (enter number)" << endl;
    cout << "1. Delete " << endl;
    cout << "2. Add " << endl;
    cout << "3. Update " << endl;
    cout << "Choice:  ";
    getline(cin, userChoice);

    //Delete a computer from search list 
    if(userChoice == "1"){
        deleteCopmuter(computers);
    }

    //Add new computer
    if(userChoice == "2"){
        addComputerByInput(computers);
    }

    //Update a computer objects details
    if(userChoice == "3"){
        changeComputer(computers);
    }

    //Prompt user to make more changes, even if the initial change was successful.
    cout << "would you like to make more changes? 1=Yes, 0=No " << endl;
    cout << "Choice:  ";
    getline(cin, userChoice);

    //recursion (search again)
    if (userChoice == "0"){ //base case
        return;
    }else if(userChoice == "1"){
        alterations(computers);
        //return; //was getting recursive stacking bug
    }
}

void deleteCopmuter(vector<Computer*>& computers){
    string userInput;
    int i;

    cout << "Enter ITEM: [number]" << endl;
    cout << "Choice:  ";
    getline(cin, userInput);

    try{
        i = stoi(userInput); // string to int in try/catch block incase of error
        //check index is valid -- TO DO
        if (i < 0 || i >=computers.size()){ //check for invalid index
            cout << "Index outside vector size";
            return;
        }

        //Display selected Computer
        cout << endl << "Are you sure you want to delete this computer: " << endl;
        cout << "ITEM: " << i << endl;
        computers[i]->displayinfo();

        cout << endl << "1=Yes, 0=No " <<endl;
        cout << "Choice:  ";
        getline(cin, userInput);

        if(userInput == "1"){
            delete computers[i];
            computers.erase(computers.begin() + i);
            cout << "Computer Deleted" << endl;
        } else {
            cout << "Deletion Canned" << endl;
        }

    } catch (const exception& e){
        cout << "ERROR -> In Delete Computer Function" << endl;
        cout << "Enter a number" << endl;
    }


}

//sorts inputs into vector of items and sends it to addComputer() Function
void addComputerByInput(vector<Computer*>& computers){
    vector<string> items;
    string cat;
    // Base class var
    string type;
    string id;
    string manufacturer;
    string processor;
    string entered_price;

    string entered_ram;
    string entered_ssd;
    string entered_screenSize;

    //Prompting for Category
    cout << "Select Category of New Computer: (enter number)" << endl;
    cout << "1. Desktop PC" << endl;
    cout << "2. Laptop" << endl;
    cout << "3. Tablet" << endl;
    cout << "4. Generic Computer / Other" << endl;
    cout << "Choice:  ";
    getline(cin, cat);

    //prompting for base class var
    cout << "Enter Type:  ";
    getline(cin, type);
    items[1] = type;

    cout << "Enter ID:  ";
    getline(cin, id);
    items[2] = id; 

    cout << "Enter Manufacturer:  ";
    getline(cin, manufacturer);
    items[3] = manufacturer; 


    cout << "Enter CPU:  ";
    getline(cin, processor);
    items[4] = processor; 

    cout << "Enter Price:  $";
    getline(cin, entered_price);

    //try creating new objects
    try{
        if(cat == "1"){
            items[0] = "Desktop PC"; //avoids user error
            items[7] = entered_price; 

            //prompting for subclass var
            cout << "Enter Ram:  (GB)";
            getline(cin, entered_ram);
            items[5] = entered_ram;

            cout << "Enter Storage Size:  (GB)";
            getline(cin, entered_ssd);
            items[6] = entered_ssd;

            //create new Desktop PC
            addComputer(items);

        } else if(cat == "2"){
            items[0] = "Laptop";
            items[8] = entered_price; 

            //prompting for subclass var
            cout << "Enter Ram:  (GB)";
            getline(cin, entered_ram);
            items[5] = entered_ram; 

            cout << "Enter Storage Size:  (GB)";
            getline(cin, entered_ssd);
            items[6] = entered_ssd;

            cout << "Enter Screen Size:  (Inches)";
            getline(cin, entered_screenSize);
            items[7] = entered_screenSize;

            //create new Laptop
            addComputer(items);

        } else if(cat == "3"){
            items[0] = "Tablet";
            items[6] = entered_price; 

            //prompting for subclass var
            cout << "Enter Screen Size:  (Inches)";
            getline(cin, entered_screenSize);
            items[5] = entered_screenSize;

            //create new Tablet
            addComputer(items);

        } else{
            items[5] = entered_price;
            addComputer(items); 
        }


    } catch (const exception& e) {

    }



}
    
void changeComputer(vector<Computer*>& computers){
    string userInput;
    int i;

    cout << "Enter ITEM: [number]" << endl;
    cout << "Choice:  ";
    getline(cin, userInput);

    try{
        i = stoi(userInput);
        if (i < 0 || i >=computers.size()){ //check for invalid index
            cout << "Index outside vector size";
            return;
        }

        cout << endl << "Item you would like to Update: " << endl;
        cout << "ITEM: " << i << endl;
        computers[i]->displayinfo();


    } catch (const exception& e){

    }
}


// MAIN -----------------------------------------------------------------------------------------------

int main(){
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