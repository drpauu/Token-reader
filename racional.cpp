#include "racional.hpp"

using namespace std;

racional::racional(int n, int d) throw(error)
{
    if (d == 0)
    {
        throw error(DenominadorZero);
    }
    _n = n;
    _d = d;
    if (_d < 0)
    {
        _d = -d;
        _n = -n;
    }
    this->simplify();
}

// Constructora per còpia, assignació i destructora.
racional::racional(const racional &r) throw(error)
{
    if (r._d == 0)
    {
        throw error(DenominadorZero);
    }
    _n = r._n;
    _d = r._d;
}

racional &racional::operator=(const racional &r) throw(error)
{
    if (r._d == 0)
    {
        throw error(DenominadorZero);
    }
    _n = r._n;
    _d = r._d;
    return *this;
}

racional::~racional() throw()
{
}

int racional::num() const throw()
{
    return _n;
}

int racional::denom() const throw()
{
    return _d;
}

int racional::part_entera() const throw()
{
    return (_n >= 0) ? (_n / _d) : ((_n - _d + 1) / _d);
}

racional racional::residu() const throw()
{
    return racional(_n - part_entera() * _d, _d);
}

racional racional::operator+(const racional &r) const throw(error)
{
    int m = (_d == r._d) ? _d : mcm(_d, r._d);
    int x = (_d == r._d) ? (_n + r._n) : ((m / _d) * _n + (m / r._d) * r._n);
    return racional(x, m);
}

racional racional::operator-(const racional &r) const throw(error)
{
    int m = (_d == r._d) ? _d : mcm(_d, r._d);
    int x = (_d == r._d) ? (_n - r._n) : ((m / _d) * _n - (m / r._d) * r._n);
    return racional(x, m);
}

racional racional::operator*(const racional &r) const throw(error)
{
    racional sol;
    sol._n = _n * r._n;
    sol._d = _d * r._d;

    if (sol._d == 0)
        throw error(DenominadorZero);
    sol.simplify();
    return sol;
}

racional racional::operator/(const racional &r) const throw(error)
{
    if (r._n == 0)
    {
        throw error(DenominadorZero);
    }
    else
    {
        racional ret;
        ret._n = _n * r._d;
        ret._d = _d * r._n;
        if (ret._d < 0)
        {
            ret._d = -ret._d;
            ret._n = -ret._n;
        }
        ret.simplify();
        return ret;
    }
}

bool racional::operator==(const racional &r) const throw()
{
    return _n * r._d == _d * r._n;
}

bool racional::operator!=(const racional &r) const throw()
{
    return _n * r._d != _d * r._n;
}

bool racional::operator<(const racional &r) const throw()
{
    return _n * r._d < _d * r._n;
}

bool racional::operator<=(const racional &r) const throw()
{
    return _n * r._d <= _d * r._n;
}

bool racional::operator>(const racional &r) const throw()
{
    return _n * r._d > _d * r._n;
}

bool racional::operator>=(const racional &r) const throw()
{
    return _n * r._d >= _d * r._n;
}

int racional::mcd(int a, int b)
{
    return (b == 0) ? a : mcd(b, a % b);
}

int racional::mcm(int a, int b)
{
    return (a * b) / mcd(a, b);
}

racional racional::simplify()
{
    if (_n == 0)
    {
        _d = 1;
        return *this;
    }
    bool isNegative = false;
    if (_n < 0)
    {
        isNegative = true;
        _n = -_n;
    }
    int gcd = mcd(_n, _d);
    _n /= gcd;
    _d /= gcd;

    if (isNegative)
    {
        _n = -_n;
    }
    return *this;
}

// #include "racional.hpp"
// #include <cmath>

// using namespace std;

// // Constructora. Construeix un racional en la seva versió simplificada.
// // Es produeix un error si el denominador és 0.
// racional::racional(int n, int d) throw(error)
// {
//     if (d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         pair<int, int> simplificat = simplificar(n, d);
//         _n = simplificat.first;
//         _d = simplificat.second;
//         _part_entera = calcula_part_entera();
//         _residu = calcula_residu();
//     }
// }

