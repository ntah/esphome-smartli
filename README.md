# ESPHome Smartli External Component

Komponen ESPHome untuk membaca cell voltage secara efisien dari Modbus BMS menggunakan block read (array) dengan `modbus_controller`.


## Contoh Penggunaan YAML


external_components:
  - source: github://ntah/esphome-smartli

custom_component:
  - lambda: |-
      auto array0 = new ModbusCellArraySensor(id(bms0), 34, 15, 10000);
      App.register_component(array0);
      id(cell_array0) = array0;

sensor:
- platform: template
  name: "BMS 2 Cell 01 Voltage"
  lambda: |-
    return id(cell_array0).get_voltage(0);
  unit_of_measurement: "V"
  accuracy_decimals: 3
  device_class: voltage
  state_class: measurement
  update_interval: never
