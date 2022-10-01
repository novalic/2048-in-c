#ifndef _LIST_H
#define _LIST_H

struct AuxList;

typedef AuxList* List;

List createList();
void insertFront(List &l, int i, int j);
int getLength(List &l);
int* returnRandom(List &l);
void destroyList(List &l);


#endif /* _LIST_H */
