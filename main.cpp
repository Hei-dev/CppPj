#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

class CSVObject {
	public :
		/**
		 * Split a string with a string delimitor into an array
		 * @param s - the string to be splitted
		 * @param delim - the string that decides the boundary for each element of the array
		 * @param returnStr[255] - the string array to be written into
		 */
		static void split(string s, string delim, string returnStr[255]){
			int findVal = 0, prevPos = 0;
			int strArrIdx = 0;
			do{
				findVal = s.find(delim, prevPos);
				if(findVal==string::npos){ //If it did not found a string
					continue;
				}
				//cout << "Found: " << findVal << endl;
				returnStr[strArrIdx] = s.substr(prevPos,findVal-prevPos);
				//cout << returnStr[strArrIdx] << " and " << s.substr(prevPos,findVal-1) << endl;
				prevPos = findVal+1;
				strArrIdx++;
			}while(findVal!=string::npos);
			returnStr[strArrIdx] = s.substr(prevPos,s.length()-prevPos);
			//return returnStr;
		}
		/**
		 * Split a string with a char delimitor into an array
		 *//*
		static void split_strtok(string s,const char* delim, string returnStr[255]){
			int strIdx = 0;
			char *token = strtok(s.c_str(),delim);
			while(token!=NULL){
				returnStr[strIdx] = token;
				token = strtok(NULL,delim);
			}
		}*/
		/**
		 * prints a string array
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
		
		void readCSV(string fileLocation){
		    int dum;
		    cout << fileLocation.c_str();
		    //cin >> dum;
			FILE* csvfiles=fopen(fileLocation.c_str(),"r");
			char line[255];
			int i=0;
			while (fgets(line, sizeof line, csvfiles) != NULL ){
				//cout << line;
				split(line,",",elements[i]);
				i++;
				cout<<i<<endl;
			}
			fclose(csvfiles);
		}
		
	private:
		string elements[1000][255];
			
};

bool checkYNvalid(string ynchoice){
    return (ynchoice=="Y"||ynchoice=="N");
}

bool checkYN(string ynchoice){
    return (ynchoice=="Y");
}

//Variables declaration here
CSVObject bookList;
CSVObject borrowList;

int main(){
    string ynchoice;
    //Check if user wants to import from file for book list
    do{
        cout << "Import book list from file? [Y/N]: ";
        cin >> ynchoice;
        if(checkYNvalid(ynchoice))
            cout << "Invalid input, please type again.\n";
    }while(checkYNvalid(ynchoice));
	if(checkYN(ynchoice)){
	    string path;
	    cout << "Path of book list file: ";
	    cin >> path;
	    cout << "Importing book list... ";
	    bookList.readCSV(path);
	    cout << "Done";
	}
	else{
	    cout << "No book list is imported ";
	}
	
	//Check if user wants to import from file for borrow list
    do{
        cout << "Import borrower list from file? [Y/N]: ";
        cin >> ynchoice;
        if(checkYNvalid(ynchoice))
            cout << "Invalid input, please type again.\n";
    }while(checkYNvalid(ynchoice));
	if(checkYN(ynchoice)){
	    string path;
	    cout << "Path of borrower list file: ";
	    cin >> path;
	    cout << "Importing borrower list... ";
	    borrowList.readCSV(path);
	    cout << "Done";
	}
	else{
	    cout << "No borrower list is imported ";
	}
	
	return 0;
}