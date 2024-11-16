#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iomanip>

using namespace std;

const string FileName = "Client.txt";

void Show_Main_Menue_Screen();
void Show_Transactions_Menue_Screen();

enum enMain_Menue_Option {
    eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClientInfo = 4, eFindClient = 5, Transactions = 6, eExit = 7
};


struct stClient
{
    string Account_Number;
    string PIN_Code;
    string Name;
    string Phone;
    double Account_Balance;
    bool Make_For_Delete = false;
};


vector <string> Split_String(string S1, string Delimiter = "#//#") {

    short Pos;
    string Word;

    vector <string> vString;

    while ((Pos = S1.find(Delimiter)) != std::string::npos) {

        Word = S1.substr(0, Pos);

        if (Word != "")
        {
            vString.push_back(Word);
        }

        S1.erase(0, Pos + Delimiter.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}



stClient Convert_LineData_To_Record(string Line, string Delimiter = "#//#") {

    vector<string> vRecord = Split_String(Line);
    stClient Client;

    Client.Account_Number = vRecord[0];
    Client.PIN_Code = vRecord[1];
    Client.Name = vRecord[2];
    Client.Phone = vRecord[3];
    Client.Account_Balance = stod(vRecord[4]); //Cast String To Double

    return Client;
}


vector <stClient> Load_Client_Data_From_File(string FileName) {

    fstream My_File;

    vector <stClient> vClient;
    string Line;
    stClient Client;

    My_File.open(FileName, ios::in);  // Read Mode

    if (My_File.is_open())
    {
        while (getline(My_File, Line)) {

            Client = Convert_LineData_To_Record(Line);
            vClient.push_back(Client);
        }

        My_File.close();
    }

    return vClient;
}



void Print_Client_Record_Line(stClient Client) {

    cout << left << "|" << setw(15) << Client.Account_Number;
    cout << left << "|" << setw(10) << Client.PIN_Code;
    cout << left << "|" << setw(38) << Client.Name;
    cout << left << "|" << setw(12) << Client.Phone;
    cout << left << "|" << setw(12) << Client.Account_Balance;
}



void Show_Client_List() {

    vector <stClient> vClient = Load_Client_Data_From_File(FileName);

    cout << "\t\t\t Client List (" << vClient.size() << ") Client(s). \n";

    cout << "\n----------------------------------------------------------------------------------------\n";
    cout << left << "|" << setw(15) << "Account Number";
    cout << left << "|" << setw(10) << "PIN Code";
    cout << left << "|" << setw(38) << "Client Name";
    cout << left << "|" << setw(12) << "Phone";
    cout << left << "|" << setw(12) << "Balance";

    cout << "\n----------------------------------------------------------------------------------------\n";

    if (vClient.size() == 0)
    {
        cout << "\n\n\t\t\t No Clients Available in The System! ";
    }
    else
    {
        for (stClient& Client : vClient)
        {
            Print_Client_Record_Line(Client);
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------------------------------------------------\n";
}




string Convert_RecordData_To_Line(stClient Client, string Delimiter = "#//#") {

    string Line = "";

    Line += Client.Account_Number + Delimiter;
    Line += Client.PIN_Code + Delimiter;
    Line += Client.Name + Delimiter;
    Line += Client.Phone + Delimiter;
    Line += to_string(Client.Account_Balance);

    return Line;
}


bool Client_Exists_By_Account_Number(string Account_Number, string FileName) {

    fstream My_File;

    My_File.open(FileName, ios::in); // Read Mode

    if (My_File.is_open())
    {
        string Line;
        stClient Client;

        while (getline(My_File, Line)) {

            Client = Convert_LineData_To_Record(Line);

            if (Client.Account_Number == Account_Number)
            {
                My_File.close();
                return true;
            }

        }
        My_File.close();
    }

    return false;
}



stClient Read_NewClient_Info() {

    stClient Client;

    cout << "\nEnter Account Number? ";
    getline(cin >> ws, Client.Account_Number);


    while (Client_Exists_By_Account_Number(Client.Account_Number, FileName)) {

        cout << "\nClient With [" << Client.Account_Number << "] Already Exists! Enter Another Account Number? ";
        getline(cin >> ws, Client.Account_Number);
    }


    cout << "\nEnter PIN Code? ";
    getline(cin, Client.PIN_Code);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.Account_Balance;


    return Client;
}


void Add_DataLine_To_File(string FileName, string Line) {

    fstream My_File;

    My_File.open(FileName, ios::out | ios::app);

    if (My_File.is_open())
    {
        My_File << Line << endl;

        My_File.close();
    }
}


void Add_Client() {

    stClient Client = Read_NewClient_Info();

    Add_DataLine_To_File(FileName, Convert_RecordData_To_Line(Client));
}




void Add_New_Client() {

    char Answer = 'Y';

    do
    {

        cout << "Adding New Client : \n\n";

        Add_Client();

        cout << "\nClient Added Successfully, Do U Want To Add More Client ? (Y/N) ";
        cin >> Answer;

    } while (toupper(Answer) == 'Y');

}

void Show_Add_New_Clients_Screen() {


    cout << "\n----------------------------------------------\n";
    cout << "\t\t Add New CLients Screen ";
    cout << "\n----------------------------------------------\n";

    Add_New_Client();

}




vector <stClient> Save_ClientData_To_File(string FileName, vector<stClient> vClient) {

    fstream My_File;
    string Line;

    My_File.open(FileName, ios::out);

    if (My_File.is_open())
    {
        for (stClient& Client : vClient)
        {
            if (Client.Make_For_Delete == false) {

                Line = Convert_RecordData_To_Line(Client);
                My_File << Line << endl;
            }
        }

        My_File.close();
    }
    return vClient;
}



bool Find_Client_By_Account_Number(string Account_Number, vector <stClient> vClient, stClient& Client_Info) {

    for (stClient& Client : vClient)
    {
        if (Client.Account_Number == Account_Number) {

            Client_Info = Client;
            return true;
        }
    }
    return false;
}



bool Mark_Client_For_Delete_By_Account_Number(string Account_Number, vector<stClient>& vClient) {

    for (stClient& Client : vClient)
    {
        if (Client.Account_Number == Account_Number) {

            Client.Make_For_Delete = true;
            return true;
        }
    }
    return false;
}



string Read_Account_Number() {
    string Account_Number;

    cout << "\nPlease Enter Account Number : ";
    cin >> Account_Number;

    return Account_Number;
}


void Print_Client_Card(stClient Client) {

    cout << "\nThe Following Are The Client Details : \n";

    cout << "\n----------------------------------------------\n";
    cout << "Account Number      : " << Client.Account_Number << endl;
    cout << "PIN Code            : " << Client.PIN_Code << endl;
    cout << "Name                : " << Client.Name << endl;
    cout << "Phone               : " << Client.Phone << endl;
    cout << "Account Balance     : " << Client.Account_Balance << endl;
    cout << "\n----------------------------------------------\n";
}

bool Delete_Client_By_Account_Number(string Account_Number, vector <stClient>& vClient) {

    stClient Client;
    char Answer = 'n';

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);

        cout << "\n\nAre U Sure U Want Delete This Account :(Y/N) ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            Mark_Client_For_Delete_By_Account_Number(Account_Number, vClient);
            Save_ClientData_To_File(FileName, vClient);

            // Refresh
            vClient = Load_Client_Data_From_File(FileName);

            cout << "\n\nClient Deleted Successfully! ";
            return true;
        }
    }

    else
    {
        cout << "\nClient With Account Number [" << Account_Number << "] Not Found! ";
        return false;
    }

}


void Show_Delete_Client_Screen() {

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Delete Client Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Account_Number();
    vector <stClient> vClient = Load_Client_Data_From_File(FileName);


    Delete_Client_By_Account_Number(Account_Number, vClient);
}





stClient Edit_Client_Info(string Account_Number) {

    stClient Client;

    Client.Account_Number = Account_Number;

    cout << "\nEnter  PIN Code : ";
    getline(cin >> ws, Client.PIN_Code);

    cout << "\nEnter Name : ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone : ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance : ";
    cin >> Client.Account_Balance;

    return Client;
}


bool Update_Client_Info_By_Account_Number(string Account_Number, vector<stClient>& vClient) {

    char Answer = 'n';
    stClient Client;

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);

        cout << "\nAre U Sure U Want Update This Client? (Y/N) ";
        cin >> Answer;

        if (toupper(Answer) == 'Y')
        {
            for (stClient& C : vClient)
            {
                if (C.Account_Number == Account_Number)
                {
                    C = Edit_Client_Info(Account_Number);
                    break;
                }
            }

            Save_ClientData_To_File(FileName, vClient);

            cout << "\n\nClient Updated Successfully! ";
            return true;
        }

    }
    else
    {
        cout << "\nClient With Account Number (" << Account_Number << ") Not Found! ";
        return false;
    }
}


