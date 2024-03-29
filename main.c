#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Instance {
  char text[50];
  int score;
} Instance;

char *inputText();
FILE *openFile();
void sortDescOrder();
Instance *parseCsv();

void main() {
  setlocale (LC_ALL, "");
	
	Instance *instanceTable;

  FILE *csvFile;
  char *fileName;
  int i = 0;

  fileName = inputText("Enter csv filename: ", 60);

  csvFile = openFile(fileName, "r", ".csv");

  free(fileName);

  instanceTable = parseCsv(csvFile);

  sortDescOrder(instanceTable, 25);

  printf("\n\n");

  for(i = 0; i < 25; i++) {
    printf("%s %i\n", instanceTable[i].text, instanceTable[i].score);
  }

	free(instanceTable);
  fclose(csvFile);
  system("pause");
}

char *inputText(char printText[], int inputLength) {
  char *input = (char*) malloc(inputLength * sizeof(char));

  printf("%s", printText);
  gets(input);

  return input;
}

Instance *parseCsv(FILE *csvFile) {
  Instance *instanceTable = (Instance *) malloc(25 * sizeof(Instance));
  
    char string[200];
    char *tmp;
    int i = 0;

  while (fgets(string, sizeof(string), csvFile) != NULL) {
    tmp = strtok(string, ",");
    strcpy(instanceTable[i].text, tmp);

    tmp = strtok(NULL, ",");
    instanceTable[i].score = atoi(tmp);

    printf("%s %i\n", instanceTable[i].text, instanceTable[i].score);

    i++;
  }

  return instanceTable;
}

FILE *openFile(char fileName[], char accessMode[], char extension[]) {
  FILE *file;
  
  strcat(fileName, extension);

  file = fopen(fileName, accessMode);

  if (file == NULL) {
    printf("Error opening file\n\n");
    system("pause");
    exit(-1);
  } else {
    printf("File successfully opened\n\n");
    return file;
  }
}

void sortDescOrder(Instance *instanceTable, int sizeOfTable) {
  Instance aux;
	int gap = sizeOfTable / 2;
	int i, j;
	
	while (gap > 0) {
		for (i = gap; i < sizeOfTable; i++) {
			aux = instanceTable[i];
			j = i;
			
			while (j >= gap && aux.score > instanceTable[j - gap].score) {
				instanceTable[j] = instanceTable[j - gap];
				j = j - gap;
			}
			instanceTable[j] = aux;
		}
		gap = gap / 2;
	}
}
