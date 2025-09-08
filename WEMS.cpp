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
#include <algorithm>
#include <cctype>
#include <conio.h>
using namespace std;



// Struct definitions
struct Person
{
    string firstName;
    string lastName;
    string email;
    string contact;

    Person() = default;

    Person(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, firstName, ',');
            getline(ss, lastName, ',');
            getline(ss, email, ',');
            getline(ss, contact);
        }
    }

    string fullName() const {
        return lastName.empty() ? firstName : (lastName + ", " + firstName);
    }

    void toString(string& line) const {
        line = lastName + "," + firstName + "," + email + "," + contact;
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

struct Vendor {
    string vendorID = "VD0000";
    Person person;
    string vendorType;
    float  cost = 0.00f;

    Vendor() = default;

    Vendor(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, vendorID, ',');
            getline(ss, vendorType, ',');
            getline(ss, person.lastName, ',');
            getline(ss, person.firstName, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            ss >> cost;
            if (!ss) cost = 0.0f;
        }
    }

    void toString(string& line) const {
        stringstream ss;
        ss << vendorID << "," << vendorType << ","
            << person.lastName << "," << person.firstName << ","
            << person.email << "," << person.contact << ","
            << fixed << setprecision(2) << cost;
        line = ss.str();
    }
};

struct Client {
    string clientID = "C0000";
    Person person;
    string partnerName;
    string weddingDate;
    string specialRequest;
    int    guestCount = 0;
    int    tableCount = 0;

    string selectedPackage;
    string venueBooked;
    string foodPackageID;
    string cateringSelected;
    vector<string> selectedVendors;

    float  totalPayment = 0.0f;
    float  amountPaid   = 0.0f;
    string paymentStatus = "UNPAID";

    Client() = default;

    Client(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);

        if (cols.size() >= 18) {
            clientID          = cols[0];
            person.firstName  = cols[1];
            person.lastName   = cols[2];
            person.email      = cols[3];
            person.contact    = cols[4];
            partnerName       = cols[5];
            weddingDate       = cols[6];
            specialRequest    = cols[7];
            try { guestCount  = stoi(cols[8]); }  catch (...) {}
            try { tableCount  = stoi(cols[9]); }  catch (...) {}
            selectedPackage   = cols[10];
            venueBooked       = cols[11];
            foodPackageID     = cols[12];
            cateringSelected  = cols[13];
            selectedVendors.clear();
            if (!cols[14].empty()) {
                string t; stringstream vs(cols[14]);
                while (getline(vs, t, ';')) if (!t.empty()) selectedVendors.push_back(t);
            }
            try { totalPayment = stof(cols[15]); } catch (...) {}
            try { amountPaid   = stof(cols[16]); } catch (...) {}
            paymentStatus     = cols[17];
        }
    }

    void toString(string& line) const {
        string vendors;
        size_t i;
        for (i = 0; i < selectedVendors.size(); ++i) {
            vendors += selectedVendors[i];
            if (i + 1 < selectedVendors.size()) vendors += ";";
        }
        stringstream ss;
        ss << clientID << ","
           << person.firstName << "," << person.lastName << ","
           << person.email << "," << person.contact << ","
           << partnerName << "," << weddingDate << "," << specialRequest << ","
           << guestCount << "," << tableCount << ","
           << selectedPackage << "," << venueBooked << "," << foodPackageID << "," << cateringSelected << ","
           << vendors << ","
           << fixed << setprecision(2) << totalPayment << ","
           << fixed << setprecision(2) << amountPaid << ","
           << paymentStatus;
        line = ss.str();
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

struct FoodPackage {
    string foodID = "FP0000";
    string appetizer;
    string mainCourse;
    string dessert;
    string provider;      // 可填“XX酒店厨房”/“某某外部餐饮”，不做强校验
    string billingMode;   // "PER_PERSON" / "PER_TABLE" / "FLAT"
    float  unitPrice = 0.0f;
    int    minGuests = 0; // 适用人数组合（可为0表示不限制）
    int    maxGuests = 0; // 0 表示不限制上限
    int    minTables = 0; // 适用桌数下限（可为0）
    string description;

    FoodPackage() = default;
    FoodPackage(const string& line) {
        if (line.empty()) return;
        stringstream ss(line);
        getline(ss, foodID, ',');
        getline(ss, appetizer, ',');
        getline(ss, mainCourse, ',');
        getline(ss, dessert, ',');
        getline(ss, provider, ',');
        getline(ss, billingMode, ',');
        ss >> unitPrice; ss.ignore();
        ss >> minGuests; ss.ignore();
        ss >> maxGuests; ss.ignore();
        ss >> minTables; ss.ignore();
        getline(ss, description);
    }
    void toString(string& line) const {
        line = foodID + "," + appetizer + "," + mainCourse + "," + dessert + "," + provider + "," + billingMode + "," +
            to_string(unitPrice) + "," + to_string(minGuests) + "," +
            to_string(maxGuests) + "," + to_string(minTables) + "," + description;
    }
};

struct FoodMenuItem {
    // 独立ID；父级关联到 FoodPackage.foodID
    string itemID = "FM0000";
    string foodID = "FP0000";

    // 类别：APPETIZER / MAIN / DESSERT / DRINK / OTHER
    string category;

    // 具体菜名，如 "Beef Wellington"
    string itemName;

    // 过敏原：用 | 分隔存（保持与你风格一致）
    string allergens;

    // 可选价差：大多数为 0，若勾选会在将来扩展用（当前可只展示）
    float priceDelta = 0.0f;

    // 备注（可空）
    string note;

    FoodMenuItem() = default;

    FoodMenuItem(const string& line) {
        if (line.empty()) return;
        // CSV: itemID, foodID, category, itemName, allergens, priceDelta, note
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);
        auto asFloat = [](const string& s)->float { try { return stof(s); } catch (...) { return 0.0f; } };

        if (cols.size() >= 6) {
            itemID = cols[0];
            foodID = cols[1];
            category = cols[2];
            itemName = cols[3];
            allergens = cols[4];
            priceDelta = asFloat(cols[5]);
            if (cols.size() >= 7) note = cols[6];
        }
    }

    void toString(string& line) const {
        line = itemID + "," + foodID + "," + category + "," + itemName + "," +
            allergens + "," + to_string(priceDelta) + "," + note;
    }
};

struct GuestRecord {
    string guestID;       // 形如 "G-R0123-001"
    string reservationID; // 归属的 reservation
    Person person;        // firstName/lastName/email/contact
    string rsvpStatus;
    string mealPreference;
    int    tableNumber;

    GuestRecord() : tableNumber(-1) {}

    GuestRecord(const string& line) {
        if (line.empty()) return;
        // CSV: guestID,reservationID,lastName,firstName,email,contact,rsvp,meal,table
        stringstream ss(line);
        getline(ss, guestID, ',');
        getline(ss, reservationID, ',');
        getline(ss, person.lastName, ',');
        getline(ss, person.firstName, ',');
        getline(ss, person.email, ',');
        getline(ss, person.contact, ',');
        getline(ss, rsvpStatus, ',');
        getline(ss, mealPreference, ',');
        ss >> tableNumber;
        if (!ss) tableNumber = -1;
    }

    void toString(string& line) const {
        stringstream ss;
        ss << guestID << "," << reservationID << ","
            << person.lastName << "," << person.firstName << ","
            << person.email << "," << person.contact << ","
            << rsvpStatus << "," << mealPreference << ","
            << tableNumber;
        line = ss.str();
    }
};

struct SeatingPlan {
    vector< vector<string> > seats; // seats[table][seat] = guestID (空串 = 空位)

    int tables() const {
        return (int)seats.size();
    }
    int seatsPerTable() const {
        return seats.empty() ? 0 : (int)seats[0].size();
    }
};

struct EventSchedule {
    string scheduleID = "S0000";
    string reservationID = "R0000"; // ★ 改：用预订绑定
    string weddingDate;              // 冗余保存，便于独立查看
    string time;                     // 格式建议 HH:MM
    string activity;
    int    orderNo = 0;              // 同时给一个手动排序权重

    EventSchedule() = default;

    // 新 CSV: 0 scheduleID,1 reservationID,2 weddingDate,3 time,4 activity,5 orderNo
    EventSchedule(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);

        if (cols.size() >= 5) {
            scheduleID = cols[0];
            reservationID = cols[1];
            weddingDate = cols[2];
            time = cols[3];
            activity = cols[4];
        }
        if (cols.size() >= 6) {
            try { orderNo = stoi(cols[5]); }
            catch (...) { orderNo = 0; }
        }
    }

    void toString(string& line) const {
        stringstream ss;
        ss << scheduleID << "," << reservationID << "," << weddingDate << ","
            << time << "," << activity << "," << orderNo;
        line = ss.str();
    }
};

struct Reservation {
    string reservationID = "R0000";
    string clientID = "C0000";    
    string weddingDate;                // YYYY-MM-DD
    string specialRequest;
    int    guestCount = 0;
    int    tableCount = 0;

    string selectedPackage;            // PK...
    string venueBooked;                // VN...
    string foodPackageID;              // FP...
    string cateringSelected;           // CT...
    vector<string> selectedVendors;

    float  totalPayment = 0.0f;              // 应付（不含折扣）
    float  amountPaid = 0.0f;               // 已付
    string paymentStatus = "UNPAID";        // UNPAID/PARTIAL/PAID

    //determine reservation status
    string reservationStatus = "ACTIVE";    // ACTIVE / CANCELLED
    string cancelReason;                 

    Reservation() = default;

    Reservation(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);

        if (cols.size() >= 14) {
            reservationID = cols[0];
            clientID = cols[1];
            weddingDate = cols[2];
            specialRequest = cols[3];
            try { guestCount = stoi(cols[4]); }
            catch (...) {}
            try { tableCount = stoi(cols[5]); }
            catch (...) {}
            selectedPackage = cols[6];
            venueBooked = cols[7];
            foodPackageID = cols[8];
            cateringSelected = cols[9];

            selectedVendors.clear();
            if (!cols[10].empty()) {
                string t; stringstream vs(cols[10]);
                while (getline(vs, t, ';')) if (!t.empty()) selectedVendors.push_back(t);
            }
            try { totalPayment = stof(cols[11]); }
            catch (...) {}
            try { amountPaid = stof(cols[12]); }
            catch (...) {}
            paymentStatus = cols[13];
        }
        if (cols.size() >= 15) reservationStatus = cols[14];
        if (cols.size() >= 16) cancelReason = cols[15];
    }

    void toString(string& line) const {
        string vendors;
        size_t i;
        for (i = 0; i < selectedVendors.size(); ++i) {
            vendors += selectedVendors[i];
            if (i + 1 < selectedVendors.size()) vendors += ";";
        }
        stringstream ss;
        ss << reservationID << "," << clientID << "," << weddingDate << "," << specialRequest << ","
            << guestCount << "," << tableCount << ","
            << selectedPackage << "," << venueBooked << "," << foodPackageID << "," << cateringSelected << ","
            << vendors << ","
            << fixed << setprecision(2) << totalPayment << ","
            << fixed << setprecision(2) << amountPaid << ","
            << paymentStatus << ","
            << reservationStatus << ","
            << cancelReason;
        line = ss.str();
    }
};

struct Payment {
    string paymentID = "PM0001";
    string reservationID = "R0000";
    string clientID = "C0000";

    float  amountPaid = 0.0f;     // 本次支付金额
    float  discountApplied = 0.0f; // 本次折扣金额（可为0）
    string paymentDate;           // YYYY-MM-DD
    string paymentMethod;         // Cash/Card/Transfer/...
    string note;                  // 备注
    string paymentStatus = "RECEIVED"; // RECEIVED/REFUND/...

    Payment() = default;

    Payment(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);
        // CSV: 0 id,1 reservationID,2 clientID,3 amount,4 discount,5 date,6 method,7 note,8 status
        if (cols.size() >= 9) {
            paymentID = cols[0];
            reservationID = cols[1];
            clientID = cols[2];
            try { amountPaid = stof(cols[3]); }
            catch (...) {}
            try { discountApplied = stof(cols[4]); }
            catch (...) {}
            paymentDate = cols[5];
            paymentMethod = cols[6];
            note = cols[7];
            paymentStatus = cols[8];
        }
    }

    void toString(string& line) const {
        stringstream ss;
        ss << paymentID << "," << reservationID << "," << clientID << ","
            << fixed << setprecision(2) << amountPaid << ","
            << fixed << setprecision(2) << discountApplied << ","
            << paymentDate << "," << paymentMethod << ","
            << note << "," << paymentStatus;
        line = ss.str();
    }
};

struct Feedback {
    string feedbackID = "FB0000";
    string reservationID = "R0000";   // 绑定某次预订
    string authorType;                 // "CLIENT" / "STAFF"
    string authorID;                   // clientID 或 admin.username
    int    rating = 0;                 // 1..5
    string comment;
    string createdAt;                  // YYYY-MM-DD

    Feedback() = default;

    // CSV: 0 id,1 reservationID,2 authorType,3 authorID,4 rating,5 createdAt,6 comment
    Feedback(const string& line) {
        if (line.empty()) return;
        vector<string> cols; string cell; stringstream ss(line);
        while (getline(ss, cell, ',')) cols.push_back(cell);

        if (cols.size() >= 6) {
            feedbackID = cols[0];
            reservationID = cols[1];
            authorType = cols[2];
            authorID = cols[3];
            try { rating = stoi(cols[4]); }
            catch (...) { rating = 0; }
            createdAt = cols[5];
        }
        if (cols.size() >= 7) comment = cols[6];
        if (rating < 0) rating = 0;
        if (rating > 5) rating = 5;
    }

    void toString(string& line) const {
        stringstream ss;
        ss << feedbackID << "," << reservationID << ","
            << authorType << "," << authorID << ","
            << rating << "," << createdAt << ","
            << comment;
        line = ss.str();
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
        " +-----------------------------------------------------------------+  \n"
        " | 1. Reservations (New / Manage / Checkout)                       | \n"
        " | 2. Catalog (Packages / Venues / Catering / Vendors)             |\n"
        " | 3. Operations (Guests / Schedules / Payments / Clients / Admin) |\n"
        " | 4. Search                                                       |  \n"
        " | 0. Exit                                                         |  \n"
        " +-----------------------------------------------------------------+  \n";


    const string ReservationMenu =
        " +-----------------------------------------+  \n"
        " |            Reservation Center           |  \n"
        " +-----------------------------------------+  \n"
        " | 1. New Reservation                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Cancel Reservation                   |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Modify Reservation                   |  \n"
        " +-----------------------------------------+  \n"
        " | 4. View All Reservations                |  \n"
        " +-----------------------------------------+  \n"
        " | 5. Checkout / Payment                   |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";

    const string CatalogMenu =
        " +-----------------------------------------+  \n"
        " |                 Catalog                 |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Package Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Vendor Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 5. Food Package Management              |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";

    const string FoodMenuMgmt =
        " +-----------------------------------------+  \n"
        " |           Food Menu Management          |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Menu Item                     |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Menu Item                     |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Menu Item                     |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show Items by Food ID                |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Catalog                      |  \n"
        " +-----------------------------------------+  \n";

    const string EventMenu =
        " +-----------------------------------------+  \n"
        " |            Event Management             |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Package Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Catalog                      |  \n"
        " +-----------------------------------------+  \n";

    const string PackageMenu =
        " +-----------------------------------------+  \n"
        " |        Wedding Package Management       |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Packages                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Catalog                      |  \n"
        " +-----------------------------------------+  \n";

    const string VenueMenu =
        " +-----------------------------------------+  \n"
        " |            Venue Management             |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Venues                      |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Catalog                      |  \n"
        " +-----------------------------------------+  \n";

    const string CaterMenu =
        " +-----------------------------------------+  \n"
        " |           Catering Management           |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Catering                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to catalog                      |  \n"
        " +-----------------------------------------+  \n";


    const string VendorMenu =
        " +-----------------------------------------+  \n"
        " |            Vendor Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Vendors                     |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Catalog                      |  \n"
        " +-----------------------------------------+  \n";


    const string OperationsMenu =
        " +-----------------------------------------+  \n"
        " |                Operations               |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Payment Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Client Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 5. Admin Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";

    const string ClientMenu =
        " +-----------------------------------------+  \n"
        " |            Client Management            |  \n"
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
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";

    const string PaymentMenu =
        " +-----------------------------------------+  \n"
        " |           Payment Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Payments                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";


    const string AdminMenu =
        " +-----------------------------------------+  \n"
        " |             Admin Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Admin                       |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";


    const string EventMonitoringMenu =
        " +-----------------------------------------+  \n"
        " |            Event Monitoring             |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";


    const string GuestMenu =
        " +-----------------------------------------+  \n"
        " |             Guest Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Import Guest List                    |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Guest RSVP                    |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Show Guest List                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Assign Seating                       |  \n"
        " +-----------------------------------------+  \n"
        " | 5. Show Seating Plan                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";



    const string ScheduleMenu =
        " +-----------------------------------------+  \n"
        " |        Event Schedule Management        |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Remove Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Schedules                   |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Operations                   |  \n"
        " +-----------------------------------------+  \n";


    const string SearchMenu =
        " +-----------------------------------------+  \n"
        " |          Search Functionality           |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Search Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Search Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Search Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+  \n";
};

void trim(string& s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) a++;
    while (b > a && isspace((unsigned char)s[b - 1])) b--;
    s = s.substr(a, b - a);
}

int toIntSafe(const string& s) {
    try { return s.empty() ? 0 : stoi(s); }
    catch (...) { return 0; }
}

float toFloatSafe(const string& s) {
    try { return s.empty() ? 0.0f : stof(s); }
    catch (...) { return 0.0f; }
}


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

template <typename T>
void loadList(const string& filename, vector<T>& list) {
    list.clear();
    ifstream fin(filename);
    if (!fin.is_open()) return;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) list.push_back(T(line));
    }
}

// Template function for input validation
template <typename T>
bool validateInput(const T& input, const string& type = "") {
    if constexpr (is_same_v<T, string>) {
        //cout << "Debug: Input received: '" << input << "'" << endl; // Debug output
        if (type == "email") 
        {
            regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
            return !input.empty() && regex_match(input, emailPattern);
        }
        else if (type == "date") 
        {
            regex datePattern(R"(\d{4}-\d{2}-\d{2})");
            if (!regex_match(input, datePattern)) 
                return false;
            stringstream ss(input);

            int y, m, d; 
            char a, b;
            ss >> y >> a >> m >> b >> d;

            if (ss.fail() || a != '-' || b != '-') 
                return false;
            if (y < 2025 || y > 2050)
                return false;
            if (m < 1 || m > 12) 
                return false;
            if (d < 1 || d > 31) 
                return false;
            if (m == 2) 
            {
                bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
                return d <= (leap ? 29 : 28);
            }
            if (m == 4 || m == 6 || m == 9 || m == 11) 
                return d <= 30;
            return true;
        }
        else if (type == "time") 
        {
            regex timePattern(R"(\d{2}:\d{2})");
            if (!regex_match(input, timePattern)) return false;
            stringstream ss(input);
            int H, M; char c;
            ss >> H >> c >> M;
            if (ss.fail() || c != ':') return false;
            return H >= 0 && H <= 23 && M >= 0 && M <= 59;
        }
        else if (type == "non_empty") 
        {
            return !input.empty() && input.find_first_not_of(" \t\n") != string::npos;
        }
        return !input.empty();
        }
    else if constexpr (is_integral_v<T> || is_floating_point_v<T>) {
        return input >= 0;
    }
    return true;
}

