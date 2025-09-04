#include<iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <limits>
#include <cstdio>
#include <regex>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;



// Struct definitions
struct Person {
    string name;
    string email;
    string contact;

    Person() = default;

    Person(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, contact);
        }
    }

    void toString(string& line) const {
        line = name + "," + email + "," + contact;
    }
};

struct Vendor {
    string vendorID = "VD0000";
    Person person;
    string vendorType;
    float cost = 0.00;

    Vendor() = default;

    Vendor(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, vendorID, ',');
            getline(ss, vendorType, ',');
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            ss >> cost;
        }
    }

    void toString(string& line) const {
        line = vendorID + "," + vendorType + "," + person.name + "," + person.email + "," + person.contact + "," + to_string(cost);
    }
};

struct Client {
    string clientID = "C0000";
    Person person;
    string partnerName;
    string weddingDate;
    string specialRequest;
    int guestCount = 0;
    int tableCount = 0;
    string selectedPackage;
    string venueBooked;
    string cateringSelected;
    vector<string> selectedVendors;
    float totalPayment = 0;
    float amountPaid = 0;
    string paymentStatus;

    Client() = default;

    Client(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, clientID, ',');
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            getline(ss, partnerName, ',');
            getline(ss, weddingDate, ',');
            getline(ss, specialRequest, ',');
            ss >> guestCount; ss.ignore();
            ss >> tableCount; ss.ignore();
            getline(ss, selectedPackage, ',');
            getline(ss, venueBooked, ',');
            getline(ss, cateringSelected, ',');
            string vendors;
            getline(ss, vendors, ',');
            stringstream vendorStream(vendors);
            string vendor;
            while (getline(vendorStream, vendor, ';')) {
                if (!vendor.empty()) selectedVendors.push_back(vendor);
            }
            ss >> totalPayment; ss.ignore();
            ss >> amountPaid; ss.ignore();
            getline(ss, paymentStatus);
        }
    }

    void toString(string& line) const {
        string vendors;
        for (size_t i = 0; i < selectedVendors.size(); ++i) {
            vendors += selectedVendors[i];
            if (i + 1 < selectedVendors.size()) vendors += ";";
        }
        line = clientID + "," + person.name + "," + person.email + "," + person.contact + "," +
            partnerName + "," + weddingDate + "," + specialRequest + "," +
            to_string(guestCount) + "," + to_string(tableCount) + "," +
            selectedPackage + "," + venueBooked + "," + cateringSelected + "," +
            vendors + "," + to_string(totalPayment) + "," + to_string(amountPaid) + "," +
            paymentStatus;
    }
};


struct Package {
    string packageID = "PK0000";
    string packageName;
    string description;
    float price = 0.00;

    Package() = default;

    Package(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, packageID, ',');
            getline(ss, packageName, ',');
            getline(ss, description, ',');
            ss >> price;
        }
    }

    void toString(string& line) const {
        line = packageID + "," + packageName + "," + description + "," + to_string(price);
    }
};

struct Venue {
    string venueID = "VN0000"; // Default value with prefix
    string venueName;
    string location;
    int capacity = 0;
    float rentalCost = 0.00;

    Venue() = default;

    Venue(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, venueID, ',');
            getline(ss, venueName, ',');
            getline(ss, location, ',');
            ss >> capacity; ss.ignore();
            ss >> rentalCost;
        }
    }

    void toString(string& line) const {
        line = venueID + "," + venueName + "," + location + "," + to_string(capacity) + "," + to_string(rentalCost);
    }
};

struct Cater {
    string caterID = "CT0000";
    string caterName;
    string menuDescription;
    float costPerPerson = 0.00;

    Cater() = default;

    Cater(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, caterID, ',');
            getline(ss, caterName, ',');
            getline(ss, menuDescription, ',');
            ss >> costPerPerson;
        }
    }

    void toString(string& line) const {
        line = caterID + "," + caterName + "," + menuDescription + "," + to_string(costPerPerson);
    }
};

struct GuestRecord {
    int guestID;
    Person person;
    string rsvpStatus;
    string mealPreference;
    int tableNumber = -1;

    GuestRecord() = default;

    GuestRecord(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> guestID; ss.ignore();
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            getline(ss, rsvpStatus, ',');
            getline(ss, mealPreference, ',');
            ss >> tableNumber;
        }
    }

    void toString(string& line) const {
        line = to_string(guestID) + "," + person.name + "," + person.email + "," + person.contact + "," +
            rsvpStatus + "," + mealPreference + "," + to_string(tableNumber);
    }
};

struct Admin {
    string username;
    string password;

    Admin() = default;

    Admin(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password);
        }
    }

    void toString(string& line) const {
        line = username + "," + password;
    }
};

struct Payment {
    string paymentID = "PM0001";
    string clientID = "C0000";
    float  amountPaid = 0.0f;
    string paymentDate;
    string paymentMethod;
    float  discountApplied = 0.0f;
    string note;
    string paymentStatus;

    Payment() = default;

    Payment(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);

        auto asFloat = [](const string& s)->float { try { return stof(s); } catch (...) { return 0.0f; } };

        if (cols.size() >= 5) {
            paymentID = cols[0];
            clientID = cols[1];
            amountPaid = asFloat(cols[2]);
            paymentDate = cols[3];

            if (cols.size() >= 8) {
                paymentMethod = cols[4];
                discountApplied = asFloat(cols[5]);
                note = cols[6];
                paymentStatus = cols[7];
            }
            else {
                paymentMethod = "";
                discountApplied = 0.0f;
                note = "";
                paymentStatus = cols[4];
            }
        }
    }

    void toString(string& line) const {
        line = paymentID + "," +
            clientID + "," +
            to_string(amountPaid) + "," +
            paymentDate + "," +
            paymentMethod + "," +
            to_string(discountApplied) + "," +
            note + "," +
            paymentStatus;
    }
};



struct EventSchedule {
    string scheduleID = "S0000";
    string clientID = "C0000";
    string weddingDate;
    string time;
    string activity;

    EventSchedule() = default;

    EventSchedule(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> scheduleID; ss.ignore();
            ss >> clientID; ss.ignore();
            getline(ss, weddingDate, ',');
            getline(ss, time, ',');
            getline(ss, activity);
        }
    }

    void toString(string& line) const {
        line = scheduleID + "," + clientID + "," + weddingDate + "," + time + "," + activity;
    }
};

struct StringConst {
    const string LOGO_X =
        "                XXXXXXXXXXXXX                 \n"
        "            XXXX             XXXX             \n"
        "         XXX                     XXX          \n"
        "       XX                           XX        \n"
        "      X     XXXX             XXXX     X       \n"
        "    XX    XXXXXXXX         XXXXXXXX    XX     \n"
        "   X     XXXXXXXXXXXX   XXXXXXXXXXXX     X    \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X   \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X   \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X  \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X  \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X  \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X  \n"
        " X         XXXXXXXXXXXXXXXXXXXXXXX         X  \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X   \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X   \n"
        "   X          XXXXXXXXXXXXXXXXX          X    \n"
        "    XX           XXXXXXXXXXX           XX     \n"
        "      X            XXXXXXX            X       \n"
        "       XX            XXX            XX        \n"
        "         XXX          X          XXX          \n"
        "            XXXX             XXXX             \n"
        "                XXXXXXXXXXXXX                 \n";

    const string LOGO_O =
        "                \033[1;37mXXXXXXXXXXXXX\033[0m              \n"
        "            \033[1;37mXXXX             XXXX\033[0m          \n"
        "         \033[1;37mXXX                     XXX\033[0m       \n"
        "       \033[1;37mXX                           XX\033[0m     \n"
        "      \033[1;37mX     \033[1;31mXXXX             XXXX\033[1;37m     X\033[0m      \n"
        "    \033[1;37mXX    \033[1;31mXXXXXXXX         XXXXXXXX\033[1;37m    XX\033[0m    \n"
        "   \033[1;37mX     \033[1;31mXXXXXXXXXXXX   XXXXXXXXXXXX\033[1;37m     X\033[0m   \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m  \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m  \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m \n"
        " \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m  \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m  \n"
        "   \033[1;37mX          \033[1;31mXXXXXXXXXXXXXXXXX\033[1;37m          X\033[0m   \n"
        "    \033[1;37mXX           \033[1;31mXXXXXXXXXXX\033[1;37m           XX\033[0m    \n"
        "      \033[1;37mX            \033[1;31mXXXXXXX\033[1;37m            X\033[0m      \n"
        "       \033[1;37mXX            \033[1;31mXXX\033[1;37m            XX\033[0m       \n"
        "         \033[1;37mXXX          \033[1;31mX\033[1;37m          XXX\033[0m         \n"
        "            \033[1;37mXXXX             XXXX\033[0m         \n"
        "                \033[1;37mXXXXXXXXXXXXX\033[0m             \n";

    const string TITLE =
        " +-----------------------------------------+  \n"
        " | - Celestial Wedding  Event Management - |  \n"
        " +-----------------------------------------+     ";

    const string MainScMenu =
        " +-----------------------------------------+  \n"
        " | 1. Manage Client                        |  \n"
        " | 2. Manage Event                         |  \n"
        " | 3. Manage Vendors                       |  \n"
        " | 4. View Payment Records                 |  \n"
        " | 5. Manage Admin                         |  \n"
        " | 6. Event Monitoring                     |  \n"
        " | 7. Search Functionality                 |  \n"
        " | 0. Exit                                 |  \n"
        " +-----------------------------------------+  \n";

    const string ClientMenu =
        " +-----------------------------------------+  \n"
        " |    Client Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Clients                     |  \n"
        " +-----------------------------------------+  \n"
        " | 5. Checkout / Reservation               |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";

    const string EventMenu =
        " +-----------------------------------------+  \n"
        " |    Event Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Package Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";

    const string PackageMenu =
        " +-----------------------------------------+  \n"
        " |    Wedding Package Management           |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Packages                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+  \n";

    const string VenueMenu =
        " +-----------------------------------------+  \n"
        " |    Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Venues                      |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+  \n";

    const string CaterMenu =
        " +-----------------------------------------+  \n"
        " |    Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Catering                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+  \n";


    const string VendorMenu =
        " +-----------------------------------------+  \n"
        " |    Vendor Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Vendors                     |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";


