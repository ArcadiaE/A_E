#include<iostream>
#include<vector>
#include <algorithm>
#include <random>
#include <chrono>

#include"copyright.h"

using namespace std;

enum CardType {
    ATTACK,
    DEFENSE,
    HEAL
};

enum WeaponType {
    COLD_WEAPON,
    HOT_WEAPON,
    FIRE_GUN,
    SPEAR,
    SWORD
};

class Card {
private:
    string name;
    int damage;
    CardType type;
    WeaponType weapon;
public:
    Card(string name, int damage, CardType type, WeaponType weapon)
        : name(name), damage(damage), type(type), weapon(weapon) {}
    string getName() { return name; }
    int getDamage() { return damage; }
    CardType getType() { return type; }
    WeaponType getWeapon() { return weapon; }
    // 其他相关函数
};

class Player {
private:
    string name;
    int hp; // 玩家血量
    vector<Card*> hand; // 手牌
    vector<Card*> deck; // 牌阵
    vector<Card*> deck_backup; // 备用牌阵
public:
    Player::Player("King");
    Player(string name, int hp)
        : name(name), hp(hp) {}
    string getName() { return name; }
    int getHp() { return hp; }
    void setHp(int new_hp) { hp = new_hp; }
    vector<Card*>& getHand() { return hand; }
    vector<Card*>& getDeck() { return deck; }
    vector<Card*>& getDeckBackup() { return deck_backup; }
    void drawCard(); // 摸牌
    void playCard(int card_idx, Player& target_player, int target_idx); // 出牌
    void discardCard(int card_idx); // 弃牌
    void moveCard(int from_idx, vector<Card*>& from_deck, vector<Card*>& to_deck); // 移动牌
    // 其他相关函数
};

class Game {
private:
    int current_round_; // 当前回合数
    std::vector<Card> deck_; // 牌堆
    std::vector<Player> players_; // 玩家列表

public:
    Game(int num_players); // 构造函数，初始化游戏
    void startGame(); // 开始游戏
    void endGame(); // 结束游戏
    void nextRound(); // 进入下一回合
    void drawCard(int player_id, int num_cards); // 摸牌
    void playCard(int player_id, int card_id, int target_id); // 出牌
    void attack(int attacker_id, int target_id); // 攻击
    void dealDamage(int player_id, int damage); // 扣除血量
    void handleEndRound(); // 回合结束时的处理
    bool isGameOver(); // 判断游戏是否结束
};

Game::Game(int num_players) {
    // 初始化牌堆和玩家
    // ...
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            // 不包括角色牌
            if (i == 1 || i == 2 || i == 7 || i == 8) {
                continue;
            }
            Card card(i, j);
            deck_.push_back(card);
        }
    }
    // 初始化玩家
    for (int i = 0; i < num_players; i++) {
        Player player ("King");
        players_.push_back(player);
    }
    // 随机抽牌
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < num_players; j++) {
            int random_index = rand() % deck_.size();
            Card card = deck_[random_index];
            players_[j].drawCard();
            deck_.erase(deck_.begin() + random_index);
        }
    }
}


void Game::startGame() {
    // 发牌，确定先手等操作
    // ...
}

void Game::endGame() {
    // 游戏结束的处理
    // ...
}

void Game::nextRound() {
    // 进入下一回合
    // ...
}

void Game::drawCard(int player_id, int num_cards) {
    // 玩家摸牌
    // ...
}

void Game::playCard(int player_id, int card_id, int target_id) {
    // 玩家出牌
    // ...
}

void Game::attack(int attacker_id, int target_id) {
    // 攻击
    // ...
}

void Game::dealDamage(int player_id, int damage) {
    // 扣除血量
    // ...
}

void Game::handleEndRound() {
    // 回合结束时的处理，如处理玩家备牌区的卡牌等
    // ...
}

bool Game::isGameOver() {
    // 判断游戏是否结束
    // ...
}



int main() {
copyright();
system("pause");

return 0;
}
