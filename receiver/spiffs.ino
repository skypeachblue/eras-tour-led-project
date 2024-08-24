// from https://github.com/crankyoldgit/IRremoteESP8266/blob/master/src/IRutils.cpp#L66
String uint64_to_string(uint64_t input) {
  String result = "";
  uint8_t base = 10;

  do {
    char c = input % base;
    input /= base;

    if (c < 10)
      c +='0';
    else
      c += 'A' - 10;
    result = c + result;
  } while (input);

  return result;
}

int get_num_of_files(fs::FS &fs, const char * path) {
  File root = fs.open(path);
  if(!root || !root.isDirectory()){
      return -1;
  }

  int num = 0;
  File file;
  while (file = root.openNextFile()) {
    num++;
    file.close();
  }
  root.close();
  return num;
}

bool list_dir(fs::FS &fs, const char * path) {
  File root = fs.open(path);
  if(!root || !root.isDirectory()){
      return false;
  }

  File file = root.openNextFile();
  while(file) {
    if (file.isDirectory()) {
      Serial.printf("DIR: %s\n", file.name());
    } else {
      Serial.printf("FILE: %s SIZE: %d\n", file.name(), file.size());
    }
    file.close();
    file = root.openNextFile();
  }
  root.close();
  return true;
}

bool create_file(fs::FS &fs, const char * path) {
  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    return false;
  } else {
    file.close();
    return true;
  }
}

bool delete_file(fs::FS &fs, const char * path) {
  if (fs.remove(path)) {
    return true;
  } else {
    return false;
  }
}

bool delete_all_files(fs::FS &fs, const char * path) {
  File root = fs.open(path);
  if(!root || !root.isDirectory()){
      return false;
  }

  File file = root.openNextFile();
  while(file) {
    String name = file.name();
    Serial.printf("Deleting %s\n", name);
    file.close();
    fs.remove("/" + name);
    file = root.openNextFile();
  }
  root.close();
  return true;
}

bool append_string(fs::FS &fs, const char * path, String s) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    return false;
  }

  file.print(s);
  file.close();
  return true;
}

bool append_uint64(fs::FS &fs, const char * path, uint64_t new_int) {
  String s = uint64_to_string(new_int);
  return append_string(fs, path, s);
}

bool print_file(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    return false;
  }

  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
  return true;
}

bool print_all_files(fs::FS &fs, const char * path) {
  File root = fs.open(path);
  if(!root || !root.isDirectory()){
      return false;
  }

  File file = root.openNextFile();
  while(file) {
    String name = file.name();
    Serial.printf("Reading %s\n", name);
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
    file = root.openNextFile();
  }
  root.close();
  return true;
}