// Template function to get validated input
template <typename T>
T getValidatedInput(const string& prompt, const string& type = "", const string& errorMsg = "\n Invalid input. Please try again: ") 
{
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
    string key = prefix + "@" + filename;

    // Initialize from file once per (prefix, file)
    if (!idCounters.count(key)) {
        int maxID = 0;
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            string id; stringstream ss(line);
            getline(ss, id, ',');
            if (id.rfind(prefix, 0) == 0) {
                try {
                    int n = stoi(id.substr(prefix.size()));
                    if (n > maxID) maxID = n;
                }
                catch (...) { /* ignore malformed IDs */ }
            }
        }
        idCounters[key] = maxID;
    }

    // Generate and ensure uniqueness against current file contents
    vector<T> existing = getList<T>(filename);
    while (true) {
        int& counter = idCounters[key];
        counter++;

        // zero-pad to 4 digits without snprintf/sprintf
        ostringstream os;
        os << setw(4) << setfill('0') << counter;
        string candidate = prefix + os.str();

        bool clash = false;
        for (const auto& item : existing) {
            string line, existingID;
            item.toString(line);
            stringstream ss(line);
            getline(ss, existingID, ',');
            if (existingID == candidate) { clash = true; break; }
        }
        if (!clash) return candidate;
    }
}

template<typename T>
bool anyEqualMember(const vector<T>& vec, string T::* member, const string& id) {
    size_t i;
    for (i = 0; i < vec.size(); ++i) {
        if (vec[i].*member == id) return true;
    }
    return false;
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

template <typename T, typename Pred> T* findPtr(vector<T>& vec, Pred pred) {
    auto it = find_if(vec.begin(), vec.end(), pred);
    return (it == vec.end()) ? nullptr : &(*it);
}



void trim(string& s);
int toIntSafe(const string& s);
float toFloatSafe(const string& s);

bool login();

void showLoginScreen();
void showMainScreen();
void reservationCenter();
void catalog();
void operations(); 
void searchFun();

void managePackage();
void manageVenue();
void manageCatering();
void manageVendor();
void manageFoodPackage();

void manageAdmin();
void manageClient();
void managePayment();
void manageGuest();
void manageSchedule();

void clearScreen();
void pauseLine();
bool isBackKey(const string& s);
bool isYes(const string& s);
bool confirmAction(const string& msg);
string myr(float v);

string joinVec(const vector<string>& v, char sep = ';');
vector<string> splitIds(const string& s, char sep = ';');
float computeReservationTotal(const Reservation& r, const vector<Package>& packages, const vector<Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors, const vector<FoodPackage>& foods);
string normalizeBilling(string s);
string nextGuestId(const string& reservationID, const vector<GuestRecord>& all);

float computeClientTotal(const Client& c, const vector<Package>& packages, const vector<Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors, const vector<FoodPackage>& foods);
void checkoutWizard();
void checkoutReservationWizard();
string maskedInput(const string& prompt);
void adminRun();


//for display many in one time
string joinVec(const vector<string>& v, char sep) {
    string out;
    for (size_t i = 0; i < v.size(); ++i) {
        out += v[i];
        if (i + 1 < v.size()) out += sep;
    }
    return out;
}

//inverse of joinvec
vector<string> splitIds(const string& s, char sep) {
    vector<string> ids;
    string item;
    stringstream ss(s);
    while (getline(ss, item, sep)) {
        if (!item.empty()) ids.push_back(item);
    }
    return ids;
}


//admin section
string maskedInput(const string& prompt)
{
    cout << prompt;
    string pwd;

    while (true) {
        int ch = _getch();         
        if (ch == 13) {           
            cout << "\n";
            break;
        }
        if (ch == 8) {           
            if (!pwd.empty()) {
                pwd.pop_back();
                cout << "\b \b";
            }
            continue;
        }
        if (ch == 0 || ch == 224) 
        { 
            _getch();
            continue;
        }
        pwd.push_back(char(ch));
        cout << '*';
    }
    return pwd;
}

void adminRun()
{
    ifstream f("admins.csv");
    if (!f.is_open())
    {
        ofstream out("admins.csv");

        if (out.is_open())
        {
            out << "admin,admin\n";
            out.close();
        }
    }
}


//Basic UI helpers 
void clearScreen()
{
    system("cls");
}

void pauseLine() {
    cout << "\nPress Enter...";
    cin.get();
}

bool isBackKey(const string& s) {
    return (s == "0" || s == "b" || s == "B");
}

bool isYes(const string& s) {
    return !s.empty() && (s[0] == 'Y' || s[0] == 'y');
}

bool confirmAction(const string& msg) {
    cout << msg << " (Y/N): ";
    string s; getline(cin, s);
    return isYes(s);
}

string myr(float v) {
    stringstream ss;
    ss << "MYR " << fixed << setprecision(2) << v;
    return ss.str();
}


//client section
float computeClientTotal(const Client& c, const vector<Package>& packages, const vector
    <Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors, const vector<FoodPackage>& foods)
{
    float total = 0.0f;
    size_t i;

    if (!c.selectedPackage.empty()) {
        for (i = 0; i < packages.size(); ++i) {
            if (packages[i].packageID == c.selectedPackage) {
                total += packages[i].price;
                break;
            }
        }
    }
    else {
        if (!c.venueBooked.empty()) {
            for (i = 0; i < venues.size(); ++i) {
                if (venues[i].venueID == c.venueBooked) {
                    total += venues[i].rentalCost;
                    break;
                }
            }
        }
        if (!c.foodPackageID.empty()) {
            for (i = 0; i < foods.size(); ++i) {
                if (foods[i].foodID == c.foodPackageID) {
                    if (foods[i].billingMode == "PER_PERSON")
                        total += foods[i].unitPrice * (c.guestCount > 0 ? c.guestCount : 0);
                    else if (foods[i].billingMode == "PER_TABLE")
                        total += foods[i].unitPrice * (c.tableCount > 0 ? c.tableCount : 0);
                    else
                        total += foods[i].unitPrice;
                    break;
                }
            }
        }
        else if (!c.cateringSelected.empty()) {
            for (i = 0; i < caters.size(); ++i) {
                if (caters[i].caterID == c.cateringSelected) {
                    int g = (c.guestCount > 0 ? c.guestCount : 0);
                    total += caters[i].costPerPerson * g;
                    break;
                }
            }
        }
    }

    size_t k;
    for (k = 0; k < c.selectedVendors.size(); ++k) {
        for (i = 0; i < vendors.size(); ++i) {
            if (vendors[i].vendorID == c.selectedVendors[k]) {
                total += vendors[i].cost;
                break;
            }
        }
    }
    return total;
}

//catalog section
string normalizeBilling(string s) {
    string t; t.reserve(s.size());
    size_t i;
    for (i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == ' ' || c == '-' || c == '\t') continue;
        if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
        t.push_back(c);
    }
    if (t == "1" || t == "PERPERSON" || t == "PER_PERSON") return "PER_PERSON";
    if (t == "2" || t == "PERTABLE" || t == "PER_TABLE")  return "PER_TABLE";
    if (t == "3" || t == "FLAT")                          return "FLAT";
    return "PER_PERSON";
}

bool isIdInUse(const string& kind, const string& id) {
    // kind: "PACKAGE" | "VENUE" | "CATER" | "VENDOR" | "FOOD"
    vector<Reservation> rs = getList<Reservation>("reservations.csv");
    vector<Client>      cs = getList<Client>("clients.csv");

    size_t i, k;

    // 查 Reservation
    for (i = 0; i < rs.size(); ++i) {
        if (kind == "PACKAGE" && rs[i].selectedPackage == id) return true;
        if (kind == "VENUE" && rs[i].venueBooked == id) return true;
        if (kind == "CATER" && rs[i].cateringSelected == id) return true;
        if (kind == "FOOD" && rs[i].foodPackageID == id) return true;
        if (kind == "VENDOR") {
            for (k = 0; k < rs[i].selectedVendors.size(); ++k)
                if (rs[i].selectedVendors[k] == id) return true;
        }
    }

    // 查 Client（兼容历史数据）
    for (i = 0; i < cs.size(); ++i) {
        if (kind == "PACKAGE" && cs[i].selectedPackage == id) return true;
        if (kind == "VENUE" && cs[i].venueBooked == id) return true;
        if (kind == "CATER" && cs[i].cateringSelected == id) return true;
        if (kind == "FOOD" && cs[i].foodPackageID == id) return true;
        if (kind == "VENDOR") {
            for (k = 0; k < cs[i].selectedVendors.size(); ++k)
                if (cs[i].selectedVendors[k] == id) return true;
        }
    }
    return false;
}


//operation section
string nextGuestId(const string& reservationID, const vector<GuestRecord>& all) {
    int maxSeq = 0;
    size_t i;
    for (i = 0; i < all.size(); ++i) {
        if (all[i].reservationID == reservationID) {
            const string& gid = all[i].guestID;
            string prefix = string("G-") + reservationID + "-";
            if (gid.size() > prefix.size()) {
                bool ok = true;
                size_t j;
                for (j = 0; j < prefix.size(); ++j) if (gid[j] != prefix[j]) { ok = false; break; }
                if (ok) {
                    int val = 0;
                    j = prefix.size();
                    for (; j < gid.size(); ++j) {
                        char c = gid[j];
                        if (c < '0' || c > '9') { ok = false; break; }
                        val = val * 10 + (c - '0');
                    }
                    if (ok && val > maxSeq) maxSeq = val;
                }
            }
        }
    }
    int next = maxSeq + 1;
    string s = to_string(next);
    if (next < 10) s = "00" + s;
    else if (next < 100) s = "0" + s;
    return string("G-") + reservationID + "-" + s;
}

string nextGuestIDForReservation(const string& reservationID, const vector<GuestRecord>& allGuests) {
    int maxSeq = 0;
    size_t i;
    for (i = 0; i < allGuests.size(); ++i) {
        if (allGuests[i].reservationID == reservationID) {
            // 解析尾部 NNN
            const string& gid = allGuests[i].guestID; // "G-<res>-NNN"
            size_t pos = gid.rfind('-');
            if (pos != string::npos && pos + 1 < gid.size()) {
                int n = 0;
                // 手动 atoi（稳妥）
                string tail = gid.substr(pos + 1);
                stringstream ssn(tail);
                ssn >> n;
                if (ssn) {
                    if (n > maxSeq) maxSeq = n;
                }
            }
        }
    }
    int nextSeq = maxSeq + 1;
    // 补足 3 位
    stringstream ss;
    ss << "G-" << reservationID << "-";
    if (nextSeq < 10) ss << "00";
    else if (nextSeq < 100) ss << "0";
    ss << nextSeq;
    return ss.str();
}

//reservation payment section
float computeReservationTotal(const Reservation& r, const vector<Package>& packages, const vector<Venue>& venues, const vector<Cater>& caters, const vector<Vendor>& vendors, const vector<FoodPackage>& foods)
{
    float total = 0.0f;

    if (!r.selectedPackage.empty()) 
    {
        for (const auto& p : packages)
            if (p.packageID == r.selectedPackage) 
            { 
                total += p.price; 
                break; 
            }
    }
    else {
        if (!r.venueBooked.empty()) {
            for (const auto& v : venues)
                if (v.venueID == r.venueBooked) { total += v.rentalCost; break; }
        }
        if (!r.foodPackageID.empty()) {
            for (const auto& f : foods)
                if (f.foodID == r.foodPackageID) {
                    if (f.billingMode == "PER_PERSON") total += f.unitPrice * max(0, r.guestCount);
                    else if (f.billingMode == "PER_TABLE") total += f.unitPrice * max(0, r.tableCount);
                    else total += f.unitPrice; // FLAT
                    break;
                }
        }
        else if (!r.cateringSelected.empty()) {
            for (const auto& c : caters)
                if (c.caterID == r.cateringSelected) {
                    bool multiplyGuests = true; // 你已经决定真实计价乘人数
                    total += multiplyGuests ? (c.costPerPerson * max(0, r.guestCount))
                        : c.costPerPerson;
                    break;
                }
        }
    }

    for (const auto& vid : r.selectedVendors) {
        for (const auto& v : vendors)
            if (v.vendorID == vid) { total += v.cost; break; }
    }
    return total;
}

void recomputeReservationPayments(vector<Reservation>& reservations, const vector<Payment>& payments)
{
    map<string, float> sumsPaid, sumsDiscount;
    for (const auto& p : payments) {
        sumsPaid[p.reservationID] += p.amountPaid;
        sumsDiscount[p.reservationID] += p.discountApplied;
    }
    for (auto& r : reservations) {
        r.amountPaid = sumsPaid[r.reservationID];
        float effectiveTotal = max(0.0f, r.totalPayment - sumsDiscount[r.reservationID]);
        if (r.amountPaid <= 0.0f) r.paymentStatus = "UNPAID";
        else if (r.amountPaid + 1e-3 >= effectiveTotal) r.paymentStatus = "PAID";
        else r.paymentStatus = "PARTIAL";
    }
}

