#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.h"

using namespace std;

int main(int argc, char *argv[])
{

    int a = 0;
    // lexico.entrada("b aa33.33 1556 275.12 Hola int char float void string class bool +- */ <=>>=< || && ! !=== ; ,"
    //                "() {} = if else while return .632");

    while (a == 0)
    {

        Lexico lexico;
        string palabra;
        cout << "\nEscribe algo: ";
        getline(cin, palabra);
        lexico.entrada(palabra); // Guarda palabra en variable interna "fuente"
        cout << palabra << endl;

        cout << "\nResultado del Analisis Lexico" << endl
             << endl;
        cout << "Simbolo\t\tTipo" << endl;

        while (lexico.simbolo.compare("$") != 0)
        {
            lexico.sigSimbolo();
            cout << lexico.simbolo << "\t\t" << lexico.tipoAcad(lexico.tipo) << endl;
        }

        // cin.get();
    }

    return 0;
}
