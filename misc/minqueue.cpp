#include <sstream>
#include <fstream> 
#include <iostream> 
#include <algorithm>

struct CPUjob {
    private:
    int ID; 
    int length; 
    int prior; 
    public: 
    CPUjob(int a =0; int b=0; int c=0) : ID(a), length(b), prior(c) {}; 
    int getID() const {return ID;}
    int getLength() const {return length;}
    int getPrior() const {return prior;}
    bool operator< (const CPUjob& job); 
}
void operator>>(ifstream &fin, vector<Record> &rc){
    if (!fin.is_open()) {
        throw runtime_error("could not open file");
    }
    string ttl, author, isbn_, pubyear, edtnum;
    string space;
    while(!fin.eof()) {
        getline(fin,ttl);
        getline(fin,author);
        getline(fin,isbn_);
        getline(fin,pubyear);
        getline(fin, edtnum);
        getline(fin,space);
        if (!fin.fail()) {
            Record temp_rc(ttl, author, isbn_, pubyear, edtnum);
            rc.push_back(temp_rc); 
        }
    }
} //run time 
void operator<< (ostream &os, Record &rc) {
    os << rc.getTitle() <<endl; 
    os << rc.getAuthor() <<endl;
    os << rc.getIsbn() <<endl;
    os << rc.getPublYear() <<endl;
    os << rc.getEdtNum() <<endl;
    os << endl;

} //rt 
bool operator<(Record& r1, Record& r2) { 
    if(r1.getTitle() == r2.getTitle()) {
        if ((r1.getAuthor() == r2.getAuthor()) && (r1.getIsbn() == r2.getIsbn())) {
            return true;
        }
    }
        else {
          return false;
        }
}