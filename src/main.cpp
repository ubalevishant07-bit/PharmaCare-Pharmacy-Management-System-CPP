#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>
#include <filesystem>

using namespace std;

struct Medicine {
    int id;
    string name;
    string category;
    double price;
    int stock;
    int reorderLevel;
    string expiry;
};

struct Doctor {
    int id;
    string name;
    string specialization;
    string phone;
    string password;
};

struct Patient {
    int id;
    string name;
    string phone;
    string email;
    string password;
};

struct Sale {
    int invoice;
    string customer;
    string medicine;
    int quantity;
    double total;
    string date;
};

vector<Medicine> medicines;
vector<Doctor> doctors;
vector<Patient> patients;
vector<Sale> sales;

const string MED_FILE = "data/medicines.txt";
const string DOC_FILE = "data/doctors.txt";
const string PAT_FILE = "data/patients.txt";
const string SALE_FILE = "data/sales.txt";

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string today() {
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    stringstream ss;
    ss << put_time(now, "%Y-%m-%d");

    return ss.str();
}

// ================= FILE HANDLING =================

void saveMedicines() {
    ofstream file(MED_FILE);

    for (const auto &m : medicines) {
        file << m.id << "|"
             << m.name << "|"
             << m.category << "|"
             << m.price << "|"
             << m.stock << "|"
             << m.reorderLevel << "|"
             << m.expiry << "\n";
    }
}

void loadMedicines() {
    medicines.clear();

    ifstream file(MED_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        Medicine m;
        string price, stock, reorder;

        getline(ss, line, '|');
        m.id = stoi(line);

        getline(ss, m.name, '|');
        getline(ss, m.category, '|');

        getline(ss, price, '|');
        m.price = stod(price);

        getline(ss, stock, '|');
        m.stock = stoi(stock);

        getline(ss, reorder, '|');
        m.reorderLevel = stoi(reorder);

        getline(ss, m.expiry);

        medicines.push_back(m);
    }
}

void saveDoctors() {
    ofstream file(DOC_FILE);

    for (const auto &d : doctors) {
        file << d.id << "|"
             << d.name << "|"
             << d.specialization << "|"
             << d.phone << "|"
             << d.password << "\n";
    }
}

void loadDoctors() {
    doctors.clear();

    ifstream file(DOC_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        Doctor d;

        string id;

        getline(ss, id, '|');
        d.id = stoi(id);

        getline(ss, d.name, '|');
        getline(ss, d.specialization, '|');
        getline(ss, d.phone, '|');
        getline(ss, d.password);

        doctors.push_back(d);
    }
}

void savePatients() {
    ofstream file(PAT_FILE);

    for (const auto &p : patients) {
        file << p.id << "|"
             << p.name << "|"
             << p.phone << "|"
             << p.email << "|"
             << p.password << "\n";
    }
}

void loadPatients() {
    patients.clear();

    ifstream file(PAT_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        Patient p;

        string id;

        getline(ss, id, '|');
        p.id = stoi(id);

        getline(ss, p.name, '|');
        getline(ss, p.phone, '|');
        getline(ss, p.email, '|');
        getline(ss, p.password);

        patients.push_back(p);
    }
}

void saveSales() {
    ofstream file(SALE_FILE);

    for (const auto &s : sales) {
        file << s.invoice << "|"
             << s.customer << "|"
             << s.medicine << "|"
             << s.quantity << "|"
             << s.total << "|"
             << s.date << "\n";
    }
}

void loadSales() {
    sales.clear();

    ifstream file(SALE_FILE);
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        Sale s;

        string value;

        getline(ss, value, '|');
        s.invoice = stoi(value);

        getline(ss, s.customer, '|');
        getline(ss, s.medicine, '|');

        getline(ss, value, '|');
        s.quantity = stoi(value);

        getline(ss, value, '|');
        s.total = stod(value);

        getline(ss, s.date);

        sales.push_back(s);
    }
}

// ================= ID GENERATORS =================

int nextMedicineId() {
    int id = 1001;

    for (const auto &m : medicines) {
        if (m.id >= id)
            id = m.id + 1;
    }

    return id;
}

