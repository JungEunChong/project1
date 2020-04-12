#include "books.h"

void receive_book();
void receive_by_file();
void info_book();
void search_book();
void list_book();
void save_file();
void report_file();
void update_book_one();
void update_book();
void release_book_one();
void release_book();
void sort_book();
void optimize_record();

int main() {
	int menu;
	while(1) {
		printf("\nMenu : 1.Receive 2.Receive(file) 3.info 4.Search 5.List 6.Save 7.Report 8.Update_one 9.Update 10.Delete_one 11.Delete 12.Sort 13.Optimize 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			case 1:
				receive_book();
				break;
			case 2:
				receive_by_file();
				break;
			case 3:
				info_book();
				break;
			case 4:
				search_book();
				break;
			case 5:
				list_book();
				break;
			case 6:
				save_file();
				break;
			case 7:
				report_file();
				break;
			case 8:
				update_book_one();
				break;
			case 9:
				update_book();
				break;
			case 10:
				release_book_one();
				break;
			case 11:
				release_book();
				break;
			case 12:
				sort_book();
				break;
			case 13:
				optimize_record();
				break;
			case 0:
			default:
				return 0;
		}
	}
	return 0;
}

void receive_book() {
	if(b_count() == MAX_AMOUNTS) printf("There is no space!\n");
	else {
		char subject[40], code[40];
		int page, amount, borrow;
		printf("Enter a new book's info.\n");
		printf("Subject > ");
		scanf("%s", subject);
		if(b_search_by_subject(subject)) {
			printf("Duplicated subject!\n");
			return;
		}
		printf("Code > ");
		scanf("%s", code);
		if(b_search_by_code(code)) {
			printf("Buplicated code!\n");
			return;
		}
		printf("Page > ");
		scanf("%d", &page);
		printf("Amount > ");
		scanf("%d", &amount);
		printf("Borrow > ");
		scanf("%d", &borrow);
		b_create(subject, code, page, amount, borrow);	
	}
}

void receive_by_file() {
	int check;
	printf("Do you add record by file? of Overwrite record by file? (1: add 2: overwrite) : ");
	while(1) {
		scanf("%d", &check);
		if(check == 1 || check == 2) break;
		else printf("Please choose 1 or 2\n");
	}

	if(check == 1) b_read_data(1);
	else b_read_data(2);
}

void info_book() {
	char subject[40];
	T_book* b;
	printf("Enter a subject > ");
	scanf("%s", subject);
	if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
	else {
		b = b_search_by_subject(subject);
		printf("Book info.\n");
		printf("%s\n", b_to_string(b));
	}
}

void search_book() {
	int menu;
	RE:
	printf("Find Method (1.Subject 2.Code 3.Page 4.Amount 5.Borrow) > ");
	scanf("%d", &menu);
	printf("\n");

	switch(menu) {
		case 1:
			b_many(1, 1);
			break;
		case 2:
			b_many(1, 2);
			break;
		case 3:
			b_many(1, 3);
			break;
		case 4:
			b_many(1, 4);
			break;
		case 5:
			b_many(1, 5);
			break;
		default:
			goto RE;
			break;
	}		
}

void list_book() {
	printf("-- Book List --\n");
	b_list();
}

void save_file() {
	int check;
	printf("Do you overwrite save file? (1: Yes 2: No) : ");
	while(1) {
		scanf("%d", &check);
		if(check == 1 || check == 2) break;
		else printf("Please choose 1 or 2\n");
	}

	if(check == 1) b_save_data();
}

void report_file() {
	int check;
	printf("Do you overwrite report file? (1: Yes 2: No) : ");
	while(1) {
		scanf("%d", &check);
		if(check == 1 || check == 2) break;
		else printf("Please choose 1 or 2\n");
	}

	if(check == 1) b_report();
}

void update_book_one() {
	char subject[40];
	char sb[40];
	char cd[40];
	int p, a, b;
        T_book* bo;
        printf("Enter a subject > ");
        scanf("%s", subject);
        if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
        else {
		bo = b_search_by_subject(subject);
		printf("Enter Subject > ");
		scanf("%s", sb);
		printf("Enter Code > ");
		scanf("%s", cd);
		printf("Enter Page > ");
		scanf("%d", &p);
		printf("Enter Amount > ");
		scanf("%d", &a);
		printf("Enter Borrow > ");
		scanf("%d", &b);
		b_update(bo, sb, cd, p, a, b);
		printf("Updated\n");
        }
}

void update_book() {
	int menu;
        RE:
        printf("Find Method (1.Subject 2.Code 3.Page 4.Amount 5.Borrow) > ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu) {
                case 1:
                        b_many(2, 1);
                        break;
                case 2:
                        b_many(2, 2);
                        break;
                case 3:
                        b_many(2, 3);
                        break;
                case 4:
                        b_many(2, 4);
                        break;
                case 5:
                        b_many(2, 5);
                        break;
                default:
                        goto RE;
                        break;
        }
}

void release_book_one() {
        char subject[40];
        T_book* bo;
        printf("Enter a subject > ");
        scanf("%s", subject);
        if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
        else {
                bo = b_search_by_subject(subject);
		b_delete(bo);
        }
}

void release_book() {
        int menu;
        RE:
        printf("Find Method (1.Subject 2.Code 3.Page 4.Amount 5.Borrow) > ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu) {
                case 1:
                        b_many(3, 1);
                        break;
                case 2:
                        b_many(3, 2);
                        break;
                case 3:
                        b_many(3, 3);
                        break;
                case 4:
                        b_many(3, 4);
                        break;
                case 5:
                        b_many(3, 5);
                        break;
                default:
                        goto RE;
                        break;
        }

}

void sort_book() {

}

void optimize_record() {

}
