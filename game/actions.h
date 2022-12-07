#ifndef ACTIONS_H
#define ACTIONS_H

#include "enums.h"
#include "coordinate.h"

#include <vector>
#include <unordered_map>
#include <string>

/* The interface for a single 'card', or action.
 * Each one can:
 *      move the hero (generate a list of possible locations to move to),
 *      block damage types,
 *      charge up meter
 */
struct action {
    /* The name of the action.
     */
    std::string name;

    /* The description of the action, such as:
     * Move Diagonal 2
     * Block Physical
     * Charge 1
     */
    std::string description;

    /* A list of Coordinates that corresponds to squares the hero can move to with their action.
     */
    std::vector<coordinate> moves;

    /* A list of damage types the action blocks.
     * Should not have duplicates.
     */
    std::vector<DAMAGE_TYPE> blocks;

    /* Amount the action charges the hero's weapon.
     */
    int charge;

    /* Per-parameter constructor.
     */
    action(const std::string& name, const std::string& description, const std::vector<coordinate>& moves, const std::vector<DAMAGE_TYPE>& blocks, const int& charge = 0);

    /* Ostream overload for information of action, for testing
     */
    friend std::ostream& operator<<(std::ostream& out, const action& action);
};

/* A 'deck' of actions; one per player character.
 * Specifies the total list of cards, along with a list of cards currently in play/in discard, and the current hand of the hero.
 */
class heroActions {
private:
    /* Full unordered list of actions available to the hero.
     */
    std::vector<std::string> allActions;

    /* Randomized, ordered list of actions; drawn from the back.
     * Does not include used actions.
     */
    std::vector<std::string> actionDeck;

    /* The list of actions the player character can use on his turn.
     * Max hand size 7, draw up to max hand size per turn.
     * Can discard any amount.
     */
    std::vector<action> hand;

public:
    /* Default constructor contains the default list of actions that is available to the hero at the beginning.
     * Contains: (test) pass, charge, sidestep
     */
    heroActions();

    /* Copy constructor
     * Only copies allActions
     *
     * Input:
     *      other = Another instance of heroActions
     */
    heroActions(const heroActions& other);

    /* Copy a list of action IDs into a heroActions class.
     *
     * Input:
     *      actionList = standard vector of actions
     */
    heroActions(const std::vector<std::string>& actionList);

    /* Shuffle the full action list into the deck, and re-empty the hand.
     */
    void shuffle();

    /* Attempt to draw an action from the top (back) of the deck into the hand.
     * Max hand size is currently 7.
     * 
     * Throws:
     *      0 - Deck is empty
     *      1 - Hand is full
     */
    void draw();

    /* Remove an action from the hand.
     *
     * Input:
     *      index = 0-index of action to be discarded from hand. Assumed to be valid.
     */
    void discard(const int& index);

    int getTotalActions();

    int getCurrentActions();

    int getNumHand();
    
    action& getHandAction(int index);

    /* Print every action in the hand.
     * For testing purposes.
     */
    void printHand();
};

/* A hash table containing every action by their internal ID (different from action name).
 */
extern std::unordered_map<std::string, action> actions;

/* A vector containing a list of action IDs that disincludes standard actions.
 * Separated by "level" of cards; how strong they are, subjectively.
 * Used to generate new cards to select from upon win.
 */
extern std::vector<std::vector<std::string>> actionGen; 

#endif