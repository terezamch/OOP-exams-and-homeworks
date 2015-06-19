#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;
struct Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	Date()
	{
		this->Day = 1;
		this->Month = 1;
		this->Year = 1900;
	}
Date(int Day, int Month, int Year)
{
	assert(Month > 0 && Month <= 12);
	assert(Year >= 1900);
	if (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12)
	{
		assert(Day > 0 && Day <= 31);
	}
	else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
	{
		assert(Day > 0 && Day <= 30);
	}
	else
	{
		if (((Year % 4 == 0) && (Year % 100 != 0)) || (Year % 400 == 0))
		{
			assert(Day > 0 && Day <= 29);
		}
		else
		{
			assert(Day > 0 && Day <= 28);
		}
	}
};

struct BusinessCard
{
private:
	char* Family;
	Date Birthday;
	void init(char* Family, Date Birthday)
	{
		this->Family = new char[strlen(Family) + 1];
		assert(this->Family != NULL);
		strcpy(this->Family, Family);
		this->Birthday = Birthday;
	}
public:
	char* getFamily()
	{
		return this->Family;
	}

	Date getBirthday()
	{
		return this->Birthday;
	}

	BusinessCard(char* Family, Date Birthday)
	{
		init(Family, Birthday);
	}

	BusinessCard()
	{
		init("no name", Date(1, 1, 1900));
	}

	BusinessCard(const BusinessCard& other)
	{
		init(other.Family, other.Birthday);
	}

	BusinessCard& operator= (const BusinessCard& other)
	{
		if (this != &other)
		{
			delete[] this->Family;
			init(other.Family, other.Birthday);
		}
		return *this;
	}

	~BusinessCard()
	{
		delete[] this->Family;
	}
};

class ListPerson
{
private:
	BusinessCard* Cards;
	int Capacity;
	int CardCount;
	void increaseCapacity(){
		BusinessCard* temp = new BusinessCard[this->Capacity];
		assert(temp != NULL);
		copyCards(this->Cards, temp, this->Capacity);
		delete[] this->Cards;
		this->Cards = new BusinessCard[this->Capacity * 2];
		assert(this->Cards != NULL);
		copyCards(temp, this->Cards, this->Capacity);
		this->Capacity *= 2;
		delete[] temp;
	}

	void copyCards(BusinessCard* source, BusinessCard* destination, int count){
		for (int i = 0; i < count; i++){
			destination[i] = source[i];
		}
	}

	int findCardByName(char* Family)
	{
		for (int i = 0; i < this->CardCount; i++)
		{
			if (strcmp(this->Cards[i].getFamily(), Family) == 0)
			{
				return i;
			}
		}
		return -1;
	}


public:
	void printCards()
	{
		for (int i = 0; i < this->CardCount; i++)
		{
			cout << this->Cards[i].getFamily() << endl;
		}
	}

	void addBusinessCard(BusinessCard& card)
	{
		assert(findCardByName(card.getFamily()) == -1);
		if (this->Capacity == this->CardCount)
		{
			increaseCapacity();
		}
		this->Cards[this->CardCount] = card;
		this->CardCount++;
	}

	BusinessCard* getBusinessCard(char* Family)
	{
		int index = findCardByName(Family);
		if (index != -1)
		{
			return this->Cards + index;
		}
		return NULL;
	}

	void deleteBusinessCard(char* Family)
	{
		int index = findCardByName(Family);
		if (index != -1)
		{
			for (int i = index; i < this->CardCount - 1; i++)
			{
				this->Cards[i] = this->Cards[i + 1];
			}
			this->CardCount--;
		}
	}

	ListPerson()
	{
		this->Cards = new BusinessCard[2];
		assert(this->Cards != NULL);
		this->Capacity = 2;
		this->CardCount = 0;
	}

	~ListPerson()
	{
		delete[] this->Cards;
	}
};

int main()
{
	BusinessCard num1("Kolio", Date(16, 11, 1995));
	BusinessCard num2("Samuil", Date(23, 6, 1992));
	BusinessCard num3("Dimitur", Date(22, 2, 1991));
	BusinessCard num5("Iliqn", Date(28, 2, 1969));
	BusinessCard num6("Nikolai", Date(66, 69, 1969));
	ListPerson list;
	list.addBusinessCard(num1);
	list.addBusinessCard(num2);
	list.addBusinessCard(num3);
	list.addBusinessCard(num5);
	list.addBusinessCard(num6);
	list.printCards();
	cout << endl;
	list.deleteBusinessCard("Dimitur");
	list.printCards();

	BusinessCard* card = list.getBusinessCard("Kolio");
	cout << card->getFamily();
	system("pause");
	return 0;
}
