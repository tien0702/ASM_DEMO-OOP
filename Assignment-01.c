#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char firstName[21];
    char middleName[21];
    char lastName[21];
}Name;
typedef struct {
    char prefix[21];
    int checkPrefix;
    char suffix[21];
    int checkSuffix;
    char nickName[21];
    int checkNickName;
    char jobTitle[21];
    int checkJobTitle;
}AddField;
struct Info{
    Name name;
    AddField field;
    char comnamy[31];
    char phone[21];
    char email[51];
    char address[51];
    char birth[9];
    char website[51];
    char note[101];
    int checkFavourites;
};
int menu(int *n);
void printLine();
void printTitle();
char* rmvMid(char *s);
char* up_low(char *s);
void sortContact(struct Info *info, int count);
void printList(struct Info info[], int i);
void line();
void inputName(Name *name);
struct Info inputInfo(struct Info info[], int *count);
void getString(char *str, int length);
char* checkPhone(char *phone);
char* checkBirth(char *birth);
void disPlayContact(struct Info *info, int *count, int choose);
void disPlayFullInfo(struct Info info[], int choice, int *count);
bool space(char c);
int checkChoice(int limitF, int limitL, int *choice);
struct Info addFavourites(struct Info *info, int index);
void searchYourContact(struct Info *info, int *count);
void updateInfo(struct Info *info);
int menuEdit(struct Info info[], int* choose, int* count);
void deleteContact(struct Info *info,int *count, int *position);
void addField(struct Info *info, int choice, int count);
int menuField(struct Info *info, int choice);
void writeFileContact(struct Info *info, int count);
void readFileContact(struct Info *info, int count);

