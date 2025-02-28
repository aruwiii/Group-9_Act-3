#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

/*
Error Handling Check
- Invalid File name
- Negative Value
- If there is no data to sort
- File opening errors
- If the directory doesnt exist where's it
trying to save (compiler error handling to though)

Added Features:
- nilagay ko na siya sa class for accessibility ng variables
- unique na yung mga gine generate na ID
- ginawa ko is hindi siya nag s save to file na sorted_inventory lang
bale ano user input yung file name and then pwede mag make ng multiple files
ayoko kasi na pang isahan lang yung program na nag o overwrite.

Notes:
- lalagay ko rin naman sa user manual pero tignan mo nalang yung directory sa baba
if you want to test the code ibahin mo. Bale nilagay ko diyan is sa Documents folder siya
and then manually gagawa ng folder don named Sorted Inventory Documents. 
*/


struct Item {
    int id;
    int qually;
};

class Inventory {
private:
    Item* store;   
    int size;      

public:
    Inventory() : store(nullptr), size(0) {}
    
	bool isValidFilename(const string& filename) {
    	string illegalChars = "\\/:*?\"<>|"; // illegal characters that are not allowed in filenames

    	for (char ch : filename) {
        	if (illegalChars.find(ch) != string::npos) {
            	return false;
        	}
    	}
    return true; 
	}

	// function for checking if the random generated ID is unique
    bool isUnique(int id, int currentIndex) {
        for (int i = 0; i < currentIndex; ++i) {
            if (store[i].id == id) {
                return false;
            }
        }
        return true;
    }

	// function for generating random data
    void randItems(int &a, int &b, int currentIndex) {
        do {
            a = rand() % 100 + 1;  
        } while (!isUnique(a, currentIndex)); 

        b = rand() % 50 + 1; 
    }

	// function that fills the array with random unique IDs and its quantities
	// outputs the array
    void generateData(int value) {
        delete[] store;        
        store = new Item[value]; 
        size = value;      
		
		cout << "\n";
        for (int i = 0; i < size; ++i) {
            randItems(store[i].id, store[i].qually, i);
            cout << "|ID: " << setw(2) << store[i].id << "       " << "Quantity: " << setw(2) << store[i].qually << "|\n";
        }
        cout << "\n\n";
    }

	// insertion sort implementation
    void insertionSort(const string& filename) {
        if (size == 0) {
            cout << "No data to sort. Generate data first.\n";
            return;
        }
		
		cout << "\n\nITERATIONS: \n";
        for (int i = 1; i < size; ++i) {
            Item key = store[i];
            int j = i - 1;

            while (j >= 0 && store[j].id > key.id) {
                store[j + 1] = store[j];
                --j;
            }
            store[j + 1] = key;

            cout << "Iteration " << i << ": ";
            for (int k = 0; k < size; ++k) {
                cout << store[k].id << " ";
            }
            cout << "\n\n";
        }


        cout << "\n\nSorted Inventory:\n";
        for (int i = 0; i < size; ++i) {
            cout << "|ID: " << setw(2) << store[i].id << "     " << "Quantity: " << setw(2) << store[i].qually << "|\n";
        }
        
    	// Save to file
    	fstream inputFile;		//filepath depends on the user
		string filePath = "C:\\Users\\Asus\\Documents\\Sorted Inventory Documents\\" + filename + ".txt";
    	inputFile.open(filePath, ios::out);
    	if (inputFile.is_open()) {
        	for (int i = 0; i < size; ++i) {
            	inputFile << "ID: " << store[i].id << " Quantity: " << store[i].qually << "\n";
        	}
        	cout << "\nData saved to " << filename << ".txt\n";
    		cout << "+-----------------------------------------+\n";
        	inputFile.close();
    	} else {
    		perror("File opening error");
    	}
        
    }
};

int main() {
    srand(time(0));

    Inventory inventory;
    int option, value;
    string filename;

    do {
    	system("cls");
    	cout << "+-------------------------------+\n";
    	cout << "|      INVENTORY MANAGEMENT     |\n";
    	cout << "|-------------------------------|\n";
    	cout << "| 1. Generate Random Data       |\n";
    	cout << "| 2. Do Insertion Sort          |\n";
    	cout << "| 3. Exit                       |\n";
    	cout << "+-------------------------------+\n";
    	cout << "Choice: ";
        cin >> option;

        switch (option) {
            case 1:
            	system("cls");
    			cout << "+---------------------------------------------+\n";
                cout << "|  How many data would you like to generate?  |";
    			cout << "\n+---------------------------------------------+\n";
    			cout << "=+ Data: ";
    			
    			do{
                cin >> value;
                if (value <= 0) {
                    cout << "Negative/0 number is not allowed. Input value again\n";}
                }while(value <= 0);
                
                inventory.generateData(value);
                system("pause");
                break;

            case 2:
                system("cls");
    			cout << "+-----------------------------------------+\n";
				cout << "Input file name to save to: ";
				
				do {
    			cin >> filename;
    			if (!inventory.isValidFilename(filename)) {
        		cout << "Filename contains illegal characters [`\\ / : * ? \" < > |`] \n";
        		cout << "Please enter a valid filename: ";} 
				}while(!inventory.isValidFilename(filename));

				inventory.insertionSort(filename);
                system("pause");
                break;

            case 3:
                cout << "\n\nExiting Program....\n\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (option != 3);

    return 0;
}

