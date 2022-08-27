#include "lexico.h"

Lexico::Lexico(string fuente)
{
    ind = 0;
    this->fuente = fuente;
}

Lexico::Lexico()
{
    ind = 0;
}

string Lexico::tipoAcad(int tipo)
{
    string cad = "";

    switch (tipo)
    {
    case TipoSimbolo::IDENTIFICADOR:
        cad = "Identificador";
        break;

    case TipoSimbolo::ENTERO:
        cad = "Entero";
        break;

    case TipoSimbolo::REAL:
        cad = "Real";
        break;

    case TipoSimbolo::CADENA:
        cad = "Cadena";
        break;

    case TipoSimbolo::TIPO:
        cad = "Tipo de Variable";
        break;

    case TipoSimbolo::OPSUMA:
        cad = "Suma";
        break;

    case TipoSimbolo::INCREMENTO:
        cad = "Incremento";
        break;

    case TipoSimbolo::OPMENOS:
        cad = "Resta";
        break;

    case TipoSimbolo::DECREMENTO:
        cad = "Decremento";
        break;

    case TipoSimbolo::OPMULT:
        cad = "Multiplicacion";
        break;

    case TipoSimbolo::OPDIVICION:
        cad = "Divicion";
        break;

    case TipoSimbolo::MODULO:
        cad = "Modulo";
        break;

    case TipoSimbolo::OPRELAC:
        cad = "Op. Relacional";
        break;

    case TipoSimbolo::OPOR:
        cad = "Op. Or";
        break;

    case TipoSimbolo::OPAND:
        cad = "Op. And";
        break;

    case TipoSimbolo::OPNOT:
        cad = "Op. Not";
        break;

    case TipoSimbolo::OPIGUALDAD:
        cad = "Igualdad";
        break;

    case TipoSimbolo::DIFERENCIA:
        cad = "Diferencia";
        break;

    case TipoSimbolo::PUNTOCOMA:
        cad = "Punto y Coma";
        break;

    case TipoSimbolo::COMA:
        cad = "Comilla";
        break;

    case TipoSimbolo::PARENTESIS:
        cad = "Parentesis";
        break;

    case TipoSimbolo::LLAVE:
        cad = "Llave";
        break;

    case TipoSimbolo::CORCHETE:
        cad = "Corchete";
        break;

    case TipoSimbolo::IGUAL:
        cad = "Igual";
        break;

    case TipoSimbolo::PALABRESERV:
        cad = "Palabra Reservada";
        break;

    case TipoSimbolo::PESOS:
        cad = "Fin de la Entrada";
        break;

    case TipoSimbolo::ERROR:
        cad = "Error";
        break;
    }

    return cad;
}

void Lexico::entrada(string fuente)
{
    ind = 0;
    this->fuente = fuente;
}

