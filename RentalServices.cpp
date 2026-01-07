/**
 * This is a menu for a simple rentals service system
 * Incomplete. Need to figure out how to search a vector...Just did! (see SelectGuest())
 * I learned how to use private and public on a class. Along with getters/setters
 * Split functions and kept main clean. (maybe split too much? too little? idk actually)
 * Learned how to save information for next boot up (see initialize())
 * Used references "&", I needed to research these, I knew I needed them, didnt know how to use them.
 * Now I do.
 * dont look too hard at CustomerTotalCost(), yes it does blow up...
 * i didnt really want to comment so i hope it is relatively readable </3
 * camelCase / PascalCase
 * last updated: 12/28/25
 * @author Jackson Virtue
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Boots {
    private:
        int bootSize, bootID;
        string skiOrSnowboardID;

    public:
        Boots(int ID, int size, string choice) {
            bootSize = size;
            bootID = ID;
            skiOrSnowboardID = choice;
        }

        int getBootSize() const {return bootSize;}
        int getBootID() const {return bootID;}
        string getSkiOrSnowboard() const {return skiOrSnowboardID;}
};

class Helmets {
    private: 
        char helmetSize;
        int helmetID;

    public:
        Helmets(int ID, char size) {
            helmetSize = size;
            helmetID = ID;
        }

        char getHelmetSize() const {return helmetSize;}
        int getHelmetID() const {return helmetID;}
};

class RentalService {
    private:
        int guestAge, guestWeight;
        float servicesRendered;
        string guestLastName, guestFirstName;
        vector<string> guestHelmetID;
        vector<string> guestBootID;

    public:
        RentalService(int age, int weight, string Lname, string Fname, float service, vector<string> boot, vector<string> helmet) {
            guestLastName = Lname;
            guestFirstName = Fname;
            guestAge = age;
            guestWeight = weight;
            servicesRendered = service;
            guestHelmetID = helmet;
            guestBootID = boot;
        }
        
        //getters
        string getFirstName() const {return guestFirstName;}
        string getLastName() const {return guestLastName;}
        int getGuestAge() const {return guestAge;}
        int getGuestWeight() const {return guestWeight;}
        float getServicesRendered() const {return servicesRendered;}
        vector<string> getGuestHelmet() const {return guestHelmetID;}
        vector<string> getGuestBoots() const {return guestBootID;}

        //setters
        void setServicesRendered(float service) {
            servicesRendered = service;
        }
        void setGuestHelmetID(string helmet) {
            guestHelmetID.push_back(helmet);
        }
        void setBootID(string boot) {
            guestBootID.push_back(boot);
        }
};

/*Boots GuestBootGetter() {
    auto gue;
    string line, choice;
    int size, ID;
    ifstream boots("Boots.txt");

    while(getline(boots, line)) {
        if(line.rfind("SB", 0) == 0) {choice = "SB";}
        else if(line.rfind("S") == 0) {choice = "S";}

        size_t emdashPos = line.find("-");
        if(emdashPos == string::npos) continue;

        int typeLength = (choice == "SB") ? 2 : 1;
        size = stoi(line.substr(typeLength, emdashPos - typeLength));
        ID = stoi(line.substr(emdashPos + 1));
        gue = Boots(size, ID, choice);
    }
    return gue;
}*/

vector<RentalService> Initialize() { //Learned how to import info using a standardized input.
    vector<RentalService> guestInfo;
    string line, Fname, Lname;
    vector<string> boot;
    vector<string> helmet;
    int age, weight;
    float service;
    ifstream guestListComp("GuestListComp.txt");

    while(getline(guestListComp, line)) { //parsing
        if(line.find("Fname: ") != string::npos) {
            Fname = line.substr(line.find(":") + 2);
        }
        if(line.find("Lname: ") != string::npos) {
            Lname = line.substr(line.find(":") + 2);
        }
        if(line.find("age: ") != string::npos) {
            age = stoi(line.substr(line.find(":") + 2));
        }
        if(line.find("weight: ") != string::npos) {
            weight = stoi(line.substr(line.find(":") + 2));
        }
        if(line.find("outstanding payments: ") != string::npos) {
            service = stof(line.substr(line.find(":") + 2));
        }
        if(line.find("guest boot: ") != string::npos) {
            boot.push_back(line.substr(line.find(":") + 2));
        }
        if(line.find("guest helmet: ") != string::npos) {
            helmet.push_back(line.substr(line.find(":") + 2));
            guestInfo.emplace_back(age, weight, Lname, Fname, service, boot, helmet);

            Fname.clear();
            Lname.clear();
            boot.clear();
            helmet.clear();
            age = 0;
            weight = 0;
            service = 0.0f;
        }
    }
    return guestInfo; //returns the vector
}

