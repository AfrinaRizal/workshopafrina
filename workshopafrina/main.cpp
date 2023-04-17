#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql.h>



#pragma

using namespace std;

// Global Variable
int qstate;
int qstate1;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
// Global Variable End


string customerID, paymentID, ticketID, matchID, adminID;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
		{
			cout << "Database Connected" << endl;
			cout << "Press any key to continue..." << endl;
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
		conn = mysql_real_connect(conn, "localhost", "root", "", "workshopafrina", 3306, NULL, 0);
		if (conn)
		{
			cout << "Database Connected To MySql" << conn << endl;
			cout << "Press any key to continue..." << endl;
			system("cls");
		}
		else
			cout << "Failed To Connect!" << mysql_errno(conn) << endl;
	}
};


void Welcome() 
{
	cout << endl << "Welcome To Football Ticketing System" << endl << endl;

}


//Function Declaration
void Register();
void Login();
void AdminMenu();
void CustomerMenu();
void StaffMenu();
void Match();
void AddStaff();
void DeleteStaff();
void UpdateStaff();
void AddMatch();
void DeleteMatch();
void UpdateMatch();
void ListCustomer();
void ListMatch();
void BookTicket();
void DisplayChoice();
void Report();
void Staff();
void ListStaff();

//End Function Declaration


int main()
{
	system("cls");
	system("FOOTBALL TICKETING SYSTEM");
	system("color 06");
	db_response::ConnectionFunction();

	int chooseOneFromMenu = 0;

	cout << "====================================================================================================================" << endl;
	cout << "\n" << endl;
	cout <<"               -------------------     WELCOME TO STADIUM BUKIT JALIL, MALAYSIA       ----------------------          " << endl;
	cout << "\n" << endl;
	cout << "====================================================================================================================" << endl;
	cout <<"                                                      1. Login" << endl;
	cout <<"                                                      2. Register" << endl;
	cout <<"                                                      3. Exit" << endl;
	cout <<"                                                      Choose One: ";
	cin >> chooseOneFromMenu;

	switch (chooseOneFromMenu)
	{
	case 1:
		Login();
		break;
	case 2:
		Register();
		break;
	case 3:
		cout << "Program Exiting..." << endl;
		exit(0);
	default:
		cout << "Please choose between 1 , 2 , 3. Press Enter To Continue...";
		_getch; // get char // pause console // 
		system("cls"); // clear console
		main(); //
		break;
	}
	return 0;
}


void AdminMenu()
{
	system("cls");
	system("color 07");

	int choose;
	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                              ------   ADMIN MENU    ------                             " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "1. Staff" << endl;
	cout << "2. View the list of Customer" << endl;
	cout << "3. Sales Report" << endl;
	cout << "4. Exit" << endl;
	cout << "Please choose: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		Staff(); //function to insert new data
		break;
	case 2:
		ListCustomer();
		break;
	case 3:
		Report();
		break;
	case 4:
		exit(0);
		break;

	}
};

void StaffMenu()
{
	system("cls");
	system("color 07");

	int choose;
	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                              ------   STAFF MENU    ------                             " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "1. Match" << endl;
	cout << "2. Exit" << endl;
	cout << "Please choose: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		Match(); //function to insert new data
		break;
	case 2:
		exit(0);
		break;

	}
};

void CustomerMenu()
{
	system("cls");
	system("color 03");

	int choose;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                              ------   CUSTOMER MENU    ------                             " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "1. View the list of Ticket Price" << endl;
	cout << "2. Ticket Purchase" << endl;
	cout << "3. Exit" << endl;
	cout << "Please choose: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		DisplayChoice();//siap
		break;
	case 2:
		BookTicket();
		break;
	case 3:
		exit(0);
		break;

	}
	
};

