#include "books.h"
//#define DEBUG

T_book* books[MAX_AMOUNTS];
int _count = 0;

int b_first_available() {
	int i;
	for(i=0; i<MAX_AMOUNTS; i++) {
		if(books[i] == NULL) return i;
	}
	return -1;
}

void b_create(char* sb, char* cd, int p, int a, int bo) {
	int index = b_first_available();
	books[index] = (T_book*)malloc(sizeof(T_book));
	T_book* b = books[index];
	strcpy(b->subject, sb);
	strcpy(b->code, cd);
	b->page = p;
	b->amount = a;
	b->borrow = bo;
	_count++;
}

void b_read_data(int check) {
	FILE *book_data = fopen("book_data.txt", "r");
	int i=0;
	char sb[40], cd[40];
	int p, a, bo;
	
	if(check == 1) {
		int result;
#ifdef DEBUG
		printf("[DEBUG] Start add record\n");
#endif
		while(1) {
			if(feof(book_data)) break;
			result = fscanf(book_data, "%s %s %d %d %d", cd, sb, &p, &a, &bo);
			if(result < 5) break;
			if(b_search_by_subject(sb)) printf("%s already received!\n", sb);
			else {
				if(b_search_by_code(cd)) printf("%s already received!\n", cd);
				else {
					b_create(sb, cd, p, a, bo);
#ifdef DEBUG
					printf("[DEBUG] add record\n");
#endif
				}
			}
		}
	}
	else {
#ifdef DEBUG
		printf("[DEBUG] Start overwrite record\n");
#endif
		for(int i = 0; i < MAX_AMOUNTS; i++) {
			if(books[i] != NULL) {
				free(books[i]);
				books[i] = NULL;
				_count--;
#ifdef DEBUG
				printf("[DEBUG] Delete original record\n");
#endif
			}
		}
		int result;
		while(1) {
			if(feof(book_data)) break;
			result = fscanf(book_data, "%s %s %d %d %d", cd, sb, &p, &a, &bo);
			if(result < 5) break;
			b_create(sb, cd, p, a, bo);
#ifdef DEBUG
			printf("[DEBUG] Overwrite record\n");
#endif
		}
		
	}
	fclose(book_data);
	printf("Data read.\n");
#ifdef DEBUG
	if(check == 1) printf("[DEBUG] End add record\n");
	else printf("[DEBUG] End overwrite record\n");
#endif
}

void b_save_data() {
	FILE *book_data = fopen("book_data.txt", "w");
	int i;
#ifdef DEBUG
	printf("[DEBUG] Start save data\n");
#endif
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] != NULL) { 
			fprintf(book_data, "%s %s %d %d %d\n", books[i]->code, books[i]->subject, books[i]->page, books[i]->amount, books[i]->borrow);
#ifdef DEBUG
			printf("[DEBUG] Save data\n");
#endif
		}
	}
	fclose(book_data);
	printf("Data saved.\n");
}

void b_report() {
	FILE *report = fopen("book_report.txt", "w");
	int i, index=0;
#ifdef DEBUG
	printf("[DEBUG] Start write report\n");
#endif
	fputs("--- Book Report ---\n\n", report);
	fprintf(report, "Total book : %d\n\n", _count);
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] != NULL) {
			index++;
			fprintf(report, "%d. [%s] %s (p.%d) / amount : %d / borrow : %d\n", index, books[i]->code, books[i]->subject, books[i]->page, books[i]->amount, books[i]->borrow);
#ifdef DEBUG
			printf("[DEBUG] Write report\n");
#endif
		}
	}
	fclose(report);
	printf("Data reported.\n"); 
}

void b_list() {
	int i;
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] != NULL) printf("%s\n", b_to_string(books[i]));
	}
}

int b_count() {
	return _count;
}

char* b_to_string(T_book* b) {
	static char str[80];
	sprintf(str, "[%s] %s (p.%d) / amount : %d(%d)", b->code, b->subject, b->page, b->amount, b->borrow);
	return str;
}

void b_update(T_book* bo, char* sb, char* cd, int p, int a, int b) {
	strcpy(bo->subject, sb);
	strcpy(bo->code, cd);
	bo->page = p;
	bo->amount = a;
	bo->borrow = b;
}

void b_delete(T_book* b) {
	int i;
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] && strcmp(b->subject, books[i]->subject) == 0) {
			printf("'%s' Deleted\n", books[i]->subject);
			free(books[i]);
			books[i] = NULL;
		}
	}
	_count--;
}

