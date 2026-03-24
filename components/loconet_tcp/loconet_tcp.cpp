#include "loconet_tcp.h"
#include "esphome/core/log.h"

namespace loconet_tcp {

static const char *TAG = "loconet_tcp";

LocoNetTCP::LocoNetTCP(std::string host, uint16_t port)
    : host_(host), port_(port) {}

void LocoNetTCP::setup() {
  connect_();
}

void LocoNetTCP::loop() {
  if (!client_.connected()) {
    ESP_LOGW(TAG, "Disconnected. Reconnecting...");
    connect_();
    return;
  }

  while (client_.available()) {
    char c = client_.read();
    buffer_ += c;

    if (buffer_.size() >= 2 &&
        buffer_.substr(buffer_.size() - 2) == "\r\n") {

      std::string line = buffer_.substr(0, buffer_.size() - 2);
      buffer_.clear();

      ESP_LOGD(TAG, "Received: %s", line.c_str());
      handle_line_(line);
    }
  }
}

void LocoNetTCP::connect_() {
  ESP_LOGI(TAG, "Connecting to %s:%d", host_.c_str(), port_);
  client_.connect(host_.c_str(), port_);
}

void LocoNetTCP::send(std::string msg) {
  if (client_.connected()) {
    client_.print(msg.c_str());
    client_.print("\r\n");
  } else {
    ESP_LOGW(TAG, "Send failed, not connected");
  }
}

void LocoNetTCP::handle_line_(const std::string &line) {
  if (line.rfind("RECEIVE", 0) == 0) {
    if (receive_trigger_ != nullptr)
      receive_trigger_->trigger(line);
  } else if (line.rfind("SENT OK", 0) == 0) {
    if (sent_ok_trigger_ != nullptr)
      sent_ok_trigger_->trigger(line);
  }
}

}  // namespace loconet_tcp