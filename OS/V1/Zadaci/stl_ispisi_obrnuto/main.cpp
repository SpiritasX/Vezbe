/*
Napraviti program koji prihvata proizvoljan broj
linija sa standardnog ulaza i zatim ih ispisuje u
obrnutom redosledu (poslednja prihvaćena linija se
ispisuje prva).
*/

#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> lines;

    std::string s;

    while (std::getline(std::cin, s))
        lines.push_back(s);
    
    // da bi izbegli auto
    // lines.rbegin()
    // lines.rend()
    for (auto it = lines.end(); it != lines.begin() - 1; it--)
        std::cout << *it << std::endl;
    
    return 0;
}