//DONE
void Register()
{
	system("cls");
	string name, telno, username, password,customerIC,email,address;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                              ------   REGISTER    ------                                 " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;

	cout << "Enter Name: ";
	cin.ignore(1, '\n'); // ignore space as next line
	getline(cin, name); // include space in input
	cout << "Identification Number: ";
	getline(cin, customerIC);
	cout << "Enter Phone: ";
	getline(cin, telno);
	cout << "Address: ";
	getline(cin, address);
	cout << "Email: ";
	getline(cin, email);
	cout << "Enter Username: "; //should be unique
	getline(cin, username);
	cout << "Enter Password: ";
	getline(cin, password);

	// check username 
	string checkUser_query = "select * from customer where username = '" + username + "'"; //get the first line only
	//compare input dgn data dlm databse
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu); //execute query

	if (!qstate) //boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) //username exist
		{
			cout << "Username is already exist. Press Enter to Try Again...";
			_getch();
			Register();
		}
		else
		{
			string insertCustomer_query = "insert into customer (name, customerIC,telno,address,email, username, password) values ('" + name + "', '" + customerIC + "','" + telno + "','" + address + "','" + email + "','" + username + "', '" + password + "')";
			const char* q = insertCustomer_query.c_str(); // convert
			qstate = mysql_query(conn, q); //execute

			if (!qstate) //query boleh jalan
			{
				cout << endl << "You have been successfully registered. Press Enter to Continue...";
				_getch();
				main(); //go main function
			}
			else
			{
				cout << "Error" << endl;
			}
		}

	}

};


//DONE
void Login()
{
	system("cls");
	string username, password, adminID, customerID,staffID;
	char ch;
	int role = 0;

	cout << "========================================================================================" << endl;
	cout << "                              ------   LOG IN    ------                                 " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	do
	{
		cout << "\n		1. Admin " ;
		cout << "\n		2. Staff ";
		cout << "\n		3. Customer ";
		cout << "\n";
		cout << "\n		Choose one (1) or (2) or (3) : ";
		cin >> role;
		cout << "\n";
	} while (role != 1 && role != 2 && role !=3); //selain 1 & 2 //keep looping
	cout << "----------------------------------------------------------------------------------------\n";
	cout << "       Username : ";
	cin >> username;
	cout << "       Password : ";
	getline(cin, password);
	while ((ch = _getch()) != 13)
	{
		password += ch;
		cout << '*';
	}

	//do
	//{
	//	cout << "\n" << endl;
	//	cout << "\nAdmin (1) or Customer (2) : ";
	//	cin >> role;
	//} while (role != 1 && role != 2); //selain 1 & 2 //keep looping

	if (role == 1) //admin
	{
		//check username & password 
		string checkUser_query = "select * from Admin where Username = '" + username + "' and Password = '" + password + "'";
		const char* cu = checkUser_query.c_str();//convert
		qstate = mysql_query(conn, cu);//executee

		if (!qstate)
		{
			res = mysql_store_result(conn); //store result
			if (res->row_count == 1) //jumpa user
			{
				while (row = mysql_fetch_row(res)) //loop each of row dalam result
					adminID = row[0]; //store ID in variable

				cout << ("\n\n\nLOADING\n");
				int a;
				for (a = 1;a < 8;a++)
				{
					Sleep(500);
					cout << ("...");
				}
				system("PAUSE");
				system("CLS");
				AdminMenu();
			}
			else //tak jumpa user //username & password salah
			{
				char c;
				cout << "Invalid username or password. Want to try again? (y/n): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					Login();
				else
					main();
			}
		}
	}

	else if (role == 2)//staff
	{
		string checkUser_query = "select * from staff where Username = '" + username + "' and Password = '" + password + "'";
		const char* cu = checkUser_query.c_str();//convert
		qstate = mysql_query(conn, cu);//executee

		if (!qstate) //query boleh jalan
		{
			res = mysql_store_result(conn); //store result
			if (res->row_count == 1) //jumpa user
			{
				while (row = mysql_fetch_row(res)) //loop each of row dalam result
					staffID = row[0]; //store ID in variable


				cout << ("\n\n\nLOADING\n");
				int a;
				for (a = 1;a < 8;a++)
				{
					Sleep(500);
					cout << ("...");
				}
				system("PAUSE");
				system("CLS");

				StaffMenu();
			}
			else //username & password error
			{
				char c;
				cout << "Invalid username or password. Want to try again? (y/n): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					Login();
				else
					main();
			}
		}
	}

	else if (role == 3)//customer
	{
		string checkUser_query = "select * from customer where Username = '" + username + "' and Password = '" + password + "'";
		const char* cu = checkUser_query.c_str();//convert
		qstate = mysql_query(conn, cu);//executee

		if (!qstate) //query boleh jalan
		{
			res = mysql_store_result(conn); //store result
			if (res->row_count == 1) //jumpa user
			{
				while (row = mysql_fetch_row(res)) //loop each of row dalam result
					customerID = row[0]; //store ID in variable


				cout << ("\n\n\nLOADING\n");
				int a;
				for (a = 1;a < 8;a++)
				{
					Sleep(500);
					cout << ("...");
				}
				system("PAUSE");
				system("CLS");

				CustomerMenu();
			}
			else //username & password error
			{
				char c;
				cout << "Invalid username or password. Want to try again? (y/n): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					Login();
				else
					main();
			}
		}
	}

};

