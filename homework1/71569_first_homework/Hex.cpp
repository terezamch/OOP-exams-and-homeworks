#include <iostream>
#include <cstring>
#include "Hex.h"

using namespace std;



const char* reverseHex(const char* number)
{
        size_t length = strlen(number) +1;
        char* temp = new char[length];
        for(size_t i = 0; i < length - 1; i++)
        {
                temp[i] = number[length - i - 2];
        }
        temp[length -1] = '\0';

        return temp;
        
}


bool isValidDigit(char ch)
{
        return ch >= '0' && ch <='9';
}        

bool isValidLetter(char ch)
{
        return ch >= 'A' && ch <= 'F';
}


int toInt(char ch)
{
        if(isValidDigit(ch))
                return ch - '0';

        if(isValidLetter(ch))
        {
                int num;
                switch(ch){
                        case 'A': num = 10; break;
                        case 'B': num = 11; break;
                        case 'C': num = 12; break;
                        case 'D': num = 13; break;
                        case 'E': num = 14; break;        
                        case 'F': num = 15; break;
                }
                return num;
        }
        return 0;
}        


char toChar(int num)
{
        char ch = (num >= 0 && num <=9) ? ('0' + num) :((num >= 10 && num <= 15) ? ('F' -
(15 - num)) : '?');
        
        return ch;

}

Hex::Hex()
:number(NULL)
{}

void Hex::setHex(const char* number)
{
        if(this->isValidHex(number))
        {
                        delete[] this->number;
                        this->length = strlen(number) + 1;
                        this->number = new char[length];
                        strcpy(this->number, number);
        }
        else
        {
                this->number = NULL;
        }

}



Hex::Hex(const char* number)
        :number(NULL)
{
        
                this->setHex(reverseHex(number));

}

Hex::Hex(const Hex& other)
        :number(NULL)
{
        this->setHex(other.number);

}

void Hex::setHex(int number)
{

        this->setHex(this->toHeximal(number));

}

Hex& Hex::operator=(const Hex& other)
{
        
        if(this == &other)
        {
                return *this;

        }

        this->setHex(other.number);
        return *this;

}


Hex::~Hex()
{
        delete[] this->number;

}

bool Hex::isValidHex(const char* number) const
{

        if(strlen(number) >= MAX_CAPACITY)
        {
                return false;
        }

        for(size_t i=0; i < strlen(number); i++)
        {
                if(!(isValidLetter(*(number + i)) || isValidDigit(*(number+i))))
                        return false;
        }
                
        return true;

}

size_t Hex::getLength() const
{
        return this->length;

}

int Hex::toDecimal() const // make long int - big numbers!!
{
        if(!number)
                return 0;
        int pow = 1;
        int decimal = 0;
        for(size_t i =0; this->number[i] ;i++)
        {        
                decimal += ((toInt(this->number[i]))*pow);
                pow *= 16;
                
        } 
        return decimal;

}


const char* Hex::toHeximal(int number) const
{
        int copy = number;
        size_t length =0;
        while(copy)
        {
		length++;
                copy /=16;
        }
        if(length > 99)
                return NULL;

	
        char* temp = new char[length +1];
        for(size_t i =0; i < length; i++)
        {
                temp[i] = toChar(number%16);
                number /=16;
        }
        temp[length] ='\0';
        return temp;

}



void Hex::print() const
{
        if(!number)
        {
                cout << "Error! Nothing to show, you must have entered an invalid number. " << endl;
                return;
        }
        
        cout << "Hexidecimal number is: " << reverseHex(this->number) << endl;
        return;

}

Hex& Hex::operator+=(const Hex& other)
{
        int newNumber = this->toDecimal() + other.toDecimal();
        this->setHex(newNumber);        

        return *this;
}

const Hex Hex::operator+(const Hex& other) const
{
        Hex result(*this);
        result += other;
        
        return result;
        
}

const Hex Hex::operator-(const Hex& other) const
{
        int newNumber = this->toDecimal() - other.toDecimal();

        Hex result(toHeximal((newNumber > 0 ? newNumber : (-newNumber))));
        return result;
}



bool Hex::operator==(const Hex& other) const
{
        return this->toDecimal() == other.toDecimal();
        
}

bool Hex::operator!=(const Hex& other) const
{
        return !(*this == other);

}        

bool Hex::operator<(const Hex& other) const
{
        return this->toDecimal() < other.toDecimal();
        
}

bool Hex::operator>(const Hex& other) const
{
        return !(*this < other || *this == other);

}

bool Hex::operator<=(const Hex& other) const
{
        return !(*this > other);
}

bool Hex::operator>=(const Hex& other) const
{

        return !(*this < other);

}




int main()
{

        // char* number= new char[10];
        
        //cout << "Enter number(hex): " << endl;
        //cin >> number;

        Hex tryout("AD");
        //cout << tryout.isValidHex("AD") << endl;
        //cout << tryout.getLength() << endl;
        //cout << toInt('A') << endl;
        //cout << isValidDigit('9') << " " << isValidLetter('A') << endl;
        //cout << reverseHex("AD4") <<endl;
        //cout<< tryout.toDecimal()<<endl;
        //cout << toInt('B') << " " << toInt('D') << " "<<toInt('0') << endl;
        //tryout.print();
        Hex check("CD");
        check.print();
        tryout.print();
        //cout << tryout.toHeximal(401) << endl;
        tryout += check;
        tryout.print();

        //Hex check1(tryout);
        //check1.print();
        //check1 = tryout + check;
        //check1.print();


        return 0;

}
