#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>
#include <unordered_map>

#define MAX_ACCOUNTS 10

// Struct representing a bank account
struct BankAccount {
  std::string accountNumber;
  std::string accountHolder;
  double balance;
};

// Function to create a new bank account
void createAccount(std::unordered_map<std::string, BankAccount>& accounts) {
  if (accounts.size() >= MAX_ACCOUNTS) {
    std::cout << "Maximum number of accounts reached." << std::endl;
    return;
  }

  std::string number, holder;
  do {
    std::cout << "Enter account number: ";
    std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (accounts.find(number) != accounts.end()); // Check for unique account number

  std::cout << "Enter account holder name: ";
  std::getline(std::cin, holder);

  // Validate account holder name (not empty and doesn't contain invalid characters)
  if (holder.empty() || std::find_if(holder.begin(), holder.end(), [](char c) { return !isalnum(c) && c != ' '; }) != holder.end()) {
    std::cout << "Invalid account holder name. Please enter a valid name." << std::endl;
    return;
  }

  accounts[number] = {number, holder, 0.0}; // Add account to the map
  std::cout << "Account created successfully!" << std::endl;
}

// Function to perform deposit operation
void deposit(const std::string& accountNumber, std::unordered_map<std::string, BankAccount>& accounts) {
  auto it = accounts.find(accountNumber);
  if (it == accounts.end()) {
    std::cout << "Account not found." << std::endl;
    return;
  }

  double amount;
  std::cout << "Enter deposit amount: ";
  std::cin >> amount;

  // Validate deposit amount (positive value)
  if (amount <= 0) {
    std::cout << "Invalid deposit amount. Please enter a positive amount." << std::endl;
    return;
  }

  it->second.balance += amount; // Update account balance
  std::cout << "Deposit successful. Current balance: E" << it->second.balance << std::endl;
}

// Function to perform withdrawal operation
void withdraw(const std::string& accountNumber, std::unordered_map<std::string, BankAccount>& accounts) {
  auto it = accounts.find(accountNumber);
  if (it == accounts.end()) {
    std::cout << "Account not found." << std::endl;
    return;
  }

  double amount;
  std::cout << "Enter withdrawal amount: ";
  std::cin >> amount;

  // Validate withdrawal amount (positive value and not exceeding balance)
  if (amount <= 0 || amount > it->second.balance) {
    std::cout << "Insufficient funds or invalid amount." << std::endl;
    return;
  }

  it->second.balance -= amount; // Update account balance
  std::cout << "Withdrawal successful. Remaining balance: $" << it->second.balance << std::endl;
}

// Function to check account balance
void checkBalance(const std::string& accountNumber, const std::unordered_map<std::string, BankAccount>& accounts) {
  auto it = accounts.find(accountNumber);
  if (it == accounts.end()) {
    std::cout << "Account not found." << std::endl;
    return;
  }

  std::cout << "Current balance: $" << it->second.balance << std::endl;
}

// Main function
int main() {
  std::unordered_map<std::string, BankAccount> accounts;
  int choice;
  std::string accountNumber;

  do {
    std::cout << "\nBanking System Menu:\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Withdraw\n";
    std::cout << "4. Check Balance\n";
        std::cout << "5. Exit\n";
    std::cout << "Enter your choice (1-5): ";
    std::cin >> choice;

    switch (choice) {
      case 1:
        createAccount(accounts);
        break;

      case 2:
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        deposit(accountNumber, accounts);
        break;

      case 3:
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        withdraw(accountNumber, accounts);
        break;

      case 4:
        std::cout << "Enter account number: ";
        std::cin >> accountNumber;
        deposit(accountNumber, accounts);
        break;

      case 5:
        std::cout << "Thank you for using our banking system!" << std::endl;
        break;

      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
}
} while (choice != 5);

return 0;
}




