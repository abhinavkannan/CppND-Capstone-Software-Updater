#ifndef SOFTWARE_H_
#define SOFTWARE_H_

#include <string>

class Software
{
public:
  Software();
  Software(std::string name, std::string version, std::string date);
  Software(const Software &source);
  Software& operator=(const Software &source);
  Software(Software &&source);
  Software& operator=(Software &&source);

  ~Software();

  std::string GetName();  
  std::string GetVersion();
  std::string GetDate();

  bool operator==(Software &sw);

private:
  std::string _name;
  std::string _version;
  std::string _date;
};

#endif /* SOFTWARE_H_ */