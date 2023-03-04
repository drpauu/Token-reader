#include "expressio.hpp"
#include <stack>

using namespace std;

expressio::expressio(const token t /* = token()*/) throw(error)
{
  node *nou = new node;
  nou->_info = t;
  nou->f_dret = NULL;
  nou->f_esq = NULL;
  _arrel = nou;
}

expressio::expressio(const list<token> &l) throw(error)
{
  node *nou = new node;
  nou->_info = l.front();
  nou->f_dret = NULL;
  nou->f_esq = NULL;
  _arrel = nou;
  // list<token> llista_de_tokens = l;
  // stack<expressio> expre;
  // stack<token> oops;
  // for (list<token>::const_iterator it = l.begin(); it != l.end(); ++it)
  // {
  //   if (is_open_parenthesis(*it) or funcio(*it))
  //   {
  //     oops.push(*it);
  //   }
  //   else if (is_close_parenthesis(*it))
  //   {
  //     while (!oops.empty() and (operators(oops.top()) >= operators(*it)) and
  //            !is_open_parenthesis(oops.top()))
  //     {
  //       expressio aux = expre.top();
  //       expre.pop();
  //       expressio exp = constructora_op(oops.top(), expre.top(), aux);
  //       expre.pop();
  //       oops.pop();
  //       expre.push(exp);
  //     }
  //     oops.pop();
  //     if (funcio(oops.top()))
  //     {
  //       expressio aux;
  //       expressio exp = constructora_op(oops.top(), aux, expre.top());
  //       expre.pop();
  //       oops.pop();
  //       expre.push(exp);
  //     }
  //   }
  //   else if (es_operador(*it) or es_variable(*it))
  //   {
  //     while (!oops.empty() and (operators(*it) <= operators(oops.top())))
  //     {
  //       expressio aux = expre.top();
  //       expre.pop();
  //       expressio exp = constructora_op(oops.top(), expre.top(), aux);
  //       expre.pop();
  //       oops.pop();
  //       expre.push(exp);
  //     }
  //     oops.push(*it);
  //   }
  //   else if (es_operand(*it))
  //   {
  //     expressio exp(*it);
  //     expre.push(exp);
  //   }
  // }
  // while (!oops.empty())
  // {
  //   expressio aux = expre.top();
  //   expre.pop();
  //   expressio exp = constructora_op(oops.top(), expre.top(), aux);
  //   expre.pop();
  //   oops.pop();
  //   expre.push(exp);
  // }
  // _arrel = copia_nodes(expre.top()._arrel);
}

expressio::expressio(const expressio &e) throw(error)
{
  node *nou = new node;
  nou->_info = e._arrel->_info;
  nou->f_dret = NULL;
  nou->f_esq = NULL;
  _arrel = nou;
}
expressio &expressio::operator=(const expressio &e) throw(error)
{
  node *nou = new node;
  nou->_info = e._arrel->_info;
  nou->f_dret = NULL;
  nou->f_esq = NULL;
  _arrel = nou;
  return *this;
}
expressio::~expressio() throw(error)
{
  esborra_nodes(_arrel);
}

expressio::operator bool() const throw()
{
  return NULL != _arrel;
}

bool expressio::operator==(const expressio &e) const throw()
{
  return true;
}
bool expressio::operator!=(const expressio &e) const throw()
{
  return true;
}

void expressio::vars(list<string> &l) const throw(error) {
  if(_arrel->_info.tipus() == token::VARIABLE){
    l.push_back(_arrel->_info.identificador_variable());
  }
}

void expressio::apply_substitution(const string &v, const expressio &e) throw(error) {}

void expressio::simplify_one_step() throw(error) {}

void expressio::simplify() throw(error) {}

void expressio::list_of_tokens(list<token> &lt) throw(error)
{
  lt.push_back(_arrel->_info);
}

// #include "expressio.hpp"
// #include <cmath>
// #include <iostream>
// #include <list>
// #include <stack>

// using namespace std;

// // oepradors, copies de nodes pels operadors, i elimina nodes
// // per utilitat (aquestes dues ultimes estan escrites al .rep)

// // operacions;

// expressio expressio::operacio_corrent(token op, expressio a, expressio b){
//   if(op.tipus() == token::CANVI_DE_SIGNE){
//     return canvi_de_signe(b);
//   }
//   if(op.tipus() == token::LOG){
//     return logaritme(b);
//   }
//   if(op.tipus() == token::SQRT){
//     return func_sqrt(b);
//   }
//   if(op.tipus() == token::EXP){
//     return exp_funct(b);
//   }
//   if(op.tipus() == token::EXPONENCIACIO){
//     return exponenciacio(a, b);
//   }
//   if(op.tipus() == token::MULTIPLICACIO){
//     return multiplicacio(a, b);
//   }
//   if(op.tipus() == token::DIVISIO){
//     return divisio(a, b);
//   }
//   if(op.tipus() == token::SUMA){
//     return suma(a, b);
//   }
//   if(op.tipus() == token::RESTA){
//     return resta(a, b);
//   }
//   if(op.tipus() == token::EVALF){
//     return evalf(b);
//   }
//   return a;
// }

// int expressio::que_eres(token t)
// {
//   if (t.tipus() == token::CT_ENTERA)
//   {
//     return 1;
//   }
//   else if (t.tipus() == token::CT_RACIONAL)
//   {
//     return 2;
//   }
//   else if (t.tipus() == token::CT_REAL)
//   {
//     return 3;
//   }
//   else if (t.tipus() == token::VARIABLE)
//   {
//     return 4;
//   }
//   else if (t.tipus() == token::CANVI_DE_SIGNE)
//   {
//     return 5;
//   }
//   return 0;
// }

// bool expressio::regla1(expressio a)
// {
//   if (que_eres(a._arrel->_info) == 2)
//   {
//     if (a._arrel->_info.valor_racional().num() % a._arrel->_info.valor_racional().denom() == 0)
//     {
//       return true;
//     }
//   }
//   return false;
// }