//these vectors are mostly for inventory purposes, implementing sort by size, ID, etc. in the RentalServices class im just using a string for the item ID.

vector<Helmets> InitializeHelmets() {
    vector<Helmets> helmetVector;
    string line;
    char size;
    int ID;
    ifstream helmets("Helmets.txt");

    while(getline(helmets, line)) {
        if(line.find("S") != string::npos) {
            size = 'S';
        }
        if(line.find("M") != string::npos) {
            size = 'M';
        }
        if(line.find("L") != string::npos) {
            size = 'L';
        }
        if(line.find("-") != string::npos) {
            ID = stoi(line.substr(line.find("-") + 1));
            helmetVector.emplace_back(ID, size);
        }
    }
    return helmetVector;
}

vector<Boots> InitializeBoots() {
    vector<Boots> bootVector;
    int ID, size;
    string line, choice;
    ifstream boots("Boots.txt");

    while(getline(boots, line)) {
        if(line.rfind("SB", 0) == 0) {choice = "SB";} //SB = Snowboard
        else if(line.rfind("S") == 0) {choice = "S";} //S = Ski

        size_t emdashPos = line.find("-");
        if(emdashPos == string::npos) continue;

        int typeLength = (choice == "SB") ? 2 : 1;
        size = stoi(line.substr(typeLength, emdashPos - typeLength));
        ID = stoi(line.substr(emdashPos + 1));
        bootVector.emplace_back(ID, size, choice);
    }
    return bootVector;
}

void GuestList(const vector<RentalService>& GuestInfo) { //simple guest display, uses the nice looking GuestList.txt instead of ugly GuestListComp.txt
    for(int i = 0; i < GuestInfo.size(); i++) {
        if(GuestInfo[i].getServicesRendered() > 0) {
            cout << "OUTSTANDING PAYMENT DUE: " << GuestInfo[i].getServicesRendered() << "     ";
        }
        cout << GuestInfo[i].getFirstName() << " ";
        cout << GuestInfo[i].getLastName() << " Age: ";
        cout << GuestInfo[i].getGuestAge() << " Weight: ";
        cout << GuestInfo[i].getGuestWeight() << "\n";
    }
}

RentalService GetGuestInfo() { //Manually add a guest
    int age, weight;
    float service = 0.0;
    string Lname, Fname;
    vector<string> helmet;
    vector<string> boot;
    
    cout << "Guest First Name: ";
    cin >> Fname;
    cout << "Guest Last Name: ";
    cin >> Lname;
    cout << "Guest Age: ";
    cin >> age;
    cout << "Guest Weight: ";
    cin >> weight;

    return RentalService(age, weight, Lname, Fname, service, helmet, boot); //returns full RentalService object
}

/* vector<string> RentItems(const vector<string>& AvailableItems) {
    string itemID;
    vector<string> itemsOut;

    while(true) {
        cout << "Enter Item ID (enter NO to exit): " << "\n";
        if(itemID == "NO") {
            break;
        }
        cin >> itemID;
        itemsOut.push_back(itemID);
    }
    return itemsOut;
}*/

