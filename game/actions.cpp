#include "actions.h"
#include "standardActions.h"
#include "randomGen.h"

#include <iostream>

action::action(const std::string& name, const std::string& description, const std::vector<coordinate>& moves, const std::vector<DAMAGE_TYPE>& blocks, const int& charge, const bool& strike) : name(name), description(description), moves(moves), blocks(blocks), charge(charge), strike(strike) {}

std::ostream& operator<<(std::ostream& out, const action& action) {
    out << action.name << std::endl;
    out << action.description << std::endl;
    return out;
}


heroActions::heroActions() : allActions(), actionDeck(), hand() {
    allActions.push_back("shift");
    allActions.push_back("shift");
    allActions.push_back("slide");
    allActions.push_back("slide");
    allActions.push_back("shield");
    allActions.push_back("shield");
    allActions.push_back("embolden");
    allActions.push_back("embolden");
}

heroActions::heroActions(const heroActions& other) : allActions(other.allActions), actionDeck(), hand() {}

heroActions::heroActions(const std::vector<std::string>& actionList) : allActions(actionList), actionDeck(), hand() {}

void heroActions::shuffle() {
    // It's called "shuffle" because original intent was to randomize in this function;
    // now, randomization occurs in draw().
    actionDeck = allActions;
    hand.clear();
}

void heroActions::draw() {
    if (actionDeck.size() == 0) {
        throw 0;
    }
    if (hand.size() == 7) {
        throw 1;
    }
    // Draw until 7
    while (hand.size() < 7) {
        int randAction = random(0, actionDeck.size() - 1);
        hand.push_back(actions.at(actionDeck.at(randAction)));
        actionDeck.erase(actionDeck.begin() + randAction);

        if (actionDeck.size() == 0) {
            return;
        }
    }
}

void heroActions::discard(const int& index) {
    hand.erase(hand.begin() + index);
}

void heroActions::printHand() {
    for (int i = 0; i < hand.size(); i++) {
        std::cout << hand.at(i) << std::endl;
    }
}

int heroActions::getTotalActions() {
    return allActions.size();
}

int heroActions::getCurrentActions() {
    return actionDeck.size();
}

int heroActions::getNumHand() {
    return hand.size();
}

action& heroActions::getHandAction (int index) {
    if (index >= hand.size()) {
        throw 0;
    }

    return hand.at(index);
}

std::unordered_map<std::string, action> actions;

std::vector<std::vector<std::string>> actionGen;