/*
Napraviti program koji prihvata proizvoljan broj linija sa standardnog ulaza i zatim ih ispisuje u redosledu kojim su uneti.
*/

#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> input;

    std::string str;

    while (getline(std::cin, str))
        input.push_back(str);
    
    for (std::string line : input)
        std::cout << line << std::endl;
    
    return 0;
}
