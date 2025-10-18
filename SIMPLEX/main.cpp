#include <iostream>
using namespace std;

const int MAX = 201;

void rellenar(int filas, int columnas, double matriz[][MAX])
{
    cout<<"Ingrese los valores:\n";
    for(int i = 0; i<filas; i++){

        cout<<"\nRestriccion R"<<i+1<<"\n";

        for(int j = 0; j<columnas - 1; j++){
            cout << "Valor de X" << j + 1 << ": ";
            cin >> matriz[i][j];
        }

        cout<<"Valor del lado derecho en forma <= ";
        cin>>matriz[i][columnas - 1];
    }
}

double simplex(int filas, int columnas, double A[][MAX], double c[])
{

    int n = columnas - 1;
    int m = filas;
    int totalCols = n + m + 1;

    const int TAM = 2 * MAX;
    double tabla[TAM][TAM] = {0};

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++) tabla[i][j] = A[i][j];

        tabla[i][n + i] = 1;

        tabla[i][totalCols - 1] = A[i][n];
    }

    for(int j = 0; j < n; j++) tabla[m][j] = -c[j];

    while(true){
        int colPiv = -1;
        double minVal = 0;

        for(int j = 0; j < totalCols - 1; j++){
            if(tabla[m][j] < minVal){
                minVal = tabla[m][j];
                colPiv = j;
            }
        }

        if (colPiv == -1) break;

        int filaPiv = -1;
        double minRatio = 1e9; //auxiliar para comparar y encontrar un numero mas pequeño


        for(int i = 0; i < m; i++){
            if (tabla[i][colPiv] > 0){
                double ratio = tabla[i][totalCols - 1] / tabla[i][colPiv];

                if(ratio < minRatio){
                    minRatio = ratio;
                    filaPiv = i;
                }

            }
        }

        if(filaPiv == -1){
            cout << "Solución no acotada.\n";
            return 0;
        }

        double pivote = tabla[filaPiv][colPiv];

        for(int j = 0; j < totalCols; j++)
            tabla[filaPiv][j] /= pivote;

        for(int i = 0; i <= m; i++){
            if(i != filaPiv){
                double factor = tabla[i][colPiv];
                for (int j = 0; j < totalCols; j++)
                    tabla[i][j] -= factor * tabla[filaPiv][j];
            }
        }
    }

    return tabla[m][totalCols - 1];
}

int main()
{

    int filas, columnas;

    cout<<"Ingrese el numero restricciones: ";
    cin >>filas;
    cout<<"Ingrese el numero de variables: ";
    cin >>columnas;

    columnas++;
    cout<<"\n";


    double matriz[MAX][MAX];
    double FunObjetivo[MAX];

    rellenar(filas, columnas, matriz);

    cout<<"\nIngrese los coeficientes de la funcion objetivo Max Z = \n";

    for (int j = 0; j < columnas - 1; j++){
        cout<<"Coeficiente de X"<<j+1<<": ";
        cin>>FunObjetivo[j];
    }

    double resultado = simplex(filas, columnas, matriz, FunObjetivo);
    cout << "\nEl valor maximo de Z es: " << resultado << endl;


    return 0;
}
