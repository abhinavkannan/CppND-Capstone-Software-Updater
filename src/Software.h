#ifndef SOFTWARE_H_
#define SOFTWARE_H_

#include <string>

class Software
{
public:
  Software(std::string name, std::string version, std::string date);

  ~Software();

  std::string GetName();
  
  std::string GetVersion();

  std::string GetDate();

private:
  std::string _name;
  std::string _version;
  std::string _date;
};

#endif /* SOFTWARE_H_ */