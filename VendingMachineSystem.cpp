/**
 * This is a vending machine back end
 * Learned more OOS & Classes, Enumeration classes, Mapping
 * I really need to use headerfiles...
 * Incomplete, sometimes eats your money lowkey but im lazy
 * This is a boring program but was very fun to learn
 * camelCase/PascalCase and honestly kinda whatever i felt like in the moment this time
 */
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>

enum class AccessLevel {
    User,
    Administrator,
    VendingMachine
};

enum class MachineState {
    Idle,
    ShutDown,
    Dispensing,
    Refunding
};

enum class VendingItems {
    CandyBar,
    Lolipop,
    BeefJerky,
    Cola,
    GingerAle,
    GummyCandy
};

enum class Coin {
    Quarter,
    FiftyCents,
    DollarCoin
};

enum class PaperCash {
    Dollar,
    TwoDollar,
    FiveDollar,
    TenDollar,
    TwentyDollar,
    FiftyDollar,
    HundredDollar
};

enum class TransactionResult {
    Failed,
    Succeeded
};

class VendingMachineTechnician {
    private:
        AccessLevel level = AccessLevel::Administrator;
        std::vector<PaperCash> papercash; // "Wallet"
        std::vector<Coin> coins;

    public:
        AccessLevel getAccessLevel() const {return level;}

        void switchAccessLevel(AccessLevel& livelevel) {
            if(livelevel == AccessLevel::User) {
                livelevel = AccessLevel::Administrator;
            }
            else if(livelevel == AccessLevel::Administrator) {
                livelevel = AccessLevel::User;
            }
        }

        ServiceRequest() {
            int serviceRequest;

            std::cin >> serviceRequest;
            return serviceRequest;
        }
};

class Customer {
    private:
        const AccessLevel level = AccessLevel::User;

    public:
};

class VendingMachine {
    private:
        float vendingMachineCashContent = 0.0;
        MachineState state = MachineState::Idle;
        TransactionResult result;
        const AccessLevel level = AccessLevel::VendingMachine;
        VendingMachineTechnician tech;
        PaperCash userPaperCash;
        Coin userCoin;
        Customer user;

        std::map<MachineState, std::string> stateLookup = {
            {MachineState::Idle, "Idle"},
            {MachineState::Dispensing, "Dispensing"},
            {MachineState::Refunding, "Refunding"},
            {MachineState::ShutDown, "Shutdown"}
        };

    public:
        void InputMoneyCoin(Coin userCoin) {
            this->userCoin = userCoin;
        }
        void InputMoneyCash(PaperCash userCash) {
            this->userPaperCash = userCash;
        }

        float getTotalCashContent() const {return vendingMachineCashContent;}
        MachineState getMachineCurrState() const {return state;}
        Coin getUserCoins() const {return userCoin;}
        PaperCash getUserCash() const {return userPaperCash;}

        void setMachineStateFunction() {
            std::string techAnswer;
            MachineState currState = getMachineCurrState();

            if(tech.getAccessLevel() == AccessLevel::Administrator) {
                std::cout << "Enter_Vending_Machine_State(Idle/Shutdown): ";
                std::cin >> techAnswer;

                if(techAnswer == "Idle") {
                    state = MachineState::Idle;
                }
                else {
                    state = MachineState::ShutDown;
                }
            }
        }

        void addCustomerInputCoin() {
            if(state == MachineState::Idle) {
                if(userCoin == Coin::Quarter) {
                    vendingMachineCashContent += .25;
                }
                else if(userCoin == Coin::FiftyCents) {
                    vendingMachineCashContent += .5;
                } 
                else if(userCoin == Coin::DollarCoin) {
                    vendingMachineCashContent += 1;
                }
            } else {
                std::cout << "ERROR:VENDING";
                MachineState::ShutDown;
            }
        }

        void addCustomerInputCash() {
            if(state == MachineState::ShutDown || state == MachineState::Dispensing || state == MachineState::Refunding) {
                std::cout << "ERROR:SHUT_DOWN_";
                RefundingCash();
            }
            else if(userPaperCash == PaperCash::Dollar) {
                vendingMachineCashContent += 1;
            }
            else if(userPaperCash == PaperCash::TwoDollar) {
                vendingMachineCashContent += 2;
            }
            else if(userPaperCash == PaperCash::FiveDollar) {
                vendingMachineCashContent += 5;
            }
            else if(userPaperCash == PaperCash::TenDollar) {
                vendingMachineCashContent += 10;
            }
            else if(userPaperCash == PaperCash::TwentyDollar) {
                vendingMachineCashContent += 20;
            } 
            else if(userPaperCash == PaperCash::FiftyDollar) {
                vendingMachineCashContent += 50;
            } 
            else if(userPaperCash == PaperCash::HundredDollar) {
                vendingMachineCashContent += 100;   
            }
        }

