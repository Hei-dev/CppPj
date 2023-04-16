#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include <filesystem>
//#include <regex>

using namespace std;

char dum;
int numbooks = 0;

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
		static int split(string s, string delim, string returnStr[255]){
			int findVal = 0, prevPos = 0;
			int strArrIdx = 0;
			//Iterate through each delim
			do{
				//Check if it is quoted
				//Somewhat hacky way to do it, but it's alright
				if((s.substr(prevPos==0 ? 0 : prevPos-1,2)==",\"") && delim==","){
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


				//cout << strArrIdx << ": " << returnStr[strArrIdx] << endl;
				//cout << prevPos << "," << findVal << endl;

				//cout << returnStr[strArrIdx] << " and " << s.substr(prevPos,findVal-1) << endl;
				prevPos = findVal+1;
				strArrIdx++;
			}while(findVal!=string::npos);
			returnStr[strArrIdx] = s.substr(prevPos,s.length()-prevPos);
			return strArrIdx;
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
				//cout<<i << ". ";
				split(line,",",elements[i]);
				i++;
			}
			fclose(csvfiles);
			//cout << elements[76][1];
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
		/**
		 * @brief Construct a new Books object with parameters
		 * 
		 * @param bkid The book's ID
		 * @param bkname The book's name
		 * @param bkauthor The book's author
		 * @param bkpub The book's publisher
		 * @param bkyr The book's year
		 */
		Books(string bkid,string bkname,string bkauthor, string bkpub, int bkyr){
			bk_id = bkid;
			bk_name = bkname;
			bk_author = bkauthor;
			bk_pub = bkpub;
			bk_yr = bkyr;
		}
		/**
		 * @brief Construct a new empty Books object
		 * 
		 */
		Books(){}
		void setBooks(string bkid,string bkname,string bkauthor, string bkpub, int bkyr){
			bk_id = bkid;
			bk_name = bkname;
			bk_author = bkauthor;
			bk_pub = bkpub;
			bk_yr = bkyr;
		}

		/**
		 * @brief Check if the provided book is the same as itself
		 * 
		 * @param bk the Books to compare
		 */
		bool equal(Books bk){
			return (
				bk_id == bk.getBookId()
			&&  bk_name == bk.getBookName()
			&&  bk_author == bk.getBookAuthor()
			&&  bk_pub == bk.getBookPublisher()
			&&  bk_yr == bk.getBookYear());
		}
		
		void setBookId(string id){bk_id = id;}
		void setBookName(string str){bk_name = str;}
		void setBookAuthor(string str){bk_author = str;}
		void setBookPublisher(string str){bk_pub = str;}
		void setBookYear(int yr){bk_yr = yr;}
		void setBookBorrowed(bool isBorrowed){bk_borrowed = isBorrowed;}
		string getBookId(){return bk_id;}
		string getBookName(){return bk_name;}
		string getBookAuthor(){return bk_author;}
		string getBookPublisher(){return bk_pub;}
		int getBookYear(){return bk_yr;}
		bool isBookBorrowed(){return bk_borrowed;}
	private:
		string bk_id;
		string bk_name;
		string bk_author;
		string bk_pub;
		int bk_yr;
		bool bk_borrowed = false;
};

