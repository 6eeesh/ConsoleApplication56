#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

class Device {
protected:
    string manufacturer;
    string model;
    string name;
    int capacity;
    int quantity;

public:
    Device(const string& manufacturer, const string& model, const string& name, int capacity, int quantity)
        : manufacturer(manufacturer), model(model), name(name), capacity(capacity), quantity(quantity) {}

    virtual ~Device() = default;

    virtual void print() const {
        cout << "Manufacturer: " << manufacturer << "\n";
        cout << "Model: " << model << "\n";
        cout << "Name: " << name << "\n";
        cout << "Capacity: " << capacity << " GB\n";
        cout << "Quantity: " << quantity << "\n";
    }

    virtual void save(ofstream& outFile) const {
        outFile << manufacturer << " " << model << " " << name << " " << capacity << " " << quantity << "\n";
    }

    virtual void load(ifstream& inFile) {
        inFile >> manufacturer >> model >> name >> capacity >> quantity;
    }
};

class FlashDrive : public Device {
public:
    FlashDrive(const string& manufacturer, const string& model, const string& name, int capacity, int quantity)
        : Device(manufacturer, model, name, capacity, quantity) {}

    void print() const override {
        Device::print();
        cout << "Type: Flash Drive\n";
    }

    void save(ofstream& outFile) const override {
        outFile << "FlashDrive ";
        Device::save(outFile);
    }

    void load(ifstream& inFile) override {
        Device::load(inFile);
    }
};

class HardDrive : public Device {
public:
    HardDrive(const string& manufacturer, const string& model, const string& name, int capacity, int quantity)
        : Device(manufacturer, model, name, capacity, quantity) {}

    void print() const override {
        Device::print();
        cout << "Type: Hard Drive\n";
    }

    void save(ofstream& outFile) const override {
        outFile << "HardDrive ";
        Device::save(outFile);
    }

    void load(ifstream& inFile) override {
        Device::load(inFile);
    }
};

class Phone : public Device {
public:
    Phone(const string& manufacturer, const string& model, const string& name, int capacity, int quantity)
        : Device(manufacturer, model, name, capacity, quantity) {}

    void print() const override {
        Device::print();
        cout << "Type: Phone\n";
    }

    void save(ofstream& outFile) const override {
        outFile << "Phone ";
        Device::save(outFile);
    }

    void load(ifstream& inFile) override {
        Device::load(inFile);
    }
};

int main() {
    vector<unique_ptr<Device>> devices;

    devices.push_back(make_unique<FlashDrive>("Kingston", "DataTraveler", "USB 3.0", 64, 5));
    devices.push_back(make_unique<HardDrive>("Seagate", "Backup Plus", "External HDD", 1000, 2));
    devices.push_back(make_unique<Phone>("Apple", "iPhone 12", "Smartphone", 256, 10));

    for (const auto& device : devices) {
        device->print();
        cout << "\n";
    }

    ofstream outFile("devices.txt");
    if (outFile.is_open()) {
        for (const auto& device : devices) {
            device->save(outFile);
        }
        outFile.close();
        cout << "Devices saved to devices.txt\n";
    }
    else {
        cerr << "Error opening file for writing.\n";
    }

    ifstream inFile("devices.txt");
    if (inFile.is_open()) {
        string type;
        while (inFile >> type) {
            if (type == "FlashDrive") {
                devices.push_back(make_unique<FlashDrive>("", "", "", 0, 0));
            }
            else if (type == "HardDrive") {
                devices.push_back(make_unique<HardDrive>("", "", "", 0, 0));
            }
            else if (type == "Phone") {
                devices.push_back(make_unique<Phone>("", "", "", 0, 0));
            }

            devices.back()->load(inFile);
        }
        inFile.close();

        cout << "\nLoaded Devices:\n";
        for (const auto& device : devices) {
            device->print();
            cout << "\n";
        }
    }
    else {
        cerr << "Error opening file for reading.\n";
    }

    return 0;
}
