#include <string>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <format>
#include <Windows.h>
#include <codecvt>
#include <fstream>
#pragma warning(disable : 4996)

using namespace std;
using namespace std::filesystem;
vector <wstring> music = { L"sorted\\music", L".mp3", L".ogg" , L".wav" };
vector <wstring> executable = { L"sorted\\executable", L".exe", L".bat" , L".apk" };
vector <wstring> video = { L"sorted\\video", L".avi", L".mpg" , L".mov" };
vector <wstring> archive = { L"sorted\\archive", L".zip", L".rar" , L".7z" };
vector <wstring> text = { L"sorted\\text", L".txt", L".text" , L".log" };
vector <wstring> picture = { L"sorted\\picture", L".jpg", L".png" , L".bmp" };
vector <vector <wstring>> types = { music, executable, video, archive, text, picture };
vector <string> dirs = { "sorted\\music", "sorted\\executable", "sorted\\video", "sorted\\archive", "sorted\\text", "sorted\\picture" };
// = { ".mp3", ".ogg" , ".wav" }
// = { ".exe", ".bat" , ".apk"}


bool moveToDirAuto(wstring pathdir, wstring rootdir)
{
    path pathdir1(pathdir);
    for (vector <wstring> a: types)
    {
        for (wstring ext : a)
        {
            bool r = ext == pathdir1.extension();
            if (r)
            {
                wstring b = pathdir1.filename();
                wstring g = rootdir + L"\\" + a[0] + L"\\" + b;
                wstring path = wstring(g.begin(), g.end());
                LPCWSTR result = path.c_str();
                if (pathdir1.c_str() == result) { return true; }

                if (MoveFile(pathdir1.c_str(), result) != 0)
                {
                    switch (GetLastError())
                    {
                    case ERROR_FILE_NOT_FOUND:
                        printf("ERR: File not found\n");
                        return false;
                    case ERROR_ALREADY_EXISTS:
                        printf("ERR: File already exists\n");
                        return false;
                    default:
                        printf("ERR: %d\n", GetLastError());
                        if (GetLastError() != 0)
                        {
                            return false;
                        }

                    }
                }
                return true;
            }
        }
    }

    if (pathdir1.extension() != "") 
    {
        wstring b = pathdir1.filename();
        wstring a = rootdir + L"\\sorted\\other\\" + b;
        wstring path = wstring(a.begin(), a.end());
        LPCWSTR result = path.c_str();
        if (pathdir1.c_str() == result) { return true; }
        
        if (MoveFile(pathdir1.c_str(), result) != 0)
        {
            switch (GetLastError())
            {
            case ERROR_FILE_NOT_FOUND:
                printf("ERR: File not found\n");
                return false;
            case ERROR_ALREADY_EXISTS:
                printf("ERR: File already exists\n");
                return false;
            default:
                printf("ERR: %d\n", GetLastError());
                if (GetLastError() != 0)
                {
                    return false;
                }

            }
        }
        return true;
    }
    return true;
}

bool getPathes(wstring pathdir, bool withInclusions, wstring root)
{
    bool flag = true;
    for (auto& p : directory_iterator(pathdir.c_str()))
    {
        path pathdir1(p);
        bool res = moveToDirAuto(pathdir1, root);
        if (flag and !res) { flag = false; }
        if (pathdir1.extension() == "" and withInclusions)
        {
            getPathes(pathdir1, withInclusions, root);
        }
    }
    return flag;
}


int main()
{
    ifstream file("temp.txt");
    bool trig;
    string root = "";
    string f;
    getline(file, root);
    getline(file, f);
    if (f == "1") { trig = true; } else { trig = false; }
    wstring rootw = wstring(root.begin(), root.end());
    file.close();
    
    setlocale(LC_ALL, "rus");
    char b[MAX_PATH] = "cd ";
    strcat(b, root.c_str());
    strcat(b, " & mkdir sorted");
    system(b);
    for (string c : dirs)
    {
        char b[MAX_PATH] = "cd ";
        strcat(b, root.c_str());
        strcat(b, " & mkdir ");
        strcat(b, c.c_str());
        system(b);
    }
    char c[MAX_PATH] = "cd ";
    strcat(c, root.c_str());
    strcat(c, " & mkdir sorted\\other");
    system(c);

    bool a = getPathes(rootw, trig, rootw);
    cout << a;
}