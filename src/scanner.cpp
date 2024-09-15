#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
using namespace std;

char* text_Arr = nullptr;
int index = 0;
int sizee = 0;
int line_global = 0;
int col_global = 1;

struct token {
    string token_name;
    string text;
    int line;
    int col;
    token(string N_, string T_, int L_, int C_) { token_name = N_; text = T_; line = L_; col = C_; }
};

vector<token>tokens;

map<string, string> tokens_list = {
    pair<string,string>("boolean","TOKEN_BOOLEAN"),
    pair<string,string>("char","TOKEN_CHAR"),
    pair<string,string>("array","TOKEN_ARRAY"),
    pair<string,string>("else","TOKEN_ELSE"),
    pair<string,string>("false","TOKEN_FALSE"),
    pair<string,string>("for","TOKEN_FOR"),
    pair<string,string>("function","TOKEN_FUNCTION"),
    pair<string,string>("if","TOKEN_IF"),
    pair<string,string>("integer","TOKEN_INTEGER"),
    pair<string,string>("print","TOKEN_PRINT"),
    pair<string,string>("return","TOKEN_RETURN"),
    pair<string,string>("string","TOKEN_STRING"),
    pair<string,string>("true","TOKEN_TRUE"),
    pair<string,string>("void","TOKEN_VOID"),
    pair<string,string>("while","TOKEN_WHILE"),

    pair<string,string>("[","TOKEN_["),
    pair<string,string>("]","TOKEN_]"),
    pair<string,string>("++","TOKEN_++"),
    pair<string,string>("--","TOKEN_--"),
    pair<string,string>("-","TOKEN_NEGNUM"),
    pair<string,string>("!","TOKEN_NEGEXPR"),
    pair<string,string>("^","TOKEN_EXPONEN"),
    pair<string,string>("*","TOKEN_MULT"),
    pair<string,string>("/","TOKEN_DIV"),
    pair<string,string>("%","TOKEN_MOD"),
    pair<string,string>("+","TOKEN_SUM"),
    pair<string,string>("-","TOKEN_SUB"),
    pair<string,string>("<","TOKEN_<"),
    pair<string,string>("<=","TOKEN_<="),
    pair<string,string>(">","TOKEN_>"),
    pair<string,string>(">=","TOKEN_>="),
    pair<string,string>("==","TOKEN_WHILE"),
    pair<string,string>("!=","TOKEN_WHILE"),
    pair<string,string>("=","TOKEN_WHILE"),
    pair<string,string>("&&","TOKEN_AND"),
    pair<string,string>("||","TOKEN_OR"),
    pair<string,string>(";","TOKEN_END"),
    pair<string,string>("\'","TOKEN_COMILLA"),
    pair<string,string>("\"","TOKEN_COMILLA_DOBLE"),
    pair<string,string>(",","TOKEN_SEPARATION"),
    pair<string,string>("//","TOKEN_COMLINE"),
    pair<string,string>("/*","TOKEN_COMBLOCKS"), //COMMENT BLOCK START
    pair<string,string>("*/","TOKEN_COMBLOCKE"), //   ''    ''   END

};

bool Find_char(char a) {
    if (int(a) > 64 && int(a) < 91 || int(a) > 96 && int(a) < 122 || int(a) == 95) { return true; }
    else return false;  //revisa que sea char permitido
}

bool Find_int(char a) {
    if (int(a) > 47 && int(a) < 58) { return true; }
    else return false;
} // revisa que sea int permitido

bool Find_symbol(char a) {  //lo mismo pero para simbolos ya que tipo para errores de id como hol@c deberia salir fallo pero cortaba de frente en el hol, asi q con esto
    //quiero hacer que los lea normal pero cuando es uno de estos simbolos pues que sepa q es un simbolo que si es perteneciente al lenguaje por lo que puede tener otro token
    string symbols = "[]+-*/%=!&|<>; \'\",";
    return symbols.find(a) != string::npos;
}


void read_file(const string& filename, char*& content, int& size) {
    ifstream file(filename, ios::binary | ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        file.seekg(0, ios::beg);  //regresa al inicio

        content = new char[size];
        file.read(content, size);
        file.close();
    }
    else {
        std::cerr << "No se puede abrir el archivo :c" << std::endl;
        content = nullptr;
        size = 0;
    }
}


