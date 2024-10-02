#include <array>
#include <vector>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <unordered_map>
#include <algorithm>
#include <tuple>

#include <gcheck/tests.h>
#include <gcheck/redirectors.h>
#include "../src/dragon.hpp"
#include "../src/fantasy_dragon.hpp"
#include "../src/magic_dragon.hpp"
#include "../src/dragon_cave.hpp"

std::string to_string(TreasureType t) {
    switch (t) {
    case Wisdom:
        return "Wisdom";
    case Potions:
        return "Potions";
    case Jewellery:
        return "Jewellery";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Treasure& t) {
    return "[" + to_string(t.type) + ", " + t.name + "]";
}
bool operator==(const Treasure& l, const Treasure& r) {
    return l.type == r.type && l.name == r.name;
}

std::string to_string(FoodType t) {
    switch (t) {
    case People:
        return "People";
    case PeopleFood:
        return "PeopleFood";
    case Herbs:
        return "Herbs";
    default:
        return "ErrorType";
    }
}
std::string to_string(const Food& f) {
    return "[" + to_string(f.type) + ", " + f.name + "]";
}
bool operator==(const Food& l, const Food& r) {
    return l.type == r.type && l.name == r.name;
}

std::string to_construct(const Treasure& d) {
    return "(Treasure){" + to_string(d.type) + "," + gcheck::toConstruct(d.name) + "}";
}
std::string to_construct(const Food& d) {
    return "(Food){" + to_string(d.type) + "," + gcheck::toConstruct(d.name) + "}";
}

std::vector<Treasure> CreateRandomTreasures(size_t count) {
    std::vector<Treasure> treasures;

    // Jewellery
    gcheck::Random j_names({"Ruby", "Gold bar", "Agate", "Amber", "Silver coins", "Jade stone", "Bag of pearls", "Topaz", "Sapphire dust"});
    // Wisdom
    gcheck::Random w_names({"Scroll of infinite wisdom", "Sun Tzu's Art of War", "Biographia literaria", "MAOL", "Gabriel's Wing", "Critique of pure reason", "The C++ standard", "The Symposium", "Thus Spoke Zarathustra"});
    // Potions
    gcheck::Random p_names({"Cough syrup", "Liquid luck", "Stoneskin potion", "Blemish blitzer", "Elixir of euphoria", "Garroting gas", "Essence of insanity", "Gin tonic", "Truth serum"});

    gcheck::Random rnd_type(std::vector<TreasureType>({Jewellery, Wisdom, Potions}));
    std::unordered_map<TreasureType, gcheck::Random<const char*>*> names({std::pair(Jewellery, &j_names), std::pair(Wisdom, &w_names), std::pair(Potions, &p_names)});

    for(size_t i = 0; i < count; i++) {
        TreasureType type = rnd_type.Next();
        treasures.push_back({type, std::string(names[type]->Next())});
    }

    return treasures;
}

std::vector<Food> CreateRandomFood(size_t count) {
    std::vector<Food> food;

    // PeopleFood
    gcheck::Random pf_names({"Tenderloin steak", "Carnivore pizza", "Beef chuck", "Pork ribs", "Cornered beef", "Flank steak", "Pork rack", "Half of a pork's ass", "Horse (salami)"});
    // People
    gcheck::Random p_names({"Raimo", "Petteri", "Joonas", "Konsta", "Jack Sparrow", "John Smith", "Random crusader", "Barack Obama", "The Pope"});
    // Herbs
    gcheck::Random h_names({"Arrowroot", "Bay leaves", "Hawthorn", "Hypericum perforatum", "Poppy seeds", "Magic mushrooms", "Salvia divinorum", "Salvia officinalis", "Peppermint root"});

    gcheck::Random rnd_type(std::vector<FoodType>({People, PeopleFood, Herbs}));
    std::unordered_map<FoodType, gcheck::Random<const char*>*> names({std::pair(People, &p_names), std::pair(PeopleFood, &pf_names), std::pair(Herbs, &h_names)});

    for(size_t i = 0; i < count; i++) {
        FoodType type = rnd_type.Next();
        food.push_back({type, std::string(names[type]->Next())});
    }

    return food;
}

auto rnd_treasures = gcheck::RandomSizeContainer<std::list>(10, 30, CreateRandomTreasures(50));
auto rnd_foods = gcheck::RandomSizeContainer<std::list>(10, 30, CreateRandomFood(50));
gcheck::Random<std::string> rnd_name(std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
gcheck::Random<size_t> rnd_age(0, 10000);
gcheck::Random<size_t> rnd_size(5, 30);
auto rnd_names = gcheck::RandomSizeContainer(3, 3, std::vector<std::string>{"Puff", "Drogon", "Bahamut", "Haku"});
auto rnd_ages = gcheck::RandomSizeContainer(3, 3, (size_t)0, (size_t)10000);
auto rnd_sizes = gcheck::RandomSizeContainer(3, 3, (size_t)5, (size_t)30);


TEST(Dragons, constructors, 1) {

    size_t puff_age = rnd_age.Next();
    size_t bahamut_age = rnd_age.Next();
    size_t puff_size = rnd_size.Next();
    size_t bahamut_size = rnd_size.Next();
    MagicDragon* mdragon = new MagicDragon("Puff", puff_age, puff_size);
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", bahamut_age, bahamut_size);

    EXPECT_EQ("Puff", mdragon->GetName());
    EXPECT_EQ(puff_age, mdragon->GetAge());
    EXPECT_EQ(puff_size, mdragon->GetSize());

    EXPECT_EQ("Bahamut", fdragon->GetName());
    EXPECT_EQ(bahamut_age, fdragon->GetAge());
    EXPECT_EQ(bahamut_size, fdragon->GetSize());

    delete fdragon;
    delete mdragon;
}

template<typename T>
std::string THoardOutput(std::list<Treasure> treasures) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Hoard(treasures);
    return tout.str();
}
template<typename T>
std::vector<Treasure> THoardList(std::list<Treasure> treasures) {
    T("", 0, 0).Hoard(treasures);
    return std::vector<Treasure>(treasures.begin(), treasures.end());
}
template<typename T>
std::vector<Treasure> THoardDragons(std::list<Treasure> treasures) {
    T dragon("", 0, 0);
    dragon.Hoard(treasures);
    auto& treas = dragon.GetTreasures();
    return std::vector<Treasure>(treas.begin(), treas.end());
}

TEST(MagicDragon, Hoard_printed_output, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Wisdom,std::string("Gabriel's Wing")}}))) t) { return std::apply(THoardOutput<MagicDragon>, t); };
        std::vector correct = {std::string("Magic dragon received: Garroting gas\u000AMagic dragon received: Truth serum\u000AMagic dragon received: Liquid luck\u000A"),std::string("Magic dragon received: Truth serum\u000AMagic dragon received: Truth serum\u000AMagic dragon received: Gin tonic\u000AMagic dragon received: Liquid luck\u000AMagic dragon received: Cough syrup\u000AMagic dragon received: Garroting gas\u000AMagic dragon received: Cough syrup\u000A"),std::string("Magic dragon received: Essence of insanity\u000AMagic dragon received: Stoneskin potion\u000AMagic dragon received: Liquid luck\u000AMagic dragon received: Liquid luck\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Wisdom,std::string("Gabriel's Wing")}})),std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Critique of pure reason")}})),std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Liquid luck")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Hoard_printed_output, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Silver coins")}}))) t) { return std::apply(THoardOutput<FantasyDragon>, t); };
        std::vector correct = {std::string("Fantasy dragon received: Topaz\u000AFantasy dragon received: Sapphire dust\u000AFantasy dragon received: Silver coins\u000AFantasy dragon received: Gold bar\u000AFantasy dragon received: Silver coins\u000A"),std::string("Fantasy dragon received: Bag of pearls\u000AFantasy dragon received: Amber\u000AFantasy dragon received: Amber\u000AFantasy dragon received: Amber\u000AFantasy dragon received: Agate\u000AFantasy dragon received: Gold bar\u000A"),std::string("Fantasy dragon received: Topaz\u000AFantasy dragon received: Jade stone\u000AFantasy dragon received: Topaz\u000AFantasy dragon received: Topaz\u000AFantasy dragon received: Topaz\u000AFantasy dragon received: Topaz\u000AFantasy dragon received: Gold bar\u000AFantasy dragon received: Sapphire dust\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Silver coins")}})),std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Gold bar")}})),std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Sapphire dust")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}

