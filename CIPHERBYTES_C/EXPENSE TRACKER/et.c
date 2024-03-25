#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INITIAL_CAPACITY 10
#define MAX_CATEGORY_LENGTH 100
#define DATETIME_LENGTH 20

// Structure to represent an expense
struct Expense {
    char category[MAX_CATEGORY_LENGTH];
    float amount;
    char datetime[DATETIME_LENGTH];
};

// Global variables
struct Expense* expenses = NULL;
int expenseCount = 0;
int capacity = 0;

// Function to add an expense with date and time
void addExpense() {
    float amount;
    time_t now;
    struct tm* localTime;

    // Check if expenses array needs to be resized
    if (expenseCount >= capacity) {
        int newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
        struct Expense* temp = realloc(expenses, newCapacity * sizeof(struct Expense));
        if (temp == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        expenses = temp;
        capacity = newCapacity;
    }

    // Input category
    printf("Enter category: ");
    fgets(expenses[expenseCount].category, MAX_CATEGORY_LENGTH, stdin);
    expenses[expenseCount].category[strcspn(expenses[expenseCount].category, "\n")] = '\0'; // Remove trailing newline if present

    // Input amount
    printf("Enter amount: ");
    scanf("%f", &amount);
    while (getchar() != '\n'); // Clear input buffer

    // Get current date and time
    time(&now);
    localTime = localtime(&now);
    strftime(expenses[expenseCount].datetime, DATETIME_LENGTH, "%Y-%m-%d %H:%M:%S", localTime);

    expenses[expenseCount].amount = amount;
    expenseCount++;

    printf("Expense added successfully.\n");
}

// Function to display all expenses
void displayExpenses() {
    if (expenseCount == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("\nExpenses:\n");
    printf("%-20s%-15s%-10s\n", "Datetime", "Category", "Amount");
    printf("--------------------------------------------\n");

    for (int i = 0; i < expenseCount; i++) {
        printf("%-20s%-15s%-10.2f\n", expenses[i].datetime, expenses[i].category, expenses[i].amount);
    }
}

// Function to compute total expenses
float computeTotalExpenses() {
    float total = 0;
    for (int i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
    }
    return total;
}

// Function to display total expenses
void displayTotalExpenses() {
    printf("\nTotal expenses: %.2f\n", computeTotalExpenses());
}

// Function to free allocated memory
void cleanup() {
    free(expenses);
}

// Main function
int main() {
    int choice;

    // Allocate memory for expenses
    expenses = malloc(INITIAL_CAPACITY * sizeof(struct Expense));
    if (expenses == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    capacity = INITIAL_CAPACITY;

    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. Display Expenses\n");
        printf("3. Display Total Expenses\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n'); // Clear input buffer

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                displayExpenses();
                break;
            case 3:
                displayTotalExpenses();
                break;
            case 4:
                printf("Exiting Expense Tracker.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    // Clean up allocated memory
    cleanup();

    return 0;
}
