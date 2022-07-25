#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include <climits>
#include <cmath>
#include <ctime>
using namespace std;

#define DIM 10


template <class T>
class Dungeon{
    public:
       // virtual ~Dungeon() = 0;
    //protected:
        Dungeon(){    }
    private:
        virtual int ciao()=0;
};


template <class T>
class Volcano: public Dungeon<T>{
     public:
        Volcano() :  Dungeon<T>(){ }
    private:
        int ciao(){return 0;}
};

template <class T>
class Abyss: public Dungeon<T>{
    public:
        Abyss() :  Dungeon<T>(){ }
    private:
        int ciao(){return 0;}
};



template<class T>
class Character{
    private:
        T*** power;
    protected:
        Dungeon<T>* dungeon;
        int rows;
        int columns;
        int len;
        T* HP;
        
        int basehp=30;
        T** getColumn(int index){
            T** colonna = new T*[columns];
            for(int i=0; i<columns; i++){
                *colonna[i] = *power[i][index];
            }
            return colonna;
        }

    public:
        Character(int rows, int columns, int len, Dungeon<T> *dungeon){
                 
            this->rows=rows;
            this->columns=columns;
            this->len=len;
            this->dungeon=dungeon;
            power=new T **[rows];
                for(int i=0; i<rows; i++)
                    power[i]=new T *[columns];
                    for(int i=0; i<rows; i++){
                        for(int j=0; j<columns; j++){
                            power[i][j]=new T(rand()/(T)RAND_MAX);
                        }  
                  //  cout<<endl;
                }  
            HP = new T [len];
            for(int i=0; i<len; i++){
                HP[i] = rand()%6;
             //   cout<<HP[i]<<"\t";
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
    
    virtual T health() = 0;

    virtual ostream& put(ostream& os){
        os<<"La tua classe (s)fortunata: "<< typeid(*this).name()<<endl;
        os<<endl<<"La tua 'MATRICE DI POTERE' e': "<<endl;
        for(int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){ 
                os<<*(power[i][j])<<"\t";
                } os<<endl;
        }
        os<<endl<<"La tua 'BARRA DEGLI HP' e' di:"<<endl;
        for(int i=0; i<len; i++){
            os<<HP[i]<<"\t";
        }
        os<<endl;
        return os;
    }
};

template <class T> 
class Wizard : public Character<T>{
    public:
        Wizard(int rows, int columns, int len, Dungeon<T> *dungeon) : Character<T>::Character(rows, columns, len, dungeon){
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
                for(int  i=0; i<<Character<T>::rows; i++){
                    attacco+=*Character<T>::getColumn(index)[i];
                }
            return attacco;
            }
        }
        
        T health(){
            T vita;
        //    if(typeid(*this(Character<T>::dungeon))==typeid(Volcano<T>))){ //????????????????????  
        
                                                    //IF VOLCANO
            /*
            int randomlen = rand()%Character<T>::len+1;
            
            cout<<endl<<"*lancio del dado*... tiro: "<<randomlen<<endl;
            T somma = 0;
            for (int i = 0; i<randomlen;i++){
                somma+=Character<T>::HP[i];
            }
            vita=round(sqrt(somma))+Character<T>::basehp;
            cout<<"Che fortuna! Ci troviamo nel vulcano e i tuoi HP salgono! HP  =";
           */
            
                                            //IF ABYSS
            //if(typeid(*this(Character<dungeon>))==typeid(Abyss)){ // ?????
            cout<<"OGGETTO INIETTATO DI TIPO "<<typeid(this->dungeon).name()<<endl;

            int dado = rand()%6+1;
            cout<<endl<<"Che sfortuna! Ci troviamo nell'abisso, sei debole! Tentiamo la fortuna per i tuoi hp..";
            cout<<endl<<"*lancio del dado*... tiro: "<<dado<<endl;
            if(dado%2==0){
                vita=Character<T>::basehp;
                cout<<"sei fortunato, la tua salute non e' scesa, HP = ";
            }
            else{
                T somma = 0;
                for (int i = 0; i<Character<T>::len;i++){
                    if(((int)Character<T>::HP[i])%3==0)
                    somma+=Character<T>::HP[i];
            }
            vita=Character<T>::basehp-round(sqrt(somma));
            cout<<endl<<"ahi ahi, dispari!! Potresti perdere hp! HP = ";
            }
            


    
         return vita;
        }

        ostream& put(ostream& os) {
            Character<T>::put(os);
            os<<endl<<"il tuo misero attacco e' di ="<<Wizard<T>::attack()<<endl; 
           os<<Wizard<T>::health();
            return os;
        }
    
    
};

template <class T> 
class Cleric : public Character<T>{
    public:
    
    Cleric(int rows, int columns, int len, Dungeon<T>* dungeon) : Character<T>::Character(rows, columns, len, dungeon){ }

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

T health(){
  
        T vita=0;
                             //IF ABYSS
       /* cout<<endl<<"che fortuna! ci troviamo nell'abisso, la tua salute potrebbe aumentare! HP = ";
        int totale=0, dispari=0;        
        for(int i=0; i<Character<T>::len; i++){
            totale+=Character<T>::HP[i];
            if(i%2!=0) dispari+=Character<T>::HP[i];
        }
        int diff=totale-dispari;
        if(diff<0) vita = Character<T>::basehp;
        else{ vita=diff+Character<T>::basehp;}
*/
        //IF VOLCANO
        cout<<"OGGETTO INIETTATO DI TIPO "<<typeid(this->dungeon).name()<<endl;
        int dado = rand()%6+1;
            cout<<endl<<"Che sfortuna! Ci troviamo nel vulcano, sei debole! Tentiamo la fortuna per i tuoi hp..";
            cout<<endl<<"*lancio del dado*... tiro: "<<dado<<endl;
            if(dado%2==0){
                vita=Character<T>::basehp;
                cout<<"sei fortunato, la tua salute non e' scesa, HP = ";
            }
            else{
               int differenza = Character<T>::HP[Character<T>::len-1] - Character<T>::HP[Character<T>::len-2];
            
            vita=Character<T>::basehp-abs(differenza);
            cout<<endl<<"ahi ahi, dispari!! Potresti perdere hp! HP = ";
            }
        return vita;
    
}

    ostream& put(ostream& os) {
        Character<T>::put(os);
        os<<endl<<"il tuo misero attacco e' di = "<<Cleric<T>::attack()<<endl<<endl;
         os<<Cleric<T>::health();
        return os;
    }    


};

template <class T> 
ostream& operator<<(ostream& os, Character<T>& obj) {
    return obj.put(os);
};


int main(){

    srand(11223344);

    Character<double>* vec[DIM];
    int random;
    Dungeon<double>* dungeon1 = new Volcano<double>();
    Dungeon<double>* dungeon2 = new Abyss<double>();
    //typeid(dungeon2)==typeid(new Abyss<double>()) ? cout<<1<<endl : cout<<2<<endl; 
    cout<<(typeid(*dungeon1).name())<<endl;
    for(int i=0; i<DIM; i++){
       
        random=rand()%2;
        if(random%2==0){
             vec[i] = new Wizard<double>(5,3,5, dungeon1);
      
        } 
        else {
            vec[i] = new Cleric<double>(3,5,5, dungeon2);
        }
    }
      
/*
    for(int i = 0; i < DIM; i++) {
        cout<<endl<<"PERSONAGGIO NUMERO: "<<i+1<<endl<<endl;
        cout << *vec[i] << endl;
        cout<<"_____________________"<<endl;
        
    }
*/
}