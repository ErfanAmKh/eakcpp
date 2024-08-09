#include <chrono>
#include <iostream>
#include <math.h>
#include <cmath>
#include <ctime>

using namespace std;
using namespace chrono;

int starting_x = 10 ;
int starting_y = 42 ;

int end_point_x = 39 ;
int end_point_y = 15 ;

bool no_path_exists = false ;

typedef struct Node
{
    int x ;
    int y ;
    bool walkable ;
    double g_cost ;
    double h_cost ;
    double f_cost ;
    int parent_x ;
    int parent_y ;
    bool is_closed ;
    bool is_open ;
    char shape ;
} Node ;

Node find_open_node_with_lowest_f() ;
Node grid[64][64] ;


void _swap(Node &a, Node &b)
{
    Node temp ;
    temp = a ;
    a = b ;
    b = temp ;
}

class MinHeap
{
private:

public:
    Node* harr ;
    int capacity ;
    int heap_size ;

    MinHeap(int cap)
    {
        heap_size = 0 ;
        capacity = cap ;
        harr = new Node [cap] ;
    }

    bool linear_search(Node input)
    {
        for (int i=0 ; i<heap_size ; i++)
        {
            if (harr[i].x == input.x && harr[i].y == input.y)
            {
                //cout << "value found" << endl ;
                return true;
            }
        }
        //cout << "value not found" << endl ;
        return false ;
    }

    void print_array()
    {
        for (int i=0 ; i<heap_size ; i++)
        {
            cout << "(" << harr[i].x << ", " << harr[i].y << ")" << endl ;
        }
        cout << endl ;
    }

    int height()
    {
        return ceil(log2(heap_size + 1)) - 1 ;
    }

    int parent(int i)
    {
        return (i-1)/2 ;
    }

    int left(int i)
    {
        return 2*i+1 ;
    }

    int right(int i)
    {
        return 2*i+2 ;
    }

    void insert_key(Node new_node)
    {
        if (heap_size == capacity)
        {
            cout << "heap is full" << endl ;
            return ;
        }

        heap_size++ ;
        int i = heap_size - 1 ;
        harr[i] = new_node ;

        while (i != 0 && harr[parent(i)].f_cost > harr[i].f_cost)
        {
            _swap(harr[i], harr[parent(i)]) ;
            i = parent(i) ;
        }
    }

    void minHeapify(int i)
    {
        int l = left(i) ;
        int r = right(i) ;
        int smallest = i ;

        if (l < heap_size && harr[l].f_cost < harr[i].f_cost)
        {
            smallest = l ;
        }
        if (r < heap_size && harr[r].f_cost < harr[smallest].f_cost)
        {
            smallest = r ;
        }
        if (smallest != i)
        {
            _swap(harr[i], harr[smallest]) ;
            minHeapify(smallest) ;
        }
    }

    Node extract_min()
    {
        if (heap_size <= 0)
        {
            return grid[0][0] ;
        }
        if (heap_size == 1)
        {
            heap_size-- ;
            return harr[0] ;
        }

        Node root = harr[0] ;
        harr[0] = harr[heap_size-1] ;
        heap_size-- ;
        minHeapify(0) ;
        return root ;
    }

    Node get_min()
    {
        return harr[0] ;
    }


    void decrease_key(int i, int new_f_val)
    {
        harr[i].f_cost = new_f_val ;
        while (i != 0 && harr[parent(i)].f_cost > harr[i].f_cost)
        {
            _swap(harr[i], harr[parent(i)]) ;
            i = parent(i) ;
        }
    }

    void delete_key(int i)
    {
        decrease_key(i, 0) ;
        extract_min() ;
    }



};

MinHeap mh(3600) ;


void initialize_grid()
{
    for (int i=0 ; i<64 ; i++)
    {
        for (int j=0 ; j<64 ; j++)
        {
            grid[i][j].x = i ;
            grid[i][j].y = j ;
            grid[i][j].walkable = true ;
            grid[i][j].g_cost = 99999999  ;
            grid[i][j].h_cost = 99999999  ;
            grid[i][j].f_cost = 99999999  ;
            grid[i][j].parent_x = starting_x ;
            grid[i][j].parent_y = starting_y ;
            grid[i][j].is_closed = false ;
            grid[i][j].is_open = false ;
            grid[i][j].shape = 176 ;
        }
    }
}

void place_walls()
{
    for (int i=27 ; i<35 ; i++)
    {
        for (int j=20 ; j<35 ; j++)
        {
            grid[i][j].walkable = false ;
            grid[i][j].shape = 178 ;
        }
    }

    for (int i=41 ; i<53 ; i++)
    {
        for (int j=5 ; j<25 ; j++)
        {
            grid[i][j].walkable = false ;
            grid[i][j].shape = 178 ;
        }
    }

    for (int i=41 ; i<53 ; i++)
    {
        for (int j=37 ; j<57 ; j++)
        {
            grid[i][j].walkable = false ;
            grid[i][j].shape = 178 ;
        }
    }

    for (int i=5 ; i<15 ; i++)
    {
        for (int j=24 ; j<40 ; j++)
        {
            grid[i][j].walkable = false ;
            grid[i][j].shape = 178 ;
        }
    }

    for (int i=0 ; i<64 ; i++)
    {
        grid[i][0].walkable = false ;
        grid[i][0].shape = 178 ;
    }
    for (int i=0 ; i<64 ; i++)
    {
        grid[i][63].walkable = false ;
        grid[i][63].shape = 178 ;
    }

    for (int i=0 ; i<63 ; i++)
    {
        grid[0][i].walkable = false ;
        grid[0][i].shape = 178 ;
    }

    for (int i=0 ; i<63 ; i++)
    {
        grid[63][i].walkable = false ;
        grid[63][i].shape = 178 ;
    }
}

