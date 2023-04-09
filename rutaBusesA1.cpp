//---------------------------------------------------------------------------------BIBLIOTECAS---------------------------------------------------------------------
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>     
#include <time.h> 
#include <ctime> 
#include <iostream>
#include <fstream> 
#include <algorithm>
#include <random>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <cctype>
#include <regex>
#include <sstream>
#include <cmath>
#include <chrono>
#include "xlsxwriter.h"

using namespace std;
//----------------------------------------------------------------------------------FUNCIONES------------------------------
bool randomPerteneceAdigitosRandom(int& random,vector<int> digitosRandom){
	bool flag = false;
	for (int i = 0; i < digitosRandom.size(); ++i){
		if(random == digitosRandom.at(i)){
			flag = true;
			break;
		}else{
			flag = false;
		}	
	}
	return flag;
}
int escogoRandom(int& min,int& max, vector<int>& digitosRandom){
	int digitoAleatorio;
	bool fstop = true;
	do{
		digitoAleatorio = min + rand()%(max-min+1);
		fstop = randomPerteneceAdigitosRandom(digitoAleatorio,digitosRandom);
	}while(fstop);
    return digitoAleatorio;
}
void orden_aleatorio(vector<string>& vector) {
    random_device rd;
    mt19937 g(rd());
    shuffle(vector.begin(), vector.end(), g); //Funcion que desordena un vector con la planificacion diaria
}
vector<int> definirDigitosSiguientes(vector<int>& vectorDiaAnterior){
	vector<int> vec1;
	bool flag = false;
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < vectorDiaAnterior.size(); ++j){
			if (i == vectorDiaAnterior.at(j)){
				flag=true;
				break;
			}
		}
		if (!flag){
			vec1.push_back(i);
			flag = true;
		}
		flag = false;
	}
	return vec1;
}
vector<string> obtenerListado( vector<int>& digitos,vector<string>& patentes){ 
	unordered_set<string> result_set; // usamos unordered_set para chequear duplicados
    vector<string> result; // vector para devolver el resultado
    
    for (const auto& patente : patentes) {
        if (patente.size() >= 1) {
            string ultimas_dos_letras = patente.substr(patente.size() - 1);
            for (const auto& digito : digitos) {
                if (ultimas_dos_letras.find(to_string(digito)) != string::npos) {
                    result_set.insert(patente); // insertamos en el set
                    break;
                }
            }
        }
    }
    
    // convertimos el set a un vector para devolver el resultado
    for (const auto& patente : result_set) {
        result.push_back(patente);
    }
    
    return result;
}
unordered_map<string, int> iniciarMapa(vector<string>& patentes) {
    unordered_map<string, int> mapa;
    for (int i = 0; i < patentes.size(); i++) {
    	string patente = patentes[i];
    	mapa[patente] = 0;
	}
    return mapa;
}
void contarPatentes(vector<string>& lista, unordered_map<string, int>& mapa) {
    for (string patente : lista) {
        if (mapa.count(patente)) {
            mapa[patente]++;
        }
    } // Función para aumentar el valor en 1 por cada patente encontrada en otra lista
}
vector<int> leerArchivoDigitos(string nombreArchivo) {
    vector<int> digitos;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            for (char c : linea) {
                if (c >= 48 && c <= 57) {
                    digitos.push_back(c - 48);
                }
            }
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo" << endl;
    }
    return digitos; //lee solo los caracteres que sean numeros 
}
vector<string> leerFolios(string nombreArchivo) {
   vector<string> resultado;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            string digitos;
            for (char c : linea) {
                if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)) {
                    digitos.push_back(c);
                }
            }
            resultado.push_back(digitos);
        }
        archivo.close();
    }
    return resultado;
}
vector<string> leerArchivoPatentes(string nombreArchivo) {
    vector<string> resultado;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            string digitos;
            for (char c : linea) {
                if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90)) {
                    digitos.push_back(c);
                }
            }
            resultado.push_back(digitos);
        }
        archivo.close();
    }
    return resultado;
}
void guardar_map_en_archivo(unordered_map<string, int>& mapa, const string& archivo, const string& archivo2) {
    ofstream ofs(archivo);
    ofstream ofs2(archivo2);
    if (ofs.is_open()) {
        for (const auto& par : mapa) {
         ofs<< par.first << "\n";
        }
        ofs.close();
        cout << "Estadistica de buses guardada en  " << archivo << endl;
    } else {
        cerr << "No se pudo abrir el archivo " << archivo << endl;
    }


    if (ofs2.is_open()) {
        for (const auto& par : mapa) {
            ofs2 << par.second << "\n";
        }
        ofs2.close();
        cout << "Estadistica de buses guardada en  " << archivo2 << endl;
    } else {
        cerr << "No se pudo abrir el archivo " << archivo2 << endl;
    }
}
void guardarDias( string& nombreArchivo,vector<string>& datos){
	ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (auto dato : datos) {
            archivo << dato << endl;
        }
        archivo.close();
        //cout << "Vector guardado en archivo exitosamente." << endl;
    }
    else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
