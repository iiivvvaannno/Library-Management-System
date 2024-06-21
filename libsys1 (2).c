#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // used for usleep function
#include <time.h>

//BOLD WHITE 
#define BOLD "\033[1m" 
#define RESET "\033[0m"

//BOLD GREEN 
#define GREEN "\x1b[1;32m"
#define FORMAT "\x1b[0m"


#define MAX_LINES 1500
#define MAX_LENGTH 400


//Void Funtion Declarations {
void loadingAnimation(); 
void bookID();                           // Mark
void addBooks();                         // Mark
void viewBooks();                        // Dominic
void borrowBooks();                      // Ivan 
void borrowedList();                     // Dominic
void edit();                             // Shawnlee
void editFile(const char *filename);     // Shawnlee
void editBooks(const char *filename);    // James 
void editBorrowed(const char *filename); // Reinwel

//typedef struct 
struct Books {
    int ID;
    char bookName[50];
    char authorName[50];
    char date[11];
} B;

struct Students{
    long int ID;
    int bookID;
    char studentName[50];
    char program[50];
    char bookName[50];
    char authorName[50];
    char status[10];
} S;

int choice;
int editNum;


FILE *fp, *file; //Allowing for file creation 

int main() 
{
    int choices;

    do {
        printf("\e[1;1H\e[2J"); // clear screen
    
        printf("\n\n");
        printf(BOLD "\t   |[=======================================================]|\n" RESET);
        printf(BOLD "\t   ||              "GREEN"WELCOME TO BOOKLY RECORDS"FORMAT"                ||\n" RESET);
        printf(BOLD "\t   |[=======================================================]|\n\n" RESET);


        printf(BOLD"\t      MAIN MENU \n" RESET);
        printf("\t      |[===============================================]|\n");
        printf("\t      ||  %sOPTION%s        |      %sDESCRIPTION%s             ||\n",GREEN,RESET,GREEN,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s1%s           |      %sADD BOOKS%s               ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s2%s           |      %sVIEW BOOKS LIST%s         ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s3%s           |      %sBORROW BOOKS%s            ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s4%s           |      %sBORROWED BOOKS LIST%s     ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s5%s           |      %sEDIT LIST%s               ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      ||----------------+------------------------------||\n");
        printf("\t      ||    %s0%s           |      %sEXIT PROGRAM%s            ||\n",BOLD, RESET,BOLD,RESET);
        printf("\t      |[===============================================]|\n");
    

        printf("\n\n\n\t\tEnter your choice here >> ");
        scanf(" %d", &choices);
    
        getchar();// Consume the newline character in the buffer
    
        switch (choices) {
            case 0:
                printf("\e[1;1H\e[2J"); // clear screen
                loadingAnimation();
    
                printf("\e[1;1H\e[2J"); // clear screen
                printf("\n");
                printf(BOLD "\t    ================================================\n" RESET);
                printf(BOLD "\t    ||    %sTHANK YOU FOR USING BOOKLY RECORDS!%s     ||\n" RESET,GREEN, RESET);
                printf(BOLD "\t    ================================================\n\n" RESET);                
                break;
    
            case 1:
                addBooks();
                break;
    
            case 2:
                viewBooks();
                break;
    
            case 3:
                borrowBooks();
                break;
    
            case 4:
                borrowedList();
                break;

            case 5: 
                edit();
                break;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }  
    
        if (choices != 0) {
            printf("\n\n\tPress Enter to Continue...");
            getchar(); // Wait for the user to press Enter
        }
        
    }
    while(choices != 0);

    return 0;
}
  
//  [================== VOID FUNCTIONS ====================]

void loadingAnimation() {
    printf(" "); // Use puts for simple string output
    printf(BOLD "\n\t  =====================================\n" RESET);
    printf("\t\tExiting the Program... ");
        for (int i = 0; i < 30; ++i) {
            printf("\b|");
            fflush(stdout); // basically overwrites the line for the output
            usleep(100000);

            printf("\b/");
            fflush(stdout);
            usleep(100000);

            printf("\b-");
            fflush(stdout);
            usleep(100000);

            printf("\b\\");
            fflush(stdout);
            usleep(100000);
        }
}

void bookID(){
    // Read the last used Book ID from a file
    int lastBookID = 0;                       //initializes a var lastBookID to 0 
    FILE *idFile;

    idFile = fopen("book_id.txt", "r");       //creates book_id in read mode 
    if (idFile != NULL)                       // condition where it checks if the file is successfully opened.
    {
        fscanf(idFile, "%d", &lastBookID);    //reads the file and gets the lastBookId value from the file 
        fclose(idFile);
    }

    B.ID = lastBookID + 1;                    //struct Book, B.ID stores the lastBookID + 1;

    // Update the stored Book ID
    idFile = fopen("book_id.txt", "w");      //creates bookID in write mode
    if (idFile != NULL) {
        fprintf(idFile, "%d", B.ID);         //prints B.ID = 1 immediately in the bookId file 
        fclose(idFile);
    }

}

void addBooks() {
    bookID();                      //checks the last Book ID

    fp = fopen("books.txt", "a");  // "a" - for appending / updating the data in books.txt

    if (fp == NULL) {
        printf("\e[1;1H\e[2J"); // clear screen
        printf("\n   |[===========================================================================================================================================]|n\n");    
        printf(BOLD "\t\nERROR OPENING THE FILE!\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");        
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Check if the file is empty, if yes, write the header
    fseek(fp, 0, SEEK_END); // Move to the end of the file
        if (ftell(fp) == 0) {  // Check the position, if it's 0, the file is empty, then proceeds to printing 
            fprintf(fp, "\t%-15s%-60s%-40s%-15s\n", "Book ID", "Book Name", "Author Name", "Date Added");
        }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file


    printf(GREEN "\n\n\t\t===================[ ADD BOOKS ]===================\n" FORMAT);


    printf(BOLD "\n\t\t  Enter Book Name: " RESET); //Displays a formatted prompt asking the user to enter a book name.
    fgets(B.bookName, 50, stdin);                   //Reads the user's input from the keyboard and stores it in the B.bookName array.
    B.bookName[strcspn(B.bookName, "\n")] = '\0';   //Cleans up the user input by removing any trailing newline character to ensure proper handling of the book title string.

    printf(BOLD "\n\t\t  Enter Author Name: " RESET);
    fgets(B.authorName, 50, stdin);
    B.authorName[strcspn(B.authorName, "\n")] = '\0';

    // Generate current date and time
    time_t t;                        //declares a variable t of type time_t (represents time in seconds since the epoch)
    struct tm *now;                  //declares a struct tm (in time.h, stores dates in yr, mo, day, hr, min, sec, etc) | *now holds the memory address of struct tm 
    time(&t);                        //accesses the time function, and retrieves current calendar time and stores it in varible t 
    now = localtime(&t);             // The localtime function takes a pointer to a time_t value (in this case, the address of t) and converts it to a broken down calendar date and time representation stored in a tm structure. 
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now); 

    fprintf(fp, "\t%-15d%-60s%-40s%-15s\n", B.ID, B.bookName, B.authorName, B.date);

    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\t\t\t     BOOK ADDED SUCESSFULLY!! \n" FORMAT);
    printf("\t\t   ============================================== \n");

    fclose(fp); // Closes the file
}

void viewBooks() {
    char line[300]; // Assuming a maximum of 300 characters per line

    fp = fopen("books.txt", "r"); // "r" for reading

    if (fp == NULL) 
    {
        printf("\e[1;1H\e[2J"); // clear screen
        printf("\n   |[===========================================================================================================================================]|n\n");    
        printf(BOLD "\tERROR OPENING THE FILE!\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Checks if the file is empty. if yes, print a message
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {               
        printf("   |[===========================================================================================================================================]|n\n");
        printf(BOLD "\n\t\t\t\t No books available.\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");
    } 
    else 
    {
        // Move the file pointer to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        printf(GREEN "\n[VIEW BOOKS LIST]\n" FORMAT);
        // Print a separator line
                 
        printf(" |[===========================================================================================================================================]|\n\n");

        // Read and print each line until the end of the file
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf(BOLD "%s" RESET, line);
        }
        

      printf("\n |[===========================================================================================================================================]|\n");
    }
    fclose(fp); // Close the file
}

void borrowBooks() {
    FILE *fp;

    printf("\e[1;1H\e[2J"); // clear screen

    fp = fopen("borrow.txt", "a");

    if (fp == NULL) {
        printf("   |[===========================================================================================================================================]|n\n");
        printf(BOLD "\n\t\t\t\t Error opening the file .\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");
        return;
    }

    fseek(fp, 0, SEEK_END); // Move to the end of the file
    if (ftell(fp) == 0) {
        // Check the position, if it's 0, the file is empty
        fprintf(fp, " %-20s%-35s%-35s%-10s%-35s%-13s%-15s%-10s\n", "Student ID[06-]", "Student Name", "Program", "Book ID", "Book Name", "Date Lent", "Return Date", "Status");
    }
    fseek(fp, 0, SEEK_SET); // Move back to the beginning of the file

    // Generate current date and time
    time_t t;                        //declares a variable t of type time_t (represents time in seconds since the epoch)
    struct tm *now;                  //declares a struct tm (in time.h, stores dates in yr, mo, day, hr, min, sec, etc) | *now holds the memory address of struct tm 
    time(&t);                        //accesses the time function, and retrieves current calendar time and stores it in varible t 
    now = localtime(&t);             // The localtime function takes a pointer to a time_t value (in this case, the address of t) and converts it to a broken down calendar date and time representation stored in a tm structure. 
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now); 

    printf(GREEN "\n\n\t\t===========================[ BOOK LENDING ]===========================\n" FORMAT);

    printf("\n\t\t Fatima Student ID (06-): ");
    scanf("%ld", &S.ID);
    getchar();

    printf("\n\t\t Enter Student Name: ");
    fgets(S.studentName, 50, stdin);
    S.studentName[strcspn(S.studentName, "\n")] = '\0';

    printf("\n\t\t Enter Program (e.g.; BS Computer Science): ");
    fgets(S.program, 50, stdin);
    S.program[strcspn(S.program, "\n")] = '\0';

    printf("\e[1;1H\e[2J"); // clear screen
    viewBooks(); // reference for viewing the booklist 

    printf("\n\t\t Enter Book ID: ");
    scanf("%d", &S.bookID);
    getchar(); // Consume the newline character

    printf("\n\t\t Enter Book Name: ");
    fgets(S.bookName, 50, stdin);
    S.bookName[strcspn(S.bookName, "\n")] = '\0';

    strcpy(S.status, "Borrowed"); // Use strcpy to assign the string "Borrowed" to S.status
    printf("\n\t\t Status: %s", S.status);

    // Assuming the return date is one week from the borrow date
    struct tm returnDate;               // declares a var returnDate of a struct tm
    returnDate = *now;                  // returnDate has the same data *now [refer to line 304] has 
    returnDate.tm_mday += 7;            // in returnDate in tm_day increments by 7 days.
    mktime(&returnDate);                // the function takes a pointer to struct tm; function: attempts to convert broken time componets to values
    char returnDateString[11];          // declares a var of returnDateString that stores 11 characters, stores formatted date strings
    strftime(returnDateString, sizeof(returnDateString), "%m-%d-%Y", &returnDate);
    //strftime function. This function formats a time value according to a specified format string
    //strftime(destination, (calculates if the variable has enough storage(sizeof())), desired format, source  )

    fprintf(fp, " %-20ld%-35s%-35s%-10d%-35s%-13s%-15s%-10s\n", S.ID, S.studentName , S.program, S.bookID, S.bookName, B.date , returnDateString, S.status);

    sleep(2);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION ADDED SUCCESSFULLY!! \n" FORMAT);
    printf("\n\t\t ================================================= ");


    fclose(fp); // Closes the file
}

void borrowedList(){ 
    char line[300]; // Assuming a maximum of 300 characters per line

    fp = fopen("borrow.txt", "r"); // "r" for reading

    if (fp == NULL) 
    {
        printf("\e[1;1H\e[2J"); // clear screen
        printf("   |[===========================================================================================================================================]|n\n");
        printf(BOLD "\n\t\t\t\t Error opening the file .\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");
        return;
    }

    printf("\e[1;1H\e[2J"); // clear screen

    // Check if the file is empty, if yes, print a message
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        printf("   |[===========================================================================================================================================]|n\n");
        printf(BOLD "\n\t\t\t\t No data available.\n" RESET);
        printf("\n   |[===========================================================================================================================================]|n");
    } 
    else 
    {
        // Move the file pointer to the beginning of the file
        fseek(fp, 0, SEEK_SET);

        printf(GREEN "\n[ LENDING INFORMATION ]\n" FORMAT);

        // Print a separator line
        printf(" ========================================================================================================================================================================\n");
 
        // Read and print each line until the end of the file
        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s", line);
        }

        printf("\n ======================================================================================================================================================================\n");
    }
    fclose(fp); // Close the file
}

