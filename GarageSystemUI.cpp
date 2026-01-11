/**
 * This is a Parking Garage UI
 * Using classes to manage different objects in the program
 * Each class has a specific set of tasks the class can operate
 * Learned Ownership vs Operating
 * Unfinished
 * Last edited - 1/11/26
 * camelCase/PascalCase
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

enum class GarageState {
    Open,
    Closed,
    Full,
    Maintenance
};

enum class TicketState {
    Active,
    Paid,
    Closed
};

enum class VehicleType {
    Car,
    Truck,
    CompactVehicle
};

std::map<std::string, VehicleType> vehicleMap {
    {"Car", VehicleType::Car},
    {"Truck", VehicleType::Truck},
    {"Compact Vehicle", VehicleType::CompactVehicle}
};

enum class AccessLevel {
    Customer,
    Employee,
    Admin
};

class Ticket { // Gets challanged by PaymentProcessor, Owns a timeStamp
    private:
        TicketState ticketState;
        int ticketNumber = 1;
        int timeStampDays = 0;

    public:
        int getTimeStampDays() const {return timeStampDays;}

        void timeStampTicket() {
            ticketState = TicketState::Active;
            timeStampDays = 1;
        }
        void terminateTicket() {
            ticketState = TicketState::Closed;
        }
        void paidTicket() {
            ticketState = TicketState::Paid;
        }
        void addDay() {
            timeStampDays++;
        }
};

class Vehicle { // Owns userMoney, an AccessLevel which is constant, and a VehicleType, Can respond to PaymentProcessor, or Employee
    private:
        const AccessLevel accessLevel = AccessLevel::Customer;
        VehicleType vehicleType;
        Ticket ticket;
        std::string licensePlate = "000-000";

    public:
        std::string getLicensePlate() const {return licensePlate;}
        VehicleType getVehicleType() const {return vehicleType;}

        void initializeVehicle() {
            std::string vechicleType;
            std::cout << "Car | Truck | Compact Vehicle\n";
            std::cin >> vechicleType;

            auto vehicleTypeAddress = vehicleMap.find(vechicleType);
            vehicleType = vehicleTypeAddress->second;
            
            std::cout << "Enter License Plate: ";
            std::cin >> licensePlate;
        }
        void addTicket(Ticket newTicket) {
            ticket = newTicket;
        }
        void payTicket() {
            const int dayPrice = 12;
            int amountDue = ticket.getTimeStampDays() * dayPrice;
            std::cout << amountDue << "\n";
            ticket.paidTicket();
        }
};

class PaymentProcessor { // Challenges a Vehicle, and a Ticket, Owns a ticket
    private:
        Vehicle visitingVehicle;
        Ticket currentTicket;
        std::vector<Vehicle> vehicleHistory;

        std::map<VehicleType, std::string> vehicleOutMap {
            {VehicleType::Car, "Car"},
            {VehicleType::Truck, "Truck"},
            {VehicleType::CompactVehicle, "Compact Vehicle"}
        };

    public:
        Vehicle ticketVehicle() {
            visitingVehicle.initializeVehicle();
            currentTicket.timeStampTicket();
            visitingVehicle.addTicket(currentTicket);

            return visitingVehicle;
        }
        void challangeVehicle() {
            visitingVehicle.payTicket();
        }
        void VehicleHistory(Vehicle paidVehicle) {
            vehicleHistory.push_back(paidVehicle);
        }
        void searchHistory() {
            for(const auto& paidVehicle: vehicleHistory) {
                std::cout << paidVehicle.getLicensePlate();
            }
        }
};

class ParkingGarage { // Can Challange Payment Processor, or Vehicle. Challanged by Employee. Owns parking spaces
    private:
        GarageState state;
        PaymentProcessor Processor1;
        std::vector<Vehicle> vehiclePopulationForSearch;
        double inputCapacity;
        double liveCapacity = 0.0;

    public:
        void checkPopulation() {
            if(liveCapacity >= inputCapacity) {
                std::cout << "Current Population: 50 We are Full\n";
            }
            std::cout << "Current Population: " << vehiclePopulationForSearch.size() << "\n";
        }
        void addToVehiclePopulation() {
            if(state == GarageState::Closed || state == GarageState::Full || state == GarageState::Maintenance) {
                std::cout << "No space at this time";
                return;
            }
            else {
                Vehicle tempVehicle = Processor1.ticketVehicle();
                if(tempVehicle.getVehicleType() == VehicleType::Car && liveCapacity++ > inputCapacity) {
                    std::cout << "No space at this time";
                    return;
                }
                else if(tempVehicle.getVehicleType() == VehicleType::Truck && liveCapacity + 2 > inputCapacity) {
                    std::cout << "No space at this time";
                    return;
                }
                else if(tempVehicle.getVehicleType() == VehicleType::CompactVehicle && liveCapacity + 0.5 > inputCapacity){
                    std::cout << "No space at this time";
                    return;
                }
                Processor1.VehicleHistory(tempVehicle);
                vehiclePopulationForSearch.push_back(tempVehicle);
                std::cout << vehiclePopulationForSearch.size() << "\n"; // Debugging

                if(tempVehicle.getVehicleType() == VehicleType::Car) {
                    liveCapacity++;
                }
                else if(tempVehicle.getVehicleType() == VehicleType::Truck) {
                    liveCapacity += 2;
                }
                else {
                    liveCapacity += .5;
                }
            }
        }
        void InputCapactity(double requestCapacity) {
            inputCapacity = requestCapacity;
        }
        void carExit() {
            std::string licenseTarget;
            std::cout << "Enter License Plate: ";
            std::cin >> licenseTarget;
            
            for(const auto& vehicle: vehiclePopulationForSearch) {
                if(vehicle.getLicensePlate() == licenseTarget) {
                    Processor1.challangeVehicle();
                    Vehicle paidVehicle = vehicle;
                    Processor1.VehicleHistory(paidVehicle);

                } 
                else {
                    std::cout << "No Matching Plate Found";
                }
            } 
        }
        void closeParkingGarage() {
            state = GarageState::Closed;
        }
        void openParkingGarage() {
            state = GarageState::Open;
        }
        void maintainenceParkingGarage() {
            state = GarageState::Maintenance;
        }
        void fullParkingGarage() {
            state = GarageState::Full;
        }
};

class Employee { // Can challange any class depending on access level, still deciding what an Employee might own
    private:
        AccessLevel accessLevel;
        ParkingGarage& assignedParkingGarage;

    public:
        void determineAccessLevel() {
            int userCode;
            std::cout << "Enter Access Code: ";
            std::cin >> userCode; 

            if(userCode == 1) { // Will make these numbers random soon
                accessLevel = AccessLevel::Employee;
            }
            else if(userCode == 2) { // ^^
                accessLevel = AccessLevel::Admin;
            }
        }
        void setParkingGarageState() {
            int adminAnswer;
            if(accessLevel == AccessLevel::Admin) {
                std::cout << "1-Close | 2-Open | 3-Maintenence | 4-Full";
                std::cin >> adminAnswer;

                switch(adminAnswer) {
                    case 1: {
                        assignedParkingGarage.closeParkingGarage();
                        break;
                    }
                    case 2: {
                        assignedParkingGarage.openParkingGarage();
                        break;
                    }
                    case 3: {
                        assignedParkingGarage.maintainenceParkingGarage();
                        break;
                    }
                    case 4: {
                        assignedParkingGarage.fullParkingGarage();
                    }
                }
            }
        }
        void changeGarageCapacity() {
            double desiredCapactiy;

            std::cout << "Enter Desired Capacity: ";
            std::cin >> desiredCapactiy;

            assignedParkingGarage.InputCapactity(desiredCapactiy);
        }
};

int main() {
    int userChocie;
    int userAnswer;
    ParkingGarage Garage1;
    Employee Employee1;

    while(true) {
        std::cout << "Normal Operations (1) | Employee Operations (2)\n";
        std::cin >> userChocie;
        switch(userChocie) {
            case 1: {
                Garage1.checkPopulation();
                Garage1.addToVehiclePopulation();
                Garage1.carExit();
                break;
            }
            case 2: {
                Employee1.determineAccessLevel();

                std::cout << "Change Garage Capacity (1) | Set Garage State (2)\n";
                std::cin >> userAnswer;

                switch(userAnswer) {
                    case 1: {
                        Employee1.changeGarageCapacity();
                        break;
                    }
                    case 2: {
                        Employee1.setParkingGarageState();
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}