    const string PaymentMenu =
        " +-----------------------------------------+  \n"
        " |    Payment Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Payments                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";


    const string AdminMenu =
        " +-----------------------------------------+  \n"
        " |    Admin Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Admin                       |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";


    const string EventMonitoringMenu =
        " +-----------------------------------------+  \n"
        " |    Event Monitoring                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";


    const string GuestMenu =
        " +-----------------------------------------+  \n"
        " |    Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Import Guest List                    |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Guest RSVP                    |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Show Guest List                      |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Monitoring             |  \n"
        " +-----------------------------------------+  \n";


    const string ScheduleMenu =
        " +-----------------------------------------+  \n"
        " |    Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Remove Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Schedules                   |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Monitoring             |  \n"
        " +-----------------------------------------+  \n";


    const string SearchMenu =
        " +-----------------------------------------+  \n"
        " |    Search Functionality                 |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Search Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Search Event                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Search Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";
};



// Template function to read things
template <typename T>
vector<T> getList(string filename) {
    ifstream file(filename);
    vector<T> list;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return list; // Return empty vector if file cannot be opened
    }

    string line;
    while (getline(file, line)) {
        list.emplace_back(line);
    }
    file.close();
    return list;
}

// Template function to save things
template <typename T>
void saveList(const vector<T>& list, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& r : list) {
            string line;
            r.toString(line);
            file << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }
}

// Template function for input validation
template <typename T>
bool validateInput(const T& input, const string& type = "") {
    if constexpr (is_same_v<T, string>) {
        //cout << "Debug: Input received: '" << input << "'" << endl; // Debug output
        if (type == "email") {
            regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
            return regex_match(input, emailPattern) && !input.empty();
        }
        else if (type == "date") {
            regex datePattern(R"(\d{4}-\d{2}-\d{2})");
            if (!regex_match(input, datePattern)) return false;
            stringstream ss(input);
            int year, month, day;
            char dash1, dash2;
            ss >> year >> dash1 >> month >> dash2 >> day;
            if (ss.fail() || dash1 != '-' || dash2 != '-') return false;
            if (year < 1900 || year > 9999) return false;
            if (month < 1 || month > 12) return false;
            if (day < 1 || day > 31) return false;
            if (month == 2) {
                bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
                return day <= (isLeap ? 29 : 28);
            }
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                return day <= 30;
            }
            return true;
        }
        else if (type == "time") {
            regex timePattern(R"(\d{2}:\d{2})");
            if (!regex_match(input, timePattern)) return false;
            stringstream ss(input);
            int hours, minutes;
            char colon;
            ss >> hours >> colon >> minutes;
            if (ss.fail() || colon != ':') return false;
            return hours >= 0 && hours <= 23 && minutes >= 0 && minutes <= 59;
        }
        else if (type == "non_empty") {
            return !input.empty() && input.find_first_not_of(" \t\n") != string::npos;
        }
        return !input.empty(); // Default check
    }
    else if constexpr (is_integral_v<T> || is_floating_point_v<T>) {
        return input >= 0;
    }
    return true;
}

// Template function to get validated input
template <typename T>
T getValidatedInput(const string& prompt, const string& type = "", const string& errorMsg = " Invalid input. Please try again: ") {
    T input;
    bool firstAttempt = true;
    while (true) {
        cout << prompt;

        if (!firstAttempt) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore only after first failed attempt
        }
        firstAttempt = false;

        if constexpr (is_same_v<T, string>) {
            getline(cin, input);
        }
        else {
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (cin.fail()) {
            cin.clear();
            cout << errorMsg;
            continue;
        }

        if (validateInput(input, type)) {
            return input;
        }

        cin.clear();
        cout << errorMsg;
    }
}

// Template function for generating unique IDs
template <typename T>
string uniqueIDGenerator(const string& prefix, const string& filename) {
    static map<string, int> idCounters;
    string key = prefix + typeid(T).name();

    // Initialize counter based on existing IDs in the file
    if (idCounters.find(key) == idCounters.end()) {
        int maxID = 0;
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string id;
                getline(ss, id, ',');
                if (id.substr(0, prefix.length()) == prefix) {
                    try {
                        int num = stoi(id.substr(prefix.length()));
                        maxID = max(maxID, num);
                    }
                    catch (...) {
                        // Skip invalid IDs
                    }
                }
            }
            file.close();
        }
        idCounters[key] = maxID;
    }

    // Increment counter and generate new ID
    int& counter = idCounters[key];
    counter++;

    char idStr[6]; // "0000" + '\0'
    #ifdef _MSC_VER
        sprintf_s(idStr, "%04d", counter);
    #else
        snprintf(idStr, sizeof(idStr), "%04d", counter);
    #endif
        string newID = prefix + idStr;

    // 确保唯一：若冲突则自增
    vector<T> list = getList<T>(filename);
    for (const auto& item : list) {
        string line;
        item.toString(line);
        stringstream ss(line);
        string existingID;
        getline(ss, existingID, ',');
        if (existingID == newID) 
        {
            counter++;
            #ifdef _MSC_VER
                sprintf_s(idStr, "%04d", counter);
            #else
                snprintf(idStr, sizeof(idStr), "%04d", counter);
            #endif
                newID = prefix + idStr;
        }
    }

    return newID;
}

// Template function to update fields, keeping old value if input is blank
template <typename T>
T updateField(const T& currentValue, const string& prompt, const string& type = "", const string& errorMsg = " Invalid input. Please try again: ") {
    if constexpr (is_same_v<T, string>) {
        cout << prompt << "\n(Current: " << currentValue << ", press Enter to keep): ";
        string input;
        getline(cin, input);
        if (input.empty() || input.find_first_not_of(" \t\n") == string::npos) {
            return currentValue;
        }
        if (validateInput(input, type)) {
            return input;
        }
        cout << errorMsg;
        return updateField(currentValue, prompt, type, errorMsg);
    }
    else {
        cout << prompt << "\n(Current: " << currentValue << ", enter 0 to keep): ";
        T input;
        cin >> input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << errorMsg;
            return updateField(currentValue, prompt, type, errorMsg);
        }
        if (input == 0) {
            return currentValue;
        }
        if (validateInput(input, type)) {
            return input;
        }
        cout << errorMsg;
        return updateField(currentValue, prompt, type, errorMsg);
    }
}

template <typename T>
void printRecords(vector<vector<pair<string, T>>> records, int perRow = 2) {
    // Calculate maximum width needed for each record
    vector<int> widths(records.size(), 0);
    for (size_t i = 0; i < records.size(); ++i) {
        for (const auto& field : records[i]) {
            ostringstream oss;
            oss << field.second;
            // Calculate total length: key + " : " + value + 2 for borders
            int contentLength = field.first.length() + oss.str().length() + 3;
            widths[i] = max(widths[i], contentLength);
        }
        // Ensure minimum width for aesthetics
        widths[i] = max(widths[i], 15);
    }

    for (size_t i = 0; i < records.size(); i += perRow) {
        int actualCount = min(perRow, static_cast<int>(records.size() - i));

        // Top borders
        for (int j = 0; j < actualCount; ++j) {
            // Width includes borders, so use widths[i + j] directly
            cout << "+" << string(widths[i + j], '-') << "+";
            if (j < actualCount - 1) cout << "   ";
            else cout << "";
        }
        cout << endl;

        // Find max number of fields in this row
        size_t maxFields = 0;
        for (int j = 0; j < actualCount; ++j) {
            maxFields = max(maxFields, records[i + j].size());
        }

        // Print each field row by row
        for (size_t line = 0; line < maxFields; ++line) {
            for (int j = 0; j < actualCount; ++j) {
                cout << "|";
                if (line < records[i + j].size()) {
                    auto& field = records[i + j][line];
                    ostringstream oss;
                    oss << field.second;
                    string content = field.first + " : " + oss.str();
                    // Adjust setw to account for borders
                    cout << left << setw(widths[i + j]) << content << "|";
                }
                else {
                    cout << setw(widths[i + j] - 1) << " " << "|";
                }
                if (j < actualCount - 1) cout << "   ";
                else cout << "";
            }
            cout << endl;
        }

        // Bottom borders
        for (int j = 0; j < actualCount; ++j) {
            cout << "+" << string(widths[i + j], '-') << "+";
            if (j < actualCount - 1) cout << "   ";
            else cout << "";
        }
        cout << endl << endl;
    }
}



bool login();

void showLoginScreen();
void showMainScreen();

void manageEvent();
void managePackage();
void manageVenue();
void manageCatering();
void manageVendor();
void manageAdmin();
void manageClient();
void managePayment();
void manageGuest();
void manageSchedule();
void manageEventMonitoring();
void searchFun();
void checkoutWizard();


int nextIntId(const string& filename);
string joinVec(const vector<string>& v, char sep = ';');
vector<string> splitIds(const string& s, char sep = ';');
float computeClientTotal(const Client& c, const vector<Package>& packages, const vector<Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors);