// expressio expressio::suma(expressio a,
//                           expressio b)
// { // revisar comentaris, pero ja estan fetes
//   if (a._arrel->_info.tipus() == token::VARIABLE or
//       b._arrel->_info.tipus() == token::VARIABLE)
//   {
//     if (que_eres(a._arrel->_info) == 1)
//     {
//       if (a._arrel->_info.valor_enter() == 0)
//       {
//         return b;
//       }
//     }
//     else
//     {
//       if (b._arrel->_info.valor_enter() == 0)
//       {
//         return b;
//       }
//     }
//   }
//   // 3
//   if (que_eres(a._arrel->_info) == 4 and que_eres(b._arrel->_info) == 4)
//   {
//     if (a._arrel->_info.identificador_variable() ==
//         b._arrel->_info.identificador_variable())
//     {
//       expressio t(a);
//       token mult("*");
//       token dos("2");
//       expressio ret = constructora_op(mult, dos, t);
//       return ret;
//     }
//   }
//   // 4 i 5
//   if (que_eres(a._arrel->_info) == 5 or que_eres(b._arrel->_info) == 5)
//   {
//     expressio ret;
//     if (que_eres(a._arrel->_info) == 5)
//     {
//       return resta(b, a);
//     }
//     else
//     {
//       return resta(a, b);
//     }
//   }

//   if (a._arrel->_info.tipus() == token::MULTIPLICACIO and b._arrel->_info.tipus() == token::MULTIPLICACIO)
//   {
//     if (a._arrel->f_dret->_info.tipus() == token::VARIABLE and a._arrel->f_esq->_info.tipus() == token::VARIABLE and
//         b._arrel->f_dret->_info.tipus() == token::VARIABLE and a._arrel->f_esq->_info.tipus() == token::VARIABLE)
//     {
//       token mult("*");
//       token r("+");
//       if (a._arrel->f_dret->_info.identificador_variable() ==
//           b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact =
//             constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_dret->_info.identificador_variable() ==
//           b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact =
//             constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() ==
//           b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact =
//             constructora_op(r, a._arrel->f_dret->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_esq->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() ==
//           b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_dret->_info,
//                                          b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_esq->_info, fact);
//         return ret;
//       }
//     }

//     if (a._arrel->_info.tipus() == token::CT_RACIONAL and b._arrel->_info.tipus() == token::CT_RACIONAL)
//     {
//       token sum("+");
//       token div("/");
//       if (a._arrel->f_dret->_info.valor_racional().denom() ==
//           b._arrel->f_esq->_info.valor_racional().denom())
//       {
//         token a1(a._arrel->f_dret->_info.valor_racional().num());
//         token b1(b._arrel->f_esq->_info.valor_racional().num());
//         token d(a._arrel->_info.valor_racional().denom());
//         expressio fact = constructora_op(sum, a1, b1);
//         expressio ret = constructora_op(div, fact, d);
//         return ret;
//       }
//     }

//     if (que_eres(a._arrel->_info) ==
//         que_eres(b._arrel->_info))
//     {
//       if (que_eres(a._arrel->_info) == 1)
//       {
//         int ret = a._arrel->_info.valor_enter() +
//                   b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 2)
//       {
//         racional ret = a._arrel->_info.valor_racional() +
//                        b._arrel->_info.valor_racional();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 3)
//       {
//         double ret = a._arrel->_info.valor_real() +
//                      b._arrel->_info.valor_real();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->_info) == 4)
//       {
//         token sum("+");
//         expressio addi = constructora_op(sum, a._arrel->f_dret->_info,
//                                          b._arrel->f_dret->_info);
//         return addi;
//       }
//     }
//     if (que_eres(a._arrel->_info) == 2 and que_eres(b._arrel->_info) == 1)
//     {
//       if (regla1(a._arrel->_info))
//       {
//         int ret = a._arrel->_info.valor_racional().part_entera() +
//                   b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (regla1(b._arrel->_info))
//       {
//         int ret = b._arrel->_info.valor_racional().part_entera() +
//                   b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//     }
//   }

//   expressio buida;
//   return buida;
//   // falta fer la regla 1
// }

// expressio expressio::resta(expressio a, expressio b)
// {
//   // 1 i 2
//   if (a._arrel->_info.tipus() == token::VARIABLE or
//       b._arrel->_info.tipus() == token::VARIABLE)
//   {
//     if (que_eres(a._arrel->_info) == 1)
//     {
//       if (a._arrel->_info.valor_enter() == 0)
//       {
//         return b;
//       }
//     }
//     else
//     {
//       if (b._arrel->_info.valor_enter() == 0)
//       {
//         return b;
//       }
//     }
//   }
//   // 3
//   if (que_eres(a._arrel->_info) == 4 and que_eres(b._arrel->_info) == 4)
//   {
//     if (a._arrel->_info.identificador_variable() ==
//         b._arrel->_info.identificador_variable())
//     {

//       token zero("0");
//       expressio t(zero);
//       return t;
//     }
//   }

//   if (que_eres(a._arrel->_info) == 5 or que_eres(b._arrel->_info) == 5)
//   {
//     if (que_eres(b._arrel->_info) == 5)
//     {
//       return suma(a, b);
//     }
//   }

//   if (a._arrel->_info.tipus() == token::MULTIPLICACIO and b._arrel->_info.tipus() == token::MULTIPLICACIO)
//   {
//     if (a._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE and
//         b._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE)
//     {
//       token mult("*");
//       token r("-");
//       if (a._arrel->f_dret->_info.identificador_variable() == b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_dret->_info.identificador_variable() == b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() == b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_dret->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_esq->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() == b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_dret->_info,
//                                          b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_esq->_info, fact);
//         return ret;
//       }
//     }
//   }

//   if (a._arrel->_info.tipus() == token::CT_RACIONAL and b._arrel->_info.tipus() == token::CT_RACIONAL)
//   {
//     token r("-");
//     token div("/");
//     if (a._arrel->f_dret->_info.valor_racional().denom() ==
//         b._arrel->f_esq->_info.valor_racional().denom())
//     {
//       token a1(a._arrel->f_dret->_info.valor_racional().num());
//       token b1(b._arrel->f_esq->_info.valor_racional().num());
//       token d(a._arrel->_info.valor_racional().denom());
//       expressio fact = constructora_op(r, a1, b1);
//       expressio ret = constructora_op(div, fact, d);
//       return ret;
//     }
//   }