int nextDoctorId() {
    int id = 1;

    for (const auto &d : doctors) {
        if (d.id >= id)
            id = d.id + 1;
    }

    return id;
}

int nextPatientId() {
    int id = 1;

    for (const auto &p : patients) {
        if (p.id >= id)
            id = p.id + 1;
    }

    return id;
}

int nextInvoice() {
    int id = 10001;

    for (const auto &s : sales) {
        if (s.invoice >= id)
            id = s.invoice + 1;
    }

    return id;
}

// ================= DEFAULT DATA =================

void createDefaultMedicines() {

    if (!medicines.empty())
        return;

    Medicine m1;
    m1.id = 1001;
    m1.name = "Paracetamol 500mg";
    m1.category = "Tablet";
    m1.price = 20;
    m1.stock = 100;
    m1.reorderLevel = 10;
    m1.expiry = "2027-12-31";

    Medicine m2;
    m2.id = 1002;
    m2.name = "Cetirizine 10mg";
    m2.category = "Tablet";
    m2.price = 30;
    m2.stock = 50;
    m2.reorderLevel = 10;
    m2.expiry = "2027-08-31";

    Medicine m3;
    m3.id = 1003;
    m3.name = "Amoxicillin 500mg";
    m3.category = "Capsule";
    m3.price = 50;
    m3.stock = 40;
    m3.reorderLevel = 5;
    m3.expiry = "2027-06-30";

    Medicine m4;
    m4.id = 1004;
    m4.name = "Vitamin C";
    m4.category = "Tablet";
    m4.price = 45;
    m4.stock = 45;
    m4.reorderLevel = 10;
    m4.expiry = "2028-01-31";

    Medicine m5;
    m5.id = 1005;
    m5.name = "Antiseptic Cream";
    m5.category = "Cream";
    m5.price = 60;
    m5.stock = 20;
    m5.reorderLevel = 5;
    m5.expiry = "2027-10-31";

    medicines.push_back(m1);
    medicines.push_back(m2);
    medicines.push_back(m3);
    medicines.push_back(m4);
    medicines.push_back(m5);

    saveMedicines();
}

void createDefaultDoctors() {

    if (!doctors.empty())
        return;

    Doctor d1;
    d1.id = 1;
    d1.name = "Dr. Rahul Sharma";
    d1.specialization = "General Physician";
    d1.phone = "0000000000";
    d1.password = "Dr. Rahul Sharma@123";

    Doctor d2;
    d2.id = 2;
    d2.name = "Dr. Priya Mehta";
    d2.specialization = "Dermatologist";
    d2.phone = "0000000000";
    d2.password = "Dr. Priya Mehta@123";

    Doctor d3;
    d3.id = 3;
    d3.name = "Dr. Amit Patil";
    d3.specialization = "Cardiologist";
    d3.phone = "0000000000";
    d3.password = "Dr. Amit Patil@123";

    doctors.push_back(d1);
    doctors.push_back(d2);
    doctors.push_back(d3);

    saveDoctors();
}

// ================= UI =================

void header(const string &title) {

    cout << "\n";
    cout << "==============================================\n";
    cout << "                 PHARMACARE\n";
    cout << "        PHARMACY MANAGEMENT SYSTEM\n";
    cout << "==============================================\n";
    cout << title << "\n";
    cout << "----------------------------------------------\n";
}

// ================= MEDICINES =================

void listMedicines() {

    header("MEDICINE LIST");

    if (medicines.empty()) {
        cout << "No medicines available.\n";
        return;
    }

    cout << left
         << setw(8) << "ID"
         << setw(25) << "Medicine"
         << setw(15) << "Category"
         << setw(10) << "Price"
         << setw(10) << "Stock"
         << setw(15) << "Expiry"
         << "\n";

    cout << "--------------------------------------------------------------------------\n";

    for (const auto &m : medicines) {

        cout << left
             << setw(8) << m.id
             << setw(25) << m.name
             << setw(15) << m.category
             << setw(10) << fixed << setprecision(2) << m.price
             << setw(10) << m.stock
             << setw(15) << m.expiry
             << "\n";
    }
}