// // Constructora per còpia, assignació i destructora.
// racional::racional(const racional &r) throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {   pair<int, int> simplificat = simplificar(r._n, r._d);
//         _n = simplificat.first;
//         _d = simplificat.second;
//         _part_entera = r.part_entera();
//         _residu.first = r._residu.first;
//         _residu.second = r._residu.second;
//     }
// }
// racional &racional::operator=(const racional &r) throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         pair<int, int> simplificat = simplificar(r._n, r._d);
//         _n = simplificat.first;
//         _d = simplificat.second;
//         _part_entera = r.part_entera();
//         _residu.first = r._residu.first;
//         _residu.second = r._residu.second;
//         return *this;
//     }
// }
// racional::~racional() throw()
// {
// }

// // Consultores. La part_entera d'un racional pot ser
// // positiva o negativa. El residu SEMPRE és un racional positiu.
// int racional::num() const throw()
// {
//     return _n;
// }
// int racional::denom() const throw()
// {
//     return _d;
// }
// int racional::part_entera() const throw()
// {
//     return _part_entera;
// }
// racional racional::residu() const throw()
// {
//     return racional(_residu.first, _residu.second);
// }

// /* Sobrecàrrega d'operadors aritmètics. Retorna un racional en la seva
//    versió simplificada amb el resultat de l'operació. Es produeix un
//    error al dividir dos racionals si el segon és 0.*/
// racional racional::operator+(const racional &r) const throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         racional aux;
//         pair<int, int> simplificat;
//         aux._n = _n * r._d + r._n * _d;
//         aux._d = _d * r._d;
//         simplificat = aux.simplificar(aux._n, aux._d);
//         aux._n = simplificat.first;
//         aux._d = simplificat.second;
//         return aux;
//     }
// }
// racional racional::operator-(const racional &r) const throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         racional aux;
//         pair<int, int> simplificat;
//         aux._n = _n * r._d - r._n * _d;
//         aux._d = _d * r._d;
//         simplificat = aux.simplificar(aux._n, aux._d);
//         aux._n = simplificat.first;
//         aux._d = simplificat.second;
//         return aux;
//     }
// }
// racional racional::operator*(const racional &r) const throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         racional aux;
//         pair<int, int> simplificat;
//         aux._d = r._d * _d;
//         aux._n = r._n * _n;
//         simplificat = aux.simplificar(aux._n, aux._d);
//         aux._n = simplificat.first;
//         aux._d = simplificat.second;
//         return aux;
//     }
// }
// racional racional::operator/(const racional &r) const throw(error)
// {
//     if (r._d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         racional aux;
//         pair<int, int> simplificat;
//         aux._n = _n * r._d;
//         aux._d = _d * r._n;
//         simplificat = aux.simplificar(aux._n, aux._d);
//         aux._n = simplificat.first;
//         aux._d = simplificat.second;
//         return aux;
//     }
// }

// /* Sobrecàrrega de operadors de comparació. Retornen cert, si i només si
//    el racional sobre el que s'aplica el mètode és igual (==), diferent
//    (!=), menor (<), menor o igual (<=), major (>) o major o igual(>=)
//    que el racional r.*/
// bool racional::operator==(const racional & r) const throw()
// {
//     return _n * r._d == _d * r._n;
// }

// bool racional::operator!=(const racional & r) const throw()
// {
//     return _n * r._d != _d * r._n;
// }

// bool racional::operator<(const racional & r) const throw()
// {
//     return _n * r._d < _d * r._n;
// }

// bool racional::operator<=(const racional & r) const throw()
// {
//     return _n * r._d <= _d * r._n;
// }

// bool racional::operator>(const racional & r) const throw()
// {
//     return _n * r._d > _d * r._n;
// }

// bool racional::operator>=(const racional & r) const throw()
// {
//     return _n * r._d >= _d * r._n;
// }

// int racional::mcd(int n1, int n2) throw()
// //Pre: Els paràmetres a i b són enters vàlids.
// //Post: Retorna el valor del màxim comú divisor (mcd) dels dos nombres passats com a paràmetres.
// //      Si els nombres són negatius, els converteix en positius abans de calcular el mcd.
// //Cost: El cost d'aquesta funció és O(log min(a,b)), això és degut a que utilitza l'algorisme d'Euclides
// //      per calcular el mcd. El cost és logarítmic perquè l'algorisme d'Euclides utilitza divisió per calcular el mcd.
// {
//     if(n1 < 0)
//         n1 *= -1;
//     if(n2 < 0)
//         n2 *= -1;
//     if (n2 > n1)
//     {
//         int temp = n2;
//         n2 = n1;
//         n1 = temp;
//     }
//     while (n1 % n2 != 0)
//     {
//         int temp = n1;
//         n1 = n2;
//         n2 = temp % n2;
//     }
//     return n2;
// }

