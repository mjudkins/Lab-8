#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// READ FILE TO GET MENU
// inputs... foodnames and prices for each)
bool getMenu(string& foodName1, double& unitPrice1_s, double& unitPrice1_m, double& unitPrice1_l,
    string& foodName2, double& unitPrice2_s, double& unitPrice2_m, double& unitPrice2_l,
    string& foodName3, double& unitPrice3_s, double& unitPrice3_m, double& unitPrice3_l,
    string& foodName4, double& unitPrice4_s, double& unitPrice4_m, double& unitPrice4_l);

// DISPLAY MENU
void displayMenuItem(string itemName, double small, double med, double large);

// ORDER TAKING FUNCTION
double takeOrder(string foodName1, double unitPrice1_s, double unitPrice1_m, double unitPrice1_l,
    string foodName2, double unitPrice2_s, double unitPrice2_m, double unitPrice2_l,
    string foodName3, double unitPrice3_s, double unitPrice3_m, double unitPrice3_l,
    string foodName4, double unitPrice4_s, double unitPrice4_m, double unitPrice4_l,
    ofstream& fout,
    int& coffeeInv, int& milkInv, int& sugarInv, int& teaInv);

// APPLY MEMBER DISCOUNT
double memberDiscount(double runningTotal, bool& isMember);

// APPLY TAX
double applyTax(double runningTotal, double& ART, double& FCT, double& CMT);

// CALCULATE TIP + DISPLAY TIP OPTIONS
void displayTipOptions(double runningTotal, double& tip15, double& tip20, double& tip25);

// GET TIP CHOICE
void getTip(char& tipChoice, double& runningTotal, double tip15,
    double tip20, double tip25, double& customTip);

// SHOW TIP
void showTip(char tipChoice, double tip15, double tip20,
    double tip25, double customTip);

// DISPLAY TAX
void displayTax(double& ART, double& FCT, double& CMT);

// DISPLAY GRAND TOTAL
void displayGrand(double& runningTotal);

// DISPLAY LOYALTY POINTS
void displayLoyalty(bool isMember, double runningTotal);

// DISPLAY # OF CUSTOMERS/ INVENTORY LIST
void endOfDay(int customerTotal, double grandTotalSales,
    int coffeeInv, int milkInv, int sugarInv, int teaInv,
    string foodName1, string foodName2, string foodName3, string foodName4);

// DISPLAY RECEIPT ITEMS
void displayReceipt(string name);

