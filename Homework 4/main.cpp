#include "ActivityBST.h"
#include <iostream>
using namespace std;
void print_calendar(const ActivityBST& cal) {
	cout << "Calender:\n" << cal;
	ActivityBST study_sessions;
	study_sessions.add(1000, "study");
	study_sessions.add(1600, "study");
	cout << "Calender with study sessions:\n" << study_sessions + cal;
	ActivityBST meetings;
	meetings.add(1300, "meeting");
	meetings.add(900, "meeting");
	cout << "Calender with meetings:\n" << cal + meetings;
	ActivityBST complete_calendar;
	complete_calendar += cal;
	complete_calendar += study_sessions + meetings;
	cout << "Complete calendar:\n" << complete_calendar;
}
int main() {

	ActivityBST calendar;
	calendar.add(800, "breakfast");
	calendar.add(1200, "lunch");
	calendar.add(2000, "dinner");
	print_calendar(calendar);
	return 0;
}
