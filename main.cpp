#include<iostream> 
#include<vector>

using namespace std;

class Secuencia
{
	int indice_0 = -1;	
	float valor_0 = 0;	// Valor que tiene la secuencia fuera de su rango definido. 
	vector<float> muestras; 
	
	public:
	Secuencia(int indice_0, vector<float> muestras)
	{
		this -> indice_0 = indice_0; 
		this -> muestras = muestras; 
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


}; 

ostream& operator<<(ostream& os, Secuencia a)
{
	for(int i = a.menor_indice(); i <= a.mayor_indice(); i++)
	{
		if(i == 0) 
			os << a[i] << "*" << " ";
		else 
			os << a[i] << " ";
	}

	return os; 
}

int main()
{
	Secuencia a(4, {-4, -3, -2, -1, 0, 1, 2, 3});
	Secuencia b(6, {-1, 2.5, 3.14, 1, -7, 4, 3, 1.3}); 
	cout << "a = { " << a << "}" << endl; 
	cout << "b = { " << b << "}" << endl; 
	cout << (a + b) << endl; 
	cout << (a - b) << endl;
	return 0; 
}