int main()
{
    string name;
    bool isMember;
    double tip15, tip20, tip25;
    double ART = 0, FCT = 0, CMT = 0;
    char tipChoice;
    char anotherCustomer;
    int customerTotal = 0;
    double grandTotalSales = 0;

    int coffeeInv = 0;
    int milkInv = 0;
    int sugarInv = 0;
    int teaInv = 0;

    string foodName1;
    double unitPrice1_s, unitPrice1_m, unitPrice1_l;

    string foodName2;
    double unitPrice2_s, unitPrice2_m, unitPrice2_l;

    string foodName3;
    double unitPrice3_s, unitPrice3_m, unitPrice3_l;

    string foodName4;
    double unitPrice4_s, unitPrice4_m, unitPrice4_l;

    // READING FILE TO GET MENU
    if (!getMenu(foodName1, unitPrice1_s, unitPrice1_m, unitPrice1_l,
        foodName2, unitPrice2_s, unitPrice2_m, unitPrice2_l,
        foodName3, unitPrice3_s, unitPrice3_m, unitPrice3_l,
        foodName4, unitPrice4_s, unitPrice4_m, unitPrice4_l))
    {
        return 1;
    }

    do
    {

        double runningTotal = 0.00;
        double customTip = 0;

        ofstream fout;
        fout.open("data2.txt");

        // GREETING/GET NAME
        cout << "Welcome to Morgan and Jayda's Coffee Shop! Can I get a name for your order?" << endl;
        cin >> name;
        cout << "Thank you, " << name << "! Here are our menu items:\n"
            << endl;

        // DISPLAY MENU
        cout << fixed << setprecision(2);
        cout << "Item\t\t" << "Small\t\t" << "Medium\t\t" << "Large\t\t" << endl;
        cout << "______________________________________________________" << endl;
        displayMenuItem(foodName1, unitPrice1_s, unitPrice1_m, unitPrice1_l);
        displayMenuItem(foodName2, unitPrice2_s, unitPrice2_m, unitPrice2_l);
        displayMenuItem(foodName3, unitPrice3_s, unitPrice3_m, unitPrice3_l);
        displayMenuItem(foodName4, unitPrice4_s, unitPrice4_m, unitPrice4_l);
        cout << "\nPlease enter 'Checkout' when your order is complete." << endl;

        // ORDER LOOP (all items)
        fout << fixed << setprecision(2);
        fout << endl;

        runningTotal = takeOrder(foodName1, unitPrice1_s, unitPrice1_m, unitPrice1_l,
            foodName2, unitPrice2_s, unitPrice2_m, unitPrice2_l,
            foodName3, unitPrice3_s, unitPrice3_m, unitPrice3_l,
            foodName4, unitPrice4_s, unitPrice4_m, unitPrice4_l,
            fout,
            coffeeInv, milkInv, sugarInv, teaInv);

        // APPLY MEMBER DISCOUNT
        runningTotal = memberDiscount(runningTotal, isMember);

        // APPLY TAX
        runningTotal = applyTax(runningTotal, ART, FCT, CMT);

        // CALCULATE TIP + DISPLAY TIP OPTIONS
        displayTipOptions(runningTotal, tip15, tip20, tip25);

        // GET TIP CHOICE
        getTip(tipChoice, runningTotal, tip15, tip20, tip25, customTip);

        // DISPLAY RECEIPT
        displayReceipt(name);

        // SHOW TIP
        showTip(tipChoice, tip15, tip20, tip25, customTip);

        // DISPLAY TAX
        displayTax(ART, FCT, CMT);

        // DISPLAY GRAND TOTAL
        displayGrand(runningTotal);

        // DISPLAY LOYALTY POINTS
        displayLoyalty(isMember, runningTotal);

        // order complete.

        cout << "\n";
        cout << "Is there another customer? Y/N\n";
        cin >> anotherCustomer;

        customerTotal++;
        grandTotalSales += runningTotal;

    } while (anotherCustomer == 'Y' || anotherCustomer == 'y');

    endOfDay(customerTotal, grandTotalSales,
        coffeeInv, milkInv, sugarInv, teaInv,
        foodName1, foodName2, foodName3, foodName4);
}


// READ FILE TO GET MENU
// inputs... foodnames and prices for each)
bool getMenu(string& foodName1, double& unitPrice1_s, double& unitPrice1_m, double& unitPrice1_l,
    string& foodName2, double& unitPrice2_s, double& unitPrice2_m, double& unitPrice2_l,
    string& foodName3, double& unitPrice3_s, double& unitPrice3_m, double& unitPrice3_l,
    string& foodName4, double& unitPrice4_s, double& unitPrice4_m, double& unitPrice4_l)
{
    ifstream menuFile("menu.txt");
    if (!menuFile)
    {
        cout << "Could not open menu.txt" << endl;
        return false;
    }
    getline(menuFile, foodName1);
    menuFile >> unitPrice1_s;
    menuFile >> unitPrice1_m;
    menuFile >> unitPrice1_l;
    menuFile.ignore();
    getline(menuFile, foodName2);
    menuFile >> unitPrice2_s;
    menuFile >> unitPrice2_m;
    menuFile >> unitPrice2_l;
    menuFile.ignore();
    getline(menuFile, foodName3);
    menuFile >> unitPrice3_s;
    menuFile >> unitPrice3_m;
    menuFile >> unitPrice3_l;
    menuFile.ignore();
    getline(menuFile, foodName4);
    menuFile >> unitPrice4_s;
    menuFile >> unitPrice4_m;
    menuFile >> unitPrice4_l;
    menuFile.ignore();
    return true;
}

// DISPLAY MENU
void displayMenuItem(string itemName, double small, double med, double large)
{
    cout << itemName << " \t\t$" << small << " \t\t$" << med << " \t\t$" << large << endl;
}