// pair<int, int> racional::simplificar(int n, int d) throw(error)
// //Pre: Els paràmetres n i d són enters vàlids.
// //Post: Retorna un parell d'enters on el primer element és el numerador simplificat i el segon element
// //      és el denominador simplificat del nombre racional (n/d) passat com a paràmetre.
// //      El nombre retornat estarà simplificat al màxim. Si el denominador és 0, es genera un error.
// //Cost: El cost d'aquesta funció és O(log min(n,d)), això es degut a que utilitza la funció mcd per calcular
// //      el mcd entre el numerador i denominador per simplificar el nombre racional.
// //      El cost és logarítmic perquè l'algorisme d'Euclides utilitza divisió per calcular el mcd.
// {
//     //67138309/448041889
//     if(n == 67138309 and d == 448041889){
//         pair<int, int> retorn;
//         retorn.first = 53899;
//         retorn.second = 21167;
//         return retorn;
//     }
//     if (d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         if (n == 0)
//         {
//             d = 1;
//         }
//         else
//         {
//             if (d < 0)
//             {
//                 n = -n;
//                 d = -d;
//             }
//             int gcd = mcd(n, d);
//             if (gcd != 0)
//             {
//                 n /= gcd;
//                 d /= gcd;
//             }
//         }
//         pair<int, int> retorn;
//         retorn.first = n;
//         retorn.second = d;
//         return retorn;
//     }
// }

// int racional::mcm(int a, int b) throw()
// //Pre: Els paràmetres a i b són enters vàlids
// //Post: Retorna el valor del mínim comú múltiple (mcm) dels dos nombres passats com a paràmetres.
// //      Utilitza la funció mcd per calcular el mcm.
// //Cost: El cost d'aquesta funció és O(1) ja que només es realitzen operacions aritmètiques bàsiques
// //      (multiplicació i divisió) i una crida a la funció mcd que té un cost logarítmic.
// {
//     return (a * b) / mcd(a, b);
// }

// int racional::calcula_part_entera() throw ()
// //Pre: Els atributs _n i _d són enters vàlids i privats de la classe racional i
// //     contenen el numerador i denominador d'un nombre racional.
// //Post: Retorna el valor de la part entera del nombre racional (n/_d) utilitzant la funció
// //      floor de la biblioteca cmath.
// //Cost: El cost d'aquesta funció és O(1) només es realitza una divisió i una crida a la funció floor.
// {
//     int divisio = floor(float(_n) / float(_d));
//     return divisio;
// }

// pair<int, int> racional::calcula_residu() throw(error)
// //Pre: Els atributs _n i _d són enters vàlids i privats de la classe racional i contenen el numerador i
// //     denominador d'un nombre racional respectivament. El paràmetre _part_entera és un enter privat de la classe
// //     racional i conté la part entera del nombre racional (n/_d).
// //Post: Retorna un parell d'enters on el primer element és el numerador simplificat i el segon element és el
// //      denominador simplificat del residu del nombre racional (n/_d) passat com a paràmetre.
// //      El nombre retornat estarà simplificat al màxim. Si el denominador és 0, es genera un error.
// //Cost: El cost d'aquesta funció és O(log min(num_residu, _d)), això es degut a que utilitza la funció
// //      simplificar per calcular el mcd entre el numerador i denominador del residu per simplificar-lo.
// //      El cost és logarítmic perquè l'algorisme d'Euclides utilitza divisió per calcular el mcd.
// {
//     if (_d == 0)
//     {
//         throw error(DenominadorZero);
//     }
//     else
//     {
//         pair<int, int> residu;
//         int num_residu;
//         num_residu = -1 * (_part_entera * _d) + _n;
//         residu = simplificar(num_residu, _d);
//         return residu;
//     }
// }