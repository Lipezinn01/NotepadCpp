#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_SALVAR_COMO 201
#define ID_SALVAR_TXT  202
#define ID_ABRIR       203
#define ID_FORMATAR    204
#define ID_AJUDA       205
#define ID_AREA_TEXTO  206

HWND hTexto;
bool modificado = false, qAutomatica = true;
int tamFonte = 11;
HFONT hFonte = NULL;

void AplicarFonte() {
    if (hFonte) DeleteObject(hFonte);
    hFonte = CreateFontW(tamFonte * 1.5, 0, 0, 0, 400, 0, 0, 0, 1, 0, 0, 0, 0, L"Consolas");
    SendMessage(hTexto, WM_SETFONT, (WPARAM)hFonte, TRUE);
}

void Abrir(HWND hw) {
    OPENFILENAMEW ofn = {}; wchar_t arq[MAX_PATH] = L"";
    ofn.lStructSize = sizeof(ofn); ofn.hwndOwner = hw; ofn.lpstrFile = arq; ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Texto (*.txt)\0*.txt\0Todos (*.*)\0*.*\0"; ofn.Flags = OFN_FILEMUSTEXIST;
    if (GetOpenFileNameW(&ofn)) {
        HANDLE f = CreateFileW(arq, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (f != INVALID_HANDLE_VALUE) {
            DWORD tam = GetFileSize(f, NULL), lidos; std::vector<char> b(tam + 1);
            ReadFile(f, b.data(), tam, &lidos, NULL); CloseHandle(f); b[tam] = 0;
            int wTam = MultiByteToWideChar(CP_UTF8, 0, b.data(), -1, NULL, 0);
            std::vector<wchar_t> wb(wTam); MultiByteToWideChar(CP_UTF8, 0, b.data(), -1, wb.data(), wTam);
            SetWindowTextW(hTexto, wb.data()); modificado = false;
            SetWindowTextW(hw, (L"Notepad - " + std::wstring(arq)).c_str());
        }
    }
}

void Salvar(HWND hw) {
    OPENFILENAMEW ofn = {}; wchar_t ca[MAX_PATH] = L"";
    ofn.lStructSize = sizeof(ofn); ofn.hwndOwner = hw; ofn.lpstrFile = ca; ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Todos os arquivos (*.*)\0*.*\0Texto (*.txt)\0*.txt\0";
    if (GetSaveFileNameW(&ofn)) {
        int t = GetWindowTextLengthW(hTexto); std::vector<wchar_t> b(t + 1); GetWindowTextW(hTexto, b.data(), t + 1);
        int uTam = WideCharToMultiByte(CP_UTF8, 0, b.data(), -1, NULL, 0, NULL, NULL);
        std::vector<char> ub(uTam); WideCharToMultiByte(CP_UTF8, 0, b.data(), -1, ub.data(), uTam, NULL, NULL);
        HANDLE f = CreateFileW(ca, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (f != INVALID_HANDLE_VALUE) { DWORD escritis; WriteFile(f, ub.data(), uTam - 1, &escritis, NULL); CloseHandle(f); modificado = false; }
    }
}

void SalvarTxt(HWND hw) {
    OPENFILENAMEW ofn = {}; wchar_t ca[MAX_PATH] = L"";
    ofn.lStructSize = sizeof(ofn); ofn.hwndOwner = hw; ofn.lpstrFile = ca; ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = L"Texto (*.txt)\0*.txt\0";
    if (GetSaveFileNameW(&ofn)) {
        int t = GetWindowTextLengthW(hTexto); std::vector<wchar_t> b(t + 1); GetWindowTextW(hTexto, b.data(), t + 1);
        int uTam = WideCharToMultiByte(CP_UTF8, 0, b.data(), -1, NULL, 0, NULL, NULL);
        std::vector<char> ub(uTam); WideCharToMultiByte(CP_UTF8, 0, b.data(), -1, ub.data(), uTam, NULL, NULL);
        HANDLE f = CreateFileW(ca, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (f != INVALID_HANDLE_VALUE) { DWORD escritis; WriteFile(f, ub.data(), uTam - 1, &escritis, NULL); CloseHandle(f); modificado = false; }
    }
}

void EscolherFonte(HWND hw) {
    CHOOSEFONTW cf = {}; LOGFONTW lf = {};
    cf.lStructSize = sizeof(cf); cf.hwndOwner = hw; cf.lpLogFont = &lf;
    cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
    if (ChooseFontW(&cf)) {
        if (hFonte) DeleteObject(hFonte);
        hFonte = CreateFontIndirectW(&lf);
        SendMessage(hTexto, WM_SETFONT, (WPARAM)hFonte, TRUE);
    }
}

WNDPROC oldEdit;
LRESULT CALLBACK EditProc(HWND hw, UINT m, WPARAM wp, LPARAM lp) {
    if (m == WM_CHAR) {
        wchar_t ch = (wchar_t)wp;
        if (ch != 8 && ch != 127 && ch != 13 && GetAsyncKeyState(VK_CONTROL) >= 0) {
            long long p = SendMessage(hw, EM_GETSEL, 0, 0); int tl = SendMessage(hw, EM_LINELENGTH, LOWORD(p), 0);
            if (tl >= 1024) { if (qAutomatica) SendMessage(hw, EM_REPLACESEL, TRUE, (LPARAM)L"\r\n"); else return 0; }
        }
    } return CallWindowProc(oldEdit, hw, m, wp, lp);
}

LRESULT CALLBACK WindowProc(HWND hw, UINT m, WPARAM wp, LPARAM lp) {
    switch (m) {
        case WM_CREATE: {
            HFONT fB = CreateFontW(15, 0, 0, 0, 400, 0, 0, 0, 1, 0, 0, 0, 0, L"Segoe UI");
            int ids[] = { ID_SALVAR_COMO, ID_SALVAR_TXT, ID_ABRIR, ID_FORMATAR, ID_AJUDA }, px[] = { 5, 120, 225, 390, 485 }, la[] = { 110, 100, 160, 90, 80 };
            const wchar_t* lbls[] = { L"Salvar Como...", L"Salvar .txt", L"Escolher Documento", L"Formatar", L"Ajuda" };
            for (int i = 0; i < 5; i++) {
                HWND b = CreateWindowExW(0, L"BUTTON", lbls[i], WS_CHILD | WS_VISIBLE, px[i], 5, la[i], 30, hw, (HMENU)(INT_PTR)ids[i], NULL, NULL);
                SendMessage(b, WM_SETFONT, (WPARAM)fB, TRUE);
            }
            hTexto = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, 5, 40, 875, 515, hw, (HMENU)ID_AREA_TEXTO, NULL, NULL);
            oldEdit = (WNDPROC)SetWindowLongPtr(hTexto, GWLP_WNDPROC, (LONG_PTR)EditProc);
            AplicarFonte(); return 0;
        }
        case WM_SIZE: MoveWindow(hTexto, 5, 40, LOWORD(lp) - 10, HIWORD(lp) - 45, TRUE); return 0;
        case WM_COMMAND:
            if (HIWORD(wp) == EN_CHANGE && LOWORD(wp) == ID_AREA_TEXTO) modificado = true;
            switch (LOWORD(wp)) {
                case ID_SALVAR_COMO: Salvar(hw); break;
                case ID_SALVAR_TXT: SalvarTxt(hw); break;
                case ID_ABRIR: Abrir(hw); break;
                case ID_FORMATAR: {
                    HMENU hMenu = CreatePopupMenu();
                    std::wstring txtQuebra = qAutomatica ? L"✓ Quebra de Linha Automática" : L"Quebra de Linha Manual";
                    AppendMenuW(hMenu, MF_STRING, 901, txtQuebra.c_str());
                    AppendMenuW(hMenu, MF_STRING, 902, L"Fontes...");
                    
                    // Pega a posição do botão Formatar para abrir o menu logo abaixo dele
                    RECT rc; GetWindowRect(GetDlgItem(hw, ID_FORMATAR), &rc);
                    int x = rc.left; int y = rc.bottom;
                    
                    int selecao = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, x, y, 0, hw, NULL);
                    DestroyMenu(hMenu);
                    
                    if (selecao == 901) {
                        qAutomatica = !qAutomatica;
                        MessageBoxW(hw, qAutomatica ? L"✅ Quebra AUTOMÁTICA ativada!" : L"⚠️ Quebra MANUAL ativada!", L"Quebra de Linha", MB_OK | MB_ICONINFORMATION);
                    } else if (selecao == 902) {
                        EscolherFonte(hw);
                    }
                    break;
                }

                case ID_AJUDA:
                    MessageBoxW(hw, L"AJUDA DO NOTEPAD\n\nAtalhos:\nCTRL+S: Salvar\nCTRL+O: Abrir\nCTRL+N: Formatar", L"Ajuda", MB_OK);
                    break;
            } return 0;
        case WM_CLOSE:
            if (modificado && MessageBoxW(hw, L"Deseja salvar antes de sair?", L"Aviso", MB_YESNO) == IDYES) Salvar(hw);
            DestroyWindow(hw); return 0;
        case WM_DESTROY: PostQuitMessage(0); return 0;
    } return DefWindowProcW(hw, m, wp, lp);
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nS) {
    InitCommonControls();
    WNDCLASSW c = {}; c.lpfnWndProc = WindowProc; c.hInstance = hI; c.lpszClassName = L"NP";
    c.hCursor = LoadCursor(NULL, IDC_ARROW); c.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    RegisterClassW(&c);
    HWND hw = CreateWindowExW(0, L"NP", L"Notepad - Sem título", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600, NULL, NULL, hI, NULL);
    ShowWindow(hw, nS);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (GetAsyncKeyState(VK_CONTROL) < 0) {
            if (GetAsyncKeyState('S') < 0) { Salvar(hw); Sleep(150); }
            else if (GetAsyncKeyState('O') < 0) { Abrir(hw); Sleep(150); }
            else if (GetAsyncKeyState('N') < 0) { qAutomatica = !qAutomatica; Sleep(150); }
        }
        TranslateMessage(&msg); DispatchMessage(&msg);
    } return 0;
}
