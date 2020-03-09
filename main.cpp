#include <iostream>
using namespace std;

//число всех вершин (первая строка файла)
int vertices = 0;
//входная матрица
int **matrixInput;
//выходная матрица
int **matrixOutput;
//таблица путей
int **tableRoutes;
//хранит значения сечений всех путей
int *section;

//рекурсивно ищет все пути
void findRoute(int x, int y, int min, int * route)
{
    if(x == (vertices - 1))
    {
        for(int a = 0; a < vertices; a++)
            if(route[a] == 0)
            {
                route[a] = x+1;
                cout << route[a];

                for(int i = 0; i < (vertices*vertices); i++)
                    if(tableRoutes[i][0] == 0)
                    {
                        for(int j = 0; j < vertices; j++)
                            tableRoutes[i][j] = route[j];
                        section[i] = min;
                        break;
                    }
                break;
            }
            else cout << route[a];
        cout << "\t" << min << endl;
    }
    else {
        for(int i = 0; i < vertices; i++)
            if(route[i] == 0)
            {
                route[i] = x+1;
                break;
            }
        while(y < vertices)
        {
            if(matrixInput[x][y] > 0)
            {
                int * duplicate = new int[vertices];
                for(int i = 0; i < vertices; i++)
                    duplicate[i] = route[i];

                if(matrixInput[x][y] < min) findRoute(y,y, matrixInput[x][y], route);
                else findRoute(y,y, min, route);

                for(int i = 0; i < vertices; i++)
                    route[i] = duplicate[i];

                delete[] duplicate;
            }
            y++;
        }
    }
}

//строит выходную таблицу от путей с наибольшим сечением
void findOptimalRouteMax()
{
    int max = -1;
    int coord = 0;

    while(max != 0)
    {
        for(int i = 0; i < (vertices * vertices); i++)
            if(section[i] > max)
            {
                max = section[i];
                coord = i;
            }

        if(max != 0)
        {
            int approach;
            while(max != 0)
            {
                approach = 0;
                for(int i = 0; i < vertices-1; i++)
                    if(tableRoutes[coord][i+1] != 0)
                    {
                        if(max <= (matrixInput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1] - matrixOutput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1]))
                        {
                            approach++;
                        }
                        else
                        {
                            approach = -100;
                        }
                    }

                if(approach > 0)
                {
                    for(int i = 0; i < vertices-1; i++)
                        if(tableRoutes[coord][i+1] != 0)
                        {
                            matrixOutput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1] += max;
                        }
                max = 1;
                }

            max--;
            }
            for(int j = 0; j < vertices; j++)
                tableRoutes[coord][j] = 0;
            section[coord] = 0;
            max = -1;
        }
        else
        {
            return;
        }
    }
}

//строит выходную таблицу от путей с наименьшим сечением
void findOptimalRouteMin()
{
    int min = 1000;
    int coord = 0;

    while(min != -1)
    {
        for(int i = 0; i < (vertices * vertices); i++)
            if(section[i] != 0 && section[i] < min)
            {
                min = section[i];
                coord = i;
            }

        if(min != 1000)
        {
            int approach;
            while(min != 0)
            {
                approach = 0;
                for(int i = 0; i < vertices-1; i++)
                    if(tableRoutes[coord][i+1] != 0)
                    {
                        if(min <= (matrixInput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1] - matrixOutput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1]))
                        {
                            approach++;
                        }
                        else
                        {
                            approach = -100;
                        }
                    }

                if(approach > 0)
                {
                    for(int i = 0; i < vertices-1; i++)
                        if(tableRoutes[coord][i+1] != 0)
                        {
                            matrixOutput[tableRoutes[coord][i]-1][tableRoutes[coord][i+1]-1] += min;
                        }
                min = 1;
                }

            min--;
            }
            for(int j = 0; j < vertices; j++)
                tableRoutes[coord][j] = 0;
            section[coord] = 0;
            min = 1000;
        }
        else
        {
            return;
        }
    }
}

