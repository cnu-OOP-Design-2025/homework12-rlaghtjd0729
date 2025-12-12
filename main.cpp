#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept> // std::invalid_argument 사용
#include "character.h"
#include "logger.h" // Logger 사용을 위해 포함

using namespace std;

// 친구 코드 로직: try/catch 추가
void equip_test1(shared_ptr<Character> c1) {
    try{
        c1 = make_shared<Armor>(c1);
        c1 = make_shared<Boots>(c1);
        c1 = make_shared<Sword>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    } catch(const std::invalid_argument& error_obj){ // 변수명을 error_obj로 변경, const & 사용
        Logger::getInstance()->log("[Fail to Equip] ");
        cout << "Invalid equip: " << error_obj.what() << endl;
    }
}

// 친구 코드 로직: try/catch 추가
void equip_test2(shared_ptr<Character> c1) {
    try{
        c1 = make_shared<Armor>(c1);
        c1 = make_shared<Bow>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    }catch(const std::invalid_argument& error_obj){ // 변수명을 error_obj로 변경, const & 사용
        Logger::getInstance()->log("[Fail to Equip] ");
        cout << "Invalid equip: " << error_obj.what() << endl;
    }
}

// 친구 코드 로직: try/catch 추가
void equip_test3(shared_ptr<Character> c1) {
    try{
        c1 = make_shared<Boots>(c1);
        c1 = make_shared<Staff>(c1);
        cout << c1->getDescription()
            << " | Attack: " << c1->getAttack()
            << " | Speed: " << c1->getSpeed()
            << " | Defense: " << c1->getDefense() << endl;
    } catch(const std::invalid_argument& error_obj){ // 변수명을 error_obj로 변경, const & 사용
        Logger::getInstance()->log("[Fail to Equip] ");
        cout << "Invalid equip: " << error_obj.what() << endl;
    }
}

void doTest() {
    // Logger 인스턴스를 미리 호출하여 [Init] 로그를 확실히 기록
    Logger::getInstance(); 
    
    vector<shared_ptr<Character>> players;
    players.push_back(make_shared<Knight>());
    players.push_back(make_shared<Wizard>());
    players.push_back(make_shared<Archer>());

    for(auto player: players){
        cout << "-------------------------------------------------------------" << endl;
        equip_test1(player);
        equip_test2(player);
        equip_test3(player);
    }
    cout << "-------------------------------------------------------------" << endl;

}

struct Student{
    string name;
    Student(string name): name(name) {};
    Student() = delete;
    ~Student() { cout << "Delete Student " << name << endl; }
};



int main(int argc, const char *argv[]) {
    doTest();
    return 0;
}