#pragma once

#include "esphome/core/component.h"

# Namespace definition
namespace esphome {
namespace my_external_component {

class MyExternalComponent : public Component {

 public:
     // Constructor
     MyExternalComponent();
    
     // Configuration function
     void set_conf_x(float conf_x);
    
     // Standard component functions to override
     void setup() override;
     void dump_config() override;
    
    protected:
    # Internal fields definition
    float conf_x_;
};

}  // namespace cc1101
}  // namespace esphome