# Bluetooth Integration Guide

This document describes the bluetooth integration implemented in the waveshare-ui-basic project.

## Overview

The UI has been connected to bluetooth functions to enable wireless control of various features including mute, push-to-talk (PTT), and status display.

## UI Elements Connected to Bluetooth

### 1. Mute Button (`ui_Mute_Button`)
- **Location**: Main screen, center aligned
- **Type**: Button (100x50 pixels)
- **Event Handler**: `MuteButton(lv_event_t * e)`
- **Bluetooth Function**: `ble_mute_from_ui()`
- **Behavior**: When the mute button is pressed, it calls the bluetooth mute function

### 2. PTT Switch (`ui_PTT`)
- **Location**: Main screen (x:6, y:128)
- **Type**: Switch (50x25 pixels)
- **Label**: "PTT"
- **Event Handler**: `on_ptt_switch_changed(lv_event_t * e)`
- **Bluetooth Function**: `ble_ptt_from_ui(int state)`
- **Behavior**: 
  - When switch is ON (checked): sends state=1 via bluetooth
  - When switch is OFF (unchecked): sends state=0 via bluetooth

### 3. Bluetooth Status Label (`ui_uiBluetoothStatusLabel`)
- **Location**: Main screen (x:-46, y:-135)
- **Type**: Label
- **Event Handler**: `ui_BluetoothStatusLabel(lv_event_t * e)`
- **Bluetooth Function**: `ble_update_status_ui()`
- **Behavior**: Updates the bluetooth connection status display

## Bluetooth Functions

### `void ble_mute_from_ui(void)`
**Purpose**: Send mute command via Bluetooth

**Called from**: MuteButton event handler

**TODO**: Implement actual BLE communication to send mute command to connected device

**Example Implementation**:
```cpp
void ble_mute_from_ui(void)
{
    // Send mute command via BLE
    if (ble_is_connected()) {
        ble_send_command(BLE_CMD_MUTE);
    }
}
```

### `void ble_ptt_from_ui(int state)`
**Purpose**: Send PTT (Push-to-Talk) state via Bluetooth

**Called from**: on_ptt_switch_changed event handler

**Parameters**: 
- `state`: 1 for PTT active (pushed), 0 for PTT inactive (released)

**TODO**: Implement actual BLE communication to send PTT state to connected device

**Example Implementation**:
```cpp
void ble_ptt_from_ui(int state)
{
    // Send PTT state via BLE
    if (ble_is_connected()) {
        ble_send_command(state ? BLE_CMD_PTT_ON : BLE_CMD_PTT_OFF);
    }
}
```

### `void ble_update_status_ui(void)`
**Purpose**: Update the bluetooth status display in the UI

**Called from**: ui_BluetoothStatusLabel event handler

**TODO**: Implement BLE status reading and UI label update

**Example Implementation**:
```cpp
void ble_update_status_ui(void)
{
    // Update bluetooth status label
    if (ble_is_connected()) {
        lv_label_set_text(ui_uiBluetoothStatusLabel, "BLE: Connected");
    } else {
        lv_label_set_text(ui_uiBluetoothStatusLabel, "BLE: Disconnected");
    }
}
```

## Integration Steps for BLE Implementation

To complete the bluetooth integration, you need to:

1. **Add BLE Library**: Include the appropriate ESP32 BLE library in your project
   ```cpp
   #include <BLEDevice.h>
   #include <BLEServer.h>
   #include <BLEUtils.h>
   ```

2. **Initialize BLE**: Set up BLE in your setup() function
   ```cpp
   void setup() {
       // ... existing setup code ...
       
       // Initialize BLE
       BLEDevice::init("Waveshare Remote");
       // Configure BLE server, services, characteristics
   }
   ```

3. **Implement BLE Functions**: Replace the stub implementations in ui_events.cpp with actual BLE communication code

4. **Handle BLE Events**: Add callbacks to update UI when BLE connection status changes

## File Locations

- **Header**: `ui_events.h` - Contains bluetooth function declarations
- **Implementation**: `ui_events.cpp` - Contains bluetooth function implementations
- **UI Definition**: `ui_Main.c` - Contains UI element definitions and event bindings

## Notes

- All bluetooth functions use `extern "C"` linkage for compatibility with C code
- The stub implementations are ready to be filled in with actual BLE communication code
- Make sure to test BLE functionality thoroughly before deploying to production
