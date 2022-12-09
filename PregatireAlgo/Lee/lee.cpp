#include <iostream>
#include <fstream>
#include <queue>
#define NMAX 1000
#define MMAX 1000
using namespace std;

int a[NMAX][MMAX], dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
//-1 obstacol rest 0

struct coords
{
    int x, y;
};

void lee(int x0, int y0){
    int i, pas, xv, yv;
    queue<coords> coada;
    coada.push({x0, y0});
    a[x0][y0] = 1;
    coords actual;

    while(!coada.empty()){
        actual = coada.front();
        coada.pop(); pas = a[actual.x][actual.y];
        for(i = 0; i < 4; ++i){
            xv = actual.x + dx[i], yv = actual.y + dy[i];
            if(a[xv][yv] == 0){
                a[xv][yv] = pas + 1;
                coada.push({xv, yv});
            }
        }
    }
}
void bordare(int n, int m){
    int i;
    for(i = 0; i <= n + 1; ++i) a[i][0] = a[i][m + 1] = -1;
    for(i = 0; i <= m + 1; ++i) a[0][i] = a[n + 1][i] = -1;
}
void afisare_matrice(int n, int m){
    int i, j;
    for(i = 0; i <= n + 1; ++i){
        for(j = 0; j <= m + 1; ++j)
                if(a[i][j] == -1) cout << "| "; 
                else cout << a[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}
int main(){
    ifstream f("matrice.in");
    int n, m, i, j;
    f >> n >> m;
    for(i = 1; i <= n; ++i)
        for(j = 1; j <= m; ++j)
            f >> a[i][j];

    bordare(n, m);
    afisare_matrice(n, m);
    lee(1, 1);
    afisare_matrice(n, m);
    f.close();
}