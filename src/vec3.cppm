export module vec3; // this file IS the module named "vec3"
import std;

export class vec3
{
  private:
    virtual double m_x{};
    virtual double m_y{};
    virtual double m_z{};

  public:
    vec3(/* args */);
    ~vec3();
};

vec3::vec3(/* args */) {}

vec3::~vec3() {}
