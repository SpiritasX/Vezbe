/**
 * Napisati C++ program koji iz ulazne datoteke cita podatke o temperaturi u toku vikenda sa ski
 * staza na Kopaoniku, Zlatiboru i Jahorini i odredjuje koji dani i na kojoj planini su idealni
 * za skijanje a koji nisu. Neki idealni opseg temperature za skijanje je od -5 do 3 stepena.
 *
 * Za svaku od planina postoji posebna datoteka cije ime se sastoji od imena planine i prosirenja
 * (ekstenzije) ".txt". U svakoj pojedinacnoj datoteci se u jednom redu nalaze podaci za jedan dan.
 * Jedan red sadrzi redom ime_dana, datum, i potom izmerene temperature. Temperatura se meri na
 * svakih sat vremena, pocevsi od 8 ujutru, do 8 uvece. Svi podaci su odvojeni razmakom.
 *
 * Izgled jednog reda iz ulaznih datoteka "Kopaonik.txt" "Zlatibor.txt" "Jahorina.txt"
 *
 *     subota 01.02.  -15 -13 -10 -8 -3 0 -2 -3 2 2 -5 -7 -3
 *
 * Treba za svaki dan pronaci najnizu i najvisu dnevnu temperaturu. Ukoliko minimalna i maksimalna
 * temperatura upadaju u navedeni opseg, treba informacije za taj dan ispisati u datoteku
 * "idealno.txt", u suprotnom u datoteku "lose.txt".
 *
 * Ispis u izlaznu datoteku treba da prati format:
 *     <ime_planine> [<ime_dana> <datum>] <min. temp.> >> <maks. temp.>
 *
 * Primer ispisa u bilo kojoj od izlaznih datoteka "idealno.txt", "lose.txt":
 *
 *     Kopaonik [subota 01.02.] -15 >> 2
 *
 * Treba napraviti jednu nit koja ce samo citati podatke iz ulaznih datoteka, jednu nit koja ce
 * samo pisati spremljene podatke u izlazne datoteke i 4 niti radnika koji ce na osnovu podataka iz
 * ulaznih datoteka generisati sve neophodno za ispis u izlazne datoteke.
 */

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <regex>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

class Data
{
private:
    string dan;
    string datum;
    vector<int> temperature;
    string planina;
public:
    string getDan() { return this->dan; }
    void setDan(string dan) { this->dan = dan; }
    string getDatum() { return this->datum; }
    void setDatum(string datum) { this->datum = datum; }

    vector<int> getTemperature() { return this->temperature; }
    void setTemperature(string temp)
    {
        stringstream input(temp);
        string token;
        for (int i = 0; i < 13; i++) {
            getline(input, token, ' ');
            temperature.push_back(stoi(token));
        }
    }

    string getPlanina() { return this->planina; }
    void setPlanina(string planina) { this->planina = planina; }
};

template <typename T>
class InputData
{
private:
    mutex data_mtx;
    condition_variable cv;
    vector<string> input;
    int workers_num;
    bool end;
public:
    InputData() : end(false), workers_num(0) {}

    void add_data(T data_element)
    {
        unique_lock<mutex> lock(data_mtx);
        input.push_back(data_element);
        cv.notify_one();
    }

    bool remove_data(T &data_element)
    {
        unique_lock<mutex> lock(data_mtx);

        while (input.empty() && !end)
        {
            cv.wait(lock);
        }

        if (input.empty())
            return false;

        data_element = *(input.end() - 1);
        input.pop_back();
        return true;
    }

    bool the_end()
    {
        return input.empty() && end;
    }

    void signIn()
    {
        unique_lock<mutex> lock(data_mtx);
        workers_num++;
    }

    void signOut()
    {
        unique_lock<mutex> lock(data_mtx);
        workers_num--;
        if (workers_num == 0)
        {
            end = true;
            cv.notify_all();
        }
    }
};

template <typename T>
class OutputData
{
private:
    mutex data_mtx;
    condition_variable cv;
    vector<Data> output;
    int workers_num;
    bool end;
public:
    OutputData() : end(false), workers_num(0) {}

