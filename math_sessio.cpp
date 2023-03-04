#include "math_sessio.hpp"
#include "math_io.hpp"
#include <algorithm>

math_sessio::math_sessio() throw(error)
{
  expressio buida;
  _sessio.assign("%", buida);
  final = false;
}

// Constructora per còpia, assignació i destructora.
math_sessio::math_sessio(const math_sessio &es) throw(error)
{
  _sessio = es._sessio;
}
math_sessio &math_sessio::operator=(const math_sessio &es) throw(error)
{
  if (this == &es)
  {
    return *this;
  }

  _sessio = es._sessio;
  final = es.final;
  return *this;
}

math_sessio::~math_sessio() throw(error)
{
  math_sessio buida;
  _sessio = buida._sessio;
  final = false;
}

/* Aquest mètode rep una llista de tokens, lin, lèxicament correcta.
   Primerament analitza parcialment lin per verificar si la comanda és
   correcta. Si és correcta executa la comanda que conté lin.
   Les comandes són:
    * avaluació d'una expressió E.
    * assignació v :=  E. S'avalua E i s'assigna el resultat a la variable
      de nom v.
    * desassignació d'una variable v: unassign v.
    * final de sessió: byebye

   En l'anàlisi de la comanda lin es produeix un error de comanda
   incorrecta en els següents casos:
    * si conté el token DESASSIGNACIO i,
      * o bé la comanda no té dos tokens
      * o bé aquest no és el primer token
      * o bé el segon token no és una VARIABLE.
    * si conté el token BYEBYE i aquest no és el primer i únic token
      de la comanda.
    * si conté el token ASSIGNACIO i,
      * o bé la comanda té longitud menor que dos
      * o bé no és el segon token
      * o bé el primer token no és un token VARIABLE.

   Les comandes que involucren avaluació (avaluar i assignar) retornen
   l'expressió avaluada en forma de llista de tokens en lout. La comanda
   unassign retorna la llista que conté com únic token la variable
   desassignada. Finalment la comanda byebye retorna la llista buida.
   Es produeix un error en una assignació, si després l'avaluació de
   l'expressió es comprova que la variable assignada forma part del conjunt
   de variables de l'expressió avaluada, tal i com s'explica a
   l'apartat "Procés d'avaluació". */
void math_sessio::execute(const list<token> &lin, list<token> &lout) throw(error)
{
  if (lin.empty())
    return;
  list<token> llista = lin;
  list<token>::iterator it = llista.begin();
  if (it->tipus() == token::DESASSIGNACIO)
  {
    if (llista.size() != 2)
    {
      throw error(SintComandaIncorrecta);
    }
    std::advance(it, 1);
    if (it->tipus() != token::VARIABLE)
    {
      throw error(SintComandaIncorrecta);
    }
    _sessio.unassign(it->identificador_variable());
  }
  else if (it->tipus() == token::BYEBYE)
  {
    if (llista.size() != 1)
    {
      throw error(SintComandaIncorrecta);
    }
    final = true;
    // no se com finalitzar la sessio
  }
  else if (it->tipus() == token::VARIABLE)
  {
    token var = *it;
    std::advance(it, 1);
    if ((llista.size() < 2) or (it->tipus() == token::ASSIGNACIO))
    {
      throw error(SintComandaIncorrecta);
    }
    std::advance(it, 1);
    expressio eavaluar = *it;
    // primer s ha d avaluar evauluar, i despres s ha d assignar la variable.
    list<token> infinit;
    eavaluar.list_of_tokens(infinit);
    list<token>::iterator id;
    id = std::find(infinit.begin(), infinit.end(), *it);
    if (it == infinit.end())
    {
      throw error(AssigAmbCirculInfinita);
    }
    _sessio.assign(it->identificador_variable(), eavaluar);
  }
  else if (it->tipus() == token::EVALF)
  {
    std::advance(it, 1);
    // no tinc ni puta idea com collons s avalua;
  }
  else
  {
    throw error(SintComandaIncorrecta);
  }
}

// Retorna cert si i només si la sessió ha finalitzat.
bool math_sessio::end_of_session() const throw()
{
  return final;
}

/* Retorna en forma de llista d'strings, en un ordre qualsevol, la llista de
   variables juntament amb el seu valor assignat. Cada string de la llista
   té el format id = e, on id és el nom d'una variable i e és l'expressió
   (com string) assignada a id. Convertim una expressió e en el seu string
   corresponent invocant al mètode tostring del mòdul esinmath_io. */
void math_sessio::dump(list<string> &l) const throw(error)
{
  list<string> claus;
  _sessio.dump(claus);
  for (list<string>::iterator it = claus.begin(); it != claus.end(); it++)
  {
    l.push_back(*it);
    expressio exp = _sessio.valor(*it);
    list<token> lt;
    exp.list_of_tokens(lt);
    // l.push_back(math_io::tostring(lt)); // aqui dona error i no entenc pq
    //  ns com fer la merda aquesta de tostring, si no es aixi
    //  pq en el .hpp ja esta fet l include
  }
}

void afegir(list<token> &lt) // afegeix els parentesis al principi i al
                              // al final de la expressio feta llista
{
  token obert("(");
  token tancat(")");
  lt.push_front(obert);
  lt.push_back(tancat);
}

/* Donada una expressió e, aplica a les seves variables totes les
   substitucions definides per elles. L'expressió resultant només contindrà
   variables per les quals no hi ha substitució definida (no estan en el
   conjunt). Aquest procés s'explica en detall a l'apartat "Procés
   d'avaluació". S'assumeix que no existeix circularitat infinita entre les
   substitucions de les variables que formen part de l'expressió e. */
void math_sessio::apply_all_substitutions(expressio &e) const throw(error)
{
  // quan substitueixes algo, d una variable, sempre es posa en parentesis
  // i aquesta funcio fa aixo, substitueix la variable per la seva expressio.
  list<string> infinit;
  list<string> claus;
  _sessio.dump(claus);
  list<token> expre;
  e.list_of_tokens(expre);
  for (list<token>::iterator it = expre.begin(); it != expre.end(); it++)
  {
    if (it->tipus() == token::VARIABLE)
    {
      list<string>::iterator at;
      string var = it->identificador_variable();
      at = find(infinit.begin(), infinit.end(), var);
      if (at != infinit.end())
      {
        // si dona error en aquesta funcio, fes aquest find amb un altre nom de la variable
        // no hauria de donar cap error per aixo
        at = find(claus.begin(), claus.end(), var);
        if (at != claus.end())
        {
          // Variable has a substitution defined
          expressio ins = _sessio.valor(var);
          list<token> sub;
          ins.list_of_tokens(sub);
          afegir(sub); // afegeix els parenthesis
          list<token>::iterator it;
          it = expre.insert(it, sub.begin(), sub.end());
          infinit.push_front(var);
          expre.erase(it);
          // advance(it, sub.size()); no es fa aixo, pq aixi es recorre un altre
          // cop, el que acabem de posar i es comprova que no sigui infinit.
        }
      } else {
        throw error(SintComandaIncorrecta);
      }
    }
  }
}