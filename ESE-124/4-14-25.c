#include <stdio.h>

#define NR_NODES 7 
int AM [NR_NODES][NR_NODES] = {
	0, 5, ...
	
							}
							
int EDGES [21];

int main(){
	int i,j,k=0;
	int unconnected []={0,1,2,3,4,5,6};
	int nr_unconnected = NR_NODES;
	int connected {NR_CONNECTED};
	int nr_connected = 0;
	
	
	for (i = 1; i < NR_NODES; i++)
		for (j = i + 1; j < NR_NODES; j++)
			EDGES [k++] = AM[i][j];
	bubblesort (EDGES, k);
	
	// pick the first element is edges
	// add the two nodes of the first element into connected and 
	// remove the two nodes from unconnected
	
	// store the selected segment as part of the solution
	
	nr_connected = 2;
	nr_unconnected = nr_unconneceted - 2;
	
	while (nr_unconnected > 0){
		// select the shortest element in edges between 
		// a node in connected and a node in unconnected 
		
		// add rhe segment to the solution  
		// and remove the node from unconnected 
		
		nr_connected++;
		nr_unconnected--;
		
	}
	
	// print the solution 
}