//   if (que_eres(a._arrel->_info) ==
//       que_eres(b._arrel->_info))
//   {
//     if (que_eres(a._arrel->_info) == 1)
//     {
//       int ret = a._arrel->_info.valor_enter() -
//                 b._arrel->_info.valor_enter();
//       token resultat(ret);
//       expressio addi(resultat);
//       return addi;
//     }
//     if (que_eres(a._arrel->f_dret->_info) == 2)
//     {
//       racional ret = a._arrel->_info.valor_racional() -
//                      b._arrel->_info.valor_racional();
//       token resultat(ret);
//       expressio addi(resultat);
//       return addi;
//     }
//     if (que_eres(a._arrel->f_dret->_info) == 3)
//     {
//       double ret = a._arrel->_info.valor_real() -
//                    b._arrel->_info.valor_real();
//       token resultat(ret);
//       expressio addi(resultat);
//       return addi;
//     }
//     if (que_eres(a._arrel->_info) == 4)
//     {
//       token sum("-");
//       expressio addi = constructora_op(sum, a._arrel->f_dret->_info,
//                                        b._arrel->f_dret->_info);
//       return addi;
//     }
//   }
//   if (que_eres(a._arrel->_info) == 2 and que_eres(b._arrel->_info) == 1)
//   {
//     if (regla1(a._arrel->_info))
//     {
//       int ret = a._arrel->_info.valor_racional().part_entera() -
//                 b._arrel->_info.valor_enter();
//       token resultat(ret);
//       expressio addi(resultat);
//       return addi;
//     }
//     if (regla1(b._arrel->_info))
//     {
//       int ret = b._arrel->_info.valor_racional().part_entera() -
//                 b._arrel->_info.valor_enter();
//       token resultat(ret);
//       expressio addi(resultat);
//       return addi;
//     }
//   }

//   expressio buida;
//   return buida;
//   // falta fer la regla 1
// }

// expressio expressio::multiplicacio(expressio a, expressio b)
// {
//   if (a._arrel->_info.tipus() == token::VARIABLE or
//       b._arrel->_info.tipus() == token::VARIABLE)
//   {
//     if (que_eres(a._arrel->_info) == 1)
//     {
//       if (a._arrel->_info.valor_enter() == 0)
//       {
//         token zero("0");
//         expressio t(zero);
//         return t;
//       }
//     }
//     else if (b._arrel->_info.valor_enter() == 0)
//     {
//       if (b._arrel->_info.valor_enter() == 0)
//       {
//         token zero("0");
//         expressio t(zero);
//         return t;
//       }
//     }
//     else if (a._arrel->_info.valor_enter() == 1)
//     {
//       return b;
//     }
//     else if (a._arrel->_info.valor_enter() == 1)
//     {
//       return a;
//     }
//   }
//   // 3
//   if (que_eres(a._arrel->_info) == 4 and que_eres(b._arrel->_info) == 4)
//   {
//     if (a._arrel->_info.identificador_variable() == b._arrel->_info.identificador_variable())
//     {
//       token dos("2");
//       return exponenciacio(a, dos);
//     }
//   }

//   // revisar aquesta regla
//   if (que_eres(a._arrel->_info) == 5 or que_eres(b._arrel->_info) == 5)
//   {
//     if (que_eres(a._arrel->_info) == 5)
//     {
//       return canvi_de_signe(multiplicacio(canvi_de_signe(a._arrel->_info), b._arrel->_info));
//     }
//     else
//     {
//       return canvi_de_signe(multiplicacio(canvi_de_signe(b._arrel->_info), a._arrel->_info));
//     }
//   }
//   // falta fer la regla 1
//   if (que_eres(a._arrel->_info) == 2 or que_eres(b._arrel->_info) == 2)
//   {
//     if (que_eres(a._arrel->_info) == 2)
//     {
//       if (a._arrel->_info.valor_racional().num() == 1)
//       {
//         if (que_eres(b._arrel->_info) == 1)
//         {
//           token un(b._arrel->_info.valor_enter());
//           token dos("/");
//           token tres(a._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//         else if (que_eres(b._arrel->_info) == 3)
//         {
//           token un(b._arrel->_info.valor_real());
//           token dos("/");
//           token tres(a._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//         else if (que_eres(b._arrel->_info) == 4)
//         {
//           token un(b._arrel->_info.identificador_variable());
//           token dos("/");
//           token tres(a._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//       }
//     }
//     else if (que_eres(b._arrel->_info) == 2)
//     {
//       if (b._arrel->_info.valor_racional().num() == 1)
//       {
//         if (que_eres(a._arrel->_info) == 1)
//         {
//           token un(a._arrel->_info.valor_enter());
//           token dos("/");
//           token tres(b._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//         else if (que_eres(a._arrel->_info) == 3)
//         {
//           token un(a._arrel->_info.valor_real());
//           token dos("/");
//           token tres(b._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//         else if (que_eres(a._arrel->_info) == 4)
//         {
//           token un(a._arrel->_info.identificador_variable());
//           token dos("/");
//           token tres(b._arrel->_info.valor_racional().denom());
//           list<token> racion;
//           racion.push_back(un);
//           racion.push_back(dos);
//           racion.push_back(tres);
//           expressio ret(racion);
//           return ret;
//         }
//       }
//     }
//   }
//   if (a._arrel->_info.tipus() == token::EXPONENCIACIO and b._arrel->_info.tipus() == token::EXPONENCIACIO)
//   {
//     if (a._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE and
//         b._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE)
//     {
//       token mult("^");
//       token r("*");
//       if (a._arrel->f_dret->_info.identificador_variable() == b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() == b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_dret->_info, b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, fact, a._arrel->f_esq->_info);
//         return ret;
//       }
//     }
//   }
//   if (a._arrel->_info.tipus() == token::EXP and b._arrel->_info.tipus() == token::EXP)
//   {
//     token un(a._arrel->f_dret->_info);
//     token dos("+");
//     token tres(b._arrel->f_dret->_info);
//     list<token> racion;
//     racion.push_back(un);
//     racion.push_back(dos);
//     racion.push_back(tres);
//     expressio ret(racion);
//     return exp_funct(ret);
//   }
//   if (que_eres(a._arrel->_info) ==
//         que_eres(b._arrel->_info))
//     {
//       if (que_eres(a._arrel->_info) == 1)
//       {
//         int ret = a._arrel->_info.valor_enter() *
//                   b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 2)
//       {
//         racional ret = a._arrel->_info.valor_racional() *
//                        b._arrel->_info.valor_racional();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 3)
//       {
//         double ret = a._arrel->_info.valor_real() *
//                      b._arrel->_info.valor_real();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->_info) == 4)
//       {
//         token sum("*");
//         expressio addi = constructora_op(sum, a._arrel->f_dret->_info,
//                                          b._arrel->f_dret->_info);
//         return addi;
//       }
//     }
//     if(que_eres(a._arrel->_info) == 2 and que_eres(b._arrel->_info) == 1){
//       if(regla1(a._arrel->_info)){
//         int ret = a._arrel->_info.valor_racional().part_entera() *
//                        b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if(regla1(b._arrel->_info)){
//         int ret = b._arrel->_info.valor_racional().part_entera() *
//                        b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//     }
//   expressio buida;
//   return buida;
//   // falta regla1;
// }