void addMedicine() {

    header("ADD MEDICINE");

    Medicine m;

    m.id = nextMedicineId();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Medicine name: ";
    getline(cin, m.name);

    cout << "Category: ";
    getline(cin, m.category);

    cout << "Price: ";
    cin >> m.price;

    cout << "Stock quantity: ";
    cin >> m.stock;

    cout << "Reorder level: ";
    cin >> m.reorderLevel;

    cout << "Expiry (YYYY-MM-DD): ";
    cin >> m.expiry;

    medicines.push_back(m);

    saveMedicines();

    cout << "\nMedicine added successfully!\n";
    cout << "Medicine ID: " << m.id << "\n";
}

void updateStock() {

    listMedicines();

    int id;
    int quantity;

    cout << "\nEnter medicine ID: ";
    cin >> id;

    auto it = find_if(
        medicines.begin(),
        medicines.end(),
        [id](const Medicine &m) {
            return m.id == id;
        }
    );

    if (it == medicines.end()) {
        cout << "Medicine not found.\n";
        return;
    }

    cout << "Current stock: " << it->stock << "\n";

    cout << "Enter quantity to add: ";
    cin >> quantity;

    if (quantity < 0) {
        cout << "Invalid quantity.\n";
        return;
    }

    it->stock += quantity;

    saveMedicines();

    cout << "Stock updated successfully!\n";
    cout << "New stock: " << it->stock << "\n";
}

void lowStockReport() {

    header("LOW STOCK REPORT");

    bool found = false;

    for (const auto &m : medicines) {

        if (m.stock <= m.reorderLevel) {

            found = true;

            cout << "ID: " << m.id << "\n";
            cout << "Medicine: " << m.name << "\n";
            cout << "Current Stock: " << m.stock << "\n";
            cout << "Reorder Level: " << m.reorderLevel << "\n";
            cout << "----------------------------------\n";
        }
    }

    if (!found)
        cout << "No low-stock medicines.\n";
}

// ================= DOCTOR =================

void registerDoctor() {

    header("DOCTOR REGISTRATION");

    Doctor d;

    d.id = nextDoctorId();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Doctor full name: ";
    getline(cin, d.name);

    cout << "Specialization: ";
    getline(cin, d.specialization);

    cout << "Phone: ";
    getline(cin, d.phone);

    cout << "Password: ";
    getline(cin, d.password);

    doctors.push_back(d);

    saveDoctors();

    cout << "\nDoctor registered successfully!\n";
    cout << "Doctor ID: " << d.id << "\n";
}

bool doctorLogin(string &doctorName) {

    header("DOCTOR LOGIN");

    string name;
    string password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Doctor name: ";
    getline(cin, name);

    cout << "Password: ";
    getline(cin, password);

    for (const auto &d : doctors) {

        if (d.name == name && d.password == password) {

            doctorName = d.name;

            cout << "\nLogin successful!\n";

            return true;
        }
    }

    cout << "\nInvalid doctor name or password.\n";

    return false;
}

void viewDoctors() {

    header("REGISTERED DOCTORS");

    if (doctors.empty()) {
        cout << "No doctors registered.\n";
        return;
    }

    for (const auto &d : doctors) {

        cout << "ID: " << d.id << "\n";
        cout << "Name: " << d.name << "\n";
        cout << "Specialization: " << d.specialization << "\n";
        cout << "Phone: " << d.phone << "\n";

        cout << "----------------------------------\n";
    }
}

// ================= PATIENT =================

void registerPatient() {

    header("PATIENT REGISTRATION");

    Patient p;

    p.id = nextPatientId();

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Patient name: ";
    getline(cin, p.name);

    cout << "Phone: ";
    getline(cin, p.phone);

    cout << "Email: ";
    getline(cin, p.email);

    cout << "Password: ";
    getline(cin, p.password);

    patients.push_back(p);

    savePatients();

    cout << "\nPatient registered successfully!\n";
    cout << "Patient ID: " << p.id << "\n";
}

