#include "AUTO_PARSE.h"
#include <Arduino.h>



AUTO_PARSE::AUTO_PARSE(int count) {
  KEY_COUNT = count;
  KEY = new String[KEY_COUNT];

  debug("AUTO_PARSE initialized with " + String(KEY_COUNT) + " keys.");
}
void AUTO_PARSE::setKeyName(String baseName[]) {
  for (int i = 0; i < KEY_COUNT; i++) {
    KEY[i] = baseName[i];
    debug("Key " + String(i) + " set to: " + KEY[i]);
  }
  
}
void AUTO_PARSE::setParseChars(char chars) {
  CHARS = chars;

  debug("Parse character set to: " + String(CHARS));
}
void AUTO_PARSE::parseString(String data) {
  startIndex = 0;
  endIndex = 0;
  currentIndex = 0;
  part = "";

  debug("Parsing string: " + data);

  // Uzunluk kontrolü etkinse, kontrol yap
  if (ENABLE_LENGTH_CHECK) {
    if (data.length() == STRING_LENGTH) {
      debug("Length check passed. Length: " + String(data.length()));

      for (int i = 0; i <= data.length(); i++) {
        if (data[i] == CHARS || i == data.length()) {
          endIndex = i;
          part = data.substring(startIndex, endIndex);

          debug("Extracted part: " + part);

          if (currentIndex < KEY_COUNT) {
            PARSE_DATA[KEY[currentIndex]] = part;
            debug("Key: " + KEY[currentIndex] + ", Value: " + part);
          }
          currentIndex++;
          startIndex = i + 1;
        }
      }
    } else {
      debug("Length check failed. Expected: " + String(STRING_LENGTH) + ", Got: " + String(data.length()));
      return;  // Uzunluk hatalıysa işlemi sonlandır
    }
  } else {
    debug("Length check disabled. Proceeding with parsing.");

    for (int i = 0; i <= data.length(); i++) {
      if (data[i] == CHARS || i == data.length()) {
        endIndex = i;
        part = data.substring(startIndex, endIndex);

        debug("Extracted part: " + part);

        if (currentIndex < KEY_COUNT) {
          PARSE_DATA[KEY[currentIndex]] = part;
          debug("Key: " + KEY[currentIndex] + ", Value: " + part);
        }
        currentIndex++;
        startIndex = i + 1;
      }
    }
  }

  debug("Parsing completed.");
}
void AUTO_PARSE::setLengthString(int length) {
  STRING_LENGTH = length;
  debug("String length set to: " + String(STRING_LENGTH));
}
void AUTO_PARSE::enableLengthCheck() {
  ENABLE_LENGTH_CHECK = true;
  debug("Length check enabled.");
}
void AUTO_PARSE::disableLengthCheck() {
  ENABLE_LENGTH_CHECK = false;
  debug("Length check disabled.");
}
void AUTO_PARSE::disableDEBUG() {
  DEBUG = false;
  debug("DEBUG mode disabled.");  // DEBUG kapatılmadan önce mesaj yazdırılır
}
void AUTO_PARSE::enableDEBUG() {
  DEBUG = true;
  debug("DEBUG mode enabled.");
}
void AUTO_PARSE::debug(String message) {
  if (DEBUG) {
    Serial.println("[DEBUG] " + message);
  }
}
String AUTO_PARSE::getValue(String key) {
  if (PARSE_DATA.find(key) != PARSE_DATA.end()) {
    debug("Key found: " + key + ", Value: " + PARSE_DATA[key]);
    return PARSE_DATA[key];
  } else {
    debug("Key not found: " + key);
    return "NULL";
  }
}
void AUTO_PARSE::info() {
  Serial.println("=== AUTO_PARSE Info ===");
    Serial.println("Key Count: " + String(KEY_COUNT));
  for (int i = 0; i < KEY_COUNT; i++) {
    Serial.println("Key " + String(i) + ": " + KEY[i]);
  }
  Serial.println("Parse Character: " + String(CHARS));
  Serial.println("String Length: " + String(STRING_LENGTH));
  Serial.println("Length Check Enabled: " + String(ENABLE_LENGTH_CHECK ? "Yes" : "No"));
  Serial.println("DEBUG Mode: " + String(DEBUG ? "Enabled" : "Disabled"));
  Serial.println("Parsed Data:");
  for (auto const &entry : PARSE_DATA) {
    Serial.println("  Key: " + entry.first + ", Value: " + entry.second);
  }
  Serial.println("========================");
}