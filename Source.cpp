#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

struct Employee {
	string firstname;
	string lastname;
	int empNum;
};//struct for employee data

struct Payroll {
	int empNumber;
	double totHours;
	double regHours;
	double otHours;
	double regRate;
	double otRate;
	double regPay;
	double otPay;
	double totalPay;
	double fica;
	double socSec;
	double totDeductions;
	double netPay;

};//data Payroll

struct PayrollTotals {
	double regHours;
	double otHours;
	double regRate;
	double otRate;
	double regPay;
	double otPay;
	double totalPay;
	double fica;
	double socSec;
	double totDeductions;
	double netPay;

};//data for totals

const int MAX_EMPLOYEES = 3;//amount of employees
const int MAX_NUMBERS = 10;
const int MAX_REG_HOURS = 40;
const double FICA_PCT = .20;
const double SS_MED_PCT = .0765;
const double OT_MULT = 1.5;//multiply for the 
const int MAX_TOTALS = 2;

void displayMenu();
char getSelection();
void getEmployeeNames(Employee[]);
void displayEmployeeNames(Employee[]);
void inputHours(Employee[], Payroll[]);
void calcPayroll(Employee[], Payroll[]);
void initializeTotals(PayrollTotals[]);
void calcTotals(PayrollTotals[], Payroll[]);
void calcAverage(PayrollTotals[]);
void displayPayroll(PayrollTotals[], Payroll[], Employee []);
void getEmpName(Employee);


enum PayEnum { TOTALS, AVERAGES }; // TOTALS = 0, AVERAGES = 1

int main() {

	Employee employees[MAX_EMPLOYEES];
	Payroll pay[MAX_EMPLOYEES];
	PayrollTotals payTotals[MAX_TOTALS];
	bool processMenu = true;
	char selection = ' ';
	Employee empNames;


	do {
		displayMenu();
		selection = getSelection();
		cout << "----------------------------" << endl;
		cout << "You choose " << selection << endl;
		cout << "----------------------------" << endl;
		processMenu = true;
		switch (selection) {
		case '1':
			// input employees
			
			getEmployeeNames(employees);
			displayEmployeeNames(employees);
			break;
		case '2':
			//input hours
			inputHours(employees, pay);
			break;
		case '3':
			// calc payroll
			calcPayroll(employees, pay);
			break;
		case '4':
			calcTotals(payTotals, pay);
			break;
		case '5':   
			displayPayroll(payTotals, pay, employees);
			break;
		case 'X':
			processMenu = false;


		} // switch
		system("pause");
		//display menu - function
		//get menu selection - function
		//process menu selection using a switch
		//exit when x is pressed
		//switch(choice) {
		//case 1: etc
		//extra credit - call processSelection to process
		//remember that you will need to set processMenu to exit the program
	} while (processMenu);



	system("pause");
	return 0;
}

void displayMenu() {

	cout << "-----------------------------------------" << endl;
	cout << "Please enter one of the choices below: " << endl;
	cout << "-----------------------------------------" << endl;


	cout << "Press 1 to input employees";
	cout << "\nPress 2 to input hours ";
	cout << "\nPress 3 to calculate payroll ";
	cout << "\nPress 4 to calculate totals ";
	cout << "\nPress 5 to print payroll ";
	cout << "\nPress X to exit \n";

} // dispaly Menu

char getSelection() {

	char choice = ' ';
	bool needInput = true;

	do {
		cin >> choice;
		choice = toupper(choice);
		switch (choice) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case 'X':
			needInput = false;
			break;

		default:
			cout << "---------------------------------" << endl;
			cout << "You have entered invalid input!!!!!!!!!!!!!!!!!!!\n ";
			cout << "---------------------------------" << endl;
			displayMenu();

		} // switch
	} while (needInput);

	return choice;

}

void getEmployeeNames(Employee empInfo[]) {

	cout << "Please enter Name, Last Name and Number for each employee" << endl;
	for (int i = 0; i < MAX_EMPLOYEES; i++) {

		cout << "Employee " << (i + 1) << endl;
		cout << "Lastname: ";
		cin >> empInfo[i].lastname;
		cout << "Firstname: ";
		cin >> empInfo[i].firstname;
		cout << "Employee Number: ";
		cin >> empInfo[i].empNum;


	} //for


} //getEmployessNames 

