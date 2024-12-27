#include<stdio.h>
#include<string.h>
#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_BORROWS 100 //deal with book as it might have more than 1 copy

typedef struct {
int bID;
int copies;
} Books;

typedef struct {
int mID;
}Members;

typedef struct {
int BookID;
int MemberID;
char borrow_date[11]; //AS DD is 2 char and / is a char and MM is 2 char and / is a char and YYYY is 4 chars
}Borrowed_Books;

int book_count = 0;
int member_count = 0;
int borrow_count = 0;
int n, input_bID,input_mID;

Books b[MAX_BOOKS];
Members m[MAX_MEMBERS];
Borrowed_Books bb[MAX_BORROWS];

//Book ID is guaranteed to be no longer than 3 integers.
int validate_book_id(int bookid) {
    if (bookid< 1 || bookid > 999){return 0;}
    return 1;}
//Valid copies to be not equal to zero
int valid_book_copies(int bookcopy){
    if (bookcopy<0){return 0;}
    return 1;}
//Member ID is guaranteed to be no longer than 6 integers.
int validate_member_id(int memberid) {
    if (memberid< 1 || memberid > 999999){return 0;}
    return 1;}
//Date is in the format day/month/year
int validate_date (char *date){
    int day, month, year;
    if (sscanf(date, "%2d/%2d/%4d", &day, &month, &year) != 3) {
    return 0;}
    if (day < 1 || day > 31) {
    return 0;}
    if (month < 1 || month > 12) {
    return 0;}
    return 1;}
// Check if the BookID exists in the books array
int is_book_available(int bookid) {
    for (int i = 0; i < book_count; i++){
            if (b[i].bID == bookid) {return 1; // Book found
}}
    return 0; // Book not found
}
// Check if the MemberID exists in the members array
int is_member_valid(int memberid) {
    for (int i = 0; i < member_count; i++) {
            if (m[i].mID == memberid) {return 1; // Member found
}}
    return 0; // Member not found
}
// Count the number of books borrowed by a member
int count_books_borrowed_by_member(int memberid) {
    int count = 0;
    for (int i = 0; i < borrow_count; i++) {
        if (bb[i].MemberID == memberid) {
            count++;}}
    return count;
}
//check if there are remaining copies of this book
int is_copy_available(int bookid) {
    for (int i = 0; i < book_count; i++) {
        if (b[i].bID == bookid && b[i].copies > 0) {
            b[i].copies--;
            return 1;
        }
    }
    return 0;
}

// Functions' Declaration

void number_books();
void number_members();
void book_id_min();
void member_less(int n);
void books_Unborrowed();
void books_per_member();
void overlapping_borrowers(int id);
void books_borrowed_days(Borrowed_Books bb[], int count);

