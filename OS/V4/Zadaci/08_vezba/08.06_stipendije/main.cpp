/**
 * Napisati C++ program koji cita podatke o studentima iz ulazne datoteke i potom 
 * za svakog studenta racuna prosek
 * 
 * U ulaznoj datoteci "studenti.csv" se u svakom redu nalaze informacije o studentu: 
 *     Ime,Prezime,Broj indeksa,Ocene 
 * Pritom su ocene odvojene medjusobno zarezima.
 * 
 * Prilikom obrade podataka o studentima, mora se proveriti format indeksa da li je validan. Ako nije, zanemariti taj unos.
 * Format indeksa je:
 *     [[:alpha:]][[:alnum:]]{1,2}\s[[:digit:]]{1,3}\/[[:digit:]]{4}
 * 
 * U tri izlazne datoteke rasporediti studente u zavisnosti od proseka.
 * Ukoliko je prosek > 9.00 potrebno je upisati studenta u datoteku "kandidati_stipendija.csv".
 * Ukoliko je prosek > 8.00 i prosek <= 9.00 potrebno je upisati studenta u datoteku "kandidati_kredit.csv".
 * U ostalim slucajevima upisati studenta u datoteku "ostali.csv".
 * Format u izlaznoj datoteci treba da odgovara sledecem: Ime,Prezime,Broj_indeksa,prosek
 * 
 * Treba napraviti jednu nit koja ce samo citati redove ulazne podatke, jednu nit 
 * koja ce samo pisati gotove podatke u izlazne datoteke i 10 niti radnika koji ce na osnovu redova
 * iz ulazne datoteke generisati sve neophodno za ispis u izlaznu datoteku.
*/

#include <algorithm>
#include <mutex>
#include <vector>
#include <fstream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <regex>
#include <iostream>
#include <cstring>

using namespace std;

class Student {
private:
    string first_name;
    string last_name;
    string index;
    vector<int> grades;
public:
    Student(string first_name, string last_name, string index) {
        this->first_name = first_name;
        this->last_name = last_name;
        this->index = index;
    }
    
    // Student(const Student& s) {

    // }

    string getFirstName() { return this->first_name; }
    string getLastName() { return this->last_name; }
    vector<int> getGrades() { return this->grades; }
    string getIndex() { return this->index; }

    void addGrades(string s) {
        int grade;
        char *array = new char[s.length()];
        strcpy(array, s.c_str());
        char *output;
        output = strtok(array, ",");
        grade = stoi(output);
        while (output != NULL) {
            grades.push_back(grade);
            output = strtok(NULL, ",");
            if (output != NULL)
                grade = stoi(output);
        }
    }
};

template<typename T>
class InputData {
private:
    mutex data_mtx;
    bool end;
    int workers_num;
    queue<T> data;
    condition_variable cv;
public:
    InputData(): end(false), workers_num(0) {}

    void add_data(T data_element) {
        unique_lock<mutex> lock(data_mtx);
        data.push(data_element);
        cv.notify_one();
    }

    bool remove_data(T &data_element) {
        unique_lock<mutex> lock(data_mtx);

        while (data.empty() && !end)
            cv.wait(lock);
        
        if (data.empty())
            return false;
        
        data_element = data.front();
        data.pop();
        return true;
    }

    bool the_end() {
        return data.empty() && end;
    }

    void signIn() {
        unique_lock<mutex> lock(data_mtx);
        workers_num++;
    }

    void signOut() {
        unique_lock<mutex> lock(data_mtx);
        workers_num--;
        if (workers_num == 0) {
            end = true;
            cv.notify_all();
        }
    }

};

template<typename T>
class OutputData {
private:
    mutex data_mtx;
    bool end;
    int workers_num;
    queue<T> data;
    condition_variable cv;
public:
    OutputData(): end(false), workers_num(0) {}

    void add_data(T data_element) {
        unique_lock<mutex> lock(data_mtx);
        data.push(data_element);
        cv.notify_one();
    }

    bool remove_data(T &data_element) {
        unique_lock<mutex> lock(data_mtx);

        while (data.empty() && !end)
            cv.wait(lock);
        
        if (data.empty())
            return false;
        
        data_element = data.front();
        data.pop();
        return true;
    }

    bool the_end() {
        return data.empty() && end;
    }

    void signIn() {
        unique_lock<mutex> lock(data_mtx);
        workers_num++;
    }

    void signOut() {
        unique_lock<mutex> lock(data_mtx);
        workers_num--;
        if (workers_num == 0) {
            end = true;
            cv.notify_all();
        }
    }

};

void reader(string input_file_name, InputData<string>& raw_data) {
    raw_data.signIn();
    ifstream input(input_file_name);
    string str;
    while (!input.eof()) {
        getline(input, str, input.widen('\n'));
        raw_data.add_data(str);
    }
    input.close();
    raw_data.signOut();
}

void proccessing_data(InputData<string>& raw_data, OutputData<Student>& proccessed_data){
    //auto const index = regex("[[:alpha:]][[:alnum:]]{1,2}\\s[[:digit:]]{1,3}\\/[[:digit:]]{4}");
    auto const r1 = regex("(\\S+),(\\S+),([[:alpha:]][[:alnum:]]{1,2}\\s[[:digit:]]{1,3}\\/[[:digit:]]{4}),(\\S+)");
    
    proccessed_data.signIn();
    string str;
    while (raw_data.remove_data(str)) {
        smatch mr2;
        regex_search(str, mr2, r1);
        Student s(mr2[1].str(), mr2[2].str(), mr2[3].str());
        s.addGrades(mr2[4].str());
        // for (int grade : s.getGrades())
        //     cout << grade << " ";
        // cout << endl;
        proccessed_data.add_data(s);
    }
    proccessed_data.signOut();
}

void writer(OutputData<Student>& proccessed_data) {
    ofstream output1("kandidati_stipendija.csv");
    ofstream output2("kandidati_kredit.csv");
    ofstream output3("ostali.csv");

    Student s("a", "a", "a");

    while (proccessed_data.remove_data(s)) {
        double sum = 0;
        for (int grade : s.getGrades())
            sum += grade;
        sum /= s.getGrades().size();
        if (sum > 9)
            output1 << s.getFirstName() << "," << s.getLastName() << "," << s.getIndex() << " " << sum << endl;
        else if (sum > 8)
            output2 << s.getFirstName() << "," << s.getLastName() << "," << s.getIndex() << " " << sum << endl;
        else
            output3 << s.getFirstName() << "," << s.getLastName() << "," << s.getIndex() << " " << sum << endl;
    }

    output1.close();
    output2.close();
    output3.close();
}


int main() {
    InputData<string> raw_data;
    OutputData<Student> proccessed_data;

    thread th_reader(reader, "studenti.csv", ref(raw_data));
    thread th_writer(writer, ref(proccessed_data));
    thread th_workers[10];

    for(auto &th: th_workers){
        th = thread(proccessing_data, ref(raw_data), ref(proccessed_data));
    }

    th_reader.join();
    for(auto &th: th_workers) {
        th.join();
    }
    th_writer.join();
    
    return 0;
}
