#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHA_SZ 26

char toLower(char in){
	switch(in){
		case 'A'...'Z':
			return (in+0x20);
			break;
		default:
			break;
	}
	return in;
}

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

int lutCharIndex(char in){
	int i;
	for(i = 0; i < ALPHA_SZ;i++)
		if(alphabet[i] == in)
			return i;
	return -1;
}

size_t fileSize(FILE* fp){
	if(fp == NULL)
		return -1;
	size_t fsize;
	fsize = 0;
	fseek(fp,0L,SEEK_END);
	fsize = ftell(fp);
	fseek(fp,0L,SEEK_SET);
	return fsize;
}

void printFreqTable(int* freqCounts){
	int i;
	printf("FREQUENCY TABLE\n--------------------\n");
	for(i = 0; i < ALPHA_SZ;i++){
		printf("%c = %i\n",alphabet[i],freqCounts[i]);
	}
	printf("-------------------\n");
}
void printPercents(int* freqCounts,int totalChars){
	int i;
	for(i = 0; i < ALPHA_SZ;i++){
		printf("%c = %f%\n",alphabet[i],(((float)freqCounts[i]) / ((float)totalChars))*100.0);
	}
}

void countFreq(const char* fn,int* freqCounts,int* totalChars){
	char in;
	char lower;
	int index;
	FILE* fp;
	int i;

	fp = fopen(fn,"r");
	
	for(i = 0; i < ALPHA_SZ;i++)
		freqCounts[i] = 0;

	while((in = fgetc(fp)) != EOF){
		lower = toLower(in);
		index = lutCharIndex(lower);
		if(index != -1){
			freqCounts[index]++;
			(*totalChars)++;
		}
	}
	fclose(fp);
}


int main(int argc,char** argv){
	int freqCounts[ALPHA_SZ];
	int totalChars = 0;
	if(argc < 2)
		printf("Usage: langfreq [infile]\n");
	else{
		countFreq(argv[1],freqCounts,&totalChars);
		printFreqTable(freqCounts);
		printPercents(freqCounts,totalChars);
	}	
	return 0;
}

