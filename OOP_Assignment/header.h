#include <string>
#include <vector>

using namespace std;

class Unit;

template< class T>
using mode = bool(*)(T, T);


bool less_than(const float val1,const float val2) {
    return val1 < val2;
}
bool greater_than(const float val1, const float val2) {
    return val1 > val2;
}


class Unit {
protected:
    string _name;
    float _hp;
    float _max_hp;
    float _damage;
    float _speed;
    bool _alive;
public:
    Unit(string name = "character", float max_hp = 100, float hp = 100, float damage = 10, float speed = 50) {
        _name = name;
        _hp = hp;
        _max_hp = max_hp;
        _damage = damage;
        _speed = speed;
        _alive = true;
    }
    ~Unit() {}


    void take_damage(const float damage) {
        _damage = std::max(0.f, _hp - damage);
    }
    void heal(const float hp) {
        _hp = std::min(_hp + hp, _max_hp);
    }
    bool is_alive() const {
        return _alive;
    }
    float hp() const {
        return _hp;
    }
    virtual void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) = 0;
protected:

    Unit* find_hp_with_cond(vector<Unit*>& units, mode<float> comparision) {
    int idx = 0;
    
    for (int i = 1; i < units.size(); ++i) {
        if (comparision(units[idx]->hp(), units[i]->hp())) {
            idx = i;
        }
    }

    return units[idx];
}
};


class Hero : public Unit {
private:
public:
    Hero() : Unit() {
        _name = "Hero";
    }
    ~Hero() {}


    virtual void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) = 0;
};
class Monster : public Unit {
private:
public:
    Monster() : Unit() {
        _name = "Monster";
    }
    ~Monster() {}
    virtual void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) = 0;
};



class Warrior : public Hero {
public:
    Warrior() : Hero() {
        _name = "Warrior";
        _max_hp *= 5;
        _hp *= 2.5;
    }
    ~Warrior() {}
    // inflict damage
    // Actack
    void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) override{

    }
};
class Mage : public Hero {
public:
    Mage() : Hero() {
        _name = "Mage";
        _max_hp *= 0.8;
        _hp *= 0.8;
        _damage *= 2;
    }
    ~Mage() {}
    // actack
    // ignore armor if there is
    void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) override {

    }
};
class Healer : public Hero {
public:
    Healer() : Hero() {
        _name = "Healer";
    }
    ~Healer() {}
    // Heal an ally with lowest health
    void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) override {
        Unit* ally = find_hp_with_cond(allies, greater_than);
        ally->heal(_damage);
    }
};


class Goblin : public Monster{
public:
    Goblin() : Monster() {
        _name = "Goblin";
        _speed *= 1.5;
        _damage /= 2;
    }
    ~Goblin() {}

    // actack a hero with the lowest health
    void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) override {
        Unit* enemy = find_hp_with_cond(enemies, greater_than);
        enemy->take_damage(_damage);
    }
};
class Boss : public Monster {
private:
    bool act_cnt[3];        // actack turn counter
public:
    Boss() : Monster() {
        _name = "Boss";
        _max_hp *= 10;
        _hp *= 8;
        act_cnt[0] = act_cnt[1] = act_cnt[2] = false;
    }
    ~Boss() {}

    void do_turn(vector<Unit*>& enemies, vector<Unit*>& allies) override {
        // AOE actack
        if (act_cnt[0] && act_cnt[1] && act_cnt[2]) {
            // reset the AOE actack counter
            act_cnt[0] = act_cnt[1] = act_cnt[2] = false;

            for (Unit* & u: enemies) {
                u->take_damage(_damage);
            }
        }
        // normal actack
        else {
            Unit* enemy = find_hp_with_cond(enemies, greater_than);
            //
            for (int i = 0; i < 3; ++i) {
                if (!act_cnt[i]) {
                    act_cnt[i] = true;
                    break;
                }
            }
        }
    }
};



class BattleEngine {
private:
    vector<Unit*> _all_units;
    vector<Unit*> _dead_units;
public:
    BattleEngine() {}
    ~BattleEngine() {
        for (int i = 0; i < _all_units.size(); ++i) {
            delete _all_units[i];
        }
        for (int i = 0; i < _dead_units.size(); ++i) {
            delete _dead_units[i];
        }
    }

    void add_unit(Unit*&& unit) {
        _all_units.push_back(std::move(unit));
    }
    
    void start_battle() {
        int round = 1;
        while (!_all_units.empty()) {
            // sort base on speed
            // iterate through each units
            // check if alive

            ++round;
        }
    }
};