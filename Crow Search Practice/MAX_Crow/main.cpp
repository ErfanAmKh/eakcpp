#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <cmath>

using namespace std;

const int number_of_crows = 40 ;
const int number_of_outputs = 500 ;
const double dt = 100 ;
double crow_outputs_steer [number_of_crows][number_of_outputs] = {0.0} ;
double crow_outputs_speed [number_of_crows][number_of_outputs] = {0.0} ;
double memory_steer[number_of_crows][number_of_outputs] = {1000000.0} ;
double memory_speed[number_of_crows][number_of_outputs] = {1000000.0} ;
int max_iteration = 200 ;
double AP = 0.6 ;
double fl = 1.0 ;
double x = 0.0, y = 0.0, theta = 0.0 ;
double L = 40.0 ;



double g (double) ;
double generate_random_probability () ;
void print_positions() ;

int main()
{
    srand(time(0)) ;

    for (int i=0 ; i<number_of_crows ; i++)
    {
        for (int j=0 ; j<number_of_outputs ; j++)
        {
            crow_outputs_steer[i][j] = (double(rand() % 20000)-1000.0) / 1000.0 ;
        }
    }
    for (int i=0 ; i<number_of_crows ; i++)
    {
        for (int j=0 ; j<number_of_outputs ; j++)
        {
            crow_outputs_speed[i][j] = 20.0 * ((rand() % 3)-1) ;
        }
    }
    for (int i=0 ; i<number_of_crows ; i++)
    {
        for (int j=0 ; j<number_of_outputs ; j++)
        {
            memory_steer[i][j] = crow_outputs_steer[i][j] ;
        }
    }
    for (int i=0 ; i<number_of_crows ; i++)
    {
        for (int j=0 ; j<number_of_outputs ; j++)
        {
            memory_speed[i][j] = crow_outputs_speed[i][j] ;
        }
    }
    int iter = 0 ;
    while (iter < max_iteration)
    {
        for (int i=0 ; i<number_of_crows ; i++)
        {
            int j = rand() % number_of_crows ;
            if (generate_random_probability() >= AP)
            {
                for (int k=0 ; k<number_of_outputs ; k++)
                {
                    double temp_steer = crow_outputs_steer[i][k] + generate_random_probability() * fl * (memory_steer[j][k] - crow_outputs_steer[i][k]) ;
                    double temp_speed = crow_outputs_speed[i][k] + generate_random_probability() * fl * (memory_speed[j][k] - crow_outputs_speed[i][k]) ;
                    if ( temp_steer >= -20.0 && temp_steer <= 20.0)
                    {
                        crow_outputs_steer[i][k] = temp_steer ;
                    }
                    if (temp_speed > 0.0 && temp_speed <=20.0)
                    {
                        crow_outputs_speed[i][k] = 20.0 ;
                    }
                    if (temp_speed <0.0 && temp_speed >= -20.0)
                    {
                        crow_outputs_speed[i][k] = -20.0 ;
                    }
                }
            }
            else
            {
                for (int k=0 ; k<number_of_outputs ; k++)
                {
                    crow_outputs_steer[i][k] = (double(rand() % 20000)-1000.0) / 1000.0 ;
                }
                for (int k=0 ; k<number_of_outputs ; k++)
                {
                    crow_outputs_speed[i][k] = 20.0 * ((rand() % 3)-1) ;
                }
            }
        }
        for (int i=0 ; i<number_of_crows ; i++)
        {
            if (f(crow_position[i]) < f(memory[i]))
            {
                memory[i] = crow_position[i] ;
            }
        }
        print_positions() ;
        iter++ ;
    }
    double final_res = 100.0 ;
    for (int i=0 ; i<number_of_crows ;i++)
    {
        if (f(memory[i]) < final_res)
        {
            final_res = memory[i] ;
        }
    }
    cout << "estimation:     " << final_res << endl ;

    return 0;
}



double g (double x)
{
    //return (x*x*x*x*x - 6*x*x*x*x + 10*x*x*x - x*x - 4*x - 4) ;
    return x*x*x*x*x*x + 6*x*x*x*x - 4*x - 7*x*x ;
}

double generate_random_probability ()
{
    return (double(rand() % 20000)-10000.0)/10000.0 ;
}

void print_positions()
{
    for (int i=0 ; i<number_of_crows ; i++)
    {
        cout << crow_position[i] << '\t' ;
    }
    cout << '\n' ;
}

void calculate_MM( int steer, int speed )
{
    theta = theta + (speed * tan(steer * (3.14/180.0))) / (L) ;
}

double peymane (double adad, int be_peymane)
{
    double ashar = 0.0 ;
    ashar = adad - (int)adad ;
    return ((int)adad % be_peymane) + ashar ;
}
