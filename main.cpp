#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include <filesystem>
//#include <regex>

using namespace std;

char dum;

void memberList(){
	cout << "Members list";
	
}

//Create class/objects here
class CSVObject {
	public :
		[[deprecated("Function seems to not work.")]]
		static bool fileExist(string path){
			FILE* _f = fopen(path.c_str(),"r");
			return (_f!=NULL);
		}
		/**
		 * Split a string with a string delimitor into an array
		 * @param s - the string to be splitted
		 * @param delim - the string that decides the boundary for each element of the array
		 * @param returnStr[255] - the string array to be written into
		 */
		static void split(string s, string delim, string returnStr[255]){
			int findVal = 0, prevPos = 0;
			int strArrIdx = 0;
			//Iterate through each delim
			do{
				//Check if it is quoted
				if((s.substr(prevPos==0 ? 0 : prevPos-1,2)==",\"") ){
					/*
						TODO: 
						-Check for double quote (""lorem ipsum"")
						-remember it (double_quote = true)
						-for the closing double quote, set to false again
						-check if it is "",
							-True -> find next ",
					*/
					//Check for """,
					int _prevPos = prevPos;
					int _findVal; 

					findVal = s.find("\",",_prevPos)+1;
					if(findVal==string::npos){ //If it did not found a string
						continue;
					}
					
					//Special case check: comma after quote
					if(s.substr(findVal-3,4)!="\"\"\"," && s.substr(findVal-2,3)=="\"\","){				
						do{
							//Prevent finding the same one again
							_prevPos = findVal;
							findVal = s.find("\",",_prevPos)+1;
						}while(!((s.substr(findVal-3,4)=="\"\"\",") || (s.substr(findVal-2,3)!="\"\",")));/**/
					}


					//findVal = s.find("\",",_prevPos)+1;

					returnStr[strArrIdx] = s.substr(prevPos+1,findVal-2-prevPos);
				}
				else{
					findVal = s.find(delim, prevPos); // find the ,
					if(findVal==string::npos){ //If it did not found a string
						continue;
					}
					returnStr[strArrIdx] = s.substr(prevPos,findVal-prevPos);
				}

				int findDoubleQuote = 0, prevDoubleQuote = 0;
				do{
					findDoubleQuote = returnStr[strArrIdx].find("\"\"",0);
					if(findDoubleQuote!=string::npos){
						returnStr[strArrIdx] = returnStr[strArrIdx].replace(findDoubleQuote,2,"\"");
					}
				}while(findDoubleQuote!=string::npos);


				cout << strArrIdx << ": " << returnStr[strArrIdx] << endl;
					cout << prevPos << "," << findVal << endl;

				//cout << returnStr[strArrIdx] << " and " << s.substr(prevPos,findVal-1) << endl;
				prevPos = findVal+1;
				strArrIdx++;
			}while(findVal!=string::npos);
			returnStr[strArrIdx] = s.substr(prevPos,s.length()-prevPos);
			//return returnStr;
		}
		
		/**
		 * @brief Prints an array of string
		 * 
		 * @param str the string array to be printed
		 */
		static void printStringArray(string str[255]){
			for(int _=0;_<255;_++){cout << str[_] << ",";}
		}
		
		void printTable(){
		    for(int r=0;r<1000;r++){
		        for(int c=0;c<255;c++){
		            if(elements[r][c]!=""){
		                cout << setw(15) << elements[r][c];
		            }
		        }
		        cout << endl;
		    }
		}
		
		/**
		 * @brief Reads the csv files and store them
		 * 
		 * @param fileLocation the path to the file
		 * @return true The result is successfully stored
		 * @return false There is an error during file reading.
		 */
		bool readCSV(string fileLocation){
			if(!fileExist(fileLocation)){
				return false;
			}
		    int dum;
		    //cout << fileLocation.c_str();
		    //cin >> dum;
			FILE* csvfiles=fopen(fileLocation.c_str(),"r");
			if(csvfiles==NULL){return false;}
			char line[255];
			int i=0;
			while (fgets(line, sizeof line, csvfiles) != NULL ){
				//cout << line;
				cout<<i << ". ";
				split(line,",",elements[i]);
				i++;
				cout << endl;
			}
			fclose(csvfiles);
			cout << elements[76][1];
			return true;
		}
		
