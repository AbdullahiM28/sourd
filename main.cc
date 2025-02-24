#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;


int main() {

    std::string text;
    int x;

    std::ifstream myFile("paex_saw.c");
    std::ofstream newFile("new.c");

    while (getline(myFile, text)) {

        std::stringstream ss(text);
        ss >> x;
        std::string remaining;
        getline(ss, remaining);
        newFile << remaining << std::endl;
    }

    return 0;
}