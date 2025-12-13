#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct {
    char payment_status[20]; // "Pending" or "Complete" 
} pd;


//func prototypes

void UserMenu();
void AdminMenu();
void BusAvail();
void ReserveTicket();
void CancelTicket();
void ViewTicket();
void clearInputBuffer();
int loginUser(char usernm[], int userpass, char actualUser[]);
void newUserSignUp();
void showSeatPreview(char *busClass, int bookedSeats[], int bookedCount);
void ViewSeat(int busNo);
void makePayment(pd *passdetails);
void Payment();
void checkUserinfo();
void getBusInfo(int busNo, char *className, char *timeName);
void loadBookedSeats(int busNo, int bookedSeats[], int *bookedCount);

typedef struct {
    char username[50];
    int busNo;
    int numSeats;
    char travelClass[32];
    char travelTime[32];
    int assignedSeats[20];
} Booking;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//sign up func

void newUserSignUp() {
    char uname[50];
    int pword;
    FILE *fp;

    printf("\n===== NEW USER SIGN-UP =====\n");

    printf("Enter a username (No spaces): ");
    clearInputBuffer();
    fgets(uname, sizeof(uname), stdin);
    uname[strcspn(uname, "\n")] = '\0';

    printf("Create a password (Numeric): ");
    while (scanf("%d", &pword) != 1) {
        printf("Invalid input. Enter numeric password: ");
        clearInputBuffer();
    }

    fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%s %d\n", uname, pword);
    fclose(fp);

    printf("User created successfully!\n");
    printf("Press any key to return to main menu...");
    getch();
}


//log in func


