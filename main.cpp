#include<iostream> 
#include<vector>
#include<cstdio>
#include<string> 
#include<fstream>

using namespace std;

class Secuencia
{
	int indice_0 = -1;	
	float valor_0 = 0;	// Valor que tiene la secuencia fuera de su rango definido. 
	vector<float> muestras;

	public:	
	string nombre = "";
	Secuencia(int indice_0, vector<float> muestras)
	{
		this -> indice_0 = indice_0; 
		this -> muestras = muestras; 
	}

	Secuencia(string expresion) 
	{
		const char* cadena = expresion.c_str(); 
		char nombre[20]; 
		char igual; 
		char llave; 
		char aux = 0;
		int caracteres;
		int caracteres_leidos = 0; 
		
		sscanf(cadena, " %[^= ] %c %c%n", nombre, &igual, &llave, &caracteres);
		caracteres_leidos += caracteres;

		this -> nombre = nombre; 	

		for(int i = 0; aux != '}'; i++) 
		{
			float muestra;
			sscanf(cadena + caracteres_leidos, "%f%c%n", &muestra, &aux, &caracteres);
			caracteres_leidos += caracteres;  
			muestras.push_back(muestra); 

			if(aux == '*')
			{
				indice_0 = i; 
				sscanf(cadena + caracteres_leidos, "%c%n", &aux, &caracteres); 
				caracteres_leidos += caracteres;	
			}
		}	
	}

	float& operator[](int i)
	{
		if(i + indice_0 >= 0 && i + indice_0 < muestras.size())
			return muestras[i + indice_0];
		return valor_0;
	}	

	int menor_indice() { return -indice_0; }
	int mayor_indice() { return muestras.size() - indice_0 - 1; }

	Secuencia operator+(Secuencia b)
	{
		int i = min(menor_indice(), b.menor_indice()); 
		int j = max(mayor_indice(), b.mayor_indice()); 
		int tamaño = j - i + 1; 

		vector<float> muestras_suma(tamaño); 
		int indice_0_suma = max(indice_0, b.indice_0); 
		
		Secuencia resultado(indice_0_suma, muestras_suma); 

		for(int k = i; k <= j; k++) 
		{
			resultado[k] = (*this)[k] + b[k]; 
		}

		return resultado; 
	}

	Secuencia operator-(Secuencia b)
	{
		int i = min(menor_indice(), b.menor_indice()); 
		int j = max(mayor_indice(), b.mayor_indice()); 
		int tamaño = j - i + 1; 

		vector<float> muestras_suma(tamaño); 
		int indice_0_suma = max(indice_0, b.indice_0); 
		
		Secuencia resultado(indice_0_suma, muestras_suma); 

		for(int k = i; k <= j; k++) 
		{
			resultado[k] = (*this)[k] - b[k]; 
		}

		return resultado; 
	}

	Secuencia operator*(Secuencia b) 
	{
		int i = max(menor_indice(), b.menor_indice()); 
		int j = min(mayor_indice(), b.mayor_indice()); 
		int tamaño = j - i + 1; 

		vector<float> muestras_producto(tamaño); 
		int indice_0_producto = min(indice_0, b.indice_0); 

		Secuencia resultado(indice_0_producto, muestras_producto); 

		for(int k = i; k <= j; k++)
		{
			resultado[k] = (*this)[k] * b[k];
		}

		return resultado; 
	}

	Secuencia operator*(float k) 
	{
		Secuencia resultado = *this; 

		for(int i = menor_indice(); i <= mayor_indice(); i++) 
		{
			resultado[i] = (*this)[i] * k; 
		}

		return resultado;
	}

	void reflejar()
	{
	       	vector<float> muestras_reflejadas; 	
		for(int i = mayor_indice(); i >= menor_indice(); i--) 
		{
			 muestras_reflejadas.push_back((*this)[i]); 
		}
		this -> indice_0 = muestras.size() - 1 - indice_0; 
		this -> muestras = muestras_reflejadas; 

	}

