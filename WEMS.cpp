#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <limits>
#include <regex>
#include <map>
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
    string vendorID = "V0000";
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
    int clientID = 0;
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
            ss >> clientID; ss.ignore();
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
            if (i < selectedVendors.size() - 1) vendors += ";";
        }
        line = to_string(clientID) + "," + person.name + "," + person.email + "," + person.contact + "," +
            partnerName + "," + weddingDate + "," + specialRequest + "," +
            to_string(guestCount) + "," + to_string(tableCount) + "," +
            selectedPackage + "," + venueBooked + "," + cateringSelected + "," +
            vendors + "," + to_string(totalPayment) + "," + to_string(amountPaid) + "," +
            paymentStatus;
    }
};

struct Package {
    string packageID = "P0000";
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
    string venueID = "V0000"; // Default value with prefix
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
    string caterID = "C0000";
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
    int paymentID = 0;
    int clientID = 0;
    float amountPaid = 0;
    string paymentDate;
    string paymentStatus;

    Payment() = default;

    Payment(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> paymentID; ss.ignore();
            ss >> clientID; ss.ignore();
            ss >> amountPaid; ss.ignore();
            getline(ss, paymentDate, ',');
            getline(ss, paymentStatus);
        }
    }

    void toString(string& line) const {
        line = to_string(paymentID) + "," + to_string(clientID) + "," + to_string(amountPaid) + "," + paymentDate + "," + paymentStatus;
    }
};

struct EventSchedule {
    int scheduleID = 0;
    int clientID = 0;
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
        line = to_string(scheduleID) + "," + to_string(clientID) + "," + weddingDate + "," + time + "," + activity;
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
        cout << "Debug: Input received: '" << input << "'" << endl; // Debug output
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
    char idStr[6];
    sprintf_s(idStr, "%04d", counter);
    string newID = prefix + idStr;

    // Verify uniqueness by checking if ID exists in file
    vector<T> list = getList<T>(filename);
    for (const auto& item : list) {
        string line;
        item.toString(line);
        stringstream ss(line);
        string existingID;
        getline(ss, existingID, ',');
        if (existingID == newID) {
            counter++;
            sprintf_s(idStr, "%04d", counter);
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
        //manageClient();
        break;
    case 2:
        manageEvent();
        break;
    case 3:
        manageVendor();
        break;
    case 4:
        //managePayment();
        break;
    case 5:
        manageAdmin();
        break;
    case 6:
        //manageEventMonitoring();
        break;
    case 7:
        //searchFun();
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
        newPackage.packageID = uniqueIDGenerator<Package>("P", "packages.csv");

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

        string generatedID = uniqueIDGenerator<Venue>("V", "venues.csv");
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
        string generatedID = uniqueIDGenerator<Cater>("C", "caterings.csv");
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
        newVendor.vendorID = uniqueIDGenerator<Vendor>("V", "vendors.csv");
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

int main() {
    showLoginScreen();
    return 0;
}