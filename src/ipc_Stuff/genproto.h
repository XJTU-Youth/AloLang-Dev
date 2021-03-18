#include <string>
#include <vector>

class proto
{
  public:
    std::string protostr;
    void addType(std::string typenamestr, std::vector<std::string> membertype);
    inline std::string getProto() { return this->protostr; };
    proto();
};