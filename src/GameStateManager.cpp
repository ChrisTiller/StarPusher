#include "../include/GameStateManager.h"

GameStateManager::GameStateManager(Game* game) 
    : changeHandler(std::bind(&GameStateManager::RequestChangeState, this, std::placeholders::_1, std::placeholders::_2)) { 
        
    _game = game; 
};

//changeHandler([this](GameState* src, GameState* dst) { this->changeState(dst); }) 

void GameStateManager::RequestChangeState(GameState* src, GameState* dst) {
    changeState(dst);
}

void GameStateManager::changeState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->RequestChangeState -= changeHandler;
        _states.back()->cleanup();
        _states.pop_back();
    }

    _states.push_back(state);
    _states.back()->init(this);
    _states.back()->RequestChangeState += changeHandler;
}

void GameStateManager::pushState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->pause();
    }

    _states.push_back(state);
    _states.back()->init(this);
    _states.back()->RequestChangeState += changeHandler;
}

void GameStateManager::popState() {

    if (!_states.empty()) {
        _states.back()->RequestChangeState -= changeHandler;
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

Game& GameStateManager::getGame() {
    return (*_game);
}

void GameStateManager::cleanup() {

    while (!_states.empty() && _states.back()) {
        _states.back()->cleanup();
        _states.pop_back();
    }
}