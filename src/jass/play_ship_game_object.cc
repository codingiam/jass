#include "jass/play_ship_game_object.h"

#include "jass/video.h"

#include "jass/game_object.h"

#include "jass/mesh.h"

#include "jass/states_manager.h"
#include "jass/state_play.h"

namespace {
  int pnpoly(int npol, float *xp, float *yp, float x, float y) {
    int i, j, c = 0;
    for (i = 0, j = npol-1; i < npol; j = i++) {
      if ((((yp[i] <= y) && (y < yp[j])) ||
        ((yp[j] <= y) && (y < yp[i]))) &&
        (x < (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
        c = !c;
    }
    return c;
  }
}

namespace GameObjects {

  PlayShipGameObject::PlayShipGameObject(const GLfloat xpos, const GLfloat ypos, const Uint32 id, const GLfloat angle, std::array<Uint32, 6> const &keys) :
    ixpos_(xpos), iypos_(ypos), id_(id), iangle_(angle), keys_(keys) {
  }

  PlayShipGameObject::~PlayShipGameObject() {
    ship_.reset();
  }

  void PlayShipGameObject::Create() {
    this->ship_ = std::make_shared<Mesh>();
    ship_->LoadMeshObj("spaceship.obj", "data/obiecte/");
  }

  void PlayShipGameObject::Start() {
    this->xpos_ = ixpos_;
    this->ypos_ = iypos_;
    this->angle_ = iangle_;

    this->accel_ = 0.0f;
    this->speed_ = 0.0f;
    this->life_ = 1.0f;
    this->energy_ = 1.0f;

    this->last_time_ACC_ = 0;
    this->last_time_MOV_ = 0;
    this->last_time_ROT_ = 0;
    this->last_time_SHO_ = 0;

    this->ticks_ = 0;
  }

  void PlayShipGameObject::Update(const Uint32 dt, const Uint8 *keystate) {
    ticks_ += dt;

    if ((ticks_ - last_time_ACC_) > 150) {
      if (keystate[keys_[K_UP]]) {
        accel_ += 0.055f;
        if (accel_ > 1.0f) this->accel_ = 1.0f;
      }

      if (keystate[keys_[K_DOWN]]) {
        accel_ -= 0.055f;
        if (accel_ < -1.0f) this->accel_ = -1.0f;
      }

      if (accel_ < 0) {
        accel_ += 0.025f;
        if (accel_ > 0.0f) this->accel_ = 0.0f;
      }

      if (accel_ > 0) {
        accel_ -= 0.025f;
        if (accel_ < 0.0f) this->accel_ = 0.0f;
      }

      this->last_time_ACC_ = ticks_;
    }

    if ((ticks_ - last_time_ROT_) > 100) {
      if (keystate[keys_[K_LEFT]]) {
        angle_ += 10.0f;
      }

      if (keystate[keys_[K_RIGHT]]) {
        angle_ -= 10.0f;
      }

      if (angle_ > 360.0f) angle_ -= 360.0f;
      if (angle_ < 0.0f) angle_ += 360.0f;

      this->last_time_ROT_ = ticks_;
    }

    if ((ticks_ - last_time_SHO_) > 100) {
      if ((keystate[keys_[K_SHOOT]]) && (energy_ >= 0.15f)) {
        std::shared_ptr<StatePlay> play =
          std::static_pointer_cast<StatePlay>(State::Find(kStatePlay).lock());

        GLfloat amy = - cos(3.141516f * angle_ / 180);
        GLfloat amx = sin(3.141516f * angle_ / 180);

        play->AddProjectile(xpos_ + amx, ypos_ + amy, angle_, id_);

        energy_ -= 0.15f;
      }

      energy_ += 0.01f;
      if (energy_ > 1.0f) this->energy_ = 1.0f;

      this->last_time_SHO_ = ticks_;
    }

    Uint32 diff = ticks_ - last_time_MOV_;

    if (diff > 100) diff = 100;

    GLfloat amy = - cos(3.141516f * angle_ / 180);
    GLfloat amx = sin(3.141516f * angle_ / 180);

    ypos_ += accel_ * 0.25f * (diff / 100.f) * amy;
    xpos_ += accel_ * 0.25f * (diff / 100.f) * amx;

    if (xpos_ <= -5.8f) this->xpos_ = 5.75f;
    if (xpos_ >= 5.8f) this->xpos_ = -5.75f;

    if (ypos_ <= -4.5f) this->ypos_ = 4.45f;
    if (ypos_ >= 4.5f) this->ypos_ = -4.45f;

    if (diff > 100) {
      this->last_time_MOV_ = ticks_;
    }
  }

  void PlayShipGameObject::Render(Video *const video) {
    GL_CHECK(glPushMatrix());

    GL_CHECK(glTranslatef(xpos_, ypos_, -10.0f));
    GL_CHECK(glRotatef(90.0f, 1.0f, 0.0f, 0.0f));
    GL_CHECK(glRotatef(angle_, 0.0f, 1.0f, 0.0f));
    GL_CHECK(glScalef(0.035f, 0.035f, 0.035f));
    GL_CHECK(glColor4f(1.0f, 0.0f, 0.0f, 1.0f));
    
    ship_->Display();

    GL_CHECK(glPopMatrix());
  }

  bool PlayShipGameObject::Collide(const GLfloat x, const GLfloat y) {
    GLfloat ams = sin(3.141516f * angle_ / 180);
    GLfloat amc = cos(3.141516f * angle_ / 180);

    GLfloat xp[4], yp[4];

    xp[0] = xpos_ + (-0.40f) * amc - (0.55f) * ams;
    yp[0] = ypos_ + (-0.40f) * ams + (0.55f) * amc;

    xp[1] = xpos_ + (0.40f) * amc - (0.55f) * ams;
    yp[1] = ypos_ + (0.40f) * ams + (0.55f) * amc;

    xp[2] = xpos_ + (0.40f) * amc - (-0.55f) * ams;
    yp[2] = ypos_ + (0.40f) * ams + (-0.55f) * amc;

    xp[3] = xpos_ + (-0.40f) * amc - (-0.55f) * ams;
    yp[3] = ypos_ + (-0.40f) * ams + (-0.55f) * amc;


    bool hit = (pnpoly(4, xp, yp, x, y) == 1);
    if (hit) {
      life_ -= 0.10f;
      // std::cout << life << std::endl;
    }

    return hit;
  }

  const GLfloat PlayShipGameObject::GetLife() {
    return life_;
  }

}