        std::string DispenseItem() {
            return "";
        }

        void RefundingCash() {
            MachineState tempstate = state;
            state = MachineState::Refunding;
            int refundAmount = 0;
                if(userPaperCash == PaperCash::Dollar) {
                    refundAmount += 1;
                }
                else if(userPaperCash  == PaperCash::TwoDollar) {
                    refundAmount += 2;
                }
                else if(userPaperCash == PaperCash::FiveDollar) {
                    refundAmount += 5;
                }
                else if(userPaperCash == PaperCash::TenDollar) {
                    refundAmount += 10;
                }
                else if(userPaperCash == PaperCash::TwentyDollar) {
                    refundAmount += 20;
                } 
                else if(userPaperCash == PaperCash::FiftyDollar) {
                    refundAmount += 50;
                } 
                else if(userPaperCash == PaperCash::HundredDollar) {
                    refundAmount += 100;
                }
            std::cout << "AMT_DUE: $" << refundAmount << "\n";
            state = tempstate;
        }
        float RefundingCoins(Coin customerInputCoin) {
            state = MachineState::Refunding;
            float refundAmount;

            if(customerInputCoin == Coin::Quarter) {
                refundAmount += .25;
            }
            else if(customerInputCoin == Coin::FiftyCents) {
                refundAmount += .5;
            } 
            else if(customerInputCoin == Coin::DollarCoin) {
                refundAmount += 1;
            }
            return refundAmount;
        }

        void Servicing() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distrib(1, 10000);
            
            int serviceCode = distrib(gen);
            std::cout << serviceCode << "\n";

            if(serviceCode == tech.ServiceRequest()) {
                state = MachineState::ShutDown;
                std::cout << "Available_To_Service" << "\n";
            }
        }
};

int main() {
    VendingMachine Machine1;
    VendingMachineTechnician Tech1;
    Customer Customer1;
    std::string userMoney, userItemRequest;
    int userAnswer;
    int customerInputCash;

    std::map<std::string, PaperCash> cashName = {
        {"1", PaperCash::Dollar},
        {"2", PaperCash::TwoDollar},
        {"5", PaperCash::FiveDollar},
        {"10", PaperCash::TenDollar},
        {"20", PaperCash::TwentyDollar},
        {"50", PaperCash::FiftyDollar},
        {"100", PaperCash::HundredDollar}
    };

    std::map<std::string, Coin> coinName = {
        {".25", Coin::Quarter},
        {".50", Coin::FiftyCents},
        {"1.00", Coin::DollarCoin}
    };

    std::map<std::string, VendingItems> itemName = {
        {"CandyBar", VendingItems::CandyBar},
        {"Cola", VendingItems::Cola},
        {"BeefJerky", VendingItems::BeefJerky},
        {"GingerAle", VendingItems::GingerAle},
        {"GummyCandy", VendingItems::GummyCandy},
        {"Lolipop", VendingItems::Lolipop}
    };

    while (true) {
    std::cout << "Add Money (1) | Service (2) | View Cash (3) | Select Item (4) | Exit (0)\n";
    std::cin >> userAnswer;

        switch (userAnswer) {
            case 1: {
                std::cout << "Insert Currency: ";
                std::cin >> userMoney;

                auto userCoin = coinName.find(userMoney);
                if(userCoin != coinName.end()) {
                    Machine1.InputMoneyCoin(userCoin->second);
                    Machine1.addCustomerInputCoin();
                }
                else {
                    auto userCash = cashName.find(userMoney);
                    if(userCash != cashName.end()) {
                        Machine1.InputMoneyCash(userCash->second);
                        Machine1.addCustomerInputCash();
                    }
                    else {
                        std::cout << "Enter Legal Tender.\n";
                    }
                }
                float totalMoney = Machine1.getTotalCashContent();
                std::cout << "TOTAL_CREDIT: $" << totalMoney << "\n";
                break;
            }
            case 2: {
                Machine1.Servicing();
                break;
            }
            case 3: {
                float totalMoney = Machine1.getTotalCashContent();
                std::cout << totalMoney << "\n";
                break;
            }
            case 4: {
                std::cout << "Enter Item: ";
                std::cin >> userItemRequest;

                auto userItem = itemName.find(userItemRequest);
                if(userItem != itemName.end()) {
                    std::string item = Machine1.DispenseItem();
                    std::cout << item;
                    }
            }
            case 5: {
                Machine1.setMachineStateFunction();
                break;
            }
            case 0: {
                std::cout << "Shutting down program.\n";
                return 0;
            }
            default:
                std::cout << "Invalid selection. Try again.\n";
                break;
        }
    }
}