// expressio expressio::divisio(expressio a, expressio b) throw(error)
// {
//   if (que_eres(b._arrel->_info) == 1)
//   {
//     if (b._arrel->_info.valor_enter() == 0)
//     {
//       throw error(DivPerZero);
//     }
//     else if (b._arrel->_info.valor_enter() == 1)
//     {
//       return a;
//     }
//   }
//   if (que_eres(a._arrel->_info) == 1)
//   {
//     if (a._arrel->_info.valor_enter() == 0)
//     {
//       token zero("0");
//       expressio t(zero);
//       return t;
//     }
//   }
//   if (que_eres(a._arrel->_info) == 4 and que_eres(b._arrel->_info) == 4)
//   {
//     if (a._arrel->_info.identificador_variable() == b._arrel->_info.identificador_variable())
//     {
//       token un("1");
//       expressio t(un);
//       return t;
//     }
//   }
//   if (que_eres(a._arrel->_info) == 5 or que_eres(b._arrel->_info) == 5)
//   {
//     if (que_eres(b._arrel->_info) == 5)
//     {
//       return canvi_de_signe(divisio(canvi_de_signe(b._arrel->_info), a._arrel->_info));
//     }
//   }
//   if (que_eres(b._arrel->_info) == 2)
//   {
//     if (b._arrel->_info.valor_racional().num() == 1)
//     {
//       token d(b._arrel->_info.valor_racional().denom());
//       expressio den(d);
//       return multiplicacio(a, den);
//     }
//   }
//   if (a._arrel->_info.tipus() == token::EXPONENCIACIO and b._arrel->_info.tipus() == token::EXPONENCIACIO)
//   {
//     if (a._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE and
//         b._arrel->f_dret->_info.tipus() == token::VARIABLE and
//         a._arrel->f_esq->_info.tipus() == token::VARIABLE)
//     {
//       token mult("^");
//       token r("/");
//       if (a._arrel->f_dret->_info.identificador_variable() == b._arrel->f_dret->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_esq->_info, b._arrel->f_esq->_info);
//         expressio ret = constructora_op(mult, a._arrel->f_dret->_info, fact);
//         return ret;
//       }
//       if (a._arrel->f_esq->_info.identificador_variable() == b._arrel->f_esq->_info.identificador_variable())
//       {
//         expressio fact = constructora_op(r, a._arrel->f_dret->_info, b._arrel->f_dret->_info);
//         expressio ret = constructora_op(mult, fact, a._arrel->f_esq->_info);
//         return ret;
//       }
//     }
//   }
//   if (a._arrel->_info.tipus() == token::EXP and b._arrel->_info.tipus() == token::EXP)
//   {
//     token un(a._arrel->f_dret->_info);
//     token dos("-");
//     token tres(b._arrel->f_dret->_info);
//     list<token> racion;
//     racion.push_back(un);
//     racion.push_back(dos);
//     racion.push_back(tres);
//     expressio ret(racion);
//     return exp_funct(ret);
//   }
//   if (que_eres(a._arrel->_info) ==
//         que_eres(b._arrel->_info))
//     {
//       if (que_eres(a._arrel->_info) == 1)
//       {
//         int ret = a._arrel->_info.valor_enter() /
//                   b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 2)
//       {
//         racional ret = a._arrel->_info.valor_racional() /
//                        b._arrel->_info.valor_racional();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->f_dret->_info) == 3)
//       {
//         double ret = a._arrel->_info.valor_real() /
//                      b._arrel->_info.valor_real();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if (que_eres(a._arrel->_info) == 4)
//       {
//         token sum("/");
//         expressio addi = constructora_op(sum, a._arrel->f_dret->_info,
//                                          b._arrel->f_dret->_info);
//         return addi;
//       }
//     }
//     if(que_eres(a._arrel->_info) == 2 and que_eres(b._arrel->_info) == 1){
//       if(regla1(a._arrel->_info)){
//         int ret = a._arrel->_info.valor_racional().part_entera() /
//                        b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//       if(regla1(b._arrel->_info)){
//         int ret = b._arrel->_info.valor_racional().part_entera() /
//                        b._arrel->_info.valor_enter();
//         token resultat(ret);
//         expressio addi(resultat);
//         return addi;
//       }
//     }
//   expressio buida;
//   return buida;
//   // falta regla1;
// }

