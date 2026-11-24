#include "classes.h"

//constructor
Computer::Computer(string cat, string typ, string i, string manu, string cpu, int p)
    : category(cat), type(typ), id(i), manufacturer(manu), processor(cpu), price(p) {}

void Computer::displayinfo() const {
    cout << "Category: " << category << endl;
    cout << "Type: " << type << endl;
    cout << "ID: " << id << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "CPU: " << processor << endl;
    cout << "Price: $" << price << endl;
}
//getters
string Computer::getCategory() const { 
    return category; 
}
string Computer::getType() const { 
    return type; 
}
string Computer::getID() const { 
    return id; 
}
string Computer::getProcessor() const { 
    return processor; 
}
string Computer::getManufacturer() const { 
    return manufacturer; 
}
int Computer::getPrice() const { 
    return price; 
}

Computer::~Computer() {
    //empty destructor
}

//setters
void Computer::setCategory(const string& cat)  {
    category = cat;
}
void Computer::setType(const string& typ)  {
    type = typ;
}
void Computer::setID(const string& i)  {
    id = i;
}
void Computer::setManufacturer(const string& manu)  {
    manufacturer = manu;
}
void Computer::setProcessor(const string& cpu)  {
    processor = cpu;
}
void Computer::setPrice(int p)  {
    price = p;
}
string Computer::exportComputers() const {
    return category+"," +type+","+id+","+manufacturer+","+processor+","+to_string(price);
}

//derived classes
Desktop::Desktop(string cat, string typ, string i, string manu, string cpu, int r, int s, int p)
    : Computer(cat, typ, i, manu, cpu, p), ram(r), ssd(s) {}

void Desktop::displayinfo() const {
    Computer::displayinfo();
    cout << "RAM: " << ram << "GB" << endl;
    cout << "SSD: " << ssd << "GB" << endl;
}
//getters
int Desktop::getRam() const {
    return ram;
}
int Desktop::getSsd() const {
    return ssd;
}
//setters
void Desktop::setRam(int r) {
     ram = r;
}
void Desktop::setSsd(int s) {
    ssd = s;
}
string Desktop::exportComputers() const {
        return Computer::exportComputers()+","+to_string(ram)+","+to_string(ssd);
}


Laptop::Laptop(string cat, string typ, string i, string manu, string cpu, int r, int s, float scr, int p)
    : Computer(cat, typ, i, manu, cpu, p), ram(r), ssd(s), screen(scr) {}

void Laptop::displayinfo() const {
    Computer::displayinfo();
    cout << "RAM: " << ram << "GB" << endl;
    cout << "SSD: " << ssd << "GB" << endl;
    cout << "Screen Size: " << screen << " inches" << endl;
}
//getters
int Laptop::getRam() const {
    return ram;
}
int Laptop::getSsd() const {
    return ssd;
}
float Laptop::getScreen() const {
    return screen;
}
//setters
void Laptop::setRam(int r) {
     ram = r;
}
void Laptop::setSsd(int s) {
    ssd = s;
}
void Laptop::setScreen(float scr) {
    screen = scr;
}
string Laptop::exportComputers() const {
        return Computer::exportComputers()+","+to_string(ram)+","+to_string(ssd);
}


Tablet::Tablet(string cat, string typ, string i, string manu, string cpu, float scr, int p)
    : Computer(cat, typ, i, manu, cpu, p), screen(scr) {}

void Tablet::displayinfo() const {
    Computer::displayinfo();
    cout << "Screen Size: " << screen << "inches" << endl;
}
//getter
float Tablet::getScreen() const {
    return screen;
}
//setter
void Tablet::setScreen(float scr) {
    screen = scr;
}
string Tablet::exportComputers() const {
        return Computer::exportComputers()+","+to_string(screen);
}