TEST(MagicDragon, Hoard_treasures_left_in_list, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}}))) t) { return std::apply(THoardList<MagicDragon>, t); };
        std::vector correct = {std::vector<Treasure>({(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}}),std::vector<Treasure>({(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Agate")}}),std::vector<Treasure>({(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}})),std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Truth serum")}})),std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Hoard_treasures_left_in_list, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Bag of pearls")}}))) t) { return std::apply(THoardList<FantasyDragon>, t); };
        std::vector correct = {std::vector<Treasure>({(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("Biographia literaria")}}),std::vector<Treasure>({(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")}}),std::vector<Treasure>({(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Bag of pearls")}})),std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Essence of insanity")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Jewellery,std::string("Bag of pearls")}})),std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}

TEST(MagicDragon, Hoard_dragons_treasures, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Cough syrup")}}))) t) { return std::apply(THoardDragons<MagicDragon>, t); };
        std::vector correct = {std::vector<Treasure>({(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Cough syrup")}}),std::vector<Treasure>({(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Garroting gas")}}),std::vector<Treasure>({(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Potions,std::string("Liquid luck")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Cough syrup")}})),std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("MAOL")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("MAOL")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Potions,std::string("Garroting gas")}})),std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Liquid luck")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Hoard_dragons_treasures, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Blemish blitzer")}}))) t) { return std::apply(THoardDragons<FantasyDragon>, t); };
        std::vector correct = {std::vector<Treasure>({(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Gold bar")}}),std::vector<Treasure>({(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Bag of pearls")}}),std::vector<Treasure>({(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Agate")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Potions,std::string("Truth serum")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Blemish blitzer")}})),std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Bag of pearls")}})),std::tuple(std::list<Treasure>({(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Critique of pure reason")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}

