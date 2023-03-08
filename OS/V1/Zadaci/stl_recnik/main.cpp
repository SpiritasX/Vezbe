/*
Napraviti jednostavan program za prevođenje reči sa engleskog na srpski jezik.
Nakon unosa reči sa standardnog ulaza, ispisuje se prevod (ukoliko unesena reč postoji u rečniku). 

Uneti 3 engleske reči i njihove prevode na srpski.
*/

#include <iostream>
#include <map>

int main()
{
    std::map<std::string, std::string> recnik = {{"Hello", "Zdravo"}, {"Goodbye", "Dovidjenja"}, {"House", "Kuca"}};

    std::string input;
    std::cin >> input;

    if (recnik[input] != "")
        std::cout << recnik[input] << std::endl;
    else
        std::cout << "Ta rec ne postoji u recniku.\n";
    
    return 0;
}