int nextIntId(const string& filename) {
    ifstream f(filename);
    int maxId = 0;
    string line;
    while (getline(f, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        int id = 0;
        ss >> id;                 // 读第一列的整型 ID
        if (!ss.fail()) maxId = max(maxId, id);
    }
    return maxId + 1;
}

string joinVec(const vector<string>& v, char sep) {
    string out;
    for (size_t i = 0; i < v.size(); ++i) {
        out += v[i];
        if (i + 1 < v.size()) out += sep;
    }
    return out;
}

vector<string> splitIds(const string& s, char sep) {
    vector<string> ids;
    string item;
    stringstream ss(s);
    while (getline(ss, item, sep)) {
        if (!item.empty()) ids.push_back(item);
    }
    return ids;
}

// 费用计算（MVP）：优先使用套餐价；否则 = 场地租金 + 餐饮人均（不乘人数，保持和你当前 Package 逻辑一致）+ 所选供应商费用总和
float computeClientTotal(const Client& c, const vector<Package>& packages, const vector<Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors) 
{
    float total = 0.0f;

    if (!c.selectedPackage.empty()) {
        auto pit = find_if(packages.begin(), packages.end(),
            [&](const Package& p) { return p.packageID == c.selectedPackage; });
        if (pit != packages.end()) total += pit->price;
    }
    else {
        if (!c.venueBooked.empty()) {
            auto vit = find_if(venues.begin(), venues.end(),
                [&](const Venue& v) { return v.venueID == c.venueBooked; });
            if (vit != venues.end()) total += vit->rentalCost;
        }
        if (!c.cateringSelected.empty()) {
            auto cit = find_if(caters.begin(), caters.end(),
                [&](const Cater& c2) { return c2.caterID == c.cateringSelected; });
            if (cit != caters.end()) total += cit->costPerPerson;
        }
    }

    for (const auto& vid : c.selectedVendors) {
        auto vit = find_if(vendors.begin(), vendors.end(),
            [&](const Vendor& v) { return v.vendorID == vid; });
        if (vit != vendors.end()) total += vit->cost;
    }
    return total;
}

void recomputeClientPayments(vector<Client>& clients, const vector<Payment>& payments)
{
    map<string, float> sumsPaid, sumsDiscount;
    for (const auto& p : payments) {
        sumsPaid[p.clientID] += p.amountPaid;
        sumsDiscount[p.clientID] += p.discountApplied;
    }
    for (auto& c : clients) {
        c.amountPaid = sumsPaid[c.clientID];
        float effectiveTotal = max(0.0f, c.totalPayment - sumsDiscount[c.clientID]);
        if (c.amountPaid <= 0.0f) c.paymentStatus = "UNPAID";
        else if (c.amountPaid + 1e-3 >= effectiveTotal) c.paymentStatus = "PAID";
        else c.paymentStatus = "PARTIAL";
    }
}



void checkoutWizard() 
{
    StringConst strConst;

    vector<Client>   clients = getList<Client>("clients.csv");
    vector<Package>  packages = getList<Package>("packages.csv");
    vector<Venue>    venues = getList<Venue>("venues.csv");
    vector<Cater>    caters = getList<Cater>("caterings.csv");
    vector<Vendor>   vendors = getList<Vendor>("vendors.csv");
    vector<Payment>  payments = getList<Payment>("payments.csv");

    auto saveAll = [&]() 
        {
        saveList(payments, "payments.csv");
        recomputeClientPayments(clients, payments);
        saveList(clients, "clients.csv");
        };

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;

    if (clients.empty()) 
    {
        cout << "No clients found. Please create a client first.\n";
        cout << "Press Enter..."; cin.get();
        return;
    }

    // Select Client
    {
        vector<vector<pair<string, string>>> recs;

        for (auto& c : clients) 
        {
            recs.push_back(
                {
                {"Client ID", c.clientID},
                {"Name", c.person.name},
                {"Wedding Date", c.weddingDate},
                {"Total", to_string(c.totalPayment)},
                {"Paid", to_string(c.amountPaid)},
                {"Status", c.paymentStatus}
                });
        }
        printRecords<string>(recs, 1);
    }

    string cid = getValidatedInput<string>("Enter client ID to checkout: ");
    auto cit = find_if(clients.begin(), clients.end(),
        [&](const Client& c) 
        { 
            return c.clientID == cid; 
        });
    if (cit == clients.end()) 
    { 
        cout << "Client not found.\nPress Enter..."; 
        cin.get(); 
        return; 
    }
    Client& c = *cit;

    // 计算小计
    float subtotal = computeClientTotal(c, packages, venues, caters, vendors);
    c.totalPayment = subtotal;

    // 输入折扣
    float discount = getValidatedInput<float>("Enter discount amount (0 for none): ");
    if (discount < 0) 
        discount = 0;

    if (discount > subtotal) 
        discount = subtotal;

    float net = subtotal - discount;

    // 发票预览
    {
        vector<vector<pair<string, string>>> inv;
        inv.push_back({
            {"Invoice (Preview)", ""},
            {"Client", c.person.name},
            {"Email",  c.person.email},
            {"Partner", c.partnerName},
            {"Wedding Date", c.weddingDate}
            });
        inv.push_back({
            {"Selections", ""},
            {"Package", c.selectedPackage.empty() ? "-" : c.selectedPackage},
            {"Venue",   c.venueBooked.empty() ? "-" : c.venueBooked},
            {"Catering",c.cateringSelected.empty() ? "-" : c.cateringSelected},
            {"Vendors", joinVec(c.selectedVendors)}
            });
        inv.push_back({
            {"Pricing", ""},
            {"Subtotal", to_string(subtotal)},
            {"Discount", to_string(discount)},
            {"Net Total", to_string(net)}
            });
        printRecords<string>(inv, 1);
    }

    string confirm = getValidatedInput<string>("Confirm this order? (Y/N): ", "non_empty");
    if (!(confirm.size() && (confirm[0] == 'Y' || confirm[0] == 'y'))) {
        cout << "Cancelled. Press Enter..."; cin.get();
        return;
    }

    // 选择是否立即支付
    string payNow = getValidatedInput<string>("Pay now? (Y/N): ", "non_empty");
    if (payNow.size() && (payNow[0] == 'Y' || payNow[0] == 'y')) 
    {
        string method = getValidatedInput<string>("Payment method (Cash/Card/Transfer/...): ", "non_empty");
        float amount = getValidatedInput<float>("Payment amount (default is Net): ");

        if (amount <= 0) amount = net; // 默认付净额
        if (amount > net) amount = net;

        Payment p;
        p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
        p.clientID = c.clientID;
        p.amountPaid = amount;
        p.paymentDate = getValidatedInput<string>("Payment date (YYYY-MM-DD): ", "date");
        p.paymentMethod = method;
        p.discountApplied = discount;              // 将此次折扣一并入账
        p.note = "checkout";
        p.paymentStatus = "RECEIVED";

        payments.push_back(p);
        saveAll();

        float allDiscount = 0.0f;
        for (const auto& q : payments) 
        {
            if (q.clientID == c.clientID) allDiscount += q.discountApplied;
        }

        // 收据
        vector<vector<pair<string, string>>> receipt;
        receipt.push_back({
            {"Receipt", ""},
            {"Payment ID", p.paymentID},
            {"Client ID", p.clientID},
            {"Client", c.person.name},
            {"Date", p.paymentDate}
            });
        receipt.push_back({
            {"Amount Paid", to_string(p.amountPaid)},
            {"Method", p.paymentMethod},
            {"Discount Applied", to_string(p.discountApplied)},
            {"Client Paid Total", to_string(c.amountPaid)},
            {"Effective Order Total", to_string(max(0.0f, c.totalPayment - allDiscount))},
            {"Client Status", c.paymentStatus}
            });
        printRecords<string>(receipt, 1);
        cout << "Press Enter..."; 
        cin.get();
    }
    else {
        // 不立即支付：若有折扣，建议也入账，以便状态计算用“有效总额”
        if (discount > 0.0f) {
            Payment p;
            p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
            p.clientID = c.clientID;
            p.amountPaid = 0.0f;
            p.paymentDate = getValidatedInput<string>("Record date for discount (YYYY-MM-DD): ", "date");
            p.paymentMethod = "N/A";
            p.discountApplied = discount;
            p.note = "discount only";
            p.paymentStatus = "DISCOUNT_APPLIED";
            payments.push_back(p);
            saveAll();
        }
        else {
            // 只记录“订单确认”
            Payment p;
            p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
            p.clientID = c.clientID;
            p.amountPaid = 0.0f;
            p.paymentDate = getValidatedInput<string>("Order confirmation date (YYYY-MM-DD): ", "date");
            p.paymentMethod = "N/A";
            p.discountApplied = 0.0f;
            p.note = "order confirmed (no payment)";
            p.paymentStatus = "ORDER_CONFIRMED";
            payments.push_back(p);
            saveAll();
        }
        cout << "Order confirmed. Current client status: " << c.paymentStatus << "\n";
        cout << "Press Enter..."; 
        cin.get();
    }
}


bool login() {
    cin.clear();
    string username = getValidatedInput<string>("Enter Username: ", "non_empty", "Invalid username. Please enter a non-empty username: ");
    string password = getValidatedInput<string>("Enter Password: ", "non_empty", "Invalid password. Please enter a non-empty password: ");
    vector<Admin> adminList = getList<Admin>("admins.csv");

    for (const auto& admin : adminList) {
        if (admin.username == username && admin.password == password) {
            cout << "Login successful!" << endl;
            return true;
        }
    }
    return false;
}

void showLoginScreen() {
    StringConst strConst;

    // Check if admins.csv exists, if not create with default admin
    ifstream checkFile("admins.csv");
    if (!checkFile.is_open()) {
        ofstream initFile("admins.csv");
        if (initFile.is_open()) {
            initFile << "admin,admin" << endl;
            initFile.close();
        }
    }
    else {
        checkFile.close();
    }

    while (true) {
        system("cls");
        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl;
        cout << "Please login to continue." << endl << endl;

        if (login()) {
            showMainScreen();
            break;
        }
        else {
            cout << "\nCREDENTIAL DO NOT MATCH. \nPress Enter to try again..." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ensure buffer is clear
        }
    }
}

void showMainScreen() {
    StringConst strConst;
    int x;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.MainScMenu;
    x = getValidatedInput<int>("\n Choose an option: ", "", " Invalid option. Please enter a number.");

    switch (x) {
    case 0:
        system("cls");
        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl << endl;
        cout << " Exiting the system. Goodbye!" << endl;
        exit(0);
        break;
    case 1:
        manageClient();
        break;
    case 2:
        manageEvent();
        break;
    case 3:
        manageVendor();
        break;
    case 4:
        managePayment();
        break;
    case 5:
        manageAdmin();
        break;
    case 6:
        manageEventMonitoring();
        break;
    case 7:
        searchFun();
        break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showMainScreen();
        break;
    }
}

void manageEvent() {
    StringConst strConst;
    int x;
    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.EventMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:
        managePackage();
        break;
    case 2:
        manageVenue();
        break;
    case 3:
        manageCatering();
        break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEvent();
        break;
    }
}

