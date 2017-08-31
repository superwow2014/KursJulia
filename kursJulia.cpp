#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

int M,N;
int **T;
bool *working;
int minTime = -1, minPossibleTime = -1;
vector< pair<int,int> > answer, curr;
clock_t  t1,t2;

void WriteTimeAndExit()
{
	for (int i = 0; i < M; i++)
		cout << "Узел " << answer[i].first + 1 << " -> Фабрика " << answer[i].second + 1 
             << " Время: " << T[answer[i].first][answer[i].second] << "\n";
	    cout << "Минимальное время: " << minTime << endl;
	    exit(0);
}

void Rec(int level, int currMaxTime)
{
    t1 = clock();
	if (currMaxTime >= minTime)
		return;
	if (level == M)
	{
		if (currMaxTime < minTime)
		{
			answer = curr;
			minTime = currMaxTime;
			if (currMaxTime == minPossibleTime)
				WriteTimeAndExit();
		}
		return;
	}
	for (int i = 0; i < N; ++i)
		if (!working[i])
		{
			working[i] = true;
			curr.push_back({level, i});
			Rec(level + 1, max(currMaxTime, T[level][i]));
			curr.pop_back();
			working[i] = false;
		}
    t2 = clock();    	
}

int menu()
{
    int var;
    cout << "1.Заполнить данные!\n"
         << "2.Вывести данные на экран!\n"
         << "3.Решить задачу!\n"
         << "4.Выход!\n"
         << ">>> "; 
    cin >> var;
    return var;       
}

int main()
{
    setlocale(LC_ALL,"RUS");
    int temp,minTimeInRow;
    
    srand(unsigned(time(0)));
    
    start:
    switch (menu())
    {
        case 1:{
            system("cls");
            cout << "Введите кол-во узлов: ";
            cin >> N;
            cout << "Введите кол-во фабрик: ";
            cin >> M;
            T = new int*[M];
            cout << "Случайно заполнить матрицу(1) или заполнить вручную(2)?\n>>> ";
            cin >> temp;
            
            minTimeInRow = -1;
            
            working = new bool[M];

	        for (int i = 0; i < N; ++i)
	            working[i] = false;
            
            for (int i = 0; i < M; i++)
                T[i] = new int[N];
                
            if (temp == 1){
               for (int i = 0; i < M; i++){
                   for (int j = 0; j < N; j++){
                       T[i][j] = rand() % 101 + 1;
                       cout << setw(4) << T[i][j];
                       if (minTimeInRow == -1)
                           minTimeInRow = T[i][0];
                       else
                           minTimeInRow = min(minTimeInRow, T[i][j]);
                       minTime = max(minTime, T[i][j]);
                   }
                   cout << endl;
                   minPossibleTime = max(minTimeInRow, minPossibleTime);
               }
            } else {
                for (int i = 0; i < M; i++){
                   for (int j = 0; j < N; j++){
                       cin >> T[i][j];
                       if (minTimeInRow == -1)
                           minTimeInRow = T[i][0];
                       else
                           minTimeInRow = min(minTimeInRow, T[i][j]);
                       minTime = max(minTime, T[i][j]);   
                   }
                   minPossibleTime = max(minTimeInRow, minPossibleTime);
               }
            }
            cout << "Исходные данные сформированы!\n\n";
			system("pause");
			system("cls");
			goto start;
        }
        case 2:{
            system("cls");
    		cout << "Кол-во узлов = " << N
                 << "\nКол-во фабрик = " << M << endl;
            cout << "Матрица:\n";
            for (int i = 0; i < M; i++){
                for (int j = 0; j < N; j++)
                    cout << setw(4) << T[i][j];
                cout << endl;    
            }
    		system("pause");
    		system("cls");
    		goto start;
           
        }
        case 3:{
            Rec(0,0);
	        WriteTimeAndExit();
	        cout << t2 - t1 << endl;
        }
        case 4:{
            break;
        } 
        default:
	    	system("cls");
		    cout << "Вы что-то ввели не правильно! Повторите ввод! \n\n";
			goto start;	   
    }
    
    return 0;
}