void edit(){
    start: 
    printf("\e[1;1H\e[2J"); // clear screen
    printf("\n\t   |[===================================================]|");
    printf("\n\t   || SELECT A FILE TO EDIT                             ||"); //prompts to user to select a file to edit 
    printf("\n\t   |[===================================================]|");
    printf("\n\t   || 1. books.txt                                      ||"); //prompts to user to select a file to edit 
    printf("\n\t   |[===================================================]|");
    printf("\n\t   || 2. borrow.txt                                     ||"); //prompts to user to select a file to edit 
    printf("\n\t   |[===================================================]|\n");      
   
    printf("\n\t   Enter your Choice >> ");
    scanf("%d", &editNum);
    getchar();

    if (editNum == 1) {
        editFile("books.txt");
    } 
    else if (editNum == 2){
        editFile("borrow.txt");
    }
    else{
        goto start;
    }
}

/**/void editFile(const char *filename) // editFile works through passing by ptr
{
    printf("\e[1;1H\e[2J"); // clear screen

    char lines[MAX_LINES][MAX_LENGTH];
    int lineCount = 0;

    // Open file for reading
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("   |[===========================================================================================================================================]|\n");
        printf(BOLD "\n\t\t\t\t Error opening the file .\n" RESET);
        printf("\n   |[===========================================================================================================================================]|");        
        return;
    }

    // Read file content into memory
    //while the line per row in the filename still has value, fgets will fetch all the data [MAX LENGTH = all characters in one line] and stores it in char line
    //if the condition detects that the line has no more data the loop will then be terminated and the file will close 
    //linecount here is used for counter 
    while (fgets(lines[lineCount], MAX_LENGTH, file) != NULL) 
    {
        lineCount++;
    }
    fclose(file);

    // Display file content with line numbers
    printf("\nContents of %s:\n", filename);
    for (int i = 0; i < lineCount; i++) {
        printf("[%d] %s", i, lines[i]); //prints all the data (char) stored in the lines array and prints the line per row in i = 1 
    }

    // Ask user for line to edit
    printf("\nEnter the line number to edit (0 to cancel): ");
    scanf("%d", &choice);
    getchar(); // Consume newline character

    if (choice == 0 || choice > lineCount) {
        printf("Invalid choice or line number.\n");
        return;
    } //handles error in choice input

    if (filename == "books.txt"){
        editBooks("books.txt");
    }

    if (filename == "borrow.txt") {
        editBorrowed("borrow.txt");
    }
    
    fclose(file);

    printf("File %s updated successfully.\n", filename);
}