void setup_starting_point()
{
    grid[starting_x][starting_y].is_open = true ;
    grid[starting_x][starting_y].g_cost = 0 ;
    grid[starting_x][starting_y].h_cost = pow((grid[starting_x][starting_y].x-end_point_x), 2) + pow((grid[starting_x][starting_y].y-end_point_y), 2) ;
    grid[starting_x][starting_y].f_cost = grid[starting_x][starting_y].g_cost + 0.01*grid[starting_x][starting_y].h_cost ;
    mh.insert_key(grid[starting_x][starting_y]) ;
}


void show_final_path()
{
    Node* temp_node = &grid[end_point_x][end_point_y] ;
    while (temp_node->x != starting_x || temp_node->y != starting_y)
    {
        grid[temp_node->x][temp_node->y].shape = '*' ;
        temp_node = &grid[temp_node->parent_x][temp_node->parent_y] ;
    }


    for (int i=0 ; i<64 ; i++)
    {
        for (int j=0 ; j<64 ; j++)
        {
            cout << grid[i][j].shape ;
        }
        cout << endl ;
    }
}



void run_aStar()
{
    //Node* current_node = &grid[find_open_node_with_lowest_f().x][find_open_node_with_lowest_f().y] ;
    Node* current_node = &grid[mh.get_min().x][mh.get_min().y] ;
    Node* end_node = &grid[end_point_x][end_point_y] ;

    while ( !( (current_node->x == end_node->x) && (current_node->y == end_node->y) ) )
    {
        if (no_path_exists)
        {
            cout << "no path" << endl ;
            break ;
        }
        //current_node = &grid[find_open_node_with_lowest_f().x][find_open_node_with_lowest_f().y] ;
        current_node = &grid[mh.get_min().x][mh.extract_min().y] ;
        current_node->is_open = false ;
        current_node->is_closed = true ;
        for (int i=-1 ; i<=1 ; i++)
        {
            for (int j=-1 ; j<=1 ; j++)
            {
                if (i==0 && j==0)
                {
                    continue ;
                }
                if (current_node->x + i<64 && current_node->x + i>=0 && current_node->y + j<64 && current_node->y + j>=0)
                {
                    int temp_x = current_node->x + i ;
                    int temp_y = current_node->y + j ;
                    if (!grid[temp_x][temp_y].walkable || grid[temp_x][temp_y].is_closed)
                    {
                        continue ;
                    }
                    double g_neighbour = current_node->g_cost + pow(i, 2) + pow(j, 2) ;
                    double h_neighbour =  pow((grid[temp_x][temp_y].x-end_node->x), 2) + pow((grid[temp_x][temp_y].y-end_node->y), 2) ;
                    //if ( (g_neighbour < grid[temp_x][temp_y].g_cost)  || !grid[temp_x][temp_y].is_open)
                    if ( (g_neighbour < grid[temp_x][temp_y].g_cost)  || !mh.linear_search(grid[temp_x][temp_y]))
                    {
                        if (g_neighbour < grid[temp_x][temp_y].g_cost)
                        {
                            grid[temp_x][temp_y].g_cost = g_neighbour ;
                        }
                        grid[temp_x][temp_y].g_cost = g_neighbour ;
                        grid[temp_x][temp_y].h_cost = h_neighbour ;
                        grid[temp_x][temp_y].f_cost = 0.01*h_neighbour + g_neighbour ;
                        grid[temp_x][temp_y].parent_x = current_node->x ;
                        grid[temp_x][temp_y].parent_y = current_node->y ;
                        //if (!grid[temp_x][temp_y].is_open)
                        //{
                        //    grid[temp_x][temp_y].is_open = true ;
                        //}
                        if (!mh.linear_search(grid[temp_x][temp_y]))
                        {
                            grid[temp_x][temp_y].is_open = true ;
                            mh.insert_key(grid[temp_x][temp_y]) ;
                        }
                    }
                }
            }
        }
    }
}


Node find_open_node_with_lowest_f()
{
    int saved_i=-1, saved_j=-1 ;
    double min_f = 9999999 ;
    for (int i=0 ; i<64 ; i++)
    {
        for (int j=0 ; j<64 ; j++)
        {
            if (grid[i][j].is_open && grid[i][j].f_cost<min_f)
            {
                saved_i = grid[i][j].x ;
                saved_j = grid[i][j].y ;
                min_f = grid[i][j].f_cost ;
            }
        }
    }
    if (saved_i == -1)
    {
        no_path_exists = true ;
        return grid[0][0] ;
    }
    return grid[saved_i][saved_j] ;
}




int main()
{
    initialize_grid() ;
    place_walls() ;
    setup_starting_point() ;
    int a = time(NULL) ;
    cout << "start time: " << a << endl ;
    auto start1 = high_resolution_clock::now();
    run_aStar() ;
    auto stop1 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop1 - start1);
    int b = time(NULL) ;
    cout << "end time: " << b << endl ;

    cout << "duration: " << b-a << endl ;
    cerr << "Time taken in microseconds : "
         << (double)(duration.count() / 1000.0) << endl;
    show_final_path() ;


    return 0;
}
