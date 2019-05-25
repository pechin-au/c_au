#pragma once

#include <unordered_map>
#include <string>
#include <utility>
#include <cstdint>
#include <ctime>
#include <set>

enum speciality {Veterinarian, Cashier, Consultant};

class Animal; {
private:
	std::string species;
	std::string shortName;
	std::string name;
	time_t birthdate;
	bool gender;			// BEN SHAPIRO DESTROYS LIBERALS WITH FACTS AND LOGIC
public:
	Animal(
		std::string species,
		std::string shortName,
		std::string name,
		time_t birthdate);
	std::string getSpecies() const;
	std::string getShortName() const;
	std::string getName() const;
	time_t getBirthdate() const;
	int64_t getAge() const;
	int64_t getAgeYears const;
};

class Human : public Animal; {
private:
	std::string surname;
public:
	Human(
		std::string name,
		std::string surname,
		bool gender,
		time_t birthdate
	);
	std::string getSurname() const;
	std::string getFullname() const;
};

class Worker : public Human; {
private:
	std::set<speciality> specialities;
public:
	Worker(
		std::string name,
		std::string surname,
		bool gender,
		time_t birthdate
	);
	void addSpeciality(speciality s);
	void removeSpeciality(speciality s);
	bool checkSpeciality(speciality s);
}