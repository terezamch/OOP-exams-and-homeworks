#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

// Polymorphism
// Encapsulation
// Abstraction
// Inheritance

struct Musical_skill{
//The big 4???
//Да се реализира голяма четворка и други необходими за следващите задачи методи.
    char* name;
    int skill;
};

class Musician{
private:
    char* name;
    Musical_skill* skills;
    int current_skills;
    char* type;
protected:
    int positive;
    int negative;
public:
    Musician(){
        this->name = "Unknown";
    }
    Musician(char* name){
        setName(name);
    }
    void setName(char* name){
        this->name = name;
    }
    char* getName(){
        return this->name;
    }
    virtual int getPositive(){
        return this->positive;
    }
    int getNegative(){
        return this->negative;
    }
    Musical_skill* getSkills(){
        return this->skills;
    }
    int getCurrentSkills(){
        return this->current_skills;
    }
    int getSkill(char* instrument){
        Musical_skill* skills = getSkills();
        for(int i = 0; i < getCurrentSkills(); i++){
            if(skills[i].name == instrument){
                return skills[i].skill;
            }
        }
    }
    void addSkill(Musical_skill add){
        if(getCurrentSkills() < 5){
            this->skills[getCurrentSkills()-1] = add;
        }
    }
    void setType(char* type){
        this->type = type;
    }
    char* getType(){
        return this->type;
    }
    int getSumSkills(){
        int sum = 0;
        Musical_skill* skills = getSkills();
        for(int i = 0; i < getCurrentSkills(); i++){
            sum += skills[i].skill;
        }
        return sum;
    }
    Musical_skill* getBestSkills(int n){
        Musical_skill* result = new Musical_skill;
        if(n == 1){
            result[0] = getSkills()[0];
            return result;
        }
        if(n > 1){
            result = getSkills();
        Musical_skill* swap = new Musical_skill;
            for(int i = 0; i < getCurrentSkills(); i++){
                if(result[i].skill < result[i+1].skill){
                    swap[0] = result[i+1];
                    result[i+1] = result[i];
                    result[i] = swap[0];
                }
            }
            return result;
        }
    }
    ~Musician(){
        delete name;
    }
};

class Rock : public Musician{
public:

//Да се реализира голяма четворка и други необходими за следващите задачи методи.??
    Rock(){
        setType("rock");
    }
    int getPositive(){ //красота( член данна)^2 + сумата от всички музикални умения - пороци * 3 ПИ.
        return (this->positive * 2 + getSumSkills() - this->negative * 3);
    }
//вземане на пороци ?? 
//тип на музиканта - Да връща стринг 'rock' ?? 

};

class PopFolk : public Musician{
private:
    bool isRace;
public:
    PopFolk() : Musician(){
        setType("rock_tack");
    }
    int getPositive(){ //  красота( член данна)^5 + пороци + расова принадлежност * cos(от най-доброто му музикално умение);
        return (this->positive * 5 + this->negative);
    }
// .....
};

class Band{
private:
    char* name;
protected:
    Musician* members;
    int members_count;
    double avrgPositive;
public:
    Band(){
        setName("Unknown");
    }
    Band(char* name){
        setName(name);
    }
    void setName(char* name){
        this->name = name;
    }
    char* getName(){
        return this->name;
    }
    int getMembersCount(){
        return this->members_count;
    }
    Musician* getMembers(){
        return this->members;
    }
    virtual void addMusician(Musician add){
        this->members[getMembersCount()] = add;
        this->members_count++;
    }
    double getAvrgPositive(){
        double result = 0;
        for(int i = 0; i < getMembersCount(); i++){
            result += getMembers()[i].getPositive();
        }
        result = result / getMembersCount();
        return result;
    }
    void removeMusician(char* name){
        Musician* swap = new Musician;
        bool found = false;
        for(int i = 0; i < getMembersCount(); i++){
            if(found == true){
                swap[0] = members[i+1];
                members[i+1] = members[i];
                members[i] = swap[0];
            }
            if(this->members[i].getName() == name){
                found = true;
            }
        }
        this->members_count--;
        swap[0] = members[getMembersCount()-1];
        delete swap;
    }
};

class RockBand : public Band{ //virtual?
private:
public:
    void addMusician(Musician add){
        if(add.getType() == "rock" || add.getBestSkills(1)[0].skill >= 100 && this->members_count < 10){
            this->members[getMembersCount()] = add;
            this->members_count++;
        }
    }
    int getFullGrade(){
        int result;
        for(int i = 0; i < getMembersCount(); i++){
            result += getMembers()[i].getNegative();
            result += getMembers()[i].getSumSkills();
        }
        return result;
    }
};

class PopFolkBand : public Band{ //virtual??
private:
public:
    void addMusician(Musician add, char* instrument){
        if(add.getType() == "rock_tack" || add.getSkill(instrument) < 10 && this->members_count < 10){
            this->members[getMembersCount()] = add;
            this->members_count++;
        }
    }
    int getFullGrade(){
        int result;
        for(int i = 0; i < getMembersCount(); i++){
            result += getMembers()[i].getPositive();
            result += getMembers()[i].getSumSkills();
        }
        return result;
    }

};

int main(){
    cout << "Main";
return 0;
}
