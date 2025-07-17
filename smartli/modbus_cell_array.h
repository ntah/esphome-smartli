#include "esphome.h"
#include "modbus_controller.h"

using namespace esphome;
using namespace esphome::modbus_controller;

class ModbusCellArraySensor : public PollingComponent, public Sensor {
 public:
  ModbusCellArraySensor(ModbusController *controller, uint16_t start_address, uint8_t count)
      : controller_(controller), start_address_(start_address), count_(count) {
    cell_voltages_.resize(count_);
  }

  void setup() override {}

  void update() override {
    controller_->queue_command(
        ModbusCommandItem::create_read_holding_registers(
            controller_->id(), start_address_, count_,
            [this](std::vector<uint8_t> &data) {
              for (int i = 0; i < count_; i++) {
                uint16_t raw = encode_uint16(data[2 * i], data[2 * i + 1]);
                cell_voltages_[i] = raw * 0.001f;  // mV to V
              }
            }));
  }

  float get_voltage(uint8_t index) {
    if (index >= cell_voltages_.size()) return NAN;
    return cell_voltages_[index];
  }

 protected:
  ModbusController *controller_;
  uint16_t start_address_;
  uint8_t count_;
  std::vector<float> cell_voltages_;
};
