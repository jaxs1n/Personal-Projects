/**
 * This is a Course Information storage program
 * First prompts user if they would like to add a class,
 * or access their pre-existing stored classes
 * Utilizes: File IO, OOP, and basic arithmetic operators
 * Ends with calculating total GPA, and regardless of input method
 * stores GPA in user file
 * camelCase
 * @author Jackson Virtue
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std; //yeah yeah i know...

class CourseInformation {
    public:
        string courseName, courseProfessor, courseTA; //declaring public variables, idk how to use private/protected in tandem with public...
        float courseGrade;

    CourseInformation(string name, string professor, string ta, float grade) { //constructor able to be use by input from file or user
        courseGrade = grade; //each segment asks user to input grade, name, professor, and ta. So its easier to have them as a universal temp variable, and just set them equal to the class variable
        courseName = name;
        courseProfessor = professor;
        courseTA = ta;
    }
};

int main() {
    vector<CourseInformation> courseMaterial; //vector for amount of classes user inputs
    fstream Classinfo("Classinfo.txt"); //can put whatever file, cant tell you what formats it accepts, tested on .txt
    string userAnswer; //just for breaking out of loops
    float totalGPA = 0.0; //initializing to prevent garbage
    
    while(true) { //first loop, requests user information
        cout << "Add a class? (y/n): "; //first thing user sees on console.
        cin >> userAnswer;

        if(userAnswer == "N" || userAnswer == "n") { //to end adding classes, jumps to line 61
            break;
        } else {
            string name, professor, ta; //re-declaring those same variables as in the constructor
            float grade;
            
            cin.ignore();
            cout << "Course Name: ";
            getline(cin, name);
            cout << ("Course Professor: ");
            getline(cin, professor);
            cout << ("Course TA: ");
            getline(cin, ta);
            cout << ("Course Grade: ");
            cin >> grade;

            CourseInformation tempCourseMaterial(name, professor, ta, grade); //creates temp object with all temp variables
            courseMaterial.push_back(tempCourseMaterial); //pushes temp object into vector courseMateial for later extraction
        }
    }
    while(true) { //second loop, this time for reading file. File needs to be formatted this way or else improper extraction.
        cout << "Read from file? (y/n): "; 
        cin >> userAnswer;
        
        if(userAnswer == "N" || userAnswer == "n") {
            break;
        } else {
            string name, professor, ta, line; //re-declaring those variables again!
            float grade;

            while(getline(Classinfo, line)) { //loop to read the file

                if(line.find("Course Name: ") != string::npos) {
                    name = line.substr(line.find(":") + 2);
                }
                if(line.find("Course Professor: ") != string::npos) {
                    professor = line.substr(line.find(":") + 2);
                }
                if(line.find("Course TA: ") != string::npos) {
                    ta = line.substr(line.find(":") + 2);
                }
                if(line.find("Course Grade: ") != string::npos) {
                    grade = stof(line.substr(line.find(":") + 2)); //must use stof for floats/integers. Read as string, must convert to float/integer stof does that
                    courseMaterial.emplace_back(name, professor, ta, grade); //constructs a CourseInformation object directly inside the vector
                }
            }
            break;
        }
    }
    for(int i = 0; i < courseMaterial.size(); i++) { //inserts info into designated file, a couple of lines of additional program can change where data is stored but for now same file
        Classinfo << "----Course " << i + 1 << "----" << "\n"; //proud of this line because it's simple, just a nice header for each class. takes the loops current rotation and adds 1(vectors start at 0)
        Classinfo << "Course Name: " << courseMaterial[i].courseName << "\n";;
        Classinfo << "Course Professor: " << courseMaterial[i].courseProfessor << "\n";;
        Classinfo << "Course TA: " << courseMaterial[i].courseTA << "\n";
        Classinfo << "Course Grade: " << courseMaterial[i].courseGrade << "\n";
    }
    for(int i = 0; i < courseMaterial.size(); i++) { //adds up all the grades into totalGPA variable
        totalGPA += courseMaterial[i].courseGrade;
    }
    if(!courseMaterial.empty()) { //checks if empty, divides by size
            totalGPA /= courseMaterial.size();
        }
    //cout << courseMaterial.size(); //debugging, i had a lot of problems with the parsing 
    Classinfo << "Total GPA: " << totalGPA << "\n"; // storage
    cout << totalGPA; //for the user, also could be for debugging idc
}