//вывод выходной и остаточной матрицы
void printMatrixOutput()
{
    cout << "\nOutput matrix-----------------------------------------------\n";
    for(int i = 0; i < vertices; i++)
        cout <<  "\t" << i + 1;
    cout << endl;
    for(int i = 0; i < vertices; i++)
    {
        cout << i + 1;
        for(int j = 0; j < vertices; j++)
        {
            cout << "\t" << matrixOutput[i][j];
        }
        cout << endl;
    }

    cout << "\nResidual matrix-----------------------------------------------\n";
    for(int i = 0; i < vertices; i++)
        cout <<  "\t" << i + 1;
    cout << endl;
    for(int i = 0; i < vertices; i++)
    {
        cout << i + 1;
        for(int j = 0; j < vertices; j++)
        {
            cout << "\t" << (matrixInput[i][j] - matrixOutput[i][j]);
        }
        cout << endl;
    }
}

int main()
{
    //чтение из файла
    freopen("../Ford-Fulkerson_Algorithm/matrix.txt", "r",stdin);

    //инициализация и заполнение входной матрицы
    cin >> vertices;
    cout << "number of vertices: " << vertices << "\n";

    matrixInput = new int *[vertices];
    for(int i = 0; i < vertices; i++)
        matrixInput[i] = new int [vertices];

    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
        {
            cin >> matrixInput[i][j];
        }

    //вывод входной матрицы
    for(int i = 0; i < vertices; i++)
        cout <<  "\t" << i + 1;
    cout << endl;
    for(int i = 0; i < vertices; i++)
    {
        cout << i + 1;
        for(int j = 0; j < vertices; j++)
        {
            cout << "\t" << matrixInput[i][j];
        }
        cout << "\n";
    }

    //инициализация выходной матрицы
    matrixOutput = new int *[vertices];
    for(int i = 0; i < vertices; i++)
        matrixOutput[i] = new int [vertices];

    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
        {
            matrixOutput[i][j] = 0;
        }

    //инициализация таблицы путей
    tableRoutes = new int *[(vertices*vertices)];
    for(int i = 0; i < (vertices*vertices); i++)
        tableRoutes[i] = new int [vertices];

    for(int i = 0; i < (vertices*vertices); i++)
        for(int j = 0; j < vertices; j++)
        {
            tableRoutes[i][j] = 0;
        }

    //иницализация значений сечений всех путей
    section = new int[(vertices*vertices)];
    for(int i = 0; i < (vertices*vertices); i++)
        section[i] = 0;

    //инициализация начального пути
    int *route = new int[vertices];
    for(int i = 0; i < vertices; i++)
        route[i] = 0;

    //поиск путей
    cout << "\nRoutes:\n";
    findRoute(0,0,1000, route);

    //Сохраняем найденные пути и их сечения
    int **duplicateTableRoutes = new int *[(vertices*vertices)];
    for(int i = 0; i < (vertices*vertices); i++)
        duplicateTableRoutes[i] = new int [vertices];

    for(int i = 0; i < (vertices*vertices); i++)
        for(int j = 0; j < vertices; j++)
        {
            duplicateTableRoutes[i][j] = tableRoutes[i][j];
        }

    int * duplicateSection = new int[(vertices*vertices)];
    for(int i = 0; i < (vertices*vertices); i++)
        duplicateSection[i] = section[i];

    //ищем от наибольшего
    cout << "\nsearch from the biggest";
    findOptimalRouteMax();
    printMatrixOutput();

    //восстанавливаем найденные пути, их значения и освобождаем память дублирующих
    for(int i = 0; i < (vertices*vertices); i++)
        for(int j = 0; j < vertices; j++)
        {
            tableRoutes[i][j] = duplicateTableRoutes[i][j];
        }

    for(int i = 0; i < (vertices*vertices); i++)
        section[i] = duplicateSection[i];

    for(int i = 0; i < (vertices*vertices); i++)
        delete[] duplicateTableRoutes[i];
    delete[] duplicateSection;

    //обнуляем выходную матрицу
    for(int  i = 0; i < vertices; i++)
        for(int j = 0; j < vertices; j++)
            matrixOutput[i][j] = 0;

    //ищем от наименьшего
    cout << "\nsearch from the smallest";
    findOptimalRouteMin();
    printMatrixOutput();


    delete[] route;
    delete[] section;
    for(int i = 0; i < vertices; i++)
    {
        delete[] matrixInput[i];
        delete[] matrixOutput[i];
    }

    for(int i = 0; i < (vertices*vertices); i++)
        delete[] tableRoutes[i];

}
