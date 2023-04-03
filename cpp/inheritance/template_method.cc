// Implement Template Method Pattern using Non-Virtual Interface (NVI)

#include <iostream>

class GameCharacter {
public:
    // Not redefined in derived classes
    int healthValue() const {
        // do things
        int ret = doHealthValue();
        // do things
        std::cout << "GameCharacter::healthValue() is " << ret << std::endl;
        return ret;
    }
private:
    // Redefined in derived classes
    virtual int doHealthValue() const = 0;
};

class PersonCharacter : public GameCharacter {
private:
    virtual int doHealthValue() const {
        std::cout << "PersonCharacter::doHealthValue()" << std::endl;
        return 50;
    }
};

class MonsterCharacter : public GameCharacter {
private:
    virtual int doHealthValue() const {
        std::cout << "MonsterCharacter::doHealthValue()" << std::endl;
        return 100;
    }
};

int main() {
    GameCharacter* p1 = new PersonCharacter();
    GameCharacter* p2 = new MonsterCharacter();
    p1->healthValue();
    p2->healthValue();
    return 0;
}