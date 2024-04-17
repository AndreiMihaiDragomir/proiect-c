#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"
#include "product.h"
#include "user.h"
void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Properly clear the buffer
}

void exitShop(){
    printf("Thank you for using the Online Shop. Goodbye!\n");
    exit(0); // Exit the program
}

// Function prototypes assuming updated signatures
void loginUser(const char *username, const char *password, int *loggedIn);
void createAccount(const char *username, const char *password);
void addProduct(const char *name, int quantity, double price);
void placeOrder(int code, const char *productName, int quantity, double paidAmount, const char *userName, const char *userSurname);
void viewOrders(const char *userName, const char *userSurname);
void searchProductByName(const char *name);
void searchProductByPrice(double minPrice, double maxPrice);
void searchProductByNameAndPrice();
void loadProducts();
void saveProducts();
void clearInputBuffer();
void exitShop();


int main() {

    int loggedIn = 0;
    int option, result;
    char
    input[100], loginName[100], loginSurname[100];

    while (!loggedIn) {
        printf("Welcome to EMAG\n");
        printf("1.Login\n");
        printf("2.Create a new account\n");
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin); // Read the whole line
        result = sscanf(input, "%d", &option); // Safely parse integer

        if (result < 1) {
            // Check if conversion failed
            printf("Invalid input. Please choose an option between 1 and 2.\n");
            continue; // Skip the rest of the loop
        }
        switch (option){
            case 1:
                printf("Enter name: ");
                fgets(loginName, sizeof(loginName), stdin);
                loginName[strcspn(loginName, "\n")] = 0;  // Remove newline
                printf("Enter surname: ");
                fgets(loginSurname, sizeof(loginSurname), stdin);
                loginSurname[strcspn(loginSurname, "\n")] = 0;  // Remove newline
                loginUser(loginName, loginSurname, &loggedIn);
                break;
            case 2:
                printf("Enter your name: ");
                fgets(loginName, sizeof(loginName), stdin);
                loginName[strcspn(loginName, "\n")] = 0;  // Remove newline
                printf("Enter your surname: ");
                fgets(loginSurname, sizeof(loginSurname), stdin);
                loginSurname[strcspn(loginSurname, "\n")] = 0;  // Remove newline
                createAccount(loginName, loginSurname);
                break;
            default:
                printf("Invalid choice. Please choose an option between 1 and 2.\n");
        }
    }

    while (1) {
        printf("\nEmag Main Menu\n");
        printf("1.Add a product\n");
        printf("2.Place an order\n");
        printf("3.View orders\n");
        printf("4.Search for a product by name\n");
        printf("5.Search for a product by price\n");
        printf("6.Search for a product by name and price\n");
        printf("7.Exit\n");
        printf("Enter your choice: ");

        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &option) != 1) {
            printf("Invalid choice. Please choose from the options listed 1 to 7.\n");
            continue;
        }

        switch (option) {
            case 1: {
                char name[100];
                int quantity;
                double price;
                printf("Enter product name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;  // Remove newline character
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                printf("Enter price: ");
                scanf("%lf", &price);
                clearInputBuffer();
                addProduct(name, quantity, price);
                break;
            }
            case 2: {
                int orderCode;
                char productName[100];
                int quantity;
                char userName[100];
                char userSurname[100];
                double totalAmount;
                printf("Enter order code: ");
                scanf("%d", &orderCode);
                clearInputBuffer();
                printf("Enter product name: ");
                fgets(productName, sizeof(productName), stdin);
                productName[strcspn(productName, "\n")] = 0;
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                printf("Enter total amount paid: ");
                scanf("%lf", &totalAmount);
                clearInputBuffer();
                placeOrder(orderCode, productName, quantity, totalAmount, userName, userSurname);
                break;
            }
            case 3: {
                char userName[100];
                char userSurname[100];
                printf("Enter user's first name: ");
                fgets(userName, sizeof(userName), stdin);
                userName[strcspn(userName, "\n")] = 0;
                printf("Enter user's surname: ");
                fgets(userSurname, sizeof(userSurname), stdin);
                userSurname[strcspn(userSurname, "\n")] = 0;
                viewOrders(userName, userSurname);
                break;
            }
            case 4: {
                char name[100];
                printf("Enter product name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                searchProductByName(name);
                break;
            }
            case 5: {
                double minPrice, maxPrice;
                printf("Enter minimum price: ");
                scanf("%lf", &minPrice);
                printf("Enter maximum price: ");
                scanf("%lf", &maxPrice);
                clearInputBuffer();
                searchProductByPrice(minPrice, maxPrice);
                break;
            }
            case 6: {
                char name[100];
                double minPrice, maxPrice;
                printf("Enter product name to search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Enter minimum price: ");
                scanf("%lf", &minPrice);
                printf("Enter maximum price: ");
                scanf("%lf", &maxPrice);
                clearInputBuffer();
                searchProductByNameAndPrice(name, minPrice, maxPrice);
                break;
            }
            case 7:
                exitShop();
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    }
}