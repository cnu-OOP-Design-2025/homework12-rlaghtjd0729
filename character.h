#pragma once
#include <iostream>
#include <string>
#include <stdexcept> // invalid_argument 사용
#include <memory>    // shared_ptr 사용
#include "logger.h"
using namespace std;


enum class CharacterType {
    Knight,
    Wizard,
    Archer,
    Unknown
};


class Character {
protected:
    string description;
    CharacterType type = CharacterType::Unknown; // 원본 변수명 유지
public:
    virtual string getDescription() const { return description; }
    virtual int getAttack() const = 0;
    virtual int getSpeed() const = 0;
    virtual int getDefense() const = 0;
    virtual CharacterType getType() const { return type; } // 원본 변수명 유지
    virtual ~Character() {
        if (this->type != CharacterType::Unknown)
            cout << "Delete Character: " << description << endl;
    }
};

// 기본 캐릭터
class Knight : public Character {
public:
    Knight() { 
        description = "Knight"; 
        type = CharacterType::Knight;
        // 친구 코드 로직: 로그 추가
        Logger::getInstance()->log("[Create] "+description);
    }
    int getAttack() const override { return 15; }
    int getSpeed() const override { return 8; }
    int getDefense() const override { return 20; }
};

class Wizard : public Character {
public:
    Wizard() { 
        description = "Wizard"; 
        type = CharacterType::Wizard; 
        // 친구 코드 로직: 로그 추가
        Logger::getInstance()->log("[Create] "+description);
    }
    int getAttack() const override { return 20; }
    int getSpeed() const override { return 10; }
    int getDefense() const override { return 10; }
};

class Archer : public Character {
public:
    Archer() { 
        description = "Archer"; 
        type = CharacterType::Archer; 
        // 친구 코드 로직: 로그 추가
        Logger::getInstance()->log("[Create] "+description);
    }
    int getAttack() const override { return 18; }
    int getSpeed() const override { return 15; }
    int getDefense() const override { return 8; }
};

// Decorator 기본 구조
class EquipDeco : public Character {
protected:
    shared_ptr<Character> character; // 원본 변수명 유지
public:
    // 친구 코드 로직: 생성자에서 로그 기록
    EquipDeco(shared_ptr<Character> c, string item) : character(c) {
        // 친구 코드의 로그 메시지 생성 로직을 유지하되, 내부적으로 .get() 대신 ->를 사용하도록 변경
        Logger::getInstance()->log("[Trying to Equip] " + c->getDescription() +" + " + item);
    }
    virtual ~EquipDeco() { }
    // CharacterType getType()은 EquipDeco에서 구현하지 않았지만, 필요 시 base class에서 상속됨.
};

// 장비 클래스
class Armor : public EquipDeco {
public:
    Armor(shared_ptr<Character> c) : EquipDeco(c, "Armor") {} 
    string getDescription() const override { return character->getDescription() + " + Armor"; }
    int getAttack() const override { return character->getAttack(); }
    int getSpeed() const override { return character->getSpeed() - 2; }
    int getDefense() const override { return character->getDefense() + 10; }
    CharacterType getType() const override {return character->getType();}
};

class Boots : public EquipDeco {
public:
    Boots(shared_ptr<Character> c) : EquipDeco(c, "Boots") {} 
    string getDescription() const override { return character->getDescription() + " + Boots"; }
    int getAttack() const override { return character->getAttack(); }
    int getSpeed() const override { return character->getSpeed() + 5; }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Staff : public EquipDeco {
public:
    // 친구 코드 로직: 예외 처리 추가
    Staff(shared_ptr<Character> c) : EquipDeco(c, "Staff") {
        if(c->getType() != CharacterType::Wizard){ // .get() 대신 -> 사용
            throw std::invalid_argument("Staff requires Wizard");
        }
    }
    string getDescription() const override { return character->getDescription() + " + Staff"; }
    int getAttack() const override { return character->getAttack() + 8; }
    int getSpeed() const override { return character->getSpeed(); }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Sword : public EquipDeco {
public:
    Sword(shared_ptr<Character> c) : EquipDeco(c, "Sword") {} 
    string getDescription() const override { return character->getDescription() + " + Sword"; }
    int getAttack() const override { return character->getAttack() + 10; }
    int getSpeed() const override { return character->getSpeed(); }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};

class Bow : public EquipDeco {
public:
    // 친구 코드 로직: 예외 처리 추가
    Bow(shared_ptr<Character> c) : EquipDeco(c, "Bow") {
        if(c->getType() == CharacterType::Wizard){ // .get() 대신 -> 사용
            throw std::invalid_argument("Bow requires Archer or Knight");
        }
    }
    string getDescription() const override { return character->getDescription() + " + Bow"; }
    int getAttack() const override { return character->getAttack() + 7; }
    int getSpeed() const override { return character->getSpeed() + 2; }
    int getDefense() const override { return character->getDefense(); }
    CharacterType getType() const override {return character->getType();}
};