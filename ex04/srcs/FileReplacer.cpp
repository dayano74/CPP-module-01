#include "FileReplacer.hpp"
#include <fstream>
#include <sstream>

FileReplacer::FileReplacer(const std::string& filename, const std::string& s1, const std::string &s2)
    : _in(filename), _out(filename + ".replace"), _s1(s1), _s2(s2) {}

std::string FileReplacer::replacerAll(const std::string& src, const std::string& from, const std::string& to){

}

bool FileReplacer::run(std::string& err) {
  if (_s1.empty()) {
    err = "s1 must not be empty";
    return false;
  }
  std::ifstream ifs(_in.c_str(), std::ios::in | std::ios::binary);
  if (!ifs) {
    err = "failed to open input: " + _in;
    return false;
  }
  std::ostringstream oss;
  oss << ifs.rdbuf();
  if (!ifs.good() && !ifs.eof()) {
    err = "failed to read input: "  + _in;
    return false;
  }
  const std::string content = oss.str();
}
