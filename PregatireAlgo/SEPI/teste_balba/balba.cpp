#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
    int option, n, ultim = -1, penultim = -1;
    ifstream in("input.test_2_11");
    ofstream out("balba.out");

    in >> option >> n;
    
    if(option == 1){
        int numar_copii = 0, numar_unic = 0;
        bool consecutive = 0;
        while(n--){
            in >> ultim;

            if(ultim != penultim){
                numar_unic++;
                numar_copii += consecutive;
                consecutive = 0;
            }
            else consecutive = 1;

            penultim = ultim;
        }
        numar_copii += consecutive;
        
        cout << "Cerinta 1\n";
        out << numar_unic << "\n" << numar_copii;
    }
    else{
        cout << "Cerinta 2\n";
        int frecventa[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, x, i, j, jum;
        while(n--) in >> x, frecventa[x]++;
        bool balba_folosita = 0;
        for(i = 9; i >=0; --i){
            if(frecventa[i] & 1)
                if(balba_folosita){
                    frecventa[i] = 0;
                    continue;
                }
                else balba_folosita = 1;
            jum = ceil(frecventa[i] / 2.0);
            for(j = 0; j < jum; ++j) out << i;
            frecventa[i] -= jum;
        }
        for(i = 0; i < 10; ++i){
            for(j = 0; j < frecventa[i]; ++j)
                out << i;
        }
        out << '\n';
    }

    in.close();
    out.close();
    return 0;
}