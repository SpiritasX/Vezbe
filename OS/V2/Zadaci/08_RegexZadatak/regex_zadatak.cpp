/*
    Uz zadatke ide fajl koji se zove ulaz.txt
    U njemu se nalaze bodovi studenata u formi:
    Ime,Prezime,V=70&P=30,Beleska
    Napraviti program koji na osnovu fajla sračuna prosek za V (vežbe) i prosek za 
    P(ispit). 
*/

#include <iostream>
#include <regex>
#include <string>
#include <fstream>

int main() {
    std::ifstream input("ulaz.txt");

    std::string str;

    auto const r1 = std::regex("\\S+,\\S+,V=(\\d\\d)&P=(\\d\\d),\\S+");

    int sum_v = 0;
    int sum_p = 0;
    int i = 0;

    while(!input.eof()) {
        getline(input, str, input.widen('\n'));
        std::smatch mr2;
        std::regex_search(str, mr2, r1);
        sum_v += std::stoi(mr2[1].str());
        sum_p += std::stoi(mr2[2].str());
        i++;
    }

    double avg_v = sum_v / i;
    double avg_p = sum_p / i;

    std::cout << "Average V: " << avg_v << "\nAverage P: " << avg_p << std::endl;

    input.close();

    return 0;
}