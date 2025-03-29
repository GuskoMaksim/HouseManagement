#pragma once
#include <Gyver433.h>

#include <List.hpp>

#include "Variant.h"

template <uint8_t RX_PIN = 4, uint16_t RX_BUF = 12>
class ManagerRX {
 private:
  struct StoredDate {
    uint32_t lastGet;
    uint8_t idDevice;
    MessageType messageType;
    Variant data;
  };
  struct ReceivedData {
    uint8_t idDevice_;
    MessageType messageType_;
    ValueType typeOfValue_;
    SensorDataType typeOfSensorData_;
    Value value_;
    uint16_t CRC_;
    uint16_t pass_;
    uint16_t getHash(uint16_t data, int length) {
      uint16_t hash = 0;
      int i = 0;
      while (length--) {
        hash += data + i;
        i++;
      }
      return hash;
    }
    uint16_t calcCRC(ReceivedData& receivedData) {
      uint16_t CRC = 0;
      CRC += getHash(static_cast<uint16_t>(idDevice_), sizeof(idDevice_));
      CRC += getHash(static_cast<uint16_t>(messageType_), sizeof(messageType_));
      CRC += getHash(static_cast<uint16_t>(typeOfSensorData_), sizeof(typeOfSensorData_));
      CRC += getHash(static_cast<uint16_t>(typeOfValue_), sizeof(typeOfValue_));
      CRC += getHash(static_cast<uint16_t>(pass_), sizeof(pass_));
      switch (receivedData.typeOfValue_) {
        case ValueType::Bool:
          CRC += getHash(static_cast<uint16_t>(receivedData.value_.bool_value), sizeof(bool));
          break;
        case ValueType::Float:
          CRC += getHash(static_cast<uint16_t>(receivedData.value_.float_value), sizeof(float));
          break;
        case ValueType::Int32_t:
          CRC += getHash(static_cast<uint16_t>(receivedData.value_.int32_value), sizeof(uint16_t));
          break;
        default:
          static_assert("ERROR get value_ from Variant");
          break;
      }
      return CRC;
    }
    void setVariantFromData(StoredDate* data, ReceivedData& receivedData) {
      switch (receivedData.typeOfValue_) {
        case ValueType::Bool:
          data->data.setValue(receivedData.value_.bool_value);
          break;
        case ValueType::Float:
          data->data.setValue(receivedData.value_.float_value);
          break;
        case ValueType::Int32_t:
          data->data.setValue(receivedData.value_.int32_value);
          break;
        default:
          static_assert("ERROR get value_ from Variant");
          break;
      }
    }
  };

  uint32_t maxTimeBetweenRetrieval_ = 3600000;
  Gyver433_RX<RX_PIN, RX_BUF> rx;
  // delete
  const uint32_t refresh_send_ms = 10000;
  uint32_t send_update_ms = refresh_send_ms + 1;
  //
  uint16_t getHash(uint16_t data, int length) {
    uint16_t hash = 0;
    int i = 0;
    while (length--) {
      hash += data + i;
      i++;
    }
    return hash;
  }

 public:
  List<StoredDate*> storedDate_;
  void Update();
  void setMaxTimeBetweenRetrieval(uint32_t hour);
  ~ManagerRX() = default;
};

template <uint8_t RX_PIN, uint16_t RX_BUF>
void ManagerRX<RX_PIN, RX_BUF>::Update() {
  if (rx.tick()) {
    ReceivedData data;
    if (rx.readData(data)) {
      bool find = false;
      if (data.calcCRC(data) != data.CRC_) {
        Serial.print("Error");
      } else {
        StoredDate* sdNew = nullptr;
        for (int i = 0; i < storedDate_.getSize(); ++i) {
          sdNew = storedDate_.getValue(i);
          if (sdNew->idDevice == data.idDevice_ && sdNew->messageType == data.messageType_ &&
              sdNew->data.typeOfSensorData == data.typeOfSensorData_) {
            find = true;
            break;
          }
        }
        if (!find) {
          sdNew = new StoredDate();
          sdNew->idDevice = data.idDevice_;
          sdNew->messageType = data.messageType_;
          sdNew->data.setSensorDataType(data.typeOfSensorData_);
          sdNew->data.setValueType(data.typeOfValue_);
          sdNew->lastGet = millis();
          storedDate_.add(sdNew);
        }
        data.setVariantFromData(sdNew, data);
        ////////////////////////////////////////DELETE
        // Serial.print("data.pass: ");
        // Serial.println(data.pass_);
        // Serial.print("CRC: ");
        // Serial.println(data.calcCRC(data));
        // Serial.print("data.CRC: ");
        // Serial.println(data.CRC_);
        // Serial.print("sdNew.idDevice: ");
        // Serial.println(sdNew->idDevice);
        // Serial.print("sdNew->messageType: ");
        // Serial.println((uint8_t)sdNew->messageType);
        // Serial.print("sdNew->v.typeOfValue: ");
        // Serial.println((uint8_t)sdNew->data.typeOfValue);
        // Serial.print("sdNew->data.typeOfSensorData: ");
        // Serial.println((uint8_t)sdNew->data.typeOfSensorData);
        // Serial.print("sdNew->v.getValue: ");
        // // Serial.println(sdNew->data.getValue<float>());
        // Serial.print("sdNew->lastGet: ");
        // Serial.println(sdNew->lastGet);
        // Serial.println("-------------------------------");
        // Serial.println();
        ////////////////////////////////////////////
      }
    } else
      Serial.println("Data error");
  }
  // delete
  // if (millis() - send_update_ms > refresh_send_ms) {
  //     send_update_ms = millis();
  //     Serial.print("Size: ");
  //     Serial.println(storedDate_.getSize());
  //     Serial.println("-----------------------");
  //     Serial.println();
  // }
  //
};

template <uint8_t RX_PIN, uint16_t RX_BUF>
void ManagerRX<RX_PIN, RX_BUF>::setMaxTimeBetweenRetrieval(uint32_t mins) {
  maxTimeBetweenRetrieval_ = uint32_t(mins);
};
