#include "standardEnemies.h"
#include "enemy.h"

void initStandardEnemies() {
    moveGroup moveGroupBuilder;
    std::vector<threatenedTile> attackShapeBuilder;

    // lvl 1

    // Slime
    // 1: Tackle
    // 2: Roll -> Splatter
    // 3: Spit
    enemies.emplace("slime", enemy("Slime", 3));
    // 1
    attackShapeBuilder.emplace_back(0, 1, DAMAGE_TYPE::physical);
    moveGroupBuilder.addMove(enemyMove("Tackle", coordinate(0, 1), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::relative));
    attackShapeBuilder.clear();
    enemies.at("slime").addMoveGroup(moveGroupBuilder);
    moveGroupBuilder.clear();
    // 2
    moveGroupBuilder.addMove(enemyMove("Roll", coordinate(0, 2), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::direct));
    attackShapeBuilder.emplace_back(0, 1, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(1, 0, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(0, -1, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(-1, 0, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(1, 1, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(1, -1, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(-1, -1, DAMAGE_TYPE::chemical);
    attackShapeBuilder.emplace_back(-1, 1, DAMAGE_TYPE::chemical);
    moveGroupBuilder.addMove(enemyMove("Splatter", coordinate(0, 0), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::absolute));
    attackShapeBuilder.clear();
    enemies.at("slime").addMoveGroup(moveGroupBuilder);
    moveGroupBuilder.clear();
    // 3
    attackShapeBuilder.emplace_back(0, 0, DAMAGE_TYPE::chemical);
    moveGroupBuilder.addMove(enemyMove("Spit", coordinate(0, 0), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::ranged, 2));
    attackShapeBuilder.clear();
    enemies.at("slime").addMoveGroup(moveGroupBuilder);
    moveGroupBuilder.clear();

    // Goblin
    // 1: Stab
    // 2: Scurry -> Throw Rock
    enemies.emplace("goblin", enemy("Goblin", 2));
    // 1
    attackShapeBuilder.emplace_back(0, 1, DAMAGE_TYPE::physical);
    moveGroupBuilder.addMove(enemyMove("Stab", coordinate(0, 2), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::relative));
    attackShapeBuilder.clear();
    enemies.at("goblin").addMoveGroup(moveGroupBuilder);
    moveGroupBuilder.clear();
    // 2
    moveGroupBuilder.addMove(enemyMove("Scurry", coordinate(0, -2), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::direct));
    attackShapeBuilder.emplace_back(0, 0, DAMAGE_TYPE::physical);
    moveGroupBuilder.addMove(enemyMove("Throw Rock", coordinate(0, 0), ENEMY_MOVEMENT_DIRECTION::relative, attackShapeBuilder, ENEMY_ATTACK_TYPE::ranged, 3));
    attackShapeBuilder.clear();
    enemies.at("goblin").addMoveGroup(moveGroupBuilder);
    moveGroupBuilder.clear();
}