// lee simbolo en "fuente" y determina su tipo
// retorna entero que representa el tipo
// untiliza automata para determinar validez
// si deja de ser valido, retrocede puntero
int Lexico::sigSimbolo()
{

    estado = 0;
    continua = true;
    simbolo = "";

    // Inicio del Automata
    while (continua)
    {
        c = sigCaracter(); // carga siguiente caracter en c

        // Switch segun estado actual.
        // al saltar de estado, internamente se
        // concatena el caracter evaluado "c" al final de "simbolo"
        switch (estado)
        {
        case 0: // estado inicial
            // digito?
            if (c >= '0' && c <= '9')
                sigEstado(1);

            // caracter alfabetico?
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                sigEstado(3);

            else if (c == '.')
                sigEstado(5);

            else if (c == '+')
                sigEstado(6);

            else if (c == '-')
                sigEstado(13);

            else if (c == '*')
                aceptacion(7);

            else if (c == '/')
                aceptacion(20);

            else if (c == '%')
                aceptacion(21);

            else if (c == '<' || c == '>')
                sigEstado(8);

            else if (c == '|')
                sigEstado(9);

            else if (c == '&')
                sigEstado(10);

            else if (c == '!')
                sigEstado(11);

            else if (c == '=')
                sigEstado(12);

            else if (c == ';')
                aceptacion(13);

            else if (c == ',')
                aceptacion(14);

            else if (c == '(' || c == ')')
                aceptacion(15);

            else if (c == '{' || c == '}')
                aceptacion(16);

            else if (c == '[' || c == ']')
                aceptacion(25);

            else if (c == '$')
                aceptacion(50);
            // agregar default para caracteres desconocidos
            break;

        // Se llega procedente de un digito como
        // primer caracter de cadena
        case 1:
            if (c >= '0' && c <= '9')
                sigEstado(1); // si es digito, continua ciclo en estado 1
            else if (c == '.')
                sigEstado(2); // si es punto, pasa a esado
            else              // si no es digito o punto, termina ciclo
            {
                continua = false;
                retroceso(); // retrocede puntero "ind"
            }
            break;
        case 2:
            if (c >= '0' && c <= '9')
            {
                sigEstado(2);
            }
            else
            {
                continua = false;
                retroceso();
            }
            break;
        case 3:
            if ((c >= '0' && c <= '9'))
                sigEstado(3);
            else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) /*|| (c >= '0' && c <= '9')*/)
                sigEstado(4);
            else
            {
                continua = false;
                retroceso();
            }
            break;
        case 4:
            if ((c >= '0' && c <= '9'))
                sigEstado(3);
            else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) /*|| (c >= '0' && c <= '9')*/)
                sigEstado(4);
            else
            {
                continua = false;
                retroceso();
            }
            break;
        case 5:
            if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9'))
                sigEstado(5);
            else
            {
                continua = false;
                retroceso();
            }
            break;
        case 6:
            if (c == '+')
                aceptacion(22);
            else
            {
                estado = 6;
                retroceso();
            }
            break;
        case 8:
            if (c == '=')
                aceptacion(8);
            else
            {
                continua = false;
                retroceso();
            }
            break;
        case 9:
            if (c == '|')
                aceptacion(9);
            else
            {
                estado = 5;
                retroceso();
            }
            break;
        case 10:
            if (c == '&')
                aceptacion(10);
            else
            {
                estado = 5;
                retroceso();
            }
            break;
        case 11:
            if (c == '=')
                aceptacion(24);
            else
            {
                estado = 11;
                retroceso();
            }
            break;
        case 12:
            if (c == '=')
                aceptacion(12);
            else
            {
                estado = 17;
                retroceso();
            }
            break;
        case 13:
            if (c == '-')
                aceptacion(23);
            else
            {
                estado = 19;
                retroceso();
            }
        }
    }
    // Fin del Automata

    // asignamos el "tipo" segun el estado
    // en el que se termina el automata
    switch (estado)
    {
    case 1:
        tipo = TipoSimbolo::ENTERO;
        break;
    case 2:
        tipo = TipoSimbolo::REAL;
        break;
    case 3:
        tipo = TipoSimbolo::IDENTIFICADOR;
        break;
    case 4:
        if (simbolo == "int" || simbolo == "float" || simbolo == "void" ||
            simbolo == "char" || simbolo == "string" || simbolo == "bool" || simbolo == "class" || simbolo == "double" || simbolo == "struct")
            tipo = TipoSimbolo::TIPO;
        else if (simbolo == "if" || simbolo == "else" || simbolo == "while" || simbolo == "return" || simbolo == "break" || simbolo == "auto" || simbolo == "case" || simbolo == "const" || simbolo == "continue" || simbolo == "default" || simbolo == "enum" || simbolo == "extern" || simbolo == "for" || simbolo == "goto" || simbolo == "do" || simbolo == "long" || simbolo == "register" || simbolo == "short" || simbolo == "signed" || simbolo == "sizeof" || simbolo == "static" || simbolo == "switch" || simbolo == "typedef" || simbolo == "union" || simbolo == "unsigned" || simbolo == "volatile")
            tipo = TipoSimbolo::PALABRESERV;
        else
            tipo = TipoSimbolo::CADENA;
        break;
    case 5:
        tipo = TipoSimbolo::ERROR;
        break;
    case 6:
        tipo = TipoSimbolo::OPSUMA;
        break;
    case 7:
        tipo = TipoSimbolo::OPMULT;
        break;
    case 8:
        tipo = TipoSimbolo::OPRELAC;
        break;
    case 9:
        tipo = TipoSimbolo::OPOR;
        break;
    case 10:
        tipo = TipoSimbolo::OPAND;
        break;
    case 11:
        tipo = TipoSimbolo::OPNOT;
        break;
    case 12:
        tipo = TipoSimbolo::OPIGUALDAD;
        break;
    case 13:
        tipo = TipoSimbolo::PUNTOCOMA;
        break;
    case 14:
        tipo = TipoSimbolo::COMA;
        break;
    case 15:
        tipo = TipoSimbolo::PARENTESIS;
        break;
    case 16:
        tipo = TipoSimbolo::LLAVE;
        break;
    case 17:
        tipo = TipoSimbolo::IGUAL;
        break;
    case 19:
        tipo = TipoSimbolo::OPMENOS;
        break;
    case 20:
        tipo = TipoSimbolo::OPDIVICION;
        break;
    case 21:
        tipo = TipoSimbolo::MODULO;
        break;
    case 22:
        tipo = TipoSimbolo::INCREMENTO;
        break;
    case 23:
        tipo = TipoSimbolo::DECREMENTO;
        break;
    case 24:
        tipo = TipoSimbolo::DIFERENCIA;
        break;
    case 25:
        tipo = TipoSimbolo::CORCHETE;
        break;
    default:
        tipo = TipoSimbolo::PESOS;
    }

    return tipo;
}

// retorna siguiente caracter de cadena,
// si llegó a fin de cadena, retorna "$"
char Lexico::sigCaracter()
{
    if (terminado())
        return '$';
    return fuente[ind++];
}

// cambia de estado y concatena "c" a "simbolo"
void Lexico::sigEstado(int estado)
{
    this->estado = estado;
    simbolo += c;
}

// Cambia de estado y niega bandera "continua" para detener ciclo
void Lexico::aceptacion(int estado)
{
    sigEstado(estado);
    continua = false;
}

bool Lexico::terminado()
{ // es fin de cadena?
    return ind >= fuente.length();
}

bool Lexico::esLetra(char c)
{
    return isalpha(c) || c == '_';
}

bool Lexico::esDigito(char c)
{
    return isdigit(c);
}

bool Lexico::esEspacio(char c)
{
    return c == ' ' || c == '\t';
}

// cambia bandera para detener ciclo y
// retrocede puntero "ind" para solo evaluar
// mientras la cadena fue valida
void Lexico::retroceso()
{
    if (c != '$')
        ind--;
    continua = false;
}
