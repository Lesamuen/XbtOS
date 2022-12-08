#include "standardActions.h"
#include "actions.h"

void initStandardActions() {
    std::vector<coordinate> moveBuilder;
    std::vector<DAMAGE_TYPE> blockBuilder;

    // dummy empty action
    // null
    actions.emplace("null", action("", "", moveBuilder, blockBuilder));

    // free actions:
    // Pass
    actions.emplace("pass", action("Pass", "Do nothing", moveBuilder, blockBuilder));

    // Charge
    actions.emplace("charge", action("Charge", "Charge 1", moveBuilder, blockBuilder, 1));

    // Sidestep
    moveBuilder.emplace_back(1, 0);
    moveBuilder.emplace_back(0, 1);
    moveBuilder.emplace_back(-1, 0);
    moveBuilder.emplace_back(0, -1);
    actions.emplace("sidestep", action("Sidestep", "Move adjacently 1 tile", moveBuilder, blockBuilder));
    moveBuilder.clear();

    // Strike
    actions.emplace("strike", action("Strike", "Commit the final blow", moveBuilder, blockBuilder, 0, true));

    // lvl 1 actions:
    // Shift
    moveBuilder.emplace_back(1, 0);
    moveBuilder.emplace_back(0, 1);
    moveBuilder.emplace_back(-1, 0);
    moveBuilder.emplace_back(0, -1);
    moveBuilder.emplace_back(1, 1);
    moveBuilder.emplace_back(-1, -1);
    moveBuilder.emplace_back(-1, 1);
    moveBuilder.emplace_back(1, -1);
    actions.emplace("shift", action("Shift", "Move 1 tile", moveBuilder, blockBuilder));
    moveBuilder.clear();

    // Slide
    moveBuilder.emplace_back(1, 0);
    moveBuilder.emplace_back(0, 1);
    moveBuilder.emplace_back(-1, 0);
    moveBuilder.emplace_back(0, -1);
    moveBuilder.emplace_back(2, 0);
    moveBuilder.emplace_back(0, 2);
    moveBuilder.emplace_back(-2, 0);
    moveBuilder.emplace_back(0, -2);
    actions.emplace("slide", action("Slide", "Move adjacently up to 2 tiles", moveBuilder, blockBuilder));
    moveBuilder.clear();

    // Shield
    blockBuilder.push_back(DAMAGE_TYPE::physical);
    actions.emplace("shield", action("Shield", "Block all Physical damage", moveBuilder, blockBuilder));
    blockBuilder.clear();

    // Embolden
    moveBuilder.emplace_back(1, 0);
    moveBuilder.emplace_back(0, 1);
    moveBuilder.emplace_back(-1, 0);
    moveBuilder.emplace_back(0, -1);
    actions.emplace("embolden", action("Embolden", "Move adjacently 1 tile\nCharge 1", moveBuilder, blockBuilder, 1));
    moveBuilder.clear();
}