/**//**/void editBooks(const char *filename)
{
    printf("\e[1;1H\e[2J"); // clear screen

    char line[MAX_LINES];
    char lineNumber = 0;
    long position;

    file = fopen(filename, "rw+"); //open the file in read and write+ 

    printf(BOLD "\n\t\t  Enter Book ID:  " RESET);    
    //    printf(BOLD "\n\t\t  Enter Book ID: %d " RESET, B.ID);    
    scanf("%d", &B.ID);
    getchar();

    printf(BOLD "\n\t\t  Enter Book Name: " RESET);
    fgets(B.bookName, 50, stdin);
    B.bookName[strcspn(B.bookName, "\n")] = '\0';

    printf(BOLD "\t\t  Enter Author Name: " RESET);
    fgets(B.authorName, 50, stdin);
    B.authorName[strcspn(B.authorName, "\n")] = '\0';

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);
    //can be deleted 

    
    while (fgets(line, sizeof(line), file)) 
    {
        if (choice == lineNumber) {
            position = ftell(file); // Save the current offset/position 
            
            // Edit the line (replace "author me" with "new author")
            fseek(file, position - strlen(line), SEEK_SET); // <-- Moving file pointer to beginning of line
            fprintf(file, "\t%-15d%-60s%-40s%-15s\n", B.ID, B.bookName, B.authorName, B.date);
        }
        lineNumber++;
    }
    // scans the char line and gets the size of line in the file
    //check if the choice and linenumber in the file is the same
        // No - continues the loop until it becomes equal
        // Yes - position saves the current position of the pointer base on the ftell(file). ftell moves it pointer at the end of the data in line right after \n   
            // - position - strlen(line), moves the pointer from the end to start of the line.
            // - prints the edited data accordingly
    
    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION MODIFIED SUCCESSFULLY!! \n" FORMAT);
    printf("\n\t\t  =============================================== ");


}

