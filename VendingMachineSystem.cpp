/**
 * This is a vending machine back end
 * Learned more OOS & Classes, Enumeration classes, Mapping
 * I really need to use headerfiles...
 * Incomplete, still eats your money lowkey and doesn't give you candy - after 1/9/26 IT DOES!
 * (its my buisness plan -> 100% Profit Margin)
 * This is a boring program but was very fun to learn
 * yes its overcomplicated, yes it can be streamlined, yes im lazy.
 * In my defence more lines of code = better code... ;)
 * camelCase/PascalCase and honestly kinda whatever i felt like in the moment this time
 * Enjoy my overcomplicated Vending Machine UI! if anyone sees this please give feedback!
 * last edited - 1/9/26
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
    GummyCandy,
    ITEMNULL
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

        int ServiceRequest() {
            int serviceRequest;

            std::cin >> serviceRequest;
            return serviceRequest;
        }
};

class Customer {
    private:
        const AccessLevel level = AccessLevel::User;

    public:
        AccessLevel getAccessLevel() const {return level;}
};

class VendingMachine {
    private:
        float vendingMachineCashContent = 0.0;
        // Tally
            std::vector<Coin> coinTally;
            std::vector<PaperCash> cashTally;
            std::vector<VendingItems> itemsTally;
        MachineState state = MachineState::Idle;
        TransactionResult result;
        const AccessLevel level = AccessLevel::VendingMachine;
        VendingMachineTechnician tech;
        PaperCash userCash;
        Coin userCoin;

        std::map<MachineState, std::string> stateLookup = {
            {MachineState::Idle, "Idle"},
            {MachineState::Dispensing, "Dispensing"},
            {MachineState::Refunding, "Refunding"},
            {MachineState::ShutDown, "Shutdown"}
        };

        std::map<Coin, float> convertCoinToF = {
            {Coin::Quarter, .25},
            {Coin::FiftyCents, .5},
            {Coin::DollarCoin, 1.0}
        };

        std::map<PaperCash, int> convertCashToI = {
            {PaperCash::Dollar, 1},
            {PaperCash::TwoDollar, 2},
            {PaperCash::FiveDollar, 5},
            {PaperCash::TenDollar, 10},
            {PaperCash::TwentyDollar, 20},
            {PaperCash::FiftyDollar, 50},
            {PaperCash::HundredDollar, 100}
        };

    public:
        void InputMoneyCoin(Coin userCoin) {
            this->userCoin = userCoin;
        }
        void InputMoneyCash(PaperCash userCash) {
            this->userCash = userCash;
        }

        float getTotalCashContent() {
            totalVendingMachineCredit();
            return vendingMachineCashContent;
        }
        MachineState getMachineCurrState() const {return state;}
        Coin getUserCoins() const {return userCoin;}
        PaperCash getUserCash() const {return userCash;}

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

        void totalVendingMachineCredit() {
            for(const auto coin: coinTally) {
                auto credit = convertCoinToF.find(coin);
                vendingMachineCashContent += credit->second;
                coinTally.pop_back();
            }
            for(const auto cash: cashTally) {
                auto credit = convertCashToI.find(cash);
                vendingMachineCashContent += credit->second;
                cashTally.pop_back();
            }
        }

        void addCustomerInputCoin() {
            if(state == MachineState::Idle) {
                if(userCoin == Coin::Quarter) {
                    coinTally.push_back(Coin::Quarter);
                }
                else if(userCoin == Coin::FiftyCents) {
                    coinTally.push_back(Coin::FiftyCents);
                } 
                else if(userCoin == Coin::DollarCoin) {
                    coinTally.push_back(Coin::DollarCoin);
                }
            } else {
                std::cout << "ERROR:VENDING";
                MachineState::ShutDown;
            }
        }

        void addCustomerInputCash() {
            if(state == MachineState::ShutDown || state == MachineState::Dispensing || state == MachineState::Refunding) {
                std::cout << "ERROR:SHUT_DOWN_";
                RefundingCredit();
            }
            else if(userCash == PaperCash::Dollar) {
                cashTally.push_back(PaperCash::Dollar);
            }
            else if(userCash == PaperCash::TwoDollar) {
                cashTally.push_back(PaperCash::TwoDollar);
            }
            else if(userCash == PaperCash::FiveDollar) {
                cashTally.push_back(PaperCash::FiveDollar);
            }
            else if(userCash == PaperCash::TenDollar) {
                cashTally.push_back(PaperCash::TenDollar);
            }
            else if(userCash == PaperCash::TwentyDollar) {
                cashTally.push_back(PaperCash::TwentyDollar);
            } 
            else if(userCash == PaperCash::FiftyDollar) {
                cashTally.push_back(PaperCash::FiftyDollar);
            } 
            else if(userCash == PaperCash::HundredDollar) {
                cashTally.push_back(PaperCash::HundredDollar);   
            }
        }

        void InitializeVendingItems() {
            for(int i = 0; i < 10; i++) {
                itemsTally.push_back(VendingItems::BeefJerky);
                itemsTally.push_back(VendingItems::CandyBar);
                itemsTally.push_back(VendingItems::Cola);
                itemsTally.push_back(VendingItems::GummyCandy);
                itemsTally.push_back(VendingItems::GingerAle);
                itemsTally.push_back(VendingItems::Lolipop);
            }
        }

        VendingItems DispenseItem(VendingItems userItem) {
            std::string ERROR;
            if(state == MachineState::Dispensing || state == MachineState::Refunding) {
                ERROR = "PLEASE_WAIT";
                std::cout << ERROR;
                return VendingItems::ITEMNULL;
            }
            else if(state == MachineState::ShutDown) {
                ERROR = "MACHINE_UNOPERATIONAL_CONTACT_ASSISTANCE";
                std::cout << ERROR;
                return VendingItems::ITEMNULL;
            }
            else if(vendingMachineCashContent >= 1) {
                for (auto it = itemsTally.begin(); it != itemsTally.end(); ++it) {
                    if (*it == userItem) {
                        itemsTally.erase(it);
                        vendingMachineCashContent--;
                        return userItem;
                    }
                }
                return VendingItems::ITEMNULL;
            }
            else {
                std::cout << "NOT_ENOUGH_CREDIT";
                return VendingItems::ITEMNULL;
            }
            userItem = VendingItems::ITEMNULL; // Should NOT reach this point normally...
            return userItem;
        }

        void RefundingCredit() {
            MachineState tempstate = state;
            state = MachineState::Refunding;
            
            std::cout << "REFUNDED: $" << vendingMachineCashContent << "\n";
            vendingMachineCashContent = 0.0;

            state = tempstate;
        }

        void Servicing() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> distrib(100000, 999999);
            
            int serviceCode = distrib(gen);
            std::cout << serviceCode << "\n";

            if(serviceCode == tech.ServiceRequest()) {
                state = MachineState::ShutDown;
                std::cout << "AVAILABLE_TO_SERVICE" << "\n";
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

    Machine1.InitializeVendingItems(); // Going to add function where only a vending machine tech can add, but for now,
                                       // to change amount of contents: change the i variable in this function
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

    std::map<VendingItems, std::string> reverseItemName = {
        {VendingItems::CandyBar, "CandyBar"},
        {VendingItems::Cola, "Cola"},
        {VendingItems::BeefJerky,  "BeefJerky"},
        {VendingItems::GingerAle, "GingerAle"},
        {VendingItems::GummyCandy, "GummyCandy"},
        {VendingItems::Lolipop, "Lolipop"}
    };

    while (true) {
    std::cout << "Add Money (1) | Service (2) | View Cash (3) | Select Item (4) | Refund (5) | Display Available Item (6) | Exit (0)\n";
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
                        std::cout << "ENTER_LEGAL_TENDER\n";
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
                std::cout << "TOTAL_CREDIT: $" << totalMoney << "\n";
                break;
            }
            case 4: {
                std::cout << "Candy Bar - 1$ | Cola - 1$ | Beef Jerky - 1$ | Ginger Ale - 1$ | Gummy Candy - 1$ | Lolipop - 1$\n";
                std::cout << "Enter Item: "; // still need to make a payment method, should't be hard
                std::cin >> userItemRequest;

                auto userItem = itemName.find(userItemRequest);
                if(userItem != itemName.end()) {
                    VendingItems item = Machine1.DispenseItem(userItem ->second);
                    auto itemAdress = reverseItemName.find(item);
                    std::cout << "DISPENSED: " << itemAdress->second << "\n";
                    // std::cout << item;
                    }
                break;
            }
            case 5: {
                Machine1.RefundingCredit(); // When making the dispensing, I somehow broke this...
                break;
            }
            case 6: {
                 std::cout << "Candy Bar - 1$ | Cola - 1$ | Beef Jerky - 1$ | Ginger Ale - 1$ | Gummy Candy - 1$ | Lolipop - 1$\n";
                 break;
            }
            case 7: {
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