	void desplazar(int n0)
	{
		if(menor_indice() <= -n0 && -n0 <= mayor_indice()) 
		{
			this -> indice_0 = indice_0 - n0; 
		}	
		else if(-n0 < menor_indice()) 
		{
			int faltantes_principio = n0 + menor_indice(); 
			vector<float> muestras_desplazadas;
			for(int i = 0; i < faltantes_principio; i++) 
				muestras_desplazadas.push_back(0); 
			for(int i = 0; i < muestras.size(); i++) 
				muestras_desplazadas.push_back(muestras[i]); 

			this -> muestras = muestras_desplazadas; 
			this -> indice_0 = 0; 
		}
		else if(-n0 > mayor_indice())
		{
			int faltantes_final = -n0 - mayor_indice(); 
			for(int i = 0; i < faltantes_final; i++) 
				muestras.push_back(0); 
			this -> indice_0 -= n0; // this -> indice_0 = muestras.size() - 1;  
		}

		
	}

	void imprimir_secuencia_txt(string nombre_archivo)
	{
		ofstream of(nombre_archivo); 
		
		for(int i = menor_indice(); i <= mayor_indice(); i++) 
		{
			of << i << " " << (*this)[i] << "\n"; 
		}
	}


}; 

ostream& operator<<(ostream& os, Secuencia a)
{
	os << a.nombre << " = {";
	for(int i = a.menor_indice(); i <= a.mayor_indice(); i++)
	{
		if(i == 0) 
			os << a[i] << "*";
		else 
			os << a[i];
		if(i < a.mayor_indice())
			os << ", "; 
	}
	cout << "}";

	return os; 
}

void graficar_señal(FILE* gnuplot, string señal_txt) 
{
	fprintf(gnuplot, "plot \"%s\" with impulses lw 3, \"%s\" with points pt 7 ps 2\n", señal_txt.c_str(), señal_txt.c_str());
	fflush(gnuplot); 

}

void imprimir_menu()
{
	printf("\n\n"); 
	printf("\ta) Sumar/Restar\n"); 
	printf("\tb) Multiplicar/Amplificar/Atenuar\n"); 
	printf("\tc) Reflejar\n");
       	printf("\td) Desplazar\n"); 
	printf("\te) Diezmacion/Interpolacion\n"); 
	printf("\tf) Convolución\n");  
}