bool patientLogin(string &patientName) {

    header("PATIENT LOGIN");

    string name;
    string password;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Patient name: ";
    getline(cin, name);

    cout << "Password: ";
    getline(cin, password);

    for (const auto &p : patients) {

        if (p.name == name && p.password == password) {

            patientName = p.name;

            cout << "\nLogin successful!\n";

            return true;
        }
    }

    cout << "\nInvalid patient name or password.\n";

    return false;
}

// ================= PURCHASE =================

void purchaseMedicine(const string &customer) {

    header("PATIENT PURCHASE");

    listMedicines();

    int id;
    int quantity;

    cout << "\nEnter medicine ID: ";
    cin >> id;

    auto it = find_if(
        medicines.begin(),
        medicines.end(),
        [id](const Medicine &m) {
            return m.id == id;
        }
    );

    if (it == medicines.end()) {

        cout << "Medicine not found.\n";
        return;
    }

    cout << "Medicine: " << it->name << "\n";
    cout << "Price: Rs. " << it->price << "\n";
    cout << "Available stock: " << it->stock << "\n";

    cout << "Quantity: ";
    cin >> quantity;

    if (quantity <= 0) {

        cout << "Invalid quantity.\n";
        return;
    }

    if (quantity > it->stock) {

        cout << "Insufficient stock.\n";
        return;
    }

    double total = it->price * quantity;

    int invoice = nextInvoice();

    it->stock -= quantity;

    Sale sale;

    sale.invoice = invoice;
    sale.customer = customer;
    sale.medicine = it->name;
    sale.quantity = quantity;
    sale.total = total;
    sale.date = today();

    sales.push_back(sale);

    saveMedicines();
    saveSales();

    cout << "\n==================================\n";
    cout << "          PHARMACARE BILL\n";
    cout << "==================================\n";

    cout << "Invoice No : " << invoice << "\n";
    cout << "Customer   : " << customer << "\n";
    cout << "Medicine   : " << it->name << "\n";
    cout << "Quantity   : " << quantity << "\n";
    cout << "Price      : Rs. " << it->price << "\n";
    cout << "Total      : Rs. " << total << "\n";
    cout << "Date       : " << today() << "\n";
    cout << "Stock Left : " << it->stock << "\n";

    cout << "==================================\n";
    cout << "Purchase completed successfully!\n";
}

// ================= SALES =================

void salesReport() {

    header("SALES & PATIENT PURCHASES");

    if (sales.empty()) {

        cout << "No sales recorded.\n";
        return;
    }

    double grandTotal = 0;

    for (const auto &s : sales) {

        cout << "Invoice  : " << s.invoice << "\n";
        cout << "Customer : " << s.customer << "\n";
        cout << "Medicine : " << s.medicine << "\n";
        cout << "Quantity : " << s.quantity << "\n";
        cout << "Total    : Rs. "
             << fixed << setprecision(2)
             << s.total << "\n";
        cout << "Date     : " << s.date << "\n";

        cout << "----------------------------------\n";

        grandTotal += s.total;
    }

    cout << "\nGrand Total Sales: Rs. "
         << fixed << setprecision(2)
         << grandTotal << "\n";
}

void patientPurchaseHistory(const string &patient) {

    header("MY PURCHASES");

    bool found = false;

    for (const auto &s : sales) {

        if (s.customer == patient) {

            found = true;

            cout << "Invoice  : " << s.invoice << "\n";
            cout << "Medicine : " << s.medicine << "\n";
            cout << "Quantity : " << s.quantity << "\n";
            cout << "Total    : Rs. " << s.total << "\n";
            cout << "Date     : " << s.date << "\n";

            cout << "----------------------------------\n";
        }
    }

    if (!found)
        cout << "No purchases found.\n";
}

// ================= DASHBOARD =================

void dashboard() {

    header("SYSTEM DASHBOARD");

    int lowStock = 0;

    for (const auto &m : medicines) {

        if (m.stock <= m.reorderLevel)
            lowStock++;
    }

    double totalSales = 0;

    for (const auto &s : sales)
        totalSales += s.total;

    cout << "Total Medicines : " << medicines.size() << "\n";
    cout << "Total Doctors   : " << doctors.size() << "\n";
    cout << "Total Patients  : " << patients.size() << "\n";
    cout << "Total Sales     : Rs. "
         << fixed << setprecision(2)
         << totalSales << "\n";
    cout << "Low Stock Items : " << lowStock << "\n";
}