int main ()
{
    char incommand [150];
    printf("-*-*-*-*-*-*-*-*-*-*-*  Welcome to Library Control System   -*-*-*-*-*-*-*-*-*-*-*-*-\n");
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=---=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n\n\n");

    // How to use our program
    printf("Set of instructions for successful Input:\n");
    printf("1. Book info ex: 101 5\n");
    printf("2. Member command upper or lower case\n");
    printf("3. Member info ex: 205000\n");
    printf("4. Borrowed_Books command upper or lower case\n");
    printf("5. Borrowed books info ex: 101 205000 31/12/2024\n");
    printf("--------------------------------------------------\n\n");
    printf("Set of instructions for successful usage:\n");
    printf("1. Write Number_Books to get the results\n");
    printf("2. Write Number_Members to get the results\n");
    printf("3. Write Book_ID_Min to get the results\n");
    printf("4. Write Books_Available to get the results\n");
    printf("5. Write List_Book_Borrowers to get the results\n");
    printf("6. Write List_Member_Books to get the results\n");
    printf("7. Write Most_Borrowed to get the results\n");
    printf("8. Write Members_Less n to get the results\n");
    printf("9. Write Books_Unborrowed to get the results\n");
    printf("10. Write Books_Per_Member to get the results\n");
    printf("11. Write Overlapping_Borrowers to get the results\n");
    printf("12. Write Quit to end\n");
    printf("--------------------------------------------------\n\n");

    //Starting point of input format
    printf("Books:\n");

    //Input books available with ID & copies
    fgets(incommand, sizeof(incommand), stdin);
    while (strcmp(incommand, "members:\n") != 0 && strcmp(incommand, "Members:\n") != 0) {
    if (book_count < MAX_BOOKS){
        if (sscanf(incommand, "%d %d", &b[book_count].bID, &b[book_count].copies) == 2) {
            if (validate_book_id(b[book_count].bID) && (valid_book_copies(b[book_count].copies))){
                                        book_count++;}
            else{
                printf("Invalid book ID format. Reminder: Book ID should be up to 3 positive digits and copies mote than or equal 0\n");}}
        else{
            printf("Invalid book input format which is expected to be [ID copies]\n");}}
    else{
        printf("Maximum number of books reached\n");}
        fgets(incommand, sizeof(incommand), stdin);
                                                                                         }
    //Input Members IDs
    //Input Members IDs
    fgets(incommand, sizeof(incommand), stdin);
    while (strcmp(incommand, "Borrowed_Books:\n") != 0 && strcmp(incommand, "borrowed_books:\n") != 0) {
    if (member_count < MAX_MEMBERS){
        if (sscanf(incommand, "%d", &m[member_count].mID) == 1){
            if (validate_member_id(m[member_count].mID)){
                                        member_count++; }
            else{
                printf("Invalid Member ID format. Reminder: Member ID should be up to 6 postitive digits\n");}}
        else{
            printf("Invalid member input format which is expected to be [MEMBER ID]\n");}}
    else{
        printf("Maximum number of members reached\n");}
        fgets(incommand, sizeof(incommand), stdin);
                                                                                                       }
    //Input Borrowed Books Data\
    // infinite loop having 3 scenarios which are: 1- no borrowed books 2- EOF to start operations 3- still reading
    while (1){
    if (fgets(incommand, sizeof(incommand), stdin) == NULL){
            break;}
        if (strcmp(incommand, "<EOF>\n") == 0){
            break;}
        if (borrow_count < MAX_BORROWS){
            if (sscanf(incommand, "%d %d %10s", &bb[borrow_count].BookID, &bb[borrow_count].MemberID, bb[borrow_count].borrow_date) == 3){
                if (!is_book_available(bb[borrow_count].BookID)) {
                    printf("Invalid BookID: Book not found in the library.\n");
                    continue;}
                        if (!is_member_valid(bb[borrow_count].MemberID)) {
                          printf("Invalid MemberID: Member not found.\n");
                            continue;}
                              if (count_books_borrowed_by_member(bb[borrow_count].MemberID) > 5){
                                printf("Member %d has already borrowed 5 books. Cannot borrow more.\n", bb[borrow_count].MemberID);
                              continue;}
                              if (!is_copy_available(bb[borrow_count].BookID)) {
                                printf("No copies available for BookID %d.\n", bb[borrow_count].BookID);
                            continue;}
                            if (validate_date(bb[borrow_count].borrow_date)) {
                                borrow_count++;}
                            else {
                        printf("Invalid borrow date format. Reminder: Date should be in the form [DD/MM/YYYY]\n");}}
                    else {
                printf("Invalid borrowed book format which is expected to be [book_id member_id borrow_date]\n");}}
            else {
            printf("Maximum number of borrowed books reached\n");}
          }


      // Validation of the output operations

       while (1){

    fgets(incommand, sizeof(incommand), stdin);
    incommand[strcspn(incommand, "\n")] = 0;
    if (strcmp(incommand, "Quit") == 0) {
            printf("Thanks!\n");
            break; // End the program
    }
    else if (strcmp(incommand, "Number_Books") == 0 || strcmp(incommand, "Number_Books:") == 0 || strcmp(incommand, "number_books:") == 0 || strcmp(incommand, "number_books") == 0) {
            number_books();
    }
    else if (strcmp(incommand, "Number_Members") == 0 || strcmp(incommand, "Number_Members:") == 0 || strcmp(incommand, "number_members:") == 0 || strcmp(incommand, "number_members") == 0) {
            number_members();
    }
    else if (strcmp(incommand, "Book_ID_Min") == 0 || strcmp(incommand, "Book_ID_Min:") == 0 || strcmp(incommand, "book_id_min:") == 0 || strcmp(incommand, "book_id_min") == 0) {
            book_id_min();
    }
    else if (strcmp(incommand, "Books_Available") == 0 || strcmp(incommand, "Books_Available:") == 0 || strcmp(incommand, "books_available") == 0 || strcmp(incommand, "books_available:") == 0) {
             Books_Available();
     }
    else if (sscanf(incommand, "List_Book_Borrowers %d", &input_bID) == 1 || sscanf(incommand, "List_Book_Borrowers %d:", &input_bID) == 1 || sscanf(incommand, "list_book_borrowers %d", &input_bID) == 1 || sscanf(incommand, "list_book_borrowers %d:", &input_bID) == 1) {
            List_Book_Borrowers_ID(input_bID);
    }
    else if (sscanf(incommand, "List_Member_Books %d", &input_mID) == 1 || sscanf(incommand, "List_Member_Books %d:", &input_mID) == 1 || sscanf(incommand, "list_member_books %d", &input_mID) == 1 || sscanf(incommand, "list_member_books %d:", &input_mID) == 1) {
          List_Member_Books_ID(input_mID);
    }
    else if (strcmp(incommand, "Most_Borrowed") == 0 || strcmp(incommand, "Most_Borrowed:") == 0 || strcmp(incommand, "most_borrowed") == 0 || strcmp(incommand, "most_borrowed:") == 0) {
        Most_Borrowed();
    }
    else if (sscanf(incommand, "Members_Less %d", &n) == 1 || sscanf(incommand, "Member_Less %d:", &n) == 1  || sscanf(incommand, "member_less %d:", &n) == 1 || sscanf(incommand, "member_less %d", &n) == 1) {
            member_less(n);
    }
    else if (strcmp(incommand, "Books_Unborrowed") == 0 || strcmp(incommand, "Books_Unborrowed:") == 0 || strcmp(incommand, "books_unborrowed:") == 0 || strcmp(incommand, "books_unborrowed") == 0) {
            books_unborrowed();
    }
    else if (strcmp(incommand, "Books_Borrowed_Days") == 0 || strcmp(incommand, "Books_Borrowed_Days:") == 0 || strcmp(incommand, "books_borrowed_days:") == 0 || strcmp(incommand, "books_borrowed_days") == 0) {
            books_borrowed_days(bb, borrow_count);
    }
    else if (strcmp(incommand, "Books_Per_Member") == 0 || strcmp(incommand, "Books_Per_Member:") == 0 || strcmp(incommand, "books_per_member:") == 0 || strcmp(incommand, "books_per_member") == 0) {
            books_per_member();
    }
    else if (sscanf(incommand, "Overlapping_Borrowers %d", &input_bID) == 1 || sscanf(incommand, "Overlapping_Borrowers %d:", &input_bID) == 1 || sscanf(incommand, "overlapping_borrowers %d", &input_bID) == 1 || sscanf(incommand, "overlapping_borrowers %d", &input_bID) == 1) {
            overlapping_borrowers(input_bID);
    }
    else {
        printf("ERROR\n");
    }
                }
        return 0;
}


