#include "lexico.h"

  Lexico::Lexico(string fuente){
    ind= 0;
    this->fuente= fuente;
  }

  Lexico::Lexico(){
    ind= 0;
  }

  string Lexico::tipoAcad(int tipo){
         string cad= "";

         switch (tipo){
           case TipoSimbolo::IDENTIFICADOR:
                cad= "Identificador";
                break;

           case TipoSimbolo::ENTERO:
                cad= "Entero";
                break;

           case TipoSimbolo::REAL:
                cad= "Real";
                break;

           case TipoSimbolo::CADENA:
                cad="Cadena";
                break;

            case TipoSimbolo::TIPO:
                cad= "Tipo de Variable";
                break;

           case TipoSimbolo::OPSUMA:
                cad= "Op. Suma";
                break;

           case TipoSimbolo::OPMENOS:
                cad= "Op. resta";
                break;

           case TipoSimbolo::OPMULT:
                cad= "Op. Multiplicacion";
                break;

           case TipoSimbolo::OPRELAC:
                cad= "Op. Relacional";
                break;

            case TipoSimbolo::OPOR:
                cad= "Op. Or";
                break;

            case TipoSimbolo::OPAND:
                cad= "Op. And";
                break;

            case TipoSimbolo::OPNOT:
                cad= "Op. Not";
                break;

            case TipoSimbolo::OPIGUALDAD:
                cad= "Op. Igualdad";
                break;

            case TipoSimbolo::PUNTOCOMA:
                cad= "Punto y Coma";
                break;

            case TipoSimbolo::COMA:
                cad= "Comilla";
                break;

            case TipoSimbolo::PARENTESIS:
                cad= "Parentesis";
                break;

            case TipoSimbolo::LLAVE:
                cad= "Llave";
                break;

            case TipoSimbolo::IGUAL:
                cad= "Igual";
                break;

            case TipoSimbolo::PALABRESERV:
                cad= "Palabra Reservada";
                break;

           case TipoSimbolo::PESOS:
                cad= "Fin de la Entrada";
                break;

           case TipoSimbolo::ERROR:
                cad= "Error";
                break;

         }

         return cad;
  }

  void Lexico::entrada(string fuente){
      ind= 0;
      this->fuente= fuente;
  }

