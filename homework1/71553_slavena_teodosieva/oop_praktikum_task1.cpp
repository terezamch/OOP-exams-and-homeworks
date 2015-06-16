#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>
using namespace std;
class Binary
{
    char* binaryNum;
    int sizeOfNum;
    int capacity;
public:
    Binary(char* binaryNum = "00", int sizeOfNum = 0, int capacity = 2)
    {
        this->sizeOfNum = sizeOfNum;
        this->capacity = capacity;
        this->binaryNum = new char[capacity];
        assert(this->binaryNum != NULL);
        strcpy(this->binaryNum, binaryNum);
    }
    Binary(const Binary& other)
    {
        sizeOfNum = other.sizeOfNum;
        capacity = other.capacity;
        binaryNum = new char[other.capacity];
        assert(binaryNum != NULL);
        strcpy(binaryNum, other.binaryNum);
    }
    ~Binary()
    {
        delete [] binaryNum;
    }
    Binary& operator=(const Binary& other)
    {
        if(this!=&other)
        {
            delete [] binaryNum;
            sizeOfNum = other.sizeOfNum;
            capacity = other.capacity;
            binaryNum = new char[other.capacity];
            assert(binaryNum != NULL);
            strcpy(binaryNum, other.binaryNum);
        }
        return *this;
    }
    void setSizeOfNum(int _size)
    {
        if(_size > 0)
            sizeOfNum = _size;
        else
            cout<<"Nevaliden razmer"<<endl;
    }
    void setCapacity(int _capacity)
    {
        if(_capacity > 0)
            capacity = _capacity;
        else
            cout<<"Nevaliden kapacitet"<<endl;
    }
    int getSizeOfNum() const
    {
        return sizeOfNum;
    }
    int getCapacity() const
    {
        return capacity;
    }
    char* getBinaryNum() const
    {
        return binaryNum;
    }
    void print()
    {
        cout<<"Binary"<<endl;
        cout<<"Size: "<<sizeOfNum<<endl
            <<"Capacity: "<<capacity<<endl
            <<"Binary number: "<<binaryNum<<endl;
    }
    bool operator==(const Binary& other)
    {
        if(!strcmp(this->binaryNum, other.binaryNum))
            return true;
        return false;
    }
    bool operator!=(const Binary& other)
    {
        if(strcmp(this->binaryNum, other.binaryNum) == 1 || strcmp(this->binaryNum, other.binaryNum) == -1)
            return true;
        return false;
    }
    bool operator>(const Binary& other)
    {
        return (this->getBinaryNum().fromBinary()) > (other.getBinaryNum().fromBinary());
    }
    bool operator<(const Binary& other)
    {
        return this->getBinaryNum().fromBinary() < other.getBinaryNum().fromBinary();
    }
    Binary operator+(const Binary& other)
    {
        int maxSize = 0;
        if(strlen(this->binaryNum) > strlen(other.binaryNum))
            maxSize = strlen(this->binaryNum);
        else
            maxSize = strlen(other.binaryNum);
        Binary result = new char[maxSize + 2];
        assert(result!=NULL);
        int tmp = this->getBinaryNum().fromBinary() + other.getBinaryNum().fromBinary();
        strcpy(result.binaryNum, toBinary(tmp));
        return result.binaryNum;
    }
    Binary operator-(const Binary& other)
    {
        int maxSize = 0;
        if(strlen(this->binaryNum) > strlen(other.binaryNum))
            maxSize = strlen(this->binaryNum);
        else
            maxSize = strlen(other.binaryNum);
        Binary result = new char[maxSize + 2];
        assert(result!=NULL);
        if(this->getBinaryNum().fromBinary() > other.getBinaryNum().fromBinary())
        {
            int tmp = this->getBinaryNum().fromBinary() - other.getBinaryNum().fromBinary();
            strcpy(result.binaryNum, toBinary(tmp));
            return result.binaryNum;
        }
        else
            return 0;
    }

    char* toBinary(int n)
    {
        int sizeOfNum = 0;
        int copyOfNum = n;
        while(copyOfNum != 0)
        {
            copyOfNum /= 10;
            sizeOfNum++;
        }
        binaryNum = new char[sizeOfNum+1];
        assert(binaryNum != NULL);
        itoa(n, binaryNum, 2);
        return binaryNum;
    }
    int fromBinary()
    {
        int sum = 0, k = 0;
        for(int i=sizeOfNum-1; i>=0; i--)
        {
            sum += this->binaryNum[i]*(pow(2,k));
            k++;
        }
        return sum;
    }
}; /*
int i = 0;
        do
        {
            binaryNum[i]=n%2;
            n=n/2;
            i++;
        } while(n!=0);
        int sizeOfNum = i;
        binaryNum[i]='\0';
        for(int i=0; i<sizeOfNum/2; i++)
        {
            char tmp = binaryNum[i];
            binaryNum[i] = binaryNum[sizeOfNum - i - 1];
            binaryNum[sizeOfNum - i - 1] = tmp;
        }
        return binaryNum; */
int main()
{
    Binary b1("1011", 4, 10);
    Binary b2("1001", 4, 10);
    b1.print();
    b2.print();
    if(b1 > b2) cout<< "cool"<<endl;
    else cout<<"fuck OOP"<<endl;
    //cout<< fromBinary("1001")<<endl;
    return 0;
}

