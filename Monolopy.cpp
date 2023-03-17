#include "Monolopy.h"
#include <algorithm>

using namespace ::std;

const int Monopoly::PLAYER_SAVINGS = 6000;
const int Monopoly::NUMBER_OF_FIELDS = 7;
enum class RentFees {
  PRISON_RENT_FEES = 1000,
  BANK_RENT_FEES = 700,
  OTHERS_RENT_FEES = 250
};

enum class SellFees {
  AUTO_SELL_FEES = 500,
  FOOD_SELL_FEES = 250,
  TRAVEL_SELL_FEES = 700,
  CLOTHER_SELL_FEES = 100
};

Monopoly::Monopoly(std::string names[], int countPlayers)
    : NUMBER_OF_PLAYERS(countPlayers) {
  Players.reserve(NUMBER_OF_PLAYERS);
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    Players.emplace_back(new Player(names[i], PLAYER_SAVINGS));
  }
  Fields.reserve(NUMBER_OF_FIELDS);
  Fields.emplace_back(new Field("Ford", Type::AUTO));
  Fields.emplace_back(new Field("MCDonald", Type::FOOD));
  Fields.emplace_back(new Field("Lamoda", Type::CLOTHER));
  Fields.emplace_back(new Field("Air Baltic", Type::TRAVEL));
  Fields.emplace_back(new Field("Nordavia", Type::TRAVEL));
  Fields.emplace_back(new Field("Prison", Type::PRISON));
  Fields.emplace_back(new Field("TESLA", Type::AUTO));
}

const std::vector<Player *> &Monopoly::GetPlayersList() const {
  return Players;
}

const std::vector<Field *> &Monopoly::GetFieldsList() const { return Fields; }

Player *Monopoly::GetPlayerInfo(int m) const {
  if (m >= NUMBER_OF_PLAYERS || m < 0) {
    throw "Invalid index !!!";
  }

  return Players[m];
}

Field *Monopoly::GetFieldByName(const std::string &l) const {
  auto it = std::find_if(Fields.begin(), Fields.end(),
                         [&](auto &field) { return field->getName() == l; });
  if (it == Fields.end()) {
    throw "Invalid field name !!!";
  }

  return *it;
}

bool Monopoly::Buy(int playerIndex, Field *f) {
  auto p = GetPlayerInfo(playerIndex);
  if (f->getOwner() == p) {
    return false;
  }
  switch (f->getType()) {
  case Type::AUTO:
    p->updateSavings(-static_cast<int>(SellFees::AUTO_SELL_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(static_cast<int>(SellFees::AUTO_SELL_FEES));
    }
    f->updateOwner(p);
    break;
  case Type::FOOD:
    p->updateSavings(-static_cast<int>(SellFees::FOOD_SELL_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(static_cast<int>(SellFees::FOOD_SELL_FEES));
    }
    f->updateOwner(p);
    break;
  case Type::TRAVEL:
    p->updateSavings(-static_cast<int>(SellFees::TRAVEL_SELL_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(
          static_cast<int>(SellFees::TRAVEL_SELL_FEES));
    }
    f->updateOwner(p);
    break;
  case Type::CLOTHER:
    p->updateSavings(-static_cast<int>(SellFees::CLOTHER_SELL_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(
          static_cast<int>(SellFees::CLOTHER_SELL_FEES));
    }
    f->updateOwner(p);
    break;
  default:
    return false;
  };
  return true;
}

bool Monopoly::Renta(int playerIndex, Field *f) {
  auto p = GetPlayerInfo(playerIndex);
  if (f->getOwner() == p) {
    return false;
  }
  switch (f->getType()) {
  case Type::AUTO:
  case Type::FOOD:
  case Type::TRAVEL:
  case Type::CLOTHER:
    p->updateSavings(-static_cast<int>(RentFees::OTHERS_RENT_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(
          static_cast<int>(RentFees::OTHERS_RENT_FEES));
    }
    break;
  case Type::PRISON:
    p->updateSavings(-static_cast<int>(RentFees::PRISON_RENT_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(
          static_cast<int>(RentFees::PRISON_RENT_FEES));
    }
    break;
  case Type::BANK:
    p->updateSavings(-static_cast<int>(RentFees::BANK_RENT_FEES));
    if (f->getOwner() != nullptr) {
      f->getOwner()->updateSavings(static_cast<int>(RentFees::BANK_RENT_FEES));
    }
    break;
  default:
    return false;
  }
  return true;
}

Monopoly::~Monopoly() {
  for (auto &player : Players) {
    delete player;
  }

  for (auto &field : Fields) {
    delete field;
  }
}