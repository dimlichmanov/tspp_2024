#include <iostream>
#include <vector>
#include "papi.h"

class CSR_graph {
    int row_count; //number of vertices in graph
    unsigned int col_count; //number of edges in graph
    
    std::vector<unsigned int> row_ptr;
    std::vector<int> col_ids;
    std::vector<double> vals;

public:

    void read(const char* filename) {
        FILE *graph_file = fopen(filename, "rb");
        fread(reinterpret_cast<char*>(&row_count), sizeof(int), 1, graph_file);
        fread(reinterpret_cast<char*>(&col_count), sizeof(unsigned int), 1, graph_file);
        
        row_ptr.resize(row_count + 1);
        col_ids.resize(col_count);
        vals.resize(col_count);
         
        fread(reinterpret_cast<char*>(row_ptr.data()), sizeof(unsigned int), row_count + 1, graph_file);
        fread(reinterpret_cast<char*>(col_ids.data()), sizeof(int), col_count, graph_file);
        fread(reinterpret_cast<char*>(vals.data()), sizeof(double), col_count, graph_file);
    }

    void print_vertex(int idx) {
        for (int col = row_ptr[idx]; col < row_ptr[idx + 1]; col++) {
            std::cout << col_ids[col] << " " << vals[col] <<std::endl;
        }
        std::cout << std::endl;
    }

    void reset() {
        row_count = 0;
        col_count = 0;
        row_ptr.clear();
        col_ids.clear();
        vals.clear();
    }
}; 

#define N_TESTS 5

int main () {
    const char* filenames[N_TESTS];
    filenames[0] = "synt";
    /* Тесты 1-4 будут выложены 3.10 */

    for (int n_test = 0; n_test < 1; n_test++) {
        CSR_graph a;
        a.read(filenames[n_test]);
        

        //


    }
}