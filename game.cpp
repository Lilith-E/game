#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <climits>
#include <cmath>
#include <ctime>
using namespace std;

#define DIM 10

template<class T>
class Character{
    private:
        T*** power;
    protected:
        int rows;
        int columns;
        
        T** getColumn(int index){
            T** colonna = new T*[columns];
            for(int i=0; i<columns; i++){
                *colonna[i] = *power[i][index];
            }
            return colonna;
        }

    public:
        Character(int rows, int columns){
                 
            this->rows=rows;
            this->columns=columns;
           
            
            power=new T **[rows];
                for(int i=0; i<rows; i++)
                    power[i]=new T *[columns];
                    for(int i=0; i<rows; i++){
                        for(int j=0; j<columns; j++){
                            power[i][j]=new T(rand()/(T)RAND_MAX);
                        }  
                  //  cout<<endl;
                }  
        }
        
        void traspose(){ 
          
            T*** powerT; 
            powerT= new T **[columns];
                for(int i=0; i<columns; i++)
                    powerT[i]=new T *[rows];
                    for(int i=0; i<columns; i++){
                        for(int j=0; j<rows; j++){
                            powerT[i][j] = new T;
                      
                    }
                }
            for(int i=0; i<this->columns; i++){
                for(int j=0; j<this->rows; j++){
                     powerT[i][j] = power[j][i];
               
                }
            }
            for(int i=0; i<this->columns; i++){
                for(int j=0; j<this->rows; j++){
                    power[i][j] = powerT[i][j]; 
                }
            }
        }

    virtual T attack() = 0;

    virtual ostream& put(ostream& os){
        os<<"La tua classe (s)fortunata: "<< typeid(*this).name()<<endl;
        os<<endl<<"La tua 'MATRICE DI POTERE' e': "<<endl;
        for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){ 
                os<<*(power[i][j])<<"\t";
                } os<<endl;
        }
        os<<endl;
        return os;
    }
};

template <class T> 
class Wizard : public Character<T>{
    public:
        Wizard(int rows, int columns) : Character<T>::Character(rows, columns){
          Character<T>::traspose();
        }  
        
        T attack(){
        
            int random = rand()%12+1;
             
            if(random%2==0){
                Character<T>::traspose();
                return 0;
            }
            else{
                int index;
                do{
                    index = rand()%Character<T>::columns;
                }while(index%2==0);
                

                T attacco = random%6+1;
                for(int  i=0; i<Character<T>::rows; i++){
                    attacco+=*Character<T>::getColumn(index)[i];
                }
            return attacco;
            }
        }

        ostream& put(ostream& os) {
            Character<T>::put(os);
            os<<"il tuo misero attacco e' di ="<<Wizard<T>::attack();
            return os;
        }
    
};

template <class T> 
class Cleric : public Character<T>{
    public:
    
    Cleric(int rows, int columns) : Character<T>::Character(rows, columns){ }

    T attack(){

        int random = rand()%6+1;
        switch(random){
            case 1: 
            case 5:{ return 0; }
            case 2:
            case 4:
            case 6: {
                T attacco = random;
                int index = rand()%Character<T>::columns;
                for(int  i=0; i<<Character<T>::rows; i++){
                    attacco+=*Character<T>::getColumn(index)[i];
                }
            }

            default: 
                return random/2;

        }
    }

    ostream& put(ostream& os) {
        Character<T>::put(os);
        os<<"il tuo misero attacco e' di = "<<Cleric<T>::attack();
        return os;
    }    


};


template <class T> 
ostream& operator<<(ostream& os, Character<T>& obj) {
    return obj.put(os);
}

int main(){

    srand(11223344);

    Character<double>* vec[DIM];
    int random;
    for(int i=0; i<DIM; i++){
         random=rand()%20;
      
        if(random%2==0){
             vec[i] = new Wizard<double>(5,3);
      
        } 
        else {
            vec[i] = new Cleric<double>(3,5);
        }
    }
      

    for(int i = 0; i < DIM; i++) {
        cout<<endl<<"PERSONAGGIO NUMERO: "<<i+1<<endl<<endl;
        cout << *vec[i] << endl;
        cout<<"_____________________"<<endl;
        
    }

}