#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AMOUNTS 100

typedef struct st_book{
	char subject[40];  	// 책이름
	char code[40];		// 책 코드
	int page;		// 책 페이지 수
	int amount;		// 책 수
	int borrow;		// 대여 가능한 책 수
} T_book;

int b_first_available();
void b_create(char* sb, char* cd, int p, int a, int b);
void b_read_data(int check);
void b_save_data();
void b_report();
void b_list();
int b_count();
char* b_to_string(T_book* b);
void b_update(T_book* B, char* sb, char* cd, int p, int a, int b);
void b_delete(T_book* b);
T_book* b_search_by_subject(char* sb);
T_book* b_search_by_code(char* cd);
void b_many(int mode, int what);
void b_sort(int mode);
void b_optimize();