template<typename T>
std::string TEatOutput(std::list<Food> foods) {
    gcheck::StdoutCapturer tout;
    T("", 0, 0).Eat(foods);
    return tout.str();
}
template<typename T>
std::vector<Food> TEatList(std::list<Food> foods) {
    T("", 0, 0).Eat(foods);
    return std::vector<Food>(foods.begin(), foods.end());
}
template<typename T>
size_t TEatSize(std::list<Food> foods) {
    T dragon("", 0, 0);
    dragon.Eat(foods);
    return dragon.GetSize();
}

TEST(MagicDragon, Eat_printed_output, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Magic mushrooms")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Hawthorn")},(Food){People,std::string("John Smith")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("Joonas")},(Food){Herbs,std::string("Peppermint root")}}))) t) { return std::apply(TEatOutput<MagicDragon>, t); };
        std::vector correct = {std::string("Magic dragon ate: Hypericum perforatum\u000AMagic dragon ate: Poppy seeds\u000AMagic dragon ate: Poppy seeds\u000AMagic dragon ate: Magic mushrooms\u000AMagic dragon ate: Hawthorn\u000AMagic dragon ate: Peppermint root\u000A"),std::string("Magic dragon ate: Magic mushrooms\u000AMagic dragon ate: Poppy seeds\u000AMagic dragon ate: Hypericum perforatum\u000AMagic dragon ate: Salvia divinorum\u000AMagic dragon ate: Hawthorn\u000AMagic dragon ate: Magic mushrooms\u000AMagic dragon ate: Salvia divinorum\u000AMagic dragon ate: Bay leaves\u000A"),std::string("Magic dragon ate: Salvia divinorum\u000AMagic dragon ate: Poppy seeds\u000AMagic dragon ate: Hypericum perforatum\u000AMagic dragon ate: Hawthorn\u000AMagic dragon ate: Hawthorn\u000AMagic dragon ate: Hypericum perforatum\u000AMagic dragon ate: Salvia divinorum\u000AMagic dragon ate: Poppy seeds\u000AMagic dragon ate: Hypericum perforatum\u000AMagic dragon ate: Hypericum perforatum\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Magic mushrooms")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Hawthorn")},(Food){People,std::string("John Smith")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("Joonas")},(Food){Herbs,std::string("Peppermint root")}})),std::tuple(std::list<Food>({(Food){Herbs,std::string("Magic mushrooms")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Poppy seeds")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Hawthorn")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Magic mushrooms")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("John Smith")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Bay leaves")}})),std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Flank steak")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Pork ribs")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Hawthorn")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Hawthorn")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Pork ribs")},(Food){Herbs,std::string("Salvia divinorum")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Carnivore pizza")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Eat_printed_output, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){People,std::string("John Smith")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Magic mushrooms")},(Food){Herbs,std::string("Hawthorn")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Salvia divinorum")}}))) t) { return std::apply(TEatOutput<FantasyDragon>, t); };
        std::vector correct = {std::string("Fantasy dragon ate: John Smith\u000AFantasy dragon ate: Raimo\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: John Smith\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Joonas\u000AFantasy dragon ate: Beef chuck\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Tenderloin steak\u000AFantasy dragon ate: Horse (salami)\u000AFantasy dragon ate: Random crusader\u000AFantasy dragon ate: Random crusader\u000AFantasy dragon ate: Tenderloin steak\u000AFantasy dragon ate: Beef chuck\u000A"),std::string("Fantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Pork rack\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Pork rack\u000AFantasy dragon ate: Barack Obama\u000AFantasy dragon ate: Konsta\u000AFantasy dragon ate: Raimo\u000AFantasy dragon ate: Pork rack\u000AFantasy dragon ate: Tenderloin steak\u000AFantasy dragon ate: John Smith\u000AFantasy dragon ate: Raimo\u000AFantasy dragon ate: Raimo\u000A"),std::string("Fantasy dragon ate: Joonas\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Beef chuck\u000AFantasy dragon ate: Carnivore pizza\u000AFantasy dragon ate: Raimo\u000AFantasy dragon ate: Random crusader\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){People,std::string("John Smith")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Magic mushrooms")},(Food){Herbs,std::string("Hawthorn")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Salvia divinorum")}})),std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Bay leaves")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("Raimo")},(Food){People,std::string("Raimo")}})),std::tuple(std::list<Food>({(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}

TEST(MagicDragon, Eat_foods_left_in_list, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Bay leaves")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hawthorn")},(Food){People,std::string("Raimo")}}))) t) { return std::apply(TEatList<MagicDragon>, t); };
        std::vector correct = {std::vector<Food>({(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Raimo")}}),std::vector<Food>({(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Barack Obama")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Flank steak")}}),std::vector<Food>({(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Pork ribs")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("Raimo")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Bay leaves")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hawthorn")},(Food){People,std::string("Raimo")}})),std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Barack Obama")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Flank steak")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Flank steak")},(Food){Herbs,std::string("Poppy seeds")}})),std::tuple(std::list<Food>({(Food){Herbs,std::string("Salvia divinorum")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Pork ribs")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Flank steak")},(Food){Herbs,std::string("Salvia divinorum")},(Food){People,std::string("Raimo")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Poppy seeds")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Eat_foods_left_in_list, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Raimo")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")}}))) t) { return std::apply(TEatList<FantasyDragon>, t); };
        std::vector correct = {std::vector<Food>({(Food){Herbs,std::string("Salvia divinorum")}}),std::vector<Food>({(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Salvia divinorum")}}),std::vector<Food>({(Food){Herbs,std::string("Bay leaves")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Magic mushrooms")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Bay leaves")}})};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Raimo")},(Food){People,std::string("Barack Obama")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("Raimo")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")}})),std::tuple(std::list<Food>({(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Cornered beef")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Salvia divinorum")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Salvia divinorum")}})),std::tuple(std::list<Food>({(Food){Herbs,std::string("Bay leaves")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Peppermint root")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Magic mushrooms")},(Food){People,std::string("Raimo")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Bay leaves")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Cornered beef")},(Food){People,std::string("Raimo")},(Food){People,std::string("Raimo")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}

TEST(MagicDragon, Eat_dragon_size, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){Herbs,std::string("Bay leaves")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Pork rack")}}))) t) { return std::apply(TEatSize<MagicDragon>, t); };
        std::vector correct = {5UL,6UL,8UL};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){Herbs,std::string("Bay leaves")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Pork rack")}})),std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Beef chuck")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Cornered beef")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Poppy seeds")},(Food){People,std::string("Konsta")},(Food){PeopleFood,std::string("Flank steak")},(Food){People,std::string("Random crusader")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hawthorn")}})),std::tuple(std::list<Food>({(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Random crusader")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){People,std::string("Raimo")},(Food){People,std::string("Joonas")},(Food){People,std::string("Joonas")},(Food){People,std::string("Konsta")},(Food){Herbs,std::string("Salvia divinorum")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Raimo")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Hawthorn")},(Food){Herbs,std::string("Poppy seeds")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Tenderloin steak")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}
TEST(FantasyDragon, Eat_dragon_size, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Food>({(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Barack Obama")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Magic mushrooms")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")}}))) t) { return std::apply(TEatSize<FantasyDragon>, t); };
        std::vector correct = {13UL,20UL,18UL};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Food>({(Food){Herbs,std::string("Poppy seeds")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Barack Obama")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Magic mushrooms")},(Food){Herbs,std::string("Peppermint root")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")}})),std::tuple(std::list<Food>({(Food){PeopleFood,std::string("Pork rack")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Magic mushrooms")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Random crusader")},(Food){People,std::string("John Smith")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("John Smith")},(Food){PeopleFood,std::string("Beef chuck")},(Food){PeopleFood,std::string("Horse (salami)")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){People,std::string("Joonas")},(Food){Herbs,std::string("Poppy seeds")},(Food){People,std::string("Barack Obama")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){PeopleFood,std::string("Tenderloin steak")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Half of a pork's ass")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Beef chuck")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Cornered beef")}})),std::tuple(std::list<Food>({(Food){People,std::string("Joonas")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Cornered beef")},(Food){People,std::string("Random crusader")},(Food){PeopleFood,std::string("Flank steak")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Joonas")},(Food){PeopleFood,std::string("Pork ribs")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){PeopleFood,std::string("Pork rack")},(Food){Herbs,std::string("Peppermint root")},(Food){PeopleFood,std::string("Flank steak")},(Food){PeopleFood,std::string("Pork rack")},(Food){People,std::string("Random crusader")},(Food){People,std::string("Raimo")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Poppy seeds")},(Food){Herbs,std::string("Hypericum perforatum")},(Food){Herbs,std::string("Salvia divinorum")},(Food){PeopleFood,std::string("Carnivore pizza")},(Food){People,std::string("Random crusader")}}))}));
        CompareWithAnswer(3,correct,forwarder,inputs);
    };
}


template<typename T>
std::string TPrint(std::list<Treasure> treasures, std::string name, size_t age, size_t size) {
    T dragon(name, age, size);
    dragon.Hoard(treasures);
    std::stringstream os;
    os << dragon;
    return os.str();
}

TEST(Dragon, ostream_write_operator, 1, "Dragons.constructors") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Truth serum")}}),std::string("Bahamut"),691UL,26UL)) t) { return std::apply(TPrint<MagicDragon>, t); };
        std::vector correct = {std::string("Dragon named: Bahamut, age: 691, size: 26\u000ATreasures:\u000AStoneskin potion\u000ALiquid luck\u000AGarroting gas\u000ATruth serum\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Wisdom,std::string("The C++ standard")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Truth serum")}}),std::string("Bahamut"),691UL,26UL)}));
        CompareWithAnswer(1,correct,forwarder,inputs);
    };
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Jewellery,std::string("Silver coins")}}),std::string("Haku"),9189UL,25UL)) t) { return std::apply(TPrint<FantasyDragon>, t); };
        std::vector correct = {std::string("Dragon named: Haku, age: 9189, size: 25\u000ATreasures:\u000ABag of pearls\u000AGold bar\u000ASapphire dust\u000ATopaz\u000ATopaz\u000AJade stone\u000AGold bar\u000ATopaz\u000AAgate\u000ASilver coins\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Potions,std::string("Cough syrup")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Wisdom,std::string("Sun Tzu's Art of War")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Wisdom,std::string("The Symposium")},(Treasure){Jewellery,std::string("Jade stone")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Potions,std::string("Cough syrup")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Thus Spoke Zarathustra")},(Treasure){Jewellery,std::string("Silver coins")}}),std::string("Haku"),9189UL,25UL)}));
        CompareWithAnswer(1,correct,forwarder,inputs);
    };
}

