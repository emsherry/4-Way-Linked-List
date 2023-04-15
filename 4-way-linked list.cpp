/**
 * 
 * Author: Shehryar Ahmad 
 * Description: A 4-way linked list used to store phone numbers of 
 *              users which includes the functions of adding a user,
 *              deleting a user, displaying all users, and searching
 *              a user data.
*/


#include <iostream>
#include <string.h>
#include <string>
using namespace std;

int N = 0;          //Globally defined variables
int Count = 0;
int RowMax = 3;
int ColMax = 3;



struct Node            //Structure for making a linked list
{
	int Phone;
	char Name[10];
	char Address[10];
	char Email[10];

	Node* Next;
	Node* Back;
	Node* Up;
	Node* Down;
};

Node* VerticalLinks(Node* HeadPtr)   //Implementing a 4-way linked list
{
	int CurrRow = N / ColMax;
	int CurrCol = N % ColMax;
	
	if (CurrRow > 0 && CurrCol > 0)
	{
		Node* UpperRow = HeadPtr;
		Node* LowerRow = HeadPtr->Down;

		for (int i = 1; i < CurrRow; i++)
		{
			UpperRow = UpperRow->Down;
			LowerRow = LowerRow->Down;
		}
		for (int j = 0; j < CurrCol; j++)
		{
			UpperRow = UpperRow->Next;
			LowerRow = LowerRow->Next;
		}

		UpperRow->Down = LowerRow;
		LowerRow->Up = UpperRow;
	}

	return HeadPtr;
}

Node* CreateNode()        //Function to create a Node
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	if (NewNode == NULL)
	{
		cout << "No memory left!" << endl;;
		return NULL;
	}

	NewNode->Phone = NULL;
	NewNode->Name ;
	NewNode->Address  ;
	NewNode->Email ;
 
	NewNode->Next = NULL;
	NewNode->Back = NULL;
	NewNode->Up = NULL;
	NewNode->Down = NULL;

	return NewNode;
}



Node* AddInfo(Node* HeadPtr)        //Function to add info of user
{
	if (N == (RowMax * ColMax))
	{
		cout << "No more data can be stored in this directory!" << endl;
		return NULL;
	}

	Node* NewData = CreateNode();
	cout << "Enter Phone No.: " << endl;
	cin >> NewData->Phone;
	cout << "Enter Name: " << endl;
	cin.ignore();
	cin.getline(NewData->Name,10);
	cout << "Enter Address: " << endl;
	cin.ignore();
	cin.getline(NewData->Address,10);
	cout << "Enter Email: " << endl;
	cin.ignore();
	cin.getline(NewData->Email,10);
	

	if (N == 0)
	{
		HeadPtr = NewData;
		return HeadPtr;
	}

	Node* Curr = HeadPtr;
	Node* Prev = CreateNode();

	int CurrRow = N / ColMax;
	for (int i = 0; i < CurrRow; i++)
	{
		Prev = Curr;
		Curr = Curr->Down;
	}

	int CurrCol = N % ColMax;
	for (int j = 1; j < CurrCol; j++)
		Curr = Curr->Next;

	if (CurrCol == 0)
	{
		NewData->Up = Prev;
		Curr = NewData;
		Prev->Down = Curr;
	}
	else
	{
		NewData->Back = Curr;
		Curr->Next = NewData;
	}

	return HeadPtr;
}

Node* DeleteInfo(Node* HeadPtr, int DeletePtr)     //Function to delete a users data
{
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return NULL;
	}

	if (Count == 0)
	{
		cout << "Input the phone number you wish to delete: ";
		cin >> DeletePtr;
	}

	Node* Temp = CreateNode();
	Node* CurrH = HeadPtr;
	Node* CurrV = HeadPtr;

	int i;
	int CurrRow = Count / ColMax;
	for (i = 0; i < CurrRow; i++)
	{
		CurrV = CurrV->Down;
		CurrH = CurrV;
	}

	for (int j = 0; j < ColMax; j++)
	{
		if (CurrH->Phone == DeletePtr)
		{
			CurrRow = N / ColMax;

			for (i; i < CurrRow; i++)
			{
				while (CurrH->Next != NULL)
				{

					CurrH->Phone = CurrH->Next->Phone;
					CurrH->Name[10] = CurrH->Next->Name[10];
					CurrH->Address[10] = CurrH->Next->Address[10];
					CurrH->Email[10] = CurrH->Next->Email[10];
					CurrH = CurrH->Next;
					Count++;

					if (Count == N - 1)
					{
						CurrH = NULL;
						Count = 0;
						return HeadPtr;
					}
				}

				Temp = CurrH;
				CurrV = CurrV->Down;

				if (CurrV != NULL)
				{
					Temp->Phone = CurrV->Phone;
					Temp->Name[10] = CurrV->Name[10];
					Temp->Address[10] = CurrV->Address[10];
					Temp->Email[10] = CurrV->Email[10];
					CurrH = CurrV;
				}
				Count++;

				if (Count == N - 1)
				{
					CurrH = NULL;
					Count = 0;
					return HeadPtr;
				}
			}

			Count = 0;
			return HeadPtr;
		}

		CurrH = CurrH->Next;
		Count++;
		cout << "Node Deleted Successfully";

		if (Count == N)
		{
			cout << "This phone number does not exist in the directory!" << endl;
			Count = 0;
			return NULL;
		}
	}

	HeadPtr = DeleteInfo(HeadPtr, DeletePtr);
	return HeadPtr;
}



