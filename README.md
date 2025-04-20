# ESP32-Over-the-Air-OTA-Update-via-HTTP


## Overview
This project enables OTA (Over-the-Air) updates for an ESP32 using HTTP. The ESP32 periodically checks for firmware updates hosted on a server (e.g. GitHub) and updates itself when a new version is available.


## Features
* Wi-Fi Connectivity: Connects to a specified Wi-Fi network.
* Firmware Version Checking: Fetches the latest version number from a remote server.
* OTA Update Process: Downloads and installs new firmware if an update is detected.
* Automatic Reboot: Restarts ESP32 after a successful update.
* Periodic Update Checks: Every 30 seconds, it checks for updates.


## Hardware Requirements
* ESP32 development board
* Internet access via Wi-Fi

## Software Requirements
* Arduino IDE with ESP32 board support installed
* Required libraries:
   * #include <WiFi.h>
   * #include <HTTPClient.h>
   * #include <ESP32httpUpdate.h>
* A web server (or GitHub) to host :
   * firmware_version.txt (containing the latest version number)
   * Firmware_OTA.bin (compiled firmware file)
 
# Setup Instructions
1. Configure Wi-Fi Credentials
   * const char* username = "Your_SSID";
   * const char* password = "Your_PASSWORD";
  
2. Host Firmware Files
   * Upload your firmware binary (.bin) file and version file (firmware_version.txt) to a web server or GitHub repository
   * Update the URLs in the code :
     * const char* version_url = "https://your_server/firmware_version.txt";
     * const char* firmware_url = "https://your_server/Firmware_OTA.bin";

3. Upload the Initial Firmware
   * Compile and upload the sketch to your ESP32 using Arduino IDE.
   * Open Serial Monitor (115200 baud) to verify the update process.

4. Perform an OTA Update
   * Change the version number in firmware_version.txt (e.g., from 1.1.1 to 1.1.2).
   * Upload a new .bin firmware file to your server.
   * The ESP32 will detect the update and install it.
  
5. Code Breakdown
   * Wi-Fi Connection
     * ![image](https://github.com/user-attachments/assets/d4b4a84d-e387-4585-891c-8caecf8c5a60)

   * Checking for Updates
     * ![image](https://github.com/user-attachments/assets/938934b2-f32f-44cc-88bc-3708bbd6dc31)

   * Performing OTA Update
     * ![image](https://github.com/user-attachments/assets/4ceeee1f-9355-4528-80b3-bff3eceb3b6e)

    
## Expected Behavior
* ESP32 connects to Wi-Fi.
* It fetches the latest firmware version from the server.
* If a new version is found, it downloads and installs the update.
* The ESP32 restarts and runs the updated firmware.
* If no update is found, it prints "Already running the latest firmware".
* The ESP32 checks for updates every 30 seconds.


## Notes
* Ensure firmware_version.txt contains only the version number (e.g., 1.1.1).
* Make sure the .bin file is properly uploaded and accessible.


# License
This project is open-source. Feel free to modify and improve it!


  


