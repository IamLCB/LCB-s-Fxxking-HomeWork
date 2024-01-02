#include <iostream>
using namespace std;

// ��������
const int CREATURE_MONSTER = 1;

// ������� Creature
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

// ������ Monster
class Monster : public Creature {
public:
    bool attack(Creature& creature) override {
        if (creature.getCreatureType() == CREATURE_MONSTER) {
            return false; // Monster ���ܹ��� Monster
        }

        creature.getHurt(baseDamage);
        return creature.isDead();
    }

    int getCreatureType() const override {
        return CREATURE_MONSTER;
    }
};

// �� Zombie
class Zombie : public Monster {
public:
    Zombie() {
        baseDamage = 15;
    }
};

int main() {
    // �������� Zombie ʵ��
    Zombie zombie1, zombie2;

    // ��ʾ��ʼ����ֵ
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    // Zombie 1 ���� Zombie 2
    if (zombie1.attack(zombie2)) {
        cout << "Zombie 2 was defeated by Zombie 1." << endl;
    }

    // ��ʾ�����������ֵ
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    // Zombie 2 ���� Zombie 1
    if (zombie2.attack(zombie1)) {
        cout << "Zombie 1 was defeated by Zombie 2." << endl;
    }

    // �ٴ���ʾ����ֵ
    cout << "Zombie 1 HP: " << zombie1.getHp() << endl;
    cout << "Zombie 2 HP: " << zombie2.getHp() << endl;

    return 0;
}