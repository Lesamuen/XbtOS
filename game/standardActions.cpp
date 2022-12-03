#include "standardActions.h"

void initStandardActions() {
    std::vector<coordinate> moveBuilder;
    std::vector<DAMAGE_TYPE> blockBuilder;

    // free actions: pass, charge 1, move adjacent
    // other free action is technically "strike" but thats a different function alltogether
    actions.emplace("pass", action("Pass", "Do nothing", moveBuilder, blockBuilder));

    actions.emplace("charge1", action("Charge", "Charge 1", moveBuilder, blockBuilder, 1));

    moveBuilder.emplace_back(1, 0);
    moveBuilder.emplace_back(0, 1);
    moveBuilder.emplace_back(-1, 0);
    moveBuilder.emplace_back(0, -1);
    actions.emplace("moveAdj1", action("Sidestep", "Move adjacently", moveBuilder, blockBuilder));
    moveBuilder.clear();
}