// ORDER TAKING FUNCTION
/*This function performs these 4 tasks:
1.  get users menu choice and input validation
2.  get users size and quantity of choice
3.  calculate the price using item size and quantity/ inv update
4.  adds subtotal to running total and writes to receipt file

inputs: -the 4 food names and prices for each
        -the receipt file (fout) PASS BY REFERENCE
        -the 4 inventory counters PASS BY REFERENCE

*/
double takeOrder(string foodName1, double unitPrice1_s, double unitPrice1_m, double unitPrice1_l,
    string foodName2, double unitPrice2_s, double unitPrice2_m, double unitPrice2_l,
    string foodName3, double unitPrice3_s, double unitPrice3_m, double unitPrice3_l,
    string foodName4, double unitPrice4_s, double unitPrice4_m, double unitPrice4_l,
    ofstream& fout,
    int& coffeeInv, int& milkInv, int& sugarInv, int& teaInv)
{
    string food;
    char size;
    int quantity;
    double subtotal;
    double runningTotal = 0.00;

    do
    {
        // get item choice + validate
        cout << "\nEnter the name of the food item (or Checkout): ";
        cin >> food;
        while (food != foodName1 && food != foodName2 && food != foodName3 && food != foodName4 && food != "Checkout")
        {
            cout << "Invalid item. Try again" << endl;
            cin >> food;
        }

        if (food != "Checkout")
        {
            // get size and quantity
            cout << "Enter the size of the food item\n(s for small, m for medium, l for large): ";
            cin >> size;
            size = tolower(size);
            cout << "Enter the quantity of the food item: ";
            cin >> quantity;

            // price calculations + inventory update
            subtotal = 0;

            if (food == foodName1)
            {
                coffeeInv += quantity;
                if (size == 's')
                    subtotal = unitPrice1_s * quantity;
                else if (size == 'm')
                    subtotal = unitPrice1_m * quantity;
                else if (size == 'l')
                    subtotal = unitPrice1_l * quantity;
            }
            else if (food == foodName2)
            {
                milkInv += quantity;
                if (size == 's')
                    subtotal = unitPrice2_s * quantity;
                else if (size == 'm')
                    subtotal = unitPrice2_m * quantity;
                else if (size == 'l')
                    subtotal = unitPrice2_l * quantity;
            }
            else if (food == foodName3)
            {
                sugarInv += quantity;
                if (size == 's')
                    subtotal = unitPrice3_s * quantity;
                else if (size == 'm')
                    subtotal = unitPrice3_m * quantity;
                else if (size == 'l')
                    subtotal = unitPrice3_l * quantity;
            }
            else if (food == foodName4)
            {
                teaInv += quantity;
                if (size == 's')
                    subtotal = unitPrice4_s * quantity;
                else if (size == 'm')
                    subtotal = unitPrice4_m * quantity;
                else if (size == 'l')
                    subtotal = unitPrice4_l * quantity;
            }

            // add total + write to receipt
            runningTotal += subtotal;
            fout << quantity << " " << size << " " << food << "......... $" << subtotal << endl;
        }
    } while (food != "Checkout");
    fout.close();
    return runningTotal;
}

// APPLY MEMBER DISCOUNT
/*This function applies member discount
    inputs: runningTotal from takeOrder, isMember input
    outputs: new total with discount, or same total if not member */
double memberDiscount(double runningTotal, bool& isMember)
{
    cout << "Are you a member? (1 for yes, 0 for no): ";
    cin >> isMember;

    if (isMember)
        runningTotal *= 0.9; // 10% discount

    return runningTotal;
}

// APPLY TAX
/*This function applies tax to running total*/
double applyTax(double runningTotal, double& ART, double& FCT, double& CMT)
{
    ART = runningTotal * .065;
    FCT = runningTotal * .005;
    CMT = runningTotal * .02125;

    runningTotal += ART + FCT + CMT;
    return runningTotal;
}

