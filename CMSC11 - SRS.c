//CMSC Student Register System
#include<stdio.h>
#include<stdlib.h>


struct subjectSystem{
    int SubID;
    char SubCode[20];
    char title[50];
};

struct studentSystem{
    int studentID;
    char firstName[50];
    char lastName[50];
    char lecSection[10];
    int hex[3];
    struct subjectSystem *enrolled[3];
    int total;
    char grade[5];
};

struct statisticSystem{
    int lowest[4];
    int highest[4];
    double avg[4];
    double std[4];
};

struct studentSystem CMSC11[1000] = {0};
struct subjectSystem in[100] = {11, "CMSC11", "Introduction to Computer Science"};
struct subjectSystem emp = {0, "None", "None"};
struct statisticSystem data;

static int read = 0;
static int read2 = 0;

void StudentRecord(struct studentSystem *CMSC11, struct subjectSystem *in);
void CreateStudentRecord(struct studentSystem *CMSC11);
void ReadFromFileStudent(struct studentSystem *CMSC11);
void CreateNewStudent(struct studentSystem *CMSC11, struct subjectSystem *in, struct subjectSystem *emp);
void StudentEnrollment(struct studentSystem *CMSC11, int idx);
void SearchStudentRecord(struct studentSystem *CMSC11);
void SearchStudentID(struct studentSystem *CMSC11);
void SearchStudentLastName(struct studentSystem *CMSC11);
void EditStudentRecord(struct studentSystem *CMSC11, int idx);
void DropSubject(struct studentSystem *CMSC11, int idx);
void DisplayStudentSearchedRecord(struct studentSystem *CMSC11, int idx);
void DeleteStudentRecord(struct studentSystem *CMSC11, int idx);
void DisplayStudentRecord(struct studentSystem *CMSC11, struct subjectSystem *in);
void StatisticsRecord(struct studentSystem *CMSC11, struct statisticSystem *data);
void ClearStudentRecord(struct studentSystem *CMSC11);
void ExportStudentRecord(struct studentSystem *CMSC11, struct statisticSystem *data);

void SubjectRecord(struct subjectSystem *in);
void CreateSubjectRecord(struct subjectSystem *in);
void ReadFromFileSubject(struct subjectSystem *in, char a[]);
void CreateNewSubject(struct subjectSystem *in);
void SearchSubjectRecord(struct subjectSystem *in);
void SearchSubjectID(struct subjectSystem *in);
void SearchSubjectCode(struct subjectSystem *in);
void EditSubjectRecord(struct subjectSystem *in, int idx);
void DeleteSubjectRecord(struct subjectSystem *in, int idx);
void DisplaySubjectSearchedRecord(struct subjectSystem *in, int idx);
void DisplaySubjectRecord(struct subjectSystem *in);
void ClearSubjectRecord(struct subjectSystem *in);
void ExportSubjectRecord(struct subjectSystem *in);

int Strcspn(char a[], char b[]);
int ToInteger(char st[]);
int Strcmp(char s1[], char s2[]);

char ToLower(char ch);
char ToUpper(char ch);

void Strcpy(char src[], char dest[]);

double Sqrt(double number);