void checkoutWizard() {
    // ========== 0) 标题 ==========
    system("cls");
    cout << "Checkout / Payment (by Reservation)\n";

    // ========== 1) 输入 ReservationID ==========
    string rid = getValidatedInput<string>("Enter Reservation ID: ", "non_empty");

    // ========== 2) 一次性加载所需数据（仍复用你现有 getList） ==========
    vector<Client>       clients = getList<Client>("clients.csv");
    vector<Reservation>  reservations = getList<Reservation>("reservations.csv");
    vector<Package>      packages = getList<Package>("packages.csv");
    vector<Venue>        venues = getList<Venue>("venues.csv");
    vector<Cater>        caters = getList<Cater>("caterings.csv");
    vector<Vendor>       vendors = getList<Vendor>("vendors.csv");
    vector<FoodPackage>  foods = getList<FoodPackage>("food_packages.csv");
    vector<Payment>      payments = getList<Payment>("payments.csv");

    // ========== 3) 查找 Reservation 与 Client（展示名） ==========
    int rIdx = -1;
    size_t i;
    for (i = 0; i < reservations.size(); ++i) {
        if (reservations[i].reservationID == rid) { rIdx = (int)i; break; }
    }
    if (rIdx < 0) { cout << "Reservation not found.\nPress Enter..."; cin.get(); return; }
    Reservation& r = reservations[(size_t)rIdx];

    string clientName = r.clientID;
    for (i = 0; i < clients.size(); ++i) {
        if (clients[i].clientID == r.clientID) {
            if (clients[i].person.lastName.size() > 0)
                clientName = clients[i].person.lastName + ", " + clients[i].person.firstName;
            else
                clientName = clients[i].person.firstName;
            break;
        }
    }

    // ========== 4) 基础输入校验（计费模式 vs 人数/桌数） ==========
    // 校验 weddingDate 格式（沿用你现有 validateInput）
    if (!validateInput<string>(r.weddingDate, "date")) {
        cout << "Invalid wedding date stored in reservation.\nPress Enter...";
        cin.get();
        return;
    }
    // 若选了 FoodPackage，则校验它的计费模式需要的数量是否就绪
    if (r.foodPackageID.size() > 0) {
        int foodIdx = -1;
        for (i = 0; i < foods.size(); ++i) {
            if (foods[i].foodID == r.foodPackageID) { foodIdx = (int)i; break; }
        }
        if (foodIdx >= 0) {
            string mode = foods[(size_t)foodIdx].billingMode;
            if (mode == "PER_PERSON" && r.guestCount <= 0) {
                cout << "Food package is PER_PERSON, but guestCount <= 0.\nPress Enter...";
                cin.get();
                return;
            }
            if (mode == "PER_TABLE" && r.tableCount <= 0) {
                cout << "Food package is PER_TABLE, but tableCount <= 0.\nPress Enter...";
                cin.get();
                return;
            }
        }
    }

    // ========== 5) 计算小计，并同步回 Reservation.totalPayment ==========
    float subtotal = computeReservationTotal(r, packages, venues, caters, vendors, foods);
    r.totalPayment = subtotal;

    // ========== 6) 汇总历史付款与折扣 ==========
    float paidPrev = 0.0f, discPrev = 0.0f;
    for (i = 0; i < payments.size(); ++i) {
        if (payments[i].reservationID == r.reservationID) {
            paidPrev += payments[i].amountPaid;
            discPrev += payments[i].discountApplied;
        }
    }

    // ========== 7) 生成 Food 行（展示用） ==========
    string foodLine = "-";
    if (r.foodPackageID.size() > 0) {
        int foodIdx = -1;
        for (i = 0; i < foods.size(); ++i) {
            if (foods[i].foodID == r.foodPackageID) { foodIdx = (int)i; break; }
        }
        if (foodIdx >= 0) {
            string qty = "1";
            if (foods[(size_t)foodIdx].billingMode == "PER_PERSON") qty = to_string(r.guestCount);
            else if (foods[(size_t)foodIdx].billingMode == "PER_TABLE") qty = to_string(r.tableCount);
            foodLine = r.foodPackageID + " (" + foods[(size_t)foodIdx].billingMode + " x " + qty + ")";
        }
        else {
            foodLine = r.foodPackageID;
        }
    }
    else if (r.cateringSelected.size() > 0) {
        foodLine = r.cateringSelected + " (Cater)";
    }

    // ========== 8) 组装并渲染 INVOICE（单框，函数内就地渲染） ==========
    vector< pair<string, string> > inv;
    inv.push_back(pair<string, string>("Reservation ID", r.reservationID));
    inv.push_back(pair<string, string>("Client", clientName));
    inv.push_back(pair<string, string>("Wedding Date", r.weddingDate));
    inv.push_back(pair<string, string>("Guests / Tables", to_string(r.guestCount) + " / " + to_string(r.tableCount)));
    inv.push_back(pair<string, string>("Package", r.selectedPackage.size() ? r.selectedPackage : string("-")));
    inv.push_back(pair<string, string>("Venue", r.venueBooked.size() ? r.venueBooked : string("-")));
    inv.push_back(pair<string, string>("Food", foodLine));
    inv.push_back(pair<string, string>("Vendors", joinVec(r.selectedVendors, ';')));
    inv.push_back(pair<string, string>("Subtotal", myr(subtotal)));
    inv.push_back(pair<string, string>("Discounts (so far)", myr(discPrev)));
    inv.push_back(pair<string, string>("Paid (so far)", myr(paidPrev)));
    {
        float effective = subtotal - discPrev; if (effective < 0.0f) effective = 0.0f;
        float due = effective - paidPrev; if (due < 0.0f) due = 0.0f;
        inv.push_back(pair<string, string>("Effective Due", myr(due)));
    }

    // 渲染方框（就地渲染，不额外抽函数）
    {
        int w = 78; if (w < 40) w = 40; if (w > 120) w = 120;
        string title = "INVOICE";
        cout << "+" << string(w - 2, '-') << "+\n";
        int pad = w - 2 - (int)title.size(); if (pad < 0) pad = 0;
        int lpad = pad / 2; int rpad = pad - lpad;
        cout << "|" << string(lpad, ' ') << title << string(rpad, ' ') << "|\n";
        cout << "|" << string(w - 2, ' ') << "|\n";

        int labelMax = 0;
        for (i = 0; i < inv.size(); ++i)
            if ((int)inv[i].first.size() > labelMax) labelMax = (int)inv[i].first.size();
        if (labelMax > 22) labelMax = 22;
        int valueWidth = w - 2 - 2 - labelMax - 3; if (valueWidth < 10) valueWidth = 10;

        for (i = 0; i < inv.size(); ++i) {
            string L = inv[i].first;
            string R = inv[i].second;
            if ((int)L.size() > labelMax) L = L.substr(0, labelMax);
            size_t pos = 0;
            while (true) {
                string chunk;
                if (pos >= R.size()) chunk = "";
                else {
                    size_t remain = R.size() - pos;
                    size_t take = (size_t)valueWidth;
                    if (remain < take) take = remain;
                    chunk = R.substr(pos, take);
                    pos += take;
                }
                cout << "| " << setw(labelMax) << left << L << " : "
                    << setw(valueWidth) << left << chunk << " |\n";
                if (pos >= R.size()) break;
                L = "";
            }
        }
        cout << "+" << string(w - 2, '-') << "+\n";
    }

    // ========== 9) 折扣与是否立即付款 ==========
    float discountNew = getValidatedInput<float>("Enter discount amount (0 for none): ");
    if (discountNew < 0.0f) discountNew = 0.0f;

    float effectiveTotal = subtotal - (discPrev + discountNew);
    if (effectiveTotal < 0.0f) effectiveTotal = 0.0f;
    float amountDue = effectiveTotal - paidPrev;
    if (amountDue < 0.0f) amountDue = 0.0f;

    string payNow = getValidatedInput<string>("Pay now? (Y/N): ", "non_empty");
    if (payNow != "Y" && payNow != "y") {
        // 虽不付款，也要保存更新后的小计
        recomputeReservationPayments(reservations, payments);
        saveList(reservations, "reservations.csv");
        cout << "No payment recorded. Press Enter...";
        cin.get();
        return;
    }

    // ========== 10) 入账（Payment 追加） ==========
    string method = getValidatedInput<string>("Payment method (Cash/Card/Transfer/...): ", "non_empty");
    float amount = getValidatedInput<float>("Payment amount (0 = pay full due): ");
    if (amount <= 0.0f) amount = amountDue;
    if (amount > amountDue) amount = amountDue;

    Payment p;
    p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
    p.reservationID = r.reservationID;
    p.clientID = r.clientID;
    p.amountPaid = amount;
    p.discountApplied = discountNew;
    p.paymentDate = getValidatedInput<string>("Payment date (YYYY-MM-DD): ", "date");
    p.paymentMethod = method;
    p.note = "checkout";
    p.paymentStatus = "RECEIVED";

    payments.push_back(p);
    recomputeReservationPayments(reservations, payments);
    saveList(payments, "payments.csv");
    saveList(reservations, "reservations.csv");

    // ========== 11) 渲染 RECEIPT（单框，函数内就地渲染） ==========
    float paidNow = 0.0f, discNow = 0.0f;
    for (i = 0; i < payments.size(); ++i) {
        if (payments[i].reservationID == r.reservationID) {
            paidNow += payments[i].amountPaid;
            discNow += payments[i].discountApplied;
        }
    }
    float effNow = subtotal - discNow; if (effNow < 0.0f) effNow = 0.0f;
    float dueNow = effNow - paidNow;  if (dueNow < 0.0f) dueNow = 0.0f;

    vector< pair<string, string> > rec;
    rec.push_back(pair<string, string>("Payment ID", p.paymentID));
    rec.push_back(pair<string, string>("Reservation ID", r.reservationID));
    rec.push_back(pair<string, string>("Client", clientName));
    rec.push_back(pair<string, string>("Method", p.paymentMethod));
    rec.push_back(pair<string, string>("Amount", myr(p.amountPaid)));
    rec.push_back(pair<string, string>("New Discount (this txn)", myr(discountNew)));
    rec.push_back(pair<string, string>("Paid (so far)", myr(paidNow)));
    rec.push_back(pair<string, string>("Discounts (so far)", myr(discNow)));
    rec.push_back(pair<string, string>("Effective Due", myr(dueNow)));

    {
        int w = 78; if (w < 40) w = 40; if (w > 120) w = 120;
        string title = "RECEIPT";
        cout << "+" << string(w - 2, '-') << "+\n";
        int pad = w - 2 - (int)title.size(); if (pad < 0) pad = 0;
        int lpad = pad / 2; int rpad = pad - lpad;
        cout << "|" << string(lpad, ' ') << title << string(rpad, ' ') << "|\n";
        cout << "|" << string(w - 2, ' ') << "|\n";

        int labelMax = 0;
        for (i = 0; i < rec.size(); ++i)
            if ((int)rec[i].first.size() > labelMax) labelMax = (int)rec[i].first.size();
        if (labelMax > 22) labelMax = 22;
        int valueWidth = w - 2 - 2 - labelMax - 3; if (valueWidth < 10) valueWidth = 10;

        for (i = 0; i < rec.size(); ++i) {
            string L = rec[i].first;
            string R = rec[i].second;
            if ((int)L.size() > labelMax) L = L.substr(0, labelMax);
            size_t pos = 0;
            while (true) {
                string chunk;
                if (pos >= R.size()) chunk = "";
                else {
                    size_t remain = R.size() - pos;
                    size_t take = (size_t)valueWidth;
                    if (remain < take) take = remain;
                    chunk = R.substr(pos, take);
                    pos += take;
                }
                cout << "| " << setw(labelMax) << left << L << " : "
                    << setw(valueWidth) << left << chunk << " |\n";
                if (pos >= R.size()) break;
                L = "";
            }
        }
        cout << "+" << string(w - 2, '-') << "+\n";
    }

    cout << "Payment recorded. Press Enter...";
    cin.get();
}

void checkoutReservationWizard()
{
    // 载入数据
    vector<Reservation> reservations = getList<Reservation>("reservations.csv");
    vector<Client>      clients = getList<Client>("clients.csv");
    vector<Package>     packages = getList<Package>("packages.csv");
    vector<Venue>       venues = getList<Venue>("venues.csv");
    vector<Cater>       caters = getList<Cater>("caterings.csv");
    vector<Vendor>      vendors = getList<Vendor>("vendors.csv");
    vector<FoodPackage> foods = getList<FoodPackage>("food_packages.csv");
    vector<FoodMenuItem> menuItems = getList<FoodMenuItem>("food_menu_items.csv");
    vector<Payment>     payments = getList<Payment>("payments.csv");

    // 简单列表，帮助用户选择 Reservation
    system("cls");
    cout << "== Checkout / Payment ==\n";
    if (reservations.empty()) { cout << "No reservations.\nPress Enter..."; cin.get(); return; }

    // 展示关键字段
    size_t i;
    for (i = 0; i < reservations.size(); ++i) {
        string cname = reservations[i].clientID;
        size_t j;
        for (j = 0; j < clients.size(); ++j) {
            if (clients[j].clientID == reservations[i].clientID) {
                cname = clients[j].person.fullName();
                break;
            }
        }
        cout << " [" << reservations[i].reservationID << "] "
            << cname << "  " << reservations[i].weddingDate
            << "  status=" << reservations[i].paymentStatus << "\n";
    }

    // 选择 ID
    cout << "\n Enter Reservation ID: ";
    string rid; getline(cin, rid);

    int idx = -1;
    for (i = 0; i < reservations.size(); ++i)
        if (reservations[i].reservationID == rid) { idx = (int)i; break; }
    if (idx < 0) { cout << "Reservation not found.\nPress Enter..."; cin.get(); return; }

    // 当前订单与客户
    Reservation r = reservations[idx];  // 本地副本，便于操作
    Client c; bool foundClient = false;
    for (i = 0; i < clients.size(); ++i) if (clients[i].clientID == r.clientID) { c = clients[i]; foundClient = true; break; }
    if (!foundClient) { cout << "Client not found for this reservation.\nPress Enter..."; cin.get(); return; }

    // 重算总额（确保一致）
    float recomputed = computeReservationTotal(r, packages, venues, caters, vendors, foods);
    r.totalPayment = recomputed;

    // 汇总已付与折扣
    float sumPaid = 0.0f, sumDisc = 0.0f;
    for (i = 0; i < payments.size(); ++i) {
        if (payments[i].reservationID == r.reservationID) {
            sumPaid += payments[i].amountPaid;
            sumDisc += payments[i].discountApplied;
        }
    }
    r.amountPaid = sumPaid;
    float effectiveTotal = r.totalPayment - sumDisc;
    if (effectiveTotal < 0.0f) effectiveTotal = 0.0f;
    if (r.amountPaid <= 0.0f) r.paymentStatus = "UNPAID";
    else if (r.amountPaid + 1e-3 >= effectiveTotal) r.paymentStatus = "PAID";
    else r.paymentStatus = "PARTIAL";

    // ===== 打印发票（一个方框内） =====
    {
        string cname = c.person.fullName();
        string foodLine = r.foodPackageID.empty()
            ? (r.cateringSelected.empty() ? "-" : r.cateringSelected + " (Cater)")
            : r.foodPackageID + " (FoodPkg)";

        // 预构造 Vendors 文本
        string vendorsTxt = joinVec(r.selectedVendors, ';');

        // 方框打印
        cout << "\n+=================================================================+\n";
        cout << "|                             INVOICE                              |\n";
        cout << "+=================================================================+\n";
        cout << "|  Reservation ID : " << setw(55) << left << r.reservationID << "|\n";
        cout << "|  Client         : " << setw(55) << left << cname << "|\n";
        cout << "|  Wedding Date   : " << setw(55) << left << r.weddingDate << "|\n";
        cout << "+-----------------------------------------------------------------+\n";
        cout << "|  Selections                                                    |\n";
        cout << "|   - Package      : " << setw(48) << left << r.selectedPackage << "|\n";
        cout << "|   - Venue        : " << setw(48) << left << r.venueBooked << "|\n";
        cout << "|   - Food/Cater   : " << setw(48) << left << foodLine << "|\n";
        cout << "|   - Vendors      : " << setw(48) << left << vendorsTxt << "|\n";
        cout << "|   - Guests/Tables: " << setw(48) << left << (to_string(r.guestCount) + "/" + to_string(r.tableCount)) << "|\n";
        cout << "+-----------------------------------------------------------------+\n";

        // 如选择了 FoodPackage，显示其明细
        if (!r.foodPackageID.empty()) {
            cout << "|  Menu Details (" << setw(54) << left << r.foodPackageID << "|\n";
            bool any = false;
            for (i = 0; i < menuItems.size(); ++i) {
                if (menuItems[i].foodID == r.foodPackageID) {
                    any = true;
                    string line = string("   - [") + menuItems[i].category + "] " + menuItems[i].itemName;
                    if (!menuItems[i].allergens.empty()) line += string(" (Allergens: ") + menuItems[i].allergens + ")";
                    if (menuItems[i].priceDelta > 0.0001f) {
                        stringstream tmp; tmp << " (+RM" << fixed << setprecision(2) << menuItems[i].priceDelta << ")";
                        line += tmp.str();
                    }
                    if (!menuItems[i].note.empty()) line += string(" - ") + menuItems[i].note;

                    if (line.size() > 61) line = line.substr(0, 58) + "...";
                    cout << "|  " << setw(61) << left << line << "|\n";
                }
            }
            if (!any) {
                cout << "|  " << setw(61) << left << "(package has no detailed items listed)" << "|\n";
            }
            cout << "+-----------------------------------------------------------------+\n";
        }

        // 金额区域
        stringstream ssT, ssP, ssD, ssE;
        ssT << fixed << setprecision(2) << r.totalPayment;
        ssP << fixed << setprecision(2) << r.amountPaid;
        ssD << fixed << setprecision(2) << sumDisc;
        ssE << fixed << setprecision(2) << (effectiveTotal - r.amountPaid < 0 ? 0.0f : (effectiveTotal - r.amountPaid));

        cout << "|  Total      : RM " << setw(48) << left << ssT.str() << "|\n";
        cout << "|  Discount   : RM " << setw(48) << left << ssD.str() << "|\n";
        cout << "|  Paid       : RM " << setw(48) << left << ssP.str() << "|\n";
        cout << "|  Balance    : RM " << setw(48) << left << ssE.str() << "|\n";
        cout << "|  Status     : " << setw(55) << left << r.paymentStatus << "|\n";
        cout << "+=================================================================+\n";
    }

    // 是否付款
    cout << "\n Pay now?  0=No  1=Full  2=Half  3=Custom : ";
    int act = 0;
    if (!(cin >> act)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); act = 0; }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (act == 0) { cout << "No payment recorded. Press Enter..."; cin.get(); return; }

    // 计算应付金额（Full/Half/Custom）
    float payAmount = 0.0f;
    if (act == 1) {
        // 全款 = 有效总额 - 已付
        float need = r.totalPayment - sumDisc - r.amountPaid;
        if (need < 0.0f) need = 0.0f;
        payAmount = need;
    }
    else if (act == 2) {
        // 半款 = (有效总额 - 已付) 的一半
        float need = r.totalPayment - sumDisc - r.amountPaid;
        if (need < 0.0f) need = 0.0f;
        payAmount = need * 0.5f;
    }
    else {
        // 自定义
        while (true) {
            cout << " Enter amount to pay: ";
            string s; getline(cin, s);
            stringstream ss(s); float v = 0.0f; ss >> v;
            if (ss && v >= 0.0f) { payAmount = v; break; }
            cout << "  Invalid.\n";
        }
    }

    // 折扣（可选）
    float disc = 0.0f;
    cout << " Enter discount (RM, 0 if none): ";
    {
        string s; getline(cin, s);
        if (!s.empty()) { stringstream ss(s); float v = 0.0f; ss >> v; if (ss && v >= 0.0f) disc = v; }
    }

    // 方式 / 日期 / 备注
    cout << " Payment method (Cash/Card/Transfer/...): ";
    string method; getline(cin, method);
    if (method.empty()) method = "Cash";

    cout << " Payment date (YYYY-MM-DD): ";
    string pdate; getline(cin, pdate);
    if (pdate.empty()) pdate = "2025-09-08"; // 如需固定今天可改为你系统的日期输入

    cout << " Note (optional): ";
    string pnote; getline(cin, pnote);

    // 生成 Payment 记录
    Payment pm;
    pm.paymentID = uniqueIDGenerator<Payment>("PM", "payments.csv");
    pm.reservationID = r.reservationID;
    pm.clientID = r.clientID;
    pm.amountPaid = payAmount;
    pm.discountApplied = disc;
    pm.paymentDate = pdate;
    pm.paymentMethod = method;
    pm.note = pnote;
    pm.paymentStatus = "RECEIVED";

    payments.push_back(pm);
    saveList(payments, "payments.csv");

    // 重新汇总订单支付状态并保存
    recomputeReservationPayments(reservations, payments);
    // 同时把我们本地副本 r 也刷新为最新
    for (i = 0; i < reservations.size(); ++i) {
        if (reservations[i].reservationID == rid) {
            r = reservations[i];
            break;
        }
    }
    saveList(reservations, "reservations.csv");

    // ===== 打印收据（一个方框内） =====
    {
        string cname = c.person.fullName();
        stringstream sA, sD, sTP, sPA, sBal;
        sA << fixed << setprecision(2) << pm.amountPaid;
        sD << fixed << setprecision(2) << pm.discountApplied;

        // 最新余额计算（基于 recompute 后）
        float newSumPaid = 0.0f, newSumDisc = 0.0f;
        for (i = 0; i < payments.size(); ++i) {
            if (payments[i].reservationID == r.reservationID) {
                newSumPaid += payments[i].amountPaid;
                newSumDisc += payments[i].discountApplied;
            }
        }
        float newEffective = r.totalPayment - newSumDisc; if (newEffective < 0) newEffective = 0.0f;
        float newBalance = newEffective - newSumPaid;   if (newBalance < 0) newBalance = 0.0f;

        sTP << fixed << setprecision(2) << r.totalPayment;
        sPA << fixed << setprecision(2) << newSumPaid;
        sBal << fixed << setprecision(2) << newBalance;

        cout << "\n+=================================================================+\n";
        cout << "|                             RECEIPT                              |\n";
        cout << "+=================================================================+\n";
        cout << "|  Payment ID    : " << setw(55) << left << pm.paymentID << "|\n";
        cout << "|  Reservation ID: " << setw(55) << left << r.reservationID << "|\n";
        cout << "|  Client        : " << setw(55) << left << cname << "|\n";
        cout << "|  Date/Method   : " << setw(55) << left << (pm.paymentDate + " / " + pm.paymentMethod) << "|\n";
        cout << "+-----------------------------------------------------------------+\n";
        cout << "|  Amount Paid   : RM " << setw(46) << left << sA.str() << "|\n";
        cout << "|  Discount      : RM " << setw(46) << left << sD.str() << "|\n";
        cout << "+-----------------------------------------------------------------+\n";
        cout << "|  Order Total   : RM " << setw(46) << left << sTP.str() << "|\n";
        cout << "|  Paid (Total)  : RM " << setw(46) << left << sPA.str() << "|\n";
        cout << "|  Balance       : RM " << setw(46) << left << sBal.str() << "|\n";
        cout << "|  Status        : " << setw(55) << left << r.paymentStatus << "|\n";
        cout << "+=================================================================+\n";
    }

    cout << "\nPayment recorded. Press Enter..."; cin.get();
}


