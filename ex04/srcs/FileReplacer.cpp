#include "FileReplacer.hpp"

#include <fstream>
#include <sstream>

FileReplacer::FileReplacer(const std::string& filename, const std::string& s1, const std::string& s2)
    : _in(filename), _out(filename + ".replace"), _s1(s1), _s2(s2) {}

std::string FileReplacer::replacerAll(const std::string& src, const std::string& from, const std::string& to) {
  if (from.empty()) return src;
  std::string result = src;
  size_t pos = 0;
  while ((pos = result.find(from, pos)) != std::string::npos) {
    result.erase(pos, from.length());
    result.insert(pos, to);
    pos += to.length();
  }
  return result;
}

bool FileReplacer::readFile(std::string& content, std::string& err) {
  std::ifstream ifs(_in.c_str(), std::ios::in | std::ios::binary);
  if (!ifs) {
    err = "failed to open input: " + _in;
    return false;
  }
  std::ostringstream oss;
  oss << ifs.rdbuf();
  if (!ifs.good() && !ifs.eof()) {
    err = "failed to read input: " + _in;
    return false;
  }
  content = oss.str();
  return true;
}

bool FileReplacer::writeFile(const std::string& replaced, std::string& err) {
  std::ofstream ofs(_out.c_str(), std::ios::out | std::ios::binary);
  if (!ofs) {
    err = "failed to open output: " + _out;
    return false;
  }
  ofs << replaced;
  if (!ofs.good()) {
    err = "failed to write output: " + _out;
    return false;
  }
  return true;
}

bool FileReplacer::run(std::string& err) {
  if (_s1.empty()) {
    err = "s1 must not be empty";
    return false;
  }
  std::string content;
  if (!readFile(content, err)) {
    return false;
  }
  const std::string replaced = replacerAll(content, _s1, _s2);
  if (!writeFile(replaced, err)) {
    return false;
  }
  return true;
}
