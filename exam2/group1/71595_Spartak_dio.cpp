#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

// абстракция, енкапсулация, полиморфизъм, наследяване

using namespace std;

//no time for nothing

struct MusicalSkill {
private:
    char*name;
    int skill;

    void del() {
        delete[]this -> name;
    }

    void copyMusicalSkill(char*n, int sk) {
        del(); //why del?
        this -> name = new char[strlen(n) + 1];
        assert(this -> name);
        strcpy(this -> name, n);

        this -> skill = sk;
    }

public:
    const int getSkill() const {
        return this -> skill;
    }

    MusicalSkill(char*n = "Piano", int sk = 3) {
        this -> name = NULL;
        copyMusicalSkill(n, sk);
    }

    ~MusicalSkill() {
        del();
    }

    MusicalSkill(const MusicalSkill &other) {
        copyMusicalSkill(other.name, other.skill);
    }

    MusicalSkill &operator=(const MusicalSkill &other) {
        if(this != &other) {
            copyMusicalSkill(other.name, other.skill);
        }
        return *this;
    }

};


class Musician {
private:
    char*musicName;
    int pretty;
    int sins;

protected:
    MusicalSkill*all;
    int size;
    int maxSize;

    void delmusician() {
        delete[]this -> musicName;
    }

    void copyMusician(char*mn, int pr, int s) {
        delmusician(); // ?
        this -> musicName = new char[strlen(mn) + 1];
        assert(this -> musicName);
        strcpy(this -> musicName, mn);

        this -> pretty = pr;

        this -> sins = s;
    }

public:
    const char*getName() const {
        return this -> musicName;
    }
    const int getPretty() const {
        return this -> pretty;
    }
    const int getSins() const {
        return this -> sins;
    }
    const int getSize() const {
        return this -> size;
    }

    Musician(char*mn = "Ivan", int pr = 40, int s = 5) {
        this -> musicName = NULL;
        this -> all = NULL;
        this -> size =0;
        this -> maxSize = 0;

        delmusician(); //?

        copyMusician(mn, pr, s);
    }

// maybe virtual
    ~Musician() {
        delmusician();
    }

    Musician(const Musician &other) {
        delmusician(); //?
        copyMusician(other.musicName, other.pretty, other.sins);
//copy musical skills?  
  }

    Musician &operator=(const Musician &other) {
        if(this != &other) {
           delmusician();
            copyMusician(other.musicName, other.pretty, other.sins);
        }
        return *this;
    }

    void addSkill(MusicalSkill &skillToAdd) {
        if(size == maxSize){
            if(maxSize == 0) maxSize = 2; //2?
            maxSize *= 2;

            MusicalSkill *temp = new MusicalSkill[maxSize];
            for(int i = 0; i < size; i++) {
                temp[i] = all[i];
            }
            delete[]all;
            all = temp;
        }
        all[size++] = skillToAdd;
    }

// will remove by skill
    void rmv(int sk) {
        if(maxSize > size / 2) {
            maxSize /= 2;
        }

        int index = -1;

        for(int i = 0; i < size; i++) {
            if(all[i].getSkill() == sk) {
                index = i;

                MusicalSkill *temp = new MusicalSkill[size - 1];

                for(int i = 0; i < index; i++) {
                    temp[i] = all[i];
                }

                for(int j = index; j < size - 1; j++) {
                    temp[j] = all[j + 1];
                }
                delete[]all;
                all = temp;
            }
        }
        size--;
    }

// TO DO !
/*
    MusicalSkill *getFirstN(int n) {
        MusicalSkill *temp = new MusicalSkill[n];
        MusicalSkill *best = all[0];

        for(int i = 1; i < size; i++) {
            if(all[i].getSkill() > best.getSkill();
                temp[j] = all[i];
        }
    }
*/


    virtual void setName() = 0;

    virtual char*getMusicName() const = 0;

    virtual int getPr() const = 0;

    virtual int getS() const = 0;

    virtual MusicalSkill *getFirstNMusicSkill(int n) = 0;

    virtual char*getType() const = 0;

};


class RockMusician : public Musician {
public:
    RockMusician(char*mn = "Pepi", int pr = 3, int s = 45) : Musician(mn, pr, s) { }

    ~RockMusician() { }

    RockMusician(RockMusician &other) : Musician(other) { }

    RockMusician &operator=(const RockMusician &other) {
        if(this != &other) {
            Musician::operator=(other);
        }
        return *this;
    }


    virtual int getPr() const {
        int totalSkill = 0;
        int s = getSize();

        for(int i = 0; i < s; i++) {
            totalSkill += all[i].getSkill();
        }

        return getPretty() * getPretty() + totalSkill - (getSins() * 3 * 3.14);
    }


    virtual int getS() const {
        return getSins();
    }

    virtual char*getType() const {
        return "rock";
    }

};

class Chalga : public Musician {
private:
    bool rase;

public:
    Chalga(char*mn = "Goshko",
           int pr = 2,
           int s = 34,
           bool r = true) : Musician(mn, pr, s) {
        this -> rase = r;
    }

    Chalga(const Chalga &other) : Musician(other) {
        this -> rase = other.rase;
    }

    Chalga &operator=(const Chalga &other) {
        if(this != &other) {
            Musician::operator=(other);
            this -> rase = other.rase;
        }
        return *this;
    }

//without destr.


    virtual int getPr() const {
        MusicalSkill best = all[0];

        for(int i = 0; i < size; i++ ) {
            if(all[i].getSkill() >= best.getSkill()) {
                    best = all[i];
            }
        }

    //ne mi se tursi po-lqsniq nachin
        return getPretty() *
               getPretty() *
               getPretty() *
               getPretty() *
               getPretty() + getSins() + (this -> rase * best.getSkill());
    }

    virtual int getS() const {
        return getSins();
    }

    virtual char*getType() const {
        return "rock_tack";
    }

};


class Band {
private:
    char*bandName;

protected:
    Musician*total;
    int bandSize;
    int bandMaxSize;

public:
    Band(char*n = "AC/DC") {
        this -> bandName = new char[strlen(n) + 1];
        assert(this -> bandName);
        strcpy(this -> bandName, n);

        this -> total = NULL;

        this -> bandSize = 0;

        this -> bandMaxSize = 0;
    }

    ~Band() {
        delete[]this -> bandName;
    }

//TO DO !
    Band(const Band &other) {
        delete[]this -> bandName;
        this -> bandName = new char[strlen(other.bandName) + 1];
        assert(this -> bandName);
        strcpy(this -> bandName, other.bandName);

    }


    virtual void addMusician(Musician &some) = 0;

    virtual void rmvMusician(char*n) = 0;

};

class RockBand : public Band { //virtual?
public:
//TO DO !
/*
    virtual void addMusician(Musician &some) {
        if(strcmp(some.getType(), "rock") {

        }
    }

//TO DO !
    virtual void rmvMusician(char*n) {
        int index = -1;

        for(int i = 0; i < bandSize; i++) {
            if(strcmp(total[i].getName(), n) == 0) {
                index = i;

            }
        }
    }
*/
};

int main()
{


    return 0;
}
