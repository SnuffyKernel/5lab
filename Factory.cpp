#include <iostream>
#include <string>

class Character {
public:
    virtual void displayInfo() const = 0;
};

class Mage : public Character {
protected:
    std::string abilityMage;
    std::string mageName;
    int level;

public:
    Mage(std::string ability, std::string name, int lvl) : abilityMage(ability), mageName(name), level(lvl){}

    void displayInfo() const override {
        std::cout << abilityMage << " mage" << std::endl;
        std::cout << mageName <<" mage" << std::endl;
        std::cout << "Level: " << level << std::endl;
    }
};

class Warrior : public Character {
protected:
    int strength;
    int dexterity;

public:
    Warrior(int str, int dex) : strength(str), dexterity(dex) {}

    void displayInfo() const override {
        std::cout << "Warrior character" << std::endl;
        std::cout << "Strength: " << strength << std::endl;
        std::cout << "Dexterity: " << dexterity << std::endl;
    }
};

class CharacterFactory {
public:
    virtual Mage* createMage(std::string mageName, int level) const = 0;
    virtual Warrior* createWarrior(int strength, int dexterity) const = 0;
};

class EarthCharFactory : public CharacterFactory {
protected:
    std::string ability = "Earth";
public:
    Mage* createMage(std::string mageName, int level) const override {
        return new Mage(ability, mageName, level);
    }

    Warrior* createWarrior(int strength, int dexterity) const override {
        return new Warrior(strength, dexterity);
    }
};

class WaterCharFactory : public CharacterFactory {
protected:
    std::string ability = "Water";
public:
    Mage* createMage(std::string mageName, int level) const override {
        return new Mage(ability, mageName, level);
    }

    Warrior* createWarrior(int strength, int dexterity) const override {
        return new Warrior(strength, dexterity);
    }
};

int main() {
    CharacterFactory* earthFactory = new EarthCharFactory();
    Mage* earthMage = earthFactory->createMage("BOB", 3);
    Warrior* earthWarrior = earthFactory->createWarrior(12, 3);

    CharacterFactory* waterFactory = new WaterCharFactory();
    Mage* waterMage = waterFactory->createMage("Oleg", 56);
    Warrior* waterWarrior = waterFactory->createWarrior(8, 10);

    earthMage->displayInfo();
    earthWarrior->displayInfo();

    std::cout << std::endl;

    waterMage->displayInfo();
    waterWarrior->displayInfo();

    return 0;
}