//start functions
void reservationCenter()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.ReservationMenu;

        int choice;
        cout << " Choose: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input. Press Enter..."; cin.get(); cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // eat '\n'

        if (choice == 0) { showMainScreen(); }

        else if (choice == 1) {
            // ===== New Reservation =====
            system("cls");
            cout << "== New Reservation ==\n";

            // load data
            vector<Client>      clients = getList<Client>("clients.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Package>     packages = getList<Package>("packages.csv");
            vector<Venue>       venues = getList<Venue>("venues.csv");
            vector<Cater>       caters = getList<Cater>("caterings.csv");
            vector<Vendor>      vendors = getList<Vendor>("vendors.csv");
            vector<FoodPackage> foods = getList<FoodPackage>("food_packages.csv");

            // ---- inline printers (use your struct fields) ----
            auto line = []() { cout << string(90, '-') << "\n"; };

            auto printPackages = [&]() {
                cout << "\nAvailable Packages (" << packages.size() << ")\n"; line();
                cout << left << setw(10) << "ID" << setw(28) << "Name" << setw(12) << "Price" << "Description\n"; line();
                for (const auto& p : packages) {
                    cout << left << setw(10) << p.packageID
                        << setw(28) << p.packageName
                        << setw(12) << fixed << setprecision(2) << p.price
                        << p.description << "\n";
                }
                line();
                };

            auto printVenues = [&]() {
                cout << "\nAvailable Venues (" << venues.size() << ")\n"; line();
                cout << left << setw(10) << "ID" << setw(24) << "Name" << setw(20) << "Location"
                    << setw(10) << "Capacity" << setw(12) << "Rental(RM)" << "\n"; line();
                for (const auto& v : venues) {
                    cout << left << setw(10) << v.venueID
                        << setw(24) << v.venueName
                        << setw(20) << v.location
                        << setw(10) << v.capacity
                        << setw(12) << fixed << setprecision(2) << v.rentalCost
                        << "\n";
                }
                line();
                };

            auto printFoodPackages = [&]() {
                cout << "\nAvailable Food Packages (" << foods.size() << ")\n"; line();
                cout << left << setw(10) << "ID" << setw(16) << "Provider"
                    << setw(12) << "Billing" << setw(10) << "Unit(RM)"
                    << setw(9) << "MinG" << setw(9) << "MaxG" << setw(9) << "MinT"
                    << "Menu (App/Main/Dessert)\n"; line();
                for (const auto& f : foods) {
                    cout << left << setw(10) << f.foodID
                        << setw(16) << f.provider
                        << setw(12) << f.billingMode
                        << setw(10) << fixed << setprecision(2) << f.unitPrice
                        << setw(9) << f.minGuests
                        << setw(9) << f.maxGuests
                        << setw(9) << f.minTables
                        << (f.appetizer + " / " + f.mainCourse + " / " + f.dessert) << "\n";
                }
                line();
                };

            auto printCaters = [&]() {
                cout << "\nAvailable Caterings (" << caters.size() << ")\n"; line();
                cout << left << setw(10) << "ID" << setw(24) << "Name"
                    << setw(12) << "PerPerson(RM)" << "Menu Description\n"; line();
                for (const auto& c : caters) {
                    cout << left << setw(10) << c.caterID
                        << setw(24) << c.caterName
                        << setw(12) << fixed << setprecision(2) << c.costPerPerson
                        << c.menuDescription << "\n";
                }
                line();
                };

            auto printVendors = [&]() {
                cout << "\nAvailable Vendors (" << vendors.size() << ")\n"; line();
                cout << left << setw(10) << "ID" << setw(14) << "Type"
                    << setw(20) << "Name" << setw(22) << "Email"
                    << setw(14) << "Phone" << setw(10) << "Cost(RM)" << "\n"; line();
                for (const auto& v : vendors) {
                    string fullName = v.person.firstName + " " + v.person.lastName;
                    cout << left << setw(10) << v.vendorID
                        << setw(14) << v.vendorType
                        << setw(20) << fullName
                        << setw(22) << v.person.email
                        << setw(14) << v.person.contact
                        << setw(10) << fixed << setprecision(2) << v.cost
                        << "\n";
                }
                line();
                };

            // collect client base info (查重：email/phone 或 姓名+电话)
            string ln = getValidatedInput<string>(" Last name: ", "non_empty");
            string fn = getValidatedInput<string>(" First name: ", "non_empty");
            string em = getValidatedInput<string>(" Email: ", "email");
            string ph = getValidatedInput<string>(" Phone: ", "non_empty");

            string emL = em, phL = ph, lnL = ln, fnL = fn;
            size_t i, j;
            for (i = 0; i < emL.size(); ++i) emL[i] = char(tolower((unsigned char)emL[i]));
            for (i = 0; i < phL.size(); ++i) phL[i] = char(tolower((unsigned char)phL[i]));
            for (i = 0; i < lnL.size(); ++i) lnL[i] = char(tolower((unsigned char)lnL[i]));
            for (i = 0; i < fnL.size(); ++i) fnL[i] = char(tolower((unsigned char)fnL[i]));

            string cid = "";
            for (i = 0; i < clients.size(); ++i) {
                string a = clients[i].person.email;    for (j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = clients[i].person.contact;  for (j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = clients[i].person.lastName; for (j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                string d = clients[i].person.firstName;for (j = 0; j < d.size(); ++j) d[j] = char(tolower((unsigned char)d[j]));
                if (a == emL || b == phL || (c == lnL && d == fnL && b == phL)) { cid = clients[i].clientID; break; }
            }

            if (cid.empty()) {
                Client c;
                c.clientID = uniqueIDGenerator<Client>("C", "clients.csv");
                c.person.lastName = ln;
                c.person.firstName = fn;
                c.person.email = em;
                c.person.contact = ph;
                clients.push_back(c);
                saveList(clients, "clients.csv");
                cid = c.clientID;
                cout << " New client created: " << cid << "\n";
            }
            else {
                cout << " Existing client found: " << cid << "\n";
            }

            // create reservation shell
            Reservation r;
            r.reservationID = uniqueIDGenerator<Reservation>("R", "reservations.csv");
            r.clientID = cid;

            r.weddingDate = getValidatedInput<string>(" Wedding Date (YYYY-MM-DD): ", "date");
            cout << " Special request (optional): ";
            getline(cin, r.specialRequest);

            // guests & tables (>=0)
            {
                int v = getValidatedInput<int>(" Guest count: ");
                if (v < 0) v = 0; r.guestCount = v;
                v = getValidatedInput<int>(" Table count: ");
                if (v < 0) v = 0; r.tableCount = v;
            }

            // choose: package or venue+food/cater
            string usePkg = getValidatedInput<string>(" Use wedding PACKAGE? (Y/N): ", "non_empty");
            if (usePkg == "Y" || usePkg == "y") {
                // === show packages ===
                printPackages();

                string pid; cout << "  Package ID: "; getline(cin, pid);
                bool ok = false; for (i = 0; i < packages.size(); ++i) if (packages[i].packageID == pid) { ok = true; break; }
                if (ok) {
                    r.selectedPackage = pid;
                    r.venueBooked.clear();
                    r.foodPackageID.clear();
                    r.cateringSelected.clear();
                }
                else {
                    cout << "  Package not found. Press Enter..."; cin.get(); continue;
                }
            }
            else {
                // === show venues ===
                printVenues();

                // venue
                cout << " Venue ID (Enter to skip): ";
                getline(cin, r.venueBooked);
                if (!r.venueBooked.empty()) {
                    bool okv = false; for (i = 0; i < venues.size(); ++i) if (venues[i].venueID == r.venueBooked) { okv = true; break; }
                    if (!okv) { cout << "  Venue not found. Press Enter..."; cin.get(); continue; }
                }

                // food or cater (must pick exactly one)
                cout << " Food option: 1) Food Package  2) Catering : ";
                int m = 0; { string s; getline(cin, s); stringstream ss(s); ss >> m; }
                if (m == 1) {
                    // === show food packages ===
                    printFoodPackages();

                    cout << "\n  Food Package ID: ";
                    getline(cin, r.foodPackageID);
                    bool okf = false; for (i = 0; i < foods.size(); ++i) if (foods[i].foodID == r.foodPackageID) { okf = true; break; }
                    if (!okf) { cout << "  Food package not found. Press Enter..."; cin.get(); continue; }
                    r.cateringSelected.clear();
                }
                else if (m == 2) {
                    // === show caterings ===
                    printCaters();

                    cout << "  Cater ID: ";
                    getline(cin, r.cateringSelected);
                    bool okc = false; for (i = 0; i < caters.size(); ++i) if (caters[i].caterID == r.cateringSelected) { okc = true; break; }
                    if (!okc) { cout << "  Cater not found. Press Enter..."; cin.get(); continue; }
                    r.foodPackageID.clear();
                }
                else {
                    cout << "  Must choose 1 or 2. Press Enter..."; cin.get(); continue;
                }
            }

            // vendors (validate IDs)
            printVendors();
            cout << " Vendor IDs (semicolon separated, Enter to skip): ";
            string vline; getline(cin, vline);
            if (!vline.empty()) {
                vector<string> vids = splitIds(vline, ';');
                vector<string> okv; okv.reserve(vids.size());
                for (i = 0; i < vids.size(); ++i) {
                    bool ok = false; for (j = 0; j < vendors.size(); ++j) if (vendors[j].vendorID == vids[i]) { ok = true; break; }
                    if (ok) okv.push_back(vids[i]);
                }
                r.selectedVendors = okv;
            }

            // ===== validations =====
            // A) if not package: exactly one of foodPackageID / cateringSelected
            if (r.selectedPackage.empty()) {
                int cnt = 0;
                if (!r.foodPackageID.empty()) cnt++;
                if (!r.cateringSelected.empty()) cnt++;
                if (cnt != 1) {
                    cout << " Invalid choice: pick exactly ONE of Food Package or Catering.\n";
                    cout << " Press Enter..."; cin.get(); continue;
                }
            }

            // B) venue capacity >= guestCount (if venue chosen)
            if (!r.venueBooked.empty()) {
                int cap = -1;
                for (i = 0; i < venues.size(); ++i) if (venues[i].venueID == r.venueBooked) { cap = venues[i].capacity; break; }
                if (cap >= 0 && r.guestCount > cap) {
                    cout << " Venue capacity (" << cap << ") < guest count (" << r.guestCount << ").\n";
                    cout << " Press Enter..."; cin.get(); continue;
                }
            }

            // C) venue&date conflict (if venue chosen)
            if (!r.venueBooked.empty()) {
                bool conflict = false;
                for (i = 0; i < reservations.size(); ++i) {
                    if (reservations[i].venueBooked == r.venueBooked &&
                        reservations[i].weddingDate == r.weddingDate &&
                        reservations[i].paymentStatus != "CANCELLED")
                    {
                        conflict = true; break;
                    }
                }
                if (conflict) {
                    cout << " Conflict: another reservation already booked this venue on that date.\n";
                    cout << " Press Enter..."; cin.get(); continue;
                }
            }

            // compute total & save
            r.totalPayment = computeReservationTotal(r, packages, venues, caters, vendors, foods);
            if (r.totalPayment < 0) r.totalPayment = 0.0f;
            r.amountPaid = 0.0f; r.paymentStatus = "UNPAID";

            reservations.push_back(r);
            saveList(reservations, "reservations.csv");

            cout << "\n Reservation created: " << r.reservationID
                << "  Subtotal: RM " << fixed << setprecision(2) << r.totalPayment << "\n";

            // optional checkout
            string goPay = getValidatedInput<string>(" Go to checkout now? (Y/N): ", "non_empty");
            if (goPay == "Y" || goPay == "y") {
                checkoutWizard();
            }
            else {
                cout << " Saved. Press Enter..."; cin.get();
            }

        }

        else if (choice == 2) {
            // ===== Cancel Reservation =====
            system("cls");
            cout << "== Cancel Reservation ==\n";
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Payment>     payments = getList<Payment>("payments.csv");

            string rid; cout << " Reservation ID: "; getline(cin, rid);
            int idx = -1; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].reservationID == rid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found. Press Enter..."; cin.get(); continue; }

            bool hasPay = false;
            for (i = 0; i < payments.size(); ++i) if (payments[i].reservationID == rid) { hasPay = true; break; }

            if (hasPay) {
                cout << " Payments exist. Mark as CANCELLED? (Y/N): ";
                string ans; getline(cin, ans);
                if (ans == "Y" || ans == "y") {
                    reservations[idx].paymentStatus = "CANCELLED";
                    saveList(reservations, "reservations.csv");
                    cout << " Marked CANCELLED. Press Enter..."; cin.get();
                }
                else {
                    cout << " No change. Press Enter..."; cin.get();
                }
            }
            else {
                vector<Reservation> kept; kept.reserve(reservations.size());
                for (i = 0; i < reservations.size(); ++i) if (reservations[i].reservationID != rid) kept.push_back(reservations[i]);
                saveList(kept, "reservations.csv");
                cout << " Removed.\n Press Enter..."; cin.get();
            }
        }

        else if (choice == 3) {
            // ===== Modify Reservation =====
            system("cls");
            cout << "== Modify Reservation ==\n";
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Package>     packages = getList<Package>("packages.csv");
            vector<Venue>       venues = getList<Venue>("venues.csv");
            vector<Cater>       caters = getList<Cater>("caterings.csv");
            vector<Vendor>      vendors = getList<Vendor>("vendors.csv");
            vector<FoodPackage> foods = getList<FoodPackage>("food_packages.csv");

            string rid; cout << " Reservation ID: "; getline(cin, rid);
            int idx = -1; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].reservationID == rid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found. Press Enter..."; cin.get(); continue; }

            Reservation& r = reservations[idx];
            cout << " (Enter to keep current)\n";

            string s;

            cout << " Wedding Date [" << r.weddingDate << "]: ";
            getline(cin, s); if (!s.empty()) {
                // 基本格式校验可复用 getValidatedInput，但这里按你的“不加函数”要求就不再二次调用
                r.weddingDate = s;
            }

            cout << " Special Request [" << r.specialRequest << "]: ";
            getline(cin, s); if (!s.empty()) r.specialRequest = s;

            cout << " Guest count [" << r.guestCount << "]: ";
            getline(cin, s); if (!s.empty()) { int v = 0; stringstream ss(s); ss >> v; if (ss && v >= 0) r.guestCount = v; }

            cout << " Table count [" << r.tableCount << "]: ";
            getline(cin, s); if (!s.empty()) { int v = 0; stringstream ss(s); ss >> v; if (ss && v >= 0) r.tableCount = v; }

            cout << " Package ID [" << (r.selectedPackage.empty() ? string("-") : r.selectedPackage) << "] (type '-' to clear): ";
            getline(cin, s);
            if (!s.empty()) {
                if (s == "-") r.selectedPackage.clear();
                else {
                    bool ok = false; for (i = 0; i < packages.size(); ++i) if (packages[i].packageID == s) { ok = true; break; }
                    if (ok) { r.selectedPackage = s; r.venueBooked.clear(); r.foodPackageID.clear(); r.cateringSelected.clear(); }
                    else cout << "  Package not found, keep old.\n";
                }
            }

            if (r.selectedPackage.empty()) {
                cout << " Venue ID [" << (r.venueBooked.empty() ? string("-") : r.venueBooked) << "] (type '-' to clear): ";
                getline(cin, s);
                if (!s.empty()) {
                    if (s == "-") r.venueBooked.clear();
                    else {
                        bool ok = false; for (i = 0; i < venues.size(); ++i) if (venues[i].venueID == s) { ok = true; break; }
                        if (ok) r.venueBooked = s; else cout << "  Venue not found, keep old.\n";
                    }
                }

                cout << " Food Package ID [" << (r.foodPackageID.empty() ? string("-") : r.foodPackageID) << "] (type '-' to clear): ";
                getline(cin, s);
                if (!s.empty()) {
                    if (s == "-") r.foodPackageID.clear();
                    else {
                        bool ok = false; for (i = 0; i < foods.size(); ++i) if (foods[i].foodID == s) { ok = true; break; }
                        if (ok) { r.foodPackageID = s; r.cateringSelected.clear(); }
                        else cout << "  Food package not found, keep old.\n";
                    }
                }

                cout << " Cater ID [" << (r.cateringSelected.empty() ? string("-") : r.cateringSelected) << "] (type '-' to clear): ";
                getline(cin, s);
                if (!s.empty()) {
                    if (s == "-") r.cateringSelected.clear();
                    else {
                        bool ok = false; for (i = 0; i < caters.size(); ++i) if (caters[i].caterID == s) { ok = true; break; }
                        if (ok) { r.cateringSelected = s; r.foodPackageID.clear(); }
                        else cout << "  Cater not found, keep old.\n";
                    }
                }
            }

            cout << " Vendor IDs (semicolon) ["
                << (r.selectedVendors.empty() ? string("-") : joinVec(r.selectedVendors, ';')) << "] : ";
            getline(cin, s);
            if (!s.empty()) {
                if (s == "-") r.selectedVendors.clear();
                else {
                    vector<string> vids = splitIds(s, ';');
                    vector<string> okv; okv.reserve(vids.size());
                    size_t k;
                    for (k = 0; k < vids.size(); ++k) {
                        bool ok = false; for (i = 0; i < vendors.size(); ++i) if (vendors[i].vendorID == vids[k]) { ok = true; break; }
                        if (ok) okv.push_back(vids[k]);
                    }
                    r.selectedVendors = okv;
                }
            }

            // re-validate
            if (r.selectedPackage.empty()) {
                int cnt = 0; if (!r.foodPackageID.empty())cnt++; if (!r.cateringSelected.empty())cnt++;
                if (cnt != 1) { cout << " Invalid combination (need one of Food/Cater). Not saved.\n"; cout << " Press Enter..."; cin.get(); continue; }
            }
            if (!r.venueBooked.empty()) {
                int cap = -1; for (i = 0; i < venues.size(); ++i) if (venues[i].venueID == r.venueBooked) { cap = venues[i].capacity; break; }
                if (cap >= 0 && r.guestCount > cap) { cout << " Venue capacity < guests. Not saved.\n"; cout << " Press Enter..."; cin.get(); continue; }
                bool conflict = false;
                for (i = 0; i < reservations.size(); ++i) {
                    if (i == (size_t)idx) continue;
                    if (reservations[i].venueBooked == r.venueBooked &&
                        reservations[i].weddingDate == r.weddingDate &&
                        reservations[i].paymentStatus != "CANCELLED") {
                        conflict = true; break;
                    }
                }
                if (conflict) { cout << " Venue/date conflict. Not saved.\n"; cout << " Press Enter..."; cin.get(); continue; }
            }

            r.totalPayment = computeReservationTotal(r, packages, venues, caters, vendors, foods);
            if (r.totalPayment < 0) r.totalPayment = 0.0f;
            saveList(reservations, "reservations.csv");

            cout << " Updated. Subtotal: RM " << fixed << setprecision(2) << r.totalPayment << "\n";
            cout << " Press Enter..."; cin.get();
        }

        else if (choice == 4) {
            // ===== View All =====
            system("cls");
            cout << "== All Reservations ==\n";
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            if (reservations.empty()) cout << "(none)\n";
            else {
                size_t i;
                for (i = 0; i < reservations.size(); ++i) {
                    cout << setw(8) << left << reservations[i].reservationID
                        << "  Client:" << setw(8) << left << reservations[i].clientID
                        << "  Date:" << setw(12) << left << reservations[i].weddingDate
                        << "  Guests:" << setw(4) << left << reservations[i].guestCount
                        << "  Tables:" << setw(4) << left << reservations[i].tableCount
                        << "  Status:" << setw(10) << left << reservations[i].paymentStatus
                        << "  Total: RM " << fixed << setprecision(2) << reservations[i].totalPayment
                        << "\n";
                }
            }
            cout << "\n Press Enter..."; cin.get();
        }

        else if (choice == 5) {
            // ===== Checkout / Payment =====
            checkoutWizard();
        }

        else {
            cout << "\n Invalid option. Press Enter..."; cin.get();
        }
    }
}