char get_char() {
    if (index < sizee) {
        return text_Arr[index++]; //agarra el actual y mueve el puntero
    }
    else { return '\0'; }
}

char peek_char() {
    if (index + 1 < sizee) {  // revisa el siguiente sin mover puntero
        int tmp = index + 1;
        return text_Arr[tmp];
    }
    return '\0';

}

char peek_actual_char() {
    if (index < sizee) {
        return text_Arr[index];   // revisa el actual sin mover puntero
    }
    return '\0';
}


void scanner(char* buffer) {
    string word;
    char letter;
    cout << index << endl;
    cout << sizee << endl;
    while (index < sizee) {
        
        letter = peek_actual_char();
        word = "";
        if (letter == '#') { break; }
        if (letter == '\n' || letter == ' ' || letter == '\r') {
            get_char(); //salta espacios en blanco y eso
            line_global++;
            col_global = 1;
            continue;
        }
        else if (Find_char(letter) == true) {
            bool valid_identifier = true;
            while (Find_char(peek_char()) == true || Find_int(peek_char()) == true || !Find_symbol(peek_char())==true) {
                word += get_char();  // si encuentra algo que no cuadra, tipo un simbolo que no pertenece al alfabeto
                if (!Find_char(peek_actual_char()) && !Find_int(peek_actual_char())) {
                    valid_identifier = false;
                }
            }

            word += get_char();
            if (tokens_list.find(word) != tokens_list.end()) {
                cout << tokens_list[word] << endl;
            }

            else if (valid_identifier) { //si es valido se guarda como id
                cout << word << " TOKEN_ID" << endl;
                //   tokens.push_back(token("TOKEN_ID", word, line_global, col_global));
            }
            else { // sino fallo
                //tocaria crear algun lugar donde guardar los errores y hacer el conteo de lineas y columnas q es en si solo ir aumentando la columna
                //y cuando encuentre un \n pues q reinicie col y aumente linea
                cout << "Error: Identificador inválido '" << word << endl;
            }
        }

        else if (Find_int(letter) == true) {
            bool valid_identifier = true;
            while (Find_int(peek_char()) == true || !Find_symbol(peek_char())) {
                word += get_char();
                // Si encontramos algo que no es un número ni un símbolo permitido, es error
                if (!Find_int(peek_actual_char()) && !Find_symbol(peek_actual_char())) {
                    valid_identifier = false;
                }
            }
            word += get_char();  // Añadir el último carácter leído
            if (valid_identifier) {
                cout << word << " TOKEN_NUM" << endl;
            }
            else {
                cout << "Error: Número inválido '" << word << endl;
            }
        }

        else if (letter == '/') {
            if (peek_char() == '*') {
                get_char();
                get_char();
                cout << tokens_list["/*"] << endl;
                while (peek_char() != '/' && peek_actual_char() != '*') {
                    get_char();
                }
                get_char();
                get_char();
                cout << tokens_list["*/"] << endl;
            }
            else if (peek_char() == '/') {
                get_char();
                get_char();  //porque son 2 simbolos
                cout << tokens_list["//"] << endl;
                while (peek_actual_char() != '\n') {
                    get_char();  //salta todo hasta q termine la linea
                }
            }
            else { cout << tokens_list[to_string(letter)] << endl; }
        }
        else {
            get_char(); //por ahora que estoy probando y sin esto se queda en bucle
        }
    }
}


int main() {
    string filename = "C:/codes/Compiladores/code.txt";
    read_file(filename, text_Arr, sizee);

    /*     if(text_Arr!=nullptr){
            for (int i = 0; i < size;i++){
                if (text_Arr[i] == '\n'){
                    cout << "salto de linea" << endl;
                }
                else {
                    cout << text_Arr[i];
                }
            }
        } */
    scanner(text_Arr);

    /*     cout<<Find_char('b')<<endl;
        cout<<Find_char('5')<<endl;
        cout<<Find_char('V')<<endl;
        cout<<Find_char('_')<<endl;
        cout<<Find_char('?')<<endl; */

    return 0;
}
