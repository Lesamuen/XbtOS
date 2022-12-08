#include "enemy.h"
#include "randomGen.h"

#include <cmath>

threatenedTile::threatenedTile(const int& x, const int& y, DAMAGE_TYPE type) : coordinate(x, y), type(type) {}

threatenedTile& threatenedTile::operator+=(const coordinate& other) {
    x += other.x;
    y += other.y;
    return *this;
}


enemyMove::enemyMove(const std::string& name, const coordinate& movement, const ENEMY_MOVEMENT_DIRECTION& movementDirection, const std::vector<threatenedTile>& attackShape, const ENEMY_ATTACK_TYPE& attackType, const int& range) : name(name), movement(movement), movementDirection(movementDirection), attackShape(attackShape), attackType(attackType), range(range) {}


void moveGroup::addMove(const enemyMove& move) {
    moves.push_back(move);
}

void moveGroup::clear() {
    moves.clear();
}

int* moveGroup::newInstance() {
    return new int(0);
}

void moveGroup::removeInstance(int*& tracker) {
    delete tracker;
}

enemyMove& moveGroup::nextMove(int*& tracker) {
    if (*tracker == (int) moves.size()) {
        throw 0;
    }
    return moves[(*tracker)++];
}

void moveGroup::resetGroup(int*& tracker) {
    *tracker = 0;
}


enemy::enemy(const std::string& name, const int& power) : name(name), moveSet(), power(power) {}

void enemy::addMoveGroup(const moveGroup& moveGroup) {
    moveSet.push_back(moveGroup);
}

moveGroup& enemy::nextMoves() {
    return moveSet[random(0, moveSet.size() - 1)];
}

const std::string& enemy::getName() {
    return name;
}

const int& enemy::getPower() {
    return power;
}


