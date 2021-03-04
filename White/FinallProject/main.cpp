#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <algorithm>

struct Date{
	int year, month, day;
	
	bool operator<(const Date& rhs) const{
		if(year != rhs.year)
			return year < rhs.year;
		else if(month != rhs.month)
			return month < rhs.month;
		else if(day != rhs.day)
			return day < rhs.day;
		return false;
	}
	
	bool operator==(const Date& rhs) const{
		if(	year == rhs.year &&
			month == rhs.month &&
			day == rhs.day){
				return true;
		}
		return false;
	}
	
	friend std::ostream& operator<<(std::ostream& stream, Date& date);
};

std::ostream& operator<<(std::ostream& stream, Date& date){
	std::cout << std::setfill('0');
		std::cout 	<< std::setw(4)
					<< date.year << '-'
					<< std::setw(2)
					<< date.month << '-'
					<< std::setw(2) << date.day;
	return stream;
}

std::istream& operator>>(std::istream& stream, Date& date){
	std::string allDate;
	if(!(stream >> allDate)){
		throw std::runtime_error("Wrong date format:");
	}
	
	std::stringstream ss(allDate);
	if(!(ss >> date.year)){
		std::string in; stream >> in;
		throw std::runtime_error("Wrong date format: " + allDate);
	}
	
	if(ss.peek() != '-')
		throw std::runtime_error("Wrong date format: " + allDate);
	ss.ignore(1);
	
	if(!(ss >> date.month)){
		std::string in; stream >> in;
		throw std::runtime_error("Wrong date format: " + allDate);
	}
	
	if(ss.peek() != '-')
		throw std::runtime_error("Wrong date format: " + allDate);
	ss.ignore(1);
	
	if(!(ss >> date.day)){
		std::string in; stream >> in;
		throw std::runtime_error("Wrong date format: " + allDate);
	}
	
	if(date.month < 1 || date.month > 12)
		throw std::runtime_error("Month value is invalid: " +
						std::to_string(date.month));
	if(date.day < 1 || date.day > 31)
		throw std::runtime_error("Day value is invalid: " +
						std::to_string(date.day));
	
	if(ss.peek() != EOF)
		throw std::runtime_error("Wrong date format: " + allDate);
	return stream;
}

class Data{
public:
	void Add(const Date& dt, const std::string& event){
		data[dt].insert(event);
	}
	
	void Print() const{
		for(const auto& item: data){
			Date founded = item.first;
			for(const std::string& item2: item.second){
				std::cout << founded << ' ' << item2 << '\n';
			}
		}
	}
	
	void Find(const Date& date){
		if(data.count(date)){
			for(const std::string& item: data[date]){
				std::cout << item << '\n';
			}
		}
	}
	
	int EventDelete(const Date& date, const std::string& event){
		std::set<std::string> founded;
		try{
			founded = data.at(date);
		}
		catch(...){
			return 1;
		}
		
		if(founded.count(event)){
			data[date].erase(event);
			return 0;
		}
		return 1;
	}
	
	int DateDelete(const Date& date){
		std::set<std::string> founded;
		try{
			founded = data.at(date);
		}
		catch(...){
			return 0;
		}
		
		int result = founded.size();
		data.erase(date);
		return result;
	}
	
private:
	std::map<Date, std::set<std::string> > data;
};

int main(){
	Data data;
	std::string userLine;
	while(std::getline(std::cin, userLine) && userLine != "\x4"){
		if(userLine == "")
			continue;
		std::stringstream y(userLine);
		std::string command; y >> command;
		
		if(command == "Add"){
			std::string probablyDate;
			if(!(y >> probablyDate)){
				std::cout << "Wrong date format:";
				break;
			}
			std::stringstream ss(probablyDate);
			Date newDate;
			try{
				ss >> newDate;
			}
			catch(const std::exception& ex){
				std::cout << ex.what();
				break;
			}
			std::string event;
			if(!(y >> event)){
				std::cout << "Wrong date format: " << probablyDate;
				break;
			}
			data.Add(newDate, event);
		}
		else if(command == "Print"){
			data.Print();
		}
		else if(command == "Del"){
			Date curDate;
			try{
				y >> curDate;
			}
			catch(const std::exception& ex){
				std::cout << ex.what();
				break;
			}
			
			std::string event;
			if(!(y >> event)){
				std::cout << "Deleted " << data.DateDelete(curDate) << " events\n";
			}
			else{
				if(data.EventDelete(curDate, event)){
					std::cout << "Event not found\n";
				}
				else{
					std::cout << "Deleted successfully\n";
				}
			}
		}
		else if(command == "Find"){
			Date newDate;
			try{
				y >> newDate;
			}
			catch(const std::exception& ex){
				std::cout << ex.what() << '\n';
				break;
			}
			
			data.Find(newDate);
		}
		else{
			std::cout << "Unknown command: " << command;
			break;
		}
	}
	return 0;
}
