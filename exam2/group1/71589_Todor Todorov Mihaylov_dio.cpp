//Inheritance
//Encapsulation
//Abstraction
//Polymorphism

#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
using namespace std;

class Musical_skill {
private:
	char* name;
	int skill;

public:
	Musical_skill(char* name = "", int skill = 0) {
		this->name = new char[strlen(name) + 1];
		assert(this->name != NULL);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->skill = skill;
	}

	~Musical_skill() {
		delete[]name;
	}

	Musical_skill(const Musical_skill &other) {
		name = new char[strlen(other.name) + 1];
		assert(name != NULL);
		strcpy_s(name, strlen(other.name) + 1, other.name);
		skill = other.skill;
	}

	Musical_skill &operator =(const Musical_skill &other) {
		if (this != &other) {
			delete[]name;

			name = new char[strlen(other.name) + 1];
			assert(name != NULL);
			strcpy_s(name, strlen(other.name) + 1, other.name);
			skill = other.skill;
		}
		return*this;
	}

	void setName(char* name) {
		delete[]name;
		this->name = new char[strlen(name) + 1];
		assert(this->name != NULL);
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	const char* getName() const {
		return name;
	}

	void setSkill(int skill) {
		this->skill = skill;
	}

	const int getSkill() const {
		return skill; 
	}
};

class Musician {
protected:
	char* name;
	int beauty;
	int defects;
	Musical_skill* musical_skills[5];

public:
	virtual void setName(char* name) = 0;  //definition?
	virtual const char* getName() const = 0; //definition?
	virtual const double getBeauty() const = 0;
	virtual const int getDefects() const = 0;
	virtual const Musical_skill getBest() const = 0; //definition?
	virtual const char* getType() const = 0;

	Musician(char* name = "", int beauty = 0, int defects = 0) {
		this->name = new char[strlen(name) + 1];
		assert(this->name != NULL);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->beauty = beauty;
		this->defects = defects;
	}

	virtual ~Musician() {
		delete[]name;
	}

	Musician(const Musician &other) {
		name = new char[strlen(other.name) + 1];
		assert(name != NULL);
		strcpy_s(name, strlen(other.name) + 1, other.name);
		beauty = other.beauty;
		defects = other.defects;
		
		for (int i = 0; i < 5; i++) {
			musical_skills[i] = other.musical_skills[i];
		}
	}

	Musician &operator =(const Musician &other) {
		if (this != &other) {
			delete[]name;

			name = new char[strlen(other.name) + 1];
			assert(name != NULL);
			strcpy_s(name, strlen(other.name) + 1, other.name);
			beauty = other.beauty;
			defects = other.defects;

			for (int i = 0; i < 5; i++) {
				musical_skills[i] = other.musical_skills[i];
			}
		}
		return*this;
	}
};

class RockMusician : virtual public Musician { //why virtual?
private:
	const double pi = 3.1415926535897;

public:
	virtual const double getBeauty() const {
		int sum = 0;
		for (int i = 0; i < 5; i++) {
			if (musical_skills[i]) {
				sum++;
			}
		}

		return pow(beauty, 2) + sum - defects * 3 * pi;
	}

	virtual const int getDefects() const {
		return defects;
	}

	virtual const char* getType() const {
		return "rock";
	}

	RockMusician(char* name = "", int beauty = 0, int defects = 0) : Musician(name, beauty, defects) {

	}

	virtual ~RockMusician() {

	}

	RockMusician(const RockMusician &other) : Musician(other) {

	}

	RockMusician &operator =(const RockMusician &other) {
		if (this != &other) {
			Musician::operator =(other);
		}
		return*this;
	}
};

class ChalgaMusician : virtual public Musician {
private:
	bool raceBonus;

public:
	virtual const double getBeauty() const {
		return pow(beauty, 5) + defects + raceBonus;// *cos(musical_skills[5]);
	}

	virtual const int getDefects() const {
		return defects;
	}

	virtual const char* getType() const {
		return "rock_tack";
	}

	ChalgaMusician(char* name = "", int beauty = 0, int defects = 0) : Musician(name, beauty, defects) {

	}

	virtual ~ChalgaMusician() {

	}

	ChalgaMusician(const ChalgaMusician &other) : Musician(other) {

	}

	ChalgaMusician &operator =(const ChalgaMusician &other) {
		if (this != &other) {
			Musician::operator =(other);
		}
		return*this;
	}
};

class Band {
protected:
	char* name;
	Musician* musicians[10];
	int size;

public:
	Band(char* name = "", int size = 0) {
		this->name = new char[strlen(name) + 1];
		assert(this->name != NULL);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->size = size;
	}

	virtual ~Band() {
		delete[]name;
	}

