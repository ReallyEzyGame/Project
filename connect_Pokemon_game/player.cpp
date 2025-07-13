#include "player.h"

// Each time Earse a Pair, get 10 points
void Player::UpdateScore() {
    score += __SCORE;
}

void Player::RefreshScore() {
    score = 0;
}

void Player::Rename() {
    cin  >>  name;
}