void managePayment() {
    StringConst strConst;
    int x;

    vector<Payment>      payments = getList<Payment>("payments.csv");
    vector<Client>       clients = getList<Client>("clients.csv");
    vector<Reservation>  reservations = getList<Reservation>("reservations.csv");

    auto saveAll = [&]() {
        saveList(payments, "payments.csv");
        recomputeReservationPayments(reservations, payments);
        saveList(reservations, "reservations.csv");
        };

    auto drawBox = [&](const string& title, const vector<pair<string, string>>& rows, int width) {
        int w = width; if (w < 40) w = 40; if (w > 120) w = 120;
        auto crop = [&](const string& s, int n)->string {
            if ((int)s.size() <= n) return s;
            if (n <= 3) return s.substr(0, n);
            string t = s.substr(0, n - 3); t += "..."; return t;
            };
        cout << "+" << string(w - 2, '-') << "+\n";
        int pad = (w - 2 - (int)title.size()); if (pad < 0) pad = 0;
        int l = pad / 2, r = pad - l;
        cout << "|" << string(l, ' ') << crop(title, w - 2) << string(r, ' ') << "|\n";
        cout << "|" << string(w - 2, ' ') << "|\n";
        int labelMax = 0; for (size_t i = 0; i < rows.size(); ++i) if ((int)rows[i].first.size() > labelMax) labelMax = (int)rows[i].first.size();
        if (labelMax > 22) labelMax = 22;
        int valueWidth = w - 2 - 2 - labelMax - 3;
        for (size_t i = 0; i < rows.size(); ++i) {
            string L = rows[i].first, R = rows[i].second;
            if ((int)L.size() > labelMax) L = crop(L, labelMax);
            string line = R;
            while (true) {
                string part = line;
                if ((int)part.size() > valueWidth) part = crop(part, valueWidth);
                cout << "| " << setw(labelMax) << left << L << " : " << setw(valueWidth) << left << part << " |\n";
                if ((int)line.size() <= valueWidth) break;
                line = line.substr(valueWidth);
                L = "";
            }
        }
        cout << "+" << string(w - 2, '-') << "+\n";
        };

    auto listReservations = [&]() {
        vector<vector<pair<string, string>>> recs;
        for (size_t i = 0; i < reservations.size(); ++i) {
            const Reservation& r = reservations[i];
            string cname = r.clientID;
            for (size_t j = 0; j < clients.size(); ++j) if (clients[j].clientID == r.clientID) { cname = clients[j].person.fullName(); break; }
            recs.push_back({
                {"Reservation ID", r.reservationID},
                {"Client",         cname},
                {"Wedding Date",   r.weddingDate},
                {"Total",          myr(r.totalPayment)},
                {"Paid",           myr(r.amountPaid)},
                {"Status",         r.paymentStatus}
                });
        }
        if (recs.empty()) cout << "No reservations found.\n";
        else               printRecords<string>(recs, 1);
        };

    auto listPayments = [&]() {
        vector<vector<pair<string, string>>> recs;
        for (size_t i = 0; i < payments.size(); ++i) {
            const Payment& p = payments[i];
            recs.push_back({
                {"Payment ID",       p.paymentID},
                {"Reservation ID",   p.reservationID},
                {"Client ID",        p.clientID},
                {"Amount",           myr(p.amountPaid)},
                {"Discount Applied", myr(p.discountApplied)},
                {"Date",             p.paymentDate},
                {"Method",           p.paymentMethod},
                {"Note",             p.note},
                {"Status",           p.paymentStatus}
                });
        }
        if (recs.empty()) cout << "No payments found.\n";
        else               printRecords<string>(recs, 1);
        };

    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.PaymentMenu;

        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        if (x == 0) { showMainScreen(); return; }

        if (x == 1) { // Create Payment
            system("cls");
            cout << "Reservations:\n";
            listReservations();

            // 支持：直接输 ReservationID；或留空→按 clientID/姓名检索
            string rid = getValidatedInput<string>("Enter reservation ID (leave blank to search by client): ");
            Reservation* rp = (Reservation*)0;

            if (!rid.empty()) {
                for (size_t i = 0; i < reservations.size(); ++i)
                    if (reservations[i].reservationID == rid) { rp = &reservations[i]; break; }
                if (!rp) { cout << "Reservation not found.\nPress Enter..."; cin.get(); continue; }
            }
            else {
                string cid = getValidatedInput<string>("Client ID (leave blank to use name): ");
                vector<size_t> candidates;
                if (!cid.empty()) {
                    for (size_t i = 0; i < reservations.size(); ++i)
                        if (reservations[i].clientID == cid) candidates.push_back(i);
                }
                else {
                    string ln = getValidatedInput<string>("Last name: ", "non_empty");
                    string fn = getValidatedInput<string>("First name: ", "non_empty");
                    // 找到这个客户的 clientID
                    vector<string> cids;
                    for (size_t i = 0; i < clients.size(); ++i)
                        if (clients[i].person.lastName == ln && clients[i].person.firstName == fn)
                            cids.push_back(clients[i].clientID);
                    for (size_t i = 0; i < reservations.size(); ++i)
                        for (size_t j = 0; j < cids.size(); ++j)
                            if (reservations[i].clientID == cids[j]) candidates.push_back(i);
                }
                if (candidates.empty()) { cout << "No reservation found for this client.\nPress Enter..."; cin.get(); continue; }
                if (candidates.size() == 1) rp = &reservations[candidates[0]];
                else {
                    cout << "Select one reservation:\n";
                    for (size_t t = 0; t < candidates.size(); ++t) {
                        size_t i = candidates[t];
                        string cname = reservations[i].clientID;
                        for (size_t j = 0; j < clients.size(); ++j)
                            if (clients[j].clientID == reservations[i].clientID) { cname = clients[j].person.fullName(); break; }
                        cout << " [" << t << "] " << reservations[i].reservationID << " | " << cname
                            << " | " << reservations[i].weddingDate << "\n";
                    }
                    int pick = getValidatedInput<int>("Enter index: ");
                    if (pick < 0 || pick >= (int)candidates.size()) { cout << "Invalid.\nPress Enter..."; cin.get(); continue; }
                    rp = &reservations[candidates[(size_t)pick]];
                }
            }

            // 金额与折扣
            float amount = getValidatedInput<float>("Enter amount: ", "", " Invalid number: ");
            string date = getValidatedInput<string>("Enter payment date (YYYY-MM-DD): ", "date");
            string method = getValidatedInput<string>("Payment method (Cash/Card/Transfer/...): ", "non_empty");
            float disc = getValidatedInput<float>("Discount to apply with this record (0 if none): ");
            if (disc < 0) disc = 0.0f;

            Payment p;
            p.paymentID = uniqueIDGenerator<Payment>("P", "payments.csv");
            p.reservationID = rp->reservationID;
            p.clientID = rp->clientID;
            p.amountPaid = amount;
            p.discountApplied = disc;
            p.paymentDate = date;
            p.paymentMethod = method;
            p.note = getValidatedInput<string>("Note (no comma please, Enter to skip): ");
            p.paymentStatus = "RECEIVED";

            payments.push_back(p);
            saveAll();

            // 打印单框 Receipt
            string cname = rp->clientID;
            for (size_t j = 0; j < clients.size(); ++j)
                if (clients[j].clientID == rp->clientID) { cname = clients[j].person.fullName(); break; }

            // 合计整体（用于展示）
            float paidAll = 0.0f, discAll = 0.0f;
            for (size_t i = 0; i < payments.size(); ++i)
                if (payments[i].reservationID == rp->reservationID) { paidAll += payments[i].amountPaid; discAll += payments[i].discountApplied; }

            vector<pair<string, string>> recRows;
            recRows.push_back(pair<string, string>("Payment ID", p.paymentID));
            recRows.push_back(pair<string, string>("Reservation ID", rp->reservationID));
            recRows.push_back(pair<string, string>("Client", cname));
            recRows.push_back(pair<string, string>("Date / Method", p.paymentDate + " / " + p.paymentMethod));
            recRows.push_back(pair<string, string>("Paid (this)", myr(p.amountPaid)));
            recRows.push_back(pair<string, string>("Discount (this)", myr(p.discountApplied)));
            recRows.push_back(pair<string, string>("Paid (all)", myr(paidAll)));
            recRows.push_back(pair<string, string>("Discounts (all)", myr(discAll)));
            recRows.push_back(pair<string, string>("Status", rp->paymentStatus));
            drawBox("RECEIPT", recRows, 78);

            cout << "Press Enter..."; cin.get();
        }
        else if (x == 2) { // Remove Payment
            system("cls");
            listPayments();
            string pid = getValidatedInput<string>("Enter payment ID to remove: ", "non_empty");
            size_t i = 0; for (; i < payments.size(); ++i) if (payments[i].paymentID == pid) break;
            if (i >= payments.size()) { cout << "Payment not found.\nPress Enter..."; cin.get(); continue; }
            payments.erase(payments.begin() + i);
            saveAll();
            cout << "Removed.\nPress Enter..."; cin.get();
        }
        else if (x == 3) { // Update Payment
            system("cls");
            listPayments();

            string pid = getValidatedInput<string>("Enter payment ID to update: ", "non_empty");
            size_t i = 0; for (; i < payments.size(); ++i) if (payments[i].paymentID == pid) break;
            if (i >= payments.size()) { cout << "Not found.\nPress Enter..."; cin.get(); continue; }

            Payment& p = payments[i];

            // 允许改 ReservationID / ClientID / 金额 / 折扣 / 日期 / 方式 / 备注 / 状态
            {
                string s = updateField(p.reservationID, "New reservation ID? (Enter to keep): ");
                if (!s.empty()) p.reservationID = s;
            }
            {
                string s = updateField(p.clientID, "New client ID? (Enter to keep): ");
                if (!s.empty()) p.clientID = s;
            }
            {
                float v = updateField(p.amountPaid, "New amount? (0 to keep): ");
                if (v > 0) p.amountPaid = v;
            }
            {
                float v = updateField(p.discountApplied, "New discount? (0 to keep): ");
                if (v >= 0) p.discountApplied = v;
            }
            {
                string s = updateField(p.paymentDate, "New date (YYYY-MM-DD)? ", "date");
                if (!s.empty()) p.paymentDate = s;
            }
            {
                string s = updateField(p.paymentMethod, "New method? (Enter to keep): ");
                if (!s.empty()) p.paymentMethod = s;
            }
            {
                string s = updateField(p.note, "New note? (Enter to keep): ");
                if (!s.empty()) p.note = s;
            }
            {
                string s = updateField(p.paymentStatus, "New payment status? (e.g., RECEIVED/REFUND) ", "non_empty");
                if (!s.empty()) p.paymentStatus = s;
            }

            saveAll();
            cout << "Updated.\n Press Enter..."; cin.get();
        }
        else if (x == 4) { // Show All Payments
            system("cls");
            listPayments();
            cout << " Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\n Press Enter..."; cin.get();
        }
    }
}

void catalog() {
    StringConst strConst;
    int x;
    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.CatalogMenu;

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
    case 4:
        manageVendor();
        break;
    case 5:
        manageFoodPackage();
        break;
    default:
        cout << " Invalid option.\n Please Enter..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        catalog();
        break;
    }
}

void managePackage()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.PackageMenu;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << " Invalid input. Press Enter..."; cin.get(); cin.get(); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x == 0) { catalog(); }

        else if (x == 1) { // Create
            system("cls");
            cout << "== Create Package ==\n";

            vector<Package> items = getList<Package>("packages.csv");

            Package p;
            p.packageID = uniqueIDGenerator<Package>("PK", "packages.csv");
            p.packageName = getValidatedInput<string>(" Package name: ", "non_empty");
            cout << " Description: ";
            getline(cin, p.description);

            // price >= 0
            while (true) {
                cout << " Price (>=0): ";
                string s; getline(cin, s);
                stringstream ss(s); float v = 0.0f; ss >> v;
                if (ss && v >= 0.0f) { p.price = v; break; }
                cout << "  Invalid price.\n";
            }

            items.push_back(p);
            saveList(items, "packages.csv");
            cout << "\n Created [" << p.packageID << "]. Press Enter..."; cin.get();
        }

        else if (x == 2) { // Remove —— 内联“被引用检查”
            system("cls");
            cout << "== Remove Package ==\n";

            vector<Package>     items = getList<Package>("packages.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Client>      clients = getList<Client>("clients.csv");

            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i;
                for (i = 0; i < items.size(); ++i) {
                    cout << " [" << items[i].packageID << "] " << items[i].packageName
                        << "  RM " << fixed << setprecision(2) << items[i].price
                        << "  - " << items[i].description << "\n";
                }
            }

            string pid; cout << "\n Enter Package ID to remove: "; getline(cin, pid);

            bool inUse = false; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].selectedPackage == pid) { inUse = true; break; }
            if (!inUse) for (i = 0; i < clients.size(); ++i) if (clients[i].selectedPackage == pid) { inUse = true; break; }

            if (inUse) { cout << " Cannot remove: Package is referenced.\nPress Enter..."; cin.get(); continue; }

            bool removed = false; vector<Package> kept; kept.reserve(items.size());
            for (i = 0; i < items.size(); ++i) { if (items[i].packageID == pid) { removed = true; continue; } kept.push_back(items[i]); }
            if (removed) { saveList(kept, "packages.csv"); cout << " Removed.\n"; }
            else { cout << " Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }

        else if (x == 3) { // Update
            system("cls"); cout << "== Update Package ==\n";
            vector<Package> items = getList<Package>("packages.csv");
            if (items.empty()) { cout << "(none)\n Press Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].packageID << "] " << items[i].packageName
                    << "  RM " << fixed << setprecision(2) << items[i].price
                    << "  - " << items[i].description << "\n";
            }

            string pid; cout << "\n Enter Package ID to update: "; getline(cin, pid);
            int idx = -1; size_t i; for (i = 0; i < items.size(); ++i) if (items[i].packageID == pid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found.\n Press Enter..."; cin.get(); continue; }

            string s;
            cout << "\n Name [" << items[idx].packageName << "]: "; getline(cin, s); if (!s.empty()) items[idx].packageName = s;
            cout << "\n Description [" << items[idx].description << "]: "; getline(cin, s); if (!s.empty()) items[idx].description = s;

            cout << "\n Price [" << fixed << setprecision(2) << items[idx].price << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); float v = items[idx].price; ss >> v; if (ss && v >= 0.0f) items[idx].price = v; else cout << "\n Invalid price, keep old.\n"; }

            saveList(items, "packages.csv");
            cout << "\n Updated.\n Press Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            system("cls"); cout << "== All Packages ==\n";
            vector<Package> items = getList<Package>("packages.csv");
            if (items.empty()) cout << "(none)\n";
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].packageID << "] " << items[i].packageName
                    << "  RM " << fixed << setprecision(2) << items[i].price
                    << "  - " << items[i].description << "\n";
            }
            cout << "\n Press Enter..."; cin.get();
        }

        else { cout << " Invalid option. Press Enter..."; cin.get(); }
    }
}

void manageVenue()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.VenueMenu;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << " Invalid input. Press Enter..."; cin.get(); cin.get(); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x == 0) { catalog(); }

        else if (x == 1) { // Create
            system("cls"); cout << "== Create Venue ==\n";
            vector<Venue> items = getList<Venue>("venues.csv");

            Venue v;
            v.venueID = uniqueIDGenerator<Venue>("VN", "venues.csv");
            v.venueName = getValidatedInput<string>(" Venue name: ", "non_empty");
            v.location = getValidatedInput<string>(" Location: ", "non_empty");

            // capacity >= 0
            while (true) {
                int cap = getValidatedInput<int>(" Capacity (>=0): ");
                if (cap >= 0) { v.capacity = cap; break; }
                cout << "  Invalid capacity.\n";
            }
            // rentalCost >= 0
            while (true) {
                cout << " Rental cost (>=0): ";
                string s; getline(cin, s);
                stringstream ss(s); float rc = 0.0f; ss >> rc;
                if (ss && rc >= 0.0f) { v.rentalCost = rc; break; }
                cout << "  Invalid cost.\n";
            }

            items.push_back(v);
            saveList(items, "venues.csv");
            cout << "\n Created [" << v.venueID << "]. Press Enter..."; cin.get();
        }

        else if (x == 2) { // Remove —— 引用检查
            system("cls"); cout << "== Remove Venue ==\n";
            vector<Venue>       items = getList<Venue>("venues.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Client>      clients = getList<Client>("clients.csv");

            if (items.empty()) { cout << "(none)\n Press Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].venueID << "] " << items[i].venueName
                    << " (" << items[i].location << ")  cap=" << items[i].capacity
                    << "  RM " << fixed << setprecision(2) << items[i].rentalCost << "\n";
            }

            string vid; cout << "\n Enter Venue ID to remove: "; getline(cin, vid);

            bool inUse = false; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].venueBooked == vid) { inUse = true; break; }
            if (!inUse) for (i = 0; i < clients.size(); ++i) if (clients[i].venueBooked == vid) { inUse = true; break; }

            if (inUse) { cout << " Cannot remove: Venue is referenced.\n Press Enter..."; cin.get(); continue; }

            bool removed = false; vector<Venue> kept; kept.reserve(items.size());
            for (i = 0; i < items.size(); ++i) { if (items[i].venueID == vid) { removed = true; continue; } kept.push_back(items[i]); }
            if (removed) { saveList(kept, "venues.csv"); cout << " Removed.\n"; }
            else { cout << "\n Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }

        else if (x == 3) { // Update
            system("cls"); cout << "== Update Venue ==\n";
            vector<Venue> items = getList<Venue>("venues.csv");
            if (items.empty()) { cout << "(none)\n Press Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].venueID << "] " << items[i].venueName
                    << " (" << items[i].location << ")  cap=" << items[i].capacity
                    << "  RM " << fixed << setprecision(2) << items[i].rentalCost << "\n";
            }

            string vid; cout << "\n Enter Venue ID to update: "; getline(cin, vid);
            int idx = -1; size_t i; for (i = 0; i < items.size(); ++i) if (items[i].venueID == vid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found.\nPress Enter..."; cin.get(); continue; }

            string s;
            cout << "\n Name [" << items[idx].venueName << "]: "; getline(cin, s); if (!s.empty()) items[idx].venueName = s;
            cout << "\n Location [" << items[idx].location << "]: "; getline(cin, s); if (!s.empty()) items[idx].location = s;

            cout << "\n Capacity [" << items[idx].capacity << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); int cap = items[idx].capacity; ss >> cap; if (ss && cap >= 0) items[idx].capacity = cap; else cout << "  Invalid, keep old.\n"; }

            cout << "\n Rental cost [" << fixed << setprecision(2) << items[idx].rentalCost << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); float rc = items[idx].rentalCost; ss >> rc; if (ss && rc >= 0.0f) items[idx].rentalCost = rc; else cout << "  Invalid, keep old.\n"; }

            saveList(items, "venues.csv");
            cout << "\n Updated.\n Press Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            system("cls"); cout << "== All Venues ==\n";
            vector<Venue> items = getList<Venue>("venues.csv");
            if (items.empty()) cout << "(none)\n";
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].venueID << "] " << items[i].venueName
                    << " (" << items[i].location << ")  cap=" << items[i].capacity
                    << "  RM " << fixed << setprecision(2) << items[i].rentalCost << "\n";
            }
            cout << " Press Enter..."; cin.get();
        }

        else { cout << " Invalid option. Press Enter..."; cin.get(); }
    }
}

