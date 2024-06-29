#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURITYCRITICAL_ATTRIBUTE
#include <fstream>
#include <iostream>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <search.h>
using namespace std;
struct Element3;
struct Element2;

struct Element1//Студенты факультета
{
public:
	char Name[50];
	int  kurs;
	// перегрузка operatora вывода
		// используется, где написано (11):
	friend ostream& operator<< (ostream& out, const Element1& m)
	{
		out << m.Name << " " << m.kurs << endl;
		return out;
	}

	// перегрузка оператора ввода
	// используется, где написано (12):
	friend	istream& operator>> (istream& in, Element1& m)
	{
		in >> m.Name;
		in >> m.kurs;
		return in;
	}

	//// перегрузка оператора =
	//// используется, где написано (13) :
	Element1& operator = (Element1& m)
	{
		strcpy(Name, m.Name);
		kurs = m.kurs;
		return *this;
	}
	//// используется, где написано (14) :
 

	//Element1& operator = (Element3& m)
	//{
	//	strcpy(Name, m.Name);
	//	kurs = m.kurs;
	//	return *this;
	//}


	// используется, где написано (15) :
	// перегрузка оператора = общего  для разных структур (вместо предыдущих 3-х):
	template<class T>
	Element1& operator = (T& m)
	{
		//try{
		//	strcpy(Name, m.Name);
		//}
		//catch (string ignore) {}
		//try {
		//	kurs = m.kurs;
		//}
		//catch (string ignore) {}

		return *this;
	}


	// перегрузка оператора == , сравнение структур (по полям в них)
	// используется, где написано:(16)
	template<class T>
	bool operator == (T& m)
	{
		//сравнение полей структур взять в блоки исключений (try\catch),
	// если поля нет- не произойдёт сбоя
		bool result = true;
		try {
			result = result && (Name == m.Name);
		}
		catch (string ignore) {}
		try {
			result = result && (kurs == m.kurs);
		}
		catch (string ignore) {}

		return result;
	}
	// используется, где написано  17):
	template<class T>
	bool operator < (Element1& m2)
	{
		if (strcmp(Name, m2.Name) > 0)
			return true;
		else return false;
	}

	template<class T>
	bool operator < (T& m2)
	{
			return false;
	}
};
struct Element2//Студенты имеющие задолженности по сессии
{
	char Name[50];
	int  Count;
	int  kurs;
	// используется, где написано (22) :
	friend	istream& operator>> (istream& in, Element2& m)
	{
		in >> m.Name;
		in >> m.Count;
		in >> m.kurs;
		return in;
	}
	// используется, где написано (21):
	friend ostream& operator<< (ostream& out, const Element2& m)
	{
		out << m.Name << " " << m.Count<< " " << m.kurs << endl;
		return out;
	}
	// используется, где написано (23):
	Element2& operator = (Element2& m)
	{
		strcpy(Name, m.Name);
		Count = m.Count;
		kurs = m.kurs;
		return *this;
	}
	// использование шаблонного operator == для любых типов структур:
// используется, где написано (24):
	template<class T>
	bool operator == (T& m)
	{
		//сравнение полей структур взять в блоки исключений (try\catch),
// если поля нет- не произойдёт сбоя
		//…
		return false;
	}
	// используется, где написано (25):
	bool operator < (Element2& m2)
	{
		if (strcmp(Name, m2.Name) > 0)
			return true;
		else return false;
	}
};

struct Element3//Студенты, сдавшие сессию
{
	char Name[50];
	int  kurs;
	// используется, где написано (32):
	friend	istream& operator>> (istream& in, Element3& m)
	{
		in >> m.Name >> m.kurs;
		return in;
	}

	// используется, где написано (31):
	friend ostream& operator<< (ostream& out, const Element3& m)
	{
		out << m.Name << " " << m.kurs << endl;
		return out;
	}
	// перегрузка оператора = dlya obyecta classa, 
	// используется, где написано (34):
	Element3& operator = (Element3& m)
	{
		strcpy(Name, m.Name);
		kurs = m.kurs;
		return *this;
	}
	// присвоение Element3 struct Element1 
	// используется, где написано (33) :
	Element3& operator = (Element1& m)
	{
		strcpy(Name, m.Name);
		kurs = m.kurs;
		return *this;
	}
	// используется, где написано (35) :
		// использование шаблонного operator == для любых типов структур:
	template<class T>
	bool operator == (T& m)
	{
		//сравнение полей структур взять в блоки исключений (try\catch),
// если поля нет- не произойдёт сбоя
		//…
		return false;
	}

	// перегрузка оператора <, сравнение структур по полям
	// используется, где написано (36):
	bool operator < (Element3& m2)
	{
		return kurs - m2.kurs < 0;
	}

	bool operator > (Element3& m2)
	{
		return  m2.kurs - kurs < 0;
	}
};

template<class T>
class MASSIV
{
	int count;
	T* mas;

public:

	MASSIV() {
		mas = NULL;
		count = 0;
	} MASSIV(int n)
	{
		count = n;
		mas = new T[count];
	}

	MASSIV(MASSIV <T>& m)
	{
		count = m.count;
		mas = m.mas;
	}
	~MASSIV()
	{
		delete (T*)mas;
	}

	int GetCount()
	{
		return count;

	}

	void SetCount(int k)
	{
		count = k;
	}