    void add_data(T data_element)
    {
        unique_lock<mutex> lock(data_mtx);
        output.push_back(data_element);
        cv.notify_one();
    }

    bool remove_data(T &data_element)
    {
        unique_lock<mutex> lock(data_mtx);

        while (output.empty() && !end)
        {
            cv.wait(lock);
        }

        if (output.empty())
            return false;

        data_element = *(output.end() - 1);
        output.pop_back();
        return true;
    }

    bool the_end()
    {
        return output.empty() && end;
    }

    void signIn()
    {
        unique_lock<mutex> lock(data_mtx);
        workers_num++;
    }

    void signOut()
    {
        unique_lock<mutex> lock(data_mtx);
        workers_num--;
        if (workers_num == 0)
        {
            end = true;
            cv.notify_all();
        }
    }
};

void reader(vector<string> input_filenames, InputData<string> &raw_data)
{
    raw_data.signIn();

    ifstream kopaonik(input_filenames.at(0));
    ifstream zlatibor(input_filenames.at(1));
    ifstream jahorina(input_filenames.at(2));

    string str;

    getline(kopaonik, str);
    str.append(" Kopaonik");
    raw_data.add_data(str);
    getline(kopaonik, str);
    str.append(" Kopaonik");
    raw_data.add_data(str);
    getline(zlatibor, str);
    str.append(" Zlatibor");
    raw_data.add_data(str);
    getline(zlatibor, str);
    str.append(" Zlatibor");
    raw_data.add_data(str);
    getline(jahorina, str);
    str.append(" Jahorina");
    raw_data.add_data(str);
    getline(jahorina, str);
    str.append(" Jahorina");
    raw_data.add_data(str);

    kopaonik.close();
    zlatibor.close();
    jahorina.close();

    raw_data.signOut();
}

void proccessing_data(InputData<string> &raw_data, OutputData<Data> &proccessed_data)
{
    proccessed_data.signIn();

    const auto r1 = regex("(subota|nedelja) (\\d\\d.\\d\\d.) (.+) (Kopaonik|Zlatibor|Jahorina)");
    string str;
    smatch mr;

    while (raw_data.remove_data(str)) {
        regex_search(str, mr, r1);
        Data d;
        d.setDan(mr[1].str());
        d.setDatum(mr[2].str());
        d.setTemperature(mr[3].str());
        d.setPlanina(mr[4].str());
        proccessed_data.add_data(d);
    }

    proccessed_data.signOut();
}

//<ime_planine> [<ime_dana> <datum>] <min. temp.> >> <maks. temp.>
void writer(OutputData<Data> &proccessed_data)
{
    ofstream idealno("idealno.txt");
    ofstream lose("lose.txt");

    Data d;
    while (proccessed_data.remove_data(d))
    {
        vector<int> temp = d.getTemperature();
        int min = *min_element(temp.begin(), temp.end());
        int max = *max_element(temp.begin(), temp.end());

        if (min >= -5 && max <= 3)
            idealno << d.getPlanina() << " [" << d.getDan() << " " << d.getDatum() << "] " << min << " >> " << max << endl;
        else
            lose << d.getPlanina() << " [" << d.getDan() << " " << d.getDatum() << "] " << min << " >> " << max << endl;
    }

    idealno.close();
    lose.close();
}

int main()
{
    InputData<string> raw_data;
    OutputData<Data> proccessed_data;
    vector<string> input_filenames = {"Kopaonik.txt", "Zlatibor.txt", "Jahorina.txt"};

    thread th_reader(reader, input_filenames, ref(raw_data));
    thread th_writer(writer, ref(proccessed_data));
    thread th_workers[4];

    for (auto &th : th_workers)
    {
        th = thread(proccessing_data, ref(raw_data), ref(proccessed_data));
    }

    th_reader.join();
    for (auto &th : th_workers)
    {
        th.join();
    }
    th_writer.join();

    return 0;
}