class Borrower{
	public:
		Borrower(string f_name,string l_name, string phone_no){
			fname = f_name;
			lname = l_name;
			phoneno = phone_no;
		}
		Borrower(){}
		void setBorrower(string f_name,string l_name, string phone_no){
			fname = f_name;
			lname = l_name;
			phoneno = phone_no;
		}
		void setFirstName(string str){fname = str;}
		void setLastName(string str){lname = str;}
		void setPhoneNo(string str){phoneno = str;}
		/**
		 * @brief Borrow a book to the borrower
		 * 
		 * @param book the book to be borrowed
		 */
		bool addBorrowedBook(Books book){
			if(borrowedNo>=5){
				cout  << "Borrow limit reached, cannot borrow more books.";
				return false;
			}
			if(book.isBookBorrowed()){
				cout << "Book is already borrowed";
				return false;
			}
			for(Books bk:borrowedBooks){
				if(bk.equal(book)){
					cout << "Book is already borrowed";
					return false;
				}
			}
			borrowedBooks[borrowedNo] = book;
			borrowedNo++;
		}
		/**
		 * @brief return a book from the borrower
		 * 
		 * @param book the book to be returned
		 */
		void removeBorrowedBook(Books book){
			int i; bool flag = false;
			for(i=0;i<5;i++){
				Books bk = borrowedBooks[i];
				if(book.equal(bk)){
					flag=true;
					borrowedNo--;
				}
				if(flag && (i+1)<5){
					borrowedBooks[i] = borrowedBooks[i+1];
				}
				else if((i+1)<5){
					borrowedBooks[i] = Books();
				}
			}
			borrowedBooks[i] = borrowedBooks[i+1];
		}
		string getFirstName(){return fname;}
		string getLastName(){return lname;}
		string getPhoneNo(){return phoneno;}
		/**
		 * @brief Get the Borrowed Books object and *stores* it into the array provided
		 * 
		 * @param bks the array used to store the borrowed book
		 */
		void getBorrowedBooks(Books bks[]){bks = borrowedBooks;}
		/**
		 * @brief Get the number of borrowed books by the user.
		 * 
		 * @return int the total number of borrowed books by the borrower
		 */
		int getBorrowedNo(){return borrowedNo;}
	private:
		string fname;
		string lname;
		string phoneno;
		Books borrowedBooks[5];
		int borrowedNo = 0;
};

//Variables declaration here
CSVObject bookList;
CSVObject borrowList;

Books books[1000];
Borrower borrowers[1000];

//Custom functions here
bool checkYNvalid(char choice){
    return (choice=='Y'||choice=='N');
}

bool checkYN(char choice){
    return (choice=='Y');
}

bool checkEmptyString(string s){
    return s=="";
}
string toUppercase(string s){
    for(int i=0;i<s.length();i++){
        s = toupper(s[i]);
    }
	return s;
}
//Main functions here
//R1
void displayBooks(){

}

/**
 * @brief Search for the locations of double quotes (") in a string, and returns it in an integer array.
 * 
 * @param inp the string to search on
 * @param positions the int array to be stroed
 */
void findDoubleQuote(string inp, int positions[]){
	int pos = -1, i=0;
	do{
		pos = inp.find("\"",pos+1);
		//if(pos==-1){break;}
		positions[i] = pos;
		cout << "i: " << i  << ",Pos: " << pos << endl;
		i++;
	}while(pos!=string::npos || pos<inp.length() || pos!=-1);
	positions[i] = -1;
	positions[i+1] = -1;
	if(i%2==1){
		positions[i-1] = -1;
	}
}
/**
 * @brief Check if the book info contains keyword
 * 
 * @param bk the Book object to be searched
 * @param kw the keyword to be searched
 * @param caseSensitive if set to true, only exact cases will be matched
 */
