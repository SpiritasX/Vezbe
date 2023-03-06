/* 
Napisati program koji omogućava evidentiranje fakultetskih učionica.   

Za svaku učionicu potrebno je evidentirati naziv učionice, kvadraturu i sve računare koji se nalaze u učionici. 
Za svaki računar evidentiraju se podaci o hard disku i procesoru.

U okviru main funkcije, definisati jednu učionicu koja sadrži dva računara.
Zatim je potrebno na konzolu ispisati hard disk i procesor svakog računara u učionici.
*/

#include <iostream>
#include <vector>
#include <cstring>

class HDD
{
private:
    double size;
    std::string brand;
    std::string model;
public:
    HDD() {}

    HDD(double size, std::string brand, std::string model)
    {
        this->size = size;
        this->brand = brand;
        this->model = model;
    }

    double getSize() { return this->size; }
    std::string getBrand() { return this->brand; }
    std::string getModel() { return this->model; }

    std::string toString()
    {
        std::string str = std::string("\nHDD") +
                          "\nSize  : " + std::to_string(this->size) + "TB" +
                          "\nBrand : " + this->brand +
                          "\nModel : " + this->model +
                          "\n";
        return str;
    }
};

class Processor
{
private:
    double speed;
    std::string brand;
    std::string model;
public:
    Processor() {}

    Processor(double speed, std::string brand, std::string model) 
    {
        this->speed = speed;
        this->brand = brand;
        this->model = model;
    }
    
    double getSpeed() { return this->speed; }
    std::string getBrand() { return this->brand; }
    std::string getModel() { return this->model; }

    std::string toString()
    {
        std::string str = std::string("\nProcessor") +
                          "\nSpeed : " + std::to_string(this->speed) + "GHz" +
                          "\nBrand : " + this->brand +
                          "\nModel : " + this->model +
                          "\n";
        return str;
    }
};

class Computer
{
private:
    Processor processor;
    HDD hdd;
public:
    Computer(const Processor& processor, const HDD& hdd)
    {
        this->processor = processor;
        this->hdd = hdd;
    }

    Computer(int speed, int size, std::string procBrand, std::string procModel, std::string hddBrand, std::string hddModel) : hdd(size, hddBrand, hddModel), processor(speed, procBrand, procModel)
    {

    }

    Processor getProcessor() { return this->processor; }
    HDD getHdd() { return this->hdd; }

    std::string toString()
    {
        std::string str = std::string("\nComputer") + this->hdd.toString() + this->processor.toString() + "\n";
        return str;
    }
};

class Classroom
{
private:
    std::string name;
    double sq_meters;
    std::vector<Computer> computers;
public:
    Classroom(std::string name, double sq_meters)
    {
        this->name = name;
        this->sq_meters = sq_meters;
    }

    void addComputer(const Computer& computer)
    {
        computers.push_back(computer);
    }

    std::string toString()
    {
        std::string str = std::string("Classroom ") + this->name + "[" + std::to_string(this->sq_meters) + " m^2]\n";

        for (Computer c : computers)
            str += c.toString();
        
        return str;
    }
};

int main()
{
    Classroom classroom("A1", 120.5);

    Computer c1(3.6, 1, "Intel", "i5", "Toshiba", "T1000");
    Computer c2(4.0, 3, "AMD", "Ryzen 3", "WD", "Red Plus");

    classroom.addComputer(c1);
    classroom.addComputer(c2);

    std::cout << classroom.toString() << std::endl;

    return 0;
}
