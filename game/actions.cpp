#include "actions.h"
#include "standardActions.h"

coordinate::coordinate(const int& x, const int& y) : x(x), y(y) {}

action::action(const std::string& name, const std::string& description, const std::vector<coordinate>& moves, const std::vector<DAMAGE_TYPES>& blocks, const int& charge) : name(name), description(description), moves(moves), blocks(blocks), charge(charge) {}

heroActions::heroActions() : allActions(), actionDeck(), hand() {
    allActions.push_back("pass");
    allActions.push_back("moveAdj1");
    allActions.push_back("charge1");
}

heroActions::heroActions(const heroActions& other) : allActions(other.allActions), actionDeck(), hand() {}

heroActions::heroActions(const std::vector<std::string>& actionList) : allActions(actionList), actionDeck(), hand() {}