vector<int> SearchGuestInfo(const vector<RentalService>& GuestInfo) { //speant the most time on this and pricing...the logic was a little annoying I knew 99% of the syntax.
    string userSearchTarget;
    int userNumberSearchTarget;
    vector<int> guestIndex;

    cout << "First OR Last name (type !skip to search by age or weight): "; //going to try and do a general search at some point
    cin >> userSearchTarget;

    if (userSearchTarget == "!skip") {
        cout << "Age OR Weight: ";
        cin >> userNumberSearchTarget;

        for (int i = 0; i < GuestInfo.size(); i++) {
            if (userNumberSearchTarget == GuestInfo[i].getGuestAge() || userNumberSearchTarget == GuestInfo[i].getGuestWeight()) {

                if (GuestInfo[i].getServicesRendered() > 0) {
                    cout << GuestInfo[i].getFirstName() << " " << GuestInfo[i].getLastName() << " ";
                    cout << "OUTSTANDING PAYMENT: $" << GuestInfo[i].getServicesRendered() << "\n";
                }

                cout << GuestInfo[i].getFirstName() << " ";
                cout << GuestInfo[i].getLastName() << " Age: ";
                cout << GuestInfo[i].getGuestAge() << " Weight: ";
                cout << GuestInfo[i].getGuestWeight()<< "\n";

                guestIndex.push_back(i);
            }
        }
    } 
    else {
        for (int i = 0; i < GuestInfo.size(); i++) {
            if (userSearchTarget == GuestInfo[i].getFirstName() || userSearchTarget == GuestInfo[i].getLastName()) {

                if (GuestInfo[i].getServicesRendered() > 0) {
                    cout << GuestInfo[i].getFirstName() << " " << GuestInfo[i].getLastName() << " ";
                    cout << "OUTSTANDING PAYMENT: $" << GuestInfo[i].getServicesRendered() << "\n";
                }
                cout << GuestInfo[i].getFirstName() << " ";
                cout << GuestInfo[i].getLastName() << " Age: ";
                cout << GuestInfo[i].getGuestAge()<< " Weight: ";
                cout << GuestInfo[i].getGuestWeight() << "\n";

                guestIndex.push_back(i);
            }
        }
    }
    return guestIndex; //returns vector of object placements
}

int SelectGuest(vector<RentalService>& GuestInfo) { //I should clean this up, it feels ugly
    string userAnswer;
    vector<int> guestIndex = SearchGuestInfo(GuestInfo);
    int selectedGuest = -1;

    if(guestIndex.empty()) {
        return -1;
    }

    for (int i = 0; i < guestIndex.size(); i++) {
        int idx = guestIndex[i];

        cout << "[Guest Number: " << i << "] " << GuestInfo[idx].getFirstName();
        cout << " " << GuestInfo[idx].getLastName();
        cout << " Age: " << GuestInfo[idx].getGuestAge();
        cout << " Weight: " << GuestInfo[idx].getGuestWeight() << "\n";
    }

    cout << "Select Guest Number: " << "\n";
    cin >> selectedGuest; 

    return guestIndex[selectedGuest];
}

void SaveGuestInfo(const vector<RentalService>& GuestInfo) {
    fstream guestList, guestListComp;
    guestList.open("GuestList.txt");
    guestListComp.open("GuestListComp.txt");
    
    for(int i = 0; i < GuestInfo.size(); i++) {
        guestList << GuestInfo[i].getFirstName() << " ";
        guestList << GuestInfo[i].getLastName() << " Age: ";
        guestList << GuestInfo[i].getGuestAge() << " Weight: ";
        guestList << GuestInfo[i].getGuestWeight() << "\n";
        guestListComp << "Fname: " << GuestInfo[i].getFirstName() << "\n";
        guestListComp << "Lname: " << GuestInfo[i].getLastName() << "\n";
        guestListComp << "age: " << GuestInfo[i].getGuestAge() << "\n";
        guestListComp << "weight: " << GuestInfo[i].getGuestWeight() << "\n";
        guestListComp << "outstanding payments: " << GuestInfo[i].getServicesRendered() << "\n";
        guestListComp << "guest boot: ";
            for(const auto& boot : GuestInfo[i].getGuestBoots()) {
                guestListComp << boot;
                guestListComp << "\n";
            }
        guestListComp << "guest helmet: ";
            for(const auto& helmet : GuestInfo[i].getGuestBoots()) {
                guestListComp << helmet;
                guestListComp << "\n";
            }
        guestListComp << "\n";
    }
    guestList.close();
    guestListComp.close();
}

