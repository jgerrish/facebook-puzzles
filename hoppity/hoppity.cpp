#include <iostream>
#include <fstream>

using namespace std;

// Load a single integer from the file filename
int load_number(char *filename)
{
    int num;

    std::ifstream input_file(filename);
    input_file >> num;

    return num;
}

const string hoppity_code(const int &num)
{
    if ((num % 3 == 0) && (num % 5 == 0))
        return "Hop";
    if (num % 3 == 0)
        return "Hoppity";
    if (num % 5 == 0)
        return "Hophop";

    return "";
}

int main(int argc, char **argv)
{
    int num;
    string code;

    if (argc == 2) {
        num = load_number(argv[1]);
        for (int i = 1; i <= num; ++i) {
            code = hoppity_code(i);
            if (code != "")
                cout << hoppity_code(i) << endl;
        }
    } else {
        cout << "Error: Must specify a filename to load" << endl;
        return 1;
    }

}