// expressio expressio::exponenciacio(expressio a, expressio b) throw(error)
// {
//   if (que_eres(b._arrel->_info) != 1 and !regla1(b))
//   {
//     throw error(NegatElevNoEnter);
//   }
//   else if(!regla1(b))
//   {
//     if (b._arrel->_info.valor_enter() == 0)
//     {
//       token un("1");
//       expressio t(un);
//       return t;
//     }
//     if (b._arrel->_info.valor_enter() == 1)
//     {
//       return a;
//     }
//     // canvi de signe (no ho se fer)
//     if (a._arrel->_info.tipus() == token::EXPONENCIACIO)
//     {
//       token un(a._arrel->f_dret->_info);
//       token dos("*");
//       token tres(b._arrel->_info);
//       list<token> racion;
//       racion.push_back(un);
//       racion.push_back(dos);
//       racion.push_back(tres);
//       expressio ret(racion);
//       return exponenciacio(a._arrel->f_esq->_info, ret);
//     }
//     if (a._arrel->_info.tipus() == token::EXP)
//     {
//       token un(a._arrel->f_dret->_info);
//       token dos("*");
//       token tres(b._arrel->_info);
//       list<token> racion;
//       racion.push_back(un);
//       racion.push_back(dos);
//       racion.push_back(tres);
//       expressio ret(racion);
//       return exp_funct(ret);
//     }
//   } else {
//     if (b._arrel->_info.valor_racional().part_entera() == 0)
//     {
//       token un("1");
//       expressio t(un);
//       return t;
//     }
//     if (b._arrel->_info.valor_racional().part_entera() == 1)
//     {
//       return a;
//     }
//     // canvi de signe (no ho se fer)
//     if (a._arrel->_info.tipus() == token::EXPONENCIACIO)
//     {
//       token un(a._arrel->f_dret->_info);
//       token dos("*");
//       token tres(b._arrel->_info.valor_racional().part_entera());
//       list<token> racion;
//       racion.push_back(un);
//       racion.push_back(dos);
//       racion.push_back(tres);
//       expressio ret(racion);
//       return exponenciacio(a._arrel->f_esq->_info, ret);
//     }
//     if (a._arrel->_info.tipus() == token::EXP)
//     {
//       token un(a._arrel->f_dret->_info);
//       token dos("*");
//       token tres(b._arrel->_info.valor_racional().part_entera());
//       list<token> racion;
//       racion.push_back(un);
//       racion.push_back(dos);
//       racion.push_back(tres);
//       expressio ret(racion);
//       return exp_funct(ret);
//     }
//   }
//   expressio buida;
//   return buida;
// }

// expressio expressio::c_racional(expressio a)
// {
//   int n = a._arrel->_info.valor_racional().num();
//   token regla0(n);
//   expressio ret(regla0);
//   return regla0;
// }

// expressio expressio::canvi_de_signe(expressio a)
// {
//   if (que_eres(a._arrel->_info) == 5)
//   {
//     token un("-1");
//     expressio menys(un);
//     return multiplicacio(a, menys);
//   }
//   else
//   {
//     return a;
//   }
// }

// expressio expressio::logaritme(expressio op) throw (error)
// {
//   if(que_eres(op._arrel->_info) == 1){
//     if(op._arrel->_info.valor_enter() == 1){
//     token un("0");
//     expressio menys(un);
//     return menys;
//     }
//   }
//   if(op._arrel->_info.tipus() == token::CT_E){
//     if(op._arrel->_info.valor_enter() == 1){
//       token un("1");
//     expressio menys(un);
//     return menys;
//     }
//   }
//   if(op._arrel->f_dret->_info.tipus() == token::EXP){
//     return op._arrel->f_dret->f_dret->_info;
//   }
//   if(op._arrel->f_dret->_info.tipus() == token::MULTIPLICACIO){
//     token un("+");
//     expressio menys = constructora_op(un, op._arrel->f_dret->f_esq->_info, op._arrel->f_dret->f_dret->_info);
//     return menys;
//   }
//   if(op._arrel->f_dret->_info.tipus() == token::DIVISIO){
//     token un("-");
//     expressio menys = constructora_op(un, op._arrel->f_dret->f_esq->_info, op._arrel->f_dret->f_dret->_info);
//     return menys;
//   }
//   if(op._arrel->f_dret->_info.tipus() == token::EXPONENCIACIO){
//     token un("*");
//     expressio menys = constructora_op(un, op._arrel->f_dret->f_dret->_info, logaritme(op._arrel->f_dret->f_esq->_info));
//     return menys;
//   }
//   expressio buit;
//   return buit;
// }

// expressio expressio::exp_funct(expressio op) throw (error)
// {
//   if (op._arrel->f_dret->_info.tipus() == token::LOG)
//   {
//     return op._arrel->f_dret->f_dret->_info;
//   }
//   else if (op._arrel->_info.tipus() == token::CT_RACIONAL)
//   {
//     if(op._arrel->_info.valor_racional().part_entera() <= 0){
//       throw error(NegatElevNoEnter);
//     }
//   }
//   else if (op._arrel->_info.tipus() == token::CT_REAL)
//   {
//     if(op._arrel->_info.valor_real() <= 0){
//       throw error(NegatElevNoEnter);
//     }
//     token ret(exp(op._arrel->_info.valor_real()));
//     expressio r(ret);
//     return r;
//   }
//   else if (op._arrel->_info.tipus() == token::VARIABLE)
//   {
//     return op;
//   } else if(que_eres(op._arrel->_info)){
//     if(op._arrel->_info.valor_real() <= 0){
//       throw error(NegatElevNoEnter);
//     }
//     token ret(exp(op._arrel->_info.valor_enter()));
//     expressio r(ret);
//     return r;
//   }
//   expressio buit;
//   return buit;
// }

// expressio expressio::func_sqrt(expressio op) throw(error)
// {
//   if (op._arrel->_info.tipus() == token::CT_ENTERA)
//   {
//     if (op._arrel->_info.valor_enter() <= 0)
//     {
//       throw error(SqrtDeNegatiu);
//     }
//   }
//   else if (op._arrel->_info.tipus() == token::CT_RACIONAL)
//   {
//     if (op._arrel->_info.valor_racional().part_entera() <= 0)
//     {
//       throw error(SqrtDeNegatiu);
//     }
//   }
//   else if (op._arrel->_info.tipus() == token::CT_REAL)
//   {
//     if (op._arrel->_info.valor_real() <= 0)
//     {
//       throw error(SqrtDeNegatiu);
//     }
//   }