	// Запись в бинарный файл
// работает только для строк char*
	void WriteData(char* s)
	{
		fstream out;
		out.open(s, ofstream::out | ofstream::binary); if (!out.is_open())
		{
			cout << "Open file failed.\n";
		}
		else
		{
			int i = 0;
			while (i < count)
			{
				out.write((char*)&mas[i], sizeof(T)); i++;
			}
			out.close();
		}
	}
	//Запись в текстовый файл
	void WriteTextData(char* s)
	{
		fstream out;
		out.open(s, ofstream::out);
		if (!out.is_open())
		{
			cout << "Open file failed.\n";
		}
		else
		{
			int i = 0;

			while (i < count)
			{
				out << mas[i];// (11) или (21) или (31)
				i++;
			}
			out.close();
		}
	}
	//Чтение из бинарного файла
	// работает только для строк char*
	void ReadData(char* s)
	{
		fstream in;
		in.open(s, ofstream::in | ofstream::binary);
		if (!in.is_open())
		{
			cout << "Open file failed.\n";
		}
		mas = new T[100];
		int i = 0;
		in.seekg(0, ios::beg);

		while (!in.eof())
		{
			in.read((char*)&mas[i], sizeof(T));
			i++;
		}
		count = i - 1; in.close();
	}
	


// Чтение из текстового файла
void ReadTextData(char* s)
{
	fstream in;
	in.open(s, ofstream::in); if (!in.is_open())
	{
		cout << "Open file failed.\n";

	}
	else
	{
		mas = new T[100];
		int i = 0;
		in.seekg(0, ios::beg);

		while (!in.eof())
		{
			in >> mas[i]; // (12) или (22) или (32)
			i++;
		}
		count = i - 1;
		in.close();
	}
}
// перегрузка оператора ввода массива
// используется, где написано :(111)
friend istream& operator>> (istream& in, MASSIV& m)
{
	int n;
	cout << "Enter count: "; in >> n;
	MASSIV x(n);
	m = x; // (13) или (15) 
	for (int i = 0; i < n; i++)
	{

		cout << "Enter element:";
		in >> m[i]; // (12) или (22) или (32) и (3)
	}


	return in;
}

// перегрузка оператора вывода массива
// используется, где написано :(1)
friend ostream& operator<< (ostream& out, const MASSIV& m)
{
	out << "MASSIV :" << endl;
	for (int j=0; j < m.count; j++)
		out << " " << m.mas[j]; // (11) или (21) или (31) и (3)
	return out;
}

// перегрузка оператора вывода массива
// используется, где написано :(2)
//friend istream& operator>> (istream& in, MASSIV& m)
//{
//	cout << "--------ENTER MASSIV : " << endl;
//	for (…)
//		in >> m[j]; // (12) или (22) или (32) и (3)
//	return out;
//}

// перегрузка оператора [] для объекта класса массива 
// используется, где написано:(3)
T& operator[] (int m)
{
	return mas[m];
}

//перегрузка оператора=, для объекта класса массива
// используется, где написано :(4)
template<class T>
MASSIV& operator = (MASSIV <T>& m)
{
	count = m.GetCount();
	mas = new T[count];
	for(int i=0; i< count;i++)
		mas[i]=m.mas[i];
	return *this;
}

void Sort()
{
	cout << endl << "SORT MASSIV" << endl << endl;
	T t;
	for (int i = 0; i < count - 1; i++)
		for (int j = 0; j < count - i - 1; j++)
			if (mas[j] > mas[j+1]) //(17)
			{
				t = mas[j]; // (13) или (15), если для Struct1; (23), если для Struct2…
				mas[j] = mas[j+1];
				mas[j+1] = t;
			}
}

//template<class T1, class T2>
//void SUBTRACTION(MASSIV<T1>& x, MASSIV<T2>& y)
void SUBTRACTION(MASSIV<Element1>& x, MASSIV<Element2>& y)//кто есть в элемент1, но нет в элемент2
{
	int k = 0;
	bool b;
	cout << endl << "SUBTRACTION" << endl << endl;
	for (int i = 0; i < x.GetCount(); i++)
	{
		b = true;
		for (int j = 0; j < y.GetCount(); j++)
 				if (strcmp(x[i].Name, y[j].Name)==0)  //(14) или (15) 
				{
					b = false;
				}
		if (b) {
			mas[k] = x[i]; //(33)
			k++;
		}
	}
	count = k;

}
};
template<class T>
MASSIV<T> search_function(MASSIV<T>& x)
{
	int k = 0;
	MASSIV<T> y(x.GetCount());
	for (int i = 0; i < x.GetCount(); i++) {
		if (x[i].kurs >= 3) {
			y[k] = x[i];
			k++;
		}
	}
	y.SetCount(k);
	return y;
}

int main()
{
	MASSIV <Element1> M;
	MASSIV <int> M2;
	M.ReadData((char*)"Element1.txt");
	//MASSIV <int> M;
	M2.ReadTextData((char*)"Elementint.txt");
	M.ReadTextData((char*)"textElement1.txt");
	M.WriteData((char*)"Element1out.txt");
	M.WriteTextData((char*)"textElement1out.txt");
	cout << M;
	M2.Sort();
	cout << M2;//(1)
	MASSIV <Element2> K;
	K.ReadTextData((char*)"textElement2.txt"); 
	cout<< endl << K<< endl;
	K.WriteData((char*)"Element2.txt");
	K.WriteTextData((char*)"textElement2.txt");
	cout<< endl << K[2]<< endl; //(1) (2)
	MASSIV <Element3> R(M.GetCount());
	R.SUBTRACTION(M, K);
	cout << R; //(1)
	R.Sort();
	cout << R;//(1)
	cout << "\nSTARSHEKURSNIKI\n" << search_function(M);
	MASSIV <Element3> K2;
	K2 = R;//(4)
	cout << K2;//(1)
	cin >> K2; //(2)
	cout << K2;
	cout << "exit";
	return 0;
}


