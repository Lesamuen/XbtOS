#ifndef ENEMY_H
#define ENEMY_H

#include "enums.h"
#include "coordinate.h"

#include <string>
#include <vector>
#include <unordered_map>

/* A threatened square, with a coordinate and a damage type.
 */
struct threatenedTile : coordinate {
    DAMAGE_TYPE type;

    /* Per-parameter constructor
     */
    threatenedTile(const int& x, const int& y, DAMAGE_TYPE type);

    /* Adds a coordinate to the tile's coordinates, keeping the damage type.
     */
    threatenedTile& operator+=(const coordinate& other);
};

/* A single enemy move. One of these is used per turn.
 * Due to limits of object-orientation, this structure will describe a move.
 * An external function will handle calculating results.
 * 
 * Each one will have:
 *      - A name
 *      - Movement, in terms of cartesian coordinates, top left to bottom right
 *      - Movement Direction:
 *          absolute means movement as is,
 *          relative means positive Y angled towards hero.
 *          Only in right angle increments.
 *      - Attack Shape: list of squares for the attack. Each tile has an associated damage type. 0,0 is center.
 *      - Attack Type:
 *          absolute means direction as is, with 0,0 being on enemy
 *          relative means aimed in the 90 degree rotation towards hero, with 0,0 on enemy
 *          direct means 0,0 on hero, absolute direction
 *          ranged means 0,0 towards hero up to a certain range, relative direction
 *      - Range: only used if ranged attack type.
 */
struct enemyMove {
    /* Name of the move, to show to player.
     */
    std::string name;

    /* Describes how the enemy moves.
     */
    coordinate movement;

    /* Describes whether direction affects the movement.
     */
    ENEMY_MOVEMENT_DIRECTION movementDirection;

    /* Describes the tiles that will be threatened and their damage types.
     */
    std::vector<threatenedTile> attackShape;

    /* Describes how the attack's shape will be placed on the map.
     */
    ENEMY_ATTACK_TYPE attackType;

    /* If ranged attack type, how far attack can land, 4-adjacent.
     */
    int range;

    /* Per-parameter constructor.
     */
    enemyMove(const std::string& name, const coordinate& movement, const ENEMY_MOVEMENT_DIRECTION& movementDirection, const std::vector<threatenedTile>& attackShape, const ENEMY_ATTACK_TYPE& attackType, const int& range = 0);
};

/* A movegroup consists of 1 or more moves; allows for multi-turn predictable behavior.
 * Movegroups are what are randomly selected to decide enemy behavior.
 */
class moveGroup {
    /* The list of moves in the movegroup, ordered from first to last.
     */
    std::vector<enemyMove> moves;

public:
    /* Add a move to the end of the group.
     *
     * Input:
     *      move = the move to add to the group
     */
    void addMove(const enemyMove& move);

    /* Empty the vector of moves.
     */
    void clear();
    
    /* Creates a new 'instance' of the movegroup by allocating an integer tracker.
     * Allows for multiple enemies on the map at once.
     *
     * Output:
     *      move tracker in the form of an integer (pointer).
     */
    int* newInstance();

    /* Deallocates the provided tracker.
     *
     * Input:
     *      tracker = the tracker provided by newInstance
     */
    void removeInstance(int* tracker);

    /* Gets the next move, and advances the tracker for the move group.
     *
     * Input:
     *      tracker = the tracker provided by newInstance
     * Output:
     *      next move
     * Throws:
     *      0 - No more moves left in group
     */
    enemyMove& nextMove(int* tracker);

    /* Resets the move tracker back to the beginning.
     *
     * Input:
     *      tracker = the previously provided tracker pointer
     */
    void resetGroup(int* tracker);
};

/* An enemy has a set of moveGroups it randomly selects from to decide its behavior.
 * It is defined by its move set and its "power", the amount of charge needed to kill it.
 * An object of this only holds information globally for an enemy type; values such as position will be handled elsewhere.
 */
class enemy {
    /* The display name of the enemy.
     */
    std::string name;

    /* The set of moveGroups that is randomly selected from to define the enemy's behavior.
     */
    std::vector<moveGroup> moveSet;
    
    /* The amount of charge required to deal the Ultimate Attack to this enemy.
     * If multiple enemies, charge required is averaged across them.
     */
    int power;

public:
    /* Constructor that initializes power and leaves moveSet empty, to avoid high copying overhead.
     * Initialize moveSet later by adding moveGroups manually.
     */
    enemy(const std::string& name, const int& power);

    /* Adds a move group to the move set. 
     *
     * Input:
     *      moveGroup = a moveGroup to be added; order doesn't matter because moveSet is randomly selected from.
     */
    void addMoveGroup(const moveGroup& moveGroup);

    /* Randomly selects a move group from the set.
     *
     * Output:
     *      a reference to a randomly selected move group
     */
    moveGroup& nextMoves();

    const std::string& getName();

    const int& getPower();
};

/* Parse an enemyMove based on enemy and hero position, and set new enemy position and get exact threatened squares.
 */
std::vector<threatenedTile> parseEnemyMove(const enemyMove& move, coordinate& enemyPosition, const coordinate& heroPosition);

/* A hash table containing every enemy by their internal ID (different from enemy name).
 */
extern std::unordered_map<std::string, enemy> enemies;

#endif