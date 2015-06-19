#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>
#include <stdlib.h>
using namespace std;

class Hex
{
private:
    int decimal;
    char* number;
    int max_size = 100;
    int real_size;
    void del ()
    {
        delete [] number;
    }

    void cpy (const Hex& other)
    {
        number = new char [strlen(other.number) +1];
        assert (number != NULL);
        for (int i = 0; i < other.real_size; i++)
        {
            number[i] = other.number[i];
        }

        real_size = other.real_size;
        max_size = other.max_size;
    }

public:
    Hex (int real_size, char* number)
    {
        this->real_size = real_size;
        this->number = new char [(strlen(number)) + 1];
        assert (this->number != NULL);
        for (int i = real_size; i >= 0; i--)
        {
            this-> number[i] = number[i];
        }
    }

    ~Hex ()
    {
        del();
    }

    Hex (const Hex& other)
    {
        cpy (other);
    }


    Hex &operator = (const Hex& other)
    {
        if (this != &other)
        {
            del ();
            cpy (other);
        }
        return *this;
    }

    void reverseNumber (char* number)
    {
        for (int i = 0; i < real_size/2; i++)
        {
            char tmp = number[i];
            number[i] = number[real_size - i -1];
            number[real_size - i - 1] = tmp;
        }

    }

    void print ()
    {
        reverseNumber(number);
        cout << "Chisloto e " << number << endl;
    }

    int hexToDec (char* number)
    {
        decimal = 0;
        for (int i = 0; i < real_size; i++)
        {
            if ((number[i] >= 'A' && number[i] <= 'F') || (number[i] >= '1' && number[i] <= '9' ))
            {
                int tmp = 0;
                switch (number[i])
                {
                    case 'A': tmp = 10; break;
                    case 'B': tmp = 11; break;
                    case 'C': tmp = 12; break;
                    case 'D': tmp = 13; break;
                    case 'E': tmp = 14; break;
                    case 'F': tmp = 15; break;
                    case '1': tmp = 1; break;
                    case '2': tmp = 2; break;
                    case '3': tmp = 3; break;
                    case '4': tmp = 4; break;
                    case '5': tmp = 5; break;
                    case '6': tmp = 6; break;
                    case '7': tmp = 7; break;
                    case '8': tmp = 8; break;
                    case '9': tmp = 9; break;
                }
                decimal += tmp * (pow(16, i));
            }
        }
        return decimal;
    }

    int &operator + (const Hex& other)
    {
        int new_number = hexToDec(this->number) + hexToDec(other.number);
        return (new_number);
    }

    int &operator - (const Hex& other)
    {
        int new_number = hexToDec(this->number) - hexToDec(other.number);
        return new_number;
    }

    int &operator * (const Hex& other)
    {
        int new_number = hexToDec(this->number)* hexToDec(other.number);
        return new_number;
    }

    bool operator > (const Hex& other)
    {
        return hexToDec(this->number) > hexToDec(other.number);

    }

};

int main ()
{

    Hex a (3, "A86");
    Hex b (3, "351");
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    bool c = b > a ;
    cout << "b > a ? " << c << endl;
    bool d = a > b;
    cout << "a > b ? " << d << endl;

    return 0;
}
