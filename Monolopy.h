#pragma once

#include <string>
#include <tuple>
#include <vector>

enum class Type { AUTO, FOOD, TRAVEL, CLOTHER, PRISON, BANK };

class Player;

class Field {
private:
  std::string name;
  Type type;
  Player *owner;

public:
  Field(const std::string &name, Type type, Player *owner = nullptr)
      : name(name), type(type), owner(owner) {}
  const std::string &getName() const { return name; }
  Type getType() const { return type; }
  Player *getOwner() const { return owner; }
  void updateOwner(Player *newOwner) { owner = newOwner; }
  bool operator==(const Field &field) const {
    return name == field.name && type == field.type && owner == field.owner;
  }
};

class Player {
private:
  std::string name;
  int savings;

public:
  Player(std::string name, int val) : name(name), savings(val) {}
  const std::string &getName() const { return name; }
  int getSavings() const { return savings; }
  void updateSavings(int amount) { savings += amount; }
  bool operator==(const Player &player) const {
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
  const std::vector<Player *> &GetPlayersList() const;
  const std::vector<Field *> &GetFieldsList() const;
  Player *GetPlayerInfo(int) const;
  Field *GetFieldByName(const std::string &) const;
  bool Buy(int playerIndex, Field *);
  bool Renta(int playerIndex, Field *);
};