//DONE
void Staff()
{
	string ms = "";

	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	char choice;
	// Variables End

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "=============================================================" << endl;
	cout << "--------------------    Staff        ---------------------" << endl;
	cout << "=============================================================" << endl;
	cout << "\n";
	ListStaff();
	cout << endl << "A. Add Staff" << endl;
	cout << "B. Update Staff" << endl;
	cout << "C. Delete Staff" << endl;
	cout << "What do you want to do? (Choose A to C / Choose M to go to Menu) : ";
	cin >> choice;

	if (choice == 'A' || choice == 'a')
	{
		//insert customer
		AddStaff();
	}
	else if (choice == 'B' || choice == 'b')
	{
		//update customer
		UpdateStaff();
	}
	else if (choice == 'C' || choice == 'c')
	{
		//delete customer
		DeleteStaff();
	}
	
	else if (choice == 'M' || choice == 'm')
	{
		AdminMenu();
	}
	else
	{
		cout << "Wrong Credential !" << endl;
	}
};

//DONE
void Match()
{
	string ms = "";

	// Initial Load
	system("cls");
	// Initial Load End

	// Variables
	char choice;
	// Variables End

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                             ------   MANAGE MATCH    ------                            " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n";
	ListMatch();
	cout << endl << "A. Add Match" << endl;
	cout << "B. Update Match " << endl;
	cout << "C. Delete Match" << endl;
	cout << "What do you want to do? (Choose A to C / Choose M to go to Menu) : ";
	cin >> choice;

	if (choice == 'A' || choice == 'a')
	{
		//insert match
		AddMatch();
	}
	else if (choice == 'B' || choice == 'b')
	{
		//update match
		UpdateMatch();
	}
	else if (choice == 'C' || choice == 'c')
	{
		//delete match
		DeleteMatch();
	}
	
	else if (choice == 'M' || choice == 'm')
	{
		StaffMenu();
	}
	else
	{
		cout << "Wrong Credential !" << endl;
	}

};




//DONE
void AddStaff()
{
	system("cls");
	string name, address, email, staffIC, telno, password,username,adminID;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "----------------         PROGRAM TO ADD NEW STAFF DETAILS       ---------------------" << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;


	cout << "Enter Admin username: ";
	cin >> username;
	string search_query = "select * from admin where username = '" + username + "'";
	const char* z = search_query.c_str();
	qstate = mysql_query(conn, z);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		adminID = row[0];
	};
	cout << "Admin ID : " << adminID << endl;
	cout << "\n" << endl;


	cout << "Add New Staff Details" << endl;
	cin.ignore(1, '\n');
	cout << " Name : ";
	getline(cin, name);
	cout << "Identification Number: ";
	getline(cin, staffIC);
	cout << "Telephone Number: ";
	getline(cin, telno);
	cout << "Address: ";
	getline(cin, address);
	cout << "Email:  ";
	getline(cin, email);
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);


	string insert_query = "insert into Staff (name,staffIC,telno,address,email,username,password,adminID) values ('" + name + "','" + staffIC + "','" + telno + "','" + address + "' , '" + email + "' ,'" + username + "', '" + password + "','" + adminID + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate) //query boleh jalan
	{
		cout << endl << "The details of staff is successful added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	char choose;
	do
	{
		cout << "Do you want add another staff details? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			AddStaff();
		}
		else if (choose == 'n' || choose == 'N')
		{
			AdminMenu();
		}
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
};


