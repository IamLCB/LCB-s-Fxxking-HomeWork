#include <iostream>
using namespace std;

// 常量定义
const int CREATURE_MONSTER = 1;

// 抽象基类 Creature
class Creature {
protected:
    double hp;
    double baseDamage;

public:
    Creature() : hp(100), baseDamage(0) {}

    double getHp() const { return hp; }
    double getBaseDamage() const { return baseDamage; }

    virtual bool attack(Creature& creature) = 0;
    virtual int getCreatureType() const = 0;

    void getHurt(double value) {
        hp -= value;
        if (hp < 0) hp = 0;
    }

    bool isDead() const { return hp <= 0; }
};

// 抽象类 Monster
class Monster : public Creature {
public:
    bool attack(Creature& creature) override {
        if (creature.getCreatureType() == CREATURE_MONSTER) {
            return false; // Monster 不能攻击 Monster
        }

        creature.getHurt(baseDamage);
        return creature.isDead();
    }

    int getCreatureType() const override {
        return CREATURE_MONSTER;
    }
};

// 类 Zombie
class Zombie : public Monster {
public:
    Zombie() {
        baseDamage = 15;
    }
};

int main() {
    // 创建两个 Zombie 实例
    Zombie zombie1, zombie2;

    // 显示初始生命值
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    // Zombie 1 攻击 Zombie 2
    if (zombie1.attack(zombie2)) {
        cout << "Zombie 2 was defeated by Zombie 1." << endl;
    }

    // 显示攻击后的生命值
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    // Zombie 2 反击 Zombie 1
    if (zombie2.attack(zombie1)) {
        cout << "Zombie 1 was defeated by Zombie 2." << endl;
    }

    // 再次显示生命值
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    return 0;
}