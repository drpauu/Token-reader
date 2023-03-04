#include "token.hpp"
#include <cmath>

using namespace std;

token::valors::valors()
{
}

token::valors::valors(const valors &c) throw()
{
  if (std::is_same<decltype(c._enter), int>::value)
  {
    _enter = c._enter;
  }
  else if (std::is_same<decltype(c._real), double>::value)
  {
    _real = c._real;
  }
  else if (std::is_same<decltype(c._racional), racional>::value)
  {
    _racional = c._racional;
  }
}

token::valors &token::valors::operator=(const valors &c) throw()
{
  if (std::is_same<decltype(c._enter), int>::value)
  {
    _enter = c._enter;
  }
  else if (std::is_same<decltype(c._real), double>::value)
  {
    _real = c._real;
  }
  else if (std::is_same<decltype(c._racional), racional>::value)
  {
    _racional = c._racional;
  }

  return *this;
}

token::valors::~valors() throw()
{
}

token::token(token::codi cod) throw(error)
{
  static constexpr std::array<token::codi, 21> validCodes = {
      CT_E,
      VAR_PERCENTATGE,
      SUMA,
      RESTA,
      MULTIPLICACIO,
      DIVISIO,
      EXPONENCIACIO,
      CANVI_DE_SIGNE,
      SIGNE_POSITIU,
      SQRT,
      EXP,
      LOG,
      EVALF,
      OBRIR_PAR,
      TANCAR_PAR,
      COMA,
      ASSIGNACIO,
      DESASSIGNACIO,
      BYEBYE,
      NULLTOK};

  if (cod == CT_ENTERA or cod == CT_RACIONAL or cod == CT_REAL or cod == VARIABLE)
  {
    throw error(ConstructoraInadequada);
  }

  bool isValid = false;
  for (auto validCode : validCodes)
  {
    if (cod == validCode)
    {
      isValid = true;
      break;
    }
  }

  if (!isValid)
  {
    throw error(ConstructoraInadequada);
  }

  _id = cod;
}

token::token(int n) throw(error)
{
  if (n == int(n))
  {
    _id = CT_ENTERA;
    _valor._enter = n;
  }
  else
  {
    throw error(ConstructoraInadequada);
  }
}

token::token(const racional &r) throw(error)
{
  if (isRacional(r))
    throw error(ConstructoraInadequada);
  else
  {
    _id = CT_RACIONAL;
    _valor._racional = r;
  }
}

token::token(double x) throw(error)
{
  if (std::isnan(x))
    throw error(ConstructoraInadequada);
  else
  {
    _id = CT_REAL;
    _valor._real = x;
  }
}

token::token(const string &var_name) throw(error)
{
  if (!std::is_convertible<string, const string &>::value)
    throw error(ConstructoraInadequada);
  else
  {
    if (checkvariables(var_name) == true)
      throw error(IdentificadorIncorrecte);
    else
    {
      _id = VARIABLE;
      _var = var_name;
    }
  }
}

token::token(const token &t) throw(error)
{
  switch (t._id)
  {
  case CT_ENTERA:
    _id = t._id;
    _valor._enter = t._valor._enter;
    break;
  case CT_REAL:
    _id = t._id;
    _valor._real = t._valor._real;
    break;
  case CT_RACIONAL:
    _id = t._id;
    _valor._racional = t._valor._racional;
    break;
  case VARIABLE:
    _id = t._id;
    _var = t._var;
    break;
  case CT_E:
  case VAR_PERCENTATGE:
  case SUMA:
  case RESTA:
  case MULTIPLICACIO:
  case DIVISIO:
  case EXPONENCIACIO:
  case CANVI_DE_SIGNE:
  case SIGNE_POSITIU:
  case ASSIGNACIO:
  case DESASSIGNACIO:
  case SQRT:
  case EXP:
  case LOG:
  case EVALF:
  case OBRIR_PAR:
  case TANCAR_PAR:
  case COMA:
  case BYEBYE:
  case NULLTOK:
    _id = t._id;
    break;
  default:
    throw(IdentificadorIncorrecte);
  }
}

