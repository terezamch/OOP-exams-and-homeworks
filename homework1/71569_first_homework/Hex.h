#ifndef HEX_H
#define HEX_H


class Hex{


public:

        Hex();
        Hex(const char*);
        Hex(const Hex&);
        Hex& operator=(const Hex&);
        ~Hex();
        
        bool isValidHex(const char*) const;
        void setHex(const char*);
        void setHex(int);
        
        const char* toHeximal(int) const;
        int toDecimal() const;
        size_t getLength() const;
        
        void print() const;

        Hex& operator+=(const Hex&);
        const Hex operator+(const Hex&) const;
        const Hex operator-(const Hex&) const;

        bool operator==(const Hex&) const;
        bool operator!=(const Hex&) const;
        bool operator>(const Hex&) const;
        bool operator>=(const Hex&) const;
        bool operator<(const Hex&) const;
        bool operator<=(const Hex&) const;        

private:

        static const size_t MAX_CAPACITY = 100;
        char* number;
        size_t length;
        
        




};


#endif
