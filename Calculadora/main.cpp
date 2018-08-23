#include <stdio.h>
#include <iostream>
using namespace std;

struct Calc{
    int bateria;
    int limiteBateria;

    void charge(int carga){
        bateria += carga;
        if(bateria > limiteBateria)
            bateria = limiteBateria;
    }
    float soma(float a, float b, bool * deu_certo){
        if(gastarBateria()){
            *deu_certo = true;
            return a + b;
        }
        *deu_certo = false;
        return 0;
    }
    float div(float a, float b){
        if(gastarBateria()){
            if(b == 0){
                puts("fail: nao posso dividir por 0");
                return 0;
            }
            return a/b;
        }
        return 0;
    }
    bool gastarBateria(){
        if(bateria > 0){
            this->bateria -= 1;
            return true;
        }
        puts("fail: bateria insuficiente");
        return false;
    }
    float multi(float a, float b){
        if(gastarBateria()){
            return a*b;
    }
    return 0;
}
    
};

int main(){
    string op;
    Calc calc = {2, 5};
    float a, b;
    while(true){
        cin >> op;
        if(op == "help"){
            puts("soma _a _b; div _a _b; show; charge _carga");
        }else if(op == "soma"){
            
            bool deu_certo;
            scanf("%f %f", &a, &b);
            float resp = calc.soma(a, b, &deu_certo);
            if(deu_certo)
                printf("  = %f\n", resp);
        }
        else if(op == "div"){
            
            scanf("%f %f", &a, &b);
            printf("  = %f\n", calc.div(a, b));
        }else if(op == "charge"){
            int a;
            scanf("%d", &a);
            calc.charge(a);
        }else if(op == "show"){
            printf("  bateria = %d\n", calc.bateria);
        }else if(op == "mult"){
            scanf("%f %f", &a, &b);
            printf(" = %f\n", calc.multi(a, b));
        }
        
        else if(op == "fim")
            break;
    }
    return 0;
}