void Show_Update_Client_Info_Screen() {


    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Update Client Info Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Account_Number();
    vector<stClient> vClient = Load_Client_Data_From_File(FileName);

    Update_Client_Info_By_Account_Number(Account_Number, vClient);
}







void Show_Find_Client_Screen() {


    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Find Client Screen ";
    cout << "\n--------------------------------------------------\n";

    string Account_Number = Read_Account_Number();
    vector <stClient> vClient = Load_Client_Data_From_File(FileName);

    stClient Client;

    if (Find_Client_By_Account_Number(Account_Number, vClient, Client))
    {
        Print_Client_Card(Client);
    }
    else
    {
        cout << "\nClient With Account Number [" << Account_Number << "] is Not Found! ";
    }
}



void Show_End_Screen() {

    cout << "\n--------------------------------------------------\n";
    cout << "\t\t Program Ends : -)";
    cout << "\n--------------------------------------------------\n";
}


void Go_Back_To_Main_Menue() {

    cout << "\n\n\nPress Any Key To Go Back To Main Menue...\n";
    system("pause>0");


    Show_Main_Menue_Screen();
}


short Read_Choice() {

    short Choice = 1;

    do
    {
        cout << "\nChoose What Do U want To Do Twiiha ? [1 => 7]? \n";
        cin >> Choice;

    } while (Choice < 1 || Choice > 7);


    return Choice;
}


