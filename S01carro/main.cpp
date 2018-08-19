#include <stdio.h>
#include <iostream>

using namespace std;

struct Carro{
    int pass;
    int passMax;
    float gas;
    float gasMax;
    float km;

    bool in(){
        if(pass >=0 && pass < 2){
            pass += 1;
            puts(" done");
            return true;
        }
        puts("fail: limite de passageiros atingido");
        return false;
    }

    bool out(){
        if(pass >=1){
            pass -= 1;
            puts(" done");
            return true;
        }
        puts("fail: nao ha ninguem para desembarcar");
        return false;
    }

    void fuel(float combustivel){
        gas += combustivel;
        puts(" done");
        if(gas > gasMax){
            gas = gasMax;
        }
    }

    bool drive(float distance){
        if(pass > 0){
            if(gas >= distance/10){
                km += distance;
                gas -= distance/10;
                puts(" done");
                return true;
            }
            puts("fail: combustivel insuficiente para realizar a viagem");
            return false;  
        }
        puts("fail: nao eh possivel iniciar a viagem, verifique o combustivel/passageiros"); 
        return false;
    }
};

int main()
{
    string op;
    Carro carro = {0, 2, 0, 10, 0};

    while(true){
        cin >> op;

        if(op == "show"){
            printf(" pass: %d; gass: %.3f; km: %.3f\n", carro.pass, carro.gas, carro.km);
        }else if(op == "in"){
            carro.in();
        }else if(op == "out"){
            carro.out();
        }else if(op == "fuel"){
            float a;

            scanf("%f", &a);
            carro.fuel(a);
        }else if(op == "drive"){
            float d;

            scanf("%f", &d);
            carro.drive(d);
        }
        else if(op == "help"){
            puts(" show; in; out; fuel _; drive _; end; help");
        }
        else if(op == "end"){
            break;
        }
    }
    return 0;
}
