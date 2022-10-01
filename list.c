
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct AuxList {
    int row;
    int col;
    struct AuxList* nextElement;
};
typedef AuxList* List;

List createList() { return NULL; }

void insertFront(List &l, int i, int j) {
  AuxList * aux = new AuxList;
  aux->nextElement = l;
  aux->row = i;
  aux->col = j;
  l = aux;
}

int getLength(List &l) {
  List aux = l;
  int length = 0;
  while (aux != NULL) {
    length++;
    aux = aux->nextElement;
  }
  return length;
}

int* returnRandom(List &l) {
  int size = getLength(l);

  srand(time(NULL));
  int randomPosition = rand() % size;

  List aux = l;
  for (int i = 0; i < randomPosition; i++)
    aux = aux->nextElement;

  int* elementPositions = (int*) malloc(2 * sizeof(int));
  elementPositions[0] = aux->row;
  elementPositions[1] =  aux->col;

  return elementPositions;
}

void destroyList(List &l) {
    if (l != NULL)
        destroyList(l->nextElement);
    delete l;
}
