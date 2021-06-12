#include "../include/GameStateManager.h"
#include "../include/GameState.h"



void GameStateManager::changeState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->cleanup();
        _states.pop_back();
    }

    _states.push_back(state);
    _states.back()->init(_game);

}

void GameStateManager::pushState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->pause();
    }

    _states.push_back(state);
    _states.back()->init(_game);

}

void GameStateManager::popState() {

    if (!_states.empty()) {
        _states.back()->cleanup();
        _states.pop_back();
    }

    if (!_states.empty()) {
        _states.back()->resume();
    }

}

void GameStateManager::handleEvents(SDL_Event& event) {

    _states.back()->handleEvents(event);

}

void GameStateManager::update() {

    _states.back()->update();

}

void GameStateManager::draw() {

    _states.back()->draw();

}

void GameStateManager::setGame(Game* game) {
    _game = game;
}