/**//**/void editBorrowed(const char *filename){
   
    printf("\e[1;1H\e[2J"); // clear screen

    char line[MAX_LINES];
    char lineNumber = 0;
    long position;
    
    file = fopen(filename, "rw+");

    // Generate current date and time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);
    strftime(B.date, sizeof(B.date), "%m-%d-%Y", now);
    //can be deleted

    printf("\n\t\t Fatima Student ID (06-): ");
    scanf("%ld", &S.ID);
    getchar();

    printf("\n\t\t Enter Student Name: ");
    fgets(S.studentName, 50, stdin);
    S.studentName[strcspn(S.studentName, "\n")] = '\0';

    printf("\n\t\t Enter Program (e.g.; BS Computer Science): ");
    fgets(S.program, 50, stdin);
    S.program[strcspn(S.program, "\n")] = '\0';

    printf("\n\t\t Enter Book ID: ");
    scanf("%d", &S.bookID);
    getchar(); // Consume the newline character

    printf("\n\t\t Enter Book Name: ");
    fgets(S.bookName, 50, stdin);
    S.bookName[strcspn(S.bookName, "\n")] = '\0';

    printf("\n\n\n\t Status: ");
    scanf("%s", S.status);

    // Assuming the return date is one week from the borrow date
    struct tm returnDate;
    returnDate = *now;
    returnDate.tm_mday += 7;
    mktime(&returnDate);
    char returnDateString[11];
    strftime(returnDateString, sizeof(returnDateString), "%m-%d-%Y", &returnDate);
    //can be deleted

     while (fgets(line, sizeof(line), file)) {
        if (choice == lineNumber) {
            position = ftell(file); // Save the current offset / position
            
            fseek(file, position - strlen(line), SEEK_SET); // <-- Moving file pointer to beginning of line
            fprintf(file, " %-20ld%-35s%-35s%-10d%-35s%-13s%-15s%-10s\n", S.ID, S.studentName , S.program, S.bookID, S.bookName, B.date ,returnDateString, S.status);
        }
        lineNumber++;
    }
    // scans the char line and gets the size of line in the file
    //check if the choice and linenumber in the file is the same
        // No - continues the loop until it becomes equal
        // Yes - position saves the current position of the pointer base on the ftell(file). ftell moves it pointer at the end of the data in line right after \n   
            // - position - strlen(line), moves the pointer from the end to start of the line.
            // - prints the edited data accordingly
    sleep(1);

    printf("\n\t\t==================================================== ");
    printf(GREEN "\n\n\t\t\t  INFORMATION MODIFIED SUCCESSFULLY!! \n" FORMAT);
    printf("\n\t\t  =============================================== ");


}