void imprimirUnorderedMap(unordered_map<string, int>& mapa) {
    for (auto it = mapa.begin(); it != mapa.end(); ++it) {
        cout << "Llave: " << it->first << ", Valor: " << it->second << endl;
    }
}
void imprimirEntrada(vector<int>& cantidadDeDigitosXDia,vector<string>& dias,int cantDias){
    int count = 0;
    for (int i = 0; i < cantDias; ++i){
    	string aux = "Dia: ";
		int numero = i;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	string name = aux + numero_str;
    	dias.push_back(name);
    }
    /*cout<<"Cantidad de digitos por dia"<<endl;
    for (int i = 0; i < cantDias; i++) {
    	cout << dias.at(i) <<": ";
        cout << cantidadDeDigitosXDia.at(count) << " ";
        cout << endl;
        count++;
        if (count>6){
        	count = 0;
        }
    }*/
    cout<<"Entrada leida correctamente"<<endl;
}
double calcularVarianza(unordered_map<string, int>& myMap) {
    int sum = 0;
    int count = 0;
    double mean = 0.0;
    double variance = 0.0;

    // Compute the mean
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        sum += it->second;
        count++;
    }
    mean = (double)sum / count;

    // Compute the variance
    for (auto it = myMap.begin(); it != myMap.end(); it++) {
        variance += pow((double)it->second - mean, 2);
    }
    variance /= count;

    return variance;
}
void imprimirSorteo(vector<vector<int>>& digitosXDiasSorteados){
	cout<<"Sorteo obtenido"<<endl;
	for (int i = 0; i < digitosXDiasSorteados.size(); ++i){
		//cout<<dias.at(i)<<": ";
		for (int j = 0; j < digitosXDiasSorteados.at(i).size(); ++j){
			cout<<digitosXDiasSorteados.at(i).at(j)<<" ";
		}
		cout<<endl;
	}
}
vector<vector<string>> cambiarFoliosANombres(vector<vector<string>> folios) {
    // Definimos los valores a reemplazar
    string fSot = "500766";
    string fAlce = "500768";
    string fExprc = "500767";
    string fPlaya = "500770";
    
    string sot = "Sotral";
    string alce = "Alce";
    string exprc = "ExpDelC";
    string playa = "PlayaBlanca";
    
    // Recorremos la matriz de folios
    for (int i = 0; i < folios.size(); i++) {
        for (int j = 0; j < folios[i].size(); j++) {
            // Reemplazamos los valores correspondientes
            if (folios[i][j] == fSot) {
                folios[i][j] = sot;
            } else if (folios[i][j] == fAlce) {
                folios[i][j] = alce;
            } else if (folios[i][j] == fExprc) {
                folios[i][j] = exprc;
            } else if (folios[i][j] == fPlaya) {
                folios[i][j] = playa;
            }
        }
    }
    
    // Devolvemos la matriz modificada
    return folios;
}
void guardarPlanificacionObtenidaEnArchivo(int& cantDias, vector<vector<string>>& planificacionObtenida,vector<vector<string>>&  planificacionObtenidaConFolios,vector<vector<string>>& planificacionObtenidaConNinternos,vector<vector<int>>& digitosXDiasSorteados){
	vector<string> nombreArchivos;
	for (int i = 0; i < cantDias; ++i){
		string aux = "Dia_";
		string aux2 = ".txt";
		int numero = i;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	string name = aux + numero_str;
		name = name + aux2;
		nombreArchivos.push_back(name);
	}
	for (int i = 0; i < planificacionObtenida.size(); ++i){
		guardarDias(nombreArchivos.at(i),planificacionObtenida.at(i));
	}
	vector<string> nombreArchivos5;
	for (int i = 0; i < cantDias; ++i){
		string aux = "numero_";
		string aux2 = ".txt";
		int numero = i;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	string name = aux + numero_str;
		name = name + aux2;
		nombreArchivos5.push_back(name);
	}
	for (int i = 0; i < planificacionObtenidaConNinternos.size(); ++i){
		guardarDias(nombreArchivos5.at(i),planificacionObtenidaConNinternos.at(i));
	}
	cout<<"Planificacion diaria guardada en archivo .txt con nombre del dia correspondiente"<<endl;
	vector<vector<string>> nombresFolios = cambiarFoliosANombres(planificacionObtenidaConFolios);
	vector<string> nombreArchivos2;
	for (int i = 0; i < cantDias; ++i){
		string aux = "FoliosDia_";
		string aux2 = ".txt";
		int numero = i;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	string name = aux + numero_str;
    	name = name + aux2;
		nombreArchivos2.push_back(name);
	}
	for (int i = 0; i < nombresFolios.size(); ++i){
		guardarDias(nombreArchivos2.at(i),nombresFolios.at(i));	
	}
 	// Crear archivo de Excel
	lxw_workbook* workbook = workbook_new("planificacion.xlsx");
	if (!workbook) {
	    cout << "No se pudo crear el archivo de salida." << endl;
	}
	// Crear hoja de Excel
	lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
	int count = 0;
	int count2 = 1;
	int count3 = 2;
	int count4 = 3;
	tm fecha;
    fecha.tm_year = 123; // Años desde 1900, por lo que 123 corresponde a 2023
    fecha.tm_mon = 3;    // Abril, pero empezando desde 0
    fecha.tm_mday = 10;  // Día del mes
	for (int i = 0; i < cantDias; ++i){
		string col1 = "Patentes";
		string col2 = "Linea";	
		string col3 = "nºInterno";	
		string col4 = "Hora";		
		string aux3 = "FoliosDia_";
		string aux = "Dia_";
		string aux6 = "numero_";
		string aux2 = ".txt";
		int numero = i;
		int fila = 0;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	char buffer[80];
   	 	strftime(buffer, 80, "%d/%m/%Y", &fecha); // Convertir la estructura tm a una cadena de caracteres
    	string fecha_string(buffer);
    	worksheet_write_string(worksheet, fila, i+count, numero_str.c_str(), NULL);
    	worksheet_write_string(worksheet, fila, i+count+3, fecha_string.c_str(), NULL);
    	fecha.tm_mday += 1;

    	string name = aux + numero_str;
    	string name2 = aux3 + numero_str;
    	string name6 = aux6 + numero_str;
		name = name + aux2;
		name2 = name2 + aux2;
		name6 = name6 + aux2;
		
		worksheet_write_string(worksheet, 1+fila, i+count, col1.c_str(), NULL);
		worksheet_write_string(worksheet, 1+fila, 1+i+count, col2.c_str(), NULL);
		worksheet_write_string(worksheet, 1+fila, 2+i+count, col3.c_str(), NULL);
		worksheet_write_string(worksheet, 1+fila, 3+i+count, col4.c_str(), NULL);


		ifstream inFile(name);
	    if (!inFile) {
	        cout << "No se pudo abrir el archivo de entrada." << endl;
	      
	    }
	    // Leer nombres de archivo de texto y escribir en hoja de Excel
	    string nombre;
	    
	    while (getline(inFile, nombre)) {
	        worksheet_write_string(worksheet, 2+fila, i+count, nombre.c_str(), NULL);
	        fila++;
	    }
	    count = count + 4;
	    // Cerrar archivos y liberar memoria
	    inFile.close();
	    ifstream inFile2(name2);
	    if (!inFile2) {
	        cout << "No se pudo abrir el archivo de entrada." << endl;
	      
	    }
	    // Leer nombres de archivo de texto y escribir en hoja de Excel
	    fila = 0;
	    while (getline(inFile2, nombre)) {
	        worksheet_write_string(worksheet, 2+fila, i+count2, nombre.c_str(), NULL);
	        fila++;
	    }
	    count2 = count2 + 4;
	    inFile2.close();
	    ifstream inFile6(name6);
	    if (!inFile6) {
	        cout << "No se pudo abrir el archivo de entrada." << endl;
	      
	    }
	    fila = 0;
	    
 		vector<string> horarios;
		tm horario = {};
		horario.tm_hour = 5;
		horario.tm_min = 0;
		horario.tm_sec = 0;
		time_t tiempo = mktime(&horario); // Convierte la estructura "tm" en un valor de tiempo "time_t"
		tm* horario_actual = localtime(&tiempo); // Convierte el valor de tiempo "time_t" en una estructura "tm"
		
		strftime(buffer, sizeof(buffer), "%H:%M:%S", horario_actual); // Formatea la hora en "HH:MM:SS"
		int flag = 0;
	    while (getline(inFile6, nombre)) {
	        worksheet_write_string(worksheet, 2+fila, i+count3, nombre.c_str(), NULL);
	        horario_actual->tm_min += 1; // Sumarle 30 minutos al horario actual
			time_t tiempo_actualizado = mktime(horario_actual);
			strftime(buffer, sizeof(buffer), "%H:%M:%S", horario_actual); // Formatea la hora en "HH:MM:SS"
			horarios.push_back(buffer);
			//cout << buffer << endl; 
	        worksheet_write_string(worksheet, 2+fila, i+count4, horarios.at(flag).c_str(), NULL);
	        
	        flag++;
	        fila++;
	    }
	    count3 = count3 + 4;
		count4 = count4 + 4;
		inFile6.close();
	}
	string nombre;
	vector<string> sorteo;
	for (int i = 0; i < digitosXDiasSorteados.size(); ++i){
		int second = 0;
		string key;
		for (int j = 0; j < digitosXDiasSorteados.at(i).size(); ++j){
			key = key +to_string(digitosXDiasSorteados.at(i).at(j));	
		}
		sorteo.push_back(key);
	}
	string archivoSorteo = "1-Sorteo.txt";
	ofstream archivoS(archivoSorteo);
	if (archivoS.is_open()) {
	    for (const auto& str : sorteo) {
	        archivoS << str << endl;
	    }
        archivoS.close();
    }
    ifstream inFile3(archivoSorteo);
    if (!inFile3) {
        cout << "No se pudo abrir el archivo de entrada." << endl;      
    }
	int var =0;
	while (getline(inFile3, nombre)) {
	    worksheet_write_string(worksheet, 0, 1+var, nombre.c_str(), NULL);
	 	var = var + 5;     
    }	   
	// Cerrar archivos y liberar memoria
	inFile3.close();
	vector<int> cantBusesSorteo;
	for (int i = 0; i < cantDias; ++i){
		cantBusesSorteo.push_back(planificacionObtenida.at(i).size());
	}
	string archivoFrecSort = "1-FrecuenciaSorteo.txt";
	ofstream archivoFS(archivoFrecSort);
    if (archivoFS.is_open()) {
        for (const auto& entero : cantBusesSorteo) {
            archivoFS << entero <<endl;
        }
        archivoFS.close();
    }
    ifstream inFile4(archivoFrecSort);
    if (!inFile4) {
        cout << "No se pudo abrir el archivo de entrada." << endl;      
    }
	var =0;
	while (getline(inFile4, nombre)) {
	    worksheet_write_string(worksheet, 0, 2+var,nombre.c_str(), NULL);
	 	var = var + 5;     
    }	   
	// Cerrar archivos y liberar memoria
	inFile4.close();
	workbook_close(workbook);
}
unordered_map<string, string> relacionar_patentes_con_folios(const vector<string>& folios, const vector<string>& patentes) {
  unordered_map<string, string> patentes_con_folios;
  for (int i = 0; i < patentes.size(); i++) {
    patentes_con_folios[patentes[i]] = folios[i];
  }
  return patentes_con_folios;
}
string encontrarFolio(string patenteBuscada, unordered_map<string,string> patentes) {
     auto iter = patentes.find(patenteBuscada);
    if (iter != patentes.end()) {
        return iter->second;
    }
    else {
        return "Patente no encontrada";
    }
}