// Functions Definition

// Print the total number of books in the library.
void number_books(){
    int sumBooks = 0;
    for (int i = 0; i < book_count ; i++){
        sumBooks += b[i].copies;
    }
    printf("%d\n",sumBooks);
return;
}

// Print the total number of library members.
void number_members(){
    printf("%d\n",member_count);
return;
}

// Print the minimum book ID.
void book_id_min(){
    int smallest = b[0].bID;
    for (int i = 1; i < book_count; i++){
        if (smallest > b[i].bID){
            smallest = b[i].bID;
        }
    }
    printf("%d\n",smallest);
return;
}

// List all books with at least one available copy.
void Books_Available() {
    int available = 0;
    for (int i = 0; i < book_count; i++) {
        if (b[i].copies > 0) {
            printf("%d\n", b[i].bID);
            available = 1;
        }
    }
    if (!available) {
        printf("None\n");
    }
}


// List Book Borrowers ID function
void List_Book_Borrowers_ID(int book_id) {

    int found = 0;
    for (int i = 0; i < borrow_count; i++) {
        if (bb[i].BookID == book_id) {
            printf("%d\n", bb[i].MemberID);
            found = 1;
        }
    }
    if (!found) {
        printf("None\n");
    }
}


// List Member Books ID function
void List_Member_Books_ID(int member_id) {

    int exist = 0;
    for (int i = 0; i < borrow_count; i++) {
        if (bb[i].MemberID == member_id) {
            printf("%d\n", bb[i].BookID);
            exist = 1;
        }
    }
    if (!exist) {
        printf("None\n");
    }
}