int main(void){
    int c = 1;
    while (c > 0){
        printf("\n\nWELCOME TO THE UP DEPARTMENT OF COMPUTER SCIENCE DATABASE\n\n");
        printf("Directories:\n");
        printf("\t1. Student Record\t2. Subject Record\t3. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &c);
        fflush(stdin);
        switch (c){
        case 1:
            StudentRecord(CMSC11, in);
            break;

        case 2:
            SubjectRecord(in);
            break;

        default:
            c = 0;
            /* Prompt "Save Changes?" */
            break;
        }
    }

    return 0;
};

void StudentRecord(struct studentSystem *CMSC11, struct subjectSystem *in){
    int cmd = 1;
    while(cmd > 0){
        printf("\n\nDEPARTMENT OF COMPUTER SCIENCE: STUDENT RECORD\n\n");
        printf("Commands:\n");
        printf("\t1. Create a New Student Record\n");
        printf("\t2. Search and Update/Delete an Existing Student Record\n");
        printf("\t3. Display Student Record\n");
        printf("\t4. Clear Student Record\n");
        printf("\t5. Save and Export\n");
        printf("\t0. Exit\n\n\n");
        printf("Choice: ");
        scanf("%d", &cmd);
        fflush(stdin);
        switch (cmd){
        case 1:
            CreateStudentRecord(CMSC11);
            break;

        case 2:
            SearchStudentRecord(CMSC11);
            break;

        case 3:
            DisplayStudentRecord(CMSC11, in);
            break;

        case 4:
            ClearStudentRecord(CMSC11);
            break;

        case 5:
            ExportStudentRecord(CMSC11, &data);
            break;

        default:
            cmd = 0;
            /* Prompt "Student Record Terminated" */
            break;
        }
    }
};

void SubjectRecord(struct subjectSystem *in){
    int choice = 1;
    while(choice > 0){
        printf("\n\nDEPARTMENT OF COMPUTER SCIENCE: SUBJECT RECORD\n\n");
        printf("Commands:\n");
        printf("\t1. Create a New Subject Record\n");
        printf("\t2. Search and Update/Delete an Existing Subject Record\n");
        printf("\t3. Display Subject Record\n");
        printf("\t4. Clear Student Record\n");
        printf("\t5. Save and Export\n");
        printf("\t0. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice){
        case 1:
            CreateSubjectRecord(in);
            break;

        case 2:
            SearchSubjectRecord(in);
            break;

        case 3:
            DisplaySubjectRecord(in);
            break;

        case 4:
            ClearSubjectRecord(in);
            break;

        case 5:
            ExportSubjectRecord(in);
            break;

        default:
            choice = 0;
            /* Prompt "Subject Record Terminated" */
            break;
        }
    }
};

void CreateStudentRecord(struct studentSystem *CMSC11){
    int c2 = 1;
    if(read == 0){
        printf("\n\nCREATING A NEW STUDENT RECORD\n\n");
        printf("Active Commands:\n");
        printf("\t1. Read from File\t2. Create Student Record\t3. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &c2);
        fflush(stdin);
        switch (c2){
        case 1:
            ReadFromFileStudent(CMSC11);
            break;

        case 2:
            CreateNewStudent(CMSC11, in, &emp);
            break;

        default:
            printf("\n\nYou left Create Student Record Page.\n\n");
            c2 = 0;
            break;
        }
        read++;
    }else{
        CreateNewStudent(CMSC11, in, &emp);
    }
};

void ReadFromFileStudent(struct studentSystem *CMSC11){
    char directory[100];
    printf("\n\nREADING FROM FILE\n\n");
    printf("[Note: Use /] Please enter the directory of the file: ");
    fgets(directory, 100, stdin);
    fflush(stdin);
    directory[Strcspn(directory, "\n")] = 0;
    FILE *dataset = fopen(directory, "r");
    char data[10], data1[3][10], data2[3][10];
    int idx = 0, index2, index3, index4, error;
    struct studentSystem temp;
    while (!feof(dataset)){
        fscanf(dataset, "\n%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &data, &CMSC11[idx].firstName, &CMSC11[idx].lastName, &CMSC11[idx].lecSection, &data1[0], &data1[1], &data1[2], &data2[0], &data2[1], &data2[2]);
        CMSC11[idx].studentID = ToInteger(data);
        CMSC11[idx].hex[0] = ToInteger(data1[0]);
        CMSC11[idx].hex[1] = ToInteger(data1[1]);
        CMSC11[idx].hex[2] = ToInteger(data1[2]);
        for (index2 = 0; in[index2].SubID != 0; index2++){
            if (Strcmp(data2[0], in[index2].SubCode) == 0){
                CMSC11[idx].enrolled[0] = &in[index2];
            }
            if (Strcmp(data2[1], in[index2].SubCode) == 0){
                CMSC11[idx].enrolled[1] = &in[index2];
            }
            if (Strcmp(data2[2], in[index2].SubCode) == 0){
                CMSC11[idx].enrolled[2] = &in[index2];
            }
        }
        if (CMSC11[idx].enrolled[0] == NULL){
            CMSC11[idx].enrolled[0] = &in[0];
        }
        if (CMSC11[idx].enrolled[1] == NULL){
            CMSC11[idx].enrolled[1] = &emp;
        }
        if (CMSC11[idx].enrolled[2] == NULL){
            CMSC11[idx].enrolled[2] = &emp;
        }
        CMSC11[idx].total = CMSC11[idx].hex[0] + CMSC11[idx].hex[1] + CMSC11[idx].hex[2];
        if (CMSC11[idx].total >= 135){
            Strcpy("HD", CMSC11[idx].grade);
        }else if (CMSC11[idx].total >= 120 && CMSC11[idx].total < 135){
            Strcpy("D", CMSC11[idx].grade);
        }else if (CMSC11[idx].total >= 100 && CMSC11[idx].total < 120){
            Strcpy("P", CMSC11[idx].grade);
        }else if (CMSC11[idx].total >= 75 && CMSC11[idx].total < 100){
            Strcpy("C", CMSC11[idx].grade);
        }else{
            Strcpy("F", CMSC11[idx].grade);
        }
        for(index4 = 0; index4 < idx; index4++){
            if(Strcmp(CMSC11[idx].lastName, CMSC11[index4].lastName) == -1){
                temp = CMSC11[index4];
                CMSC11[index4] = CMSC11[idx];
                CMSC11[idx] = temp;
            }
        }
        idx++;
    }
    fclose(dataset);
    printf("\n\nFilepath: %s successfully read!\n\n", directory);
};

void CreateNewStudent(struct studentSystem *CMSC11, struct subjectSystem *in, struct subjectSystem *emp){
    int c3 = 1, c4, idx, index2, match;
    struct studentSystem temp;
    if(CMSC11[999].studentID == 0){
        while(c3 > 0 && CMSC11[999].studentID == 0){
            for (idx = 0; idx < 1000; idx++){
                if (CMSC11[idx].studentID == 0){
                    break;
                }
            }
            printf("\n\nCREATING STUDENT RECORD\n\n");
            printf("Basic Information:\n");
            c4 = 1;
            while(c4 > 0){
                printf("\n\tEnter 3-Digit Student ID: ");
                scanf("%d", &CMSC11[idx].studentID);
                fflush(stdin);
                for (index2 = 0; index2 < idx; index2++){
                    if (CMSC11[idx].studentID == CMSC11[index2].studentID){
                        printf("\n\n\tOops! ID already taken. Try another one!\n\n");
                       c4 = 1;
                        break;
                    }else{
                        c4 = 0;
                    }
                }
                if (idx == 0){
                    c4 = 0;
                }
            }
            printf("\n\tEnter First Name: ");
            fgets(CMSC11[idx].firstName, 50, stdin);
            CMSC11[idx].firstName[Strcspn(CMSC11[idx].firstName, "\n")] = 0;
            printf("\n\tEnter Last Name: ");
            fgets(CMSC11[idx].lastName, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lastName[Strcspn(CMSC11[idx].lastName, "\n")] = 0;
            printf("\n\tEnter CMSC11 Section: ");
            fgets(CMSC11[idx].lecSection, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lecSection[Strcspn(CMSC11[idx].lecSection, "\n")] = 0;
            for (index2 = 0; CMSC11[idx].lecSection[index2] != '\0'; index2++){
                CMSC11[idx].lecSection[index2] = ToUpper(CMSC11[idx].lecSection[index2]);
            }
            printf("\n\tEnter Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[idx].hex[0]);
            fflush(stdin);
            printf("\n\tEnter Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[idx].hex[1]);
            fflush(stdin);
            printf("\n\tEnter Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[idx].hex[2]);
            fflush(stdin);
            CMSC11[idx].total = CMSC11[idx].hex[0] + CMSC11[idx].hex[1] + CMSC11[idx].hex[2];
            if (CMSC11[idx].total >= 135){
                Strcpy("HD", CMSC11[idx].grade);
            }else if (CMSC11[idx].total >= 120 && CMSC11[idx].total < 135){
                Strcpy("D", CMSC11[idx].grade);
            }else if (CMSC11[idx].total >= 100 && CMSC11[idx].total < 120){
                Strcpy("P", CMSC11[idx].grade);
            }else if (CMSC11[idx].total >= 75 && CMSC11[idx].total < 100){
                Strcpy("C", CMSC11[idx].grade);
            }else{
                Strcpy("F", CMSC11[idx].grade);
            }
            CMSC11[idx].enrolled[0] = &in[0];
            CMSC11[idx].enrolled[1] = emp;
            CMSC11[idx].enrolled[2] = emp;
            printf("\n\nWould you like to proceed to enrollment?\n\t1. Yes\t2. No\n\n");
            printf("Choice: ");
            scanf("%d", &c4);
            switch (c4){
            case 1:
                StudentEnrollment(CMSC11, idx);
                break;

            default:
                printf("\n\nENROLLMENT REQUEST ABORTED\n\n");
                break;
            }
            printf("Student ID: %d's Basic Information added onto database\n\n", CMSC11[idx].studentID);
            printf("\n\nWould you like to continue to create another student record?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &c3);
            fflush(stdin);
            switch (c3){
            case 1:
                break;

            default:
                c3 = 0;
                break;
            }
            for(index2 = 0; index2 < idx; index2++){
                if(Strcmp(CMSC11[idx].lastName, CMSC11[index2].lastName) == -1){
                    temp = CMSC11[index2];
                    CMSC11[index2] = CMSC11[idx];
                    CMSC11[idx] = temp;
                }
            }
        }
        if (c3 == 0){
            printf("\n\nDone Creating Student Record!\n\n");
        }
    }else{
        printf("\n\nYou cannot create another student record. Student Record is at full capacity!\n\n");
    }
};

void StudentEnrollment(struct studentSystem *CMSC11, int idx){
    int p = 1, index2, subjects, t = 0;
    for(subjects = 0; CMSC11[idx].enrolled[subjects] ->SubID != 0 && subjects < 3; subjects++);
    if (CMSC11[idx].enrolled[2] == &emp || CMSC11[idx].enrolled[1] == &emp){
        while(p > 0){
            printf("\n\nENROLLMENT REQUEST PROCESSING\n\n");
            do{
                DisplaySubjectRecord(in);
                printf("\nSelect Subject ID: ");
                scanf("%d", &p);
                fflush(stdin);
                if (p == CMSC11[idx].enrolled[0] ->SubID || p == CMSC11[idx].enrolled[1] ->SubID || p == CMSC11[idx].enrolled[2] ->SubID){
                    printf("\n\nOops! You are already enrolled in this subject. Choose a different one!\n\n");
                }
            } while (p == CMSC11[idx].enrolled[0] ->SubID || p == CMSC11[idx].enrolled[1] ->SubID || p == CMSC11[idx].enrolled[2] ->SubID);
            for(index2 = 0; in[index2].SubID != p && index2 < 100; index2++);
            if(in[index2].SubID != 0){
                CMSC11[idx].enrolled[subjects] = &in[index2];
            }else{
                do{
                    printf("\n\nID isn't in the database yet. Try Again!\n\n");
                    do{
                        DisplaySubjectRecord(in);
                        printf("Select Subject ID: ");
                        scanf("%d", &p);
                        fflush(stdin);
                        if (p == CMSC11[idx].enrolled[0] ->SubID || p == CMSC11[idx].enrolled[1] ->SubID || p == CMSC11[idx].enrolled[2] ->SubID){
                            printf("\n\nYou are already enrolled in this subject. Choose a different one!\n\n");
                        }
                    } while (p == CMSC11[idx].enrolled[0] ->SubID || p == CMSC11[idx].enrolled[1] ->SubID || p == CMSC11[idx].enrolled[2] ->SubID);
                    for(index2 = 0; in[index2].SubID != p && index2 < 100; index2++);
                    if(in[index2].SubID != 0){
                        CMSC11[idx].enrolled[subjects] = &in[index2];
                    }else{
                        t++;
                    }
                    if (t == 3){
                        p = 0;
                        break;
                    }
                } while (CMSC11[idx].enrolled[subjects] == &emp);
            }
            if(CMSC11[idx].enrolled[2] == &emp&& t < 3){
                printf("\n\nWould you like to enroll to other subjects?\n\t1. Yes\t2. No\n\n");
                printf("Select: ");
                scanf("%d", &p);
                switch (p){
                case 1:
                    subjects++;
                    break;

                default:
                    p = 0;
                    break;
                }
            }else{
                p = 0;
            }
        }
        if (p == 0){
            if (t == 3){
                printf("\n\nEnrollment Request Disapproved\n\n");
            }else{
                printf("\n\nEnrollment Request Approved\n\n");
            }
        }
    }else{
        printf(" You have already enrolled in 3 subjects.\n\n");
    }
};

void SearchStudentRecord(struct studentSystem *CMSC11){
    int p1 = 1;
    if(CMSC11[0].studentID != 0){
        while(p1 > 0){
            printf("\n\nSEARCHING FOR STUDENT INFROMATION IN STUDENT RECORD\n\n");
            printf("Active Commands:\n\t1. Search by Student ID\t\t2. Search by Student's Last Name\t\t3. Exit\n\n");
            printf("Choicet: ");
            scanf("%d", &p1);
            fflush(stdin);
            switch (p1){
            case 1:
                SearchStudentID(CMSC11);
                break;

            case 2:
                SearchStudentLastName(CMSC11);
                break;

            default:
                break;
            }
            printf("\n\nWould you like to do another search?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &p1);
            fflush(stdin);
            switch (p1){
            case 1:
                break;

            default:
                p1 = 0;
                break;
            }
        }
    }else{
        printf("\n\nStudent Record is empty. Try adding a student record first!\n\n");
    }
    printf("\n\nYou left Search Student Record Page.\n\n");
};

void SearchStudentID(struct studentSystem *CMSC11){
    int p2 = 1, idx;//
    printf("\n\nSEARCHING STUDENT BY STUDENT ID\n\n");
    printf("Enter Student ID: ");
    scanf("%d", &p2);
    fflush(stdin);
    for (idx = 0; CMSC11[idx].studentID != p2 && idx < 1000; idx++);
    if(idx < 1000){
        printf("\n\nSearch Found!\n\n");
        DisplayStudentSearchedRecord(CMSC11, idx);
        printf("Commands:\n");
        printf("\t1. Edit Student's Basic Information\n\t2. Enroll to Subject\n\t3. Drop Subject\n\t4. Delete Student's Information\n\t5. Exit\n\n");
        printf("Choicet: ");
        scanf("%d", &p2);
        fflush(stdin);
        switch (p2){
        case 1:
            EditStudentRecord(CMSC11, idx);
            break;

        case 2:
            StudentEnrollment(CMSC11, idx);
            break;

        case 3:
            DropSubject(CMSC11, idx);
            break;

        case 4:
            DeleteStudentRecord(CMSC11, idx);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nNo search results.\n\n");
    }
};

void SearchStudentLastName(struct studentSystem *CMSC11){
    int p2 = 1, idx, r, index2;
    char lastNametemp[50];
    printf("\n\nSEARCHING STUDENT BY STUDENT LAST NAME\n\n");
    printf("Enter Student's Last Name: ");
    fgets(lastNametemp, 50, stdin);
    fflush(stdin);
    lastNametemp[Strcspn(lastNametemp,"\n")] = 0;
    r = 0;
    for(idx = 0; idx< 1000; idx++){
        if(Strcmp(CMSC11[idx].lastName, lastNametemp) == 0){
            r++;
        }
    }
    printf("\n\nSearch Results:");
    if (r > 0){
        for(idx = 0; idx < 1000; idx++){
            if(Strcmp(CMSC11[idx].lastName, lastNametemp) == 0){
                DisplayStudentSearchedRecord(CMSC11, idx);
            }
        }
        printf("Choose an ID: ");
        scanf("%d", &idx);
        fflush(stdin);
        for(index2 = 0; CMSC11[index2].studentID != idx; index2++);
        if(index2 < 1000){
            DisplayStudentSearchedRecord(CMSC11, index2);
            printf("Commands:\n");
            printf("\t1. Edit Student's Basic Information\n\t2. Enroll to Subject\n\t3. Drop Subject\n\t4. Delete Student's Information\n\t5. Exit\n\n");
            printf("Choice: ");
            scanf("%d", &p2);
            fflush(stdin);
            switch (p2){
            case 1:
                EditStudentRecord(CMSC11, index2);
                break;

            case 2:
                StudentEnrollment(CMSC11, index2);
                break;

            case 3:
                DropSubject(CMSC11, index2);
                break;

            case 4:
                DeleteStudentRecord(CMSC11, index2);
                break;

            default:
                break;
            }
        }
    }else{
        printf("Student doesn't exist!\n\n");
    }
};

void EditStudentRecord(struct studentSystem *CMSC11, int idx){
    int p3 = 1, index2;
    struct studentSystem temp;
    printf("\n\nEDITING BASIC INFORMATION OF STUDENT ID: %d\n\n", CMSC11[idx].studentID);
    while(p3 > 0){
        printf("What Information to Edit?\n");
        printf("\t1. Student's First Name\n\t2. Student's Last Name\n\t3. Student's CMSC11 Section\n\t4. Student's Hands-On Exam 1\n\t5. Student's Hands-On Exam 2\n\t6. Student's Hands-On Exam 3\n\t7. Edit All\n");
        printf("\nChoice: ");
        scanf("%d", &p3);
        fflush(stdin);
        switch (p3){
        case 1:
            printf("\n\nPrevious Student's First Name: %s\n", CMSC11[idx].firstName);
            printf("New Student's First Name: ");
            fgets(CMSC11[idx].firstName, 50, stdin);
            fflush(stdin);
            CMSC11[idx].firstName[Strcspn(CMSC11[idx].firstName, "\n")] = 0;
            break;

        case 2:
            printf("\n\nPrevious Student's Last Name: %s\n", CMSC11[idx].lastName);
            printf("New Student's Last Name: ");
            fgets(CMSC11[idx].lastName, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lastName[Strcspn(CMSC11[idx].lastName, "\n")] = 0;
            break;

        case 3:
            printf("\n\nPrevious Student's CMSC11 Section: %s\n", CMSC11[idx].lecSection);
            printf("New Student's CMSC11 Section: ");
            fgets(CMSC11[idx].lecSection, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lecSection[Strcspn(CMSC11[idx].lecSection, "\n")] = 0;
            break;

        case 4:
            printf("\n\nPrevious Student's Hands-On Exam 1 Score: %d\n", &CMSC11[idx].hex[0]);
            printf("New Student's Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[idx].hex[0]);
            fflush(stdin);
            break;

        case 5:
            printf("\n\nPrevious Student's Hands-On Exam 2 Score: %d\n", &CMSC11[idx].hex[1]);
            printf("New Student's Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[idx].hex[1]);
            fflush(stdin);
            break;

        case 6:
            printf("\n\nPrevious Student's Hands-On Exam 3 Score: %d\n", &CMSC11[idx].hex[2]);
            printf("New Student's Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[idx].hex[2]);
            fflush(stdin);
            break;

        case 7:
            printf("\n\nPrevious Student's First Name: %s\n", CMSC11[idx].firstName);
            printf("New Student's First Name: ");
            fgets(CMSC11[idx].firstName, 50, stdin);
            fflush(stdin);
            CMSC11[idx].firstName[Strcspn(CMSC11[idx].firstName, "\n")] = 0;
            printf("\nPrevious Student's Last Name: %s\n", CMSC11[idx].lastName);
            printf("New Student's Last Name: ");
            fgets(CMSC11[idx].lastName, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lastName[Strcspn(CMSC11[idx].lastName, "\n")] = 0;
            printf("\nPrevious Student's CMSC11 Section: %s\n", CMSC11[idx].lecSection);
            printf("New Student's CMSC11 Section: ");
            fgets(CMSC11[idx].lecSection, 50, stdin);
            fflush(stdin);
            CMSC11[idx].lecSection[Strcspn(CMSC11[idx].lecSection, "\n")] = 0;
            printf("\nPrevious Student's Hands-On Exam 1 Score: %d\n", CMSC11[idx].hex[0]);
            printf("New Student's Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[idx].hex[0]);
            fflush(stdin);
            printf("\nPrevious Student's Hands-On Exam 2 Score: %d\n", CMSC11[idx].hex[1]);
            printf("New Student's Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[idx].hex[1]);
            fflush(stdin);
            printf("\nPrevious Student's Hands-On Exam 3 Score: %d\n", CMSC11[idx].hex[2]);
            printf("New Student's Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[idx].hex[2]);
            fflush(stdin);
            break;

        default:
            break;
        }
        if (p3 != 7){
            printf("\n\nWould you like to edit more?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &p3);
            switch (p3){
            case 1:
                break;

            default:
                printf("\n\nYou left Edit Student Basic Information Page.\n\n");
                p3 = 0;
                break;
            }
        }else{
            printf("\n\nYou left Edit Student Basic Information Page.\n\n");
        }
    }
    CMSC11[idx].total = CMSC11[idx].hex[0] + CMSC11[idx].hex[1] + CMSC11[idx].hex[2];
    if (CMSC11[idx].total >= 135){
        Strcpy("HD", CMSC11[idx].grade);
    }else if (CMSC11[idx].total >= 120 && CMSC11[idx].total < 135){
        Strcpy("D", CMSC11[idx].grade);
    }else if (CMSC11[idx].total >= 100 && CMSC11[idx].total < 120){
        Strcpy("P", CMSC11[idx].grade);
    }else if (CMSC11[idx].total >= 75 && CMSC11[idx].total < 100){
        Strcpy("C", CMSC11[idx].grade);
    }else{
        Strcpy("F", CMSC11[idx].grade);
    }
   for(idx = 0; CMSC11[idx].studentID != 0; idx++){
        for(index2 = 0; CMSC11[index2].studentID != 0; index2++){
            if (Strcmp(CMSC11[idx].lastName, CMSC11[index2].lastName) == -1){
                temp = CMSC11[index2];
                CMSC11[index2] = CMSC11[idx];
                CMSC11[idx] = temp;
            }
        }
    }
};

void DropSubject(struct studentSystem *CMSC11, int idx){
    int p4 = 1, p5;
    while (p4 > 0){
        printf("\n\nDROPPING ENROLLED SUBJECT OF STUDENT ID %d\n\n", CMSC11[idx].studentID);
        printf("Subjects Enrolled in:\n");
        printf("\t1. %s\n", CMSC11[idx].enrolled[0] ->SubCode);
        if (CMSC11[idx].enrolled[1] != &emp){
            printf("\t2. %s\n", CMSC11[idx].enrolled[1] ->SubCode);
        }
        if (CMSC11[idx].enrolled[2] != &emp){
            printf("\t3. %s\n", CMSC11[idx].enrolled[2] ->SubCode);
        }
        printf("\nSelect: ");
        scanf("%d", &p4);
        fflush(stdin);
        switch (p4){
        case 1:
            printf("You cannot drop-out from this subject.\n\n");
            break;
        case 2:
            printf("Dropping Subject %s\n", CMSC11[idx].enrolled[1] ->SubCode);
            printf("Are you sure that you would drop this subject?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &p5);
            fflush(stdin);
            switch (p5){
            case 1:
                CMSC11[idx].enrolled[1] = &emp;
                printf("\nYou successfully dropped out from this subject!\n\n");
                break;

            default:
                printf("\nDrop-Out Request cancelled!\n\n");
                break;
            }
            break;

        case 3:
            printf("Dropping Subject %s\n", CMSC11[idx].enrolled[2] ->SubCode);
            printf("Are you sure that you would drop this subject?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &p5);
            fflush(stdin);
            switch (p5){
            case 1:
                CMSC11[idx].enrolled[2] = &emp;
                printf("\nYou successfully dropped out from this subject!\n\n");
                break;

            default:
                printf("\nDrop-Out Request cancelled!\n\n");
                break;
            }
            break;

        default:
            break;
        }
        if (CMSC11[idx].enrolled[1] != &emp || CMSC11[idx].enrolled[2] != &emp){
            printf("Would you like to drop another subject?\n\t1. Yes\t2. No\n\n");
            printf("Choice: ");
            scanf("%d", &p4);
            fflush(stdin);
            switch (p4){
            case 1:
                break;

            default:
                p4 = 0;
                break;
            }
        }else{
            p4= 0;
        }
    }
    printf("\n\nYou left Drop Subject Page.\n\n");
};

void DisplayStudentSearchedRecord(struct studentSystem *CMSC11, int idx){
    printf("\n\nDISPLAYING STUDENT RECORD OF STUDENT ID %d\n\n", CMSC11[idx].studentID);
    printf("Basic Information:\n");
    printf("\tStudent ID: %d\n", CMSC11[idx].studentID);
    printf("\tStudent's First Name: %s\n", CMSC11[idx].firstName);
    printf("\tStudent's Last Name: %s\n", CMSC11[idx].lastName);
    printf("\tStudent's CMSC11 Section: %s\n", CMSC11[idx].lecSection);
    printf("\tStudent's Hands-On Exam 1 Score: %d\n", CMSC11[idx].hex[0]);
    printf("\tStudent's Hands-On Exam 2 Score: %d\n", CMSC11[idx].hex[1]);
    printf("\tStudent's Hands-On Exam 3 Score: %d\n", CMSC11[idx].hex[2]);
    if (CMSC11[idx].enrolled[0] != NULL){
        if (CMSC11[idx].enrolled[1] != NULL){
            if (CMSC11[idx].enrolled[2] != NULL){
                printf("\tStudent's Enrolled Subjects: %s, %s, %s\n\n",CMSC11[idx].enrolled[0] ->SubCode, CMSC11[idx].enrolled[1] ->SubCode, CMSC11[idx].enrolled[2] ->SubCode);
            }else{
                printf("\tStudent's Enrolled Subjects: %s, %s\n\n", CMSC11[idx].enrolled[0] ->SubCode, CMSC11[idx].enrolled[1] ->SubCode);
            }
        }else{
            printf("\tStudent's Enrolled Subjects: %s\n\n", CMSC11[idx].enrolled[0] ->SubCode);
        }
    }
};

void DeleteStudentRecord(struct studentSystem *CMSC11, int idx){
    int w, index2;
    struct studentSystem temp;
        printf("\n\nDELETING STUDENT RECORD OF STUDENT ID %d\n\n", CMSC11[idx].studentID);
        printf("Are you sure that you want to delete this student's record?\n\t1. Yes\t2. No\n\n");
        printf("Select: ");
        scanf("%d", &w);
        switch (w){
        case 1:
             CMSC11[idx].studentID = 0;
            Strcpy("", CMSC11[idx].firstName);
            Strcpy("", CMSC11[idx].lastName);
            Strcpy("", CMSC11[idx].lecSection);
            CMSC11[idx].hex[0] = 0;
            CMSC11[idx].hex[1] = 0;
            CMSC11[idx].hex[2] = 0;
            CMSC11[idx].enrolled[0] = NULL;
            CMSC11[idx].enrolled[1] = NULL;
            CMSC11[idx].enrolled[2] = NULL;
            CMSC11[idx].total = 0;
            Strcpy("", CMSC11[idx].grade);
            printf("\n\nStudent Record successfully deleted.\n\n");
            if (CMSC11[idx+1].studentID != 0){
                for (index2 = idx+1; CMSC11[index2].studentID != 0; index2++){
                    temp = CMSC11[index2-1];
                    CMSC11[index2-1] = CMSC11[index2];
                    CMSC11[index2] = temp;
                }
            }
            break;

        default:
            printf("\n\nDelete Request cancelled.\n\n");
            break;
        }
};

void DisplayStudentRecord(struct studentSystem *CMSC11, struct subjectSystem *in){
    int idx, index2;
    if(CMSC11[0].studentID != 0){
        printf("\n\nDISPLAYING ENTIRE STUDENT RECORD\n\n");
        printf("COUNT\tID\tFIRST NAME\t\tLAST NAME\tCMSC11 SECTION\tSUBJECTS ENROLLED\t\tHEX 1 SCORE\tHEX 2 SCORE\tHEX 3 SCORE\tTOTAL\tGRADE\n");
        for (idx = 0; CMSC11[idx].studentID != 0; idx++){
            printf("%d\t", idx+1);
            printf("%d\t", CMSC11[idx].studentID);
            for(index2 = 0; CMSC11[idx].firstName[index2] != '\0'; index2++);
            if (index2+1 < 9){
                printf("%s\t\t\t", CMSC11[idx].firstName);
            }else if (index2+1 < 17){
                printf("%s\t\t", CMSC11[idx].firstName);
            }else{
                printf("%.19s...\t", CMSC11[idx].firstName);
            }
            for(index2 = 0;CMSC11[idx].lastName[index2] != '\0'; index2++);
            if (index2+1 < 9){
                printf("%s\t\t", CMSC11[idx].lastName);
            }else{
                printf("%.11s...\t", CMSC11[idx].lastName);
            }
            printf("%s\t\t", CMSC11[idx].lecSection);
            if (CMSC11[idx].enrolled[0] != NULL){
                if (CMSC11[idx].enrolled[1] != NULL){
                    if (CMSC11[idx].enrolled[2] != NULL){
                        printf("%s, %s, %s\t\t", CMSC11[idx].enrolled[0] ->SubCode, CMSC11[idx].enrolled[1] ->SubCode, CMSC11[idx].enrolled[2] ->SubCode);
                    }else{
                        printf("%s, %s\t\t\t", CMSC11[idx].enrolled[0] ->SubCode,CMSC11[idx].enrolled[1] ->SubCode);
                    }
                }else{
                    printf("%s\t\t\t\t", CMSC11[idx].enrolled[0] ->SubCode);
                }
            }
            printf("%d\t\t%d\t\t%d\t\t%d\t", CMSC11[idx].hex[0], CMSC11[idx].hex[1], CMSC11[idx].hex[2], CMSC11[idx].total);
            printf("%s\n", CMSC11[idx].grade);
        }
        StatisticsRecord(CMSC11, &data);
        printf("\n\t\t\t\t\t\t\t\t\tLOWEST\t\t\t\t%d\t\t%d\t\t%d\t\t%d\n", data.lowest[0], data.lowest[1], data.lowest[2], data.lowest[3]);
        printf("\n\t\t\t\t\t\t\t\t\tHIGHEST\t\t\t\t%d\t\t%d\t\t%d\t\t%d\n", data.highest[0], data.highest[1], data.highest[2], data.highest[3]);
        printf("\n\t\t\t\t\t\t\t\t\tAVERAGE\t\t\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", data.avg[0], data.avg[1], data.avg[2], data.avg[3]);
        printf("\n\t\t\t\t\t\t\t\t\tSTD.DEVATION\t\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3f\n\n", data.std[0], data.std[1], data.std[2], data.std[3]);
    }else{
        printf("\n\nThe Student Record is empty.\n\n");
    }
};

void ClearStudentRecord(struct studentSystem *CMSC11){
    int n, idx;
    printf("\n\nCLEARING ENTIRE STUDENT RECORD\n\n");
    printf("Are you sure you want to delete all student records?\n\t1. Yes\t2. No\n\n");
    printf("Choice: ");
    scanf("%d", &n);
    fflush(stdin);
    switch (n){
    case 1:
        for(idx = 0; CMSC11[idx].studentID != 0; idx++){
            CMSC11[idx].studentID = 0;
            Strcpy("",CMSC11[idx].firstName);
            Strcpy("",CMSC11[idx].lastName);
            Strcpy("",CMSC11[idx].lecSection);
            CMSC11[idx].hex[0] = 0;
            CMSC11[idx].hex[1] = 0;
            CMSC11[idx].hex[2] = 0;
            CMSC11[idx].enrolled[0] = NULL;
            CMSC11[idx].enrolled[1] = NULL;
            CMSC11[idx].enrolled[2] = NULL;
            CMSC11[idx].total = 0;
            Strcpy("", CMSC11[idx].grade);
        }
        break;

    default:
        break;
    }
};

void ExportStudentRecord(struct studentSystem *CMSC11, struct statisticSystem *data){
    FILE *export;
    export = fopen("student.txt", "w");
    if(data->avg[0] == 0){
        StatisticsRecord(CMSC11, data);
    }
    if(CMSC11[0].studentID != 0){
        int q, idx;
        fprintf(export,"COUNT,ID,FIRST NAME,LAST NAME,CMSC11 SECTION,HEX 1 SCORE,HEX 2 SCORE,HEX 3 SCORE,SUBJECTS ENROLLED,TOTAL,GRADE\n");
        for (idx = 0; CMSC11[idx].studentID != 0; idx++){
            fprintf(export,"%d,%d,%s,%s,%s,%d,%d,%d,%s %s %s,%d,%s\n", idx+1,CMSC11[idx].studentID, CMSC11[idx].firstName, CMSC11[idx].lastName, CMSC11[idx].lecSection, CMSC11[idx].hex[0], CMSC11[idx].hex[1], CMSC11[idx].hex[2], CMSC11[idx].enrolled[0]->SubCode, CMSC11[idx].enrolled[1]->SubCode, CMSC11[idx].enrolled[2]->SubCode, CMSC11[idx].total, CMSC11[idx].grade);
        }
        fprintf(export,"\n");
        fprintf(export,",,,,,,Lowest,%d,%d,%d,%d,,\n", data->lowest[0], data->lowest[1], data->lowest[2], data->lowest[3]);
        fprintf(export,",,,,,,Highest,%d,%d,%d,%d,,\n", data->highest[0], data->highest[1], data->highest[2], data->highest[3]);
        fprintf(export,",,,,,,Average,%.3f,%.3f,%.3f,%.3f,,\n", data->avg[0], data->avg[1], data->avg[2], data->avg[3]);
        fprintf(export,",,,,,,Std. Deviation,%.3f,%.3f,%.3f,%.3f,,\n", data->std[0], data->std[1], data->std[2], data->std[3]);
        fclose(export);
        printf("\nStudent Record succesfully extracted!\n\n");
    }else{
        printf("\n\nCan't extract an empty record\n\n");
    }
};

void StatisticsRecord(struct studentSystem *CMSC11, struct statisticSystem *data){
    int idx;
    data->lowest[0] = CMSC11[0].hex[0];
    data->lowest[1] = CMSC11[0].hex[1];
    data->lowest[2] = CMSC11[0].hex[2];
    data->lowest[3] = CMSC11[0].total;
    data->highest[0] = CMSC11[0].hex[0];
    data->highest[1] = CMSC11[0].hex[1];
    data->highest[2] = CMSC11[0].hex[2];
    data->highest[3] = CMSC11[0].total;
    for (idx = 0; CMSC11[idx].studentID != 0; idx++){
        data->avg[0] = data->avg[0] + CMSC11[idx].hex[0];
        data->avg[1] = data->avg[1] + CMSC11[idx].hex[1];
        data->avg[2] = data->avg[2] + CMSC11[idx].hex[2];
        data->avg[3] = data->avg[3] + CMSC11[idx].total;
        if (data->lowest[0] > CMSC11[idx].hex[0]){
            data->lowest[0] = CMSC11[idx].hex[0];
        }
        if (data->lowest[1] > CMSC11[idx].hex[1]){
            data->lowest[1] = CMSC11[idx].hex[1];
        }
        if (data->lowest[2] > CMSC11[idx].hex[2]){
            data->lowest[2] = CMSC11[idx].hex[2];
        }
        if (data->lowest[3] > CMSC11[idx].total){
            data->lowest[3] = CMSC11[idx].total;
        }
        if (data->highest[0] < CMSC11[idx].hex[0]){
            data->highest[0] = CMSC11[idx].hex[0];
        }
        if (data->highest[1] < CMSC11[idx].hex[1]){
            data->highest[1] = CMSC11[idx].hex[1];
        }
        if (data->highest[2] < CMSC11[idx].hex[2]){
            data->highest[2] = CMSC11[idx].hex[2];
        }
        if (data->highest[3] < CMSC11[idx].total){
            data->highest[3] = CMSC11[idx].total;
        }
    }
    data->avg[0] = data->avg[0]/(idx);
    data->avg[1] = data->avg[1]/(idx);
    data->avg[2] = data->avg[2]/(idx);
    data->avg[3] = data->avg[3]/(idx);
    for (idx = 0; CMSC11[idx].studentID != 0; idx++){
        data->std[0] = data->std[0] + (CMSC11[idx].hex[0] - data->avg[0])*(CMSC11[idx].hex[0] - data->avg[0]);
        data->std[1] = data->std[1] + (CMSC11[idx].hex[1] - data->avg[1])*(CMSC11[idx].hex[1] - data->avg[1]);
        data->std[2] = data->std[2] + (CMSC11[idx].hex[2] - data->avg[2])*(CMSC11[idx].hex[2] - data->avg[2]);
        data->std[3] = data->std[3] + (CMSC11[idx].total - data->avg[3])*(CMSC11[idx].total - data->avg[3]);
    }
    data->std[0] = data->std[0]/(idx);
    data->std[1] = data->std[1]/(idx);
    data->std[2] = data->std[2]/(idx);
    data->std[3] = data->std[3]/(idx);
    data->std[0] = Sqrt(data->std[0]);
    data->std[1] = Sqrt(data->std[1]);
    data->std[2] = Sqrt(data->std[2]);
    data->std[3] = Sqrt(data->std[3]);
};

void CreateSubjectRecord(struct subjectSystem *in){
    int s = 1;
    if(read2 == 0){
        char directory[100];
        printf("\n\nCREATING A NEW SUBJECT RECORD\n\n");
        printf("Commands:\n");
        printf("\t1. Read from File\t2. Create Subject Record\t3. Exit\n\n");
        printf("Choice: ");
        scanf("%d", &s);
        fflush(stdin);
        switch (s){
        case 1:
            printf("\n\nREADING FROM FILE\n\n");
            printf("[Note: Use /] Please enter the directory of the file: ");
            fgets(directory, 100, stdin);
            directory[Strcspn(directory, "\n")] = 0;
            ReadFromFileSubject(in, directory);
            break;

        case 2:
            CreateNewSubject(in);
            break;

        default:
            printf("\n\nYou left Create Subject Record Page.\n\n");
            break;
        }
        read2++;
    }else{
        CreateNewSubject(in);
    }
};

void ReadFromFileSubject(struct subjectSystem *in, char a[]){
    FILE *dataset = fopen(a, "r");
    char data[10];
    int idx= 0, index2, index3, index4, error;
    struct studentSystem temp;
    while (!feof(dataset)){
        fscanf(dataset, "\n%[^,], %[^,], %[^\n]", &data, &in[idx].SubCode, &in[idx].title);
        in[idx].SubID = ToInteger(data);
        idx++;
    }
    fclose(dataset);
};

void CreateNewSubject(struct subjectSystem *in){
    int t = 1, idx, index2, m, m2;
    if(in[99].SubID == 0){
        while(t > 0 && in[99].SubID == 0){
            for (idx = 0; idx < 100; idx++){
                if (in[idx].SubID == 0){
                    break;
                }
            }
            printf("\n\nCREATING SUBJECT RECORD\n\n");
            printf("Basic Information:\n");
            m = 1;
            while(m > 0){
                printf("\n\tEnter 2-Digit Subject ID: ");
                scanf("%d", &in[idx].SubID);
                fflush(stdin);
                for (index2 = 0; index2 < idx; index2++){
                    if (in[idx].SubID == in[index2].SubID){
                        printf("\n\n\tOops! ID already taken. Try another one!\n\n");
                        m = 1;
                        break;
                    }else{
                        m = 0;
                    }
                }
            }
            m2 = 1;
            while(m2 > 0){
                printf("\n\tEnter Subject Code: ");
                fgets(in[idx].SubCode, 20, stdin);
                fflush(stdin);
                in[idx].SubCode[Strcspn(in[idx].SubCode, "\n")] = 0;
                for (index2 = 0; in[idx].SubCode[index2] != '\0'; index2++){
                    in[idx].SubCode[index2] = ToUpper(in[idx].SubCode[index2]);
                }
                for (index2 = 0; index2 < idx; index2++){
                    if (Strcmp(in[idx].SubCode,in[index2].SubCode) == 0){
                        printf("\n\n\tOops! Code already taken. Try another one!\n\n");
                        m2 = 1;
                        break;
                    }else{
                        m2 = 0;
                    }
                }
            }
            printf("\n\tEnter Subject Title: ");
            fgets(in[idx].title, 50, stdin);
            fflush(stdin);
            in[idx].title[Strcspn(in[idx].title, "\n")] = 0;
            printf("\n\nSubject ID: %d's Basic Information added onto database\n\n", in[idx].SubID);
            printf("\n\nWould you like to continue to create another subject record?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &t);
            fflush(stdin);
            switch (t){
            case 1:
                break;

            default:
                t = 0;
                break;
            }
        }
        if (t == 0){
            printf("\n\nDone Creating Subject Record!\n\n");
        }
    }else{
        printf("\n\nSubject Record is at full capacity!\n\n");
    }
};

void SearchSubjectRecord(struct subjectSystem *in){
    int u = 1;
    while(u > 0){
        printf("\n\nSEARCHING FOR SUBJECT INFROMATION IN SUBJECT RECORD\n\n");
        printf("Active Commands:\n\t1. Search by Subject ID\t\t2. Search by Subject Code\t\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &u);
        fflush(stdin);
        switch (u){
        case 1:
            SearchSubjectID(in);
            break;

        case 2:
            SearchSubjectCode(in);
            break;

        default:
            break;
        }
        printf("\n\nWould you like to do another search?\n\t1. Yes\t2. No\n\n");
        printf("Select: ");
        scanf("%d", &u);
        fflush(stdin);
        switch (u){
        case 1:
            break;

        default:
            u = 0;
            break;
        }
    }
    printf("\n\nYou left Search Subject Record Page.\n\n");
};

void SearchSubjectID(struct subjectSystem *in){
    int v = 1, idx;
    printf("\n\nSEARCHING SUBJECT BY SUBJECT ID\n\n");
    printf("Enter Subject ID: ");
    scanf("%d", &v);
    fflush(stdin);
    for (idx = 0; in[idx].SubID != v && idx < 100; idx++);
    if(idx < 100){
        printf("\n\nSearch Found!\n\n");
        DisplaySubjectSearchedRecord(in, idx);
        printf("Active Commands:\n");
        printf("\t1. Edit Subject's Basic Information\n\t2. Delete Student's Information\n\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &v);
        fflush(stdin);
        switch (v){
        case 1:
            EditSubjectRecord(in, idx);
            break;

        case 2:
            DeleteSubjectRecord(in, idx);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nNo search results.\n\n");
    }
};

void SearchSubjectCode(struct subjectSystem *in){
    int r = 1, idx, rs;
    char code[20];
    printf("\n\nSEARCHING STUDENT BY SUBJECT CODE\n\n");
    printf("Enter Subject Code: ");
    fgets(code, 20, stdin);
    fflush(stdin);
    code[Strcspn(code,"\n")] = 0;
    rs = 0;
    for(idx = 0; idx < 100; idx++){
        if (Strcmp( code, in[idx].SubCode) == 0){
            rs++;
            break;
        }
    }
    if(idx < 100 && rs == 1){
        printf("\n\nSearch Found!\n\n");
        DisplaySubjectSearchedRecord(in, idx);
        printf("Active Commands:\n");
        printf("\t1. Edit Subject's Basic Information\n\t2. Delete Subject's Information\n\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &r);
        fflush(stdin);
        switch (r){
        case 1:
            EditSubjectRecord(in, idx);
            break;

        case 2:
            DeleteSubjectRecord(in, idx);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nSearch found nothing.\n\n");
    }
};

void EditSubjectRecord(struct subjectSystem *in, int idx){
    int l = 1, m, index2;
    printf("\n\nEDITING BASIC INFORMATION OF SUBJECT ID: %d\n\n", in[idx].SubID);
    while(l > 0){
        printf("What Information to Edit?\n");
        printf("\t1. Subject Code\n\t2. Subject Title\n\t3. Edit All\n\n");
        printf("Choice: ");
        scanf("%d", &l);
        fflush(stdin);
        switch (l){
        case 1:
            m = 1;
            while(m > 0){
                printf("Previous Subject Code: %s\n", in[idx].SubCode);
                printf("New Subject Code: ");
                fgets(in[idx].SubCode, 20, stdin);
                fflush(stdin);
                in[idx].SubCode[Strcspn(in[idx].SubCode, "\n")] = 0;
                for (index2 = 0; in[idx].SubCode[index2] != '\0'; index2++){
                    in[idx].SubCode[index2] = ToUpper(in[idx].SubCode[index2]);
                }
                for (index2 = 0; index2 < idx; index2++){
                    if (Strcmp(in[idx].SubCode,in[index2].SubCode) == 0){
                        printf("\n\n\tCode already taken. Try another one!\n\n");
                        break;
                    }else{
                        m = 0;
                    }
                }
                if (idx == 0){
                    m = 0;
                }
            }
            break;

        case 2:
            printf("Previous Subject Title: %s\n", in[idx].SubCode);
            printf("New Subject Title: ");
            fgets(in[idx].title, 50, stdin);
            fflush(stdin);
            in[idx].title[Strcspn(in[idx].title, "\n")] = 0;
            break;

        case 3:
            printf("\n\nPrevious Subject Code: %s\n", in[idx].SubCode);
            printf("New Subject Code: ");
            fgets(in[idx].SubCode, 20, stdin);
            fflush(stdin);
            in[idx].SubCode[Strcspn(in[idx].SubCode, "\n")] = 0;
            printf("Previous Subject Title: %s\n", in[idx].SubCode);
            printf("New Subject Title: ");
            fgets(in[idx].title, 50, stdin);
            fflush(stdin);
            in[idx].title[Strcspn(in[idx].title, "\n")] = 0;
            break;

        default:
            break;
        }
        if (l != 3){
            printf("\n\nWould you like to edit more?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &l);
            switch (l){
            case 1:
                break;

            default:
                printf("\n\nYou left Edit Subject Basic Information Page.\n\n");
                l = 0;
                break;
            }
        }else{
            printf("\n\nYou left Edit Subject Basic Information Page.\n\n");
        }
    }
};

void DeleteSubjectRecord(struct subjectSystem *in, int idx){
    int j, index2;
    if (in[idx].SubID != 11){
        printf("\n\nDELETING SUBJECT RECORD OF SUBJECT ID %d\n\n", in[idx].SubID);
        printf("Are you sure that you want to delete this subject's record?\n\t1. Yes\t2. No\n\n");
        printf("Choice: ");
        scanf("%d", &j);
        switch (j){
        case 1:
            in[idx].SubID = 0;
            Strcpy("",in[idx].SubCode);
            Strcpy("",in[idx].title);
            printf("\n\nSubject Record successfully deleted.\n\n");
            if (in[idx+1].SubID != 0){
                for (index2 = idx; in[index2].SubID != 0; index2++){
                    in[index2] = in[index2+1];
                }
            }
            break;

        default:
            printf("\n\nDelete Request cancelled.\n\n");
            break;
        }
    }else{
        printf("\n\nYou cannot delete CMSC11, it is a default subject\n\n");
    }
};

void DisplaySubjectSearchedRecord(struct subjectSystem *in, int idx){
    printf("\n\nDISPLAYING SUBJECT RECORD OF SUBJECT ID %d\n\n", in[idx].SubID);
    printf("Basic Information:\n");
    printf("\tSubject ID: %d\n", in[idx].SubID);
    printf("\tSubject Code: %s\n", in[idx].SubCode);
    printf("\tSubject Title: %s\n", in[idx].title);
};

void DisplaySubjectRecord(struct subjectSystem *in){
    int idx;
    for (idx = 0; in[idx].SubID != 0; idx++){
        printf("\n\nDISPLAYING SUBJECT RECORD OF SUBJECT ID %d\n\n", in[idx].SubID);
        printf("Basic Information:\n");
        printf("\tSubject ID: %d\n", in[idx].SubID);
        printf("\tSubject Code: %s\n", in[idx].SubCode);
        printf("\tSubject Title: %s\n", in[idx].title);
    }
};

void ClearSubjectRecord(struct subjectSystem *in){
    int idx, h;
    printf("\n\nAre you sure you want to clear the entire subject record?\n\t1. Yes\t2. No\n\n");
    printf("Select: ");
    scanf("%d", &h);
    fflush(stdin);
    switch (h){
    case 1:
        for (idx = 1; in[idx].SubID != 0; idx++){
            in[idx].SubID = 0;
            Strcpy("",in[idx].SubCode);
            Strcpy("",in[idx].title);
        }
        printf("\n\nSubject Record successfully cleared.\n\n");
        break;

    default:
        printf("\n\nDelete Request cancelled.\n\n");
        break;
    }
};

void ExportSubjectRecord(struct subjectSystem *idx){
    FILE *export;
    export = fopen("subject.txt", "w");
    int g, i;
    fprintf(export,"SUBJECT ID, SUBJECT CODE, SUBJECT TITLE\n");
    for (i = 0; in[i].SubID != 0; i++){
        fprintf(export,"%d,%s,%s\n", in[i].SubID, in[i].SubCode, in[i].title);
    }
    fclose(export);
};

int Strcspn(char a[], char b[]){
    int i;
    for (i = 0; a[i] != b[0]; i++){
    }
    return(i);
};

int ToInteger(char st[]){
    int i = 0, integer = 0, sign = 1;
    if (st[0] == '-'){
        i = 1;
        sign = -1;
    }
    for (i = i; st[i] != 00; i++){
        integer = integer * 10 + st[i] - 48;
    }
    return(integer*sign);
};

int Strcmp(char s1[], char s2[]){
    int i, str;
    for (i = 0; s1[i] != '\0'; i++){
        if (ToLower(s1[i]) == ToLower(s2[i])){
            str = 0;
        }else if (ToLower(s1[i]) < ToLower(s2[i])){
            str = -1;
            break;
        }else{
            str = 1;
            break;
        }
    }
    return(str);
};

char ToLower(char ch){
    if (ch > 64 && ch < 91){
        ch = ch + 32;
    }
    return(ch);
};

char ToUpper(char ch){
    if (ch > 96 && ch < 123){
        ch = ch - 32;
    }
    return(ch);
};

void Strcpy(char src[], char dest[]){
    int i;
    for (i = 0; i < sizeof(src)/sizeof(char); i++){
        dest[i] = src[i];
    }
};

double Sqrt(double number){
    double sqrtNum, temp;
    sqrtNum= number/2;
    temp = 0;
    while(sqrtNum!= temp){
        temp = sqrtNum;
        sqrtNum = (number/temp+temp)/2;
    }
    return(sqrtNum);
};
