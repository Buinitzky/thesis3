#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<stdlib.h>

using namespace std;

class ManejadorArchivos{
	fstream* archivo;
public:
	ManejadorArchivos(){
		archivo=new fstream();
	}

	string leerArchivo(string file){
		archivo->open(file.c_str(),ios::in);
		string contenido,aux;

		while(getline(*archivo,aux))
			contenido+=aux+"\n";

		archivo->close();
		return contenido;
	}

	void escribirArchivo(string file,string contenido){
		archivo->open(file.c_str(),ios::out);
		*archivo<<contenido;
		archivo->close();
	}

};

class Matriz{
	int filas, columnas;
	double** matriz;

	void inicializar(){
		matriz=new double*[filas];

		for(int i=0;i<filas;i++){
			matriz[i]=new double[columnas];

			for(int j=0;j<columnas;j++)
				matriz[i][j]=i*10+j ;
		} 
	}

	void liberar(){
		for(int i = 0; i < filas; i++) 
			delete[] matriz[i]; 

		delete[] matriz;
	}

public:
	Matriz(int f,int c){
		filas=f;
		columnas=c;
		inicializar();
	}
	
	~Matriz(){
		liberar();
	}

	string ToString(){
		ostringstream ss;		
		for(int i=0;i<filas;i++){
			ss<<"[\t";
			for(int j=0;j<columnas;j++)
				if(matriz[i][j]<0)
					ss<<matriz[i][j]<<"\t";
				else
					ss<<" "<<matriz[i][j]<<"\t";
			ss<<"]"<<endl;  
		}
		return ss.str();
	}

	string ToString(int n,int m){
		ostringstream ss;		
		for(int i=0;i<n;i++){
			ss<<"[\t";
			for(int j=0;j<m;j++)
				if(matriz[i][j]<0)
					ss<<matriz[i][j]<<"\t";
				else
					ss<<" "<<matriz[i][j]<<"\t";
			ss<<"]"<<endl;  
		}
		return ss.str();
	}

	string Transpuesta(){
		ostringstream ss;		
		for(int i=0;i<filas;i++){
			ss<<"[\t";
			for(int j=0;j<columnas;j++)
				if(matriz[j][i]<0)
					ss<<matriz[j][i]<<"\t";
				else
					ss<<" "<<matriz[j][i]<<"\t";
			ss<<"]"<<endl;  
		}
		return ss.str();
	}

	double** obtener(){
		return matriz;
	}

	void mostrar(){
		for(int i=0;i<filas;i++){
			cout<<"[ ";
			for(int j=0;j<columnas;j++)
				if(matriz[i][j]<0)
					cout<<matriz[i][j]<<" ";
				else
					cout<<" "<<matriz[i][j]<<" ";
			cout<<"]"<<endl;  
		}
	}

	void sumarTranspuesta(double** matriz,int n){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(j>=i){
				matriz[i][j]+=matriz[j][i];
				if(i!=j)
					matriz[j][i]=matriz[i][j];
			}
	}

	int getFilas(){
		return filas;
	}

	int getColumnas(){
		return columnas;
	}

	double determinante(double** Matriz,int MAX){
		if (MAX == 2)
			{
				return (Matriz[0][0]*Matriz[1][1] - Matriz[0][1]*Matriz[1][0]);
			}
		else if(MAX==1){
			return Matriz[0][0];
		}
			else
			{
				int Actual = 0;
				int k = 0;
				double Numero = 0;
				double Multriplicador;
				double** Buffer; // Creo una nueva matriz para hacer los adjuntos
				Buffer = new double*[MAX-1];
 
				for (int i = 0; i<(MAX-1); i++)
					Buffer[i] = new double[MAX-1];
 
				for (int l = 0; l < MAX; l++) // Desarrollo por filas
				{
					for (int j = 1; j < MAX; j++) // Creo una nueva matriz adjunta
					{
						for (int i = 0; i < MAX; i++)
						{
							if (i != l)
							{
								Buffer[k][j-1] = Matriz[i][j];
								k++;
							}
						}
						k = 0;
					}
 
					if ( l % 2 != 0)
						Multriplicador = -1;
					else
						Multriplicador = 1;
					Numero += (Matriz[l][0]*determinante(Buffer,MAX-1)*Multriplicador);
				}
				return Numero;
			}
	}

};

class Nodo{
	double Vc,Tt,VM,TM,VE,CI;
	int id;

public:

	Nodo(){}