// List the book ID(s) with the highest borrowing frequency.
void Most_Borrowed() {

    int borrow_counts[MAX_BOOKS] = {0};
    for (int i = 0; i < borrow_count; i++) {
        for (int j = 0; j < book_count; j++) {
            if (bb[i].BookID == b[j].bID) {
                borrow_counts[j]++;
            }
        }
    }

    int max_borrowed = 0;
    for (int i = 0; i < book_count; i++) {
        if (borrow_counts[i] > max_borrowed) {
            max_borrowed = borrow_counts[i];
        }
    }

    if (max_borrowed == 0) {
        printf("None\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (borrow_counts[i] == max_borrowed) {
            printf("%d\n", b[i].bID);
            found = 1;
        }
    }
    if (!found) {
        printf("None\n");
    }
}

// List members who borrowed fewer than n books.
void member_less(int n) {
    int borrowCountArr[MAX_MEMBERS] = {0};
    int available = 0;
    for (int i = 0; i < borrow_count; i++) {
        int memberID = bb[i].MemberID;
        for (int j = 0; j < member_count; j++) {
            if (m[j].mID == memberID) {
                borrowCountArr[j]++;
                break;
            }
        }
    }
    for (int i = 0; i < member_count; i++) {
        if (borrowCountArr[i] < n) {
            printf("%d\n", m[i].mID);
            available = 1;
        }
    }
    if (!available) {
        printf("None\n");
    }
    return;
}


// List all book IDs that have not been borrowed by any member.
void books_unborrowed() {
    int unborrowed[MAX_BOOKS];
    int unborrowed_count = 0;

    for (int i = 0; i < book_count; i++) {
        int is_borrowed = 0;

        for (int j = 0; j < borrow_count; j++) {
            if (b[i].bID == bb[j].BookID) {
                is_borrowed = 1;
                break;
            }
        }

        if (!is_borrowed) {
            unborrowed[unborrowed_count++] = b[i].bID;
        }
    }

    if (unborrowed_count == 0) {
        printf("All books are borrowed.\n");
    } else {
        for (int i = 0; i < unborrowed_count; i++) {
            printf("%d\n", unborrowed[i]);
        }
    }
    return;
}

// Calculate the total number of unique days during which books were borrowed.
void books_borrowed_days(Borrowed_Books bb[], int count) {
    int unique_count = 0;

    for (int i = 0; i < count; i++) {
        int is_unique = 1;

        for (int j = 0; j < count; j++) {
            if (i != j && strcmp(bb[i].borrow_date, bb[j].borrow_date) == 0) {
                is_unique = 0;
                break;
            }
        }

        if (is_unique) {
            unique_count++;
        }
    }

    printf("%d\n", unique_count);
    return;
}


// List all members along with the count of books each has borrowed.
void books_per_member() {
    int borrow_counts[MAX_MEMBERS] = {0};

    for (int i = 0; i < borrow_count; i++) {
        for (int j = 0; j < member_count; j++) {
            if (bb[i].MemberID == m[j].mID) {
                borrow_counts[j]++;
                break;
            }
        }
    }

    for (int i = 0; i < member_count; i++) {
        printf("%3d %4d\n", m[i].mID, borrow_counts[i]);
    }
    return;
}


// Given a book ID, the function will list all member IDs who borrowed the same book on the same day
void overlapping_borrowers(int id) {
    int has_overlaps = 0;
    for (int i = 0; i < borrow_count; i++) {
        if (bb[i].BookID == id) {
            int overlap_found = 0;

            for (int k = 0; k < i; k++) {
                if (bb[k].BookID == id && strcmp(bb[k].borrow_date, bb[i].borrow_date) == 0) {
                    overlap_found = 1;
                    break;
                }
            }

            if (!overlap_found) {
                int count = 0;

                for (int j = 0; j < borrow_count; j++) {
                    if (bb[j].BookID == id && strcmp(bb[j].borrow_date, bb[i].borrow_date) == 0) {
                        count++;
                    }
                }

                if (count > 1) {

                    for (int j = 0; j < borrow_count; j++) {
                        if (bb[j].BookID == id && strcmp(bb[j].borrow_date, bb[i].borrow_date) == 0) {
                            printf("%d\n", bb[j].MemberID);
                        }
                    }

                    printf("\n");
                    has_overlaps = 1;
                }
            }
        }
    }

    if (!has_overlaps) {
        printf("None\n");
    }

    return;
}
