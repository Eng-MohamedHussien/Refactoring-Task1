#pragma once

#include <string>
#include <tuple>
#include <vector>

enum Type { AUTO, FOOD, TRAVEL, CLOTHER, PRISON, BANK };

class Player;

class Field {
private:
  std::string name;
  Type type;
  Player *owner;

public:
  Field(std::string name, Type type, Player *owner)
      : name(name), type(type), owner(owner) {}
  std::string &getName() { return name; }
  void setName(const std::string &newName) { name = newName; }
  Type getType() { return type; }
  void setType(Type newType) { type = newType; }
  Player *getOwner() { return owner; }
  void updateOwner(Player *newOwner) { owner = newOwner; }
  bool operator==(Field &field) {
    return name == field.name && type == field.type && owner == field.owner;
  }
};

class Player {
private:
  std::string name;
  int savings;

public:
  Player(std::string name, int val) : name(name), savings(val) {}
  std::string &getName() { return name; }
  void setName(const std::string &newName) { name = newName; }
  int getSavings() { return savings; }
  void updateSavings(int newVal) { savings = newVal; }
  bool operator==(Player &player) {
    return name == player.name && savings == player.savings;
  }
};

class Monopoly {
private:
  std::vector<Field *> Fields;
  std::vector<Player *> Players;
  const unsigned int NUMBER_OF_PLAYERS;
  static const int PLAYER_SAVINGS;
  static const int NUMBER_OF_FIELDS;

public:
  Monopoly(std::string names[], int);
  ~Monopoly();
  const std::vector<Player *> &GetPlayersList();
  const std::vector<Field *> &GetFieldsList();
  Player *GetPlayerInfo(int);
  Field *GetFieldByName(const std::string &);
  bool Buy(int playerIndex, Field *);
  bool Renta(int playerIndex, Field *);
};