void Perform_Main_Menue_Option(enMain_Menue_Option Option) {

    switch (Option)
    {

    case enMain_Menue_Option::eShowClientList:

        system("cls");
        Show_Client_List();
        Go_Back_To_Main_Menue();

        break;


    case enMain_Menue_Option::eAddNewClient:

        system("cls");
        Show_Add_New_Clients_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMain_Menue_Option::eDeleteClient:

        system("cls");
        Show_Delete_Client_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMain_Menue_Option::eUpdateClientInfo:

        system("cls");
        Show_Update_Client_Info_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMain_Menue_Option::eFindClient:

        system("cls");
        Show_Find_Client_Screen();
        Go_Back_To_Main_Menue();

        break;


    case enMain_Menue_Option::Transactions:

        Show_Transactions_Menue_Screen();

        break;


    case enMain_Menue_Option::eExit:

        system("cls");
        Show_End_Screen();

        break;
    }

}



enum enTransactions { Deposit = 1, Withdraw = 2, Total_Balances = 3, Main_Menue = 4 };

double Read_Deposit_Amount() {

    double Deposit = 0;

    cout << "\nPlease Enter Deposit Amount : ";
    cin >> Deposit;

    return Deposit;
}


bool Deposit_Balance_To_Client_By_Account_Number(string Account_Number, vector<stClient>& vClient, double Amount) {


    char Answer = 'n';

    cout << "\n\nAre U Sure U Want To Perform This Transaction? (Y/N) ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {

        for (stClient& Client : vClient)
        {
            if (Client.Account_Number == Account_Number) {

                Client.Account_Balance += Amount;
                Save_ClientData_To_File(FileName, vClient);

                cout << "\n\nDone Successfully, New Balance = " << Client.Account_Balance;

                return true;
            }
        }

        return false;
    }

}


void Show_Deposit_Screen() {

    cout << "\n=================================================\n";
    cout << "\t\t Deposit Screen";
    cout << "\n=================================================\n";

    vector <stClient> vClient = Load_Client_Data_From_File(FileName);
    stClient Client;
    string Account_Number = Read_Account_Number();


    while (!Find_Client_By_Account_Number(Account_Number, vClient, Client)) {

        cout << "\nClient With [" << Account_Number << "] Does Not Exist! \n";
        Account_Number = Read_Account_Number();
    }

    Print_Client_Card(Client);

    double Deposit_Amount = Read_Deposit_Amount();

    Deposit_Balance_To_Client_By_Account_Number(Account_Number, vClient, Deposit_Amount);
}