int loginUser(char usernm[], int userpass, char actualUser[]) {
    FILE *fp;
    char savedName[50];
    int savedPass;

    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("No users found. Please sign up first.\n");
        return 0;
    }

    while (fscanf(fp, "%s %d", savedName, &savedPass) != EOF) {
        if (strcmp(usernm, savedName) == 0 && userpass == savedPass) {
            strcpy(actualUser, savedName);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


// main func 


int main() {
    int choice;
    char usernm[50];
    int userpass;
    char actualUser[50];
    char adminname[50];
    int adminpass;

    while (1) {
        printf("\n====================\n");
        printf("    MAIN MENU\n");
        printf("======================\n");
        printf("1>> New user sign up\n");
        printf("2>> Login as User\n");
        printf("3>> Login as Admin\n");
        printf("4>> Exit\n");
        printf(">> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                newUserSignUp();
                break;

            case 2:
                printf("Enter username: ");
                clearInputBuffer();
                fgets(usernm, sizeof(usernm), stdin);
                usernm[strcspn(usernm, "\n")] = '\0';

                printf("Enter password: ");
                while (scanf("%d", &userpass) != 1) {
                    printf("Invalid input. Enter numeric password: ");
                    clearInputBuffer();
                }

                if (loginUser(usernm, userpass, actualUser)) {
                    printf("\n\nLogin Successful\n");
                    printf("Welcome %s!\n\n", actualUser);
                    UserMenu();
                } else {
                    printf("\nNo user found or wrong password\n");
                }

                break;

            case 3:
                printf("Enter username(no spaces): ");
                scanf("%s", adminname);

                printf("Enter password: ");
                if (scanf("%d", &adminpass) != 1) {
                    printf("Invalid password input.\n");
                    clearInputBuffer();
                    break;
                }

                if (strcmp(adminname, "admin") == 0 && adminpass == 1234) {
                    AdminMenu();
                } else {
                    printf("Admin login failed.\n");
                }
                break;
            case 4:
                printf("Exiting....");
                return 0;

            default:
                printf("Invalid option chosen\n");
        }
    }
}


// user menu func ----------

void UserMenu()
{
    int user_choice;
    while(1)
    {
        printf("\n=====================\n");
        printf("     USER MENU\n");
        printf("=====================\n");
        printf("1>>Check available bus and schedule\n");
        printf("2>>Reserve ticket\n");
        printf("3>>Cancel ticket\n");
        printf("4>>View ticket\n");
        printf("5>>Exit\n");
        printf(">> ");
        if (scanf("%d",&user_choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(user_choice)
        {
            case 1: BusAvail();break;
            case 2: ReserveTicket();break;
            case 3: CancelTicket();break;
            case 4: ViewTicket();break;
            case 5: printf("Exiting....");return ;
            default: printf("Wrong option chosen..\n");
        }
    }

}

//Admin menu func -----------

void AdminMenu()
{
    int user_choice;
    while(1)
    {
        printf("\n=====================\n");
        printf("     ADMIN MENU\n");
        printf("=====================\n");
        printf("1>>Check available bus details\n");
        printf("2>>Cancel ticket\n");
        printf("3>>View ticket\n");
        printf("4>>Check user info\n");
        printf("5>>Exit\n");
        printf(">> ");
        if (scanf("%d",&user_choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(user_choice)
        {
            case 1: BusAvail(); break;
            case 2: CancelTicket();break;
            case 3: ViewTicket();break;
            case 4: checkUserinfo();break;
            case 5: printf("Exiting....");return ;
            default: printf("Wrong option chosen..\n");
        }
    }

}

// Available bus ..

void BusAvail()
{
    printf("------------------------------------------------------------------------------------------------\n");
    printf("Bus.No\tClass\t\tName\t\t\tDestination\t\tCharges\t\tTime\n");
    printf("------------------------------------------------------------------------------------------------\n");

    // MORNING
    printf("---- Morning Schedule ----\n");
    printf("1001\tBusiness\tRoyal Express       \tDhaka to Chittagong\ttk 1800\t\t7:00  AM\n");
    printf("1002\tPremium \tSundarban Travels   \tDhaka to Chittagong\ttk 1700\t\t8:00  AM\n");
    printf("1003\tVIP/Sleeper\tStar Line           \tDhaka to Chittagong\ttk 3300\t\t9:00  AM\n");

    // AFTERNOON
    printf("\n---- Afternoon Schedule ----\n");
    printf("2001\tBusiness\tRoyal Express       \tDhaka to Chittagong\ttk 1800\t\t1:00  PM\n");
    printf("2002\tPremium \tSundarban Travels   \tDhaka to Chittagong\ttk 2600\t\t2:30  PM\n");
    printf("2003\tVIP/Sleeper\tStar Line           \tDhaka to Chittagong\ttk 3100\t\t4:00  PM\n");

    // NIGHT
    printf("\n---- Night Schedule ----\n");
    printf("3001\tBusiness\tRoyal Express       \tDhaka to Chittagong\ttk 1750\t\t7:30  PM\n");
    printf("3002\tPremium \tSundarban Travels   \tDhaka to Chittagong\ttk 2500\t\t9:00  PM\n");
\
    printf("3003\tVIP/Sleeper\tStar Line           \tDhaka to Chittagong\ttk 3100\t\t9:40  PM\n");

    // SPECIAL NIGHT ONLY
    printf("\n---- Special Night Only ----\n");
    printf("4001\tVIP/Sleeper\tNight Rider         \tDhaka to Chittagong\ttk 4000\t\t11:45 PM\n");

    printf("------------------------------------------------------------------------------------------------\n");
    printf("Press any key to return to user menu...");
    getch();
}

// Validate busNo against known bus list

int isValidBusNo(int busNo) {
    int validBusNos[] = {1001,1002,1003,2001,2002,2003,3001,3002,3003,4001};
    int n = sizeof(validBusNos)/sizeof(validBusNos[0]);
    for (int i = 0; i < n; i++) if (validBusNos[i] == busNo) return 1;
    return 0;
}

// Provide bus-specific class/time 

void getBusInfo(int busNo, char *className, char *timeName) {
    
    strcpy(className, "Business");
    strcpy(timeName, "Unknown");

    if (busNo == 1001) { strcpy(className, "Business"); strcpy(timeName, "7:00 AM"); }
    else if (busNo == 1002) { strcpy(className, "Premium"); strcpy(timeName, "8:00 AM"); }
    else if (busNo == 1003) { strcpy(className, "VIP/Sleeper"); strcpy(timeName, "9:00 AM"); }

    else if (busNo == 2001) { strcpy(className, "Business"); strcpy(timeName, "1:00 PM"); }
    else if (busNo == 2002) { strcpy(className, "Premium"); strcpy(timeName, "2:30 PM"); }
    else if (busNo == 2003) { strcpy(className, "VIP/Sleeper"); strcpy(timeName, "4:00 PM"); }

    else if (busNo == 3001) { strcpy(className, "Business"); strcpy(timeName, "7:30 PM"); }
    else if (busNo == 3002) { strcpy(className, "Premium"); strcpy(timeName, "9:00 PM"); }
    // 3003 -> VIP, 9:40 PM
    else if (busNo == 3003) { strcpy(className, "VIP/Sleeper"); strcpy(timeName, "9:40 PM"); }

    else if (busNo == 4001) { strcpy(className, "VIP/Sleeper"); strcpy(timeName, "11:45 PM"); }
}

// Load already booked seat numbers for a given bus 

void loadBookedSeats(int busNo, int bookedSeats[], int *bookedCount) {
    *bookedCount = 0;
    FILE *bf = fopen("bookings.txt", "r");
    if (bf == NULL) return;

    char line[512];
    while (fgets(line, sizeof(line), bf)) {
        char copy[512];
        strcpy(copy, line);
        char *tk = strtok(copy, " \n\t");
        if (!tk) continue;
        tk = strtok(NULL, " \n\t"); 
        if (!tk) continue;
        
        tk = strtok(NULL, " \n\t"); 
        if (!tk) continue;
        int fileBus = atoi(tk);
        if (fileBus != busNo) continue;

        
        tk = strtok(NULL, " \n\t"); 
        if (!tk) continue;
        tk = strtok(NULL, " \n\t"); 
        if (!tk) continue;
        tk = strtok(NULL, " \n\t"); 
        
        while ((tk = strtok(NULL, " \n\t")) != NULL) {
            int seat = atoi(tk);
            if (seat <= 0) continue;
           
            int dup = 0;
            for (int i = 0; i < *bookedCount; i++) {
                if (bookedSeats[i] == seat) { dup = 1; break; }
            }
            if (!dup && *bookedCount < 200) { 
                bookedSeats[*bookedCount] = seat;
                (*bookedCount)++;
            }
        }
    }

    fclose(bf);
}

// view seat func

void ViewSeat(int busNo) {
    char busClass[32];
    char timeName[32];
    getBusInfo(busNo, busClass, timeName);

    int bookedSeats[200];
    int bookedCount = 0;
    loadBookedSeats(busNo, bookedSeats, &bookedCount);

    showSeatPreview(busClass, bookedSeats, bookedCount);
}

// reserve ticket func 

void ReserveTicket()
{
    char username[50];
    char date[12];
    int busNo;
    int numSeats;

    pd payment;  
    strcpy(payment.payment_status, "Pending");

    printf("\n--- Ticket Reservation Section ---\n");


    clearInputBuffer();
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    
    
    printf("Enter date(dd/mm/yyyy): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';


    BusAvail();

    // Ask for bus number with validation
    while (1) {
        
        printf("\nEnter Bus Number you want to book (or 0 to cancel): ");
        if (scanf("%d", &busNo) != 1) {
            printf("Invalid input. Please enter numeric bus number.\n");
            clearInputBuffer();
            continue;
        }
        if (busNo == 0) {
            printf("Reservation cancelled by user.\n");
            return;
        }
        if (!isValidBusNo(busNo)) {
            printf("Bus number %d not found. Please choose a valid bus number from schedule.\n", busNo);
            continue;
        }
        break;
    }

    // Ask for number of seats
    while (1) {
        printf("Enter number of seats: ");
        if (scanf("%d", &numSeats) != 1) {
            printf("Invalid input. Enter a numeric value.\n");
            clearInputBuffer();
            continue;
        }
        if (numSeats <= 0 || numSeats > 10) { 
            printf("Enter a positive number of seats (max 10).\n");
            continue;
        }
        break;
    }

    clearInputBuffer();

    // Determine class/time from bus number 
    char className[32];
    char timeName[32];
    getBusInfo(busNo, className, timeName);

    // Load booked seats for this bus and show seat map
    int bookedSeats[200];
    int bookedCount = 0;
    loadBookedSeats(busNo, bookedSeats, &bookedCount);

    printf("\nBus selected: %d\n", busNo);
    printf("Class: %s, Time: %s\n", className, timeName);
    showSeatPreview(className, bookedSeats, bookedCount);

    // Decide seat count based on class layout
    int maxSeats = 40; // Business/Premium default
    if (strcmp(className, "VIP/Sleeper") == 0 || strcmp(className, "VIP") == 0 || strcmp(className, "Sleeper") == 0) {
        maxSeats = 16;
    } else {
        maxSeats = 40;
    }

    // Seat selection by user
    int chosenSeats[20];
    int chosenCount = 0;
    while (chosenCount < numSeats) {
        int s;
        printf("Enter seat number to choose (%d of %d): ", chosenCount+1, numSeats);
        if (scanf("%d", &s) != 1) {
            printf("Invalid input. Enter numeric seat number.\n");
            clearInputBuffer();
            continue;
        }
        if (s < 1 || s > maxSeats) {
            printf("Seat number must be between 1 and %d.\n", maxSeats);
            continue;
        }
        // check already booked
        int alreadyBooked = 0;
        for (int i = 0; i < bookedCount; i++) {
            if (bookedSeats[i] == s) { alreadyBooked = 1; break; }
        }
        if (alreadyBooked) {
            printf("Seat %d is already booked. Choose another seat.\n", s);
            continue;
        }
        // check duplicate selection by this user
        int dup = 0;
        for (int i = 0; i < chosenCount; i++) if (chosenSeats[i] == s) { dup = 1; break; }
        if (dup) {
            printf("You already selected seat %d. Pick a different seat.\n", s);
            continue;
        }
        // accept seat
        chosenSeats[chosenCount++] = s;
        printf("Seat %d reserved temporarily.\n", s);
    }

    // Show chosen seats
    printf("\nSeats requested: %d\n", numSeats);
    printf("Chosen seats: ");
    for (int i = 0; i < chosenCount; i++) {
        printf("%d", chosenSeats[i]);
        if (i < chosenCount-1) printf(" // ");
    }
    printf("\n");

    // Call makePayment() with predetermined code
    makePayment(&payment);

    if (strcmp(payment.payment_status, "Complete") != 0) {
        printf("Payment incomplete. Reservation aborted.\n");
        printf("Press any key to return to User Menu...");
        getch();
        return;
    }

    // Record booking to file (append simple text record)
    FILE *bf = fopen("bookings.txt", "a");
    if (bf == NULL) {
        printf("Error opening bookings file. Reservation failed.\n");
    } else {
        fprintf(bf, "%s %s %d %d %s %s", username, date, busNo, numSeats, className, timeName);
        for (int s = 0; s < chosenCount; s++) fprintf(bf, " %d", chosenSeats[s]);
        fprintf(bf, "\n");
        fclose(bf);
        printf("\nReservation complete! Booking saved.\n");
    }

    printf("Press any key to continue...");
    getch();
}

//payment func 

void Payment()
{
    int choice;
    printf("\n--- Payment Section ---\n");
    printf("Please choose payment method:\n");
    printf("1. Mobile Banking (Bkash, Nagad, Rocket)\n");
    printf("2. Card Payment\n");
    printf(">> ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Defaulting to Mobile Banking.\n");
        clearInputBuffer();
        choice = 1;
    }

    switch (choice)
    {
        case 1:
            printf("\nPayment selected: Mobile Banking.\n");
            printf("Processing mobile payment...\n");
            break;
        case 2:
            printf("\nPayment selected: Card Payment.\n");
            printf("Processing card payment...\n");
            break;
        default:
            printf("\nInvalid payment option! Defaulting to Mobile Banking.\n");
            printf("Processing mobile payment...\n");
            break;
    }

    printf("\nPayment successful!\n");
    printf("Press any key to continue...");
    getch(); 
}

// Payment function with predetermined code 1234

void makePayment(pd *passdetails)
{
    int choice;
    char code[8] = {0};
    int i = 0;
    char c;

    printf("\n\n===================================\n");
    printf("\t    TICKET PAYMENT SECTION\n");
    printf("===================================\n");
    printf("Your current payment status is: %s\n", passdetails->payment_status);

    if (strcmp(passdetails->payment_status, "Complete") == 0) {
        printf("Payment is already complete. Skipping payment.\n");
        printf("Press any key to continue...");
        getch();
        return;
    }

    printf("\nSelect a payment method:\n");
    printf("1. Mobile Banking (Bkash, Nagad, Rocket)\n");
    printf("2. Card Payment (Visa, MasterCard)\n");
    printf("Enter your choice (1-2):> ");

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 2) {
        while (getchar() != '\n');
        printf("\nInvalid choice. Payment cancelled.\n");
        getch();
        return;
    }

    printf("\nSelected: ");
    switch(choice) {
        case 1: printf("Mobile Banking"); break;
        case 2: printf("Card Payment"); break;
    }

    printf("\n\nEnter the 4-digit payment code (Predetermined code is 1234):> ");

    fflush(stdin);
    i = 0;
    while (i < 4) {
        c = getch();
        if (c == 13) break; 
        if (c >= '0' && c <= '9') {
            code[i] = c;
            printf("*");
            i++;
        }
    }
    code[i] = '\0';

    if (strcmp(code, "1234") == 0) {
        printf("\n\n--- PAYMENT SUCCESSFUL ---\n");
        printf("---Thank you for choosing us---\n\n");
        strcpy(passdetails->payment_status, "Complete");
    } else {
        printf("\n\n--- INVALID CODE. PAYMENT FAILED. ---\n");
        printf("Payment status remains: %s\n", passdetails->payment_status);
    }

    printf("Press any key to continue...");
    getch();
}

// cancel ticket func 

void CancelTicket()
{
    char username[50];
    int busNo;
    char confirm;

    printf("\n--- Ticket Cancellation Section ---\n");

    clearInputBuffer();
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Bus Number of the ticket to cancel: ");
    if (scanf("%d", &busNo) != 1) {
        printf("Invalid bus number.\n");
        clearInputBuffer();
        return;
    }
    printf("Are you sure you want to cancel ticket for Bus %d? (Y/N): ", busNo);
    clearInputBuffer();
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
    
        FILE *in = fopen("bookings.txt", "r");
        FILE *out = fopen("bookings_tmp.txt", "w");
        if (in == NULL) {
            printf("No bookings found.\n");
        } else {
            char line[512];
            int cancelled = 0;
            while (fgets(line, sizeof(line), in)) {
             
                char fileUser[50];
                int fileBus;
                if (sscanf(line, "%s %*s %d", fileUser, &fileBus) >= 2) {
                    if (strcmp(fileUser, username) == 0 && fileBus == busNo) {
                        cancelled = 1;
                        continue; 
                    }
                }
                fputs(line, out);
            }
            fclose(in);
            fclose(out);
            remove("bookings.txt");
            rename("bookings_tmp.txt", "bookings.txt");
            if (cancelled)
                printf("\nTicket for user %s on Bus %d has been cancelled.\n", username, busNo);
            else
                printf("\nNo matching booking found for user %s on Bus %d.\n", username, busNo);
        }
    } else {
        printf("\nTicket cancellation aborted.\n");
    }

    printf("Press any key to return to User Menu...");
    getch();
}

//view ticket func 

void ViewTicket()
{
    char username[50];

    printf("\n--- View Tickets Section ---\n");


    clearInputBuffer();
    printf("Enter your username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    FILE *bf = fopen("bookings.txt", "r");
    if (bf == NULL) {
        printf("No bookings found.\n");
        printf("Press any key to return to User Menu...");
        getch();
        return;
    }

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), bf)) {
       
        char fileUser[50], fileDate[12], className[50], timeName[50]; 
        int fileBus, fileNumSeats;
        char *p = line;
        
        if (sscanf(line, "%s %s %d %d %s %s", fileUser, fileDate, &fileBus, &fileNumSeats, className, timeName) < 6) continue;
        
        if (strcmp(fileUser, username) == 0) {
            found = 1;
           
            int seats[20];
            int seatCount = 0;
            char copy[512];
            strcpy(copy, line);
            char *tk = strtok(copy, " \n\t");
            int tokenIdx = 0;
            while (tk != NULL) {
                tokenIdx++;
              
                if (tokenIdx >= 7) { 
                    int seat = atoi(tk);
                    if (seat > 0 && seatCount < 20) {
                        seats[seatCount++] = seat;
                    }
                }
                tk = strtok(NULL, " \n\t");
            }
           
            if (seatCount == 0) {
                 strcpy(copy, line);
                 tk = strtok(copy, " \n\t"); 
                 for (int i = 0; i < 5; i++) tk = strtok(NULL, " \n\t"); 
                 
                 while (tk != NULL && seatCount < 20) {
                    tk = strtok(NULL, " \n\t");
                    if (tk != NULL) {
                        int seat = atoi(tk);
                        if (seat > 0 && seatCount < 20) {
                            seats[seatCount++] = seat;
                        }
                    }
                 }
            }


            // Print a formatted ticket preview
            printf("==========================================\n");
            printf("     TICKET PREVIEW FOR %s\n", fileUser);
            printf("==========================================\n");
            printf("| Name: %s\n", fileUser);
            printf("| Date: %s\n", fileDate);
            
            // Map bus number to name/time for nicer display 
            char busName[50] = "Unknown";
            char busTime[20] = "Unknown";
            if (fileBus == 4001) { strcpy(busName, "Night Rider"); strcpy(busTime, "11.45pm"); }
            else if (fileBus == 1001) { strcpy(busName, "Royal Express"); strcpy(busTime, "7:00 AM"); }
            else if (fileBus == 1002) { strcpy(busName, "Sundarban Travels"); strcpy(busTime, "8:00 AM"); }
            else if (fileBus == 1003) { strcpy(busName, "Star Line"); strcpy(busTime, "9:00 AM"); }
            else if (fileBus == 2001) { strcpy(busName, "Royal Express"); strcpy(busTime, "1:00 PM"); }
            else if (fileBus == 2002) { strcpy(busName, "Sundarban Travels"); strcpy(busTime, "2:30 PM"); }
            else if (fileBus == 2003) { strcpy(busName, "Star Line"); strcpy(busTime, "4:00 PM"); }
            else if (fileBus == 3001) { strcpy(busName, "Royal Express"); strcpy(busTime, "7:30 PM"); }
            else if (fileBus == 3002) { strcpy(busName, "Sundarban Travels"); strcpy(busTime, "9:00 PM"); }
            else if (fileBus == 3003) { strcpy(busName, "Star Line"); strcpy(busTime, "9:40 PM"); }

            printf("| Bus name(no): %s(%d)\n", busName, fileBus);
            printf("| Time: %s\n", busTime);

           
            if (seatCount > 0) {
                printf("| Seats no.: ");
                for (int i = 0; i < seatCount; i++) {
                    printf("%d", seats[i]);
                    if (i < seatCount-1) printf(" // ");
                }
                printf("\n");
            } else {
                
                printf("| Seats no.: ");
                for (int i = 1; i <= fileNumSeats; i++) {
                    printf("%d", i);
                    if (i < fileNumSeats) printf(" // ");
                }
                printf("\n");
            }

            printf("-------------------------------------------\n\n");
        }
    }

    fclose(bf);

    if (!found) {
        printf("No tickets found for user %s\n", username);
    }

    printf("Press any key to return to User Menu...");
    getch();
}

void showSeatPreview(char *busClass, int bookedSeats[], int bookedCount)
{
    int number = 1;

    printf("\nSeat layout for %s class:\n\n", busClass);

    if (strcmp(busClass, "Business") == 0 || strcmp(busClass, "Premium") == 0) {
       
        for (int row = 0; row < 4; row++) {
            if (row == 2) printf("   AISLE GAP\n"); 
            for (int col = 0; col < 10; col++) {
                int isBooked = 0;
                for (int b = 0; b < bookedCount; b++) {
                    if (bookedSeats[b] == number) { isBooked = 1; break; }
                }
                if (isBooked)
                    printf("[ X] ");
                else
                    printf("[%2d] ", number);
                number++;
            }
            printf("\n");
        }
    }
    else if (strcmp(busClass, "VIP") == 0 || strcmp(busClass, "VIP/Sleeper") == 0 || strcmp(busClass, "Sleeper") == 0) {
     
        for (int row = 0; row < 2; row++) {
            if (row == 1) printf("   AISLE GAP\n"); 
            for (int col = 0; col < 8; col++) {
                int isBooked = 0;
                for (int b = 0; b < bookedCount; b++) {
                    if (bookedSeats[b] == number) { isBooked = 1; break; }
                }
                if (isBooked)
                    printf("[ X] ");
                else
                    printf("[%2d] ", number);
                number++;
            }
            printf("\n");
        }
    }
    else {
        printf("Unknown class!\n");
    }

    printf("\n");
}

//check user unfo func.
// simple display of users file for admin
void checkUserinfo() {
 
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("No users found.\n");
    } else {
        char name[50];
        int pass;
        printf("\nUser list:\n");
        while (fscanf(fp, "%s %d", name, &pass) != EOF) {
            printf("Username: %s  Password: %d\n", name, pass);
        }
        fclose(fp);
    }
    printf("Press any key to return to Admin Menu...");
    getch();
}
