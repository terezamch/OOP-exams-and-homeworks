#include <iostream>
#include "ListPerson.h"

using namespace std;

ListPerson::ListPerson()
	: library(NULL), size(0), MAX_CAPACITY(0)
{}

ListPerson::ListPerson(size_t MAX_CAPACITY, size_t size)	
	: library(NULL), size(0), MAX_CAPACITY(0)
{	
	this->MAX_CAPACITY = MAX_CAPACITY;
	this->size = size;
	this->library = new Card[this->MAX_CAPACITY];

}

ListPerson::ListPerson(const ListPerson& other) 
	:library(NULL), size(0), MAX_CAPACITY(0)
{
	this->copyCards(other);

}


void ListPerson::copyCards(const ListPerson& other)
{

	delete[] this->library;
	this->size = other.size;
	this->MAX_CAPACITY = other.MAX_CAPACITY;
	this->library = new Card[this->MAX_CAPACITY];
	for(size_t i = 0; i < this->size; i++)
	{
		this->library[i] = other.library[i];
	}
	
}


ListPerson::~ListPerson()
{

	delete[] this->library;

}


ListPerson& ListPerson::operator=(const ListPerson& other)
{

	if(this != &other)
	{
			this->copyCards(other);
	}

	return *this;

}

int ListPerson::findCard(const char* fname) const
{	
	for(size_t i =0; i < this->size; i++)
	{
		if(!strcmp(this->library[i].familyName, fname))
		{	
			return i;	
		}

	}
	
	return -1;

}

Card& ListPerson::getCard(const char* fname) const
{
	//need to check if there is one at all
	return this->library[findCard(fname)];
			
}


void ListPerson::addCard(Card newCard)
{
	if(this->findCard(newCard.familyName) >= 0)
		return;

	if(this->size == this->MAX_CAPACITY)
	{
		this->MAX_CAPACITY *= 2;
		Card* temp = new Card[this->MAX_CAPACITY];
		for(size_t i = 0; i < this-> size; i++)
		{
			temp[i] = this->library[i];
			
		}
		delete[] this->library;
		this->library = temp;

	}

	this->library[this->size++] = newCard;	

}

void ListPerson::removeCard(const char* fname)
{
		
	size_t index = this->findCard(fname);
	if(index < 0)  //not found!
		return;

	this->library[index] = this->library[this->size-1];
	this->size--;


}


ListPerson& ListPerson::operator+=(const ListPerson& other)
{
	
	for(size_t i = 0; i < other.size; i++)
	{
		this->addCard(other.library[i]);

	}
	
	return *this;
}

ListPerson ListPerson::difference(const ListPerson& other) const
{
	ListPerson result(*this);

	for(size_t i =0; i < other.size; i++)
	{
		
		if(this->findCard(other.library[i].familyName) >= 0)
		{
			result.removeCard(other.library[i].familyName);
		}
	}
	
	return result;

}

ListPerson ListPerson::similarity(const ListPerson& other) const
{
	ListPerson result(this->MAX_CAPACITY > other.MAX_CAPACITY ? this->MAX_CAPACITY : other.MAX_CAPACITY,0);
	
	
	for(size_t i = 0; i < this->size; i++)
	{
		if(this->findCard(other.library[i].familyName) >= 0)
		{
			result.addCard(other.library[i]);
		}

	}
	
	return result;
	
}


const char* ListPerson::getSign(const char* fname) const
{
	return this->library[this->findCard(fname)].Sign;

}


void ListPerson::print() const
{
	for(size_t i = 0; i < this->size; i++)
	{
		this->library[i].printCard();

	}
	cout << endl;

}


int main()
{
	
	ListPerson pyrviopit;
	Card chovek1, chovek2;
	strcpy(chovek1.familyName, "Tedi");
	strcpy(chovek2.familyName, "Zahari");
	chovek1.birthDate.setDate(5,5, 1993);
	chovek2.birthDate.setDate(30, 8, 1993);
	
	Date bd(2,3,1990);
	Card chovek3 = { "TSA", bd};
//	strcpy(chovek3.familyName, "ABC");
//	chovek3.birthDate.setDate(2, 3, 1990);
    
    
	pyrviopit.addCard(chovek1);
	pyrviopit.addCard(chovek2);
	pyrviopit.addCard(chovek3);	

	pyrviopit.print();
	

	return 0;

}










