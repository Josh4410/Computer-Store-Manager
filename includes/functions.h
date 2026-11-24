#ifndef FUNCTIONS_H // if not defined called "include guard" not sure if it's needed but apparently good practice?
#define FUNCTIONS_H //define

#include <string>
#include <vector>
#include <sstream>
#include "classes.h"
using namespace std;

void changeComputer(std::vector<Computer*>& computers);
vector<string> rowsplitting(const string& line);
Computer* addComputer(const vector<string>& items);
void searchBy(const vector<Computer*>& computers);
void alterations(vector<Computer*>& computers);
void deleteCopmuter(vector<Computer*>& computers);
void addComputerByInput(vector<Computer*>& computers);


#endif //end of if, also used in clases.h