std::vector<threatenedTile> parseEnemyMove(const enemyMove& move, coordinate& enemyPosition) {
    // Always parse movement before attacks
    // Ignore movement if it will bring enemy upon hero (0,0)
    switch (move.movementDirection) {
        case ENEMY_MOVEMENT_DIRECTION::absolute:
            // If absolute, add as-is
            if (enemyPosition.x + move.movement.x != 0 || enemyPosition.y + move.movement.y != 0) {
                enemyPosition += move.movement;
            }
        break;

        case ENEMY_MOVEMENT_DIRECTION::relative:
            {
            // Calculate angle towards hero, in 90 degree buckets
            double angle = (std::atan2(-enemyPosition.y, -enemyPosition.x)) * 180 / (M_PI);

            // If relative, rotate towards hero
            // Movement in positive y direction.
            // 45 - 135 : no rotation
            // -45 - 45 : rotate towards positive x
            // -135 - -45 : rotate towards negative y
            // -180 - -135, 135 - 180 : rotate towards negative x
            if (angle >= 45 && angle < 135) {
                if (enemyPosition.x + move.movement.x != 0 || enemyPosition.y + move.movement.y != 0) {
                    enemyPosition += move.movement;
                }
            } else if (angle >= -45 && angle < 45) {
                if (enemyPosition.x + move.movement.rotation(3).x != 0 || enemyPosition.y + move.movement.rotation(3).y != 0) {
                    enemyPosition += move.movement.rotation(3);
                }
            } else if (angle >= -135 && angle < -45) {
                if (enemyPosition.x + move.movement.rotation(2).x != 0 || enemyPosition.y + move.movement.rotation(2).y != 0) {
                    enemyPosition += move.movement.rotation(2);
                }
            } else {
                if (enemyPosition.x + move.movement.rotation(1).x != 0 || enemyPosition.y + move.movement.rotation(1).y != 0) {
                    enemyPosition += move.movement.rotation(1);
                }
            }
            }
        break;
    }

    // Parse attack
    std::vector<threatenedTile> attack = move.attackShape;
    switch (move.attackType) {
        case ENEMY_ATTACK_TYPE::absolute:
            // Move attack shape to enemy position
            for (int i = 0; i < (int) attack.size(); i++) {
                attack[i] += enemyPosition;
            }
        break;

        case ENEMY_ATTACK_TYPE::relative:
            {
            // Rotate first, then move attack shape to enemy position

            // Calculate angle towards hero, in 90 degree buckets
            double angle = (std::atan2(-enemyPosition.y, -enemyPosition.x)) * 180 / (M_PI);

            // 45 - 135 : no rotation
            // -45 - 45 : rotate towards positive x
            // -135 - -45 : rotate towards negative y
            // -180 - -135, 135 - 180 : rotate towards negative x
            if (angle >= 45 && angle < 135) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i] += enemyPosition;
                }
            } else if (angle >= -45 && angle < 45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(3);
                    attack[i] += enemyPosition;
                }
            } else if (angle >= -135 && angle < -45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(2);
                    attack[i] += enemyPosition;
                }
            } else {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(1);
                    attack[i] += enemyPosition;
                }
            }
            }
        break;
        
        case ENEMY_ATTACK_TYPE::direct:
            {
            // Only rotate; hero is always at 0, 0

            // Calculate angle towards hero, in 90 degree buckets
            double angle = (std::atan2(-enemyPosition.y, -enemyPosition.x)) * 180 / (M_PI);

            // 45 - 135 : no rotation
            // -45 - 45 : rotate towards positive x
            // -135 - -45 : rotate towards negative y
            // -180 - -135, 135 - 180 : rotate towards negative x
            if (angle >= 45 && angle < 135) {
                // Do nothing
            } else if (angle >= -45 && angle < 45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(3);
                }
            } else if (angle >= -135 && angle < -45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(2);
                }
            } else {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(1);
                }
            }
            }
        break;

        case ENEMY_ATTACK_TYPE::ranged:
            {
            // First, do rotation and aim towards hero

            // Calculate angle towards hero, in 90 degree buckets
            double angle = (std::atan2(-enemyPosition.y, -enemyPosition.x)) * 180 / (M_PI);

            // 45 - 135 : no rotation
            // -45 - 45 : rotate towards positive x
            // -135 - -45 : rotate towards negative y
            // -180 - -135, 135 - 180 : rotate towards negative x
            if (angle >= 45 && angle < 135) {
                // Do nothing
            } else if (angle >= -45 && angle < 45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(3);
                }
            } else if (angle >= -135 && angle < -45) {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(2);
                }
            } else {
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i].rotate(1);
                }
            }

            // Calculate relative coordinates in the direction of the hero that corresponds to the limit of range
            // Get hypotenuse for exact distance between enemy and hero
            double hyp = sqrt(pow(-enemyPosition.x, 2) + pow(-enemyPosition.y, 2));

            // If exact distance less than range, then just put on top of hero.
            if (hyp > move.range) {
                // Get (exact) relative coordinates using similar triangle; new hypotenuse equal to max range
                double ratio = move.range/hyp;
                double x = ratio * (-enemyPosition.x);
                double y = ratio * (-enemyPosition.y);
                double finalx, finaly;
                double highestRange = 0;

                // Naive rounding; get all 4 combinations of rounding, and get the one with the highest distance but still within range
                if (sqrt(pow(floor(x), 2) + pow(floor(y), 2)) <= move.range && sqrt(pow(floor(x), 2) + pow(floor(y), 2)) > highestRange) {
                    highestRange = sqrt(pow(floor(x), 2) + pow(floor(y), 2));
                    finalx = floor(x);
                    finaly = floor(y);
                }
                if (sqrt(pow(floor(x), 2) + pow(ceil(y), 2)) <= move.range && sqrt(pow(floor(x), 2) + pow(ceil(y), 2)) > highestRange) {
                    highestRange = sqrt(pow(floor(x), 2) + pow(ceil(y), 2));
                    finalx = floor(x);
                    finaly = ceil(y);
                }
                if (sqrt(pow(ceil(x), 2) + pow(floor(y), 2)) <= move.range && sqrt(pow(ceil(x), 2) + pow(floor(y), 2)) > highestRange) {
                    highestRange = sqrt(pow(ceil(x), 2) + pow(floor(y), 2));
                    finalx = ceil(x);
                    finaly = floor(y);
                }
                if (sqrt(pow(ceil(x), 2) + pow(ceil(y), 2)) <= move.range && sqrt(pow(ceil(x), 2) + pow(ceil(y), 2)) > highestRange) {
                    highestRange = sqrt(pow(ceil(x), 2) + pow(ceil(y), 2));
                    finalx = ceil(x);
                    finaly = ceil(y);
                }

                // Place rotated attack on adjusted position
                coordinate attackPosition(finalx, finaly);
                attackPosition += enemyPosition;
                for (int i = 0; i < (int) attack.size(); i++) {
                    attack[i] += attackPosition;
                }
            }
            }
        break;
    }

    return attack;
}


std::unordered_map<std::string, enemy> enemies;