//DONE
void UpdateStaff()
{
	system("cls");
	char choose;

	string staffID, name, staffIC, telno, email, address, new_customerIC;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "                     ------   PROGRAM TO UPDATE STAFF    ------                      " << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "Enter Staff ID: ";
	cin >> staffID;
	system("cls");


		int chooseUpdate = 0;

		
			string search_query = "select * from staff where staffID = '" + staffID + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) //looping to retreive the data
			{
				cout << "--- Current Details of Staff ---" << endl;
				cout << "Staff ID: " << row[0] << " (Uneditable)"
					<< "\n\n1. Name: " << row[1]
					<< "\n2. Identification Number: " << row[2]
					<< "\n3. Telephone Number:  " << row[3]
					<< "\n4. Address:  " << row[4]
					<< "\n5. Email: " << row[5]
					<< "\n6. Save";
			}
				cout << endl;
				cout << "\nChoose one: ";
				cin >> chooseUpdate;
				cin.ignore(1, '\n');
			
				if (chooseUpdate == 1)
				{
					cout << "Insert New Name: ";
					getline(cin, name);
					string update_query = "update staff set Name = '" + name + "' where staffID = '" + staffID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					AdminMenu();


				}
				else if (chooseUpdate == 2)
				{
					cout << "Insert New Identification Number: ";
					getline(cin,staffIC);
					string update_query = "update staff set staffIC = '" + staffIC + "' where staffID = '" + staffID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					AdminMenu();

				}
				else if (chooseUpdate == 3)
				{
					cout << "Insert New Telephone Number: ";
					getline(cin, telno);
					string update_query = "update staff set Telephone Number = '" + telno + "' where staffID = '" + staffID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					AdminMenu();


				}
				else if (chooseUpdate == 4)
				{
					cout << "Insert New Address: ";
					getline(cin, address);
					string update_query = "update staff set address = '" + address + "' where staffID = '" + staffID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					AdminMenu();

				}
				else if (chooseUpdate == 5)
				{
					cout << "Insert New Email: ";
					getline(cin, email);
					string update_query = "update staff set Email = '" + email + "' where staffID = '" + staffID + "'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					AdminMenu();
				}
				else if (chooseUpdate == 6)
				{
					ListStaff();
				}
			

};

//DONE
void DeleteStaff()
{
	system("cls");
	char choose;
	string staffID;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "----------------        PROGRAM TO DELETE STAFF DETAILS     ---------------------" << endl;
	cout << "========================================================================================" << endl;
	
	cout << "\n" << endl; 

	ListStaff();
	cout << "Enter Staff ID: ";
	cin >> staffID; // Global Variable

	do
	{
		cout << "Are you sure want to remove this staff? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			string check = "select * from staff where staffID = '" + staffID + "'";
			const char* c = check.c_str();
			qstate = mysql_query(conn, c);
			res = mysql_store_result(conn);
			if (!qstate)
			{
				if (res->row_count > 0)
				{
					cout << "The Staff can't be remove, currently used. Press Enter to Continue...";
					_getch();
					ListStaff();
				}
			}

			string delete_query = "delete from staff where staffID = '" + staffID + "'";
			const char* q = delete_query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				cout << "The Staff has been removed. Press Enter to Continue...";
				_getch();
			     Staff();
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
		else if (choose == 'n' || choose == 'N')
		{
			Staff();
		}
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');

};


//DONE 
void AddMatch()
{
	system("cls");
	string team, date_match, quantityTicket,username,staffID;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "----------------          PROGRAM TO ADD NEW MATCH DETAILS         ---------------------" << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;

	cout << "Enter Staff username: ";
	cin >> username;
	string search_query = "select * from staff where username = '" + username + "'";
	const char* z = search_query.c_str();
	qstate = mysql_query(conn, z);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		staffID = row[0];
	};
	cout << "Staff ID : " << staffID << endl;
	cout << "\n" << endl;


	cin.ignore(1, '\n');
	cout << "Team : ";
	getline(cin, team);
	cout << "Date of the Match (yyyy/mm/dd) :  ";
	getline(cin, date_match);
	cout << "Quantity of Ticket Available: ";
	getline(cin, quantityTicket);
	

	string insert_query = "insert into matchs (team,date_match,quantityTicket,staffID) values ('" + team + "', '"+ date_match +"','" + quantityTicket + "','" + staffID + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate) //query boleh jalan
	{
		cout << endl << "The details of match is successful added in database." << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	char choose;
	do
	{
		cout << "Do you want add another match details? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			AddMatch();
		}
		else if (choose == 'n' || choose == 'N')
		{
			StaffMenu();
		}
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');

};//DONE


