/**
 * This is a password entry program
 * Asks for user's password
 * Asks to be re-entered
 * Finishes by "2FA"
 * Max attempts allowed for each segment
 * @author Jackson Virtue
 */
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main(){
//declaring variables
    string password;
    string passwordUser;
    string compAnimal;
    string userAnimal;
    int maxVal = 10;
    int minVal = 1; //shh i know
    
//"Random" generation of an integer for later use to produce an animal
    srand (time(0));
    int randomValue = minVal + (rand() % (maxVal - minVal + 1));
//declaring max attempts allowed(able to be tweaked)
    int maxAttemptsP = 5;
    int maxAttemptsA = 3;
//prompts user to set password
    cout << "Set Your Password: "; 
    cin >> passwordUser;
//debugging values
    //cout << "[2FA Key Sent]: " << randomValue << endl;
    //cout << "Max Attempts Password: " << maxAttemptsP << endl;
    //cout << "Max Attempts Animal: " << maxAttemptsA << endl;
//generating "random" animal based off previous integer
    const string animals[] = {"Cat", "Dog", "Rabbit", "Mouse", "Horse", "Cow", "Sheep", "Pig", "Owl", "Chicken"};
    compAnimal = animals[randomValue - 1]; // i know i know, this was my first "real" program ;)
//first gate, generic password checker, with max attempts
    while(password != passwordUser && maxAttemptsP != 0){
        cout << "Enter Your Password: ";
        cin >> password;
//if entity fails to enter correct password (attempts allowed - 1) = new max attempts        
        if(password != passwordUser){
            maxAttemptsP--;
            cout << "Authentication Failed. Attempts remaining: " << maxAttemptsP << endl;
//if access granted, next gate prompts user with an animal which is their their personal key animal        
        } else {
            while (userAnimal != compAnimal && maxAttemptsA != 0)
            {
                cout << "Your animal is: " << compAnimal << endl;
                cout << "Animal above?" << endl;
                cout << "Enter: ";
                cin >> userAnimal;
//same idea before with max attempts
                if(userAnimal != compAnimal){
                    maxAttemptsA--;
                    cout << "Authentication Failed. Attempts remaining: " << maxAttemptsA << endl;
//if all granted, we gain access to super secret info
                } else {
                    cout << "Super Secret Info";
                }
            
            } 
            }
        
        }
//should not normally return 0, unless critical error in system
        return 0;
}
