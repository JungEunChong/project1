# Book Management Program #

## Base struct and define ##

```C
#define MAX_AMOUNTS 100

typedef struct st_book{
        char subject[40];       // 책이름
        char code[40];          // 책 코드
        int page;               // 책 페이지 수
        int amount;             // 책 수
        int borrow;             // 대여 가능한 책 수
} T_book;
```

There is book's option.
1. Subject
2. code
3. page
4. amount
5. borrow

And max amounts of book is '100'.

***

## Menu ##

```C
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
```

This program has total 13 menu.

***

### 1. Receive_book ###

```C
void receive_book() {
        if(b_count() == MAX_AMOUNTS) printf("There is no space!\n");
        else {
                char subject[40], code[40];
                int page, amount, borrow;
                printf("Enter a new book's info.\n");
                printf("Subject > ");
                scanf(" %[^\n]s", subject);
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
```

This menu 'Create' record.
Enter '5 option of book' and store them in the book struct record.

### 2. Receive_by_file ###

```C
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
```

This menu is to load file. ( book_data.txt )

### 3. Info_book ###

```C
void info_book() {
        char subject[40];
        T_book* b;
        printf("Enter a subject > ");
        scanf(" %[^\n]s", subject);
        if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
        else {
                b = b_search_by_subject(subject);
                printf("Book info.\n");
                printf("%s\n", b_to_string(b));
        }
}
```

This menu 'Read' record.
If you write down the subject, you will find a book with the same subject.

### 4. Search_book ###

```C
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
```

This menu 'Read' record.
You can find many books through book options.

### 5. List_book ###

```C
void list_book() {
        printf("-- Book List --\n");
        b_list();
}
```
```C
void b_list() {
        int i;
        printf("< Total : %d >\n", b_count());
        for(i = 0; i < MAX_AMOUNTS; i++) {
                if(books[i] != NULL) printf("%d. %s\n", i+1, b_to_string(books[i]));
        }
}
```

This menu 'Read' record.
It shows a complete list of books.
(Contains the number of books and record storage numbers.)

### 6. Save_file ###

```C
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
```

This menu is to save file. ( book_data.txt )

### 7. Report_file ###

```C
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
```

This menu is to write a report file ( book_report.txt )

### 8. Update_book_one ###

```C
void update_book_one() {
        char subject[40];
        char sb[40];
        char cd[40];
        int p, a, b;
        T_book* bo;
        printf("Enter a subject > ");
        scanf(" %[^\n]s", subject);
        if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
        else {
                bo = b_search_by_subject(subject);
                printf("Enter Subject > ");
                scanf(" %[^\n]s", sb);
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
```

This menu 'Update' record.
Enter a subject to update the record of a book with the same subject.

### 9. Update_book ###

```C
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
```

This menu 'Update' record.
You can update many books through book options.

### 10. Release_book_one ###

```C
void release_book_one() {
        char subject[40];
        T_book* bo;
        printf("Enter a subject > ");
        scanf(" %[^\n]s", subject);
        if(b_search_by_subject(subject) == NULL) printf("No such book!\n");
        else {
                bo = b_search_by_subject(subject);
                b_delete(bo);
        }
}
```

This menu 'Delete' record.
Enter a subject to delete the record of a book with the same subject.

### 11. Release_book ###

```C
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
```

This menu 'Delete' record.
You can delete many books through book options.

### 12. Sort_book ###

```C
void sort_book() {
        int menu;
        RE:
        printf("Find Method (1.Subject 2.Code 3.Page 4.Amount 5.Borrow) > ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu) {
                case 1:
                        b_sort(1);
                        break;
                case 2:
                        b_sort(2);
                        break;
                case 3:
                        b_sort(3);
                        break;
                case 4:
                        b_sort(4);
                        break;
                case 5:
                        b_sort(5);
                        break;
                default:
                        goto RE;
                        break;
        }
}
```

You can delete books record through book options.

### 13. Optimize_record ###

```C
void optimize_record() {
        b_optimize();
}
```
```C
void b_optimize() {
        int op = 0;

        char tmpSb[40];
        char tmpCd[40];
        int tmpP, tmpA, tmpB;

        while(1) {
                if(op == 1) break;

                int index = b_first_available();
                if(index == -1) {
                        printf("Full!!\n");
                        break;
                }

                for(int i = index; i < MAX_AMOUNTS; i++) {
                        if(books[i] != NULL) {
                                strcpy(tmpSb, books[i]->subject);
                                strcpy(tmpCd, books[i]->code);
                                tmpP = books[i]->page;
                                tmpA = books[i]->amount;
                                tmpB = books[i]->borrow;

                                b_delete(books[i]);

                                b_create(tmpSb, tmpCd, tmpP, tmpA, tmpB);
                                break;
                        }
                        //printf("%d\n", i);
                        if(i == MAX_AMOUNTS - 1) op = 1;
                }
        }

        printf("Optimize Completed\n");
}
```

This menu optimize (there's no empty space in the middle) book struct record number.
