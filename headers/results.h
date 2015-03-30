#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
using namespace std;
class Results
{
    fstream results;
    string line;
    bool cheating = false;
public:
    int best_length;
    int best_score;

    bool import_file();

    bool check(int actuall_result, int type); // 1 for length, 2 for score

    void save();

    string return_points(int type);// 1 for length, 2 for score
};