bool checkMatchingBook(Books bk,string kw,bool caseSensitive){
	Books t_bk = bk;
    if(!caseSensitive){ //Case Insensitive
        t_bk.setBookName(toUppercase(t_bk.getBookName()));
        t_bk.setBookAuthor(toUppercase(t_bk.getBookAuthor()));
        t_bk.setBookPublisher(toUppercase(t_bk.getBookPublisher()));
		kw = toUppercase(kw);
    }
	cout << (t_bk.getBookName().find(kw)!=string::npos) << (t_bk.getBookAuthor().find(kw)!=string::npos) << (t_bk.getBookId().find(kw)!=string::npos) << (t_bk.getBookPublisher().find(kw)!=string::npos) << endl;
	return (
			(t_bk.getBookName().find(kw)!=string::npos)
		||  (t_bk.getBookAuthor().find(kw)!=string::npos)
		||  (t_bk.getBookId().find(kw)!=string::npos)
		||  (t_bk.getBookPublisher().find(kw)!=string::npos)
	);
}
//R1.2
void searchBooks(){
	/*
		Steps:
		-Read every char 1 by 1
		--if it is alphanumeric, concat it into a string
		--if it is a space, store the sring into an array, and reset the string
		--if it is a ",
		---if it is the first time, record it, ignore the following spaces until...
		---if second time, set quoted to false, and store the string into an array, and reset the string.
	*/
	string inp;
	string keywords[100];
	int quotePos[100];
	cout << "Please enter the keyword(s): ";
	cin.ignore(); //To make this work
	getline(cin, inp);
	
	int i=0;
	int j=0;
	string concatStr = "";
	bool isDoubleQuoted = false;
	//Phrase the keywords
	for(int i=0;i<inp.length();i++){
	    if(inp[i]==' ' && !isDoubleQuoted && concatStr!=""){
	        keywords[j] = concatStr;
	        cout << j << endl;
	        concatStr = "";
	        j++;
	    }
	    else if(inp[i]=='"'){
	        isDoubleQuoted = !isDoubleQuoted;
	        if(!isDoubleQuoted && concatStr!=""){
	            keywords[j] = concatStr;
	            //cout << "Quoted: " << j << concatStr << endl;
	            concatStr = "";
	            j++;
	        }
	    }
	    else{
	        concatStr+=inp[i];
	    }
	}
	keywords[j] = concatStr;
	
	//DEBUG print phrased keywords
	for(int i=0;i<100;i++){
		if(keywords[i]!=""){cout << i << keywords[i] << endl;}
	}
	
	//the find function SAVES AGAIN!
	for(int i=0;i<1000;i++){
	    for(string kw : keywords){
	        if(checkMatchingBook(books[i],kw,false) && !checkEmptyString(kw) && !checkEmptyString(books[i].getBookName())){
	            cout << "Searching " << kw << "\n";
				cout<<"Found: " << books[i].getBookId() << setw(18) << books[i].getBookYear() << endl << books[i].getBookName() << "\nBy " << books[i].getBookAuthor() << books[i].getBookPublisher() <<endl;
				cout << "================" << endl;
	        }
	    }
	}
}

//R1.2
[[deprecated("It does not work and overcomplicating lol")]]
void searchBooksD(){
	string inp;
	string keywords[100];
	int quotePos[100];
	cout << "Please enter the keyword(s): ";
	cin.ignore(); //To make this work
	getline (cin, inp);
	/*
		Steps:
		1. Extract Terms with "" and store them in an array
		1.5 Remove all keywords wrapped with "" in the string
		2. Split the remaining string with space
		3. Store them into an array.
	*/
	findDoubleQuote(inp,quotePos);
	string ninp = inp;
	if(quotePos[0]!=-1 || quotePos[1]!=-1){
		int i=0;
		int prevPos1 = 0, prevPos2 = 0;
		do{
			prevPos1 = quotePos[i];
			prevPos2 = quotePos[1+1];
			keywords[i] = inp.substr(prevPos1+1,prevPos2-1);
			cout << "K: " << keywords[i] << "," << quotePos[i] << "," << quotePos[i+1] << endl;
			ninp.erase(prevPos1,prevPos2-prevPos1+1);
			//prevPos1 = quotePos[i+1]+1;
			i+=2;
		}while(quotePos[i]!=-1);
	}
	
	string keyword_single[100];
	CSVObject::split(ninp," ",keyword_single);
	cout << ninp << endl;
	for(int i=0;i<100;i++){
		if(keywords[i]!=""){cout << i << keywords[i] << endl;}
		if(keyword_single[i]!=""){cout << i << "s: " << keyword_single[i] << endl;}
	}
	
}

bool idunique(string id) {
    for (int i = 0; i < numbooks; i++) {
        if (books[i].getBookId() == id) {
            return false;
        }
    }
    return true;
}

bool yearpositive(int year) {
    return year > 0;
}

void addBooks() {
    string id, title, author, publisher;
    int year;

    cout << "Enter book ID: ";
    getline(cin, id);
    while (id.length() > 10 || !idunique(id)) {
        cout << "This ID is more than 10 characters! Enter book ID:";
        cout << "Enter book ID:";
        getline(cin, id);
    }
        
    cout << "Enter book title: ";
    getline(cin, title);
    while (title.length() > 100) {
        cout << "The title is more than 100 characters!";
        cout << "Enter book title:";
        getline(cin, title);
    }

    cout << "Enter book author (if the book has more than one author, separated by ';'): ";
    getline(cin, author);
    while (author.length() > 50) {
        cout << "The authors are more than 50 characters!: ";
        cout << "Enter book author: ";
        getline(cin, author);
    }

    cout << "Enter book publisher: ";
    getline(cin, publisher);
    while (publisher.length() > 50) {
        cout << "The publisher is more then 50 characters!";
        cout << "Enter book publisher: ";
        getline(cin, publisher);
    }

    cout << "Enter book year: ";
    cin >> year;
    while (!yearpositive(year)) {
        cout << "The year is not positive!";
        cout << "Enter book year: ";
        cin >> year;
        cin.clear();
        cin.ignore(numeric_limits < streamsize > ::max(), '\n');
        cin.ignore();
    }
        
    cin.ignore();

    books[numbooks] = Books(id, title, author, publisher, year);
    numbooks++;

    cout << "Book added sucessfully!\n";
}


