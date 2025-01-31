#ifndef FIO_H
#define FIO_H
#include <string>
#include <iostream>
struct FIO{
	std::string surname;
  std::string name;
  std::string patronymic;
	FIO (const std::string& surname, const std::string& name, const std::string& patronymic): surname(surname), name(name), patronymic(patronymic) {}

	bool operator > (const FIO& other) const {
		if (surname != other.surname){
			return surname >other.surname;
		}
		if (name != other.name){
			return name > other.name;
		}
		return patronymic > other.patronymic;
	}

	bool operator < (const FIO& other) const {
		if (surname != other.surname){
			return surname < other.surname;
		}
		if (name != other.name){
			return name < other.name;
		}
		return patronymic < other.patronymic;
	}

	bool operator == (const FIO& other) const {
		return (surname == other.surname && name == other.name && patronymic == other.patronymic);
	}

	bool operator<=(const FIO& other) const {
    return *this < other || *this == other;
    }

  bool operator>=(const FIO& other) const {
    return *this > other || *this == other;
    }

};
#endif 