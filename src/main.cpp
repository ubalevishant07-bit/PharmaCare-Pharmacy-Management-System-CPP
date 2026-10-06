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

struct Medicine{int id;string name,category,expiry;double price;int stock,reorder;};
struct Doctor{int id;string name,specialization,phone,password;};
struct Patient{int id;string name,phone,email,password;};
struct Sale{int invoice;string customer,medicine,date;int qty;double total;};
vector<Medicine> meds; vector<Doctor> docs; vector<Patient> pats; vector<Sale> sales;

const string MD="data/medicines.txt",DD="data/doctors.txt",PD="data/patients.txt",SD="data/sales.txt";
void pause(){cout<<"\nPress Enter...";cin.ignore(numeric_limits<streamsize>::max(),'\n');cin.get();}
string q(const string&s){return "\""+s+"\"";}
string today(){time_t t=time(nullptr);tm*n=localtime(&t);char b[11];strftime(b,11,"%Y-%m-%d",n);return b;}
void load(){
 meds.clear();docs.clear();pats.clear();sales.clear();
 ifstream a(MD);Medicine m;while(a>>m.id>>quoted(m.name)>>quoted(m.category)>>m.price>>m.stock>>m.reorder>>m.expiry)meds.push_back(m);
 ifstream b(DD);Doctor d;while(b>>d.id>>quoted(d.name)>>quoted(d.specialization)>>quoted(d.phone)>>quoted(d.password))docs.push_back(d);
 ifstream c(PD);Patient p;while(c>>p.id>>quoted(p.name)>>quoted(p.phone)>>quoted(p.email)>>quoted(p.password))pats.push_back(p);
 ifstream e(SD);Sale s;while(e>>s.invoice>>quoted(s.customer)>>quoted(s.medicine)>>s.qty>>s.total>>quoted(s.date))sales.push_back(s);
}
void save(){
 ofstream a(MD);for(auto&m:meds)a<<m.id<<" "<<q(m.name)<<" "<<q(m.category)<<" "<<m.price<<" "<<m.stock<<" "<<m.reorder<<" "<<m.expiry<<"\n";
 ofstream b(DD);for(auto&d:docs)b<<d.id<<" "<<q(d.name)<<" "<<q(d.specialization)<<" "<<q(d.phone)<<" "<<q(d.password)<<"\n";
 ofstream c(PD);for(auto&p:pats)c<<p.id<<" "<<q(p.name)<<" "<<q(p.phone)<<" "<<q(p.email)<<" "<<q(p.password)<<"\n";
 ofstream e(SD);for(auto&s:sales)e<<s.invoice<<" "<<q(s.customer)<<" "<<q(s.medicine)<<" "<<s.qty<<" "<<s.total<<" "<<q(s.date)<<"\n";
}
int nextM(){int x=1000;for(auto&m:meds)x=max(x,m.id);return x+1;}
int nextD(){int x=0;for(auto&d:docs)x=max(x,d.id);return x+1;}
int nextP(){int x=0;for(auto&p:pats)x=max(x,p.id);return x+1;}
int nextI(){int x=10000;for(auto&s:sales)x=max(x,s.invoice);return x+1;}
void header(string t){cout<<"\n============================================\n PHARMACARE - PHARMACY MANAGEMENT SYSTEM\n============================================\n"<<t<<"\n--------------------------------------------\n";}
void listM(){header("MEDICINES");cout<<left<<setw(7)<<"ID"<<setw(25)<<"Name"<<setw(15)<<"Category"<<setw(10)<<"Price"<<setw(8)<<"Stock"<<setw(12)<<"Expiry"<<"\n";for(auto&m:meds)cout<<setw(7)<<m.id<<setw(25)<<m.name<<setw(15)<<m.category<<setw(10)<<fixed<<setprecision(2)<<m.price<<setw(8)<<m.stock<<setw(12)<<m.expiry<<"\n";}
void addM(){header("ADD MEDICINE");Medicine m{};m.id=nextM();cin.ignore();cout<<"Name: ";getline(cin,m.name);cout<<"Category: ";getline(cin,m.category);cout<<"Price: ";cin>>m.price;cout<<"Stock: ";cin>>m.stock;cout<<"Reorder level: ";cin>>m.reorder;cout<<"Expiry YYYY-MM-DD: ";cin>>m.expiry;meds.push_back(m);save();cout<<"Added. ID="<<m.id<<"\n";}
void stock(){listM();int id,n;cout<<"\nMedicine ID: ";cin>>id;for(auto&m:meds)if(m.id==id){cout<<"Add stock: ";cin>>n;if(n>=0){m.stock+=n;save();cout<<"Stock="<<m.stock<<"\n";}return;}cout<<"Not found.\n";}
void low(){header("LOW STOCK");bool f=false;for(auto&m:meds)if(m.stock<=m.reorder){f=true;cout<<m.id<<" | "<<m.name<<" | "<<m.stock<<" (reorder "<<m.reorder<<")\n";}if(!f)cout<<"No low-stock medicines.\n";}
void regD(){header("DOCTOR REGISTRATION");Doctor d{};d.id=nextD();cin.ignore();cout<<"Name: ";getline(cin,d.name);cout<<"Specialization: ";getline(cin,d.specialization);cout<<"Phone: ";getline(cin,d.phone);cout<<"Password: ";getline(cin,d.password);docs.push_back(d);save();cout<<"Doctor registered. ID="<<d.id<<"\n";}
void regP(){header("PATIENT REGISTRATION");Patient p{};p.id=nextP();cin.ignore();cout<<"Name: ";getline(cin,p.name);cout<<"Phone: ";getline(cin,p.phone);cout<<"Email: ";getline(cin,p.email);cout<<"Password: ";getline(cin,p.password);pats.push_back(p);save();cout<<"Patient registered. ID="<<p.id<<"\n";}
bool loginD(string&who){header("DOCTOR LOGIN");string n,p;cin.ignore();cout<<"Name: ";getline(cin,n);cout<<"Password: ";getline(cin,p);for(auto&d:docs)if(d.name==n&&d.password==p){who=n;return true;}cout<<"Invalid login.\n";return false;}
bool loginP(string&who){header("PATIENT LOGIN");string n,p;cin.ignore();cout<<"Name: ";getline(cin,n);cout<<"Password: ";getline(cin,p);for(auto&x:pats)if(x.name==n&&x.password==p){who=n;return true;}cout<<"Invalid login.\n";return false;}
void buy(string customer){header("PATIENT PURCHASE");listM();int id,n;cout<<"\nMedicine ID: ";cin>>id;auto it=find_if(meds.begin(),meds.end(),[&](auto&m){return m.id==id;});if(it==meds.end()){cout<<"Not found.\n";return;}cout<<"Quantity: ";cin>>n;if(n<=0||n>it->stock){cout<<"Insufficient stock.\n";return;}double total=it->price*n;it->stock-=n;int inv=nextI();sales.push_back({inv,customer,it->name,today(),n,total});save();cout<<"\nINVOICE #"<<inv<<"\n"<<it->name<<" x "<<n<<"\nTotal: Rs. "<<fixed<<setprecision(2)<<total<<"\nStock left: "<<it->stock<<"\n";}
void report(){header("SALES REPORT");double total=0;for(auto&s:sales){cout<<"#"<<s.invoice<<" | "<<s.customer<<" | "<<s.medicine<<" x"<<s.qty<<" | Rs."<<fixed<<setprecision(2)<<s.total<<" | "<<s.date<<"\n";total+=s.total;}cout<<"Total Sales: Rs."<<fixed<<setprecision(2)<<total<<"\n";}
void admin(){int c;do{header("ADMIN / PHARMACIST");cout<<"1 View Medicines\n2 Add Medicine\n3 Update Stock\n4 Low Stock\n5 Register Doctor\n6 Register Patient\n7 Sales Report\n0 Logout\nChoice: ";cin>>c;switch(c){case 1:listM();break;case 2:addM();break;case 3:stock();break;case 4:low();break;case 5:regD();break;case 6:regP();break;case 7:report();break;}if(c)pause();}while(c);}
void doctor(string who){int c;do{header("DOCTOR PANEL");cout<<"Logged in: "<<who<<"\n1 View Medicines\n2 View Sales\n0 Logout\nChoice: ";cin>>c;if(c==1)listM();else if(c==2)report();if(c)pause();}while(c);}
void patient(string who){int c;do{header("PATIENT PANEL");cout<<"Logged in: "<<who<<"\n1 View Medicines\n2 Purchase Medicine\n3 My Purchases\n0 Logout\nChoice: ";cin>>c;if(c==1)listM();else if(c==2)buy(who);else if(c==3){for(auto&s:sales)if(s.customer==who)cout<<s.invoice<<" | "<<s.medicine<<" x"<<s.qty<<" | Rs."<<s.total<<" | "<<s.date<<"\n";}if(c)pause();}while(c);}
int main(){filesystem::create_directories("data");load();if(meds.empty()){meds={{1001,"Paracetamol 500mg","Tablet",20,100,10,"2027-12-31"},{1002,"Cetirizine 10mg","Tablet",30,50,10,"2027-08-31"},{1003,"Vitamin C","Tablet",45,45,10,"2028-01-31"}};save();}if(docs.empty()){docs={{1,"Dr. Rahul Sharma","General Physician","0000000000","Dr. Rahul Sharma@123"},{2,"Dr. Priya Mehta","Dermatologist","0000000000","Dr. Priya Mehta@123"},{3,"Dr. Amit Patil","Cardiologist","0000000000","Dr. Amit Patil@123"}};save();}
int c;while(true){header("MAIN MENU");cout<<"1 Admin / Pharmacist Login\n2 Doctor Login\n3 Patient Registration\n4 Patient Login\n5 Doctor Registration\n0 Exit\nChoice: ";cin>>c;if(c==0)break;if(c==1){string u,p;cout<<"Username: ";cin>>u;cout<<"Password: ";cin>>p;if(u=="admin"&&p=="admin123")admin();else cout<<"Invalid login.\n";}else if(c==2){string x;if(loginD(x))doctor(x);}else if(c==3)regP();else if(c==4){string x;if(loginP(x))patient(x);}else if(c==5)regD();else cout<<"Invalid choice.\n";if(c)pause();}cout<<"Thank you for using PharmaCare!\n";}
