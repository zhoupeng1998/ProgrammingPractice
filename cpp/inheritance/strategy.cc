// Using function pointers to implement a strategy pattern

#include <iostream>
#include <functional>

class GameCharacter {
public:
    typedef int (*HealthCalcFunc)(const GameCharacter&);
    //typedef std::function<int(const GameCharacter&)> HealthCalcFunc;
    
    explicit GameCharacter(HealthCalcFunc hcf) : healthCalcFunc(hcf) {}

    int healthValue() const {
        return healthCalcFunc(*this);
    }
private:
    HealthCalcFunc healthCalcFunc;
};

class EvilBadGuy : public GameCharacter {
public:
    explicit EvilBadGuy(HealthCalcFunc hcf) : GameCharacter(hcf) {}
};

int loseHealthQuickly(const GameCharacter& gc) {
    std::cout << "loseHealthQuickly()" << std::endl;
    return 0;
}

int loseHealthSlowly(const GameCharacter& gc) {
    std::cout << "loseHealthSlowly()" << std::endl;
    return 0;
}

int main() {
    GameCharacter* gc1 = new EvilBadGuy(loseHealthQuickly);
    GameCharacter* gc2 = new EvilBadGuy(loseHealthSlowly);
    gc1->healthValue();
    gc2->healthValue();
    return 0;
}