	Band(const Band &other) {
		name = new char[strlen(other.name) + 1];
		assert(name != NULL);
		strcpy_s(name, strlen(other.name) + 1, other.name);
		size = other.size;
//musicians?
	}

	Band &operator =(const Band &other) {
		if (this != &other) {
			delete[]name;

			name = new char[strlen(other.name) + 1];
			assert(name != NULL);
			strcpy_s(name, strlen(other.name) + 1, other.name);
			size = other.size;
//musicians?
		}
		return*this;
	}

	virtual void addMusician(Musician* musician) = 0;
	virtual void removeMusician(char* name) = 0;
	virtual double getAverageBeauty() = 0;
	virtual int totalScore() = 0;
};

class RockBand : virtual public Band {
public:
	RockBand(char* name = "", int size = 0) : Band(name, size) {

	}

	virtual ~RockBand() {
	
	}

	RockBand(const RockBand &other) : Band(other) {

	}

	RockBand &operator =(const RockBand &other) {
		if (this != &other) {
			Band::operator =(other);
		}
		return*this;
	}

	virtual void addMusician(Musician* musician) {
		if ((!strcmp(musician->getType(), "rock"))) { // или имат умение на даден инструмент повече от 100. 
			musicians[size++] = musician;
		}
	}

	virtual void removeMusician(char* name) {
		for (int i = 0; i < 10; i++) { //i < size
			if (!strcmp(musicians[i]->getName(), name)) {
				musicians[i] = musicians[i + 1];

				for (int j = i + 1; j < 10; j++) {
					musicians[j] = musicians[j + 1];
				}
				size--;
			}
		}
	}

	virtual double getAverageBeauty() {
		int sum = 0;
		int counter = 0; //counter == size?
		for (int i = 0; i < 10; i++) { // i < size?
			sum += musicians[i]->getBeauty();
			counter++;
		}
		return sum / counter;
	}

	virtual int totalScore() {

	}
};

class ChalgaBand : virtual public Band {
public:
	ChalgaBand(char* name = "", int size = 0) : Band(name, size) {

	}

	virtual ~ChalgaBand() {

	}

	ChalgaBand(const ChalgaBand &other) : Band(other) {

	}

	ChalgaBand &operator =(const ChalgaBand &other) {
		if (this != &other) {
			Band::operator =(other);
		}
		return*this;
	}
	
	virtual void addMusician(Musician* musician) {
		if ((!strcmp(musician->getType(), "rock_tack"))) { // или имат умение на даден инструмент по-малко от 10. 
			musicians[size++] = musician;
		}
	}

	virtual void removeMusician(char* name) {
		for (int i = 0; i < 10; i++) {
			if (!strcmp(musicians[i]->getName(), name)) {
				musicians[i] = musicians[i + 1];

				for (int j = i + 1; j < 10; j++) {
					musicians[j] = musicians[j + 1];
				}
				size--;
			}
		}
	}

	virtual double getAverageBeauty() {
		int sum = 0;
		int counter = 0;
		for (int i = 0; i < 10; i++) {
			sum += musicians[i]->getBeauty();
			counter++;
		}
		return sum / counter;
	}

	virtual int totalScore() {

	}
};

class FolkRockBand : public RockBand, public ChalgaBand {
public:
	FolkRockBand(char* name = "", int size =0) : Band(name, size), RockBand(name, size), ChalgaBand(name, size) {

	}

	virtual ~FolkRockBand() {

	}

	FolkRockBand(const FolkRockBand &other) : Band(other), RockBand(name), ChalgaBand(name) {

	}

	FolkRockBand &operator =(const FolkRockBand &other) {
		if (this != &other) {
			Band::operator =(other);
			RockBand::operator =(other);
			ChalgaBand::operator =(other);
		}
		return*this;
	}
	
	virtual void addMusician(Musician* musician) {
		if ((!strcmp(musician->getType(), "rock"))) {
			RockBand::addMusician(musician);
		}

		if ((!strcmp(musician->getType(), "rock_tack"))) {
			ChalgaBand::addMusician(musician);
		}
	}

	virtual void removeMusician(char* name) {
		for (int i = 0; i < 10; i++) {
			if (!strcmp(musicians[i]->getName(), name)) {
				musicians[i] = musicians[i + 1];

				for (int j = i + 1; j < 10; j++) {
					musicians[j] = musicians[j + 1];
				}
				size--;
			}
		}
	}

	virtual double getAverageBeauty() {
		int sum = 0;
		int counter = 0;
		for (int i = 0; i < 10; i++) {
			sum += musicians[i]->getBeauty();
			counter++;
		}
		return sum / counter;
	}

	virtual int totalScore() {

	}
};

int main() {
	return 0;
}
