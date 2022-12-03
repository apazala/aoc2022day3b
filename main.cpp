#include <stdio.h>
#include <string.h>


int loadInputFile();
inline int nextLine(char *dst);


char line[128];
int letterSet[128];
int main(){
    if(loadInputFile()<0){
        fprintf(stderr, "Can't open: input.txt\n");
        return 1;
    }

    int prioritiesSum = 0, len;
    while(len = nextLine(line)){
        memset(letterSet, 0, sizeof(letterSet));

        for(int i = 0; i < len; i++){
            letterSet[line[i]] = 1;
        }

        len = nextLine(line);
        for(int i = 0; i < len; i++){
            char c = line[i];
            if(letterSet[c]) letterSet[c] = 2;
        }

        char p = 0;
        len = nextLine(line);
        for(int i = 0; p == 0 && i < len; i++){
            char c = line[i];
            p = (letterSet[c]==2?c:0);
        }

        prioritiesSum += (p>='a'? p - 'a' + 1: p - 'A' + 27);
    }

    printf("%d\n", prioritiesSum);
}


#define BUFSIZE 1<<14

char fileBuf[BUFSIZE];
char *pbuf = fileBuf;
char *pbufend = fileBuf;

int loadInputFile() {
    FILE *pf = fopen("input.txt", "r");
    if(!pf) return -1;
	pbuf = fileBuf;
	pbufend = fileBuf + fread(fileBuf, 1, BUFSIZE, pf);
    fclose(pf);
    
    return 0;
}

inline int nextLine(char *dst){
    unsigned char c;
	char *orig = dst;
    
    //skip whites
    while(*pbuf< 'A' && pbuf < pbufend ){
        pbuf++;
    }

	//read line
	while(pbuf < pbufend && (c = *(pbuf++))>= 'A'){
		*(dst++)=c;
	}
	
    //return line length
    return dst - orig;
}