void managePackage() {
    // Package created by clients or admin
    // Package price = Venue price + Catering price
    StringConst strConst;
    int x;

    vector<Package> packageList = getList<Package>("packages.csv");
    vector<Venue> venueList = getList<Venue>("venues.csv");
    vector<Cater> caterList = getList<Cater>("caterings.csv");
    vector<vector<pair<string, string>>> records;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.PackageMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

    switch (x) {
    case 0:
        manageEvent();
        break;
    case 1:     // Create Package
    {
        system("cls");
        // Display available venues
        if (venueList.empty()) {
            cout << "No venues available. Please create a venue first." << endl;
            cout << "\nPress Enter to continue..." << endl;
            cin.get();
            managePackage();
            break;
        }
        cout << "Available Venues:" << endl;
        vector<vector<pair<string, string>>> venueRecords;
        for (const auto& venue : venueList) {
            vector<pair<string, string>> record;
            record.push_back({ "Venue ID", venue.venueID });
            record.push_back({ "Name", venue.venueName });
            record.push_back({ "Location", venue.location });
            record.push_back({ "Rental Cost", to_string(venue.rentalCost) });
            venueRecords.push_back(record);
        }
        printRecords<string>(venueRecords, 1);

        // Display available catering services
        if (caterList.empty()) {
            cout << "No catering services available. Please create a catering service first." << endl;
            cout << "\nPress Enter to continue..." << endl;
            cin.get();
            managePackage();
            break;
        }
        cout << "\nAvailable Catering Services:" << endl;
        vector<vector<pair<string, string>>> caterRecords;
        for (const auto& cater : caterList) {
            vector<pair<string, string>> record;
            record.push_back({ "Catering ID", cater.caterID });
            record.push_back({ "Name", cater.caterName });
            record.push_back({ "Cost Per Person", to_string(cater.costPerPerson) });
            caterRecords.push_back(record);
        }
        printRecords<string>(caterRecords, 1);

        string name = getValidatedInput<string>("\nEnter package name: ", "non_empty", "Invalid package name. Please enter a non-empty name: ");
        string description = getValidatedInput<string>("\nEnter package description: ", "non_empty", "Invalid description. Please enter a non-empty description: ");
        string venueID = getValidatedInput<string>("\nEnter venue ID: ", "non_empty", "Invalid venue ID. Please enter a valid ID: ");
        string caterID = getValidatedInput<string>("\nEnter catering ID: ", "non_empty", "Invalid catering ID. Please enter a valid ID: ");

        // Validate venue ID
        auto venueIt = find_if(venueList.begin(), venueList.end(), [&](const Venue& v) { return v.venueID == venueID; });
        if (venueIt == venueList.end()) {
            cout << "Venue not found." << endl;
            cout << "\nPress Enter to continue..." << endl;
            cin.get();
            managePackage();
            break;
        }

        // Validate catering ID
        auto caterIt = find_if(caterList.begin(), caterList.end(), [&](const Cater& c) { return c.caterID == caterID; });
        if (caterIt == caterList.end()) {
            cout << "Catering service not found." << endl;
            cout << "\nPress Enter to continue..." << endl;
            cin.get();
            managePackage();
            break;
        }

        Package newPackage;
        newPackage.packageName = name;
        newPackage.description = description;
        newPackage.price = venueIt->rentalCost + caterIt->costPerPerson;
        newPackage.packageID = uniqueIDGenerator<Package>("PK", "packages.csv");

        packageList.push_back(newPackage);
        saveList(packageList, "packages.csv");
        cout << "New package created successfully with price: " << newPackage.price << endl;
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        managePackage();
    }
    break;
    case 2:     // Remove Package
    {
        system("cls");
        for (const auto& package : packageList) {
            vector<pair<string, string>> record;
            record.push_back({ "Package ID", package.packageID });
            record.push_back({ "Name", package.packageName });
            record.push_back({ "Description", package.description });
            record.push_back({ "Price", to_string(package.price) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No packages found." << endl;
        }
        else {
            cout << "List of Packages:" << endl;
            printRecords<string>(records, 1);
        }

        cin.clear();
        string packageID = getValidatedInput<string>("\nEnter package ID to remove: ", "non_empty", "Invalid package ID. Please enter a non-empty ID: ");
        auto it = remove_if(packageList.begin(), packageList.end(), [&](const Package& p) { return p.packageID == packageID; });
        if (it != packageList.end()) {
            packageList.erase(it, packageList.end());
            saveList(packageList, "packages.csv");
            cout << "Package removed successfully!" << endl;
        }
        else {
            cout << "Package not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        managePackage();
    }
    break;
    case 3:     // Update Package
    {
        system("cls");
        for (const auto& package : packageList) {
            vector<pair<string, string>> record;
            record.push_back({ "Package ID", package.packageID });
            record.push_back({ "Name", package.packageName });
            record.push_back({ "Description", package.description });
            record.push_back({ "Price", to_string(package.price) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No packages found." << endl;
        }
        else {
            cout << "List of Packages:" << endl;
            printRecords<string>(records, 1);
        }

        cin.clear();
        string packageID = getValidatedInput<string>("\nEnter package ID to update: ", "non_empty", "Invalid package ID. Please enter a non-empty ID: ");
        auto it = find_if(packageList.begin(), packageList.end(), [&](const Package& p) { return p.packageID == packageID; });
        if (it != packageList.end()) {
            Package& packageToUpdate = *it;
            cout << "Updating Package: " << packageToUpdate.packageName << endl;
            string newName = updateField(packageToUpdate.packageName, "\nEnter new name (or press Enter to keep current): ", "non_empty");
            string newDescription = updateField(packageToUpdate.description, "\nEnter new description (or press Enter to keep current): ", "non_empty");

            // Display available venues for update
            cout << "\nAvailable Venues:" << endl;
            vector<vector<pair<string, string>>> venueRecords;
            for (const auto& venue : venueList) {
                vector<pair<string, string>> record;
                record.push_back({ "Venue ID", venue.venueID });
                record.push_back({ "Name", venue.venueName });
                record.push_back({ "Rental Cost", to_string(venue.rentalCost) });
                venueRecords.push_back(record);
            }
            printRecords<string>(venueRecords, 1);

            // Display available catering services for update
            cout << "\nAvailable Catering Services:" << endl;
            vector<vector<pair<string, string>>> caterRecords;
            for (const auto& cater : caterList) {
                vector<pair<string, string>> record;
                record.push_back({ "Catering ID", cater.caterID });
                record.push_back({ "Name", cater.caterName });
                record.push_back({ "Cost Per Person", to_string(cater.costPerPerson) });
                caterRecords.push_back(record);
            }
            printRecords<string>(caterRecords, 1);

            string newVenueID = updateField(string(""), "\nEnter new venue ID (or press Enter to keep current package price): ", "non_empty");
            string newCaterID = updateField(string(""), "\nEnter new catering ID (or press Enter to keep current package price): ", "non_empty");

            if (!newName.empty()) {
                packageToUpdate.packageName = newName;
            }
            if (!newDescription.empty()) {
                packageToUpdate.description = newDescription;
            }
            if (!newVenueID.empty() || !newCaterID.empty()) {
                float newPrice = 0.0;
                if (!newVenueID.empty()) {
                    auto venueIt = find_if(venueList.begin(), venueList.end(), [&](const Venue& v) { return v.venueID == newVenueID; });
                    if (venueIt != venueList.end()) {
                        newPrice += venueIt->rentalCost;
                    }
                    else {
                        cout << "Venue not found. Price unchanged." << endl;
                        newPrice = packageToUpdate.price;
                    }
                }
                else {
                    newPrice = packageToUpdate.price;
                }
                if (!newCaterID.empty()) {
                    auto caterIt = find_if(caterList.begin(), caterList.end(), [&](const Cater& c) { return c.caterID == newCaterID; });
                    if (caterIt != caterList.end()) {
                        newPrice += caterIt->costPerPerson;
                    }
                    else {
                        cout << "Catering service not found. Price unchanged." << endl;
                        newPrice = packageToUpdate.price;
                    }
                }
                packageToUpdate.price = newPrice;
            }
            saveList(packageList, "packages.csv");
            cout << "Package updated successfully!" << endl;
        }
        else {
            cout << "Package not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        managePackage();
    }
    break;
    case 4:     // Show All Packages
    {
        system("cls");
        for (const auto& package : packageList) {
            vector<pair<string, string>> record;
            record.push_back({ "Package ID", package.packageID });
            record.push_back({ "Name", package.packageName });
            record.push_back({ "Description", package.description });
            record.push_back({ "Price", to_string(package.price) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No packages found." << endl;
        }
        else {
            cout << "List of Packages:" << endl;
            printRecords<string>(records, 1);
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        managePackage();
    }
    break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    }
}

void manageVenue() {
    StringConst strConst;
    int x;

    vector<Venue> venueList = getList<Venue>("venues.csv");
    vector<vector<pair<string, string>>> records;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.VenueMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

    switch (x) {
    case 0:
        manageEvent();
        break;
    case 1:     // Create Venue
    {
        system("cls");
        string name = getValidatedInput<string>("\nEnter venue name: ", "non_empty", "Invalid venue name. Please enter a non-empty name: ");
        string location = getValidatedInput<string>("\nEnter venue location: ", "non_empty", "Invalid venue location. Please enter a non-empty location: ");
        int capacity = getValidatedInput<int>("\nEnter venue capacity: ", "", "Invalid capacity. Please enter a valid number: ");
        float price = getValidatedInput<float>("\nEnter venue price: ", "", "Invalid price. Please enter a valid number: ");

        Venue newVenue;
        newVenue.venueName = name;
        newVenue.location = location;
        newVenue.capacity = capacity;
        newVenue.rentalCost = price;

        string generatedID = uniqueIDGenerator<Venue>("VN", "venues.csv");
        newVenue.venueID = generatedID;

        newVenue.toString(name);
        venueList.push_back(newVenue);
        saveList(venueList, "venues.csv");
        cout << "New venue created successfully!" << endl;
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVenue();
    }
    break;
    case 2:     // Remove Venue
    {
        system("cls");
        for (const auto& venue : venueList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Venue ID", venue.venueID);
            pair<string, string> nameField("Name", venue.venueName);
            pair<string, string> locationField("Location", venue.location);
            pair<string, string> capacityField("Capacity", to_string(venue.capacity));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(locationField);
            record.push_back(capacityField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No venues found." << endl;
        }
        else {
            cout << "List of Venues:" << endl;
            printRecords<string>(records, 1);
        }

        // Clear input buffer before prompting for venue name
        cin.clear();
        string venueName = getValidatedInput<string>("\nEnter venue name to remove: ", "non_empty", "Invalid venue name. Please enter a non-empty name: ");
        auto it = remove_if(venueList.begin(), venueList.end(), [&](const Venue& venue) { return venue.venueName == venueName; });
        if (it != venueList.end()) {
            venueList.erase(it, venueList.end());
            saveList(venueList, "venues.csv");
            cout << "Venue removed successfully!" << endl;
            cin.get();
            manageVenue();
        }
    }

    break;
    case 3:     // Update Venue
    {
        system("cls");
        for (const auto& venue : venueList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Venue ID", venue.venueID); // Use venue.venueID directly
            pair<string, string> nameField("Name", venue.venueName);
            pair<string, string> locationField("Location", venue.location);
            pair<string, string> capacityField("Capacity", to_string(venue.capacity));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(locationField);
            record.push_back(capacityField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No venues found." << endl;
        }
        else {
            cout << "List of Venues:" << endl;
            printRecords<string>(records, 1);
        }

        cin.clear();
        string venueID = getValidatedInput<string>("\nEnter venue ID to update: ", "non_empty", "Invalid venue ID. Please enter a non-empty ID: ");
        auto it = find_if(venueList.begin(), venueList.end(), [&](const Venue& venue) { return venue.venueID == venueID; });
        if (it != venueList.end()) {
            Venue& venueToUpdate = *it;
            cout << "Updating Venue: " << venueToUpdate.venueName << endl;
            string newName = updateField(venueToUpdate.venueName, "\nEnter new name (or press Enter to keep current): ", "non_empty");
            string newLocation = updateField(venueToUpdate.location, "\nEnter new location (or press Enter to keep current): ", "non_empty");
            int newCapacity = updateField(venueToUpdate.capacity, "\nEnter new capacity (or enter 0 to keep current): ");
            if (!newName.empty()) {
                venueToUpdate.venueName = newName;
            }
            if (!newLocation.empty()) {
                venueToUpdate.location = newLocation;
            }
            if (newCapacity > 0) {
                venueToUpdate.capacity = newCapacity;
            }
            saveList(venueList, "venues.csv");
            cout << "Venue updated successfully!" << endl;
        }
        else {
            cout << "Venue not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVenue();
    }
    break;
    case 4:     // Show All Venue
    {
        system("cls");
        for (const auto& venue : venueList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Venue ID", venue.venueID);
            pair<string, string> nameField("Name", venue.venueName);
            pair<string, string> locationField("Location", venue.location);
            pair<string, string> capacityField("Capacity", to_string(venue.capacity));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(locationField);
            record.push_back(capacityField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No venues found." << endl;
        }
        else {
            cout << "List of Venues:" << endl;
            printRecords<string>(records, 1);
        }

        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVenue();
    }
    break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageVenue();
        break;
    }
}

void manageCatering() {
    StringConst strConst;
    int x;

    vector<Cater> caterList = getList<Cater>("caterings.csv");
    vector<vector<pair<string, string>>> records;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.CaterMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

    switch (x) {
    case 0:
        manageEvent();
        break;
    case 1:     // Create Catering
    {
        system("cls");
        string name = getValidatedInput<string>("\nEnter catering name: ", "non_empty", "Invalid catering name. Please enter a non-empty name: ");
        string type = getValidatedInput<string>("\nEnter catering type: ", "non_empty", "Invalid catering type. Please enter a non-empty type: ");
        double price = getValidatedInput<double>("\nEnter cost per person: ", "", "Invalid price. Please enter a valid number: ");
        Cater newCater;
        newCater.caterName = name;
        newCater.menuDescription = type;
        newCater.costPerPerson = price;
        string generatedID = uniqueIDGenerator<Cater>("CT", "caterings.csv");
        newCater.caterID = generatedID;
        newCater.toString(name);
        caterList.push_back(newCater);
        saveList(caterList, "caterings.csv");
        cout << "New catering service created successfully!" << endl;
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageCatering();
    }
    break;
    case 2:     // Remove Catering
    {
        system("cls");
        for (const auto& cater : caterList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Catering ID", cater.caterID);
            pair<string, string> nameField("Name", cater.caterName);
            pair<string, string> typeField("Type", cater.menuDescription);
            pair<string, string> priceField("Price", to_string(cater.costPerPerson));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(typeField);
            record.push_back(priceField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No catering services found." << endl;
        }
        else {
            cout << "List of Catering Services:" << endl;
            printRecords<string>(records, 1);
        }

        // Clear input buffer before prompting for catering ID
        cin.clear();
        string caterID = getValidatedInput<string>("\nEnter catering ID to remove: ", "non_empty", "Invalid catering ID. Please enter a non-empty ID: ");
        auto it = remove_if(caterList.begin(), caterList.end(), [&](const Cater& cater) { return cater.caterID == caterID; });
        if (it != caterList.end()) {
            caterList.erase(it, caterList.end());
            saveList(caterList, "caterings.csv");
            cout << "Catering service removed successfully!" << endl;
        }
        else {
            cout << "Catering service not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageCatering();
    }
    break;
    case 3:     // Update Catering
    {
        system("cls");
        for (const auto& cater : caterList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Catering ID", cater.caterID);
            pair<string, string> nameField("Name", cater.caterName);
            pair<string, string> typeField("Type", cater.menuDescription);
            pair<string, string> priceField("Price", to_string(cater.costPerPerson));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(typeField);
            record.push_back(priceField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No catering services found." << endl;
        }
        else {
            cout << "List of Catering Services:" << endl;
            printRecords<string>(records, 1);
        }

        cin.clear();
        string caterID = getValidatedInput<string>("\nEnter catering ID to update: ", "non_empty", "Invalid catering ID. Please enter a non-empty ID: ");
        auto it = find_if(caterList.begin(), caterList.end(), [&](const Cater& cater) { return cater.caterID == caterID; });
        if (it != caterList.end()) {
            Cater& caterToUpdate = *it;
            cout << "Updating Catering Service: " << caterToUpdate.caterName << endl;
            string newName = updateField(caterToUpdate.caterName, "\nEnter new name (or press Enter to keep current): ", "non_empty");
            string newType = updateField(caterToUpdate.menuDescription, "\nEnter new type (or press Enter to keep current): ", "non_empty");
            double newPrice = updateField(caterToUpdate.costPerPerson, "\nEnter new price (or enter 0 to keep current): ");
            if (!newName.empty()) {
                caterToUpdate.caterName = newName;
            }
            if (!newType.empty()) {
                caterToUpdate.menuDescription = newType;
            }
            if (newPrice > 0) {
                caterToUpdate.costPerPerson = newPrice;
            }
            saveList(caterList, "caterings.csv");
            cout << "Catering service updated successfully!" << endl;
        }
        else {
            cout << "Catering service not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageCatering();
    }
    break;
    case 4:     // Show All Catering
    {
        system("cls");
        for (const auto& cater : caterList) {
            vector<pair<string, string>> record;
            pair<string, string> idField("Catering ID", cater.caterID);
            pair<string, string> nameField("Name", cater.caterName);
            pair<string, string> typeField("Type", cater.menuDescription);
            pair<string, string> priceField("Price", to_string(cater.costPerPerson));
            record.push_back(idField);
            record.push_back(nameField);
            record.push_back(typeField);
            record.push_back(priceField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No catering services found." << endl;
        }
        else {
            cout << "List of Catering Services:" << endl;
            printRecords<string>(records, 1);
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageCatering();
    }
    break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageCatering();
        break;
    }
}

void manageVendor() {
    StringConst strConst;
    int x;

    vector<Vendor> vendorList = getList<Vendor>("vendors.csv");
    vector<vector<pair<string, string>>> records;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.VendorMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:     // Create Vendor
    {
        system("cls");
        string vendorType = getValidatedInput<string>("\nEnter vendor type: ", "non_empty", "Invalid vendor type. Please enter a non-empty type: ");
        string name = getValidatedInput<string>("\nEnter vendor name: ", "non_empty", "Invalid vendor name. Please enter a non-empty name: ");
        string email = getValidatedInput<string>("\nEnter vendor email: ", "email", "Invalid email. Please enter a valid email: ");
        string contact = getValidatedInput<string>("\nEnter vendor contact: ", "non_empty", "Invalid contact. Please enter a non-empty contact: ");
        float cost = getValidatedInput<float>("\nEnter vendor service cost: ", "", "Invalid cost. Please enter a valid number: ");

        Vendor newVendor;
        newVendor.vendorID = uniqueIDGenerator<Vendor>("VD", "vendors.csv");
        newVendor.vendorType = vendorType;
        newVendor.person.name = name;
        newVendor.person.email = email;
        newVendor.person.contact = contact;
        newVendor.cost = cost;

        vendorList.push_back(newVendor);
        saveList(vendorList, "vendors.csv");
        cout << "New vendor created successfully!" << endl;
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVendor();
    }
    break;
    case 2:     // Remove Vendor
    {
        system("cls");
        for (const auto& vendor : vendorList) {
            vector<pair<string, string>> record;
            record.push_back({ "Vendor ID", vendor.vendorID });
            record.push_back({ "Type", vendor.vendorType });
            record.push_back({ "Name", vendor.person.name });
            record.push_back({ "Email", vendor.person.email });
            record.push_back({ "Contact", vendor.person.contact });
            record.push_back({ "Cost", to_string(vendor.cost) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No vendors found." << endl;
        }
        else {
            cout << "List of Vendors:" << endl;
            printRecords<string>(records, 1);
        }
        cin.clear();
        string vendorID = getValidatedInput<string>("\nEnter vendor ID to remove: ", "non_empty", "Invalid vendor ID. Please enter a non-empty ID: ");
        auto it = remove_if(vendorList.begin(), vendorList.end(), [&](const Vendor& vendor) { return vendor.vendorID == vendorID; });
        if (it != vendorList.end()) {
            vendorList.erase(it, vendorList.end());
            saveList(vendorList, "vendors.csv");
            cout << "Vendor removed successfully!" << endl;
        }
        else {
            cout << "Vendor not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVendor();
    }
    break;
    case 3:     // Update Vendor
    {
        system("cls");
        for (const auto& vendor : vendorList) {
            vector<pair<string, string>> record;
            record.push_back({ "Vendor ID", vendor.vendorID });
            record.push_back({ "Type", vendor.vendorType });
            record.push_back({ "Name", vendor.person.name });
            record.push_back({ "Email", vendor.person.email });
            record.push_back({ "Contact", vendor.person.contact });
            record.push_back({ "Cost", to_string(vendor.cost) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No vendors found." << endl;
        }
        else {
            cout << "List of Vendors:" << endl;
            printRecords<string>(records, 2);
        }
        cin.clear();
        string vendorID = getValidatedInput<string>("\nEnter vendor ID to update: ", "non_empty", "Invalid vendor ID. Please enter a non-empty ID: ");
        auto it = find_if(vendorList.begin(), vendorList.end(), [&](const Vendor& vendor) { return vendor.vendorID == vendorID; });
        if (it != vendorList.end()) {
            Vendor& vendorToUpdate = *it;
            cout << "Updating Vendor: " << vendorToUpdate.person.name << endl;
            string newType = updateField(vendorToUpdate.vendorType, "\nEnter new type (or press Enter to keep current): ", "non_empty");
            string newName = updateField(vendorToUpdate.person.name, "\nEnter new name (or press Enter to keep current): ", "non_empty");
            string newEmail = updateField(vendorToUpdate.person.email, "\nEnter new email (or press Enter to keep current): ", "email");
            string newContact = updateField(vendorToUpdate.person.contact, "\nEnter new contact (or press Enter to keep current): ", "non_empty");
            float newCost = updateField(vendorToUpdate.cost, "\nEnter new cost (or enter 0 to keep current): ");

            if (!newType.empty()) {
                vendorToUpdate.vendorType = newType;
            }
            if (!newName.empty()) {
                vendorToUpdate.person.name = newName;
            }
            if (!newEmail.empty()) {
                vendorToUpdate.person.email = newEmail;
            }
            if (!newContact.empty()) {
                vendorToUpdate.person.contact = newContact;
            }
            if (newCost > 0) {
                vendorToUpdate.cost = newCost;
            }
            saveList(vendorList, "vendors.csv");
            cout << "Vendor updated successfully!" << endl;
        }
        else {
            cout << "Vendor not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVendor();
    }
    break;
    case 4:     // Show All Vendors
    {
        system("cls");
        for (const auto& vendor : vendorList) {
            vector<pair<string, string>> record;
            record.push_back({ "Vendor ID", vendor.vendorID });
            record.push_back({ "Type", vendor.vendorType });
            record.push_back({ "Name", vendor.person.name });
            record.push_back({ "Email", vendor.person.email });
            record.push_back({ "Contact", vendor.person.contact });
            record.push_back({ "Cost", to_string(vendor.cost) });
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No vendors found." << endl;
        }
        else {
            cout << "List of Vendors:" << endl;
            printRecords<string>(records, 2);
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageVendor();
    }
    break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageVendor();
        break;
    }
}

void manageAdmin() {
    StringConst strConst;
    int x;

    vector<Admin> adminList = getList<Admin>("admins.csv");
    vector<vector<pair<string, string>>> records;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.AdminMenu;
    x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:     // Create Admin
    {
        string username = getValidatedInput<string>("\n Enter new admin username: ", "non_empty", " Invalid username. Please enter a non-empty username: ");
        string password = getValidatedInput<string>("\n Enter new admin password: ", "non_empty", " Invalid password. Please enter a non-empty password: ");
        Admin newAdmin;
        newAdmin.username = username;
        newAdmin.password = password;

        newAdmin.toString(username);
        adminList.push_back(newAdmin);
        saveList(adminList, "admins.csv");
        cout << "New admin created successfully!" << endl;
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageAdmin();
    }
    break;
    case 2:     // Remove Admin
    {
        system("cls");
        for (const auto& admin : adminList) {
            vector<pair<string, string>> record;
            pair<string, string> usernameField("Username", admin.username);
            pair<string, string> passwordField("Password", admin.password);
            record.push_back(usernameField);
            record.push_back(passwordField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No admins found." << endl;
        }
        else {
            cout << "List of Admins:" << endl;
            printRecords<string>(records, 2);
        }

        // Clear input buffer before prompting for username
        cin.clear();

        string username = getValidatedInput<string>("\nEnter admin username to remove: ", "non_empty", "Invalid username. Please enter a non-empty username: ");
        auto it = remove_if(adminList.begin(), adminList.end(), [&](const Admin& admin) { return admin.username == username; });
        if (it != adminList.end()) {
            adminList.erase(it, adminList.end());
            saveList(adminList, "admins.csv");
            cout << "Admin removed successfully!" << endl;
        }
        else {
            cout << "Admin not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageAdmin();
    }
    break;
    case 3:     // Update Admin
    {
        system("cls");
        for (const auto& admin : adminList) {
            vector<pair<string, string>> record;
            pair<string, string> usernameField("Username", admin.username);
            pair<string, string> passwordField("Password", admin.password);
            record.push_back(usernameField);
            record.push_back(passwordField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No admins found." << endl;
        }
        else {
            cout << "List of Admins:" << endl;
            printRecords<string>(records, 2);
        }

        string username = getValidatedInput<string>("\nEnter admin username to update: ", "non_empty", "Invalid username. Please enter a non-empty username: ");
        auto it = find_if(adminList.begin(), adminList.end(), [&](const Admin& admin) { return admin.username == username; });
        if (it != adminList.end()) {
            Admin& adminToUpdate = *it;
            adminToUpdate.username = updateField(adminToUpdate.username, "\nEnter new username (leave blank to keep current)", "non_empty", "Invalid username. Please enter a non-empty username: ");
            adminToUpdate.password = updateField(adminToUpdate.password, "\nEnter new password (leave blank to keep current)", "non_empty", "Invalid password. Please enter a non-empty password: ");
            string line;
            adminToUpdate.toString(line);
            saveList(adminList, "admins.csv");
            cout << "Admin updated successfully!" << endl;
        }
        else {
            cout << "Admin not found." << endl;
        }
        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageAdmin();
    }
    break;
    case 4:	 // Show All Admins with printRecords
    {
        system("cls");
        for (const auto& admin : adminList) {
            vector<pair<string, string>> record;
            pair<string, string> usernameField("Username", admin.username);
            pair<string, string> passwordField("Password", admin.password);
            record.push_back(usernameField);
            record.push_back(passwordField);
            records.push_back(record);
        }
        if (records.empty()) {
            cout << "No admins found." << endl;
        }
        else {
            cout << "List of Admins:" << endl;
            printRecords<string>(records, 2);
        }

        cout << "\nPress Enter to continue..." << endl;
        cin.get();
        manageAdmin();
    }
    break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    }
}



void manageClient() {
    StringConst strConst;
    int x;

    // 载入各表（用于选择与计算）
    vector<Client>   clients = getList<Client>("clients.csv");
    vector<Package>  packages = getList<Package>("packages.csv");
    vector<Venue>    venues = getList<Venue>("venues.csv");
    vector<Cater>    caters = getList<Cater>("caterings.csv");
    vector<Vendor>   vendors = getList<Vendor>("vendors.csv");

    auto saveClients = [&]() { saveList(clients, "clients.csv"); };

    auto showAll = [&]() {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << "List of Clients:\n";
        vector<vector<pair<string, string>>> recs;
        for (const auto& c : clients) {
            vector<pair<string, string>> r;
            r.push_back({ "Client ID",       c.clientID });
            r.push_back({ "Name",            c.person.name });
            r.push_back({ "Email",           c.person.email });
            r.push_back({ "Contact",         c.person.contact });
            r.push_back({ "Partner",         c.partnerName });
            r.push_back({ "Wedding Date",    c.weddingDate });
            r.push_back({ "Guests",          to_string(c.guestCount) });
            r.push_back({ "Tables",          to_string(c.tableCount) });
            r.push_back({ "Package",         c.selectedPackage });
            r.push_back({ "Venue",           c.venueBooked });
            r.push_back({ "Catering",        c.cateringSelected });
            r.push_back({ "Vendors",         joinVec(c.selectedVendors) });
            r.push_back({ "Total Payment",   to_string(c.totalPayment) });
            r.push_back({ "Amount Paid",     to_string(c.amountPaid) });
            r.push_back({ "Status",          c.paymentStatus });
            recs.push_back(r);
        }
        if (recs.empty()) cout << "No clients found.\n";
        else printRecords<string>(recs, 1);
        cout << "\nPress Enter to continue..."; cin.get();
        };

    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.ClientMenu;  // 复用你已有的 Client 菜单文案
        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

        if (x == 0) { showMainScreen(); return; }

        else if (x == 1) { // Create Client
            system("cls");
            cout << strConst.LOGO_O << endl << strConst.TITLE << endl;

            Client c;
            c.clientID = uniqueIDGenerator<Client>("C", "clients.csv");  
            c.person.name = getValidatedInput<string>("\nEnter client name: ", "non_empty");
            c.person.email = getValidatedInput<string>("Enter client email: ", "email");
            c.person.contact = getValidatedInput<string>("Enter client contact: ", "non_empty");
            c.partnerName = getValidatedInput<string>("Enter partner name: ", "non_empty");
            c.weddingDate = getValidatedInput<string>("Enter wedding date (YYYY-MM-DD): ", "date");
            c.specialRequest = getValidatedInput<string>("Enter special request (can be blank): ");
            c.guestCount = getValidatedInput<int>("Enter guest count: ", "", " Invalid number: ");
            c.tableCount = getValidatedInput<int>("Enter table count: ", "", " Invalid number: ");

            // 显示可选资源（只做参考，不强制）
            if (!packages.empty()) {
                cout << "\nPackages:\n";
                vector<vector<pair<string, string>>> recs;
                for (auto& p : packages)
                    recs.push_back({ {"Package ID",p.packageID},{"Name",p.packageName},{"Price",to_string(p.price)} });
                printRecords<string>(recs, 1);
            }
            cout << "Enter package ID (or leave blank): ";
            string pkg; getline(cin, pkg);
            c.selectedPackage = pkg;

            if (c.selectedPackage.empty()) {
                if (!venues.empty()) {
                    cout << "\nVenues:\n";
                    vector<vector<pair<string, string>>> recs;
                    for (auto& v : venues)
                        recs.push_back({ {"Venue ID",v.venueID},{"Name",v.venueName},{"Rental",to_string(v.rentalCost)} });
                    printRecords<string>(recs, 1);
                }
                c.venueBooked = getValidatedInput<string>("Enter venue ID (or leave blank): ");

                if (!caters.empty()) {
                    cout << "\nCaterings:\n";
                    vector<vector<pair<string, string>>> recs;
                    for (auto& ct : caters)
                        recs.push_back({ {"Cater ID",ct.caterID},{"Name",ct.caterName},{"Cost/Person",to_string(ct.costPerPerson)} });
                    printRecords<string>(recs, 1);
                }
                c.cateringSelected = getValidatedInput<string>("Enter catering ID (or leave blank): ");
            }

            if (!vendors.empty()) {
                cout << "\nVendors:\n";
                vector<vector<pair<string, string>>> recs;
                for (auto& vd : vendors)
                    recs.push_back({ {"Vendor ID",vd.vendorID},{"Type",vd.vendorType},{"Name",vd.person.name},{"Cost",to_string(vd.cost)} });
                printRecords<string>(recs, 2);
            }
            cout << "Enter vendor IDs separated by ';' (or leave blank): ";
            string vids; getline(cin, vids);
            c.selectedVendors = splitIds(vids, ';');

            // 计算费用 & 初始支付状态
            c.totalPayment = computeClientTotal(c, packages, venues, caters, vendors);
            c.amountPaid = 0.0f;
            c.paymentStatus = "UNPAID";

            clients.push_back(c);
            saveClients();

            cout << "\nClient created. Total Payment = " << c.totalPayment << "\n";
            cout << "Press Enter to continue..."; cin.get();
        }

        else if (x == 2) { // Remove Client
            showAll();
            string id = (getValidatedInput<string>("Enter client ID to remove: ", "non_empty"));
            auto it = remove_if(clients.begin(), clients.end(),
                [&](const Client& c) { return c.clientID == id; });

            if (it != clients.end()) {
                clients.erase(it, clients.end());
                saveClients();
                cout << "Removed.\n";
            }
            else {
                cout << "Client not found.\n";
            }
            cout << "Press Enter to continue..."; cin.get();
        }

        else if (x == 3) { // Update Client
            showAll();
            string id = getValidatedInput<string>("Enter client ID to update: ", "non_empty");
            auto it = find_if(clients.begin(), clients.end(),
                [&](const Client& c) { return c.clientID == id; });

            if (it == clients.end()) {
                cout << "Client not found.\nPress Enter..."; cin.get();
                continue;
            }
            Client& c = *it;

            cout << "Updating Client " << c.clientID << " (" << c.person.name << ")\n";
            c.person.name = updateField(c.person.name, "New name? (Enter to keep)", "non_empty");
            c.person.email = updateField(c.person.email, "New email? (Enter to keep)", "email");
            c.person.contact = updateField(c.person.contact, "New contact? (Enter to keep)", "non_empty");
            c.partnerName = updateField(c.partnerName, "New partner name? (Enter to keep)", "non_empty");
            c.weddingDate = updateField(c.weddingDate, "New wedding date (YYYY-MM-DD)? (Enter to keep)", "date");
            c.specialRequest = updateField(c.specialRequest, "New special request? (Enter to keep)");
            c.guestCount = updateField(c.guestCount, "New guest count? (0 to keep)");
            c.tableCount = updateField(c.tableCount, "New table count? (0 to keep)");

            cout << "New package ID? (Enter to keep): ";
            {
                string pkg; getline(cin, pkg);
                if (!pkg.empty()) {
                    c.selectedPackage = pkg;
                    // 若切换到套餐，清空直选的场地/餐饮
                    c.venueBooked.clear();
                    c.cateringSelected.clear();
                }
            }
            if (c.selectedPackage.empty()) {
                c.venueBooked = updateField(c.venueBooked, "New venue ID? (Enter to keep)");
                c.cateringSelected = updateField(c.cateringSelected, "New catering ID? (Enter to keep)");
            }

            cout << "New vendor IDs (semicolon-separated). Enter to keep: ";
            {
                string vids; getline(cin, vids);
                if (!vids.empty()) c.selectedVendors = splitIds(vids, ';');
            }

            // 重新计算总价；支付状态先不动（后续做 Payment 模块时再自动联动）
            c.totalPayment = computeClientTotal(c, packages, venues, caters, vendors);
            if (c.amountPaid <= 0.0f) c.paymentStatus = "UNPAID";
            else if (c.amountPaid + 1e-3 >= c.totalPayment) c.paymentStatus = "PAID";
            else c.paymentStatus = "PARTIAL";

            saveClients();
            cout << "Updated.\nPress Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            showAll();
        }

        else if (x == 5) { // Checkout / Reservation
            checkoutWizard();
}

        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void managePayment() {
    StringConst strConst;
    int x;

    vector<Payment> payments = getList<Payment>("payments.csv");
    vector<Client>  clients = getList<Client>("clients.csv");

    auto saveAll = [&]() {
        // 先存 payments
        saveList(payments, "payments.csv");
        // 再按 payments 汇总回写 clients 的金额与状态
        recomputeClientPayments(clients, payments);
        saveList(clients, "clients.csv");
        };

    auto listClients = [&]() {
        vector<vector<pair<string, string>>> recs;
        for (auto& c : clients) {
            recs.push_back({
                {"Client ID", c.clientID},
                {"Name",      c.person.name},
                {"Total",     to_string(c.totalPayment)},
                {"Paid",      to_string(c.amountPaid)},
                {"Status",    c.paymentStatus}
                });
        }
        if (recs.empty()) cout << "No clients found.\n"; else printRecords<string>(recs, 1);
        };

    auto listPayments = [&]() 
        {
        vector<vector<pair<string, string>>> recs;
        for (auto& p : payments) 
        {
            recs.push_back({
                {"Payment ID",       p.paymentID},
                {"Client ID",        p.clientID},
                {"Amount",           to_string(p.amountPaid)},
                {"Date",             p.paymentDate},
                {"Method",           p.paymentMethod},
                {"Discount Applied", to_string(p.discountApplied)},
                {"Note",             p.note},
                {"Status",           p.paymentStatus}
                });
        }
        if (recs.empty()) cout << "No payments found.\n"; else printRecords<string>(recs, 1);
        };


    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.PaymentMenu;  // 你已有的菜单文案

        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        
        if (x == 0) 
        { 
            showMainScreen(); 
            return; 
        }

        if (x == 1) 
        { // Create Payment
            system("cls");
            cout << "Clients:\n";
            listClients();

            Payment p;
            p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
            p.clientID = getValidatedInput<string>("Enter client ID to pay for: ", "non_empty");
            auto cit = find_if(clients.begin(), clients.end(),
                [&](const Client& c) 
                { 
                    return c.clientID == p.clientID;
                });

            if (cit == clients.end()) 
            { 
                cout << "Client not found.\nPress Enter..."; 
                cin.get(); 
                continue; 
            }

            p.amountPaid = getValidatedInput<float>("Enter amount: ", "", " Invalid number: ");
            p.paymentDate = getValidatedInput<string>("Enter payment date (YYYY-MM-DD): ", "date");
            p.paymentMethod = getValidatedInput<string>("Payment method (Cash/Card/Transfer/...): ", "non_empty");
            p.discountApplied = getValidatedInput<float>("Discount to apply with this record (0 if none): ");
            
            if (p.discountApplied < 0) 
                p.discountApplied = 0;

            p.note = getValidatedInput<string>("Note (no comma please, Enter to skip): ");
            p.paymentStatus = "RECEIVED";

            payments.push_back(p);
            saveAll();

            float totalDisc = 0.0f;
            for (const auto& q : payments) if (q.clientID == p.clientID) totalDisc += q.discountApplied;

            cout << "Payment recorded. Client now Paid=" << cit->amountPaid
                << " / Effective Total=" << max(0.0f, cit->totalPayment - totalDisc)
                << " (" << cit->paymentStatus << ")\n";
            cout << "Press Enter..."; 
cin.get();
        }
        else if (x == 2) 
        { // Remove Payment
            system("cls");
            listPayments();
            string pid = getValidatedInput<string>("Enter payment ID to remove: ");
            auto it = remove_if(payments.begin(), payments.end(),
                [&](const Payment& p) { return p.paymentID == pid; });
            if (it != payments.end()) {
                payments.erase(it, payments.end());
                saveAll();
                cout << "Removed.\n";
            }
            else {
                cout << "Payment not found.\n";
            }
            cout << "Press Enter..."; cin.get();
        }
        else if (x == 3) 
        { // Update Payment
            system("cls");
            listPayments();
            string pid = getValidatedInput<string>("Enter payment ID to update: ");
            auto it = find_if(payments.begin(), payments.end(),
                [&](const Payment& p) { return p.paymentID == pid; });
            if (it == payments.end()) { cout << "Not found.\nPress Enter..."; cin.get(); continue; }

            Payment& p = *it;

            string newCid = updateField(p.clientID, "New client ID? (0 to keep): ");
            if (!newCid.empty()) p.clientID = newCid;

            float newAmt = updateField(p.amountPaid, "New amount? (0 to keep): ");
            if (newAmt > 0) p.amountPaid = newAmt;

            string newDate = updateField(p.paymentDate, "New date (YYYY-MM-DD)?", "date");
            if (!newDate.empty()) p.paymentDate = newDate;

            string newMethod = updateField(p.paymentMethod, "New method? (Enter to keep): ");
            if (!newMethod.empty()) p.paymentMethod = newMethod;

            float newDisc = updateField(p.discountApplied, "New discount? (0 to keep): ");
            if (newDisc >= 0) p.discountApplied = newDisc;

            string newNote = updateField(p.note, "New note? (Enter to keep): ");
            if (!newNote.empty()) p.note = newNote;

            string newStat = updateField(p.paymentStatus, "New payment status? (e.g., RECEIVED/REFUND)", "non_empty");
            if (!newStat.empty()) p.paymentStatus = newStat;

            saveAll();
            cout << "Updated.\nPress Enter..."; cin.get();
        }

        else if (x == 4) { // Show All Payments
            system("cls");
            listPayments();
            cout << "Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void manageGuest() {
    StringConst strConst;
    int x;
    vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");

    auto save = [&]() { saveList(guests, "guests.csv"); };

    auto listGuests = [&]() {
        vector<vector<pair<string, string>>> recs;
        for (auto& g : guests) {
            recs.push_back({
                {"Guest ID", to_string(g.guestID)},
                {"Name", g.person.name},
                {"Email", g.person.email},
                {"Contact", g.person.contact},
                {"RSVP", g.rsvpStatus},
                {"Meal", g.mealPreference},
                {"Table", to_string(g.tableNumber)}
                });
        }
        if (recs.empty()) cout << "No guests found.\n"; else printRecords<string>(recs, 2);
        };

    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.GuestMenu;
        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        if (x == 0) return;

        if (x == 1) { // Import Guest List（文件名自行输入）
            system("cls");
            cout << "Enter import filename (e.g., guests_import.csv): ";
            string fname; getline(cin, fname);

            vector<GuestRecord> incoming = getList<GuestRecord>(fname);
            int nextId = nextIntId("guests.csv");

            // 保证ID不重复/不为0
            map<int, bool> used;
            for (auto& g : guests) used[g.guestID] = true;
            for (auto g : incoming) {
                if (g.guestID <= 0 || used[g.guestID]) g.guestID = nextId++;
                used[g.guestID] = true;
                guests.push_back(g);
            }
            save();
            cout << "Imported " << incoming.size() << " guests.\nPress Enter..."; cin.get();
        }
        else if (x == 2) { // Update Guest RSVP
            system("cls");
            listGuests();
            int gid = getValidatedInput<int>("Enter guest ID to update: ");
            auto it = find_if(guests.begin(), guests.end(),
                [&](const GuestRecord& g) { return g.guestID == gid; });
            if (it == guests.end()) { cout << "Guest not found.\nPress Enter..."; cin.get(); continue; }
            GuestRecord& g = *it;

            g.rsvpStatus = updateField(g.rsvpStatus, "New RSVP? (YES/NO/MAYBE): ", "non_empty");
            g.mealPreference = updateField(g.mealPreference, "New meal preference?: ");
            int newTable = updateField(g.tableNumber, "New table number? (0 to keep): ");
            if (newTable > 0) g.tableNumber = newTable;

            save();
            cout << "Updated.\nPress Enter..."; cin.get();
        }
        else if (x == 3) { // Show Guest List
            system("cls"); listGuests(); cout << "Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void manageSchedule() {
    StringConst strConst;
    int x;
    vector<EventSchedule> schedules = getList<EventSchedule>("schedules.csv");

    auto save = [&]() { saveList(schedules, "schedules.csv"); };

    auto listSchedules = [&]() {
        vector<vector<pair<string, string>>> recs;
        for (auto& s : schedules) {
            recs.push_back({
                {"Schedule ID", s.scheduleID},
                {"Client ID", s.clientID},
                {"Date", s.weddingDate},
                {"Time", s.time},
                {"Activity", s.activity}
                });
        }
        if (recs.empty()) cout << "No schedules found.\n"; else printRecords<string>(recs, 1);
        };

    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.ScheduleMenu;
        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        if (x == 0) return;

        if (x == 1) { // Create
            EventSchedule s;
            s.scheduleID = nextIntId("schedules.csv");
            s.clientID = getValidatedInput<int>("Enter client ID: ");
            s.weddingDate = getValidatedInput<string>("Date (YYYY-MM-DD): ", "date");
            s.time = getValidatedInput<string>("Time (HH:MM): ", "time");
            s.activity = getValidatedInput<string>("Activity: ", "non_empty");
            schedules.push_back(s);
            save();
            cout << "Created.\nPress Enter..."; cin.get();
        }
        else if (x == 2) { // Update
            system("cls");
            listSchedules();
            string sid = getValidatedInput<string>("Enter schedule ID to update: ");
            auto it = find_if(schedules.begin(), schedules.end(),
                [&](const EventSchedule& s) { return s.scheduleID == sid; });
            if (it == schedules.end()) { cout << "Not found.\nPress Enter..."; cin.get(); continue; }
            EventSchedule& s = *it;

            string newCid = updateField(s.clientID, "New client ID? (0 to keep): ");
            if (!newCid.empty()) s.clientID = newCid;
            string newDate = updateField(s.weddingDate, "New date (YYYY-MM-DD)?", "date");
            if (!newDate.empty()) s.weddingDate = newDate;
            string newTime = updateField(s.time, "New time (HH:MM)?", "time");
            if (!newTime.empty()) s.time = newTime;
            string newAct = updateField(s.activity, "New activity?", "non_empty");
            if (!newAct.empty()) s.activity = newAct;

            save();
            cout << "Updated.\nPress Enter..."; cin.get();
        }
        else if (x == 3) { // Remove
            system("cls");
            listSchedules();
            string sid = getValidatedInput<string>("Enter schedule ID to remove: ");
            auto it = remove_if(schedules.begin(), schedules.end(),
                [&](const EventSchedule& s) { return s.scheduleID == sid; });
            if (it != schedules.end()) {
                schedules.erase(it, schedules.end());
                save();
                cout << "Removed.\n";
            }
            else cout << "Not found.\n";
            cout << "Press Enter..."; cin.get();
        }
        else if (x == 4) { // Show All
            system("cls"); listSchedules(); cout << "Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void manageEventMonitoring() 
{
    StringConst strConst;
    int x;
    while (true)
    {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.EventMonitoringMenu;
        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        if (x == 0) 
        { 
            showMainScreen();
            return; 
        }
        if (x == 1) 
        { 
            manageGuest(); 
        }
        else if (x == 2) 
        { 
            manageSchedule(); 
        }
        else 
        { 
            cout << " Invalid option.\nPress Enter..."; 
            cin.get(); 
        }
    }
}

void searchFun() {
    StringConst strConst;
    int x;

    auto icontains = [&](const string& hay, const string& needle) 
        {
        if (needle.empty()) 
            return false;

        string h = hay, n = needle;
        transform(h.begin(), h.end(), h.begin(), [](unsigned char c) { return std::tolower(c); });
        transform(n.begin(), n.end(), n.begin(), [](unsigned char c) { return std::tolower(c); });
        return h.find(n) != string::npos;
        };

    while (true) 
    {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.SearchMenu;
        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
       
        if (x == 0) 
        { 
            showMainScreen(); 
            return; 
        }

        if (x == 1) 
        { // Search Client
            vector<Client> clients = getList<Client>("clients.csv");
            string q = getValidatedInput<string>("Enter client name/email/ID/date keyword: ", "non_empty");

            vector<vector<pair<string, string>>> recs;
            for (const auto& c : clients) 
            {
                if (icontains(c.person.name, q) ||
                    icontains(c.person.email, q) ||
                    icontains(c.weddingDate, q) ||
                    icontains(c.clientID, q)) {
                    recs.push_back({
                        {"Client ID",   c.clientID},
                        {"Name",        c.person.name},
                        {"Email",       c.person.email},
                        {"Wedding Date",c.weddingDate},
                        {"Status",      c.paymentStatus}
                        });
                }
            }
            if (recs.empty()) cout << "No matches.\n";
            else printRecords<string>(recs, 1);
            cout << "Press Enter..."; cin.get();
        }
        else if (x == 2) { // Search Event (packages/venues/caterings)
            vector<Package> packages = getList<Package>("packages.csv");
            vector<Venue>   venues = getList<Venue>("venues.csv");
            vector<Cater>   caters = getList<Cater>("caterings.csv");
            string q = getValidatedInput<string>("Enter keyword (ID/name/location/desc): ", "non_empty");

            cout << "\nPackages matched:\n";
            {
                vector<vector<pair<string, string>>> recs;
                for (const auto& p : packages) {
                    if (icontains(p.packageID, q) || icontains(p.packageName, q) || icontains(p.description, q)) {
                        recs.push_back({
                            {"Package ID", p.packageID},
                            {"Name",       p.packageName},
                            {"Price",      to_string(p.price)}
                            });
                    }
                }
                if (recs.empty()) cout << "(none)\n"; else printRecords<string>(recs, 1);
            }

            cout << "Venues matched:\n";
            {
                vector<vector<pair<string, string>>> recs;
                for (const auto& v : venues) {
                    if (icontains(v.venueID, q) || icontains(v.venueName, q) || icontains(v.location, q)) {
                        recs.push_back({
                            {"Venue ID", v.venueID},
                            {"Name",     v.venueName},
                            {"Location", v.location}
                            });
                    }
                }
                if (recs.empty()) cout << "(none)\n"; else printRecords<string>(recs, 1);
            }

            cout << "Caterings matched:\n";
            {
                vector<vector<pair<string, string>>> recs;
                for (const auto& c : caters) {
                    if (icontains(c.caterID, q) || icontains(c.caterName, q) || icontains(c.menuDescription, q)) {
                        recs.push_back({
                            {"Cater ID", c.caterID},
                            {"Name",     c.caterName},
                            {"Menu",     c.menuDescription}
                            });
                    }
                }
                if (recs.empty()) cout << "(none)\n"; else printRecords<string>(recs, 1);
            }

            cout << "Press Enter..."; cin.get();
        }
        else if (x == 3) { // Search Vendor
            vector<Vendor> vendors = getList<Vendor>("vendors.csv");
            string q = getValidatedInput<string>("Enter keyword (ID/type/name/email/contact): ", "non_empty");

            vector<vector<pair<string, string>>> recs;
            for (const auto& v : vendors) {
                if (icontains(v.vendorID, q) || icontains(v.vendorType, q) ||
                    icontains(v.person.name, q) || icontains(v.person.email, q) ||
                    icontains(v.person.contact, q)) {
                    recs.push_back({
                        {"Vendor ID", v.vendorID},
                        {"Type",      v.vendorType},
                        {"Name",      v.person.name},
                        {"Email",     v.person.email},
                        {"Contact",   v.person.contact},
                        {"Cost",      to_string(v.cost)}
                        });
                }
            }
            if (recs.empty()) cout << "No matches.\n";
            else printRecords<string>(recs, 2);
            cout << "Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}


int main() {
    showLoginScreen();
    return 0;
}