#ifndef AUTO_PARSE_H
#define AUTO_PARSE_H
#include <Arduino.h>
#include <map>

struct Part {
  String name;
  String value;
};

class AUTO_PARSE {
public:
  AUTO_PARSE(int Count);
  void setKeyName(String key[]);
  void setParseChars(char chars);
  void parseString(String data);
  void setLengthString(int length);
  void enableLengthCheck();
  void disableLengthCheck();
  void disableDEBUG();
  void enableDEBUG();
  void debug(String message);
  void info();
  String getValue(String key);





private:
  std::map<String, String> PARSE_DATA;
  String* KEY; 
  char CHARS= '-';
  String part;
  int startIndex = 0;
  int endIndex = 0;
  int currentIndex = 0;
  int KEY_COUNT = 0;
  int STRING_LENGTH = 0;
  bool ENABLE_LENGTH_CHECK =false;
  bool DEBUG = false;
};

#endif