void manageCatering()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.CaterMenu;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << " Invalid input. Press Enter..."; cin.get(); cin.get(); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x == 0) { catalog(); }

        else if (x == 1) { // Create
            system("cls"); cout << "== Create Catering ==\n";
            vector<Cater> items = getList<Cater>("caterings.csv");

            Cater c;
            c.caterID = uniqueIDGenerator<Cater>("CT", "caterings.csv");
            c.caterName = getValidatedInput<string>(" Cater name: ", "non_empty");
            cout << " Menu description: "; getline(cin, c.menuDescription);

            while (true) {
                cout << " Cost per person (>=0): ";
                string s; getline(cin, s);
                stringstream ss(s); float v = 0.0f; ss >> v;
                if (ss && v >= 0.0f) { c.costPerPerson = v; break; }
                cout << "  Invalid.\n";
            }

            items.push_back(c);
            saveList(items, "caterings.csv");
            cout << "\n Created [" << c.caterID << "]. Press Enter..."; cin.get();
        }

        else if (x == 2) { // Remove —— 引用检查
            system("cls"); cout << "== Remove Catering ==\n";
            vector<Cater>       items = getList<Cater>("caterings.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Client>      clients = getList<Client>("clients.csv");

            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].caterID << "] " << items[i].caterName
                    << "  RM " << fixed << setprecision(2) << items[i].costPerPerson
                    << "  - " << items[i].menuDescription << "\n";
            }

            string cid; cout << "\n Enter Cater ID to remove: "; getline(cin, cid);

            bool inUse = false; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].cateringSelected == cid) { inUse = true; break; }
            if (!inUse) for (i = 0; i < clients.size(); ++i) if (clients[i].cateringSelected == cid) { inUse = true; break; }

            if (inUse) { cout << " Cannot remove: Catering is referenced.\nPress Enter..."; cin.get(); continue; }

            bool removed = false; vector<Cater> kept; kept.reserve(items.size());
            for (i = 0; i < items.size(); ++i) { if (items[i].caterID == cid) { removed = true; continue; } kept.push_back(items[i]); }
            if (removed) { saveList(kept, "caterings.csv"); cout << " Removed.\n"; }
            else { cout << " Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }

        else if (x == 3) { // Update
            system("cls"); cout << "== Update Catering ==\n";
            vector<Cater> items = getList<Cater>("caterings.csv");
            if (items.empty()) { cout << "\n (none)\n Press Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].caterID << "] " << items[i].caterName
                    << "  RM " << fixed << setprecision(2) << items[i].costPerPerson
                    << "  - " << items[i].menuDescription << "\n";
            }

            string cid; cout << "\n Enter Cater ID to update: "; getline(cin, cid);
            int idx = -1; size_t i; for (i = 0; i < items.size(); ++i) if (items[i].caterID == cid) { idx = (int)i; break; }
            if (idx < 0) { cout << "\n Not found.\nPress Enter..."; cin.get(); continue; }

            string s;
            cout << "\n Name [" << items[idx].caterName << "]: "; getline(cin, s); if (!s.empty()) items[idx].caterName = s;
            cout << "\n Menu description [" << items[idx].menuDescription << "]: "; getline(cin, s); if (!s.empty()) items[idx].menuDescription = s;

            cout << "\n Cost per person [" << fixed << setprecision(2) << items[idx].costPerPerson << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); float v = items[idx].costPerPerson; ss >> v; if (ss && v >= 0.0f) items[idx].costPerPerson = v; else cout << "  Invalid, keep old.\n"; }

            saveList(items, "caterings.csv");
            cout << "\n Updated.\n Press Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            system("cls"); cout << "== All Caterings ==\n";
            vector<Cater> items = getList<Cater>("caterings.csv");
            if (items.empty()) cout << "\n (none)";
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].caterID << "] " << items[i].caterName
                    << "  RM " << fixed << setprecision(2) << items[i].costPerPerson
                    << "  - " << items[i].menuDescription << "\n";
            }
            cout << "\n Press Enter..."; cin.get();
        }

        else { cout << "\n Invalid option. Press Enter..."; cin.get(); }
    }
}

void manageVendor()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.VendorMenu;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << " Invalid input. Press Enter..."; cin.get(); cin.get(); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x == 0) { catalog(); }

        else if (x == 1) { // Create
            system("cls"); cout << "== Create Vendor ==\n";
            vector<Vendor> items = getList<Vendor>("vendors.csv");

            Vendor v;
            v.vendorID = uniqueIDGenerator<Vendor>("VD", "vendors.csv");
            v.vendorType = getValidatedInput<string>(" Vendor type (e.g., Photographer): ", "non_empty");
            v.person.lastName = getValidatedInput<string>(" Last name: ", "non_empty");
            v.person.firstName = getValidatedInput<string>(" First name: ", "non_empty");
            v.person.email = getValidatedInput<string>(" Email: ", "email");
            v.person.contact = getValidatedInput<string>(" Phone: ", "non_empty");

            while (true) {
                cout << " Service cost (>=0): ";
                string s; getline(cin, s);
                stringstream ss(s); float c = 0.0f; ss >> c;
                if (ss && c >= 0.0f) { v.cost = c; break; }
                cout << "  Invalid cost.\n";
            }

            items.push_back(v);
            saveList(items, "vendors.csv");
            cout << "\n Created [" << v.vendorID << "]. Press Enter..."; cin.get();
        }

        else if (x == 2) { // Remove —— 引用检查
            system("cls"); cout << "== Remove Vendor ==\n";
            vector<Vendor>      items = getList<Vendor>("vendors.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Client>      clients = getList<Client>("clients.csv");

            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i) {
                    string name = items[i].person.lastName;
                    if (!items[i].person.firstName.empty()) { if (!name.empty()) name += ", "; name += items[i].person.firstName; }
                    cout << " [" << items[i].vendorID << "] " << items[i].vendorType
                        << "  " << name << "  RM " << fixed << setprecision(2) << items[i].cost << "\n";
                }
            }

            string vid; cout << "\n Enter Vendor ID to remove: "; getline(cin, vid);

            bool inUse = false; size_t i, k;
            for (i = 0; i < reservations.size() && !inUse; ++i) for (k = 0; k < reservations[i].selectedVendors.size(); ++k)
                if (reservations[i].selectedVendors[k] == vid) { inUse = true; break; }
            if (!inUse) for (i = 0; i < clients.size() && !inUse; ++i) for (k = 0; k < clients[i].selectedVendors.size(); ++k)
                if (clients[i].selectedVendors[k] == vid) { inUse = true; break; }

            if (inUse) { cout << "\n Cannot remove: Vendor is referenced.\nPress Enter..."; cin.get(); continue; }

            bool removed = false; vector<Vendor> kept; kept.reserve(items.size());
            for (i = 0; i < items.size(); ++i) { if (items[i].vendorID == vid) { removed = true; continue; } kept.push_back(items[i]); }
            if (removed) { saveList(kept, "vendors.csv"); cout << " Removed.\n"; }
            else { cout << " Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }

        else if (x == 3) { // Update
            system("cls"); cout << "== Update Vendor ==\n";
            vector<Vendor> items = getList<Vendor>("vendors.csv");
            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i) {
                    string name = items[i].person.lastName;
                    if (!items[i].person.firstName.empty()) { if (!name.empty()) name += ", "; name += items[i].person.firstName; }
                    cout << " [" << items[i].vendorID << "] " << items[i].vendorType
                        << "  " << name << "  RM " << fixed << setprecision(2) << items[i].cost << "\n";
                }
            }

            string vid; cout << "\n Enter Vendor ID to update: "; getline(cin, vid);
            int idx = -1; size_t i; for (i = 0; i < items.size(); ++i) if (items[i].vendorID == vid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found.\nPress Enter..."; cin.get(); continue; }

            string s;
            cout << "\n Vendor type [" << items[idx].vendorType << "]: "; getline(cin, s); if (!s.empty()) items[idx].vendorType = s;

            cout << "\n Last name [" << items[idx].person.lastName << "]: "; getline(cin, s); if (!s.empty()) items[idx].person.lastName = s;
            cout << "\n First name [" << items[idx].person.firstName << "]: "; getline(cin, s); if (!s.empty()) items[idx].person.firstName = s;

            cout << "\n Email [" << items[idx].person.email << "] : "; getline(cin, s);
            if (!s.empty()) {
                // 允许你改成 getValidatedInput，但为保持“不新增函数调用”这里只简单非空检查
                items[idx].person.email = s;
            }

            cout << "\n Phone [" << items[idx].person.contact << "] : "; getline(cin, s); if (!s.empty()) items[idx].person.contact = s;

            cout << "\n Cost [" << fixed << setprecision(2) << items[idx].cost << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); float c = items[idx].cost; ss >> c; if (ss && c >= 0.0f) items[idx].cost = c; else cout << "  Invalid, keep old.\n"; }

            saveList(items, "vendors.csv");
            cout << "\n Updated.\n Press Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            system("cls"); cout << "== All Vendors ==\n";
            vector<Vendor> items = getList<Vendor>("vendors.csv");
            if (items.empty()) cout << "(none)\n";
            else {
                size_t i; for (i = 0; i < items.size(); ++i) {
                    string name = items[i].person.lastName;
                    if (!items[i].person.firstName.empty()) { if (!name.empty()) name += ", "; name += items[i].person.firstName; }
                    cout << " [" << items[i].vendorID << "] " << items[i].vendorType
                        << "  " << name << "  RM " << fixed << setprecision(2) << items[i].cost << "\n";
                }
            }
            cout << "\n Press Enter..."; cin.get();
        }

        else { cout << "\n Invalid option. Press Enter..."; cin.get(); }
    }
}

void manageFoodPackage()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.FoodMenuMgmt;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << " Invalid input. Press Enter..."; cin.get(); cin.get(); continue; }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (x == 0) { catalog(); }

        else if (x == 1) { // Create
            system("cls"); cout << "== Create Food Package ==\n";
            vector<FoodPackage> items = getList<FoodPackage>("food_package.csv");

            FoodPackage f;
            f.foodID = uniqueIDGenerator<FoodPackage>("FP", "food_package.csv");
            cout << " Appetizer: ";   getline(cin, f.appetizer);
            cout << " Main course: "; getline(cin, f.mainCourse);
            cout << " Dessert: ";     getline(cin, f.dessert);
            cout << " Provider: ";    getline(cin, f.provider);

            // Billing mode 归一：PER_PERSON / PER_TABLE / FLAT
            while (true) {
                cout << " Billing mode [1=PER_PERSON, 2=PER_TABLE, 3=FLAT]: ";
                string s; getline(cin, s);
                string t; size_t k;
                for (k = 0; k < s.size(); ++k) {
                    char c = s[k];
                    if (c == ' ' || c == '-' || c == '_' || c == '\t') continue;
                    if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
                    t.push_back(c);
                }
                if (t == "1" || t == "PERPERSON" || t == "PER_PERSON") { f.billingMode = "PER_PERSON"; break; }
                if (t == "2" || t == "PERTABLE" || t == "PER_TABLE") { f.billingMode = "PER_TABLE";  break; }
                if (t == "3" || t == "FLAT") { f.billingMode = "FLAT";       break; }
                cout << "  Invalid billing mode.\n";
            }

            while (true) {
                cout << " Unit price (>=0): ";
                string s; getline(cin, s);
                stringstream ss(s); float v = 0.0f; ss >> v;
                if (ss && v >= 0.0f) { f.unitPrice = v; break; }
                cout << "  Invalid price.\n";
            }

            while (true) {
                int v = getValidatedInput<int>(" Min Guests (>=0, 0=no limit): ");
                if (v >= 0) { f.minGuests = v; break; }
                cout << "  Invalid.\n";
            }
            while (true) {
                int v = getValidatedInput<int>(" Max Guests (>=0, 0=no limit): ");
                if (v >= 0) { f.maxGuests = v; break; }
                cout << "  Invalid.\n";
            }
            while (true) {
                int v = getValidatedInput<int>(" Min Tables (>=0): ");
                if (v >= 0) { f.minTables = v; break; }
                cout << "  Invalid.\n";
            }

            cout << " Description: "; getline(cin, f.description);

            items.push_back(f);
            saveList(items, "food_packages.csv");
            cout << "\n Created [" << f.foodID << "]. Press Enter..."; cin.get();
        }

        else if (x == 2) { // Remove —— 引用检查
            system("cls"); cout << "== Remove Food Package ==\n";
            vector<FoodPackage> items = getList<FoodPackage>("food_packages.csv");
            vector<Reservation> reservations = getList<Reservation>("reservations.csv");
            vector<Client>      clients = getList<Client>("clients.csv");

            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].foodID << "] "
                    << items[i].appetizer << " / " << items[i].mainCourse << " / " << items[i].dessert
                    << "  (" << items[i].billingMode << ")  RM " << fixed << setprecision(2) << items[i].unitPrice << "\n";
            }

            string fid; cout << "\n Enter Food Package ID to remove: "; getline(cin, fid);

            bool inUse = false; size_t i;
            for (i = 0; i < reservations.size(); ++i) if (reservations[i].foodPackageID == fid) { inUse = true; break; }
            if (!inUse) for (i = 0; i < clients.size(); ++i) if (clients[i].foodPackageID == fid) { inUse = true; break; }

            if (inUse) { cout << " Cannot remove: Food package is referenced.\nPress Enter..."; cin.get(); continue; }

            bool removed = false; vector<FoodPackage> kept; kept.reserve(items.size());
            for (i = 0; i < items.size(); ++i) { if (items[i].foodID == fid) { removed = true; continue; } kept.push_back(items[i]); }
            if (removed) { saveList(kept, "food_packages.csv"); cout << " Removed.\n"; }
            else { cout << " Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }

        else if (x == 3) { // Update
            system("cls"); cout << "== Update Food Package ==\n";
            vector<FoodPackage> items = getList<FoodPackage>("food_packages.csv");
            if (items.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].foodID << "] "
                    << items[i].appetizer << " / " << items[i].mainCourse << " / " << items[i].dessert
                    << "  (" << items[i].billingMode << ")  RM " << fixed << setprecision(2) << items[i].unitPrice << "\n";
            }

            string fid; cout << "\n Enter Food Package ID to update: "; getline(cin, fid);
            int idx = -1; size_t i; for (i = 0; i < items.size(); ++i) if (items[i].foodID == fid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found.\nPress Enter..."; cin.get(); continue; }

            string s;
            cout << "\n Appetizer [" << items[idx].appetizer << "]: "; getline(cin, s); if (!s.empty()) items[idx].appetizer = s;
            cout << "\n Main course [" << items[idx].mainCourse << "]: "; getline(cin, s); if (!s.empty()) items[idx].mainCourse = s;
            cout << "\n Dessert [" << items[idx].dessert << "]: "; getline(cin, s); if (!s.empty()) items[idx].dessert = s;
            cout << "\n Provider [" << items[idx].provider << "]: "; getline(cin, s); if (!s.empty()) items[idx].provider = s;

            cout << "\n Billing mode [" << items[idx].billingMode << "] (1=PER_PERSON,2=PER_TABLE,3=FLAT): ";
            getline(cin, s);
            if (!s.empty()) {
                string t; size_t k;
                for (k = 0; k < s.size(); ++k) {
                    char c = s[k];
                    if (c == ' ' || c == '-' || c == '_' || c == '\t') continue;
                    if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');
                    t.push_back(c);
                }
                if (t == "1" || t == "PERPERSON" || t == "PER_PERSON") items[idx].billingMode = "PER_PERSON";
                else if (t == "2" || t == "PERTABLE" || t == "PER_TABLE") items[idx].billingMode = "PER_TABLE";
                else if (t == "3" || t == "FLAT") items[idx].billingMode = "FLAT";
                else cout << "  Invalid mode, keep old.\n";
            }

            cout << "\n Unit price [" << fixed << setprecision(2) << items[idx].unitPrice << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); float v = items[idx].unitPrice; ss >> v; if (ss && v >= 0.0f) items[idx].unitPrice = v; else cout << "  Invalid, keep old.\n"; }

            cout << "\n Min Guests [" << items[idx].minGuests << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); int n = items[idx].minGuests; ss >> n; if (ss && n >= 0) items[idx].minGuests = n; else cout << "  Invalid, keep old.\n"; }

            cout << "\n Max Guests [" << items[idx].maxGuests << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); int n = items[idx].maxGuests; ss >> n; if (ss && n >= 0) items[idx].maxGuests = n; else cout << "  Invalid, keep old.\n"; }

            cout << "\n Min Tables [" << items[idx].minTables << "] : ";
            getline(cin, s);
            if (!s.empty()) { stringstream ss(s); int n = items[idx].minTables; ss >> n; if (ss && n >= 0) items[idx].minTables = n; else cout << "  Invalid, keep old.\n"; }

            cout << "\n Description [" << items[idx].description << "] : ";
            getline(cin, s); if (!s.empty()) items[idx].description = s;

            saveList(items, "food_packages.csv");
            cout << "\n Updated.\n Press Enter..."; cin.get();
        }

        else if (x == 4) { // Show All
            system("cls"); cout << "== All Food Packages ==\n";
            vector<FoodPackage> items = getList<FoodPackage>("food_packages.csv");
            if (items.empty()) cout << "(none)\n";
            else {
                size_t i; for (i = 0; i < items.size(); ++i)
                    cout << " [" << items[i].foodID << "] "
                    << items[i].appetizer << " / " << items[i].mainCourse << " / " << items[i].dessert
                    << "  (" << items[i].billingMode << ")  RM " << fixed << setprecision(2) << items[i].unitPrice << "\n";
            }

            // == 在列完所有 FoodPackage 后，追加查看某套餐的明细 ==
            cout << "\n View menu items for a Food ID (blank = skip): ";
            string q; getline(cin, q);
            if (!q.empty()) {
                vector<FoodMenuItem> all = getList<FoodMenuItem>("food_menu_items.csv");
                bool any = false;
                size_t i;

                cout << "\n == Menu Items for [" << q << "] ==\n";
                for (i = 0; i < all.size(); ++i) {
                    if (all[i].foodID == q) {
                        any = true;
                        cout << "  [" << all[i].category << "] "
                            << all[i].itemName;
                        if (!all[i].allergens.empty()) cout << "  (Allergens: " << all[i].allergens << ")";
                        if (all[i].priceDelta > 0.0001f) cout << "  (+RM" << fixed << setprecision(2) << all[i].priceDelta << ")";
                        if (!all[i].note.empty()) cout << "  - " << all[i].note;
                        cout << "\n";
                    }
                }
                if (!any) cout << "  (no items found)\n";
            }

            cout << " Press Enter..."; cin.get();
        }

        else { cout << " Invalid option. Press Enter..."; cin.get(); }
    }
}

