#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <streambuf>
#include <thread>
#include <chrono>
#include <tchar.h>
#include <map>

std::string getFileText(){
    std::ifstream t("input.txt");
    std::string str;
    std::string file_contents;
    while(std::getline(t, str)){
        file_contents += str;
        file_contents.push_back('\n');
    }
    return file_contents;
}

std::vector<unsigned char> Transform(std::vector<unsigned char> v){

    return v;
}

int SimulateKeyPress(std::vector<wchar_t> v){
    byte simb; 
    HKL kbl = GetKeyboardLayout(0x4090409);
    for(int i = 0; i<v.size(); i++){
        std::cout << '\n' << std::hex << (int)v[i] - 0x20;
        //*
        INPUT inp;  
        inp.type = INPUT_KEYBOARD;
        inp.ki.time = 0;
        inp.ki.dwExtraInfo = 0;
        inp.ki.wVk = 0;
        inp.ki.dwFlags = KEYEVENTF_UNICODE;
        inp.ki.wScan = v[i] - 0x20;
        inp.ki.wVk = VkKeyScanEx(v[i] - 0x20, kbl);
        if(v[i+1] == 0x20)
            inp.ki.wVk = 0x20;
        SendInput(1, &inp, sizeof(inp));//*/
        Sleep(5);
    }
    return 0;
}

int SimulateKeyPressRusCopy(std::vector<wchar_t> v){
    byte simb; 
    for(int i = 0; i<v.size(); i++){
        std::cout << '\n' << std::hex << (int)v[i] - 0x20;
        //*
        INPUT inp;  
        inp.type = INPUT_KEYBOARD;
        inp.ki.time = 0;
        inp.ki.dwExtraInfo = 0;
        inp.ki.wVk = 0;
        inp.ki.dwFlags = KEYEVENTF_UNICODE;
        inp.ki.wScan = v[i] - 0x20;
        inp.ki.wVk = v[i] - 0x20;
        if(v[i+1] == 0x20)
            inp.ki.wVk = 0x20;
        SendInput(1, &inp, sizeof(inp));//*/
        Sleep(20);
    }
    return 0;
}

int indexof(std::string templ, wchar_t wch){
    //std::cout << "\nindex of start\n";
    //std::cout << std::hex << wch << "\n";
    int ind = 0;
    for(int i = 0; i<templ.length(); i++){
        if(templ[i+1] - 0xffff0000 == wch){        
            //std::cout << "\nindex of end in for with i: " << i;
            return ind;
        }
        i++;
        ind++;
    }
    //std::cout << "index of end\n";
    return -1;
}

wchar_t check_special_char(wchar_t ch){
    switch(ch){
        case ',':
        return 0xbc + 0x20;
        case '`':
        return 0xc0 + 0x20;
        case ';':
        return 0xba + 0x20;
        case '[':
        return 0xdb + 0x20;
        case ']':
        return 0xdd + 0x20;
        case '\'':
        return 0xde + 0x20;
        case '.':
        return 0xbe + 0x20;
        case '\n':
        return 0x0d + 0x20;
        default:
        return ch;
    }
}

std::vector<wchar_t> converter(std::vector<wchar_t> vec){
    std::vector<wchar_t> result;
    std::string rus = "абвгдеёжзийклмнопрстуфхцчшщЪыьэюя\n";
    std::string eng = "f,dult`;pbqrkvyjghcnea[wxio]sm'.z\n";
    std::cout << "\nconverter\n";
    wchar_t temp;
    int ind_of_eng;
    for(int i = 0; i<vec.size(); i++){
        ind_of_eng = indexof(rus, vec[i+1]);
        temp = eng[ind_of_eng];
        if (ind_of_eng == 0xffffffff){
            if(vec[i] == 0xa){
                result.push_back(check_special_char('\n'));
                i--;
            }
            else{
                result.push_back(check_special_char(temp));
                result.push_back(' ');
                i--;
            }
        } 
        else{
            result.push_back(check_special_char(temp));
        }
        std::cout << std::hex << vec[i+1] << "\n";
        std::cout << " ind_of_eng: " << (int)ind_of_eng << "\n";
        i++;
    }
    return result;
}

int main(){
    //std::string path;
    //std::cin >> path;
    //setlocale(LC_ALL, "rus");
    Sleep(5000);
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::string text = getFileText();
    std::cout << text << " " << text.length();
    std::vector<wchar_t> v;
    std::vector<std::string> test;
    for(char i : text){
        v.push_back(i);
        std::string s(1,i);
        test.push_back(s);
        s="";
    }
    //SimulateKeyPress(v);
    std::cout << "\n" << "==============\n" ;
    v = converter(v);
        
    //SimulateKeyPress(v);
    SimulateKeyPressRusCopy(v);

    HKL kb = GetKeyboardLayout(0);
    std::cout << '\n' << kb;
    return 0;
}