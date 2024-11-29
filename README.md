# 🏦 Bank (Extension_1) 💼

> **A simple console-based application to manage client data with file storage and intuitive operations. 🛠️**

---

## 🌟 Project Overview
Welcome to the **Bank Management System** - a powerful C++ application for managing client accounts and transactions!🚀

---

## ✨ Features

### 📋 Client Management
- ➕ **Add New Clients**: Input details such as account number, name, phone number, PIN, and balance.
- 📝 **Update Client Details**: Modify existing records like names, phone numbers, and balances.
- ❌ **Delete Clients**: Remove clients from the system by specifying their account number.
- 🔍 **Search for Clients**: Easily locate clients by account number and display their details.
- 🗂️ **View All Clients**: Display a comprehensive list of all clients in the system.

### 💸 Transactions
- 💰 **Deposit Funds**: Add money to client accounts and log deposits.
- 💳 **Withdraw Money**: Deduct funds, ensuring sufficient balance.
- 📊 **View Total Balances**: Show overall bank holdings.

### 🔒 Data Security
- **Persistent Storage**: Client data is securely stored in `Client.txt` for future use.
- **Validation**: Enforce unique account numbers and accurate data entry.
- **Simple File-Based Database**: Efficiently manage all client and transaction data.

---

## ⚙️ Technologies Used

- **Language**: C++
- **Programming Paradigm**: Procedural
- **File Handling**: File I/O for data persistence
- **Data Structures**: Vectors for dynamic client management

---


## ⚙️ How It Works

### Core Components
1. **User Input**:
   - Administrators interact with a console-based menu to select operations like Add, Update, Delete, Deposit, Withdraw, and View Transaction History.
   - All user inputs are validated before being processed.

2. **Operations**:
   - **Add Clients**: Administrators can enter new client details, including initial balance.
   - **Update Records**: Modify client details, such as changing names, updating contact information, or adjusting balances.
   - **Delete Clients**: Remove client records based on the account number.
   - **Search Clients**: Retrieve a client's information by entering their account number.
   - **View All Clients**: Display a complete list of all client records stored in the system.
   - **Deposit**: Increase a client's balance by depositing funds into their account. Each deposit is recorded with the date, amount, and transaction type.
   - **Withdraw**: Withdraw funds from a client’s account, ensuring that the balance is sufficient. Withdrawals are recorded in the transaction history.

3. **File Management**:
   - Client data and transaction histories are stored in `Client.txt`, using delimiters for easy parsing.
   - Efficient file handling ensures data is accurately read, written, and updated in the text file.

4. **Menu Navigation**:
   - The menu offers easy navigation between operations, including options to add clients, perform transactions, view transaction history, and exit the program.
   - Users can also return to previous menus at any point.

---

## 🎯 Learning Outcomes

This project demonstrates several key C++ programming concepts:
- ✅ **File Handling**: Learn to store and retrieve data using file I/O operations, ensuring persistence.
- ✅ **Modular Design**: Functions are used for each operation, making the code organized and reusable.
- ✅ **Error Handling**: Input validation and error checking ensure the integrity of data and smooth user experience.
- ✅ **Control Structures**: Utilize loops, conditionals, and switch statements for handling complex logic.
- ✅ **Transaction Management**: Efficiently manage both deposit and withdrawal transactions, and maintain a full history of all financial activities.

---

## 🏁 Ready to Explore?

### 🚀 How to Run
1. **Download** the repository to your local machine.
2. **Compile** the C++ code using your favorite IDE or compiler (e.g., `g++` in terminal).
3. **Run** the compiled program and begin managing client data and transactions with ease!