void SearchInfo(Node* HeadPtr, int SearchPtr)       //Function to search a users info and display it
{
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return;
	}

	if (Count == 0)
	{
		cout << "Input the phone number you wish to search: ";
		cin >> SearchPtr;
	}

	Node* Curr = HeadPtr;
	
	int CurrRow = Count / ColMax;
	for (int i = 0; i < CurrRow; i++)
		Curr = Curr->Down;

	for (int j = 0; j < ColMax; j++)
	{
		if (Curr->Phone == SearchPtr)
		{
			cout << Curr->Phone << endl;
			cout << Curr->Name << endl;
			cout << Curr->Address << endl;
			cout << Curr->Email << endl;

			Count = 0;
			return;
		}

		Curr = Curr->Next;
		Count++;

		if (Count == N)
		{
			cout << "This phone number does not exist in the directory!" << endl;
			Count = 0;
			return;
		}
	}

	SearchInfo(HeadPtr, SearchPtr);
}



void DisplayInfo(Node* HeadPtr)         //Function for displaying info of all users
{
	if (N == 0)
	{
		cout << "There is no data in this directory!" << endl;
		return;
	}

	Node* Curr = HeadPtr;
	
	int CurrRow = Count / ColMax;
	for (int i = 0; i < CurrRow; i++)
		Curr = Curr->Down;
	
	for (int j = 0; j < ColMax; j++)
	{
		cout << "NODE " << Count + 1 << ":" << endl;
		cout << "Phone Number: " << Curr->Phone << endl;
		cout << "Name: " << Curr->Name << endl;
		cout << "Address: " << Curr->Address << endl;
		cout << "Email: " << Curr->Email << endl;
		cout << endl;

		Curr = Curr->Next;
		Count++;

		if (Count == N)
		{
			Count = 0;
			return;
		}
	}
	
	DisplayInfo(HeadPtr);
}



int main()          //Main driver
{
	Node* Head = CreateNode();
	Node* Temp = CreateNode();

	int Instruction;
	int FindPhone = 0;

	do
	{
		cout << "MAIN MENU:" << endl;
		cout << "0: Exit." << endl;
		cout << "1: Add Phone Number." << endl;
		cout << "2: Delete Phone Number." << endl;
		cout << "3: Search Phone Number." << endl;
		cout << "4: Display Phone Numbers." << endl;

		cout << endl << "Enter a number to perform its corresponding action: ";
		cin >> Instruction;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "You can only enter a number!" << endl;
			cout << endl << "Enter a number to perform its corresponding action: ";
			cin >> Instruction;
		}

		switch (Instruction)
		{
		case 0:
			cout << "SYSTEM IS SHUTTING DOWN!" << endl;
			break;

		case 1:
			Temp = AddInfo(Head);

			if (Temp != NULL)
			{
				Head = Temp;
				Head = VerticalLinks(Head);
				N++;
			}
			break;

		case 2:
			Temp = DeleteInfo(Head, FindPhone);
			if (Temp != NULL)
			{
				Head = Temp;
				N--;
			}
			break;

		case 3:
			SearchInfo(Head, FindPhone);
			break;

		case 4:
			DisplayInfo(Head);
			break;

		default:
			cout << "This number has no corresponding action!" << endl;
			break;
		}

		cout << endl;
		system("pause");
		system("cls");

	} while (Instruction != 0);

	return 0;
}