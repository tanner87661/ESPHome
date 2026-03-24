#include "esphome/core/log.h"
#include "my_external_component.h"

namespace esphome {
namespace my_external_component {

static const char *const TAG = "MyExternalComponent";

MyExternalComponent::MyExternalComponent() {
    // Constructor
}

void MyExternalComponent::set_conf_x(float conf_x) { conf_x_ = conf_x; }

void MyExternalComponent::setup() {
    // Setup code
}

void CC1101::dump_config() {
    ESP_LOGCONFIG(TAG, "MyExternalComponent:");
    LOG_PIN("  Conf X:  ", this->conf_x_);
}

}  // namespace my_external_component
}  // namespace esphome