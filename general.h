
#include <string>
#include <iostream>
#include <regex>

class Date{
    public:
        Date(unsigned n_day = 1, unsigned n_month = 1, unsigned n_year = 1){
            day = n_day, month = n_month, year = n_year;
        }
        friend std::ostream& operator<<(std::ostream& os, const Date& dt){
            os << dt.day << "." << dt.month << "." << dt.year;
            return os;
        }
    private:
        unsigned day, month, year;
};

enum DocumentType {NationalID, Passport};

class GovernmentID{
    public:
        GovernmentID(DocumentType n_type = NationalID, std::string n_ssn = "", std::string n_series = "", std::string n_number = "", std::string n_issuing_place = "", Date n_expiration_date = Date()){
            try{
                if(!std::regex_match(n_ssn, std::regex("[0-9]+"))) throw 1;
            }
            catch(...){
                std::cout << "Invalid ssn format (Illegal caracter/s detected)\n";
                exit(-1);
            }
            type = n_type, ssn = n_ssn, series = n_series, number = n_number, issuing_place = n_issuing_place, expiration_date = n_expiration_date;
        }
        friend std::ostream& operator<<(std::ostream& os, const GovernmentID& ID){
            switch(ID.type){
                case Passport:
                    os << "Passport:\n";
                    break;
                case NationalID:
                    os << "NationalID:\n";
                    break;
            }
            os << '\t' << ID.ssn << "\n\t" << ID.series << "\n\t" << ID.number << "\n\t" << ID.issuing_place << "\n\t" << ID.expiration_date;
            return os;
        }
    private:
        DocumentType type;
        std::string ssn;
        std::string series;
        std::string number;
        std::string issuing_place;
        Date expiration_date;
};

class Address{
    public:
        Address(std::string n_street = "", std::string n_flat = "", std::string n_country = "", std::string n_town = "", std::string n_county = "", std::string n_postal_code = "", std::string n_number = ""){
            street = n_street, flat = n_flat, country = n_country, town = n_town, county = n_county, postal_code = n_postal_code, number = n_number;
        }
    private:
        std::string street;
        std::string flat;
        std::string country;
        std::string town;
        std::string county;
        std::string postal_code;
        std::string number; 
};

class Person{
    public:
        Person(std::string n_name = "", Date n_date_of_birth = Date(), std::string n_personal_email = "", Address n_home_address = Address(), GovernmentID n_personalID = GovernmentID()){
            name = n_name, date_of_birth = n_date_of_birth, personal_email = n_personal_email, home_address = n_home_address, personalID = n_personalID; 
        }
        void setName(std::string n_name){
            name = n_name;
        }
        void setDate_of_birth(Date n_date){
            date_of_birth = n_date;
        }
        void set_personal_email(std::string n_email){
            personal_email = n_email;
        }
        void set_home_adress(Address n_address){
            home_address = n_address;
        }
        void set_personalID(GovernmentID n_ID){
            personalID = n_ID;
        }
    protected:
        std::string name;
        Date date_of_birth;
        std::string personal_email;
        Address home_address;
        GovernmentID personalID;
};
