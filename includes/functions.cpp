#include "functions.h"
#include <fstream>
#include <iostream>

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
    cout << endl <<"Enter the number of your search choice: " << endl;
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
    cout << "0. Skip " << endl; //any entry other than 1,2,3 will skip
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

    //recursion (search again)
    if (userChoice == "0"){ //base case
        cout << "Exiting Program, goodbye :)" << endl;
        return;
    }else if(userChoice == "1" || userChoice == "2" || userChoice == "3"){
        //Prompt user to make more changes, even if the initial change was successful.
        cout << "would you like to make more changes? 1=Yes, 0=No " << endl;
        cout << "Choice:  ";
        getline(cin, userChoice);

        if(userChoice == "1"){
        alterations(computers);
        //return; //was getting recursive stacking bug
        }
    }
    cout << "Would you like to export the updated list to 'computer_updated.txt'? 1=Yes, 0=No" << endl;
    cout << "Choice: ";
    getline(cin, userChoice);

    if (userChoice == "1") {
        ofstream outFile("computer_updated.txt");
        if (outFile.is_open()) {
            for (const auto& comp : computers) {
                outFile << comp->exportComputers() << endl; // Assumes Computer class has a toString() method
            }
            outFile.close();
            cout << "Exported successfully to 'computer_updated.txt'" << endl;
        } else {
            cout << "Error opening file for writing." << endl;
        }
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
    cout << "Enter ID:  ";
    getline(cin, id);
    cout << "Enter Manufacturer:  ";
    getline(cin, manufacturer);
    cout << "Enter CPU:  ";
    getline(cin, processor);
    cout << "Enter Price:  $";
    getline(cin, entered_price);

    //try creating new objects
    try{
        if(cat == "1"){
            //prompting for subclass var
            cout << "Enter Ram:  (GB)";
            getline(cin, entered_ram);
            cout << "Enter Storage Size:  (GB)";
            getline(cin, entered_ssd);

            items.push_back("Desktop PC"); //avoids user error
            items.push_back(type);
            items.push_back(id);
            items.push_back(manufacturer);
            items.push_back(processor);
            items.push_back(entered_ram);
            items.push_back(entered_ssd);
            items.push_back(entered_price);

            //create new Desktop PC
            addComputer(items);

        } else if(cat == "2"){
            //prompting for subclass var
            cout << "Enter Ram:  (GB)";
            getline(cin, entered_ram);
            cout << "Enter Storage Size:  (GB)";
            getline(cin, entered_ssd);
            cout << "Enter Screen Size:  (Inches)";
            getline(cin, entered_screenSize);
            
            items.push_back("Laptop"); //avoids user error
            items.push_back(type);
            items.push_back(id);
            items.push_back(manufacturer);
            items.push_back(processor);
            items.push_back(entered_ram);
            items.push_back(entered_ssd);
            items.push_back(entered_screenSize);
            items.push_back(entered_price);
            //create new Laptop
            addComputer(items);

        } else if(cat == "3"){
            //prompting for subclass var
            cout << "Enter Screen Size:  (Inches)";
            getline(cin, entered_screenSize);

            items.push_back("Tablet"); //avoids user error
            items.push_back(type);
            items.push_back(id);
            items.push_back(manufacturer);
            items.push_back(processor);
            items.push_back(entered_screenSize);
            items.push_back(entered_price);
            //create new Tablet
            addComputer(items);

        } else{
            items[5] = entered_price;
            addComputer(items); 
        }


    } catch (const exception& e) {
        cout << "error type: " << e.what();
    }
}
    
void changeComputer(vector<Computer*>& computers) {
    string userInput;
    int i;

    cout << "Enter ITEM: [number]" << endl;
    cout << "Choice:  ";
    getline(cin, userInput);

    try {
        i = stoi(userInput);
        if (i < 0 || i >= static_cast<int>(computers.size())) { // check for invalid index
            cout << "Index outside vector size" << endl;
            return;
        }

        Computer* comp = computers[i];

        cout << endl << "Item to Update: " << endl;
        cout << "ITEM: " << i << endl;
        comp->displayinfo();

        // Base fields update all
        cout << "Enter new Category (current: " << comp->getCategory() << ") or press Enter to keep: ";
        string input;
        getline(cin, input);
        if (!input.empty()) comp->setCategory(input);

        cout << "Enter new Type (current: " << comp->getType() << ") or press Enter to keep: ";
        getline(cin, input);
        if (!input.empty()) comp->setType(input);

        cout << "ID Locked (current: " << comp->getID() << ")" << endl;

        cout << "Enter new Manufacturer (current: " << comp->getManufacturer() << ") or press Enter to keep: ";
        getline(cin, input);
        if (!input.empty()) comp->setManufacturer(input);

        cout << "Enter new Processor (current: " << comp->getProcessor() << ") or press Enter to keep: ";
        getline(cin, input);
        if (!input.empty()) comp->setProcessor(input);

        cout << "Enter new Price (current: $" << comp->getPrice() << ") or press Enter to keep: ";
        getline(cin, input);
        if (!input.empty()) {
            try {
                int newPrice = stoi(input);
                comp->setPrice(newPrice);
            } catch (...) {
                cout << "Invalid price entered, skipping price update." << endl;
            }
        }
        //derived classses 
        if (Desktop* desktop = dynamic_cast<Desktop*>(comp)) {
            cout << "Enter new RAM (GB) (current: " << desktop->getRam() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    int newRam = stoi(input);
                    desktop->setRam(newRam);
                } catch (...) {
                    cout << "Invalid RAM value, skipping update." << endl;
                }
            }

            cout << "Enter new SSD size (GB) (current: " << desktop->getSsd() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    int newSsd = stoi(input);
                    desktop->setSsd(newSsd);
                } catch (...) {
                    cout << "Invalid SSD value, skipping update." << endl;
                }
            }

        } else if (Laptop* laptop = dynamic_cast<Laptop*>(comp)) {
            cout << "Enter new RAM (GB) (current: " << laptop->getRam() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    int newRam = stoi(input);
                    laptop->setRam(newRam);
                } catch (...) {
                    cout << "Invalid RAM value, skipping update." << endl;
                }
            }

            cout << "Enter new SSD size (GB) (current: " << laptop->getSsd() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    int newSsd = stoi(input);
                    laptop->setSsd(newSsd);
                } catch (...) {
                    cout << "Invalid SSD value, skipping update." << endl;
                }
            }

            cout << "Enter new Screen size (inches) (current: " << laptop->getScreen() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    float newScreen = stof(input);
                    laptop->setScreen(newScreen);
                } catch (...) {
                    cout << "Invalid screen size, skipping update." << endl;
                }
            }

        } else if (Tablet* tablet = dynamic_cast<Tablet*>(comp)) {
            cout << "Enter new Screen size (inches) (current: " << tablet->getScreen() << ") or press Enter to keep: ";
            getline(cin, input);
            if (!input.empty()) {
                try {
                    float newScreen = stof(input);
                    tablet->setScreen(newScreen);
                } catch (...) {
                    cout << "Invalid screen size, skipping update." << endl;
                }
            }
        }

        cout << "Computer updated successfully!" << endl;

    } catch (const exception& e) {
        cout << "Invalid input, update cancelled." << endl;
    }
}

