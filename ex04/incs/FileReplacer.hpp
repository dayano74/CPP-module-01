#ifndef FILEREPLACER_HPP
#define FILEREPLACER_HPP

#include <string>

class FileReplacer
{
  private:
    std::string _in;
    std::string _out;
    std::string _s1;
    std::string _s2;

    std::string replacerAll(const std::string& src, const std::string& from, const std::string& to);

  public:
    FileReplacer(const std::string &filename, const std::string &s1, const std::string &s2);
    bool run(std::string& err);
};

#endif  // FILEREPLACER_HPP
