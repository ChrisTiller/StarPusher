#include "../include/GameStateManager.h"

GameStateManager::GameStateManager(Game* game) 
    : changeHandler(std::bind(&GameStateManager::RequestChangeState, this, std::placeholders::_1, std::placeholders::_2)),
      popHandler(std::bind(&GameStateManager::RequestPopState, this, std::placeholders::_1)),
      pushHandler(std::bind(&GameStateManager::RequestPushState, this, std::placeholders::_1, std::placeholders::_2)) { 
        
    _game = game; 
};

//changeHandler([this](GameState* src, GameState* dst) { this->changeState(dst); }) 

void GameStateManager::RequestChangeState(GameState* src, GameState* dst) {
    changeState(dst);
}

void GameStateManager::RequestPopState(GameState* src) {
    popState();
}

void GameStateManager::RequestPushState(GameState* src, GameState* dest) {
    pushState(dest);
}

void GameStateManager::changeState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->RequestChangeState -= changeHandler;
        _states.back()->RequestPushState -= pushHandler;
        _states.back()->RequestPopState -= popHandler;
        _states.back()->cleanup();
        _states.pop_back();
    }

    _states.push_back(state);
    _states.back()->init(this);
    _states.back()->RequestChangeState += changeHandler;
    _states.back()->RequestPushState += pushHandler;
    _states.back()->RequestPopState += popHandler;
}

void GameStateManager::pushState(GameState* state) {

    if (!_states.empty()) {
        _states.back()->pause();
    }

    _states.push_back(state);
    _states.back()->init(this);
    _states.back()->RequestChangeState += changeHandler;
    _states.back()->RequestPushState += pushHandler;
    _states.back()->RequestPopState += popHandler;
}

void GameStateManager::popState() {

    if (!_states.empty()) {
        _states.back()->RequestChangeState -= changeHandler;
        _states.back()->RequestPushState -= pushHandler;
        _states.back()->RequestPopState -= popHandler;
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

    for(auto state : _states) {
        state->draw();
    }
}

Game& GameStateManager::getGame() {
    return (*_game);
}

void GameStateManager::cleanup() {

    while (!_states.empty() && _states.back()) {
        _states.back()->RequestChangeState -= changeHandler;
        _states.back()->RequestPushState -= pushHandler;
        _states.back()->RequestPopState -= popHandler;
        _states.back()->cleanup();
        _states.pop_back();
    }
}