#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "No arguments passed.\n";
        return 0;
    }
    
    std::string input_file_name = argv[1];

    std::ifstream InputFile(input_file_name, std::ios::in | std::ios::binary);
    std::ofstream OutputFile(input_file_name + ".enc", std::ios::out | std::ios::binary);

    char PIN;

    std::cout << "Input pin (1 character)\n> ";
    std::cin >> PIN;

    char ch;

    while(!InputFile.eof())
    {
        InputFile.get(ch);

        ch = ch ^ PIN;

        OutputFile.put(ch);
    }

    InputFile.close();
    OutputFile.close();
    
    return 0;
}