//   if (op._arrel->_info.tipus() == token::CT_ENTERA)
//   {
//     token ee("^");
//     racional un(1, 2);
//     token rac(un);
//     expressio r(rac);
//     expressio ret = constructora_op(ee, op, r);
//     return ret;
//   }
//   else if (op._arrel->_info.tipus() == token::CT_RACIONAL)
//   {
//     token ee("^");
//     racional un(1, 2);
//     token rac(un);
//     expressio r(rac);
//     expressio ret = constructora_op(ee, op, r);
//     return ret;
//   }
//   else if (op._arrel->_info.tipus() == token::CT_REAL)
//   {
//     double ret(sqrt(op._arrel->_info.valor_real()));
//     token r(ret);
//     expressio xd(r);
//     return xd;
//   }
//   else if (op._arrel->_info.tipus() == token::VARIABLE)
//   {
//     token ee("^");
//     racional un(1, 2);
//     token rac(un);
//     expressio r(rac);
//     expressio ret = constructora_op(ee, op, r);
//     return ret;
//   }
//   expressio buit;
//   return buit;
// }

// expressio expressio::evalf(expressio b){
//   if(que_eres(b._arrel->_info) == 3){
//     return b;
//   }
//   if(b._arrel->_info.tipus() == token::CT_E){
//     token ee(2.718281828);
//     expressio ret(ee);
//     return ret;
//   }
//   if(que_eres(b._arrel->_info) == 4){
//     return b._arrel->_info;
//   }
//   b.simplify();
//   return b;
// }

// /* Constructora d'una expressió formada per un sol token: un operand. Si
//    s'utiliza el valor del token per defecte es construeix la que
//    anomenem "expressió buida". Si el tipus del token no és el del token
//    per defecte (NULLTOK), ni el d'una CT_ENTERA, CT_RACIONAL, CT_REAL,
//    CT_E, VARIABLE o VAR_PERCENTAtGE es produeix un error sintàctic. */
// expressio::expressio(const token t) throw(error)
// {
//   if (t.tipus() == token::NULLTOK)
//   {
//     _arrel = new node;
//     _arrel = NULL;
//     es_buit = true;
//   }
//   else if (t.tipus() == token::CT_ENTERA or
//            t.tipus() == token::CT_RACIONAL or t.tipus() == token::CT_REAL or
//            t.tipus() == token::VARIABLE or
//            t.tipus() == token::VAR_PERCENTATGE)
//   {
//     _arrel = new node;
//     _arrel->f_dret = NULL;
//     _arrel->f_esq = NULL;
//     _arrel->_info = t;
//     _lt.push_back(t);
//     es_buit = false;
//   }
//   else
//   {
//     throw error(ErrorSintactic);
//   }
// }

// int operators(token op)
// {
//   if (op.tipus() == token::SUMA or op.tipus() == token::RESTA)
//     return 1;
//   if (op.tipus() == token::MULTIPLICACIO or op.tipus() == token::DIVISIO)
//     return 2;
//   else if(op.tipus() == token::EXPONENCIACIO){
//     return 3;
//   } else if(op.tipus() == token::EVALF){
//     return -1;
//   }
//   return 0;
// }

// bool expressio::es_operand(token t)
// {
//   if (t.tipus() == token::CT_ENTERA or t.tipus() == token::CT_RACIONAL or
//       t.tipus() == token::CT_REAL or t.tipus() == token::VARIABLE or
//       t.tipus() == token::VAR_PERCENTATGE)
//   {
//     return true;
//   }
//   else
//   {
//     return false;
//   }
// }

// bool es_operador(token op)
// {
//   return op.tipus() == token::MULTIPLICACIO or op.tipus() == token::DIVISIO or
//          op.tipus() == token::SUMA or op.tipus() == token::RESTA;
// }

// bool funcio(token t)
// {
//   return t.tipus() == token::LOG or t.tipus() == token::EXP or
//          t.tipus() == token::SQRT or t.tipus() == token::CANVI_DE_SIGNE;
// }

// bool canvi_de_signe(token t) { return t.tipus() == token::CANVI_DE_SIGNE; }

// bool parenter(token token)
// {
//   return token.tipus() == token::OBRIR_PAR and
//          token.tipus() == token::TANCAR_PAR;
// }

// bool es_variable(token t)
// {
//   if (!es_operador(t) and !parenter(t) and !funcio(t))
//   {
//     return true;
//   }
//   else
//   {
//     return false;
//   }
// }

// expressio expressio::constructora_op(
//     token t, expressio a,
//     expressio b) // si esta malament mirar en l arxiu de lewandoski.cc
// {
//   expressio ret(t);
//   if (es_operador(t))
//   {
//     // ret._arrel = new node;
//     // ret._arrel->_info = t;
//     ret._arrel->f_dret = a._arrel;
//     ret._arrel->f_esq = b._arrel;
//   }
//   ret.es_buit = false;
//   return ret;
// }

// int expressio::morfosintactico(list<token> &lt)
// {
//   stack<token> stk;
//   for (list<token>::iterator it = lt.begin(); it != lt.end(); it++)
//   {
//     if (it->tipus() == token::OBRIR_PAR || it->tipus() == token::SUMA ||
//         it->tipus() == token::RESTA || it->tipus() == token::MULTIPLICACIO ||
//         it->tipus() == token::DIVISIO ||
//         it->tipus() == token::EXPONENCIACIO || it->tipus() == token::LOG ||
//         it->tipus() == token::EXP || it->tipus() == token::SQRT)
//     {
//       stk.push(*it);
//     }
//     else if (it->tipus() == token::TANCAR_PAR)
//     {
//       if (stk.empty() || stk.top().tipus() == token::OBRIR_PAR)
//       {
//         return 31;
//       }
//       if (it->tipus() == token::SUMA || it->tipus() == token::RESTA ||
//           it->tipus() == token::MULTIPLICACIO ||
//           it->tipus() == token::DIVISIO ||
//           it->tipus() == token::EXPONENCIACIO || it->tipus() == token::LOG ||
//           it->tipus() == token::EXP || it->tipus() == token::SQRT)
//       {
//         return 31;
//       }
//       stk.pop();
//     }
//     else if (it->tipus() == token::RESTA)
//     {
//       if (stk.empty() || (stk.top().tipus() != token::SUMA &&
//                           stk.top().tipus() != token::RESTA &&
//                           stk.top().tipus() != token::MULTIPLICACIO &&
//                           stk.top().tipus() != token::DIVISIO &&
//                           stk.top().tipus() != token::EXPONENCIACIO &&
//                           stk.top().tipus() != token::LOG &&
//                           stk.top().tipus() != token::EXPONENCIACIO &&
//                           stk.top().tipus() != token::SQRT))
//       {
//         stk.push(*it);
//       }
//       else
//       {
//         stk.pop();
//       }
//     }
//     else
//     {
//       if (stk.empty() || (stk.top().tipus() != token::SUMA &&
//                           stk.top().tipus() != token::RESTA &&
//                           stk.top().tipus() != token::MULTIPLICACIO &&
//                           stk.top().tipus() != token::DIVISIO &&
//                           stk.top().tipus() != token::EXPONENCIACIO &&
//                           stk.top().tipus() != token::LOG &&
//                           stk.top().tipus() != token::EXPONENCIACIO &&
//                           stk.top().tipus() != token::SQRT))
//       {
//         return 31;
//       }