token &token::operator=(const token &t) throw(error)
{
  switch (t._id)
  {
  case CT_ENTERA:
    _id = t._id;
    _valor._enter = t._valor._enter;
    break;
  case CT_REAL:
    _id = t._id;
    _valor._real = t._valor._real;
    break;
  case CT_RACIONAL:
    _id = t._id;
    _valor._racional = t._valor._racional;
    break;
  case VARIABLE:
    _id = t._id;
    _var = t._var;
    break;
  case CT_E:
  case VAR_PERCENTATGE:
  case SUMA:
  case RESTA:
  case MULTIPLICACIO:
  case DIVISIO:
  case EXPONENCIACIO:
  case CANVI_DE_SIGNE:
  case SIGNE_POSITIU:
  case ASSIGNACIO:
  case DESASSIGNACIO:
  case SQRT:
  case EXP:
  case LOG:
  case EVALF:
  case OBRIR_PAR:
  case TANCAR_PAR:
  case COMA:
  case BYEBYE:
  case NULLTOK:
    _id = t._id;
    break;
  default:
    throw(IdentificadorIncorrecte);
  }
  return *this;
}
token::~token() throw()
{
  _id = NULLTOK;
}

token::codi token::tipus() const throw()
{
  return _id;
}

int token::valor_enter() const throw(error)
{
  if (_id == CT_ENTERA)
    return _valor._enter;
  else
    throw error(ConsultoraInadequada);
}

racional token::valor_racional() const throw(error)
{
  if (_id == CT_RACIONAL)
    return _valor._racional;
  else
    throw error(ConsultoraInadequada);
}

double token::valor_real() const throw(error)
{
  if (_id == CT_REAL)
    return _valor._real;
  else
    throw error(ConsultoraInadequada);
}

string token::identificador_variable() const throw(error)
{
  if (_id == VARIABLE)
    return _var;
  else
    throw error(ConsultoraInadequada);
}

bool token::operator==(const token &t) const throw()
{
  if (_id == t._id)
  {
    if (t._id == CT_ENTERA)
    {
      if (_valor._enter != t._valor._enter)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == CT_REAL)
    {
      if (_valor._real != t._valor._real)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == CT_RACIONAL)
    {
      if (_valor._racional != t._valor._racional)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == VARIABLE)
    {
      if (_var != t._var)
      {
        return false;
      }
      else
        return true;
      ;
    }
  }
  else
    return false;
  return true;
}

bool token::operator!=(const token &t) const throw()
{
  if (_id == t._id)
  {
    if (t._id == CT_ENTERA)
    {
      if (_valor._enter == t._valor._enter)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == CT_REAL)
    {
      if (_valor._real == t._valor._real)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == CT_RACIONAL)
    {
      if (_valor._racional == t._valor._racional)
      {
        return false;
      }
      else
        return true;
    }
    else if (t._id == VARIABLE)
    {
      if (_var == t._var)
      {
        return false;
      }
      else
        return true;
      ;
    }
  }
  else
    return true;
  return false;
}

int prioritat(token t)
{
  if (t.tipus() == token::EXPONENCIACIO)
  {
    return 5;
  }
  else if (t.tipus() == token::CANVI_DE_SIGNE)
  {
    return 4;
  }
  else if (t.tipus() == token::SIGNE_POSITIU)
  {
    return 4;
  }
  else if (t.tipus() == token::MULTIPLICACIO)
  {
    return 2;
  }
  else if (t.tipus() == token::DIVISIO)
  {
    return 2;
  }
  else if (t.tipus() == token::SUMA)
  {
    return 1;
  }
  else if (t.tipus() == token::RESTA)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool token::operator>(const token &t) const throw(error)
{
  if ((_id >= 7 and _id <= 13) and (t._id >= 7 and t._id <= 13))
  {
    if (_id == t._id)
    {
      return false;
    }
    else if (prioritat(*this) > prioritat(t))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
    throw(error(PrecedenciaEntreNoOperadors));
}

bool token::operator<(const token &t) const throw(error)
{
  if ((_id >= 7 and _id <= 13) and (t._id >= 7 and t._id <= 13))
  {
    if (_id == t._id)
    {
      return false;
    }
    else if (prioritat(*this) < prioritat(t))
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
    throw(error(PrecedenciaEntreNoOperadors));
}

bool token::checkvariables(const string var)
{
  if (var == "unassign" || var == "e" || var == "sqrt" || var == "log" || var == "exp" || var == "evalf" || var.empty())
    return true;

  for (char c : var)
  {
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_'))
    {
      return true;
    }
  }
  return false;
}