#ifndef LIBFORTASK_H
#define LIBFORTASK_H



char* allocMemory();
char* reallocMemory(char* s, const int len);
char* getString();
char* delSpace(char* s);
void freeString(char* s);

#endif // LIBFORTASK_H
