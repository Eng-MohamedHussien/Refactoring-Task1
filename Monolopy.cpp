#include "Monolopy.h"
#include <algorithm>

using namespace ::std;

const int Monopoly::PLAYER_SAVINGS = 6000;
const int Monopoly::NUMBER_OF_FIELDS = 7;
enum RentFees {
  PRISON_RENT_FEES = 1000,
  BANK_RENT_FEES = 700,
  OTHERS_RENT_FEES = 250
};

enum SellFees {
  AUTO_SELL_FEES = 500,
  FOOD_SELL_FEES = 250,
  TRAVEL_SELL_FEES = 700,
  CLOTHER_SELL_FEES = 100
};

Monopoly::Monopoly(std::string names[], int countPlayers)
    : NUMBER_OF_PLAYERS(countPlayers) {
  Players.reserve(countPlayers);
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++) {
    Players.emplace_back(new Player(names[i], PLAYER_SAVINGS));
  }
  Fields.reserve(NUMBER_OF_FIELDS);
  Fields.emplace_back(new Field("Ford", AUTO, Players[0]));
  Fields.emplace_back(new Field("MCDonald", FOOD, Players[0]));
  Fields.emplace_back(new Field("Lamoda", CLOTHER, Players[0]));
  Fields.emplace_back(new Field("Air Baltic", TRAVEL, Players[0]));
  Fields.emplace_back(new Field("Nordavia", TRAVEL, Players[0]));
  Fields.emplace_back(new Field("Prison", PRISON, Players[0]));
  Fields.emplace_back(new Field("TESLA", AUTO, Players[0]));
}

const std::vector<Player *> &Monopoly::GetPlayersList() { return Players; }

const std::vector<Field *> &Monopoly::GetFieldsList() { return Fields; }

Player *Monopoly::GetPlayerInfo(int m) {
  if (m >= NUMBER_OF_PLAYERS || m < 0)
    throw "Invalid index !!!";
  else
    return Players[m];
}

Field *Monopoly::GetFieldByName(const std::string &l) {
  auto it = std::find_if(Fields.begin(), Fields.end(),
                         [&](auto &field) { return field->getName() == l; });
  if (it != Fields.end()) {
    return *it;
  } else
    throw "Invalid field name !!!";
}

bool Monopoly::Buy(int playerIndex, Field *f) {
  auto p = GetPlayerInfo(playerIndex);
  switch (f->getType()) {
  case AUTO:
    if (f->getOwner() == p)
      return false;
    p->updateSavings(p->getSavings() - AUTO_SELL_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() + AUTO_SELL_FEES);
    f->updateOwner(p);
    break;
  case FOOD:
    if (f->getOwner() == p)
      return false;
    p->updateSavings(p->getSavings() - FOOD_SELL_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() + FOOD_SELL_FEES);
    f->updateOwner(p);
    break;
  case TRAVEL:
    if (f->getOwner() == p)
      return false;
    p->updateSavings(p->getSavings() - TRAVEL_SELL_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() +
                                 TRAVEL_SELL_FEES);
    f->updateOwner(p);
    break;
  case CLOTHER:
    if (f->getOwner() == p)
      return false;
    p->updateSavings(p->getSavings() - CLOTHER_SELL_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() +
                                 CLOTHER_SELL_FEES);
    f->updateOwner(p);
    break;
  default:
    return false;
  };
  return true;
}

bool Monopoly::Renta(int playerIndex, Field *f) {
  auto p = GetPlayerInfo(playerIndex);
  switch (f->getType()) {
  case AUTO:
  case FOOD:
  case TRAVEL:
  case CLOTHER:
    if (f->getOwner() == p)
      return false;
    p->updateSavings(p->getSavings() - OTHERS_RENT_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() +
                                 OTHERS_RENT_FEES);
    break;
  case PRISON:
    p->updateSavings(p->getSavings() - PRISON_RENT_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() +
                                 PRISON_RENT_FEES);
    break;
  case BANK:
    p->updateSavings(p->getSavings() - BANK_RENT_FEES);
    f->getOwner()->updateSavings(f->getOwner()->getSavings() + BANK_RENT_FEES);
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