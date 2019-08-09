#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Instance {
  char text[50];
  int score;
} Instance;

Instance instanceTable[25];

void sortDescOrder();

void main() {
  setlocale (LC_ALL, "");

  FILE *csvFile;
  char string[200];
  char row[50];
  char *tmp;
  char fileName[60];
  int i = 0;

  printf("Enter filename: ");
  scanf("%s", &fileName);

  csvFile = fopen(fileName, "r");

  if (csvFile == NULL) {
    printf("Error opening file\n\n");
  } else {
    printf("File successfully opened\n\n");
  }

  while (fgets(string, sizeof(string), csvFile) != NULL) {
    tmp = strtok(string, ",");
    strcpy(instanceTable[i].text, tmp);

    tmp = strtok(NULL, ",");
    instanceTable[i].score = atoi(tmp);

    printf("%s %i\n", instanceTable[i].text, instanceTable[i].score);

    i++;
  }

  sortDescOrder(instanceTable, 25);

  printf("\n\n");

  for(i = 0; i < 25; i++) {
    printf("%s %i\n", instanceTable[i].text, instanceTable[i].score);
  }

  system("pause");
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