		string getElement(int r,int c){
			return elements[r][c];
		}
		
		void setElement(string val,int r,int c){
			elements[r][c] = val;
		}
		
		void saveCSV(string fileLocation){
			FILE* fw = fopen(fileLocation.c_str(),"w");
			int skipLine = 0;
			for(int r=0;r<1000;r++){
				for(int c=0;c<255;c++){
					if(elements[r][c]==""){
						skipLine++;
						continue;
					}
					fprintf(fw,"%s",elements[r][c].c_str() );
					if(c!=254){fprintf(fw,",");}
				}
				if(skipLine!=255){
					fprintf(fw,"\n");
				}
			}
			fclose(fw);
		}
		
	private:
		string elements[1000][255];
			
};

class Books{
	public:
		Books(string bkid,string bkname,string bkauthor, string bkpub, int bkyr){
			bk_id = bkid;
			bk_name = bkname;
			bk_author = bkauthor;
			bk_pub = bkpub;
			bk_yr = bkyr;
		}
		Books(CSVObject csv){
			bk_id = csv.getElement(1,1);
		}
	private:
		string bk_id;
		string bk_name;
		string bk_author;
		string bk_pub;
		int bk_yr;
};

class Borrower{
	public:
		Borrower(string f_name,string l_name, string phone_no){
			fname = f_name;
			lname = l_name;
			phoneno = phone_no;
		}
	private:
		string fname;
		string lname;
		string phoneno;
};

//Variables declaration here
CSVObject bookList;
CSVObject borrowList;

//Custom functions here
bool checkYNvalid(char choice){
    return (choice=='Y'||choice=='N');
}

bool checkYN(char choice){
    return (choice=='Y');
}

//Main functions here
void manageBooks(){

}

void manageBorrowers(){
	
}

void borrowBook(){

}

void returnBook(){

}

void usefulFeaturesMenu(){

}

//MAIN FUNCTION

int main(){
    char choice;
    //Check if user wants to import from file for book list
    do{
        cout << "Import book list from file? [Y/N]: ";
        cin >> choice;
        if(!checkYNvalid(choice)){
            cout << "Invalid input, please type again.\n";
		}
    }while(!checkYNvalid(choice));
	if(checkYN(choice)){
	    string path;
	    cout << "Path of book list file: ";
	    cin >> path;
	    cout << "Importing book list... ";
	    if(bookList.readCSV(path))
	    	cout << "Done\n";
		else
			cout << "Error while importing. Book list will not be imported.\n";
	}
	else{
	    cout << "No book list is imported \n";
	}
	
	//Check if user wants to import from file for borrow list
    do{
        cout << "Import borrower list from file? [Y/N]: ";
        cin >> choice;
        if(!checkYNvalid(choice))
            cout << "Invalid input, please type again.\n";
    }while(!checkYNvalid(choice));
	if(checkYN(choice)){
	    string path;
	    cout << "Path of borrower list file: ";
	    cin >> path;
	    cout << "Importing borrower list... ";
	    if(borrowList.readCSV(path))
	    	cout << "Done\n";
		else
			cout << "Error while importing. Borrower list will not be imported.\n";
	}
	else{
	    cout << "No borrower list is imported \n";
	}
	
	cout << bookList.getElement(260,1) << endl;
	
	//MAIN MENU
	do{
		cout << "*** Library Management System ***" << endl;
		cout << "[1] Manage books" << endl;
		cout << "[2] Manage borrowers" << endl;
		cout << "[3] Borrow book(s)" << endl;
		cout << "[4] Return book(s)" << endl;
		cout << "[5] Useful feature(s) added" << endl;
		cout << "[6] Member List" << endl;
		cout << "[7] Exit" << endl;
		cout << "*********************************" << endl;
		cout << "Option (1 - 7): " << endl;
		cin >> choice;

		switch (choice){
			case '1': manageBooks(); break;
			case '2': manageBorrowers(); break;
			case '3': borrowBook(); break;
			case '4': returnBook(); break;
			case '5': usefulFeaturesMenu(); break;
			case '6': memberList(); break;
			case '7': /*Do nothing*/ break;
		}
	}while(choice!='7');

	cout << "Exiting program. Goodbye!";

	return 0;
}