int Lexico::sigSimbolo(){

    estado=0;
    continua= true;
    simbolo= "";


    //Inicio del Automata
    while (continua){
      c= sigCaracter();

      switch (estado){
        case 0:
             if ( c >= '0' && c <= '9')
                 sigEstado(1);

             else if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
                 sigEstado(3);

             else if( c == '.')
                 sigEstado(5);

             else if( c == '+')
                 aceptacion(6);

             else if(c == '-')
                 aceptacion(19);

             else if( c == '*' || c == '/')
                 aceptacion(7);

             else if( c == '<' || c == '>')
                 sigEstado(8);

             else if( c == '|')
                 sigEstado(9);

             else if( c == '&')
                 sigEstado(10);

             else if( c == '!')
                 sigEstado(11);

             else if( c == '=')
                 sigEstado(12);

             else if( c == ';')
                 aceptacion(13);

             else if( c == ',')
                 aceptacion(14);

             else if ( c == '(' || c == ')')
                 aceptacion(15);

             else if ( c == '{' || c == '}')
                 aceptacion(16);

             else if( c == '$')
                 aceptacion(23);

          break;
        case 1:
              if ( c >= '0' && c <= '9')
                  sigEstado(1);
              else if( c == '.')
                    sigEstado(2);
              else{
                    continua = false;
                    retroceso();
                  }
          break;
        case 2:
              if ( c >= '0' && c <= '9')
              {
                  sigEstado(2);
              }
              else{
                  continua = false;
                  retroceso();
              }
          break;
        case 3:
              if ((c >= '0' && c <= '9'))
                  sigEstado(3);
              else if( ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) /*|| (c >= '0' && c <= '9')*/ )
                  sigEstado(4);
              else{
                  continua = false;
                  retroceso();
              }
          break;
        case 4:
              if ((c >= '0' && c <= '9'))
                  sigEstado(3);
              else if( ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) /*|| (c >= '0' && c <= '9')*/ )
                  sigEstado(4);
              else{
                  continua = false;
                  retroceso();
                }
           break;
        case 5:
              if( ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) || (c >= '0' && c <= '9') )
                  sigEstado(5);
              else{
                  continua = false;
                  retroceso();
              }
           break;
        case 8:
              if( c == '=')
                  aceptacion(8);
              else
              {
                  continua = false;
                  retroceso();
              }
           break;
        case 9:
              if( c == '|')
                  aceptacion(9);
              else
              {
                  estado = 5;
                  retroceso();
              }
           break;
        case 10:
               if( c == '&')
                 aceptacion(10);
               else
               {
                   estado = 5;
                   retroceso();
               }
           break;
        case 11:
               if( c == '=')
                   aceptacion(12);
               else
               {
                   estado = 11;
                   retroceso();
               }
           break;
        case 12:
             if( c == '=')
                 aceptacion(12);
             else
             {
                 estado = 17;
                 retroceso();
             }
           break;

      }

   }
    //Fin del Automata

      switch (estado){

        case 1:
              tipo=TipoSimbolo::ENTERO;
              break;
        case 2:
              tipo= TipoSimbolo::REAL;
              break;
        case 3:
              tipo= TipoSimbolo::IDENTIFICADOR;
              break;
        case 4:
              if(simbolo == "int" || simbolo == "float" || simbolo == "void" ||
                      simbolo == "char" || simbolo == "string" || simbolo == "bool"
                      || simbolo == "class")
                  tipo= TipoSimbolo::TIPO;
              else if (simbolo == "if" || simbolo == "else" || simbolo == "while"
                       || simbolo == "return")
                  tipo= TipoSimbolo::PALABRESERV;
              else
                  tipo= TipoSimbolo::CADENA;
              break;
        case 5:
              tipo= TipoSimbolo::ERROR;
              break;
        case 6:
              tipo= TipoSimbolo::OPSUMA;
              break;
        case 7:
             tipo= TipoSimbolo::OPMULT;
             break;
        case 8:
             tipo= TipoSimbolo::OPRELAC;
             break;
        case 9:
             tipo= TipoSimbolo::OPOR;
             break;
        case 10:
             tipo= TipoSimbolo::OPAND;
             break;
        case 11:
             tipo= TipoSimbolo::OPNOT;
             break;
        case 12:
             tipo= TipoSimbolo::OPIGUALDAD;
             break;
        case 13:
             tipo= TipoSimbolo::PUNTOCOMA;
             break;
        case 14:
             tipo= TipoSimbolo::COMA;
             break;
        case 15:
             tipo= TipoSimbolo::PARENTESIS;
             break;
        case 16:
             tipo= TipoSimbolo::LLAVE;
             break;
        case 17:
             tipo= TipoSimbolo::IGUAL;
             break;
        case 19:
             tipo= TipoSimbolo::OPMENOS;
             break;
        default:
              tipo= TipoSimbolo::PESOS;
      }

    return tipo;
}

 char Lexico::sigCaracter(){
      if (terminado()) return '$';
      return fuente[ind++];
 }

  void Lexico::sigEstado(int estado){
       this->estado= estado;
       simbolo+= c;
  }

  void Lexico::aceptacion(int estado){
       sigEstado(estado);
       continua= false;
  }

  bool Lexico::terminado(){//fin de cadena
         return ind >= fuente.length();
  }

   bool Lexico::esLetra(char c){
        return isalpha(c) || c=='_';
   }


   bool Lexico::esDigito(char c){
        return isdigit(c);
   }

   bool Lexico::esEspacio(char c){
        return c== ' ' || c== '\t';
   }


   void Lexico::retroceso(){
      if ( c != '$') ind--;
        continua= false;
    }