// CALCULATE TIP + DISPLAY TIP OPTIONS
void displayTipOptions(double runningTotal, double& tip15, double& tip20, double& tip25)
{
    tip15 = runningTotal * .15;
    tip20 = runningTotal * .20;
    tip25 = runningTotal * .25;

    cout << "Tip Percentage: \t Amount:" << endl;
    cout << "A. 15% \t\t\t $" << tip15 << endl;
    cout << "B. 20% \t\t\t $" << tip20 << endl;
    cout << "C. 25% \t\t\t $" << tip25 << endl;
    cout << "D. Custom Tip" << endl;
    cout << "Pick a tip option. A, B, C, or D." << endl;
}

// GET TIP CHOICE
void getTip(char& tipChoice, double& runningTotal, double tip15,
    double tip20, double tip25, double& customTip)
{
    cin >> tipChoice;
    tipChoice = toupper(tipChoice);
    if (tipChoice == 'D')
    {
        cout << "How much would you like to tip?" << endl;
        cin >> customTip;
    }
    cout << "Thank you!" << endl;
    cout << " " << endl;

    if (tipChoice == 'A')
        runningTotal += tip15;
    else if (tipChoice == 'B')
        runningTotal += tip20;
    else if (tipChoice == 'C')
        runningTotal += tip25;
    else
        runningTotal += customTip;
}

// SHOW TIP
void showTip(char tipChoice, double tip15, double tip20,
    double tip25, double customTip)
{
    cout << "\n";

    if (tipChoice == 'A')
        cout << "You tipped: $" << tip15 << endl;
    else if (tipChoice == 'B')
        cout << "You tipped: $" << tip20 << endl;
    else if (tipChoice == 'C')
        cout << "You tipped: $" << tip25 << endl;
    else
        cout << "You tipped: $" << customTip << endl;

    cout << "\n";
}

// DISPLAY TAX
void displayTax(double& ART, double& FCT, double& CMT)
{
    cout << "Tax:" << endl;
    cout << "Arkansas State Tax: 6.5% - " << ART << endl;
    cout << "Faulkner County Tax: 0.5% - " << FCT << endl;
    cout << "Conway Municipal Tax: 2.125% - " << CMT << endl;
}

// DISPLAY GRAND TOTAL
void displayGrand(double& runningTotal)
{
    cout << "\n";

    cout << "Your grand total is: $" << runningTotal << endl;
}

// DISPLAY LOYALTY POINTS
void displayLoyalty(bool isMember, double runningTotal)
{
    if (isMember)
    {
        int points = runningTotal / 3;

        cout << "Loyalty points: ";
        while (points > 0)
        {
            cout << "*";
            points--;
        }
    }
}

// DISPLAY # OF CUSTOMERS/ INVENTORY LIST
void endOfDay(int customerTotal, double grandTotalSales,
    int coffeeInv, int milkInv, int sugarInv, int teaInv,
    string foodName1, string foodName2, string foodName3, string foodName4)
{
    cout << "\n";
    cout << "The total number of customers for today is: " << customerTotal << "\n";
    cout << "The grand total sales for today is: $" << grandTotalSales << "\n";

    int coffeeEnd = 100 - coffeeInv;
    int milkEnd = 100 - milkInv;
    int sugarEnd = 100 - sugarInv;
    int teaEnd = 100 - teaInv;

    cout << "Daily Inventory          Start          Change          End\n";
    cout << ".................................................................\n\n";
    cout << foodName1 << "\t\t\t 100\t\t-" << coffeeInv << "\t\t" << coffeeEnd << endl;
    cout << foodName2 << "\t\t\t 100\t\t-" << milkInv << "\t\t" << milkEnd << endl;
    cout << foodName3 << "\t\t\t 100\t\t-" << sugarInv << "\t\t" << sugarEnd << endl;
    cout << foodName4 << "\t\t\t 100\t\t-" << teaInv << "\t\t" << teaEnd << endl;
}

// DISPLAY RECEIPT ITEMS
// This function reads the receipt file written by takeOrder
void displayReceipt(string name)
{
    ifstream fin;
    fin.open("data2.txt");
    string line;

    cout << "Thank you for your purchase " << name << "!" << endl;
    cout << "You got:" << endl;

    while (getline(fin, line))
    {
        cout << line << endl;
    }

    fin.close();
}
