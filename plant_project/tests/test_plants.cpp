#include <gtest/gtest.h>
#include "../src/plants.h"

TEST(TreeTest, Matches) {
    Tree t("Дуб", 150);
    EXPECT_TRUE(t.matches("название == 'Дуб'"));
    EXPECT_TRUE(t.matches("возраст > 100"));
    EXPECT_FALSE(t.matches("возраст < 100"));
}

TEST(ShrubTest, Matches) {
    Shrub s("Сирень", Month::JUN);
    EXPECT_TRUE(s.matches("месяц == ИЮНЬ"));
}

TEST(CactusTest, Matches) {
    Cactus c("Сагуаро", 2.5);
    EXPECT_TRUE(c.matches("длина > 2.0"));
    EXPECT_FALSE(c.matches("длина < 2.0"));
}

TEST(PlantContainerTest, AddRemove) {
    PlantContainer pc;
    pc.add(make_unique<Tree>("Дуб", 150));
    pc.add(make_unique<Shrub>("Сирень", Month::JUN));
    EXPECT_EQ(pc.size(), 2);
    pc.remove("название == 'Сирень'");
    EXPECT_EQ(pc.size(), 1);
}

TEST(ExceptionsTest, InvalidMonth) {
    EXPECT_THROW(stringToMonth("ФИКТИВНЫЙ"), std::invalid_argument);
}
