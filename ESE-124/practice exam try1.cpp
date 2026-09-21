#include <stdio.h>
#include <stdlib.h>

int main(){
	 
	FILE *inp, *inp2, *outp;
	float a1[12], a2[12], a3[12];
	int size1 = 0, size2 = 0;
	int i,j,k = 0;
	
	if ((inp = fopen("File1.txt", "r")) == NULL) {
        printf("File1.txt cannot be opened\n");
        exit(1);
    }

    if ((inp2 = fopen("File2.txt", "r")) == NULL) {
        printf("File File2.txt cannot be opened\n");
        exit(1);
    }
	
	if ((outp = fopen("File3.txt", "w")) == NULL){
		printf("File File3.txt cannot be opened\n");
        exit(1);
	}
	while(fscanf(inp, "%f", &a1[size1]) !=EOF){
		size1++;
	}
	while(fscanf(inp2, "%f", &a2[size2]) !=EOF){
		size2++;
	}
	for ( i=0; i < size1; i++){
		for ( j=0; j < size2; j++){
		if (a1[i] == a2[j])	a3[k++] = a2[j];
	}
	}
	for (i=0; i < k; i++){
		//fprintf(outp, "%f ", a3[i]);
		fprintf(outp, "%f\n", a3[i]);
		printf ("%f", a3[i]);
	}
	fclose(outp);
	fclose(inp);
	fclose(inp2);
	
	return 0;
}