//DONE 
void UpdateMatch()
{
	char choose;
	
	string team, date_match, matchID, quantityTicket;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "----------------         PROGRAM TO UPDATE MATCH DETAILS       ---------------------" << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "Enter Match ID: ";
	cin >> matchID;

	
		int chooseUpdate = 0;

		
			system("cls");
			string search_query = "select * from matchs where matchID = '" + matchID + "'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res)) //looping to retreive the data
			{
				cout << "--- Current Details of Match ---" << endl;
				cout << "Match ID: " << row[0] << " (Uneditable)"
					<< "\n\n1. Team: " << row[1]
					<< "\n2. Date of the Match (yyyy/mm/dd) :  " << row[2]
					<< "\n3. Quantity of Ticket: " << row[3]
					<< "\n4. Save";
			}

			cout << "\nChoose one: ";
			cin >> chooseUpdate;
			cin.ignore(1, '\n');

			if (chooseUpdate == 1)
			{
				cout << "Insert New Team: ";
				getline(cin, team);
				string update_query = "update matchs set team  = '" + team + "' where matchID = '" + matchID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				StaffMenu();
			}
			else if (chooseUpdate == 2)
			{
				cout << "Insert New Date of Match: ";
				getline(cin, date_match);
				string update_query = "update matchs set date_match = '" +date_match + "' where matchID = '" + matchID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				StaffMenu();
			}
			else if (chooseUpdate == 3)
			{
				cout << "Insert Quantity of Ticket Available: ";
				getline(cin, quantityTicket);
				string update_query = "update matchs set quantityTicket = '" + quantityTicket + "' where matchID = '" + matchID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
				StaffMenu();
			}

			else if (chooseUpdate == 4)
			{
				ListMatch();
			}
	
};