void displayEmployeeNames(Employee empInfo[]) {

	cout << "-------------------------------------------------"<< endl;
	cout << "Please check the information you have entered:" << endl;
	cout << "-------------------------------------------------"<< endl;

	for (int i = 0; i < MAX_EMPLOYEES; i++) {
		cout << "Lastname " << empInfo[i].lastname;
		cout << "\nFirstname " << empInfo[i].firstname;
		cout << "\nEmployee Number " << empInfo[i].empNum;
		cout << endl;


	} //for

} //displayEmpnames

void inputHours(Employee emp[], Payroll pay[]) {

	// this function get the hours and rate of all employees 


	// payroll[i].empNumber = emp[i].empnum
	for (int i = 0; i < MAX_EMPLOYEES; i++) {
		cout << "How many hours did " << emp[i].lastname << " work? ";
		cin >> pay[i].totHours;
		cout << "How much does " << emp[i].lastname << " make per hour? ";
		cin >> pay[i].regRate;
		pay[i].otRate = (pay[i].regRate * OT_MULT);
		if (pay[i].totHours > MAX_REG_HOURS)
		{
			pay[i].regHours = (MAX_REG_HOURS);
			pay[i].otHours = (pay[i].totHours - MAX_REG_HOURS);
		}
		else {
			pay[i].regHours = (pay[i].totHours);
			pay[i].otHours = 0;
		} //if else

		cout <<"Regular hours: " <<pay[i].regHours << '\t' << "Overtime hours: "<<pay[i].otHours << endl;

	} //for


} // input hours

void calcPayroll(Employee emp[], Payroll pay[]) {
		
	cout << "You have Calculated The payroll\n ";
	   
	for (int i = 0; i < MAX_EMPLOYEES; i++)
	{
		//I already have over time hours calculated in Imput hours.
		pay[i].otPay = (pay[i].otRate*pay[i].otHours);
		pay[i].regPay = (pay[i].regRate*pay[i].regHours);
		pay[i].totalPay = (pay[i].otPay+pay[i].regPay);

		pay[i].fica = (pay[i].totalPay*FICA_PCT);
		pay[i].socSec= (pay[i].totalPay * SS_MED_PCT);

		pay[i].totDeductions = (pay[i].fica + pay[i].socSec);
		pay[i].netPay = (pay[i].totalPay - pay[i].totDeductions);
	}//for

	
	system("pause");

}


void initializeTotals(PayrollTotals totals[]) {

	for (int i = 0; i < MAX_TOTALS; i++) {

		totals[i].regHours = 0;
		totals[i].otHours = 0;

	} // for


} // initialize totals

void calcTotals(PayrollTotals totals[], Payroll pay[]) {

	double
		totRegHours = 0.0,
		totOTHours = 0.0,
		totRegPay = 0.0,
		totOtPay=0.0,
		totalpay = 0.0,
		totFica = 0.0,
		totsocSec = 0.0,
		totDeduction = 0.0,
		totNetPay = 0.0,  		 
		aveHours = 0.0;


	for (int i = 0; i < MAX_EMPLOYEES; i++) {



		totRegHours += pay[i].regHours;
		totOTHours += pay[i].otHours;
		totOtPay += pay[i].otPay;
		totRegPay += pay[i].regPay;
		totalpay += pay[i].totalPay;
		totFica+= pay[i].fica;
		totsocSec += pay[i].socSec;
		totDeduction +=pay[i].totDeductions;
		totNetPay += pay[i].netPay;

		 

	} // for

	totals[TOTALS].regHours = totRegHours;
	totals[TOTALS].otHours = totOTHours;
	totals[TOTALS].otPay = totOtPay;
	totals[TOTALS].regPay = totRegPay;
	totals[TOTALS].totalPay = totalpay;
	totals[TOTALS].fica = totFica;
	totals[TOTALS].socSec = totsocSec;
	totals[TOTALS].totDeductions = totDeduction;
	totals[TOTALS].netPay = totNetPay;


	calcAverage(totals);// calculate averages
	
	cout << "You have Calculated The Totals and Averages\n ";

} // calcTotals



