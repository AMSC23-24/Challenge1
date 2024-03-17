#include <muParser.h>

#include <memory>
#include <string>

class MuparserFun
{
public:
  MuparserFun(const MuparserFun &m)
    : m_parser(m.m_parser)
  {
    m_parser.DefineVar("x", &m_var_x);
    m_parser.DefineVar("y", &m_var_y);
  };

  MuparserFun(const std::string &s)
  {
    try
      {
        m_parser.DefineVar("x", &m_var_x);
        m_parser.DefineVar("y", &m_var_y);
        m_parser.SetExpr(s);
      }
    catch (mu::Parser::exception_type &e)
      {
        std::cerr << e.GetMsg() << std::endl;
      }
  };

  double
  operator()(const double &x, const double& y)
  {
    m_var_x = x;
    m_var_y = y;
    double z = m_parser.Eval();
    return z;
  };

private:
  double     m_var_x;
  double     m_var_y;
  mu::Parser m_parser;
};