int main()
{
    struct Info contact[250];
    int countContact = 0;
    int choice;
    do{
        choice = 0;
        menu(&choice);
        switch (choice)
        {
        case 1:
            searchYourContact(contact, &countContact);
            break;
        case 2:
            inputInfo(&contact[countContact], &countContact);
            countContact = countContact + 1;
            sortContact(contact, countContact);
            writeFileContact(contact, countContact);
            break;
        case 3:
            disPlayContact(contact, &countContact, 3);
            break;
        case 4:
            disPlayContact(contact, &countContact, 4);
            break;
        case 5:
            printf("Good Bye!\n");
            break;
        }
    } while (choice != 5);
    return 0;
}
int menu(int *n){
    *n = 0;
    line();
    printf("\n--- VTC ACADEMY CONTATCT MANAGEMENT ---");
    line();
    printf("\n  1. SEARCH YOUR CONTACT");
    printf("\n  2. ADD CONTACT");
    printf("\n  3. DISPLAY FAVOURITES CONTACT");
    printf("\n  4. DISPLAY ALL CONTACT");
    printf("\n  5. EXIT APPLCATION");
    line();
    printf("\n  #YOUR CHOICE: ");
    fflush(stdin);
    scanf("%d", n);
    checkChoice(1, 5, n);
    return *n;
}
//In dòng tiêu đề, viền và danh sách contact
void printLine(){
    printf("+--------------------------------------------------------------------+\n");
}
void line(){
    printf("\n=======================================");
}
void printTitle(){
    printf("|  %s  | %-60s|\n", "NO", "Full Name");
}
void printList(struct Info info[], int index){
    int space;
    int check = 0;
    int lenPre = 0, lenSuf = 0, lenNick = 0;
    int rosalia = 0;
    int lenFirst = strlen(info->name.firstName);
    int lenMid = strlen(info->name.middleName);
    int lenLast = strlen(info->name.lastName);
    if(info->field.checkPrefix == 1){
        lenPre = strlen(info->field.prefix);
        check = 1;
    }
    if(info->field.checkSuffix == 1){
        lenSuf = strlen(info->field.suffix);
        check = 1;
    if(info->field.checkNickName == 1){
        lenNick = strlen(info->field.nickName);
        check = 1;
    }
    if(check == 1){
        rosalia = lenPre + lenSuf + lenNick;
        space = 61 - (lenFirst + lenMid + lenLast + rosalia);
    }else{
        space = 61 - (lenFirst + lenMid + lenLast);
    }
    printf("|  %d   |", index+1);
    if(info->field.checkPrefix == 1){
        printf("%s", info->field.prefix);
    }
    if(info->field.checkSuffix == 1){
        printf("%s", info->field.suffix);
    }
    printf("%s%s%s", info->name.firstName, info->name.middleName, info->name.lastName);
    if(info->field.checkNickName == 1){
        printf("%s", info->field.nickName);
    }
    for(int i = 0; i < space; i++){
        printf(" ");
    }
    printf("|\n");
}
//Nhập vào tên và thông tin
void inputName(Name *name){
    printf("First Name: ");
    getString(name->firstName, 20);

    up_low(name->firstName);
    printf("Middle Name: ");

    getString(name->middleName, 20);
    up_low(name->middleName);
    printf("Last Name: ");

    getString(name->lastName, 20);
    up_low(name->lastName);
}
struct Info inputInfo(struct Info info[], int *count){
    if(info->field.checkPrefix == 1){
        printf("\nPrefix: ");
        getString(info->field.prefix, 20);
        up_low(info->field.prefix);
    }
    if(info->field.checkSuffix == 1){
        printf("\nSuffix: ");
        getString(info->field.suffix, 20);
        up_low(info->field.suffix);
    }
    if(info->field.checkNickName == 1){
        printf("\nNickname: ");
        getString(info->field.nickName, 20);
        up_low(info->field.nickName);
    }
    if(info->field.checkJobTitle == 1){
        printf("\nJob Title: ");
        getString(info->field.jobTitle, 20);
        up_low(info->field.jobTitle);
    }
    inputName(&info->name);
    printf("Company: ");
    getString(info->comnamy, 30);
    printf("Phone: ");
    getString(info->phone, 20);
    checkPhone(info->phone);
    printf("Address: ");
    getString(info->address, 50);
    printf("Email: ");
    up_low(info->address);
    getString(info->email, 50);
    printf("Birthday: ");
    getString(info->birth, 8);
    checkBirth(info->birth);
    printf("Website: ");
    getString(info->website, 50);
    printf("Note: ");
    getString(info->note, 100);
    line();
    printf("\nCreate contact complete!");
    printf("\nPress enter key continue...");
    fflush(stdin);
    getchar();
    return *info;
}
bool space(char c){
    return c == ' ' || c == '\t' || c == '\n';
}
//loại bỏ dấu cách thừa
char* rmvMid(char *s)
{
    int i, j;
    int length = strlen(s);
    int count = 0;
    //mid
    for (i = 0; i < strlen(s); i++){
        if (space(s[i]) && space(s[i + 1])){
            for (j = i + 1; j < strlen(s); j++){
                s[j] = s[j + 1];
            }
            i--;
            strlen(s-1);
        }
    //last
        if(space(s[length-1])){
            s[length-1] = '\0';
            length--;
        }
    }
    //first
    if (!space(s[0]) && strlen(s) > 0)
    {
        int lenMid = strlen(s);
        for (i = lenMid; i > 0; i--){
            s[i] = s[i - 1];
        }
        s[0] = ' ';
        s[lenMid + 1] = '\0';
    }else{
        for (i = 0; i < strlen(s); i++){
            if (space(s[i])){
                count++;
            }else{
                break;
            }
        }
        count = count - 1;
        if (count > 0){
            for (i = 0; i < length; i++){
                s[i] = s[i + count];
            }
        }
    }
    return s;
}
//viết hoa chữ cái đầu 
char* up_low(char *s){
    rmvMid(s);
    int length = strlen(s);
    int i, j;
    for(i=0; i<length; i++){
        if(space(s[i])){
            if(s[i+1] >= 97 && s[i+1] <= 122){
                s[i+1] = s[i+1] - 32;
            }
            for(j = i+2; j<length; j++){
                if(space(s[j])){
                    break;
                }
                else if(s[j] >= 65 && s[j] <= 90){
                    s[j] = s[j] + 32;
                }
            }
        }
    }
    return s;
}
//Nhap
void getString(char *str, int length){
    fseek(stdin, 0, SEEK_END);
    fflush(stdin);
    fgets(str, length, stdin);
    str[strlen(str) - 1] = '\0';
    fseek(stdin, 0, SEEK_END);
    fflush(stdin);
}
char* checkBirth(char *birth){
    int i;
    int check;
    int leng;
    if(birth[0] == '\n'){
        return birth;
    }
    do{
        check = 0;
        leng = strlen(birth);
        for(i = 1; i<leng; i++){
            if(birth[i] < 48 && birth[i] != 47 && birth[i] != 45 || birth[i] > 57){
                printf("\nInvalid, Birth: ");
                getString(birth, 20);
                check = 1;
                break;
            }
        }
    }while(check == 1);
    return birth;
}
char* checkPhone(char *phone){
    int i;
    int check;
    int leng;
    do{
        check = 0;
        leng = strlen(phone);
        if (phone[0] < 48 && phone[0] != 43 || phone[0] > 57){
            printf("\nInvalid phone number!\nPhone: ");
            getString(phone, 20);
            check = 1;
        }else{
            for (i = 1; i < leng; i++){
                if (phone[i] < 48 || phone[i] > 57){
                    printf("\nInvalid phone number!\nPhone: ");
                    getString(phone, 20);
                    check = 1;
                    break;
                }
            }
        }
    } while (check == 1);
    return phone;
}
//Hiển thị tên và thông tin
void disPlayContact(struct Info *info, int *count, int choose){
    int check = 0, i = 0;
    int choice;
    printLine();
    printTitle();
    printLine();
    sortContact(info, *count);
    if (choose == 4){
        for (i = 0; i < *count; i++){
            printList(&info[i], i);
            check = 1;
        }
        if(check == 0){
            printf("| %-67s|\n", "NO CONTACR!");
            printLine();
            printf("\nPress enter key continue...");
            fflush(stdin);
            getchar();
        }else{
            printLine();
            printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0 TO BACK MENU: ");
            fflush(stdin);
            scanf("%d", &choice);
            checkChoice(0, *count, &choice);
        }
        if (choice != 0){
                disPlayFullInfo(info, choice - 1, count);
        }
    }
    if (choose == 3){
        int save[250];
        for(i = 0; i < *count; i++){
            if(info[i].checkFavourites == 1){
                printList(&info[i], check);
                save[check + 1] = i;
                check++;
            }
        }
        if(check == 0){
            printf("| %-67s|\n", "NO CONTACR!");
            printLine();
            printf("\nPress enter key continue...");
            fflush(stdin);
            getchar();
        }else{
            printLine();
            printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0 TO BACK MENU: ");
            fflush(stdin);
            scanf("%d", &choice);
            checkChoice(0, check, &choice);
            if(choice != 0){
                printf("(%d)", choice);
                disPlayFullInfo(info, save[choice], count);
            }
        }
    }
}
//hien thi chi tiet
void disPlayFullInfo(struct Info info[], int choice, int *count){
    line();
    if(info[choice].field.checkPrefix == 1) printf("\nPrefix: %s", info[choice].field.prefix);
    if(info[choice].field.checkSuffix == 1) printf("\nSuffix: %s", info[choice].field.suffix);
    if(info[choice].field.checkNickName == 1) printf("\nNickname: %s", info[choice].field.nickName);
    if(info[choice].field.checkJobTitle == 1) printf("\nJob Title: %s", info[choice].field.jobTitle);
    printf("\nFirst Name: %s", info[choice].name.firstName);
    printf("\nMiddle Name: %s", info[choice].name.middleName);
    printf("\nLast Name: %s", info[choice].name.lastName);
    printf("\nCompany: %s", info[choice].comnamy);
    printf("\nPhone: %s", info[choice].phone);
    printf("\nAddress: %s", info[choice].address);
    printf("\nEmail: %s", info[choice].email);
    printf("\nBirthday: %s", info[choice].birth);
    printf("\nWebsite: %s", info[choice].website);
    printf("\nNote: %s", info[choice].note);
    menuEdit(info, &choice, count);
}

int menuEdit(struct Info info[], int *choice, int *count){
    int n;
    line();
    if(info[*choice].checkFavourites == 0) printf("\n1. ADD TO FAVOURITES\n2. UPDATE\n3. DELETE\n4. ADD FIELD\n5. BACK TO MAIN MENU");
    else if(info[*choice].checkFavourites == 1) printf("\n1. DELETE FAVOURITES\n2. UPDATE\n3. DELETE \n4. ADD FIELD\n5. BACK TO MAIN MENU");
    line();
    printf("\n  #YOUR CHOICE: ");
    fflush(stdin);
    scanf("%d", &n);
    checkChoice(1, 5, &n);
    switch (n){
    case 1:
        addFavourites(info, *choice);
        break;
    case 2:
        inputInfo(info, choice);
        writeFileContact(info, *count);
        break;
    case 3:
        deleteContact(info, choice, count);
        break;
    case 4:
        addField(info, *choice, *count);
        break;
    case 5:
        break;
    }
}
//tìm kiếm liên hệ
void searchYourContact(struct Info info[], int *count){
    char name[61];
    int i;
    if(*count == 0){
        printf("\nTHE DIRECTORY IS EMPTY!\n");
        printf("\nPress enter key continue...");
        fflush(stdin);
        getchar();
    }
    else{
        int save[250], check = 0, choice;
        line();
        printf("\nINPUT YOUR SEARCH: ");
        getString(name, 60);
        up_low(name);
        printf("\n");
        printLine();
        printf("|%18s %-49s|\n", "TOP NAMES MATCH:", name);
        printLine();
        printTitle();
        printLine();
        for(i = 0; i < *count; i++){
            if(strcmp(name, info[i].name.firstName) == 0 || strcmp(name, info[i].name.middleName) == 0 || strcmp(name, info[i].name.lastName) == 0){
                save[check + 1] = i;
                printList(&info[i], check);
                check ++;
            }
        }
        printLine();
        if(check == 0){
            printf("| %-67s|\n", "DON'T HAVE THIS CONTACT!");
            printLine();
            printf("\nPress Enter Key To Continue...");
            fflush(stdin);
            getchar();
        }else{
            printf("\nINPUT CONTACT NO TO VIEW DETALLS OR INPUT 0 TO BACK MENU: ");
            fflush(stdin);
            scanf("%d", &choice);
            checkChoice(0, check, &choice);
            if (choice != 0){
                disPlayFullInfo(info, save[choice], count);
            }
        }
    }
}
//sắp xếp liên hệ
void sortContact(struct Info *info, int count){
    int i, j;
    for(i=0; i<count-1; i++){
        for(j=count-1; j>i; j--){
            if(strcmp(info[j].name.firstName, info[j-1].name.firstName)<0){
                struct Info contact = info[j];
                info[j] = info[j-1];
                info[j-1] = contact;
            }
        }
    }
}
//kiem tra lua chon
int checkChoice(int limitF, int limitL, int *choice){
    while (*choice < limitF || *choice > limitL){
        printf("\nYou choose wrong!");
        printf("\nPlease re-enter: ");
        fflush(stdin);
        scanf("%d", choice);
    }
    return *choice;
}
//them vao danh sach yeu thich
struct Info addFavourites(struct Info *info, int index){
    if(info[index].checkFavourites == 0){
        info[index].checkFavourites = 1;
        printf("\nAdd Favourites Compelte!\nPress Enter Key To Continue...");
        fflush(stdin);
        getchar();
    }else{
        info[index].checkFavourites = 0;
        printf("\nDelete Favourites Compelte!\nPress Enter Key To Continue...");
        fflush(stdin);
        getchar();
    }
    return *info;
}
void deleteContact(struct Info *info, int *choice, int *count){
    int yesOrNo;
    printf("\nARE YOU SURE YOU WANT TO DELETE THIS CONTACT!");
    printf("\n     %-13s%15s\n", "1. Cancel", "2. Done");
    line();
    printf("\n#YOUR CHOICE: ");
    fflush(stdin);
    scanf("%d", &yesOrNo);
    checkChoice(1, 2, &yesOrNo);
    if (yesOrNo == 2){
        int i;
        for (i = *choice; i < *count - 1; i++){
            info[i] = info[i + 1];
        }
        *count = *count - 1;
        printf("\nDelete contact complete!");
        printf("\n\nPress enter key continue...");
        fflush(stdin);
        getchar();
    }
    if (yesOrNo == 1){
        menuEdit(info, choice, count);
    }
}
int menuField(struct Info *info, int index){
    line();
    int choice;
    if(info[index].field.checkPrefix == 0){
        printf("\n1. Prefix");
    }else{
        printf("\n1. Delete Prefix");
    }
    if(info[index].field.checkSuffix == 0){
        printf("\n2. Sufix");
    }else{
        printf("\n2. Delete Sufix");
    }
    if(info[index].field.checkNickName == 0){
        printf("\n3. Nickname");
    }else{
        printf("\n3. Delete Nickname");
    }
    if(info[index].field.checkJobTitle == 0){
        printf("\n4. Job Title");
    }else{
        printf("\n4. Delete Job Title");
    }
    line();
    printf("\n#YOUR CHOICE: ");
    fflush(stdin);
    choice = 0;
    scanf("%d", &choice);
    checkChoice(1, 4, &choice);
    return choice;
}
void addField(struct Info *info, int index, int count){
    int choice, check = 0;
    choice = menuField(info, index);
    switch (choice){
    case 1:
        if (info[index].field.checkPrefix == 0){
            printf("\nPrefix: ");
            getString(info[index].field.prefix, 20);
            up_low(info[index].field.prefix);
            info[index].field.checkPrefix = 1;
            check = 1;
        }else{
            info[index].field.checkPrefix = 0;
            check = 0;
        }
        break;
    case 2:
        if (info[index].field.checkSuffix == 0){
            printf("\nSufix: ");
            getString(info[index].field.suffix, 20);
            up_low(info[index].field.suffix);
            info[index].field.checkSuffix = 1;
            check = 1;
        }else{
            info[index].field.checkSuffix = 0;
            check = 0;
        }
        break;
    case 3:
        if (info[index].field.checkNickName == 0){
            printf("\nNickname: ");
            getString(info[index].field.nickName, 20);
            up_low(info[index].field.nickName);
            info[index].field.checkNickName = 1;
            check = 1;
        }else{
            info[index].field.checkNickName = 0;
            check = 0;
        }
        break;
    case 4:
        if (info[index].field.checkJobTitle == 0){
            printf("\nJob Title: ");
            getString(info[index].field.jobTitle, 20);
            up_low(info[index].field.jobTitle);
            info[index].field.checkJobTitle = 1;
            check = 1;
        }else{
            info[index].field.checkJobTitle = 0;
            check = 0;
        }
        break;
    }
    writeFileContact(info, count);
    if(check == 1) printf("Add field complete!");
    if(check == 0) printf("\nDelete field complete!");
    printf("\nPress enter key continue...");
    fflush(stdin);
    getchar();
}
void writeFileContact(struct Info *info, int count){
    FILE* ptr = fopen("contact.dat", "w");
    for(int i = 0; i < count; i++){
        fprintf(ptr, "%s%s", "Prefix: ", info[i].field.prefix);
        fprintf(ptr, "\n%s%s", "Sufix: ", info[i].field.suffix);
        fprintf(ptr, "\n%s%s", "NickName: ", info[i].field.nickName);
        fprintf(ptr, "\n%s%s", "Job Title: ", info[i].field.jobTitle);
        fprintf(ptr, "\n%s%s", "First Name: ", info[i].name.firstName);
        fprintf(ptr, "\n%s%s", "Middle Name: ", info[i].name.middleName);
        fprintf(ptr, "\n%s%s", "Last Name: ", info[i].name.lastName);
        fprintf(ptr, "\n%s%s", "Company: ", info[i].comnamy);
        fprintf(ptr, "\n%s%s", "Phone: ", info[i].phone);
        fprintf(ptr, "\n%s%s", "Address: ", info[i].address);
        fprintf(ptr, "\n%s%s", "Email: ", info[i].email);
        fprintf(ptr, "\n%s%s", "Birthday: ", info[i].birth);
        fprintf(ptr, "\n%s%s", "Website: ", info[i].website);
        fprintf(ptr, "\n%s%s\n\n", "Note: ", info[i].note);
    }
    fclose(ptr);
}