//--------------------------------------------------------INICIO PROGRAMA---------------------------------------------------
int main() { //-lxlsxwriter
	//-------------------------------------------------INICIALIZACION DE VARIABLES------------------------------------------
	int min = 0;
	int max = 9;
	int cantDias = 30; // cantidad de dias a planificar
	vector<string> patentes;
	vector<int> cantidadDeDigitosXDia;
	vector<string> folios;
	vector<string> nMaquinas;
	vector<string> horarios;
	vector<vector<string>> planificacionObtenida;
	vector<vector<string>> planificacionObtenidaConFolios;
	vector<vector<string>> planificacionObtenidaConNinternos;
	vector<vector<string>> horasPlanificacion;
	vector<vector<string>> calcularPatentesXDigito;
   	vector<int> frecuenciaBusesXDigito; //cantidad de buses por digito del total existentes {150,124, ... , 100}
    vector<int> digitosPrimerDia;                                    
    vector<int> digitosRandom; //digitos dia inicial
	vector<int> digitosAnteriores;
    vector<int> digitosNuevoDia;
    vector<string> planificacionDia; 
    vector<string> planificacionDiaConFolio; 
    vector<string> planificacionDiaConNinterno; 
    vector<string> dias;
	vector<vector<int>> digitosXDiasSorteados; //lunes a domingo {1-2-3-4-5-6-7, 8-9-0-2-4-5, ... , 1,2,3,4,5} son 7
	vector<vector<int>> unDigitoXDia;
	unordered_map<string, int> mapaPatentes;
	unordered_map<string, int> mapaFrecXdigitoPat;
	unordered_map<string, string> mapaFolios;
	unordered_map<string, string> mapanMaquinas;
	int random; //numero aleatorio entre 0 y 9 por los numeros en las patentes
    //-------------------------------------------------INICIO DE ALGORITMO---------------------------------------------------
    digitosPrimerDia.push_back(7);
    digitosPrimerDia.push_back(8);
    digitosPrimerDia.push_back(9);
    digitosPrimerDia.push_back(0);
    digitosPrimerDia.push_back(1);
    srand (time(NULL));
    patentes = leerArchivoPatentes("0-patentes.txt");
    nMaquinas = leerFolios("0-nMaquinas.txt");
    horarios = leerFolios("0-horas.txt");
    cantidadDeDigitosXDia = leerArchivoDigitos("0-digitosDia.txt");
    folios = leerFolios("0-folios.txt");
    mapaFolios = relacionar_patentes_con_folios(folios,patentes);
    mapanMaquinas = relacionar_patentes_con_folios(nMaquinas,patentes);
    mapaPatentes = iniciarMapa(patentes);
    mapaFrecXdigitoPat = iniciarMapa(patentes);
    /*for (int i = 0; i < cantidadDeDigitosXDia.at(0); ++i){   //o definir digitos primer dia 
		random = escogoRandom(min, max,digitosRandom);
		digitosRandom.push_back(random); //guardo un digito en un vector con mi semilla completamente aleatoria para el lunes
	}*/
	for (int i = 0; i < 10; ++i){
		vector<int> vector;
		vector.push_back(i);
		unDigitoXDia.push_back(vector);
	}
   	imprimirEntrada(cantidadDeDigitosXDia,dias,cantDias);
   	digitosAnteriores = definirDigitosSiguientes(digitosPrimerDia); // ingresar dias anteriores a un vector
	digitosNuevoDia = digitosAnteriores; //los anteriore0s que no salieron sorteados
	int x = cantidadDeDigitosXDia.at(0);
	int y = digitosAnteriores.size();
	for (int j = 0 ; j < x - y ; ++j){ //completar sorteo del dia 
		int aux = escogoRandom(min,max,digitosNuevoDia);
		digitosNuevoDia.push_back(aux);
	}
	digitosXDiasSorteados.push_back(digitosNuevoDia); 
	planificacionDia = obtenerListado(digitosXDiasSorteados.at(0),patentes);
	orden_aleatorio(planificacionDia);
	contarPatentes(planificacionDia,mapaPatentes);
	for (int i = 0; i < planificacionDia.size(); ++i){
		string folio;
		string nInterno;
		nInterno = encontrarFolio(planificacionDia.at(i),mapanMaquinas);
		folio = encontrarFolio(planificacionDia.at(i),mapaFolios);
		planificacionDiaConFolio.push_back(folio);
		planificacionDiaConNinterno.push_back(nInterno);
	}
	planificacionObtenidaConFolios.push_back(planificacionDiaConFolio);
	planificacionObtenidaConNinternos.push_back(planificacionDiaConNinterno);
	planificacionObtenida.push_back(planificacionDia);
	planificacionDiaConNinterno.clear();
	planificacionDiaConFolio.clear();
	contarPatentes(planificacionDia,mapaPatentes);
	planificacionDia.clear();
	digitosAnteriores.clear();
	digitosNuevoDia.clear();
	int lim = 1;
	for (int i = 1; i < cantDias; ++i){
		digitosAnteriores = definirDigitosSiguientes(digitosXDiasSorteados.at(i-1)); // ingresar dias anteriores a un vector
		digitosNuevoDia = digitosAnteriores; //los anteriore0s que no salieron sorteados
		int a =cantidadDeDigitosXDia.at(lim);
		lim++;
		if (lim>6) lim = 0;
		int b = digitosAnteriores.size();
		for (int j = 0 ; j < a - b ; ++j){ //completar sorteo del dia 
			int aux = escogoRandom(min,max,digitosNuevoDia);
			digitosNuevoDia.push_back(aux);
		}
		digitosXDiasSorteados.push_back(digitosNuevoDia); 
		planificacionDia = obtenerListado(digitosXDiasSorteados.at(i),patentes);
		orden_aleatorio(planificacionDia);
		for (int i = 0; i < planificacionDia.size(); ++i){
			string folio;
			string nInterno;
			nInterno = encontrarFolio(planificacionDia.at(i),mapanMaquinas);
			folio = encontrarFolio(planificacionDia.at(i),mapaFolios);
			planificacionDiaConFolio.push_back(folio);
			planificacionDiaConNinterno.push_back(nInterno);	
		}
		planificacionObtenidaConFolios.push_back(planificacionDiaConFolio);
		planificacionObtenidaConNinternos.push_back(planificacionDiaConNinterno);
		planificacionObtenida.push_back(planificacionDia);
		planificacionDiaConNinterno.clear();
		planificacionDiaConFolio.clear();
		contarPatentes(planificacionDia,mapaPatentes);
		planificacionDia.clear();
		digitosAnteriores.clear();
		digitosNuevoDia.clear();
	}
	mapaPatentes.erase("");
	mapaFrecXdigitoPat.erase("");
	guardarPlanificacionObtenidaEnArchivo(cantDias,planificacionObtenida,planificacionObtenidaConFolios,planificacionObtenidaConNinternos,digitosXDiasSorteados);

	guardar_map_en_archivo(mapaPatentes, "2-ResultadosObtenidos.txt","2-FrecuenciaBusesObtenida.txt");
	double varianza = calcularVarianza(mapaPatentes);
	for (int i = 0; i < 10; ++i){
		vector<string> vec = obtenerListado(unDigitoXDia.at(i),patentes);
		calcularPatentesXDigito.push_back(vec);
		contarPatentes(vec,mapaFrecXdigitoPat);
	}
	vector<string> nombreArchivos3;
	for (int i = 0; i < 10; ++i){
		string aux = "2-PatentesCon_";
		string aux2 = ".txt";
		int numero = i;
    	stringstream ss;
    	ss << numero;
    	string numero_str = ss.str();
    	string name = aux + numero_str;
    	name = name + aux2;
		nombreArchivos3.push_back(name);
	}
	for (int i = 0; i < calcularPatentesXDigito.size(); ++i){
		guardarDias(nombreArchivos3.at(i),calcularPatentesXDigito.at(i));
	}		
	return 0;
}