double Read_Withdraw_Amount() {

    double Withdraw = 0;

    cout << "\nPlease Enter Withdraw Amount : ";
    cin >> Withdraw;

    return Withdraw;
}


void Show_Withdraw_Screen() {

    cout << "\n=================================================\n";
    cout << "\t\t Withdraw Screen";
    cout << "\n=================================================\n";

    string Account_Number = Read_Account_Number();
    stClient Client;
    vector <stClient> vClient = Load_Client_Data_From_File(FileName);


    while (!Find_Client_By_Account_Number(Account_Number, vClient, Client)) {

        cout << "\nClient With [" << Account_Number << "] Does Not Exist! \n";

        Account_Number = Read_Account_Number();
    }

    Print_Client_Card(Client);

    double Withdraw_Amount = Read_Withdraw_Amount();


    while (Withdraw_Amount > Client.Account_Balance) {

        cout << "\nAmount Exceeds The Balance, U can Withdraw Up To : " << Client.Account_Balance;

        cout << "\nPlease Enter Another Amount : ";
        cin >> Withdraw_Amount;
    }


    Deposit_Balance_To_Client_By_Account_Number(Account_Number, vClient, Withdraw_Amount * -1);

}



void Print_Client_Record_Balance_Line(stClient Client) {

    cout << left << "| " << setw(18) << Client.Account_Number;
    cout << left << "| " << setw(28) << Client.Name;
    cout << left << "| " << setw(12) << Client.Account_Balance;
}



void Show_Total_Balances_Screen() {

    vector <stClient> vClient = Load_Client_Data_From_File(FileName);

    cout << "\n\t\t\t Balances List (" << vClient.size() << ") Client(s).";

    cout << "\n-------------------------------------------------------------\n";

    cout << left << "| " << setw(18) << " Account Number";
    cout << left << "| " << setw(28) << " Client Name";
    cout << left << "| " << setw(12) << " Balance";

    cout << "\n-------------------------------------------------------------\n";

    double Total_Balances = 0;

    if (vClient.size() == 0)
    {
        cout << "\n\n\t\t\t No Clients Available in The System! ";
    }

    else
    {

        for (stClient& Client : vClient)
        {
            Total_Balances += Client.Account_Balance;

            Print_Client_Record_Balance_Line(Client);
            cout << endl;
        }
    }

    cout << "\n-------------------------------------------------------------\n";

    cout << "\n\t\t\t  Total Balances = " << Total_Balances << endl;
}




void Go_Back_To_Transactions_Menue() {

    cout << "\n\n\nPress Any Key To Go Back To Transactions Menue...\n";
    system("pause>0");

    Show_Transactions_Menue_Screen();
}


void Perform_Transactions_Menue_Option(enTransactions Option) {

    switch (Option)
    {
    case enTransactions::Deposit:

        system("cls");
        Show_Deposit_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactions::Withdraw:

        system("cls");
        Show_Withdraw_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactions::Total_Balances:

        system("cls");
        Show_Total_Balances_Screen();
        Go_Back_To_Transactions_Menue();

        break;

    case enTransactions::Main_Menue:

        Show_Main_Menue_Screen();

        break;

    }

}



short Read_Transactions_Menue_Option() {

    short Choice = 1;

    do
    {
        cout << "\nChoose What Do U want To Do Twiiha ? [1 => 4]? \n";
        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return Choice;
}


void Show_Transactions_Menue_Screen() {

    system("cls");

    cout << "\n=================================================\n";
    cout << "\t\tTransactions Menue Screen";
    cout << "\n=================================================\n";


    cout << "\t [1] Deposit. \n";
    cout << "\t [2] Withdraw. \n";
    cout << "\t [3] Total balances. \n";
    cout << "\t [4] Main Menue. \n";

    cout << "\n=================================================\n";


    Perform_Transactions_Menue_Option((enTransactions)Read_Transactions_Menue_Option());
}



void Show_Main_Menue_Screen() {

    system("cls");

    cout << "\n=================================================\n";
    cout << "\t\tMain Menue Screen";
    cout << "\n=================================================\n";

    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions. \n";
    cout << "\t [7] Exit.";

    cout << "\n=================================================\n";

    Perform_Main_Menue_Option((enMain_Menue_Option)Read_Choice());
}


int main()
{
    system("color f3");

    Show_Main_Menue_Screen();

    system("pause>0");
    return 0;
}