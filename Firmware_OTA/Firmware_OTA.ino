#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

// WiFi credentials
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

// URLs for fetching firmware version and firmware binary
const char* VERSION_URL = "";
const char* FIRMWARE_URL = "";

// Current firmware version
String currentFirmwareVersion = "1.1.1";

// Time tracking for periodic update checks
unsigned long lastUpdateCheckTime = 0;
const unsigned long UPDATE_CHECK_INTERVAL = 3600000 ; // Check every 1 hour

// Function to fetch the current version from the server
String fetchCurrentVersion() {
    HTTPClient http;
    http.begin(VERSION_URL);
    int httpResponseCode = http.GET();

    String version = "";
    if (httpResponseCode == HTTP_CODE_OK) {
        version = http.getString();
        version.trim();
        Serial.printf("Current Firmware Version: %s\n", version.c_str());
    } else {
        Serial.printf("Failed to fetch current version. HTTP Error: %d\n", httpResponseCode);
    }
    http.end();
    return version;
}

// Function to get the latest available firmware version
String fetchLatestVersion() {
    HTTPClient http;
    
    String requestUrl = String(VERSION_URL) + "?nocache=" + String(millis()); // Prevent caching
    http.begin(requestUrl);
    int httpResponseCode = http.GET();

    String latestVersion = "";
    if (httpResponseCode == HTTP_CODE_OK) {
        latestVersion = http.getString();
        latestVersion.trim();
    }
    http.end();
    return latestVersion;
}

// Function to perform OTA update
void performOTAUpdate() {
    Serial.println("Checking for firmware update...");
    t_httpUpdate_return updateStatus = ESPhttpUpdate.update(FIRMWARE_URL);

    switch (updateStatus) {
        case HTTP_UPDATE_FAILED:
            Serial.printf("Update failed, error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
            break;
        case HTTP_UPDATE_NO_UPDATES:
            Serial.println("No new update available.");
            break;
        case HTTP_UPDATE_OK:
            Serial.println("Update successful, rebooting...");
            delay(2000);
            ESP.restart();
            break;
    }
}

void setup() {
    Serial.begin(115200);
    
    // Connect to WiFi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi.");
    
    // Fetch and compare firmware versions
    Serial.println("Checking latest firmware version...");
    String latestVersion = fetchLatestVersion();
    
    if (!latestVersion.isEmpty() && latestVersion != currentFirmwareVersion) {
        Serial.printf("New firmware available. (Current: %s, Latest: %s)\n", currentFirmwareVersion.c_str(), latestVersion.c_str());
        performOTAUpdate();
    } else {
        Serial.println("Already running the latest firmware.");
    }
}

void loop() {
    // Periodic firmware update check
    if (millis() - lastUpdateCheckTime > UPDATE_CHECK_INTERVAL) {
        Serial.println("Performing scheduled update check...");
        lastUpdateCheckTime = millis();

        String latestVersion = fetchLatestVersion();
        if (!latestVersion.isEmpty() && latestVersion != currentFirmwareVersion) {
            Serial.printf("New firmware found! (Current: %s, Latest: %s)\n", currentFirmwareVersion.c_str(), latestVersion.c_str());
            performOTAUpdate();
            currentFirmwareVersion = latestVersion;
        } else {
            Serial.println("No new updates found.");
        }
    }
    delay(100);
}
