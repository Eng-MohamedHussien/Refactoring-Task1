#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <Monolopy.h>

TEST_CASE("Test Player class") {
  Player testPlayer1{"CR7", 6000};
  Player testPlayer2{"CR17", 6000};
  SUBCASE("Test getName function") { CHECK(testPlayer1.getName() == "CR7"); }
  SUBCASE("Test getSavings function") {
    CHECK(testPlayer1.getSavings() == 6000);
  }
  SUBCASE("Test updateSavings function") {
    testPlayer1.updateSavings(10000);
    CHECK(testPlayer1.getSavings() == 16000);
  }
  SUBCASE("Test == operator") { CHECK(!(testPlayer1 == testPlayer2)); }
}

TEST_CASE("Test Field class") {
  Player testPlayer1{"CR7", 6000};
  Player testPlayer2{"Messi", 5000};
  Field testField1{"Audi", Type::AUTO, &testPlayer1};
  Field testField2{"Nissan", Type::AUTO, &testPlayer2};

  SUBCASE("Test getName function") { CHECK(testField1.getName() == "Audi"); }
  SUBCASE("Test getType function") {
    CHECK(testField1.getType() == Type::AUTO);
  }
  SUBCASE("Test getOwner function") {
    CHECK(testField1.getOwner() == &testPlayer1);
  }
  SUBCASE("Test updateOwner function") {
    testField1.updateOwner(&testPlayer2);
    CHECK(testField1.getOwner() == &testPlayer2);
  }
  SUBCASE("Test operator ==") { CHECK(!(testField1 == testField2)); }
}

TEST_CASE("Test Monolopy class") {
  std::string names[] = {"Messi", "CR7", "Mbappe"};
  Monopoly m(names, 3);

  SUBCASE("Test GetFieldsList function") {
    auto fieldList = m.GetFieldsList();
    CHECK(fieldList[2]->getName() == "Lamoda");
    CHECK(fieldList[2]->getType() == Type::CLOTHER);
  }

  SUBCASE("Test GetPlayersList function") {
    auto playerList = m.GetPlayersList();
    CHECK(playerList[2]->getName() == "Mbappe");
    CHECK(playerList[2]->getSavings() == 6000);
  }

  SUBCASE("Test GetPlayerInfo function") {
    Player testPlayer("CR7", 6000);
    CHECK(*m.GetPlayerInfo(1) == testPlayer);
    CHECK_THROWS_WITH(m.GetPlayerInfo(-1), "Invalid index !!!");
    CHECK_THROWS_WITH(m.GetPlayerInfo(4), "Invalid index !!!");
  }

  SUBCASE("Test GetFieldByName function") {
    Field *f5 = m.GetFieldByName("Prison");
    CHECK(f5->getName() == "Prison");
    CHECK(f5->getType() == Type::PRISON);
  }

  SUBCASE("Test Buy function") {
    CHECK_FALSE(m.Buy(1, m.GetFieldByName("Prison")));
    auto teslaCar = m.GetFieldsList()[6];
    CHECK(m.Buy(2, teslaCar) == 1);
    CHECK(m.GetPlayerInfo(2)->getSavings() == 5500);
    CHECK(teslaCar->getOwner() == m.GetPlayerInfo(2));
  }

  SUBCASE("Test Renta function") {
    auto fordCar = m.GetFieldsList()[0];
    m.Buy(0, fordCar);
    CHECK(m.Renta(1, fordCar) == 1);
    CHECK(m.GetPlayerInfo(0)->getSavings() == 5750);
    CHECK(m.GetPlayerInfo(1)->getSavings() == 5750);
    CHECK(fordCar->getOwner() == m.GetPlayerInfo(0));
    CHECK(m.Renta(0, fordCar) == 0);
  }
}
