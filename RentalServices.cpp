/**
 * This is a menu for a simple rentals service system
 * Incomplete. Need to figure out how to search a vector... |Just did! (see SelectGuest())|
 * I learned how to use private and public on a class. Along with getters/setters
 * Split functions and kept main clean. (maybe split too much? too little? idk actually)
 * Learned how to save information for next boot up (see initialize())
 * Used references "&", I needed to research these, I knew I needed them, didnt know how to use them.
 * Now I do.
 * dont look too hard at CustomerTotalCost(), yes it does blow up...
 * i didnt really want to comment so i hope it is relatively readable </3
 * camelCase
 * @author Jackson Virtue
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class RentalService {
    private:
        int guestAge, guestWeight;
        float servicesRendered;
        string guestLastName, guestFirstName;

    public:
        RentalService(int age, int weight, string Lname, string Fname, float service) {
            guestLastName = Lname;
            guestFirstName = Fname;
            guestAge = age;
            guestWeight = weight;
            servicesRendered = service;
        }
        //getters
        string getFirstName() const {return guestFirstName;}
        string getLastName() const {return guestLastName;}
        int getGuestAge() const {return guestAge;}
        int getGuestWeight() const {return guestWeight;}
        float getServicesRendered() const {return servicesRendered;}

        //setters
        void setServicesRendered(float service) {
            servicesRendered = service;
        }
}; 

vector<RentalService> Initialize() { //Learned how to import info using a standardized input.
    vector<RentalService> guestInfo;
    string line, Fname, Lname;
    int age, weight;
    float service;
    ifstream guestListComp("GuestListComp.txt");

    while(getline(guestListComp, line)) {
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
            guestInfo.emplace_back(age, weight, Lname, Fname, service);
        }
    }
    return guestInfo; //returns the vector
}

void GuestList(const vector<RentalService>& GuestInfo) { //simple guest display, uses the nice looking GuestList.txt instead of ugly GuestListComp.txt
    for(int i = 0; i < GuestInfo.size(); i++) {
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
    
    cout << "Guest First Name: ";
    cin >> Fname;
    cout << "Guest Last Name: ";
    cin >> Lname;
    cout << "Guest Age: ";
    cin >> age;
    cout << "Guest Weight: ";
    cin >> weight;

    return RentalService(age, weight, Lname, Fname, service); //returns full RentalService object
}

vector<int> SearchGuestInfo(const vector<RentalService>& GuestInfo) { //speant the most time on this and pricing...the logic was a little annoying I knew 99% of the syntax.
    string userSearchTarget;
    int userNumberSearchTarget;
    vector<int> guestIndex;

    cout << "First OR Last name (type !skip to search by age or weight): ";
    cin >> userSearchTarget;

    if (userSearchTarget == "!skip") {
        cout << "Age OR Weight: ";
        cin >> userNumberSearchTarget;

        for (int i = 0; i < GuestInfo.size(); i++) {
            if (userNumberSearchTarget == GuestInfo[i].getGuestAge() ||
                userNumberSearchTarget == GuestInfo[i].getGuestWeight()) {
                if (GuestInfo[i].getServicesRendered() > 0) {
                    cout << "OUTSTANDING PAYMENT: " << GuestInfo[i].getServicesRendered() << "\n";
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
            if (userSearchTarget == GuestInfo[i].getFirstName() ||
                userSearchTarget == GuestInfo[i].getLastName()) {
                cout << GuestInfo[i].getFirstName() << " ";
                cout << GuestInfo[i].getLastName() << " Age: ";
                cout << GuestInfo[i].getGuestAge()<< " Weight: ";
                cout << GuestInfo[i].getGuestWeight() << "\n";

                guestIndex.push_back(i);
            }
        }
    }
    return guestIndex;
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

        cout << "[" << i << "] " << GuestInfo[idx].getFirstName();
        cout << " " << GuestInfo[idx].getLastName();
        cout << " Age: " << GuestInfo[idx].getGuestAge();
        cout << " Weight: " << GuestInfo[idx].getGuestWeight() << "\n";
    }

    cout << "Select Guest Number: " << "\n";
    cin >> selectedGuest; 

    return guestIndex[selectedGuest];
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
            GuestInfo[guestIndex].setServicesRendered(finalCost);
            cout << "Paymet due: " << finalCost << "\n";
            break;
        }
        
        subTotal += rentalPrices[stoi(userAnswer)];
    }
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
    }
    guestList.close();
    guestListComp.close();
}

int main() {
    vector<RentalService> GuestInfo = Initialize();
    cout << "Initializing..." << "\n";

    while(true) {
        string userAnswer;

        cout << "Guest-List(G) || New-Guest(N) || Pricing(P) || Search-Guest(SG) || Save/Quit(S)" << "\n";
        cin >> userAnswer;
        if(userAnswer == "G" || userAnswer == "g") {
            GuestList(GuestInfo);
        }
        else if(userAnswer == "N" || userAnswer == "n") {
            GuestInfo.push_back(GetGuestInfo());
        }
        else if(userAnswer == "P" || userAnswer == "p") {
            CustomerTotalCost(GuestInfo);
        }
        else if(userAnswer == "SG" || userAnswer == "sg" || userAnswer == "Sg" || userAnswer == "sG") {
            SearchGuestInfo(GuestInfo);
        }
        else if(userAnswer == "S" || userAnswer == "s") { //use this function to cleanly save, helps prevents unwanted data loss. 
            SaveGuestInfo(GuestInfo);
            break;
        }
        else if(userAnswer == "T" || userAnswer == "t") {
            //test functions before implementing
            break;
        }
    }
}