// ================= ADMIN =================

void adminMenu() {

    int choice;

    do {

        header("ADMIN / PHARMACIST PANEL");

        cout << "1. Dashboard\n";
        cout << "2. View Medicines\n";
        cout << "3. Add Medicine\n";
        cout << "4. Update Stock\n";
        cout << "5. Low Stock Report\n";
        cout << "6. Register Doctor\n";
        cout << "7. View Doctors\n";
        cout << "8. Register Patient\n";
        cout << "9. Sales & Billing Report\n";
        cout << "0. Logout\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                dashboard();
                break;

            case 2:
                listMedicines();
                break;

            case 3:
                addMedicine();
                break;

            case 4:
                updateStock();
                break;

            case 5:
                lowStockReport();
                break;

            case 6:
                registerDoctor();
                break;

            case 7:
                viewDoctors();
                break;

            case 8:
                registerPatient();
                break;

            case 9:
                salesReport();
                break;

            case 0:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

        if (choice != 0) {

            cout << "\nPress Enter to continue...";
            clearInput();
            cin.get();
        }

    } while (choice != 0);
}

// ================= DOCTOR MENU =================

void doctorMenu(const string &doctor) {

    int choice;

    do {

        header("DOCTOR PANEL");

        cout << "Logged in: " << doctor << "\n\n";

        cout << "1. View Medicines\n";
        cout << "2. View Patient Purchases\n";
        cout << "3. View Doctors\n";
        cout << "0. Logout\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                listMedicines();
                break;

            case 2:
                salesReport();
                break;

            case 3:
                viewDoctors();
                break;

            case 0:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

        if (choice != 0) {

            cout << "\nPress Enter to continue...";
            clearInput();
            cin.get();
        }

    } while (choice != 0);
}

// ================= PATIENT MENU =================

void patientMenu(const string &patient) {

    int choice;

    do {

        header("PATIENT PANEL");

        cout << "Logged in: " << patient << "\n\n";

        cout << "1. View Medicines\n";
        cout << "2. Purchase Medicine\n";
        cout << "3. My Purchase History\n";
        cout << "0. Logout\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                listMedicines();
                break;

            case 2:
                purchaseMedicine(patient);
                break;

            case 3:
                patientPurchaseHistory(patient);
                break;

            case 0:
                cout << "Logging out...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

        if (choice != 0) {

            cout << "\nPress Enter to continue...";
            clearInput();
            cin.get();
        }

    } while (choice != 0);
}

// ================= MAIN =================

int main() {

    filesystem::create_directories("data");

    loadMedicines();
    loadDoctors();
    loadPatients();
    loadSales();

    createDefaultMedicines();
    createDefaultDoctors();

    int choice;

    while (true) {

        header("MAIN MENU");

        cout << "1. Admin / Pharmacist Login\n";
        cout << "2. Doctor Login\n";
        cout << "3. Patient Registration\n";
        cout << "4. Patient Login\n";
        cout << "5. Doctor Registration\n";
        cout << "0. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 0) {

            cout << "\nThank you for using PharmaCare!\n";
            break;
        }

        switch (choice) {

            case 1: {

                string username;
                string password;

                cout << "\nAdmin username: ";
                cin >> username;

                cout << "Admin password: ";
                cin >> password;

                if (username == "admin" &&
                    password == "admin123") {

                    cout << "\nAdmin login successful!\n";

                    adminMenu();

                } else {

                    cout << "\nInvalid admin username or password.\n";
                }

                break;
            }

            case 2: {

                string doctor;

                if (doctorLogin(doctor))
                    doctorMenu(doctor);

                break;
            }

            case 3:

                registerPatient();
                break;

            case 4: {

                string patient;

                if (patientLogin(patient))
                    patientMenu(patient);

                break;
            }

            case 5:

                registerDoctor();
                break;

            default:

                cout << "\nInvalid choice.\n";
        }

        cout << "\nPress Enter to continue...";
        clearInput();
        cin.get();
    }

    return 0;
}