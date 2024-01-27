#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

void _swap(int &a, int &b)
{
    int temp ;
    temp = a ;
    a = b ;
    b = temp ;
}

class MinHeap
{
private:

public:
    int* harr ;
    int capacity ;
    int heap_size ;

    MinHeap(int cap)
    {
        heap_size = 0 ;
        capacity = cap ;
        harr = new int [cap] ;
    }

    void linear_search(int value)
    {
        for (int i=0 ; i<heap_size ; i++)
        {
            if (harr[i] == value)
            {
                cout << "value found" << endl ;
                return ;
            }
        }
        cout << "value not found" << endl ;
    }

    void print_array()
    {
        for (int i=0 ; i<heap_size ; i++)
        {
            cout << harr[i] << ", " ;
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

    void insert_key(int _val)
    {
        if (heap_size == capacity)
        {
            cout << "heap is full" << endl ;
            return ;
        }

        heap_size++ ;
        int i = heap_size - 1 ;
        harr[i] = _val ;

        while (i != 0 && harr[parent(i)] > harr[i])
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

        if (l < heap_size && harr[l] < harr[i])
        {
            smallest = l ;
        }
        if (r < heap_size && harr[r] < harr[smallest])
        {
            smallest = r ;
        }
        if (smallest != i)
        {
            _swap(harr[i], harr[smallest]) ;
            minHeapify(smallest) ;
        }
    }

    int extract_min()
    {
        if (heap_size <= 0)
        {
            return INT_MAX ;
        }
        if (heap_size == 1)
        {
            heap_size-- ;
            return harr[0] ;
        }

        int root = harr[0] ;
        harr[0] = harr[heap_size-1] ;
        heap_size-- ;
        minHeapify(0) ;
        return root ;
    }

    int get_min()
    {
        return harr[0] ;
    }


    void decrease_key(int i, int new_val)
    {
        harr[i] = new_val ;
        while (i != 0 && harr[parent(i)] > harr[i])
        {
            _swap(harr[i], harr[parent(i)]) ;
            i = parent(i) ;
        }
    }

    void delete_key(int i)
    {
        decrease_key(i, INT_MIN) ;
        extract_min() ;
    }



};

int main()
{
    int s ;
    cout << "enter size of minHeap" << endl ;
    cin >> s ;

    MinHeap mh(s) ;
    cout << "minHeap created" << endl ;

    int option, val ;
    do
    {
        cout << "Choose option: " << endl ;
        cout << "1. Insert key/node/value" << endl ;
        cout << "2. Search key/node" << endl ;
        cout << "3. Delete key/node" << endl ;
        cout << "4. Get Min" << endl ;
        cout << "5. Extract Min" << endl ;
        cout << "6. Height of Heap" << endl ;
        cout << "7. Print/Traversal heap values" << endl ;
        cout << "8. Clear screen" << endl ;
        cout << "0. Exit program" << endl ;

        cin >> option ;

        switch (option)
        {
        case 0:
            break ;
        case 1:
            cout << "Insert operation - enter value: " << endl ;
            cin >> val ;
            mh.insert_key(val) ;
            cout << endl ;
            break ;
        case 2:
            cout << "Search operation - enter value: " << endl ;
            cin >> val ;
            mh.linear_search(val) ;
            cout << endl ;
            break ;
        case 3:
            cout << "Delete operation - enter index value to delete: " << endl ;
            cin >> val ;
            mh.delete_key(val) ;
            cout << endl ;
            break ;
        case 4:
            cout << "Get min value operation. " << endl ;
            cout << mh.get_min() ;
            cout << endl ;
            break ;
        case 5:
            cout << "Extract min value. " << endl ;
            cout << mh.extract_min() << endl ;
            break ;
        case 6:
            cout << "heap tree height: " << endl ;
            cout << mh.height() << endl ;
            break ;
        case 7:
            cout << " Print array operation. " << endl ;
            mh.print_array() ;
            cout << endl ;
            break ;
        case 8:
            system("cls") ;
            break ;
        default:
            cout << "enter valid number." << endl ;
        }
    }while (option != 0) ;
    return 0;
}
