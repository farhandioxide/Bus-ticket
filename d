#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERFILE "user.txt"

void signup();
int login();
void addEntry();
void viewEntries();
void searchEntry();
void editEntry();
void deleteEntry();
void clearInput() { while (getchar() != '\n'); }

char currentUser[30];  // Store the logged-in username

int main() {
    int choice;

    printf("=== Personal Diary Program ===\n");

    while (1) {
        printf("\n1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        clearInput();

        if (choice == 1) signup();
        else if (choice == 2) {
            if (login()) break;
            else printf("\nLogin failed. Try again.\n");
        }
        else exit(0);
    }

    // Logged in main menu
    while (1) {
        printf("\n=== Diary Menu ===\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Search Entry\n");
        printf("4. Edit Entry\n");
        printf("5. Delete Entry\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: addEntry(); break;
            case 2: viewEntries(); break;
            case 3: searchEntry(); break;
            case 4: editEntry(); break;
            case 5: deleteEntry(); break;
            case 6: exit(0);
            default: printf("Invalid option.\n");
        }
    }

    return 0;
}

void signup() {
    FILE *fp = fopen(USERFILE, "a");  // append mode to allow multiple users
    char user[30], pass[30];

    if (!fp) {
        printf("Error creating user file.\n");
        return;
    }

    printf("\nCreate username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    printf("Create password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    fprintf(fp, "%s %s\n", user, pass);  // store users in one line
    fclose(fp);

    printf("Signup successful!\n");
}

int login() {
    FILE *fp = fopen(USERFILE, "r");
    char storedUser[30], storedPass[30];
    char user[30], pass[30];
    int found = 0;

    if (!fp) {
        printf("No user registered. Please signup first.\n");
        return 0;
    }

    printf("\nEnter username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;

    printf("Enter password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = 0;

    while (fscanf(fp, "%s %s", storedUser, storedPass) != EOF) {
        if (strcmp(user, storedUser) == 0 && strcmp(pass, storedPass) == 0) {
            found = 1;
            strcpy(currentUser, user);
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("\nLogin successful!\n");
        return 1;
    }

    return 0;
}

void addEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "a");
    if (!fp) {
        printf("Error opening diary file.\n");
        return;
    }

    char date[20], title[50], content[500], line[200];

    printf("\nEnter date (DD/MM/YYYY): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    printf("Enter title: ");
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = 0;

    printf("Write content (end with a single line containing only ~):\n");

    content[0] = '\0';
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strcmp(line, "~\n") == 0) break;
        strcat(content, line);
    }

    fprintf(fp, "DATE: %s\nTITLE: %s\nCONTENT:\n%s---\n", date, title, content);
    fclose(fp);

    printf("Entry added.\n");
}

void viewEntries() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    char line[600];
    int current = 0;

    if (!fp) {
        printf("No entries found.\n");
        return;
    }

    printf("\n=== All Entries ===\n\n");

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            printf("\n=== Entry #%d ===\n", current);
        }
        printf("%s", line);
    }

    if (current == 0)
        printf("No entries available.\n");

    fclose(fp);
}

void searchEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp) {
        printf("No entries.\n");
        return;
    }

    printf("Enter entry number to search: ");
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;
                printf("\n=== Entry #%d ===\n", target);
                printf("%s", line);
                while (fgets(line, sizeof(line), fp)) {
                    printf("%s", line);
                    if (strstr(line, "---")) break;
                }
                break;
            }
        }
    }

    if (!found)
        printf("No entry found with that number.\n");

    fclose(fp);
}

void editEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    printf("Enter entry number to edit: ");
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;

                char date[50], newTitle[50], newContent[500];
                strcpy(date, line + 6);
                date[strcspn(date, "\n")] = 0;

                printf("New title: ");
                fgets(newTitle, sizeof(newTitle), stdin);
                newTitle[strcspn(newTitle, "\n")] = 0;

                printf("New content (end with ~):\n");
                newContent[0] = '\0';
                char l[200];
                while (1) {
                    fgets(l, sizeof(l), stdin);
                    if (strcmp(l, "~\n") == 0) break;
                    strcat(newContent, l);
                }

                fprintf(temp, "DATE: %s\nTITLE: %s\nCONTENT:\n%s---\n",
                        date, newTitle, newContent);

                while (fgets(line, sizeof(line), fp))
                    if (strstr(line, "---")) break;

                continue;
            }
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    if (found)
        printf("Entry #%d updated successfully.\n", target);
    else
        printf("No entry found with that number.\n");
}

void deleteEntry() {
    char filename[50];
    sprintf(filename, "%s_diary.txt", currentUser);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[600];
    int found = 0, target, current = 0;

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    printf("Enter entry number to delete: ");
    scanf("%d", &target);
    clearInput();

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "DATE:")) {
            current++;
            if (current == target) {
                found = 1;
                while (fgets(line, sizeof(line), fp)) {
                    if (strstr(line, "---")) break;
                }
                continue;
            }
        }
        fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    if (found)
        printf("Entry #%d deleted successfully.\n", target);
    else
        printf("No entry found with that number.\n");
}
