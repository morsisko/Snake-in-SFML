#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <fstream>
#include "../headers/results.h"
using namespace std;


bool Results::import_file()
{
    int i = 1;
    results.open("score.txt", ios::in);
    if (results.good() == false)
    {
        cout << "Error! score.txt";
        return false;
    }

    while(getline(results, line))
    {
        switch(i)
        {
        case 1:
            if (atoi(line.c_str()) % 128 == 0)
                best_length = atoi(line.c_str()) / 128;
            else
            {
            MessageBox(NULL,"Cheating! Go to score.txt and set length to 0!","ERROR",NULL);
            return false;
            }
        break;
        case 2:
            if (atoi(line.c_str()) % 2 == 0)
                best_score = atoi(line.c_str()) / 2;
            else
            {
            MessageBox(NULL,"Cheating! Go to score.txt and set score to 0!","ERROR",NULL);
            return false;
            }
        break;
        }
    i++;
    }
    results.close();
    return true;
}

bool Results::check(int actuall_result, int type)
{
    if (type == 1 && best_length < actuall_result)
    {
        best_length = actuall_result;
        return true;
    }

    else if (type == 2 && best_score < actuall_result)
    {
        best_score = actuall_result;
        return true;
    }
    return false;
}

void Results::save()
{
    results.open("score.txt", ios::out);
    results<<(best_length * 128)<<endl;
    results<<(best_score * 2);
    results.close();

}

string Results::return_points(int type)
{
    stringstream points_ss;
    if (type == 1) points_ss << best_length;
    else if (type == 2) points_ss << best_score;
    else return "Error";
    string points_to_view = points_ss.str();
    return points_to_view;
}
