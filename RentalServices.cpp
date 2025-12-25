/**
 * This is a menu for a simple rentals service system
 * Incomplete. Need to figure out how to search a vector...
 * I learned how to use private and public on a class. Along with getters.
 * Split functions and kept main clean.
 * Learned how to save information for next boot up (see initialize())
 * Used some references, I needed to research these, I knew I needed them, didnt know how to use them.
 * Now I do.
 * dont look too hard at CustomerTotalCost()
 * i didnt really want to comment so i hope it is relativly readable </3
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
        string guestLastName, guestFirstName;

    public:
        RentalService(int age, int weight, string Lname, string Fname) {
            guestLastName = Lname;
            guestFirstName = Fname;
            guestAge = age;
            guestWeight = weight;
        }

        string getFirstName() const {return guestFirstName;}
        string getLastName() const {return guestLastName;}
        int getGuestAge() const {return guestAge;}
        int getGuestWeight() const {return guestWeight;}
}; 

vector<RentalService> Initialize() {
    vector<RentalService> guestInfo;
    string line, Fname, Lname;
    int age, weight;
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
            guestInfo.emplace_back(age, weight, Lname, Fname);
        }
    }
    return guestInfo;
}

void GuestList(const vector<RentalService>& GuestInfo) {
    for(int i = 0; i < GuestInfo.size(); i++) {
        cout << GuestInfo[i].getFirstName() << " ";
        cout << GuestInfo[i].getLastName() << " Age: ";
        cout << GuestInfo[i].getGuestAge() << " Weight: ";
        cout << GuestInfo[i].getGuestWeight() << "\n";
    }
}

RentalService GetGuestInfo() {
    int age, weight;
    string Lname, Fname;
    
    cout << "Guest First Name: ";
    cin >> Fname;
    cout << "Guest Last Name: ";
    cin >> Lname;
    cout << "Guest Age: ";
    cin >> age;
    cout << "Guest Weight: ";
    cin >> weight;

    return RentalService(age, weight, Lname, Fname);
}

void CustomerTotalCost() { //Most dangerous function I've wrote so far, and its somehow one of the simplist...
    ifstream rentalsPrices("RentalsPrices.txt");
    string line, userAnswer;
    float subTotal = 0.0;
    float finalCost = 0.0;
    const int rentalPrices[] = {12, 15, 28, 45, 89, 20, 25, 30, 38, 45, 55, 60, 95};
    const double ctSalesTax = .0635;
    
    while(getline(rentalsPrices, line)) {
        cout << line << "\n";
    }

    while(true) {
        cout << "Add Rental (If Finished, Enter NO): ";
        cin >> userAnswer;

        if(userAnswer == "NO" || userAnswer == "no" || userAnswer == "No" || userAnswer == "nO") {
            finalCost = subTotal * (1 + ctSalesTax);
            break;
        }
        
        subTotal += rentalPrices[stoi(userAnswer)];
    }
    cout << finalCost;
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
    }
    guestList.close();
    guestListComp.close();
}

void SearchGuestInfo(const vector<RentalService>& GuestInfo) {
    string userSearch;

    while(true) {
        cout << "Search Guest: ";
        cin >> userSearch;

        
    }

}

int main() { 
    string userAnswer;
    vector<RentalService> GuestInfo = Initialize();

    while(true) {
        cout << "Guest-List(G) || New-Guest(N) || Test(T) || Pricing(P) || Search-Guest(SG) || Save/Quit(S)" << "\n";
        cin >> userAnswer;
        if(userAnswer == "G" || userAnswer == "g") {
            GuestList(GuestInfo);
        }
        else if(userAnswer == "N" || userAnswer == "n") {
            GuestInfo.push_back(GetGuestInfo());
        }
        else if(userAnswer == "P" || userAnswer == "p") {
            CustomerTotalCost();
        }
        else if(userAnswer == "S" || userAnswer == "s") {
            SaveGuestInfo(GuestInfo);
            break;
        }
        else if(userAnswer == "SG" || userAnswer == "sg" || userAnswer == "Sg" || userAnswer == "sG") {
            SearchGuestInfo(GuestInfo);
        }
        else if(userAnswer == "T" || userAnswer == "t") {
            //test functions before implementing
            break;
        }
    }
}
