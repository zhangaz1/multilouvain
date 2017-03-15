#include <iostream>
#include <fstream>
#include <Eigen/Core>
#include "ModularityVertexPartition.h"
#include "GraphHelper.h"
#include "Optimiser.h"

using namespace std;

void igraph_matrix_view(igraph_matrix_t *A, igraph_real_t *data, int nrows, int ncols)
{
    A->ncol = nrows;
    A->nrow = ncols;
    A->data.stor_begin = data;
    A->data.stor_end = data+ncols*nrows;
    A->data.end = A->data.stor_end;
}


Eigen::MatrixXd read_adj_matrix(const std::string &filename)
{
    Eigen::MatrixXd adj_mat;

    ifstream file;
    file.open(filename.c_str(),std::ios::in);

    vector<vector<double> > data;
    string line;

    while(!std::getline(file, line, '\n').eof())
    {
        std::istringstream reader(line);
        vector<double> lineData;
        while(!reader.eof())
        {
            double val;
            reader >> val;
            if(reader.fail())
                break;
            lineData.push_back(val);
        }
        data.push_back(lineData);
    }
    // Deep copy of data array to the adjacency matrix
    adj_mat.setZero(data.size(),data.size());
    for (unsigned int i=0; i<data.size(); ++i)
        for (unsigned int j=0; j<data.size(); ++j)
            adj_mat.coeffRef(i,j)=data[i][j];

    return adj_mat;
}

int main(int argc, char *argv[])
{

    // Create the graph from the adjacency matrix
    // Fill the adjacency matrix of the graph
    Eigen::MatrixXd A = read_adj_matrix(std::string(argv[1]));

    
    // Create the Graph helper object specifying edge weights too
    Graph *G = init(A.data(),A.rows(),A.cols());
    
    delete G;
    return 0;

    // // Create the partition function
    // MutableVertexPartition *partition;

    // vector<size_t> memb(34);

    // partition = new ModularityVertexPartition(G,memb);

    // double Qold = partition->quality();
    // double delta = partition->diff_move(3,0);
    // partition->move_node(3,0);
    // cerr << "===========" << endl;
    // double Qnew = partition->quality();
    // cerr << "Delta=" << delta << " Qnew-qold=" << Qnew-Qold << endl;

    // Qold = partition->quality();
    // delta = partition->diff_move(4,0);
    // partition->move_node(4,0);
    // cerr << "===========" << endl;
    // Qnew = partition->quality();
    // cerr << "Delta=" << delta << " Qnew-qold=" << Qnew-Qold << endl;

    // delete partition;
    // delete G;
    // return 0;
}