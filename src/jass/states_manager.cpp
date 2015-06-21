#include "states_manager.h"

#include "jass/state.h"

#include "jass/state_introduction.h"
#include "jass/state_play.h"

StatesManager::StatesManager() {
}


StatesManager::~StatesManager() {
}

void StatesManager::Initialize() {
  this->state_intro_ = boost::shared_ptr<StateIntro>(new StateIntro);
  this->state_play_ = boost::shared_ptr<StatePlay>(new StatePlay); 

  State::Register(kStateIntro, state_intro_);
  State::Register(kStatePlay, state_play_);

  State::set_state(state_intro_.get());
  State::Update();
}

void StatesManager::ShutDown() {
  State::Unregister(kStatePlay);
  State::Unregister(kStateIntro);
}