TEST(DragonCave, Accommodate, 2, "Dragons.constructors") {

    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(mdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(fdragon, *it) << "Second item in GetDragons";
}

TEST(DragonCave, Evict, 3, "Accommodate") {
    // Random treasures
    std::list<Treasure> treasures = rnd_treasures.Next();
    // Random food
    std::list<Food> food = rnd_foods.Next();

    MagicDragon* mdragon = new MagicDragon("Puff", rnd_age.Next(), rnd_size.Next());
    FantasyDragon* fdragon = new FantasyDragon("Bahamut", rnd_age.Next(), rnd_size.Next());
    MagicDragon* mdragon2 = new MagicDragon("Drogon", rnd_age.Next(), rnd_size.Next());

    DragonCave cave;

    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    cave.Accommodate(mdragon2);

    cave.Evict("Puff");

    auto it = cave.GetDragons().begin();

    EXPECT_EQ(fdragon, *it) << "First item in GetDragons";
    it++;

    EXPECT_EQ(mdragon2, *it) << "Second item in GetDragons";

    delete mdragon;
}

std::string TCavePrint(std::list<Treasure> treasures, std::vector<std::string> names, std::vector<size_t> ages, std::vector<size_t> sizes) {
    DragonCave cave;
    MagicDragon* mdragon = new MagicDragon(names[0], ages[0], sizes[0]);
    FantasyDragon* fdragon = new FantasyDragon(names[1], ages[1], sizes[1]);
    mdragon->Hoard(treasures);
    fdragon->Hoard(treasures);
    cave.Accommodate(mdragon);
    cave.Accommodate(fdragon);
    std::stringstream os;
    os << cave;
    return os.str();
}

TEST(DragonCave, stream_write_operator, 3, "Accommodate Dragon.ostream_write_operator") {
    {
        auto forwarder = [](decltype(std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Jewellery,std::string("Sapphire dust")}}),std::vector<std::__cxx11::basic_string<char>>({std::string("Puff"),std::string("Puff"),std::string("Bahamut")}),std::vector<long unsigned int>({6383UL,7178UL,7166UL}),std::vector<long unsigned int>({13UL,9UL,25UL}))) t) { return std::apply(TCavePrint, t); };
        std::vector correct = {std::string("DragonCave dwellers:\u000A\u000ADragon named: Puff, age: 6383, size: 13\u000ATreasures:\u000AGin tonic\u000ALiquid luck\u000AStoneskin potion\u000ABlemish blitzer\u000AGarroting gas\u000ALiquid luck\u000AGin tonic\u000A\u000ADragon named: Puff, age: 7178, size: 9\u000ATreasures:\u000ABag of pearls\u000ASapphire dust\u000ASilver coins\u000ATopaz\u000AAgate\u000AGold bar\u000AAmber\u000AAmber\u000AGold bar\u000AAmber\u000AAgate\u000AGold bar\u000ASapphire dust\u000A")};
        gcheck::SequenceArgument inputs(std::vector({std::tuple(std::list<Treasure>({(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Bag of pearls")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Sapphire dust")},(Treasure){Jewellery,std::string("Silver coins")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Critique of pure reason")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Potions,std::string("Stoneskin potion")},(Treasure){Jewellery,std::string("Topaz")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Wisdom,std::string("Scroll of infinite wisdom")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Blemish blitzer")},(Treasure){Potions,std::string("Garroting gas")},(Treasure){Wisdom,std::string("Biographia literaria")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Jewellery,std::string("Amber")},(Treasure){Potions,std::string("Liquid luck")},(Treasure){Jewellery,std::string("Agate")},(Treasure){Wisdom,std::string("Gabriel's Wing")},(Treasure){Jewellery,std::string("Gold bar")},(Treasure){Potions,std::string("Gin tonic")},(Treasure){Jewellery,std::string("Sapphire dust")}}),std::vector<std::__cxx11::basic_string<char>>({std::string("Puff"),std::string("Puff"),std::string("Bahamut")}),std::vector<long unsigned int>({6383UL,7178UL,7166UL}),std::vector<long unsigned int>({13UL,9UL,25UL}))}));
        CompareWithAnswer(1,correct,forwarder,inputs);
    };
}
namespace {
    template<class>
    struct sfinae_bool {};
    template<class T>
    struct sfinae_true : sfinae_bool<T>, std::true_type{};
    template<class T>
    struct sfinae_false : sfinae_bool<T>, std::false_type{};
}

namespace detail {
    template<class T>
    static auto has_copy_constructor(int) -> sfinae_true<decltype(T(std::declval<T>()))>;
    template<class T>
    static auto has_copy_constructor(long) -> sfinae_false<T>;

    template<class T>
    static auto has_copy_assignment(int) -> sfinae_true<decltype(std::declval<T>() = std::declval<T>())>;
    template<class T>
    static auto has_copy_assignment(long) -> sfinae_false<T>;
} // detail

template<class T>
struct has_copy_constructor_t : decltype(detail::has_copy_constructor<T>(0)){};
template<class T>
struct has_copy_assignment_t : decltype(detail::has_copy_assignment<T>(0)){};

TEST(DragonCave, copy_assignment_constructor, 2) {
    bool has_copy_constructor = has_copy_constructor_t<DragonCave>();
    bool has_copy_assignment = has_copy_assignment_t<DragonCave>();
    EXPECT_FALSE(has_copy_constructor) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Dragon)\nfor any changes to this to take effect when running locally";
    EXPECT_FALSE(has_copy_assignment) << "You might have to run 'make clean' (ctrl + shift + b -> Clean test Dragon)\nfor any changes to this to take effect when running locally";
}