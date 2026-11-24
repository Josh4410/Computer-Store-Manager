#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
using namespace std;

class Computer {
protected:
    string category, type, id, manufacturer, processor;
    int price;

public:
    Computer(string cat, string typ, string i, string manu, string cpu, int p);
    virtual void displayinfo() const;
    //getters
    string getCategory() const;
    string getType() const;
    string getID() const;
    string getManufacturer() const;
    string getProcessor() const;
    int getPrice() const;

    //setters
    void setCategory(const string& cat);
    void setType(const string& typ);
    void setID(const string& i);
    void setManufacturer(const string& manu);
    void setProcessor(const string& cpu);
    void setPrice(int p);
    
    //virtual to string, each computer type has different .txt outputs
    virtual string exportComputers() const;

    //Virtual Destructor! since using polymorphism to call the right destructor depending on derived class 
    virtual ~Computer();
};

//dervided classes
class Desktop : public Computer {
private:
    int ram, ssd;
public:
    Desktop(string cat, string typ, string i, string manu, string cpu, int r, int s, int p);
    void displayinfo() const override;
    //geters
    int getRam() const;
    int getSsd() const;

    //setters
    void setRam(int r);
    void setSsd(int s);

    string exportComputers() const override;
};

class Laptop : public Computer {
private:
    int ram, ssd;
    float screen;
public:
    Laptop(string cat, string typ, string i, string manu, string cpu, int r, int s, float scr, int p);
    void displayinfo() const override;
    //getters
    int getRam() const;
    int getSsd() const;
    float getScreen() const;

    //setters
    void setRam(int r);
    void setSsd(int s);
    void setScreen(float scr);

    string exportComputers() const override;
};

class Tablet : public Computer {
private:
    float screen;
public:
    Tablet(string cat, string typ, string i, string manu, string cpu, float scr, int p);
    void displayinfo() const override;
    //getters
    float getScreen() const;
    //setters
    void setScreen(float scr);
    //
    string exportComputers() const override;
};

#endif