//DONE
void DeleteMatch()
{
	char choose;
	string matchID;

	cout << "Welcome to Football Ticketing System \n";
	cout << "\n";
	cout << "========================================================================================" << endl;
	cout << "----------------         PROGRAM TO DELETE MATCH DETAILS       ---------------------" << endl;
	cout << "========================================================================================" << endl;
	cout << "\n" << endl;
	cout << "Enter Match ID: ";
	cin >> matchID; // Global Variable

	do
	{
		cout << "Are you sure want to remove this match? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			string check = "select * from Matchs where matchID = '" + matchID + "'";
			const char* c = check.c_str();
			qstate = mysql_query(conn, c);
			res = mysql_store_result(conn);
			if (!qstate)
			{
				if (res->row_count > 0)
				{
					cout << "The Match can't be remove, currently used. Press Enter to Continue...";
					_getch();
					ListMatch();
				}
			}

			string delete_query = "delete from Matchs where matchID = '" + matchID + "'";
			const char* q = delete_query.c_str();
			qstate = mysql_query(conn, q);
			if (!qstate)
			{
				cout << "The Match has been removed. Press Enter to Continue...";
				_getch();
				ListMatch();
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
		else if (choose == 'n' || choose == 'N')
		{
			ListMatch();
		}

		cout << "Press 'm' or 'M' to Menu Or Any Other key to exit: ";
		cin >> choose;

		if (choose == 'm' || choose == 'M')
		{
			StaffMenu();
		}

		else
		{
			exit(0);
		}
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');
};



//setttttleeee
void ListStaff()
{
	// Initial Load
	system("cls");
	// Initial Load End
	// Variables
	char choose;
	// Variables End
	cout << "Welcome To Fottball Ticketing System" << endl << endl;
	cout << "Display Staff Menu" << endl << endl;
	qstate = mysql_query(conn, "select * from staff");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
		printf("| %-15s | %-30s | %-15s | %-15s | %-30s | %-20s | %-15s |\n", "staffID", "name", "staffIC","telno", "email", "username",
			"Password");
		while ((row = mysql_fetch_row(res)))
		{
			printf("| %-15s | %-30s | %-15s | %-15s | %-30s | %-20s | %-15s |\n", row[0], row[1], row[2],row[3],row[5],row[6],
				row[7]);
		}
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
//	// Exit Code
//ExitMenu:
//	cout << "Press 'm' to Menu and any other key to Exit: ";
//	cin >> choose;
//	if (choose == 'm' || choose == 'M')
//	{
//		AdminMenu();
//	}
//	else
//	{
//		exit(0);
//	}
};

void ListCustomer()
{
	// Initial Load
	system("cls");
	// Initial Load End
	// Variables
	char choose;
	// Variables End
	cout << "Welcome To Football Ticketing System" << endl << endl;
	cout << "Display Customer"<< endl << endl;
	qstate = mysql_query(conn, "select * from customer");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
		printf("| %-15s | %-30s | %-15s | %-15s | %-30s | %-20s | %-15s |\n", "customerID", "name", "customerIC", "telno", "email", "username",
			"Password");
		while ((row = mysql_fetch_row(res)))
		{
			printf("| %-15s | %-30s | %-15s | %-15s | %-30s | %-20s | %-15s |\n", row[0], row[1], row[2], row[3], row[5], row[6],
				row[7]);
		}
		printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \n");
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
		// Exit Code
	ExitMenu:
		cout << "Press 'm' to Menu and any other key to Exit: ";
		cin >> choose;
		if (choose == 'm' || choose == 'M')
		{
			AdminMenu();
		}
		else
		{
			exit(0);
		}
};

//setel
void ListMatch()
{
		// Initial Load
		system("cls");
		// Initial Load End
		// Variables
		char choose;
		// Variables End
		cout << "Welcome To Football Ticketing System" << endl << endl;
		cout << "Display Match Menu" << endl << endl;
		qstate = mysql_query(conn, "select * from Matchs");
		if (!qstate)
		{
			res = mysql_store_result(conn);
			printf("----------------------------------------------------------------------------------------------------\n");
				printf("| %-20s | %-30s | %-15s | %-15s |\n", "matchID", "team", "date_match","quantityTicket");
			while ((row = mysql_fetch_row(res)))
			{
				printf("| %-20s | %-30s | %-15s | %-15s |\n", row[0], row[1], row[2], row[3]);
			}
			printf("------------------------------------------------------------------------------------------------------- \n");

			
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
};



void DisplayChoice()
{

	system("cls");
	char choose;
	cout << "Welcome to Football Ticketing System \n";
	cout << "List of Ticket Price\n";
	cout << "\n";
	cout << "===================================================================================================" << endl;
	cout << "------------------               WELCOME TO STADIUM BUKIT JALIL                --------------------" << endl;
	cout << "--------------------                FINAL PIALA MALAYSIA 2021                ----------------------" << endl;
	cout << "===================================================================================================" << endl;

	//Display the ticket price of match based on gate 
	cout << "\n" << endl;
	cout << "**********       Ticket price for gate A (VVIP)    = RM 55\n" << endl;
	cout << "**********       Ticket price for gate B (VIP)     = RM 45\n" << endl;
	cout << "**********       Ticket price for Gate C (NORMAL)  = RM 40\n" << endl;


	cout << "Press 'm' or 'M' to Menu Or Any Other key to exit: ";
		cin >> choose;

	if (choose == 'm' || choose == 'M')
	{
		CustomerMenu();
	}
	
	else
	{
		exit(0);
	}
}

////ADA PROBLEM SIKIT
//void BookTicket()
//{
//	system("cls");
//	char choose;
//
//	double payment, numAdult = 0, numChild = 0, Tprice = 0, t1 = 0, t2 = 0, t3 = 0;
//	int numCust = 0, ta = 100, tb = 100, tc = 100, qtyA = 0, qtyB = 0, qtyC = 0, no[10];
//	char ans, gate, code[10];
//
//	string detail[6] = { "GATE A = ADULT", "GATE A = CHILD","GATE B= ADULT","GATE B = CHILD","GATE C= ADULT","GATE C= CHILD" };
//	
//	int i = 1;
//	double ticketprice;
//	int qty = 0;
//	const int price = 6;
//	double gates[price] = { 45,35,39,20,39,20 };
//
//	DisplayChoice();
//		cout << "\nEnter gate = ";
//		cin >> gate;
//
//		code[i] = gate;
//		
//		
//		//loop for gate A`
//		if (gate == 'A' || gate == 'a')
//		{
//			cout << "Ticket Available = " << ta << endl;
//			cout << "Please enter total (" << detail[0] << ") ticket do you want: ";
//			cin >> numAdult;
//			cout << "Please enter total (" << detail[1] << ") ticket do you want: ";
//			cin >> numChild;
//			qtyA = numAdult + numChild;
//			if (qtyA <= 100)
//			{
//				qty = qtyA + qty;
//				ta = ta - qty;
//				ticketprice = gates[0] * qty;
//				t1 = t1 + ticketprice;
//				cout << "Ticket price = RM " << fixed <<ticketprice << setprecision(2) << endl;
//				no[i] = qtyA;
//			}
//			else if (qtyA > 100)
//			{
//				cout << "Not Sufficient";
//			}
//
//		}
//
//		//loop for gate B
//		else if (gate == 'B' || gate == 'b')
//		{
//			cout << "Ticket Available = " << tb << endl;
//			cout << "Please enter total (" << detail[2] << ") ticket do you want: ";
//			cin >> numAdult;
//			cout << "Please enter total (" << detail[3] << ") ticket do you want: ";
//			cin >> numChild;
//			qtyB = numAdult + numChild;
//
//			if (qtyB <= 100)
//			{
//				qty = qtyB + qty;
//				tb = tb - qty;
//				ticketprice = gates[1] * qty;
//				t2 = t2 + ticketprice;
//				cout << "Ticket price = RM " << fixed << ticketprice << setprecision(2) << endl;
//				no[i] = qtyB;
//
//			}
//			else if (qtyB > 100)
//			{
//				cout << "Not Sufficient";
//			}
//		}
//
//		//loop for gate C
//		else if (gate == 'C' || gate == 'c')
//			{
//				cout << "Ticket Available = " << tc << endl;
//				cout << "Please enter total (" << detail[4] << ") ticket do you want: ";
//				cin >> numAdult;
//				cout << "Please enter total (" << detail[5] << ") ticket do you want: ";
//				cin >> numChild;
//				qtyC = numAdult + numChild;
//
//				if (qtyC <= 100)
//				{
//					qty = qtyC + qty;
//					tc = tc - qty;
//					ticketprice = gates[2] * qty;
//					t3 = t3 + ticketprice;
//					cout << "Ticket price = RM " << fixed << ticketprice << setprecision(2) << endl;
//					no[i] = qtyC;
//				}
//				else if (qtyC > 100)
//				{
//					cout << "Not Sufficient";
//				}
//			}
//			numCust += qty;
//
//		
//
//};


void BookTicket()
{
	system("cls");
	int qty = 0, Totalprice = 0, quantityTicket = 0;
	char gate;
	string matchID, quantity1, purchasedStatus, customerID, quantity, purchaseTotal, newQuantityTicket ,username,purchasedQuantity,purchasedDate,team,date_match,telno,name; //PLANT_ACTPRICE
	ListMatch();
	cout << "Make Ticket Purchased" << endl;
	cout << "Enter username: ";
	cin >> username;
	string search_query = "select * from customer where username = '" + username + "'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		customerID = row[0];
	};
	cout << "customer ID : " << customerID << endl;
	cout << "Match ID: ";
	cin >> matchID;
	search_query = "select * from matchs where matchID = '" + matchID + "'";
	const char* a = search_query.c_str();
	qstate = mysql_query(conn, a);
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res))
	{
		quantityTicket = stoi(row[3]);
	};

	/*search_query = "select * from report where matchID = '" + matchID + "'";
	const char* w = search_query.c_str();
	qstate = mysql_query(conn, w);
	res = mysql_store_result(conn);

	while (row = mysql_fetch_row(res))
	{
		quantity = stoi(row[4]);
	};*/


	cout << "\nEnter gate = ";
	cin >> gate;

	if (gate == 'A' || gate == 'a')
	{
		cout << "Quantity Ticket: ";
		cin >> qty;
		Totalprice = qty * 55;
		cout << "The total price is : RM " << Totalprice << endl;
		purchaseTotal = to_string(Totalprice);
		cout << "\n" << endl;
		cout << "===========================================================================================" << endl;
		cout << "                           ******   HERE IS YOUR TICKET     ******                                " << endl;
		cout << "===========================================================================================" << endl;
		cout << "--------------                     FINAL PIALA MALAYSIA 2021                 --------------\n" << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                                          RECEIPT                                          " << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                     Match ID                     : " << matchID << endl;
		cout << "                     Quantity of ticket purchased : " << qty << endl;
		cout << "                     Price                        : " <<"RM: "<< Totalprice << endl;
		cout << "                     Time                         :  8.45 PM " << endl;
		cout << "                     Gate                         :  " << gate << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "  Customer ID         : " << customerID << endl;
		cout << "  Customer username   : " << username << endl;
		cout << "===========================================================================================" << endl;

	}
	 
	else if (gate == 'B' || gate == 'b')
	{
		cout << "Quantity Ticket: ";
		cin >> qty;
		Totalprice = qty * 45;
		cout << "The total price is : RM " << Totalprice << endl;
		purchaseTotal = to_string(Totalprice);
		cout << "\n" << endl;
		cout << "===========================================================================================" << endl;
		cout << "                           ******   HERE IS YOUR TICKET     ******                                " << endl;
		cout << "===========================================================================================" << endl;
		cout << "--------------                     FINAL PIALA MALAYSIA 2021                 --------------\n" << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                                          RECEIPT                                          " << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                     Match ID                     : " << matchID << endl;
		cout << "                     Quantity of ticket purchased : " << qty << endl;
		cout << "                     Price                        : " << "RM: " << Totalprice << endl;
		cout << "                     Time                         :  8.45 PM " << endl;
		cout << "                     Gate                         :  " << gate << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "  Customer ID         : " << customerID << endl;
		cout << "  Customer username   : " << username << endl;
		cout << "===========================================================================================" << endl;

	}

	else if (gate == 'C' || gate == 'c')
	{
		cout << "Quantity Ticket: ";
		cin >> qty;
		Totalprice = qty * 40;
		cout << "The total price is : RM " << Totalprice << endl;
		purchaseTotal = to_string(Totalprice);
		cout << "\n" << endl;
		cout << "===========================================================================================" << endl;
		cout << "                           ******   HERE IS YOUR TICKET     ******                                " << endl;
		cout << "===========================================================================================" << endl;
		cout << "--------------                     FINAL PIALA MALAYSIA 2021                 --------------\n" << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                                          RECEIPT                                          " << endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "                     Match ID                     : " << matchID << endl;
		cout << "                     Quantity of ticket purchased : " << qty << endl;
		cout << "                     Price                        : " << "RM: " << Totalprice << endl;
		cout << "                     Time                         :  8.45 PM " << endl;
		cout << "                     Gate                         :  " << gate<<endl;
		cout << "-------------------------------------------------------------------------------------------" << endl;
		cout << "  Customer ID         : " << customerID << endl;
		cout << "  Customer username   : " << username << endl;
		cout << "===========================================================================================" << endl;

	}


	//quantity1 = to_string(quantityTicket + qty);
	//string add_query = "update report set quantity = '" + quantity1 + "' where matchID = '" + matchID + "'";
	//const char* f = add_query.c_str();
	//qstate = mysql_query(conn, f);

	//if (!qstate) //query boleh jalan
	//{
	//	cout << endl;
	//}
	//else
	//{
	//	cout << "Query Execution Problem! Report update fail " << mysql_errno(conn) << endl;
	//}



	string getMATCHID = "select* from matchs where matchID =  '" + matchID + "'";
	const char* v = getMATCHID.c_str();
	qstate = mysql_query(conn, v);
	if (!qstate) //query boleh jalan
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			matchID = row[0];
		};
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	quantity = to_string(qty);
	string insert_query = "insert into ticketpurchased (matchID, gate, quantity, purchaseTotal,customerID) values ('" + matchID + "','" + gate + "','" + quantity + "','" + purchaseTotal + "','" + customerID + "')";
	const char* s = insert_query.c_str();
	qstate = mysql_query(conn, s);
	if (!qstate) 
	{
		cout << endl << "The ticket purchase is successfull.\n" << endl;
		cout << "Thank you !\n" << endl;
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	newQuantityTicket = to_string(quantityTicket - qty);
	string update_query = "update matchs set quantityTicket = '" + newQuantityTicket + "' where matchID = '" + matchID + "'";
	const char* z = update_query.c_str();
	qstate = mysql_query(conn, z);

	  

	char choose;
	do
	{
		cout << "Do you want add another purchase? (y/n): ";
		cin >> choose;
		if (choose == 'y' || choose == 'Y')
		{
			BookTicket();
		}
		else if (choose == 'n' || choose == 'N')
		{
			CustomerMenu();
		}
	} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');

};


void Report()
{ 
	// Initial Load
	system("cls");
	// Initial Load End
	// Variables
	char choose;
	// Variables End
	cout << "Welcome To Football Ticketing System" << endl << endl;
	cout << "Display Report" << endl << endl;

	qstate = mysql_query(conn, "select * from ticketpurchased");
	if (!qstate)
	{
		res = mysql_store_result(conn);
		printf("----------------------------------------------------------------------------------------------------\n");
		printf("| %-20s | %-30s | %-15s |\n", "matchID", "purchaseTotal(RM)", "quantity");
		while ((row = mysql_fetch_row(res)))
		{
			printf("| %-20s | %-30s | %-15s |\n", row[1], row[3], row[4]);
		}
		printf("------------------------------------------------------------------------------------------------------- \n");


	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	// Exit Code
ExitMenu:
	cout << "Press 'm' to Menu and any other key to Exit: ";
	cin >> choose;
	if (choose == 'm' || choose == 'M')
	{
		AdminMenu();
	}
	else
	{
		exit(0);
	}
};






