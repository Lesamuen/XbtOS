#ifndef ACTIONS_H
#define ACTIONS_H

#include <vector>
#include <string>

/* Simple structure describing a 2D set of Cartesian coordinates, whether relative or absolute.
 * Player character is assumed to be in the center of the grid at (0,0).
 * Bottom right is first quadrant (positive, positive)
 */
struct coordinate {
    int x, y;
};

/* List of damage types.
 * Every enemy move corresponds to one of these.
 */
enum DAMAGE_TYPES {
    physical,
    emotional
};

/* The interface for a single 'card', or action.
 * Each one can:
 *      move the hero (generate a list of possible locations to move to),
 *      block damage types,
 *      charge up meter
 */
class action {
private:
    /* The name of the action.
     */
    static std::string name;

    /* The description of the action, such as:
     * Move Diagonal 2
     * Block Physical
     * Charge 1
     */
    static std::string description;

    /* A list of Coordinates that corresponds to squares the hero can move to with their action.
     */
    static std::vector<coordinate> moves;

    /* A list of damage types the action blocks.
     * Should not have duplicates.
     */
    static std::vector<DAMAGE_TYPES> blocks;

    /* Amount the action charges the hero's weapon.
     */
    static int charge;

public:
    /* Returns a list of Coordinates that corresponds to squares the hero can move to with this action.
     * The hero may only choose one on their turn.
     * Default is no squares, for a non-move action.
     * 
     * Output:
     *      vector of Coordinate that describes where the hero can choose to move
     */
    std::vector<coordinate>& getMoves();

    /* Returns a list of DAMAGE_TYPEs that corresponds to the ones that don't kill the hero.
     * 
     * Output:
     *      vector of DAMAGE_TYPE that describes what damage types the hero blocks
     */
    std::vector<DAMAGE_TYPES>& getBlocks();

    /* Returns the number of levels this move increases the charge meter by.
     *
     * Output:
     *      integer describing charge level to increase charge meter by
     */
    int& getCharge();

    /* Returns the name of the action.
     *
     * Output:
     *      string describing the name of the action
     */
    std::string& getName();
    
    /* Returns the description of the action.
     *
     * Output:
     *      string describing what the action does
     */
    std::string& getDescription();
};

/* A 'deck' of actions; one per player character.
 * Specifies the total list of cards, along with a list of cards currently in play/in discard, and the current hand of the hero.
 */
class heroActions {
private:
    /* Full unordered list of actions available to the hero.
     */
    std::vector<action> allActions;

    /* Randomized, ordered list of actions; drawn from the back.
     * Does not include used actions.
     */
    std::vector<action> actionDeck;

    /* The list of actions the player character can use on his turn.
     * Max hand size 7, draw up to max hand size per turn.
     * Can discard any amount.
     */
    std::vector<action> hand;

public:
    /* Default constructor contains the default list of actions that is available to the hero at the beginning.
     * Contains:
     */
    heroActions();

    /* Copy constructor
     * Only copies allActions
     *
     * Input:
     *      other = Another instance of heroActions
     */
    heroActions(const heroActions& other);

    /* Copy a list of actions into a heroActions class.
     *
     * Input:
     *      actionList = standard vector of actions
     */
    heroActions(const std::vector<action>& actionList);

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
};

#endif