//       if (stk.top().tipus() == token::EXPONENCIACIO)
//       {
//         if (it->tipus() != token::CT_ENTERA)
//         {
//           return 32;
//         }
//       }

//       // check for division by zero
//       if (stk.top().tipus() == token::DIVISIO)
//       {
//         if (it->valor_enter() ==
//             0) // she de comprovar amb racional i real tambe, pq enter no es
//                // le unic que potser 0
//         {
//           return 33;
//         }
//       }

//       // check for log of non-positive numbers
//       if (stk.top().tipus() == token::LOG)
//       {
//         if (it->valor_enter() <= 0) // el mateix que a dalt
//         {
//           return 34;
//         }
//       }
//       // check for sqrt of negative numbers
//       if (stk.top().tipus() == token::SQRT)
//       {
//         if (it->valor_enter() < 0) // el mateix
//         {
//           return 35;
//         }
//       }

//       stk.pop();
//     }
//   }
//   if (!stk.empty())
//   {
//     if (stk.top().tipus() != token::SUMA or
//         stk.top().tipus() != token::RESTA or
//         stk.top().tipus() != token::MULTIPLICACIO or
//         stk.top().tipus() != token::DIVISIO or
//         stk.top().tipus() != token::EXPONENCIACIO or
//         stk.top().tipus() != token::LOG or
//         stk.top().tipus() != token::EXPONENCIACIO or
//         stk.top().tipus() != token::SQRT)
//     {
//       return 31;
//     }
//     else
//     {
//       return 31;
//     }
//   }
//   return 0;
// }

// expressio::expressio(const list<token> &l) throw(error)
// {
//   list<token> llista_de_tokens = l;
//   int errors_sintactics = morfosintactico(llista_de_tokens);
//   if (errors_sintactics != 0)
//   {
//     if (errors_sintactics == 31)
//       throw error(ErrorSintactic);
//     if (errors_sintactics == 32)
//       throw error(NegatElevNoEnter);
//     if (errors_sintactics == 33)
//       throw error(LogDeNoPositiu);
//     if (errors_sintactics == 34)
//       throw error(SqrtDeNegatiu);
//   }
//   stack<expressio> expre;
//   stack<token> oops;
//   for (list<token>::const_iterator it = l.begin(); it != l.end(); ++it)
//   {
//     if (is_open_parenthesis(*it) or funcio(*it) or canvi_de_signe(*it))
//     {
//       oops.push(*it);
//     }
//     else if (is_close_parenthesis(*it))
//     {
//       while (!oops.empty() and (operators(oops.top()) >= operators(*it)) and
//              !is_open_parenthesis(oops.top()))
//       {
//         expressio aux = expre.top();
//         expre.pop();
//         expressio exp = constructora_op(oops.top(), expre.top(), aux);
//         expre.pop();
//         oops.pop();
//         expre.push(exp);
//       }
//       oops.pop();
//       if (funcio(oops.top()))
//       {
//         expressio aux;
//         expressio exp = constructora_op(oops.top(), aux, expre.top());
//         expre.pop();
//         oops.pop();
//         expre.push(exp);
//       }
//     }
//     else if (es_operador(*it) or es_variable(*it))
//     {
//       while (!oops.empty() and (operators(*it) <= operators(oops.top())))
//       {
//         expressio aux = expre.top();
//         expre.pop();
//         expressio exp = constructora_op(oops.top(), expre.top(), aux);
//         expre.pop();
//         oops.pop();
//         expre.push(exp);
//       }
//       oops.push(*it);
//     }
//     else if (es_operand(*it))
//     {
//       expressio exp(*it);
//       expre.push(exp);
//     }
//   }
//   while (!oops.empty())
//   {
//     expressio aux = expre.top();
//     expre.pop();
//     expressio exp = constructora_op(oops.top(), expre.top(), aux);
//     expre.pop();
//     oops.pop();
//     expre.push(exp);
//   }
//   es_buit = false;
//   *this = expre.top();
// }
// // Constructora per còpia, assignació i destructora.
// expressio::expressio(const expressio &e) throw(error) { *this = e; }

// expressio &expressio::operator=(const expressio &e) throw(error)
// {
//   *this = e;
//   return *this;
// }
// expressio::~expressio() throw(error)
// {
//   esborra_nodes(_arrel);
//   es_buit = true;
// }

// // Retorna cert si i només si s'aplica a l'expressió buida.
// expressio::operator bool() const throw() { return es_buit; }

// /* Operadors d'igualtat i desigualtat. Dues expressions es consideren
//    iguals si i només si els seus arbres d'expressió són idèntics. */
// bool expressio::operator==(const expressio &e) const throw()
// {
//   if (*this == e)
//   {
//     return true;
//   }
//   else
//     return false;
// }
// bool expressio::operator!=(const expressio &e) const throw()
// {
//   if (*this == e)
//   {
//     return true;
//   }
//   else
//     return false;
// }