void calcAverage(PayrollTotals totals[])
{  
	totals[AVERAGES].regHours = (totals[TOTALS].regHours / MAX_EMPLOYEES);
	totals[AVERAGES].otHours = (totals[TOTALS].otHours / MAX_EMPLOYEES);
	totals[AVERAGES].otPay = (totals[TOTALS].otPay / MAX_EMPLOYEES);
	totals[AVERAGES].regPay = (totals[TOTALS].regPay / MAX_EMPLOYEES);
	totals[AVERAGES].totalPay = (totals[TOTALS].totalPay / MAX_EMPLOYEES);
	totals[AVERAGES].fica = (totals[TOTALS].fica / MAX_EMPLOYEES);
	totals[AVERAGES].socSec = (totals[TOTALS].socSec / MAX_EMPLOYEES);
	totals[AVERAGES].totDeductions = (totals[TOTALS].totDeductions / MAX_EMPLOYEES);
	totals[AVERAGES].netPay = (totals[TOTALS].netPay / MAX_EMPLOYEES);

}//calc averages

void displayPayroll(PayrollTotals totals[], Payroll pay[], Employee emp[])
{
	


	cout << fixed << showpoint << setprecision(2);
	cout << "************" << endl;
	cout << "* PAYROLL  *" << endl;
	cout << "************" << endl;

	for (int i = 0; i < MAX_EMPLOYEES; i++)
	{

		cout << fixed << showpoint << setprecision(2);


		cout << "Employee " << (i + 1) << ":" << emp[i].firstname << " " << emp[i].lastname << endl; //display the emplye number plus name
		cout << "---------------------------------------------------" << endl;
		cout << "   Total pay:    $" << pay[i].totalPay << "-" << endl;
		cout << "   Regular pay:  $" << pay[i].regPay << "-" << endl;
		cout << "   Overtime pay: $" << pay[i].otPay << "-" << endl;
		cout << "   Fica Deductions:  $" << pay[i].fica << "-" << endl;
		cout << "   Social Security Deductions: $" << pay[i].socSec << "-" << endl;
		cout << "---------------------------------------------------" << endl;

		cout << "The Net Pay, after deduction for " << emp[i].firstname << " " << emp[i].lastname << " is:  $" << pay[i].netPay << "-" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << endl;
		cout << endl;


	}// display each employee payroll data

	// display the totals

	cout << "************" << endl;
	cout << "* TOTALS  *" << endl;
	cout << "************" << endl;

	cout << "Total of Employees: " << MAX_EMPLOYEES << endl;
	cout << "Total of regular hours: " << totals[TOTALS].regHours << endl;
	cout << "Total of Overtime hours: " << totals[TOTALS].otHours << endl;
	cout << "Total of Overtime Pay: " << totals[TOTALS].otPay << endl;
	cout << "Total of regular pay: " << totals[TOTALS].regPay << endl;
	cout << "Total Pay: " << totals[TOTALS].totalPay << endl;
	cout << "DEDUCTIONS  " << endl;
	cout << "*****************************" << endl;
	cout << "Total of FICA deductions: " << totals[TOTALS].fica << endl;
	cout << "Total of Social Security Deductions: " << totals[TOTALS].socSec << endl;
	cout << "Total Deductions: " << totals[TOTALS].totDeductions << endl;
	cout << "Total of Net Pay:   " << totals[TOTALS].netPay << endl;

	// display averages
	cout << "************" << endl;
	cout << "* AVERAGES  *" << endl;
	cout << "************" << endl;


	cout << "Total of Employees: " << MAX_EMPLOYEES << endl;
	cout << "Average of regular hours: " << totals[AVERAGES].regHours << endl;
	cout << "Average of Overtime hours: " << totals[AVERAGES].otHours << endl;
	cout << "Average of Overtime Pay: " << totals[AVERAGES].otPay << endl;
	cout << "Average of regular pay: " << totals[AVERAGES].regPay << endl;
	cout << "Average of Total Pay: " << totals[AVERAGES].totalPay << endl;
	cout << "DEDUCTIONS  " << endl;
	cout << "*****************************" << endl;
	cout << "Average of FICA deductions: " << totals[AVERAGES].fica << endl;
	cout << "Average of Social Security Deductions: " << totals[AVERAGES].socSec << endl;
	cout << "Average of Total Deductions: " << totals[AVERAGES].totDeductions << endl;
	cout << "Average of Net Pay:   " << totals[AVERAGES].netPay << endl;

	   	  

}