void removeBooks(){

}

//R1
void manageBooks(){
	char choice;
	do{
		cout << "*** Manage Books ***" << endl;
		cout << "[1] Display books" << endl;
		cout << "[2] Search book" << endl;
		cout << "[3] Add book" << endl;
		cout << "[4] Remove book" << endl;
		cout << "[5] Back" << endl;
		cout << "********************" << endl;
		cout << "Option (1 - 5):" << endl;

		cin >> choice;

		switch (choice){
			case '1': displayBooks(); break;
			case '2': searchBooks(); break;
			case '3': addBooks(); break;
			case '4': removeBooks(); break;
			case '5': break;
		}
	}while(choice!='5');
}

//R2
void displayBorrowers(){

}

void searchBorrowers(){

}

void addBorrowers(){

}

void removeBorrowers(){
	
}
//R2 main
void manageBorrowers(){
	char choice;
	do{
		cout << "*** Manage Books ***" << endl;
		cout << "[1] Display borrowers" << endl;
		cout << "[2] Search borrowers" << endl;
		cout << "[3] Add borrowers" << endl;
		cout << "[4] Remove borrowers" << endl;
		cout << "[5] Back" << endl;
		cout << "********************" << endl;
		cout << "Option (1 - 5):" << endl;

		cin >> choice;

		switch (choice){
			case '1': displayBorrowers(); break;
			case '2': searchBorrowers(); break;
			case '3': addBorrowers(); break;
			case '4': removeBorrowers(); break;
			case '5': break;
		}
	}while(choice!='5');
}

//R3
void borrowBook(){

}

//R4
void returnBook(){

}

//R5
void usefulFeaturesMenu(){

}

//MAIN FUNCTION

int main(){
    char choice;
    //Check if user wants to import from file for book list
    do{
        cout << "Import book list from file? [Y/N]: ";
        cin >> choice;
		choice = toupper(choice);
        if(!checkYNvalid(choice)){
            cout << "Invalid input, please type again.\n";
		}
    }while(!checkYNvalid(choice));
	if(checkYN(choice)){
	    string path;
	    cout << "Path of book list file: ";
	    cin >> path;
	    cout << "Importing book list... ";
	    if(bookList.readCSV(path)){
			for(int i=0;i<1000;i++){
				if(bookList.getElement(i,0)==""){continue;}
				books[i] = Books(
					bookList.getElement(i,0), //ID
					bookList.getElement(i,1), //Mame
					bookList.getElement(i,2), //Author
					bookList.getElement(i,3), //Publisher
					stoi(bookList.getElement(i,4)) //Year
				);
				numbooks++;
			}
	    	cout << "Done\n";
		}
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
		choice = toupper(choice);
        if(!checkYNvalid(choice))
            cout << "Invalid input, please type again.\n";
    }while(!checkYNvalid(choice));
	if(checkYN(choice)){
	    string path;
	    cout << "Path of borrower list file: ";
	    cin >> path;
	    cout << "Importing borrower list... ";
	    if(borrowList.readCSV(path)){
			for(int i=0;i<1000;i++){
				borrowers[i] = Borrower(
					borrowList.getElement(i,0), //First Name
					borrowList.getElement(i,1), //Last Name
					borrowList.getElement(i,2) //Phone number
				);
			}
			cout << "Done\n";
		}
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
			case '7':
				char quit;
				cout << "Are you sure you want to quit? (Y/N): ";
				do{
					cin >> quit;
					quit = toupper(quit);
					if(quit!='Y'||quit!='N'){cout << "invalid input. Please type again.";}
				}while(quit!='Y'||quit!='N');
			break;
		}
	}while(choice!='7');

	cout << "Exiting program. Goodbye!";

	return 0;
}