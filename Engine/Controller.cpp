#include "Controller.h"

Controller::Controller() {

}
Controller::Controller(Controller& from) {

}
Controller::~Controller() {
}
const Rtti& Controller::GetType() const { return Type; }
const Rtti Controller::Type("Controller", &Object::Type, sizeof(Controller));