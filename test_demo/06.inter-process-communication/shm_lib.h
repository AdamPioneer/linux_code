/*shm.h*/

#ifndef SHM_H
#define SHM_H

#ifdef __cplusplus
extern "C"{
#endif
typedef struct {
	char name[4];
	int age;
}people;
people* initshm(void);
void *Create_sharememory(const char *filename,unsigned int SizeCount);
void close_sharememory(void *pshare);
int get_age(people *p);
void set_age(people *p,int age);
#ifdef __cplusplus
}
#endif
#endif
