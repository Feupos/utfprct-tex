#include <iostream>
#include <functional>

int main()
{
  int m = 5;
  auto multi_m = [m](int a){return a*m;};
  std::cout << multi_m(2);
}

#include <iostream>
#include <functional>

int main()
{
  int m = 5;
  class __lambda_7_20
  {
    public: 
    inline /*constexpr */ int operator()(int a) const
    {
      return a * m;
    }
    private: 
    int m;
    public:
    __lambda_7_20(int & _m)
    : m{_m}
    {}
  };
  __lambda_7_20 multi_m = __lambda_7_20{m};
  std::cout.operator<<(multi_m.operator()(2));
}
