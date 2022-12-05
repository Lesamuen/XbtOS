#ifndef ENUM_H
#define ENUM_H

/* List of types of movement for enemy actions.
 * See enemyMove in enemy.h.
 */
enum class ENEMY_MOVEMENT_DIRECTION {
    absolute,
    relative
};

/* List of types of attacks for enemy actions.
 * See enemyMove in enemy.h.
 */
enum class ENEMY_ATTACK_TYPE {
    absolute,
    relative,
    direct,
    ranged
};

/* List of damage types.
 * Every enemy move corresponds to one of these.
 */
enum class DAMAGE_TYPE {
    physical,
    arcane,
    flame,
    ice,
    chemical,
    mind
};

#endif