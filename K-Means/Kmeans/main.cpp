#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>

using namespace std;





struct Point {
    double x, y;     // coordinates
    int cluster;     // no default cluster
    double minDist;  // default infinite dist to nearest cluster

    Point() :
        x(0.0),
        y(0.0),
        cluster(-1),
        minDist(__DBL_MAX__) {}

    Point(double x, double y) :
        x(x),
        y(y),
        cluster(-1),
        minDist(__DBL_MAX__) {}

    double distance(Point p) {
        return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
    }
};

void kMeansClustering(Point points[], int n, int number_of_iterations, int epochs, int k);






    Point p1 = Point(1.0, 1.0) ;
    Point p2 = Point(1.0, 2.0) ;
    Point p3 = Point(1.0, 3.0) ;
    Point p4 = Point(1.0, 4.0) ;
    Point p5 = Point(2.0, 1.0) ;
    Point p6 = Point(1.2, 1.2) ;
    Point p7 = Point(3.0, 1.0) ;
    Point p8 = Point(4.0, 1.0) ;
    Point p9 = Point(2.5, 3.5) ;
    Point p10 = Point(3.0, 3.0) ;
    Point p11 = Point(3.0, 3.5) ;
    Point p12 = Point(10.0, 2.0) ;
    Point p13 = Point(10.0, 3.0) ;
    Point p14 = Point(11.0, 2.0) ;


    Point my_pts[14] = {} ;







int main ()
{

    srand(time(0)) ;


    my_pts[0] = p1 ;
    my_pts[1] = p2 ;
    my_pts[2] = p3 ;
    my_pts[3] = p4 ;
    my_pts[4] = p5 ;
    my_pts[5] = p6 ;
    my_pts[6] = p7 ;
    my_pts[7] = p8 ;
    my_pts[8] = p9 ;
    my_pts[9] = p10 ;
    my_pts[10] = p11 ;
    my_pts[11] = p12 ;
    my_pts[12] = p13 ;
    my_pts[13] = p14 ;




    kMeansClustering(my_pts, 14, 10, 1000, 3) ;



    for (int i=0 ; i<14 ; i++)
    {
        cout << "(" << my_pts[i].x << ", " << my_pts[i].y << ")       "  << " CID: " << my_pts[i].cluster << endl ;
    }







}


void kMeansClustering(Point points[], int n, int number_of_iterations, int epochs, int k)
{
    double min_variation = __DBL_MAX__ ;
    int last_clusters[n] = {-1} ;


    for (int ee=0 ; ee<epochs ; ee++)
    {
        cout << "  epoch:  " << ee << endl ;
        // make random centroids
        Point centroids[k] = {} ;
        for (int i=0 ; i<k ; i++)
        {
            int r_temp = (rand()%n) ;
            points[r_temp].cluster = i ;
            centroids[i].x = points[r_temp].x ;
            centroids[i].y = points[r_temp].y ;
            centroids[i].cluster = points[r_temp].cluster ;
        }






        // starting iterations
        for (int nn=0 ; nn<number_of_iterations ; nn++)
        {

            // clustering all points
            for (int i=0 ; i<n ; i++)
            {
                points[i].minDist = __DBL_MAX__ ;
                for (int j=0 ; j<k ; j++)
                {
                    if ( points[i].distance(centroids[j]) < points[i].minDist )
                    {
                        points[i].minDist = points[i].distance(centroids[j]) ;
                        points[i].cluster = j ;
                    }
                }
            }





            // calculate new centroids
            double sum_x[k] = {0} ;
            double sum_y[k] = {0} ;
            int p_counter[k] = {0} ;

            for (int i=0 ; i<n ; i++)
            {
                sum_x[points[i].cluster] += points[i].x ;
                sum_y[points[i].cluster] += points[i].y ;
                p_counter[points[i].cluster]++ ;

            }

            for (int i=0 ; i<k ; i++)
            {
                centroids[i].x = sum_x[i] / p_counter[i] ;
                centroids[i].y = sum_y[i] / p_counter[i] ;
            }


        }




        // calculate variations
        double cluster_max_variation[k] = {0} ;
        for (int i=0 ; i<k ; i++)
        {
            for (int p=0 ; p<n ; p++)
            {
                for (int q=0 ; q<p ; q++)
                {
                    if (points[p].cluster == points[q].cluster && points[p].cluster == i)
                    {
                        if ( points[p].distance(points[q]) > cluster_max_variation[i] )
                        {
                            cluster_max_variation[i] = points[p].distance(points[q]) ;
                        }
                    }
                }
            }
        }

        //cout << "hhhhhhhhh:    " << cluster_max_variation[0] << "   " << cluster_max_variation[1] << "   " << cluster_max_variation[2] << endl ;

        // calculate sum of variations of clusters
        double sum_of_variation = 0 ;
        for (int i=0 ; i<k ; i++)
        {
            sum_of_variation += cluster_max_variation[i] ;
        }
        cout << "  sum of variations:  " <<sum_of_variation << endl ;



        // check if the result of this epoch is better
        if (sum_of_variation > min_variation)
        {
            cout << "  get back  " << endl ;
            for (int i=0 ; i<n ; i++)
            {
                points[i].cluster = last_clusters[i] ;
            }
        }
        else
        {
            min_variation = sum_of_variation ;
        }

        cout << "--------------------------------after checking--------------------------" << endl ;
        for (int i=0 ; i<n ; i++)
        {
            cout << points[i].cluster << endl ;
        }


        // save last clustering
        for (int i=0 ; i<n ; i++)
        {
            last_clusters[i] = points[i].cluster ;
        }

        cout << "------------------clusters---------------------" << endl ;
        for (int i=0 ; i<n ; i++)
        {
            cout << points[i].cluster << endl ;
        }

    }
}