void operations()
{
    StringConst strConst;
    int x;
    while (true)
    {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.OperationsMenu;
        x = getValidatedInput<int>(" Choose an option: ", "", " \nInvalid option. Please enter a number: ");
        if (x == 0)
        {
            showMainScreen();
        }
        if (x == 1)
        {
            manageGuest();
        }
        else if (x == 2)
        {
            manageSchedule();
        }
        else if (x == 3)
        {
            managePayment();
        }
        else if (x == 4)
        {
            manageClient();
        }
        else if (x == 5)
        {
            manageAdmin();
        }
        else
        {
            cout << " Invalid option.\n Press Enter...";
            cin.get();
        }
    }
}

void manageClient() {
    StringConst strConst;
    int x;

    // 读取数据
    vector<Client>      clients = getList<Client>("clients.csv");
    vector<Reservation> reservations = getList<Reservation>("reservations.csv");

    // —— 小工具（lambda，非全局函数） ——————————————————————
    auto saveClients = [&]() {
        saveList(clients, "clients.csv");
        };
    auto trim = [](string& s) {
        size_t a = 0, b = s.size();
        while (a < b && isspace((unsigned char)s[a])) ++a;
        while (b > a && isspace((unsigned char)s[b - 1])) --b;
        s = s.substr(a, b - a);
        };
    auto lower = [&](const string& s)->string {
        string t = s;
        for (size_t i = 0; i < t.size(); ++i) t[i] = (char)tolower((unsigned char)t[i]);
        return t;
        };
    auto fullName = [&](const Person& p)->string {
        return p.lastName.empty() ? p.firstName : (p.lastName + ", " + p.firstName);
        };
    // 重复判定：同 姓+名，且 email 或 phone 任一匹配
    auto findDuplicateIndex = [&](const Person& p)->int {
        for (size_t i = 0; i < clients.size(); ++i) {
            bool sameName = (clients[i].person.firstName == p.firstName &&
                clients[i].person.lastName == p.lastName);
            bool sameContact = (!p.email.empty() && clients[i].person.email == p.email) ||
                (!p.contact.empty() && clients[i].person.contact == p.contact);
            if (sameName && sameContact) return (int)i;
        }
        return -1;
        };
    // 通过 ID 定位
    auto findIndexByID = [&](const string& cid)->int {
        for (size_t i = 0; i < clients.size(); ++i) if (clients[i].clientID == cid) return (int)i;
        return -1;
        };
    // 通过关键词过滤（姓名/邮箱/电话）
    auto filterClients = [&](const string& q)->vector<int> {
        vector<int> hits;
        string qq = lower(q);
        for (size_t i = 0; i < clients.size(); ++i) {
            string nm = lower(fullName(clients[i].person));
            string em = lower(clients[i].person.email);
            string ph = lower(clients[i].person.contact);
            if (qq.empty() || nm.find(qq) != string::npos || em.find(qq) != string::npos || ph.find(qq) != string::npos)
                hits.push_back((int)i);
        }
        return hits;
        };
    // 删除前检查：若有 reservation 绑定此 client，则不允许删
    auto canDeleteClient = [&](const string& cid)->bool {
        for (size_t i = 0; i < reservations.size(); ++i) if (reservations[i].clientID == cid) return false;
        return true;
        };
    // 展示（支持可选过滤）
    auto showClients = [&](const string& q) {
        vector<int> idxs = filterClients(q);
        vector<vector<pair<string, string>>> recs;
        for (size_t k = 0; k < idxs.size(); ++k) {
            const Client& c = clients[(size_t)idxs[k]];
            recs.push_back({
                pair<string,string>("Client ID",   c.clientID),
                pair<string,string>("Name",        fullName(c.person)),
                pair<string,string>("Email",       c.person.email),
                pair<string,string>("Phone",       c.person.contact),
                pair<string,string>("Partner",     c.partnerName),
                pair<string,string>("Wedding Date",c.weddingDate),
                pair<string,string>("Guests/Tables", to_string(c.guestCount) + "/" + to_string(c.tableCount)),
                pair<string,string>("Note",        c.specialRequest)
                });
        }
        if (recs.empty()) cout << "No clients found.\n";
        else printRecords<string>(recs, 1);
        };

    // —— 菜单循环 ————————————————————————————————
    while (true) {
        system("cls");
        cout << strConst.LOGO_O << endl;
        cout << strConst.TITLE << endl;
        cout << strConst.ClientMenu;

        x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");
        if (x == 0) { showMainScreen(); return; }

        // 1) Create Client
        else if (x == 1) {
            system("cls");
            cout << "== Create Client ==\n";
            Client c;

            // 基本信息
            c.person.lastName = getValidatedInput<string>("Last name (姓): ", "non_empty");
            c.person.firstName = getValidatedInput<string>("First name (名): ", "non_empty");
            c.person.contact = getValidatedInput<string>("Phone: ", "non_empty");
            c.person.email = getValidatedInput<string>("Email: ", "email");
            trim(c.person.lastName); trim(c.person.firstName);
            trim(c.person.contact);  trim(c.person.email);

            // 重复检查
            int dup = findDuplicateIndex(c.person);
            if (dup >= 0) {
                cout << "Existing client found: " << clients[(size_t)dup].clientID
                    << " - " << fullName(clients[(size_t)dup].person) << "\n";
                string upd = getValidatedInput<string>("Update that client instead? (Y/N): ", "non_empty");
                if (upd == "Y" || upd == "y") {
                    // 跳到更新流程（沿用 3号分支的表单）
                    int i = dup;
                    cout << "\n-- Update Fields (Enter to keep) --\n";
                    string s;

                    s = updateField(clients[(size_t)i].partnerName, "Partner name: ");
                    if (!s.empty()) clients[(size_t)i].partnerName = s;

                    s = updateField(clients[(size_t)i].weddingDate, "Wedding date (YYYY-MM-DD): ", "date");
                    if (!s.empty()) clients[(size_t)i].weddingDate = s;

                    s = updateField(clients[(size_t)i].specialRequest, "Special request: ");
                    if (!s.empty()) clients[(size_t)i].specialRequest = s;

                    // 也允许同步基础信息
                    s = updateField(clients[(size_t)i].person.email, "Email: ", "email");
                    if (!s.empty()) clients[(size_t)i].person.email = s;

                    s = updateField(clients[(size_t)i].person.contact, "Phone: ");
                    if (!s.empty()) clients[(size_t)i].person.contact = s;

                    saveClients();
                    cout << "Updated.\nPress Enter..."; cin.get();
                }
                else {
                    cout << "Create aborted.\nPress Enter..."; cin.get();
                }
                continue;
            }

            // 其它可选信息
            c.partnerName = getValidatedInput<string>("Partner name (blank allowed): ");
            c.weddingDate = getValidatedInput<string>("Wedding date (YYYY-MM-DD, blank allowed): ");
            if (!c.weddingDate.empty()) {
                // 简单校验可用 getValidatedInput 的 "date"，但这里允许空，所以手动判空即可
            }
            c.specialRequest = getValidatedInput<string>("Special request (blank allowed): ");
            c.guestCount = getValidatedInput<int>("Guest count (0 allowed): ");
            c.tableCount = getValidatedInput<int>("Table count (0 allowed): ");

            // ID 与初始状态
            c.clientID = uniqueIDGenerator<Client>("C", "clients.csv");
            c.selectedPackage.clear();
            c.venueBooked.clear();
            c.foodPackageID.clear();
            c.cateringSelected.clear();
            c.selectedVendors.clear();
            c.totalPayment = 0.0f;
            c.amountPaid = 0.0f;
            c.paymentStatus = "UNPAID";

            clients.push_back(c);
            saveClients();

            cout << "Created: " << c.clientID << " - " << fullName(c.person) << "\n";
            cout << "Press Enter..."; cin.get();
        }

        // 2) Remove Client
        else if (x == 2) {
            system("cls");
            cout << "== Remove Client ==\n";
            string cid = getValidatedInput<string>("Enter Client ID: ", "non_empty");
            int i = findIndexByID(cid);
            if (i < 0) { cout << "Client not found.\nPress Enter..."; cin.get(); continue; }
            if (!canDeleteClient(cid)) {
                cout << "Cannot delete: there are reservations under this client.\n";
                cout << "Please cancel those reservations first.\nPress Enter..."; cin.get(); continue;
            }
            cout << "Delete " << clients[(size_t)i].clientID << " - " << fullName(clients[(size_t)i].person) << "? (Y/N): ";
            string yn; getline(cin, yn); trim(yn);
            if (yn == "Y" || yn == "y") {
                clients.erase(clients.begin() + i);
                saveClients();
                cout << "Deleted.\n";
            }
            else {
                cout << "Aborted.\n";
            }
            cout << "Press Enter..."; cin.get();
        }

        // 3) Update Client
        else if (x == 3) {
            system("cls");
            cout << "== Update Client ==\n";
            // 支持：直接输 ID；或留空→按关键词检索
            string cid = getValidatedInput<string>("Enter Client ID (leave blank to search): ");
            int i = -1;
            if (!cid.empty()) {
                i = findIndexByID(cid);
                if (i < 0) { cout << "Client not found.\nPress Enter..."; cin.get(); continue; }
            }
            else {
                string q = getValidatedInput<string>("Keyword (name/email/phone): ");
                vector<int> hits = filterClients(q);
                if (hits.empty()) { cout << "No match.\nPress Enter..."; cin.get(); continue; }
                if (hits.size() > 1) {
                    cout << "Select one:\n";
                    for (size_t k = 0; k < hits.size(); ++k) {
                        const Client& c = clients[(size_t)hits[k]];
                        cout << " [" << k << "] " << c.clientID << " | " << fullName(c.person)
                            << " | " << c.person.email << " | " << c.person.contact << "\n";
                    }
                    int pick = getValidatedInput<int>("Index: ");
                    if (pick < 0 || pick >= (int)hits.size()) { cout << "Invalid.\nPress Enter..."; cin.get(); continue; }
                    i = hits[(size_t)pick];
                }
                else {
                    i = hits[0];
                }
            }

            cout << "\n-- Update Fields (Enter to keep) --\n";
            string s;

            // 姓名拆分编辑
            s = updateField(clients[(size_t)i].person.lastName, "Last name (姓): ");
            if (!s.empty()) clients[(size_t)i].person.lastName = s;
            s = updateField(clients[(size_t)i].person.firstName, "First name (名): ");
            if (!s.empty()) clients[(size_t)i].person.firstName = s;

            s = updateField(clients[(size_t)i].person.email, "Email: ", "email");
            if (!s.empty()) clients[(size_t)i].person.email = s;

            s = updateField(clients[(size_t)i].person.contact, "Phone: ");
            if (!s.empty()) clients[(size_t)i].person.contact = s;

            s = updateField(clients[(size_t)i].partnerName, "Partner name: ");
            if (!s.empty()) clients[(size_t)i].partnerName = s;

            s = updateField(clients[(size_t)i].weddingDate, "Wedding date (YYYY-MM-DD): ", "date");
            if (!s.empty()) clients[(size_t)i].weddingDate = s;

            s = updateField(clients[(size_t)i].specialRequest, "Special request: ");
            if (!s.empty()) clients[(size_t)i].specialRequest = s;

            // 这些字段只做资料性维护（不做结账）——可选：
            {
                int v = updateField(clients[(size_t)i].guestCount, "Guest count (0 to keep): ");
                if (v > 0) clients[(size_t)i].guestCount = v;
            }
            {
                int v = updateField(clients[(size_t)i].tableCount, "Table count (0 to keep): ");
                if (v > 0) clients[(size_t)i].tableCount = v;
            }

            saveClients();
            cout << "Updated.\nPress Enter..."; cin.get();
        }

        // 4) Show All Clients（带可选过滤）
        else if (x == 4) {
            system("cls");
            cout << "== Show Clients ==\n";
            string q = getValidatedInput<string>("Filter keyword (blank = show all): ");
            showClients(q);
            cout << "Press Enter..."; cin.get();
        }

        // 5) Checkout / Reservation（保持你的菜单项：跳转到 Reservation/Checkout）
        else if (x == 5) {
            // 不在 Client 做结账；跳到 Reservation 的结账/流程
            checkoutReservationWizard();
            // 返回后可能有外部变更，刷新本地缓存
            clients = getList<Client>("clients.csv");
            reservations = getList<Reservation>("reservations.csv");
        }

        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void manageGuest() {
    StringConst strConst;

    while (true) {
        system("cls");
        cout << strConst.GuestMenu;
        int x = getValidatedInput<int>(" Choose: ");
        if (x == 0) return;

        else if (x == 1) {
            // 1) Import Guest List（支持单条添加 或 从CSV导入）
            system("cls");
            cout << "Import Guest List\n";
            string reservationID = getValidatedInput<string>("Reservation ID: ", "non_empty");

            cout << " 1. Add a single guest\n";
            cout << " 2. Import from CSV file (last,first,email,phone,meal)\n";
            int mode = getValidatedInput<int>(" Choose: ");
            vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");

            if (mode == 1) {
                GuestRecord g;
                g.reservationID = reservationID;
                g.person.lastName = getValidatedInput<string>("Last name: ", "non_empty");
                g.person.firstName = getValidatedInput<string>("First name: ", "non_empty");
                g.person.email = getValidatedInput<string>("Email: ", "email");
                g.person.contact = getValidatedInput<string>("Phone: ", "non_empty");
                g.rsvpStatus = getValidatedInput<string>("RSVP (YES/NO/MAYBE): ", "non_empty");
                g.mealPreference = getValidatedInput<string>("Meal preference: ");
                g.tableNumber = -1;
                g.guestID = nextGuestIDForReservation(reservationID, guests);
                guests.push_back(g);
                saveList(guests, "guests.csv");
                cout << "Guest added: " << g.guestID << "\n";
                cout << "Press Enter..."; cin.get();
            }
            else if (mode == 2) {
                string path = getValidatedInput<string>(" CSV file path: ", "non_empty");
                ifstream fin(path.c_str());
                if (!fin) {
                    cout << "Cannot open file.\n"; cin.get(); continue;
                }
                string line;
                int count = 0;
                while (getline(fin, line)) {
                    if (line.empty()) continue;
                    string ln, fn, em, ph, meal;
                    stringstream ss(line);
                    getline(ss, ln, ',');
                    getline(ss, fn, ',');
                    getline(ss, em, ',');
                    getline(ss, ph, ',');
                    getline(ss, meal);

                    GuestRecord g;
                    g.reservationID = reservationID;
                    g.person.lastName = ln;
                    g.person.firstName = fn;
                    g.person.email = em;
                    g.person.contact = ph;
                    g.rsvpStatus = "INVITED";
                    g.mealPreference = meal;
                    g.tableNumber = -1;
                    g.guestID = nextGuestIDForReservation(reservationID, guests);

                    guests.push_back(g);
                    count++;
                }
                fin.close();
                saveList(guests, "guests.csv");
                cout << "Imported " << count << " guests.\n";
                cout << "Press Enter..."; cin.get();
            }
            else {
                cout << "Invalid choice.\n"; cin.get();
            }
        }

        else if (x == 2) {
            // 2) Update Guest RSVP
            system("cls");
            cout << "Update Guest RSVP\n";
            string reservationID = getValidatedInput<string>("Reservation ID: ", "non_empty");
            vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");

            // 列出该预约下的来宾
            size_t i;
            int shown = 0;
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].reservationID == reservationID) {
                    cout << setw(14) << left << guests[i].guestID
                        << "  " << guests[i].person.lastName << ", " << guests[i].person.firstName
                        << "  RSVP=" << guests[i].rsvpStatus
                        << "  Table=" << guests[i].tableNumber
                        << "\n";
                    shown++;
                }
            }
            if (shown == 0) { cout << "No guests found.\n"; cin.get(); continue; }

            string gid = getValidatedInput<string>(" GuestID to update: ", "non_empty");
            int found = -1;
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].guestID == gid && guests[i].reservationID == reservationID) {
                    found = (int)i; break;
                }
            }
            if (found < 0) { cout << "Guest not found.\n"; cin.get(); continue; }

            string newRSVP = getValidatedInput<string>(" New RSVP (YES/NO/MAYBE): ", "non_empty");
            guests[found].rsvpStatus = newRSVP;

            // 可选：顺便更新用餐或电话等
            string s = getValidatedInput<string>(" Update meal (Enter to skip): ");
            if (!s.empty()) guests[found].mealPreference = s;

            saveList(guests, "guests.csv");
            cout << "Updated.\n"; cin.get();
        }

        else if (x == 3) {
            // 3) Show Guest List
            system("cls");
            cout << "Show Guest List\n";
            string reservationID = getValidatedInput<string>("Reservation ID: ", "non_empty");
            vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");

            size_t i;
            int shown = 0;
            cout << left << setw(14) << "GuestID" << "  "
                << setw(20) << "Name" << "  "
                << setw(20) << "Email" << "  "
                << setw(14) << "Phone" << "  "
                << setw(8) << "RSVP" << "  "
                << setw(6) << "Table" << "\n";
            cout << string(90, '-') << "\n";
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].reservationID == reservationID) {
                    string name = guests[i].person.lastName + ", " + guests[i].person.firstName;
                    cout << setw(14) << left << guests[i].guestID << "  "
                        << setw(20) << name << "  "
                        << setw(20) << guests[i].person.email << "  "
                        << setw(14) << guests[i].person.contact << "  "
                        << setw(8) << guests[i].rsvpStatus << "  "
                        << setw(6) << guests[i].tableNumber << "\n";
                    shown++;
                }
            }
            if (shown == 0) cout << "No guests for this reservation.\n";
            cout << "Press Enter..."; cin.get();
        }

        else if (x == 4) {
            // 4) Assign Seating（按桌号轮转分配）
            system("cls");
            cout << "Assign Seating\n";
            string reservationID = getValidatedInput<string>("Reservation ID: ", "non_empty");

            // 从 reservation 里读桌数（如无，则让用户输入）
            vector<Reservation> rs = getList<Reservation>("reservations.csv");
            int tableCount = 0;
            size_t i;
            for (i = 0; i < rs.size(); ++i) {
                if (rs[i].reservationID == reservationID) { tableCount = rs[i].tableCount; break; }
            }
            if (tableCount <= 0) {
                tableCount = getValidatedInput<int>(" Table count: ");
                if (tableCount <= 0) { cout << "Invalid table count.\n"; cin.get(); continue; }
            }

            vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");
            // 过滤出该预约的来宾
            vector<int> idx;
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].reservationID == reservationID) idx.push_back((int)i);
            }
            if (idx.empty()) { cout << "No guests to assign.\n"; cin.get(); continue; }

            // 轮转分配桌号 1..tableCount
            int t = 1;
            size_t k;
            for (k = 0; k < idx.size(); ++k) {
                guests[idx[k]].tableNumber = t;
                t++;
                if (t > tableCount) t = 1;
            }
            saveList(guests, "guests.csv");
            cout << "Assigned " << (int)idx.size() << " guests across " << tableCount << " tables.\n";
            cout << "Press Enter..."; cin.get();
        }

        else if (x == 5) {
            // 5) Show Seating Plan（按桌号分组展示）
            system("cls");
            cout << "Show Seating Plan\n";
            string reservationID = getValidatedInput<string>("Reservation ID: ", "non_empty");
            vector<GuestRecord> guests = getList<GuestRecord>("guests.csv");

            // 统计最大桌号
            size_t i;
            int maxTable = 0;
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].reservationID == reservationID) {
                    if (guests[i].tableNumber > maxTable) maxTable = guests[i].tableNumber;
                }
            }
            if (maxTable <= 0) { cout << "No seating assigned.\n"; cin.get(); continue; }

            // 分组
            vector< vector<string> > tables;
            tables.resize(maxTable + 1);
            for (i = 0; i < guests.size(); ++i) {
                if (guests[i].reservationID == reservationID && guests[i].tableNumber > 0) {
                    string name = guests[i].person.lastName + ", " + guests[i].person.firstName;
                    tables[guests[i].tableNumber].push_back(name);
                }
            }

            // 打印
            int tb;
            for (tb = 1; tb <= maxTable; ++tb) {
                cout << "Table " << tb << ":\n";
                if (tables[tb].empty()) {
                    cout << "  (empty)\n";
                }
                else {
                    size_t j;
                    for (j = 0; j < tables[tb].size(); ++j) {
                        cout << "  - " << tables[tb][j] << "\n";
                    }
                }
                cout << "\n";
            }
            cout << "Press Enter..."; cin.get();
        }

        else {
            cout << "Invalid choice.\n"; cin.get();
        }
    }
}

