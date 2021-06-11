#include<iostream> 
#include<vector>
#include<cstdio>
#include<string> 
#include<fstream>
#include<unistd.h>
#include"colores.h"

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
		int tamano = j - i + 1; 

		vector<float> muestras_suma(tamano); 
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
		int tamano = j - i + 1; 

		vector<float> muestras_suma(tamano); 
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
		int tamano = j - i + 1; 

		vector<float> muestras_producto(tamano); 
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

	void diezmar(int k)
	{
		vector<float> nuevas_muestras;
		int nuevo_indice_0 = -1; 	
		for(int i = menor_indice(); i <= mayor_indice(); i++)
		{
			if(i % k == 0) 
				nuevas_muestras.push_back((*this)[i]);
		       	if(i == 0) 	
				nuevo_indice_0 = nuevas_muestras.size() - 1; 
		}
		this -> muestras = nuevas_muestras;
	       	this -> indice_0 = nuevo_indice_0; 	
	}

	void interpolacion_cero(int k)
	{
		vector<float> muestras_interpoladas;
	        for(int i = menor_indice();  i <= mayor_indice(); i++) 
		{
			muestras_interpoladas.push_back((*this)[i]); 
			if(i < mayor_indice())
				for(int j = 0; j < k - 1; j++) 
					muestras_interpoladas.push_back(0); 
		}
		this -> indice_0 *= k;
		this -> muestras = muestras_interpoladas; 
	}

	void interpolacion_escalon(int k) 
	{
		vector<float> muestras_interpoladas;
	        for(int i = menor_indice();  i <= mayor_indice(); i++) 
		{
			for(int j = 0; j < k; j++) 
				muestras_interpoladas.push_back((*this)[i]); 
		}
		this -> indice_0 *= k;
		this -> muestras = muestras_interpoladas; 
	}

	void interpolacion_lineal(int k)
	{
		vector<float> muestras_interpoladas;
	        for(int i = menor_indice() - 1;  i <= mayor_indice(); i++) 
		{
			float adyacente_izquierdo = (*this)[i]; 
			float adyacente_derecho = (*this)[i + 1];

			float constante = (adyacente_derecho - adyacente_izquierdo) / k; 	
			
			for(int j = 0; j < k; j++) 
				muestras_interpoladas.push_back(adyacente_izquierdo + j*constante); 
		}
		this -> indice_0 *= k;
		this -> muestras = muestras_interpoladas; 
	}

	Secuencia convolucion(Secuencia b)
	{
		int minimo = menor_indice() + b.menor_indice(); 
		int maximo = mayor_indice() + b.mayor_indice(); 
		vector<float> muestras_convolucion; 
		int nuevo_indice_0 = -1; 
		for(int n = minimo; n <= maximo; n++)	
		{
			float muestra = 0;  
			for(int k = menor_indice(); k <= mayor_indice(); k++) 
			{
				muestra += (*this)[k]*b[n - k]; 
			}
			muestras_convolucion.push_back(muestra); 
			if(n == 0) 
				nuevo_indice_0 = muestras_convolucion.size() - 1; 

		}
		Secuencia resultado(nuevo_indice_0, muestras_convolucion); 

		return resultado;
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

void graficar_señal(FILE* gnuplot, string nombre, int minimo_x, int maximo_x, string señal_txt) 
{
	fprintf(gnuplot, "plot [%d:%d] \"%s\" title \"%s\" with impulses lw 3, \"%s\" title \"\" with points pt 7 ps 1\n", minimo_x, maximo_x, señal_txt.c_str(), nombre.c_str(), señal_txt.c_str());
	fflush(gnuplot); 
}

void graficar_op_unaria(FILE* gnuplot, Secuencia a, Secuencia resultado)
{
	a.imprimir_secuencia_txt("a.txt"); 
	resultado.imprimir_secuencia_txt("resultado.txt");

	fprintf(gnuplot, "set term pdfcairo\n");
	fprintf(gnuplot, "set output \"grafica.pdf\"\n");
	fprintf(gnuplot, "set multiplot layout 1,2 columnsfirst\n");
	graficar_señal(gnuplot, a.nombre, a.menor_indice() - 2, a.mayor_indice() + 2, "a.txt");	
	graficar_señal(gnuplot, resultado.nombre, resultado.menor_indice() - 2, resultado.mayor_indice() + 2, "resultado.txt");	
	fprintf(gnuplot, "unset multiplot\n");
	fprintf(gnuplot, "set output\n");
	fflush(gnuplot);
	system("xdg-open grafica.pdf");
}

void graficar_op_binaria(FILE* gnuplot, Secuencia a, Secuencia b, Secuencia resultado)
{
	a.imprimir_secuencia_txt("a.txt"); 
	b.imprimir_secuencia_txt("b.txt"); 
	resultado.imprimir_secuencia_txt("resultado.txt");

	fprintf(gnuplot, "set term pdfcairo\n");
	fprintf(gnuplot, "set output \"grafica.pdf\"\n");
	fprintf(gnuplot, "set multiplot layout 2,2 columnsfirst\n");
	graficar_señal(gnuplot, a.nombre, a.menor_indice() - 2, a.mayor_indice() + 2, "a.txt");	
	graficar_señal(gnuplot, b.nombre, b.menor_indice() - 2, b.mayor_indice() + 2, "b.txt");	
	graficar_señal(gnuplot, resultado.nombre, resultado.menor_indice() - 2, resultado.mayor_indice() + 2, "resultado.txt");	
	fprintf(gnuplot, "unset multiplot\n");
	fprintf(gnuplot, "set output\n");
	fflush(gnuplot);
	system("xdg-open grafica.pdf");
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
	bool graficar = false; 
	if(num_argumentos > 1) 
	{
		if(string(argumentos[1]) == "-g")
			graficar = true; 
	}
	FILE* gnuplot = popen("gnuplot", "w"); 
	
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
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " << a.nombre << " + " << b.nombre <<  resultado << " " NONE << "\n\n";
					resultado.nombre = a.nombre + " + " + b.nombre; 
				       	if(graficar) 
						graficar_op_binaria(gnuplot, a, b, resultado); 
					break;
				}
				case '2':
				{
					Secuencia resultado = a - b; 
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " << a.nombre << " - " << b.nombre <<  resultado << " " NONE << "\n\n";
					resultado.nombre = a.nombre + " - " + b.nombre; 
				       	if(graficar) 
						graficar_op_binaria(gnuplot, a, b, resultado); 
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
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " << a.nombre << " x " << b.nombre <<  resultado << " " NONE << "\n\n";
					resultado.nombre = a.nombre + " x " + b.nombre; 
				       	if(graficar) 
						graficar_op_binaria(gnuplot, a, b, resultado); 
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
					resultado.nombre = a.nombre + " amplificada"; 
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " << factor_amplificacion << resultado << " " NONE << "\n\n"; 
				       	if(graficar) 
						graficar_op_unaria(gnuplot, a, resultado); 
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
				       	printf("\tFactor de atenuacion (k > 1): ");
					scanf("%f", &factor_atenuacion); 
				       	factor_atenuacion = 1 / factor_atenuacion;	
					Secuencia resultado = a * factor_atenuacion; 
					resultado.nombre = a.nombre + " atenuada"; 
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " << factor_atenuacion << resultado << " " NONE << "\n\n";
				       	if(graficar) 
						graficar_op_unaria(gnuplot, a, resultado); 
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
			Secuencia resultado = a; 
			resultado.reflejar();
			resultado.nombre = a.nombre + " reflejada"; 
			cout << "\n\t\t" << BG_WHITE FG_GREEN " " << resultado << " " NONE <<  "\n\n"; 
			if(graficar) 
				graficar_op_unaria(gnuplot, a, resultado); 
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
			Secuencia resultado = a; 
			resultado.nombre = a.nombre + " desplazada"; 
			int n0; 
			printf("\n\n\tIngrese un entero n0 x(n - n0): "); 
			scanf("%d", &n0); 
			resultado.desplazar(n0);
			cout << "\n\t\t" << BG_WHITE FG_GREEN " " <<  resultado << " " NONE << "\n\n"; 
			if(graficar) 
				graficar_op_unaria(gnuplot, a, resultado); 
			break; 
		}
		case 'e':
		{
			printf("\n\tSeleccione:");
			printf("\n\n\t\t1) Diezmacion"); 
			printf("\n\t\t2) Interpolacion");

			char opcion2; 
			printf("\n\n\tOpcion: "); 
			scanf("%c", &opcion2); 
			getline(cin, vacia); 
 
			switch(opcion2)
			{
				case '1':
				{
					string secuencia_a;
					int factor_diezmacion;	
					printf("\n\t\tDiezmacion");
					printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
					printf("\n\n\tSecuencia: "); 
					getline(cin, secuencia_a); 
					Secuencia a(secuencia_a);
					Secuencia resultado = a; 
					resultado.nombre = a.nombre + " diezmada"; 
					printf("\tFactor de diezmacion (k > 0): "); 
					scanf("%d", &factor_diezmacion); 
					resultado.diezmar(factor_diezmacion);  
					cout << "\n\t\t" << BG_WHITE FG_GREEN " " <<  resultado << " " NONE << "\n\n"; 
					if(graficar) 
						graficar_op_unaria(gnuplot, a, resultado); 
					break;
				}
				case '2':
				{
					string secuencia_a;
					printf("\n\t\tInterpolacion");
				       	printf("\n\n\tIngrese la secuencia en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
					printf("\n\n\tSecuencia: "); 
					getline(cin, secuencia_a); 
					Secuencia a(secuencia_a);
					Secuencia resultado = a; 
					resultado.nombre = a.nombre + " interpolada"; 
					int factor_interpolacion;  
					printf("\tFactor de interpolacion (k > 0): "); 
					scanf("%d", &factor_interpolacion);
				       
					printf("\n\n\tSeleccione: "); 	
					printf("\n\n\t\t1) Interpolacion a cero"); 
					printf("\n\t\t2) Interpolacion escalon");
					printf("\n\t\t3) Interpolacion lineal");

					char opcion3; 
					printf("\n\n\tOpcion: "); 
					scanf(" %c", &opcion3); 
					getline(cin, vacia);

					switch(opcion3)
					{
						case '1':
						{
							resultado.interpolacion_cero(factor_interpolacion); 
							cout << "\n\t\t" << BG_WHITE FG_GREEN " " << resultado << " " NONE << "\n\n"; 
							if(graficar) 
								graficar_op_unaria(gnuplot, a, resultado); 
							break;
						}
						case '2':
						{
							resultado.interpolacion_escalon(factor_interpolacion); 
							cout << "\n\t\t" << BG_WHITE FG_GREEN " " << resultado << " " NONE << "\n\n"; 
							if(graficar) 
								graficar_op_unaria(gnuplot, a, resultado); 
							break;
						}
						case '3': 
						{
							resultado.interpolacion_lineal(factor_interpolacion); 
							cout << "\n\t\t" << BG_WHITE FG_GREEN " " << resultado << " " NONE << "\n\n"; 
							if(graficar) 
								graficar_op_unaria(gnuplot, a, resultado); 
							break; 
						}
						default: 
						{
							break; 
						}
					}	


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
		case 'f': 
		{
			string secuencia_a, secuencia_b; 
			printf("\n\t\tConvolucion");
			printf("\n\n\tIngrese las secuencias en el formato [nombre={f(-2), f(-1), f(0)*, f(1), f(2)].\n\tEjemplo: a={-4, -2, 0*, 2, 4}"); 
		       	printf("\n\n\tPrimera secuencia: "); 
			getline(cin, secuencia_a);  
		       	printf("\tSegunda secuencia: ");	
			getline(cin, secuencia_b);

			Secuencia a(secuencia_a); 
			Secuencia b(secuencia_b);

			Secuencia resultado = a.convolucion(b);  
			cout << "\n\t\t" << BG_WHITE FG_GREEN " " << a.nombre << " * " << b.nombre <<  resultado << " " NONE << "\n\n";
			resultado.nombre = a.nombre + " * " + b.nombre; 
			if(graficar) 
				graficar_op_binaria(gnuplot, a, b, resultado); 
			break; 
		}
		default: 
		{

		}
	}

	return 0; 
}
