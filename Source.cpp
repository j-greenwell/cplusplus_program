// Jacob Greenwell

#include<iostream>
#include<ctime>
#include<iomanip>
#include <windows.h>
#include <limits>

#undef max  

using namespace std;

class HMS {   // Class for getting local time
public:
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int hour = timePtr->tm_hour;
	int minute = timePtr->tm_min;
	int second = timePtr->tm_sec;
};

class hours_12 :public HMS {  // Class for setting 12 hour format time
public:
	string dayNight;

	hours_12() {          // Setting AM or PM to time
		if (hour == 0 ) {
			dayNight = "AM";
			hour = hour + 12;
		}
		else if (hour > 0 && hour <= 12) {
			dayNight = "AM";
		}
		else if (hour > 12) {
			
			dayNight = "PM";
			hour -= 12;
		}

	}
		void add_hour(int h) {    // Add hour function for 12 hour clock
			hour += h;
			if (hour > 12) {
				hour = hour - 12;
			}
			else if (hour >= 12) {
				if (dayNight == "AM") {
					dayNight = "PM";
				}
				else if (dayNight == "PM") {
					dayNight = "AM";
				}
			}
		}

		void add_minute(int min) {    // Add minute function for 12 hour clock
			minute += min;
			if (minute >= 60) {
				int h = minute / 60;
				minute -= 60 * h;
				add_hour(h);
			}
		}

		void add_second(int sec) {    // Add second function for 12 hour clock
			second += sec;
			if (second >= 60) {
				int m = second / 60;
				second -= 60 * m;
				add_minute(m);
			}
		}
};

class hours_24 :public HMS {   // Class for 24 hour format time;
public:
	
	void add_hour(int h){   // Add hour function for 24 hour clock
		hour += h;
		if (hour >= 24){
			hour -= 24;
		}
	}
	
	void add_minute(int min){   // Add minute function for 24 hour clock
		minute += min;
		if (minute >= 60){
			int h = minute / 60;
			minute -= 60 * h;
			add_hour(h);
		}
	}

	void add_second(int sec){    // Add second function for 24 hour clock
		second += sec;
		if (second >= 60){
			int m = second / 60;
			second -= 60 * m;
			add_minute(m);
		}		
	}
};

void clocks(hours_12 c12, hours_24 c24) {     // function for printing both 12 and 24 hr clocks	
	    
	    system("cls");
		cout << "#######################\t\t";
		cout << "#######################\n";
		cout << "#    12-Hour Clock    #\t\t";
		cout << "#    24-Hour Clock    #\n";
		cout << "#     ";
		cout << setw(2) << setfill('0') << c12.hour << ":" << setw(2) << setfill('0') << c12.minute << ":" << setw(2) << setfill('0') << c12.second << " " << c12.dayNight;
		cout <<	"     #\t\t";
		cout << "#      ";
		cout << setw(2) << setfill('0') << c24.hour << ":" << setw(2) << setfill('0') << c24.minute << ":" << setw(2) << setfill('0') << c24.second;
		cout << "       #\n";
		cout << "#######################\t\t";
		cout << "#######################\n";
}

int main() {  // Main function
	hours_12 c12;
	hours_24 c24;

	int input = 0;

	while (true) {   // loop for printing menu, clocks and getting input from user

		clocks(c12, c24);
		cout << "\n\n#########################\n";
		cout << "#  1 - Add One Hour\t#\n";
		cout << "#  2 - Add One Minute\t#\n";
		cout << "#  3 - Add One Second\t#\n";
		cout << "#  4 - Exit Program\t#\n";
		cout << "#########################\n";

		cin >> input;

		if (input == 1) {        // if else statements for adding hour, minute, second and to exit program.
			c12.add_hour(1);
			c24.add_hour(1);
		}
		else if (input == 2) {
			c12.add_minute(1);
			c24.add_minute(1);
		}
		else if (input == 3) {
			c12.add_second(1);
			c24.add_second(1);
		}
		else if (input == 4) {
			break;
		}
		else {
			cin.clear();     // clears input and prevents infinite loop if character is used instead of integer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "INVAILD INPUT" << endl;
			Sleep(750);   // delays output to display for a certain amount of time
		}
	}
}