void manageSchedule()
{
    StringConst strConst;
    vector<EventSchedule> schedules = getList<EventSchedule>("schedules.csv");

    while (true)
    {
        system("cls");
        cout << strConst.ScheduleMenu;

        int x;
        cout << " Choose an option: ";
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input.\nPress Enter...";
            cin.get(); cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // eat '\n'

        if (x == 0) return;

        else if (x == 1)  // Create
        {
            system("cls");
            cout << "== Create Schedule ==\n";
            EventSchedule s;

            s.scheduleID = uniqueIDGenerator<EventSchedule>("S", "schedules.csv");

            cout << " Reservation ID (e.g., R0001): ";
            getline(cin, s.reservationID);

            s.weddingDate = getValidatedInput<string>(" Date (YYYY-MM-DD): ", "date");
            cout << " Time (HH:MM): ";
            getline(cin, s.time);
            cout << " Activity: ";
            getline(cin, s.activity);

            schedules.push_back(s);
            saveList(schedules, "schedules.csv");

            cout << " Created.\nPress Enter..."; cin.get();
        }
        else if (x == 2)  // Update
        {
            system("cls");
            cout << "== Update Schedule ==\n";

            if (schedules.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i;
                for (i = 0; i < schedules.size(); ++i) {
                    cout << setw(10) << left << "ID:" << schedules[i].scheduleID
                        << "  Reservation:" << schedules[i].reservationID
                        << "  Date:" << schedules[i].weddingDate
                        << "  Time:" << schedules[i].time
                        << "  Act:" << schedules[i].activity << "\n";
                }
            }

            string sid, sline;
            cout << "\n Enter schedule ID to update: ";
            getline(cin, sid);

            int idx = -1; size_t i;
            for (i = 0; i < schedules.size(); ++i) if (schedules[i].scheduleID == sid) { idx = (int)i; break; }
            if (idx < 0) { cout << " Not found.\nPress Enter..."; cin.get(); continue; }

            cout << " Reservation ID [" << schedules[idx].reservationID << "] : ";
            getline(cin, sline); if (!sline.empty()) schedules[idx].reservationID = sline;

            cout << " New date (YYYY-MM-DD) [Current: " << schedules[idx].weddingDate << "] : ";
            getline(cin, sline); if (!sline.empty()) schedules[idx].weddingDate = sline;

            cout << " New time (HH:MM) [Current: " << schedules[idx].time << "] : ";
            getline(cin, sline); if (!sline.empty()) schedules[idx].time = sline;

            cout << " New activity [Current: " << schedules[idx].activity << "] : ";
            getline(cin, sline); if (!sline.empty()) schedules[idx].activity = sline;

            saveList(schedules, "schedules.csv");
            cout << " Updated.\nPress Enter..."; cin.get();
        }
        else if (x == 3)  // Remove
        {
            system("cls");
            cout << "== Remove Schedule ==\n";

            if (schedules.empty()) { cout << "(none)\nPress Enter..."; cin.get(); continue; }
            else {
                size_t i;
                for (i = 0; i < schedules.size(); ++i) {
                    cout << setw(10) << left << "ID:" << schedules[i].scheduleID
                        << "  Reservation:" << schedules[i].reservationID
                        << "  Date:" << schedules[i].weddingDate
                        << "  Time:" << schedules[i].time
                        << "  Act:" << schedules[i].activity << "\n";
                }
            }

            string sid; cout << "\n Enter schedule ID to remove: "; getline(cin, sid);

            bool removed = false;
            vector<EventSchedule> kept; kept.reserve(schedules.size());
            size_t i;
            for (i = 0; i < schedules.size(); ++i) {
                if (schedules[i].scheduleID == sid) { removed = true; continue; }
                kept.push_back(schedules[i]);
            }
            schedules.swap(kept);

            if (removed) { saveList(schedules, "schedules.csv"); cout << " Removed.\n"; }
            else { cout << " Not found.\n"; }
            cout << " Press Enter..."; cin.get();
        }
        else if (x == 4)  // Show All
        {
            system("cls");
            cout << "== All Schedules ==\n";
            if (schedules.empty()) cout << "(none)\n";
            else {
                size_t i;
                for (i = 0; i < schedules.size(); ++i) {
                    cout << setw(10) << left << "ID:" << schedules[i].scheduleID
                        << "  Reservation:" << schedules[i].reservationID
                        << "  Date:" << schedules[i].weddingDate
                        << "  Time:" << schedules[i].time
                        << "  Act:" << schedules[i].activity << "\n";
                }
            }
            cout << " Press Enter..."; cin.get();
        }
        else {
            cout << " Invalid option.\nPress Enter..."; cin.get();
        }
    }
}

void manageAdmin() {
    StringConst sc;
    vector<Admin> admins = getList<Admin>("admins.csv");

    while (true) {
        clearScreen();
        cout << sc.LOGO_O << endl;
        cout << sc.TITLE << endl;
        cout << sc.AdminMenu;

        int x = getValidatedInput<int>(" Choose an option: ", "", " Invalid option. Please enter a number: ");

        if (x == 0) 
            return; 

        else if (x == 1) 
        { 
            clearScreen();
            cout << "Create Admin\n";
            string uname = getValidatedInput<string>(" New username: ", "non_empty");
            string pwd = maskedInput(" New password: ");

            bool exists = false;
            for (size_t i = 0; i < admins.size(); i++) {
                if (admins[i].username == uname) exists = true;
            }
            if (exists) {
                cout << "Username already exists.\n"; cin.get();
                continue;
            }

            Admin a; a.username = uname; a.password = pwd;
            admins.push_back(a);
            saveList(admins, "admins.csv");
            cout << "Created.\n"; cin.get();
        }
        else if (x == 2) { // Remove
            clearScreen();
            cout << "Remove Admin\n";
            string uname = getValidatedInput<string>(" Username to remove: ", "non_empty");

            int idx = -1;
            for (size_t i = 0; i < admins.size(); i++) {
                if (admins[i].username == uname) idx = int(i);
            }
            if (idx == -1) {
                cout << "Not found.\n"; cin.get();
                continue;
            }
            admins.erase(admins.begin() + idx);
            saveList(admins, "admins.csv");
            cout << "Removed.\n"; cin.get();
        }
        else if (x == 3) { // Update
            clearScreen();
            cout << "Update Admin\n";
            string uname = getValidatedInput<string>(" Username to update: ", "non_empty");

            int idx = -1;
            for (size_t i = 0; i < admins.size(); i++) {
                if (admins[i].username == uname) idx = int(i);
            }
            if (idx == -1) {
                cout << "Not found.\n"; cin.get();
                continue;
            }

            cout << "Leave blank to keep old value.\n";
            string newU = updateField(admins[idx].username, " New username: ", "non_empty");
            if (!newU.empty()) admins[idx].username = newU;
            string newP = maskedInput(" New password (Enter to skip): ");
            if (!newP.empty()) admins[idx].password = newP;

            saveList(admins, "admins.csv");
            cout << "Updated.\n"; cin.get();
        }
        else if (x == 4) { // Show All
            clearScreen();
            cout << "All Admins:\n";
            for (size_t i = 0; i < admins.size(); i++) {
                cout << i + 1 << ". " << admins[i].username << " , " << admins[i].password << "\n";
            }
            cin.get();
        }
    }
}

void searchFun()
{
    StringConst strConst;

    while (true)
    {
        system("cls");
        cout << strConst.SearchMenu;

        int x;
        cout << " Choose: ";
        if (!(cin >> x)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << " Invalid input.\nPress Enter...";
            cin.get(); cin.get();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 吃掉回车

        if (x == 0) { showMainScreen(); }

        else if (x == 1) // Search Client
        {
            vector<Client> clients = getList<Client>("clients.csv");
            string q;
            cout << " Keyword (ID/Name/Email/Phone/Date): ";
            getline(cin, q);

            // q -> lower
            string ql = q;
            size_t i;
            for (i = 0; i < ql.size(); ++i) ql[i] = char(tolower((unsigned char)ql[i]));

            int shown = 0;
            cout << endl << endl;
            cout << left << setw(10) << "ID" << "  "
                << setw(24) << "Name" << "  "
                << setw(22) << "Email" << "  "
                << setw(14) << "Phone" << "  "
                << setw(12) << "Wedding" << "  "
                << "Status" << "\n";
            cout << string(90, '-') << "\n";

            for (i = 0; i < clients.size(); ++i)
            {
                // 拼名字
                string name = clients[i].person.lastName;
                if (!clients[i].person.firstName.empty()) {
                    if (!name.empty()) name += ", ";
                    name += clients[i].person.firstName;
                }

                // 字段转小写
                string a = clients[i].clientID;       for (size_t j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = name;                      for (size_t j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = clients[i].person.email;   for (size_t j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                string d = clients[i].person.contact; for (size_t j = 0; j > d.size(); ++j) d[j] = char(tolower((unsigned char)d[j]));
                string e = clients[i].weddingDate;    for (size_t j = 0; j < e.size(); ++j) e[j] = char(tolower((unsigned char)e[j]));

                if (a.find(ql) != string::npos ||
                    b.find(ql) != string::npos ||
                    c.find(ql) != string::npos ||
                    d.find(ql) != string::npos ||
                    e.find(ql) != string::npos)
                {
                    cout << setw(10) << left << clients[i].clientID << "  "
                        << setw(24) << name << "  "
                        << setw(22) << clients[i].person.email << "  "
                        << setw(14) << clients[i].person.contact << "  "
                        << setw(12) << clients[i].weddingDate << "  "
                        << clients[i].paymentStatus << "\n";
                    shown++;
                }
            }

            if (shown == 0) cout << " No matches.\n";
            cout << "\n\n Press Enter..."; cin.get();
        }
        else if (x == 2) // Search Vendor
        {
            vector<Vendor> vendors = getList<Vendor>("vendors.csv");
            string q;
            cout << " Keyword (ID/Type/Name/Email/Phone): ";
            getline(cin, q);

            string ql = q;
            size_t i;
            for (i = 0; i < ql.size(); ++i) ql[i] = char(tolower((unsigned char)ql[i]));

            int shown = 0;
            cout << endl << endl;
            cout << left << setw(10) << "ID" << "  "
                << setw(14) << "Type" << "  "
                << setw(24) << "Name" << "  "
                << setw(22) << "Email" << "  "
                << setw(14) << "Phone" << "  "
                << "Cost" << "\n";
            cout << string(90, '-') << "\n";

            for (i = 0; i < vendors.size(); ++i)
            {
                string name = vendors[i].person.lastName;
                if (!vendors[i].person.firstName.empty()) {
                    if (!name.empty()) name += ", ";
                    name += vendors[i].person.firstName;
                }

                string a = vendors[i].vendorID;      for (size_t j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = vendors[i].vendorType;    for (size_t j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = name;                     for (size_t j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                string d = vendors[i].person.email;  for (size_t j = 0; j < d.size(); ++j) d[j] = char(tolower((unsigned char)d[j]));
                string e = vendors[i].person.contact; for (size_t j = 0; j < e.size(); ++j) e[j] = char(tolower((unsigned char)e[j]));

                if (a.find(ql) != string::npos ||
                    b.find(ql) != string::npos ||
                    c.find(ql) != string::npos ||
                    d.find(ql) != string::npos ||
                    e.find(ql) != string::npos)
                {
                    cout << setw(10) << left << vendors[i].vendorID << "  "
                        << setw(14) << vendors[i].vendorType << "  "
                        << setw(24) << name << "  "
                        << setw(22) << vendors[i].person.email << "  "
                        << setw(14) << vendors[i].person.contact << "  "
                        << fixed << setprecision(2) << vendors[i].cost << "\n";
                    shown++;
                }
            }

            if (shown == 0) cout << " No matches.\n";
            cout << "\n\n Press Enter..."; cin.get();
        }
        else if (x == 3) // Search Package / Venue / Catering
        {
            vector<Package> packages = getList<Package>("packages.csv");
            vector<Venue>   venues = getList<Venue>("venues.csv");
            vector<Cater>   caters = getList<Cater>("caterings.csv");

            string q;
            cout << " Keyword: ";
            getline(cin, q);

            string ql = q;
            size_t i;
            for (i = 0; i < ql.size(); ++i) ql[i] = char(tolower((unsigned char)ql[i]));

            // Packages
            cout << "\n Packages matched:\n";
            int shown = 0;
            for (i = 0; i < packages.size(); ++i) {
                string a = packages[i].packageID;   for (size_t j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = packages[i].packageName; for (size_t j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = packages[i].description; for (size_t j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                if (a.find(ql) != string::npos || b.find(ql) != string::npos || c.find(ql) != string::npos) {
                    cout << "  [" << packages[i].packageID << "] "
                        << packages[i].packageName << "  RM " << fixed << setprecision(2) << packages[i].price
                        << "  - " << packages[i].description << "\n";
                    shown++;
                }
            }
            if (shown == 0) cout << "  (none)\n";

            // Venues
            cout << "\n Venues matched:\n";
            shown = 0;
            for (i = 0; i < venues.size(); ++i) {
                string a = venues[i].venueID;    for (size_t j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = venues[i].venueName;  for (size_t j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = venues[i].location;   for (size_t j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                if (a.find(ql) != string::npos || b.find(ql) != string::npos || c.find(ql) != string::npos) {
                    cout << "  [" << venues[i].venueID << "] "
                        << venues[i].venueName << "  (" << venues[i].location << ")  cap="
                        << venues[i].capacity << "  RM " << fixed << setprecision(2) << venues[i].rentalCost << "\n";
                    shown++;
                }
            }
            if (shown == 0) cout << "  (none)\n";

            // Caterings
            cout << "\n Caterings matched:\n";
            shown = 0;
            for (i = 0; i < caters.size(); ++i) {
                string a = caters[i].caterID;         for (size_t j = 0; j < a.size(); ++j) a[j] = char(tolower((unsigned char)a[j]));
                string b = caters[i].caterName;       for (size_t j = 0; j < b.size(); ++j) b[j] = char(tolower((unsigned char)b[j]));
                string c = caters[i].menuDescription; for (size_t j = 0; j < c.size(); ++j) c[j] = char(tolower((unsigned char)c[j]));
                if (a.find(ql) != string::npos || b.find(ql) != string::npos || c.find(ql) != string::npos) {
                    cout << "  [" << caters[i].caterID << "] "
                        << caters[i].caterName << "  RM " << fixed << setprecision(2) << caters[i].costPerPerson
                        << "  - " << caters[i].menuDescription << "\n";
                    shown++;
                }
            }
            if (shown == 0) cout << "  (none)\n";

            cout << "\n\n Press Enter..."; cin.get();
        }
        else
        {
            cout << "\n\n Invalid option.\n Press Enter..."; cin.get();
        }
    }
}

bool login() {
    StringConst strConst;
    cin.clear();
    ifstream ck("admins.csv");

    if (!ck.is_open()) 
    {
        ofstream init("admins.csv");
        init.close();
    }
    ck.close();


    int attempts = 0;
    while (attempts < 3) 
    {
        clearScreen();

        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl << endl;
        cout << " ==== Admin Login ====\n\n";

        cout << " Username: ";
        string uname; getline(cin, uname);
        string pwd = maskedInput(" Password: ");

        // read csv file
        ifstream fin("admins.csv");
        string line;
        bool ok = false;

        while (getline(fin, line)) 
        {
            if (line.empty()) continue;
            Admin a(line); 
            if (a.username == uname && a.password == pwd) 
            {
                ok = true; break;
            }
        }
        fin.close();

        if (ok) {
            cout << " Login successful! Welcome, " << uname << "\n";
            return true;
        }
        else {
            attempts++;
            cout << " Invalid credentials. Attempts left: " << (3 - attempts) << "\n";
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    cout << "\nToo many failed attempts. Exiting...\n";

    exit(0);
    return false;
}

void showLoginScreen() {
    while (true) {

        if (login()) {
            showMainScreen();          
            break;                     
        }
        else {
            exit(0);
        }
    }
}

void showMainScreen() {
    StringConst strConst;
    int x;

    clearScreen();
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl;
    cout << strConst.MainScMenu;
    x = getValidatedInput<int>("\n Choose an option: ", "", " Invalid option. Please enter a number.");

    switch (x) {
    case 0:
        clearScreen();
        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl << endl;
        cout << " Exiting the system. Goodbye!" << endl;
        exit(0);
        break;
    case 1:
        reservationCenter();
        break;
    case 2:
        catalog();
        break;
    case 3:
        operations();
        break;
    case 4:
        searchFun();
        break;
    default:
        cout << " Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showMainScreen();
        break;
    }
}

int main() {
    showLoginScreen();
    return 0;
}