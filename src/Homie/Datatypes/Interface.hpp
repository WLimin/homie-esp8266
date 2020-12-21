#pragma once

#include <AsyncMqttClient.h>
#include "../Logger.hpp"
#include "../Blinker.hpp"
#include "../Constants.hpp"
#include "../Config.hpp"
#include "../Limits.hpp"
#include "./Callbacks.hpp"
#include "../../HomieBootMode.hpp"
#include "../../HomieNode.hpp"
#include "../../SendingPromise.hpp"
#include "../../HomieEvent.hpp"

namespace HomieInternals {
class Logger;
class Blinker;
class Config;
class SendingPromise;
class HomieClass;

class InterfaceData;
using InterfaceDataPtr = std::shared_ptr<InterfaceData>;

class InterfaceData :  public std::enable_shared_from_this<InterfaceData> {
  friend HomieClass;

 public:
    static InterfaceDataPtr getInstance() {
        static InterfaceDataPtr m_inst = InterfaceDataPtr(new InterfaceData());
        return m_inst;
    }
    InterfaceData(const InterfaceData&) = delete;
    InterfaceData& operator=(const InterfaceData&) = delete;

  /***** User configurable data *****/
  char brand[MAX_BRAND_LENGTH];

  HomieBootMode bootMode;

  struct ConfigurationAP {
    bool secured;
    char password[MAX_WIFI_PASSWORD_LENGTH];
  } configurationAp;

  struct Firmware {
    char name[MAX_FIRMWARE_NAME_LENGTH];
    char version[MAX_FIRMWARE_VERSION_LENGTH];
  } firmware;

  struct LED {
    bool enabled;
    uint8_t pin;
    uint8_t on;
  } led;

  struct Reset {
    bool enabled;
    bool idle;
    uint8_t triggerPin;
    uint8_t triggerState;
    uint16_t triggerTime;
    bool resetFlag;
  } reset;

  bool disable;
  bool flaggedForSleep;

  GlobalInputHandler globalInputHandler;
  BroadcastHandler broadcastHandler;
  OperationFunction setupFunction;
  OperationFunction loopFunction;
  EventHandler eventHandler;

  /***** Runtime data *****/
  HomieEvent event;
  bool ready;
  Logger& getLogger() { return *_logger; }
  Blinker& getBlinker() { return *_blinker; }
  Config& getConfig() { return *_config; }
  AsyncMqttClient& getMqttClient() { return *_mqttClient; }
  SendingPromise& getSendingPromise() { return *_sendingPromise; }

 private:
  InterfaceData();
  Logger* _logger;
  Blinker* _blinker;
  Config* _config;
  AsyncMqttClient* _mqttClient;
  SendingPromise* _sendingPromise;
};
namespace Interface {
    extern  InterfaceData& get();
}
}  // namespace HomieInternals
