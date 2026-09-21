#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *inp, *outp;
    char ch;
   inp = fopen("input.txt", "r");
    if (inp == NULL) {
        printf("error opening input.txt");
        return 1;
    }
    outp = fopen("output.txt", "w");
    if (outp == NULL) {
        printf("error opening output.txt");
        fclose(inp);
        return 1;
    }
    while (fscanf (inp, "%c", &ch) !=EOF)
    {
        if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
        {
            if (ch == 'Z' )
            {
                ch = 'A';
            } else if (ch == 'z'){
                ch ='a'; 
            }
            else {ch++;}
        }
        fprintf(outp, "%c", ch);
    }
    fclose(inp);
    fclose(outp);
    return 0;
}