vector<string> RentOutBoots() {
    vector<string> boot;
    string tempBoot;
    bool finished = false;

    while(!finished) {
        cout << "Enter Boot ID or DNE to finish: ";
        cin >> tempBoot;

        if(tempBoot == "DNE" || tempBoot == "dne") {
            return boot;
        } else {
            boot.push_back(tempBoot);
        }
    }

    return boot;
}

vector<string> RentOutHelmets() {
    vector<string> helmet;
    string tempHelmet;
    bool finished = false;

    while(!finished) {
        cout << "Enter Helmet ID or DNE to finish: ";
        cin >> tempHelmet;

        if(tempHelmet == "DNE" || tempHelmet == "dne") {
            return helmet;
        } else {
            helmet.push_back(tempHelmet);
        }
    }

    return helmet;
}

void CustomerTotalCost(vector<RentalService>& GuestInfo) {
    ifstream rentalsPrices("RentalsPrices.txt");
    string line, userAnswer;
    float subTotal = 0.0;
    float finalCost = 0.0;
    const int rentalPrices[] = {45, 45, 28, 15, 12, 89, 20, 25, 30, 38, 45, 55, 60, 95};
    const double ctSalesTax = .0635;
    
    while(getline(rentalsPrices, line)) {
        cout << line << "\n";
    }
    cout << "----Search Guest----" << "\n";
    int guestIndex = SelectGuest(GuestInfo);
    if(guestIndex == -1) {
        return;
    }

    while(true) {
        cout << "Add item (If Finished, Enter NO): ";
        cin >> userAnswer;

        if(userAnswer == "NO" || userAnswer == "no" || userAnswer == "No" || userAnswer == "nO") {
            finalCost = subTotal + subTotal * ctSalesTax;
            GuestInfo[guestIndex].setServicesRendered(GuestInfo[guestIndex].getServicesRendered() + finalCost);
            //cout << GuestInfo[guestIndex].getServicesRendered(); debugging
            cout << "Paymet due: " << finalCost << "\n";
            SaveGuestInfo(GuestInfo);
            break;
        }
        for(const auto& boot : RentOutBoots()) {
            GuestInfo[guestIndex].setBootID(boot);
        }
        for(const auto& helmet : RentOutHelmets()) {
            GuestInfo[guestIndex].setGuestHelmetID(helmet);
        }
        subTotal += rentalPrices[stoi(userAnswer)];
    }
}

int main() {
    vector<RentalService> GuestInfo = Initialize();
    vector<Helmets> AvailableHelmets = InitializeHelmets();
    vector<Boots> AvailableBoots = InitializeBoots();
    cout << "Initializing..." << "\n";

    while(true) {
        string userAnswer;

        cout << "Guest-List(G) || New-Guest(N) || Rent Out(RO) || Search-Guest(SG) || Save/Quit(S)" << "\n";
        cin >> userAnswer;
        if(userAnswer == "G" || userAnswer == "g") {
            GuestList(GuestInfo); 
        }
        else if(userAnswer == "N" || userAnswer == "n") {
            GuestInfo.push_back(GetGuestInfo());
        }
        else if(userAnswer == "RO" || userAnswer == "ro") {
            CustomerTotalCost(GuestInfo);
        }
        else if(userAnswer == "SG" || userAnswer == "sg" || userAnswer == "Sg" || userAnswer == "sG") {
            SearchGuestInfo(GuestInfo);
        }
        else if(userAnswer == "S" || userAnswer == "s") { //use this function to cleanly save, helps prevents unwanted data loss. 
            SaveGuestInfo(GuestInfo);
            break;
        }
        else if(userAnswer == "Test" || userAnswer == "test") {
            for(int i = 0; i < AvailableHelmets.size(); i++) {
                cout << AvailableHelmets[i].getHelmetSize();
                cout << AvailableHelmets[i].getHelmetID() << "\n";
            }
            for(int i = 0; i < AvailableBoots.size(); i++) {
                cout << AvailableBoots[i].getSkiOrSnowboard();
                cout << AvailableBoots[i].getBootSize();
                cout << AvailableBoots[i].getBootID() << "\n";
            }
            break;
        }
    }
}