// /* Retorna una llista sense repeticions, en qualsevol ordre, amb
//    els noms de les variables de l'expressió. */
// void expressio::vars(list<string> &l) const throw(error)
// {
//   /*for(list <token>::iterator elem = exp_.begin(); elem != exp_.end();
//   elem++){ list <string>::iterator it ;
//       //it = find(l.begin(), l.end(), elem.)
//   } */
//   l.sort();
//   l.unique();
//   for (list<token>::const_iterator it = _lt.begin(); it != _lt.end(); ++it)
//   {
//     if (it->tipus() == token::VARIABLE)
//     {
//       l.push_back(it->identificador_variable());
//     }
//   }
//   // return variables;
// }

// /* Substitueix totes les aparicions de la variable de nom v per
//    l'expressió e. Si no existeix la variable v dins de l'expressió a la
//    que apliquem aquest mètode l'expressió no es modifica. */
// void expressio::apply_substitution(const string &v,
//                                    const expressio &e) throw(error) {}

// void expressio::set_left_child(node *n) { _arrel->f_esq = n; }

// void expressio::set_right_child(node *n) { _arrel->f_dret = n; }

// /* Aplica un pas de simplificació a l'expressió. La subexpressió a
//    simplificar es busca seguint el recorregut "left to right" postordre
//    explicat a l'apartat "Procés d'avaluació". Es pot produir qualsevol dels
//    errors semàntics que apareixen més avall numerats des del 32 al 35. */
// void expressio::simplify_one_step() throw(error)
// {
//   // s ha de implementar tambe les funcions i fer les operacions correctament

//   // Check if the expression is already a leaf node (i.e., a single operand)
//   if (_arrel->f_esq == NULL && _arrel->f_dret == NULL)
//   {
//     return;
//   }

//   // Check if both children are operands

//   // en el cas que tingui fill dret pero no fill esquerra, es tractara com a
//   // una funcio
//   if (es_operand(_arrel->f_esq->_info) && es_operand(_arrel->f_dret->_info))
//   {
//     // Perform the operation and replace the current node with the result
//     expressio result = operacio_corrent(_arrel->_info, _arrel->f_dret->_info, _arrel->f_esq->_info);
//     node *nou;
//     nou = new node;
//     nou = result._arrel;
//     _arrel = nou;
//   }
//   else
//   {
//     // Simplify the left and right children recursively
//     expressio left(_arrel->f_esq->_info);
//     left.set_left_child(_arrel->f_esq->f_esq);
//     left.set_right_child(_arrel->f_esq->f_dret);
//     left.simplify_one_step();
//     _arrel->f_esq = left._arrel;

//     expressio right(_arrel->f_dret->_info);
//     right.set_left_child(_arrel->f_dret->f_esq);
//     right.set_right_child(_arrel->f_dret->f_dret);
//     right.simplify_one_step();
//     _arrel->f_dret = right._arrel;
//   }
// }

// /* Aplica successius passos de simplificació com l'anterior fins que
//    l'expressió es trobi completament simplificada. Llavors diem que es
//    troba en "forma normal". Es pot produir qualsevol dels errors
//    semàntics que apareixen més avall numerats des del 32 al 35. */
// void expressio::simplify() throw(error)
// {
//   bool simplified = false;

//   // Keep simplifying until the expression can't be simplified any further
//   while (!simplified)
//   {
//     simplify_one_step();
//     if (_arrel->f_esq == NULL && _arrel->f_dret == NULL)
//     {
//       simplified = true;
//     }
//   }
// }

// /* Converteix l'expressió en la seqüència de tokens lt corresponent: els
//    operadors apareixen entre els operands si són infixos, abans si són
//    prefixos i els símbols de funció van seguits de parèntesis que tanquen
//    els seus arguments separats per comes. S'han d'introduir només aquells
//    parèntesis que siguin estrictament necessaris per trencar les regles de
//    precedència o associativitat en l'ordre d'aplicació dels operadors. */

// void expressio::list_of_tokens(list<token> &lt) throw(error)
// {
//   tree_to_list(_arrel, lt);
// }

// void expressio::tree_to_list(node *n, list<token> &l)
// {
//   if (n == NULL)
//     return;

//   if (es_operador(n->_info))
//   {
//     int priority = 0;
//     if (n->_info.tipus() == token::EXPONENCIACIO)
//     {
//       priority = 3;
//     }
//     else if (n->_info.tipus() == token::MULTIPLICACIO or
//              n->_info.tipus() == token::DIVISIO)
//     {
//       priority = 2;
//     }
//     else if (n->_info.tipus() == token::SUMA or
//              n->_info.tipus() == token::RESTA)
//     {
//       priority = 1;
//     }

//     if (l.empty() or operators(l.back()) < priority)
//     {
//       tree_to_list(n->f_esq, l);
//       tree_to_list(n->f_dret, l);
//       l.push_back(n->_info);
//       return;
//     }

//     l.push_back(n->_info);
//     tree_to_list(n->f_esq, l);
//     tree_to_list(n->f_dret, l);
//     return;
//   }

//   tree_to_list(n->f_esq, l);
//   l.push_back(n->_info);
//   tree_to_list(n->f_dret, l);
// }

// bool operand(token t) // es diferent que la de es_operand(), no borrar
// {
//   if (t.tipus() == token::SUMA or t.tipus() == token::RESTA or
//       t.tipus() == token::MULTIPLICACIO or t.tipus() == token::DIVISIO or
//       t.tipus() == token::EXPONENCIACIO or
//       t.tipus() == token::CANVI_DE_SIGNE or
//       t.tipus() == token::SIGNE_POSITIU or t.tipus() == token::SQRT or
//       t.tipus() == token::LOG or t.tipus() == token::EXP)
//   {
//     return true;
//   }
//   else
//   {
//     return false;
//   }
// }

// void printl(list<token> l)
// {
//   list<token>::iterator it = l.begin();
//   while (it != l.end())
//   {
//     // cout << *it;, dona erro ja que ejn la clase de token
//     // no hi ha un operador per poder fer un cout d un token
//     // pero com que aquesta funcio crec que no es del tot necessaria
//     // ho deixo en comentari.
//     it++;
//     if (it != l.end())
//     {
//       cout << " ";
//     }
//     else
//     {
//       cout << endl;
//     }
//   }
// }