T_book* b_search_by_subject(char* sb) {
	int i;
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] && strcmp(books[i]->subject, sb) == 0) return books[i];
	}
	return NULL;
}

T_book* b_search_by_code(char* cd) {
	int i;
	for(i = 0; i < MAX_AMOUNTS; i++) {
		if(books[i] && strcmp(books[i]->code, cd) == 0) return books[i];
	}
	return NULL;
}

void b_many(int mode, int what) {	// mode는 1.Read 2.Update 3.Delete 로 나뉘어져있으며, what은 1.subject, 2.code, 3.page, 4.amount 5.borrow 로 나뉘어져 있다.
	if(what >= 1 && what <= 5) {  		
		char str[40];		// subject나 code 입력하는 변수
		int num;		// page, amount, borrow 입력하는 변수
		int crit;		// page, amount, borrow 일 때 이상, 일치, 이하의 기준을 입력하는 변수
		int no = 0;		// no가 0에서 1로 바뀌는 동작이 없으면 해당하는 책이 없다는 것을 뜻하는 변수

		if(what == 1) printf("Enter a subject > ");		// what == 1 이면 subject
		else if(what == 2) printf("Enter a code > ");		// what == 2 이면 code
		else if(what == 3) printf("Enter a pages > "); 		// what == 3 이면 page
		else if(what == 4) printf("Enter a amount > "); 	// what == 4 이면 amount
		else if(what == 5) printf("Enter a borrow > ");		// what == 5 이면 borrow

		if(what == 1 || what == 2) scanf("%s", str);
		else scanf("%d", &num);
		if(what >= 3 && what <= 5) {
			printf("Crit : 1.More than 2.Same 3.Less than > ");	// 1 입력시 num이상에 해당하는  책들 출력, 2 입력시 num과 같은 책들 출력, 3 입력시 num 이하에 해당하는 책들 출력
			scanf("%d", &crit);
		}

		char update[40];
		int up_num;
		
		for(int i = 0; i < MAX_AMOUNTS; i++) {
			if(books[i] == NULL) continue;
			else {
				if(what == 1) {				// what == 1 이면 subject
					if(strstr(books[i]->subject, str) != NULL) no = 1;
				} else if(what == 2) {			// what == 2 이면 code
					if(strstr(books[i]->code, str) != NULL) no = 1;
				} else if(what == 3) {			// what == 3 이면 page
					if(crit == 1) {
						if(books[i]->page >= num) no = 1;
					}
					else if(crit == 2) {
						if(books[i]->page == num) no = 1;
					}
					else if(crit == 3) {
						if(books[i]->page <= num) no = 1;
					}
				}
				else if(what == 4) {		// what == 4 이면 amount
					if(crit == 1) {
						if(books[i]->amount >= num) no = 1;
					}
					else if(crit == 2) {
						if(books[i]->amount == num) no = 1;
					}
					else if(crit == 3) {
						if(books[i]->amount <= num) no = 1;
					}
				}
				else if(what == 5) {		// what == 5 이면 borrow
					if(crit == 1) {
						if(books[i]->borrow >= num) no = 1;
					}
					else if(crit == 2) {
						if(books[i]->borrow == num) no = 1;
					}
					else if(crit == 3) {
						if(books[i]->borrow <= num) no = 1;
					}
				}
				
				if(no == 1) {
					if(mode == 1) printf("%s\n", b_to_string(books[i]));
					else if(mode == 2) {
						printf("%s\n", b_to_string(books[i]));
						printf("Update Subject > ");
						scanf("%s", update);
						strcpy(books[i]->subject, update);
						printf("Update Code > ");
						scanf("%s", update);
						strcpy(books[i]->code, update);
						printf("Update Page > ");
						scanf("%d", &up_num);
						books[i]->page = up_num;
						printf("Update Amount > ");
						scanf("%d", &up_num);
						books[i]->amount = up_num;
						printf("Update Borrow > ");
						scanf("%d", &up_num);
						books[i]->borrow = up_num;
					}
					else if(mode == 3) {
						printf("'%s' Deleted\n", books[i]->subject);
						free(books[i]);
						books[i] = NULL;
						_count--;
					}
					
					no = 2;
				}
			}
		}
		if(no == 0) printf("No such book!\n");
	}
	else {} 			// default
}
