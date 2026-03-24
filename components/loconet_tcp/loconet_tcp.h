#pragma once

#include "esphome.h"
#include <ESP8266WiFi.h>

namespace loconet_tcp {

class LocoNetTCP;

class ReceiveTrigger : public Trigger<std::string> {
 public:
  ReceiveTrigger(LocoNetTCP *parent) { parent->set_receive_trigger(this); }
};

class SentOkTrigger : public Trigger<std::string> {
 public:
  SentOkTrigger(LocoNetTCP *parent) { parent->set_sent_ok_trigger(this); }
};

class LocoNetTCP : public Component {
 public:
  LocoNetTCP(std::string host, uint16_t port);

  void setup() override;
  void loop() override;

  void send(std::string msg);

  void set_receive_trigger(ReceiveTrigger *t) { receive_trigger_ = t; }
  void set_sent_ok_trigger(SentOkTrigger *t) { sent_ok_trigger_ = t; }

 protected:
  void connect_();
  void handle_line_(const std::string &line);

  std::string host_;
  uint16_t port_;
  WiFiClient client_;
  std::string buffer_;

  ReceiveTrigger *receive_trigger_{nullptr};
  SentOkTrigger *sent_ok_trigger_{nullptr};
};

}  // namespace loconet_tcp