	Nodo(int id,double Vc,double Tt,double VM,double TM, double VE, double CI){
		this->id=id;
		this->Vc=Vc;
		this->Tt=Tt;
		this->VM=VM;
		this->TM=TM;
		this->VE=VE;
		this->CI=CI;
	}
	string ToString(){
		ostringstream ss;		
		ss<<id<<" "<<Vc<<" "<<Tt<<" "<<VM<<" "<<TM<<" "<<VE<<" "<<CI<<"\n";
		return ss.str();
	}
	int getId(){
		return id;
	}
	double getVc(){
		return Vc;
	}
	double getTt(){
		return Tt;
	}
	double getVM(){
		return VM;
	}
	double getTM(){
		return TM;
	}
	double getVE(){
		return VE;
	}
	double getCI(){
		return CI;
	}
};

class Cluster{
	Nodo* nodos;
	int n;
	ostringstream ss;
	void aplicarFormula(double** matriz){
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j)
					matriz[j][i]=nodos[j].getVM()/nodos[j].getTM();
				else
					matriz[j][i]=-((  (n-1)*nodos[i].getVM() + nodos[i].getVE()  ) / nodos[i].getTM());
	}

	bool aplicarCriterio(Matriz* matriz,int n){
		bool criterio=false;
		double det;
		ss<<endl<<"Criterio de Sylvester:"<<endl;
		for(int i=1;i<n+1;i++){
			det=matriz->determinante(matriz->obtener(),i);
			ss<<endl<<"N="<<i<<endl<<matriz->ToString(i,i)<<endl<<"El determinante es: "<<det<<endl;
			if(i%2==0)
				criterio=det>0;
			else
				criterio=det<0;

			if(!criterio){
				ss<<"No cumple con el criterio de Sylvester"<<endl<<endl;
				break;
			}
			else
				ss<<"Si cumple con el criterio de Sylvester"<<endl<<endl;
			
		}
		return criterio;
	}
public:
	Cluster(int n,Nodo* nodos){
		this->nodos=nodos;
		this->n=n;
	}

	string ToString(){
		return ss.str();
	}

	bool esEstable(){
		Matriz* matriz=new Matriz(n,n);
		aplicarFormula(matriz->obtener());
		ss<<"Matriz F': "<<endl<<matriz->ToString()<<endl;
		ss<<"Matriz F(x): "<<endl<<matriz->Transpuesta()<<endl;
		matriz->sumarTranspuesta(matriz->obtener(),n);
		ss<<"Matriz F' + F(x): "<<endl<<matriz->ToString()<<endl;
		return aplicarCriterio(matriz,n);
	}

	Nodo* getNodos(){
		return nodos;
	}

};

vector<double> split(string s) {
    string buf;
    stringstream ss(s);

    vector<double> tokens;

    while (ss >> buf)
		tokens.push_back((double)atoi(buf.c_str()));
	return tokens;
}

Nodo* decodificar(vector<double> entrada,int n){
	int id=-1,Vc=0,Tt=1,VM=2,TM=3,VE=4,CI=5;
	Nodo* nodos=new Nodo[n];
	for(int i=0;i<n;i++){
		nodos[i]=Nodo(/*entrada[i*7+id]*/0,entrada[i*6+Vc],entrada[i*6+Tt],entrada[i*6+VM],entrada[i*6+TM],entrada[i*6+VE],entrada[i*6+CI]);
	}
	return nodos; 
}

ManejadorArchivos* manejador;
Cluster* cluster;
/****************MODIFICADO****************/
int main(){
	manejador=new ManejadorArchivos();
	string entrada=manejador->leerArchivo("Archivos/entradaK"),salida="";
	vector<double> aux=split(entrada);
	int n=aux.size()/6;
	cluster=new Cluster(n,decodificar(aux,n));
        
	if(cluster->esEstable()){
                printf("\nEl cluster es estable!!!\n\n");
		salida+=cluster->ToString()+"Cumple con todas las condiciones del Criterio de Silvestre por lo tanto EL CLUSTER ES ESTABLE\n\n";
                manejador->escribirArchivo("Archivos/salidaK","1");
        }
        else{
                printf("\nEl cluster no es estable!!!\n\n");
		salida+=cluster->ToString()+"No Cumple con todas las condiciones del Criterio de Silvestre por lo tanto EL CLUSTER NO ES ESTABLE\n\n";
                manejador->escribirArchivo("Archivos/salidaK","0");
                salida=salida+cluster->ToString()+salida+"\n\nRealizado por: \n";
        }
	manejador->escribirArchivo("Archivos/detallesK",salida);
        return 0;
}