int main(int num_argumentos, char* argumentos[])
{
	char opcion; 
	string vacia;

	printf("\n\t\tOPERACIONES BASICAS CON SECUENCIAS"); 

	printf("\n\nSeleccione una opcion del siguiente del menú:"); 
	imprimir_menu(); 

	printf("\nOpcion: "); 
	scanf("%c", &opcion);
	getline(cin, vacia);
		

	switch(opcion) 
	{
		case 'a':
		{
			string secuencia_a, secuencia_b; 
			printf("\n\t\tSumar/Restar");
			printf("\n\n\tIngrese las secuencias en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
		       	printf("\n\n\tPrimera secuencia: "); 
			getline(cin, secuencia_a);  
		       	printf("\tSegunda secuencia: ");	
			getline(cin, secuencia_b);

			Secuencia a(secuencia_a); 
			Secuencia b(secuencia_b); 
		
			printf("\n\tSeleccione:");
			printf("\n\n\t\t1) Sumar"); 
			printf("\n\t\t2) Restar");

			char opcion2; 
			printf("\n\n\tOpcion: "); 
			scanf("%c", &opcion2); 
			getline(cin, vacia); 
 
			switch(opcion2)
			{
				case '1':
				{
					Secuencia resultado = a + b; 
					cout << "\n\t\t" << a.nombre << " + " << b.nombre <<  resultado << "\n"; 
					break;
				}
				case '2':
				{
					Secuencia resultado = a - b; 
					cout << "\n\t\t" << a.nombre << " - " << b.nombre << resultado << "\n"; 
					break; 
				}
				default: 
				{
					printf("Opcion invalida\n"); 
					break; 
				}
			}


			break;
		}
		case 'b': 
		{ 
			printf("\n\t\tMultiplicar/Amplificar/Atenuar");
			
			printf("\n\n\tSeleccione:");
			printf("\n\n\t1) Multiplicar"); 
			printf("\n\t2) Amplificar");
			printf("\n\t3) Atenuar"); 
			char opcion2; 
			printf("\n\n\tOpcion: "); 
			scanf("%c", &opcion2); 
			getline(cin, vacia); 

			switch(opcion2)
			{
				case '1':
				{
					string secuencia_a, secuencia_b;
					printf("\n\t\tMultiplicar");
					printf("\n\n\tIngrese las secuencias en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
					printf("\n\n\tPrimera secuencia: "); 
					getline(cin, secuencia_a);  
					printf("\tSegunda secuencia: ");	
					getline(cin, secuencia_b);

					Secuencia a(secuencia_a); 
					Secuencia b(secuencia_b); 
				
					Secuencia resultado = a * b; 
					cout << "\n\t\t" << a.nombre << " x " << b.nombre <<  resultado << "\n"; 
					break;
				}
				case '2':
				{
					string secuencia_a;
				       	float factor_amplificacion;	
					printf("\n\t\tAmplificar");
					printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
					printf("\n\n\tSecuencia: "); 
					getline(cin, secuencia_a); 
					Secuencia a(secuencia_a);
				       	printf("\tFactor de amplificacion (k > 1): "); 
					scanf("%f", &factor_amplificacion); 
					Secuencia resultado = a * factor_amplificacion; 
					cout << "\n\t\t" << factor_amplificacion << resultado << "\n"; 
					break; 
				}
				case '3':
				{
					string secuencia_a;
				       	float factor_atenuacion;	
					printf("\n\t\tAtenuar");
					printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
					printf("\n\n\tSecuencia: "); 
					getline(cin, secuencia_a); 
					Secuencia a(secuencia_a);
				       	printf("\tFactor de atenuacion (0 < k < 1): "); 
					scanf("%f", &factor_atenuacion); 
					Secuencia resultado = a * factor_atenuacion; 
					cout << "\n\t\t" << factor_atenuacion << resultado << "\n";
				        break;	
				}
				default: 
				{
					printf("Opcion invalida\n"); 
					break; 
				}
			}

			break;
		}
		case 'c':
		{
			string secuencia_a;
			printf("\n\t\tReflejar");
			printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
			printf("\n\n\tSecuencia: "); 
			getline(cin, secuencia_a); 
			Secuencia a(secuencia_a);
			a.reflejar();
			cout << "\n\t\t" << a << "\n"; 
			break; 
		}
		case 'd':
		{
			string secuencia_a;
			printf("\n\t\tDesplazar");
			printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
			printf("\n\n\tSecuencia: "); 
			getline(cin, secuencia_a); 
			Secuencia a(secuencia_a);

			int n0; 
			printf("\n\n\tIngrese un entero n0 x(n - n0): "); 
			scanf("%d", &n0); 
			a.desplazar(n0);
			cout << "\n\t\t" << a << "\n"; 
			break; 
		}
		case 'e':
		{
			break; 
		}
		case 'f': 
		{
			break; 
		}
		default: 
		{

		}
	}



/*	Secuencia a(4, {-4, -3, -2, -1, 0, 1, 2, 3});
	a.nombre = "a";
	Secuencia b("b={-1, 2.5, 3.14, 1, -7, 4, 3*, 1.3}"); 
	Secuencia c = a + b; 
	cout << (a + b) << endl; 
	cout << (a - b) << endl;
	cout << (a * b) << endl; // -12.42 -3 14 -4 0 1.3
	cout << (a * 2) << endl;
	cout << a << endl; 
	a.imprimir_secuencia_txt("a.txt"); 
	b.imprimir_secuencia_txt("b.txt");
       	c.imprimir_secuencia_txt("c.txt"); 	

	FILE* gnuplot = popen("gnuplot", "w"); 
	fprintf(gnuplot, "set multiplot layout 2,2 columnsfirst\n");
	graficar_señal(gnuplot, "a.txt");	
	graficar_señal(gnuplot, "b.txt"); 
	graficar_señal(gnuplot, "c.txt"); 
	fprintf(gnuplot, "unset multiplot\n");
	fflush(gnuplot);
       	int n; cin >> n; 	
*/
	return 0; 
}
