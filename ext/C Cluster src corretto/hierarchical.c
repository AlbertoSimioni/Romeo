#include "cluster.c"

void hierarchicalAlgorithm(int nclusters, int nrows, int ncolumns, double** data, int** mask, double weight[], char dist, int transpose, char method, int clusterid[]) {
	double** distanceMatrix = distancematrix(nrows, ncolumns, data, mask, weight, dist, transpose);
	Node* treeCluster = treecluster(nrows, ncolumns, data, mask, weight, transpose, dist, method, distanceMatrix);
	cuttree(nrows, treeCluster, nclusters, clusterid);
	//cuttree(nrows, treecluster(nrows, ncolumns, data, mask, weight, transpose, dist, method, distancematrix(nrows, ncolumns, data, mask, weight, dist, transpose)), nclusters, clusterid);
}
