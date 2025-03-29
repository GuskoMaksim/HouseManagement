#include "ManagerTX.h"

void ManagerTX::Update() {
  if (dataSensor_ != nullptr) {
    SendingData data;
    for (int i = 0; i < dataSensor_->GetDataFromSensors().getSize(); ++i) {
      data.idDevice_ = idDevice_;
      data.messageType_ = MessageType::Data;
      auto variantData = dataSensor_->GetDataFromSensors().get(i);
      data.typeOfSensorData_ = variantData.getSensorDataType();
      data.typeOfValue_ = variantData.getValueType();
      data.setDataFromVariant(data, variantData);
      data.pass_ = 2512;
      data.CRC_ = data.calcCRC(variantData);
      tx_.sendData(data);
      delay(400);
    }
  }
}

void ManagerTX::AddManagerSensor(ManagerSensor *data) { dataSensor_ = data; };

void ManagerTX::Init() {}
