#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <cstring>

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_SALVAR_COMO 201
#define ID_SALVAR_TXT  202
#define ID_ABRIR       203
#define ID_FORMATAR    204
#define ID_AJUDA       205
#define ID_IDIOMAS     207
#define ID_AREA_TEXTO  206

#define ID_LANG_EN     301
#define ID_LANG_PT     302
#define ID_LANG_ES     303
#define ID_RESTART     304
#define ID_CANCEL      305

HWND hTexto;
bool modificado = false, qAutomatica = true;
int tamFonte = 11;
HFONT hFonte = NULL;
HFONT hFonteBotoes = NULL;
int idioma = 1;

WNDPROC oldEdit;

// ============================================================
// TEXTOS DOS IDIOMAS
// ============================================================

struct Textos {
    const wchar_t* salvarComo;
    const wchar_t* salvarTxt;
    const wchar_t* abrir;
    const wchar_t* formatar;
    const wchar_t* ajuda;
    const wchar_t* idiomas;

    const wchar_t* titulo;
    const wchar_t* semTitulo;

    const wchar_t* ajudaTexto;
    const wchar_t* ajudaTitulo;

    const wchar_t* quebraAutomatica;
    const wchar_t* quebraManual;
    const wchar_t* fontes;

    const wchar_t* avisoQuebraAuto;
    const wchar_t* avisoQuebraManual;
    const wchar_t* tituloQuebra;

    const wchar_t* salvarAntes;
    const wchar_t* aviso;

    const wchar_t* escolherIdioma;
    const wchar_t* restart;
    const wchar_t* cancelar;
    const wchar_t* restartTexto;
    const wchar_t* restartTitulo;

    const wchar_t* filtroTodos;
    const wchar_t* filtroTexto;
};

Textos textos[3] = {

    // ENGLISH
    {
        L"Save As...",
        L"Save .txt",
        L"Open",
        L"Format",
        L"Help",
        L"Language",

        L"Notepad",
        L"Untitled",

        L"NOTEPAD HELP\n\nShortcuts:\nCTRL+S: Save\nCTRL+O: Open\nCTRL+N: Toggle automatic line break",
        L"Help",

        L"✓ Automatic Line Break",
        L"Manual Line Break",
        L"Fonts...",

        L"Automatic line break ENABLED!",
        L"Manual line break ENABLED!",
        L"Line Break",

        L"Do you want to save before exiting?",
        L"Warning",

        L"Choose Language",
        L"Restart",
        L"Cancel",
        L"Language changed successfully.\n\nRestart the program to apply the new language.",
        L"Restart Required",

        L"All files (*.*)",
        L"Text (*.txt)"
    },

    // PORTUGUÊS
    {
        L"Salvar Como...",
        L"Salvar .txt",
        L"Abrir",
        L"Formatar",
        L"Ajuda",
        L"Idiomas",

        L"Notepad",
        L"Sem título",

        L"AJUDA DO NOTEPAD\n\nAtalhos:\nCTRL+S: Salvar\nCTRL+O: Abrir\nCTRL+N: Alternar quebra de linha automática",
        L"Ajuda",

        L"✓ Quebra de Linha Automática",
        L"Quebra de Linha Manual",
        L"Fontes...",

        L"Quebra de linha AUTOMÁTICA ativada!",
        L"Quebra de linha MANUAL ativada!",
        L"Quebra de Linha",

        L"Deseja salvar antes de sair?",
        L"Aviso",

        L"Escolher Idioma",
        L"Reiniciar",
        L"Cancelar",
        L"Idioma alterado com sucesso.\n\nReinicie o programa para aplicar o novo idioma.",
        L"Reinicialização Necessária",

        L"Todos os arquivos (*.*)",
        L"Texto (*.txt)"
    },

    // ESPAÑOL
    {
        L"Guardar Como...",
        L"Guardar .txt",
        L"Abrir",
        L"Formato",
        L"Ayuda",
        L"Idiomas",

        L"Notepad",
        L"Sin título",

        L"AYUDA DEL NOTEPAD\n\nAtajos:\nCTRL+S: Guardar\nCTRL+O: Abrir\nCTRL+N: Alternar salto de línea automático",
        L"Ayuda",

        L"✓ Salto de Línea Automático",
        L"Salto de Línea Manual",
        L"Fuentes...",

        L"¡Salto de línea AUTOMÁTICO activado!",
        L"¡Salto de línea MANUAL activado!",
        L"Salto de Línea",

        L"¿Desea guardar antes de salir?",
        L"Aviso",

        L"Elegir Idioma",
        L"Reiniciar",
        L"Cancelar",
        L"Idioma cambiado correctamente.\n\nReinicie el programa para aplicar el nuevo idioma.",
        L"Reinicio Necesario",

        L"Todos los arquivos (*.*)",
        L"Texto (*.txt)"
    }
};

const Textos& T() {
    return textos[idioma - 1];
}

// ============================================================
// LANG.DAT
// ============================================================

std::wstring CaminhoLang() {

    wchar_t caminho[MAX_PATH] = {};

    if (GetEnvironmentVariableW(
        L"LOCALAPPDATA",
        caminho,
        MAX_PATH
    ) == 0) {
        return L"lang.dat";
    }

    std::wstring pasta =
        std::wstring(caminho) +
        L"\\NotepadCpp";

    CreateDirectoryW(
        pasta.c_str(),
        NULL
    );

    return pasta + L"\\lang.dat";
}

// ============================================================
// LER LANG.DAT
// ============================================================

void LerIdioma() {

    idioma = 1;

    HANDLE f = CreateFileW(
        CaminhoLang().c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (f == INVALID_HANDLE_VALUE) {
        CriarLangPadrao();
        return;
    }

    char texto[16] = {};
    DWORD lidos = 0;

    BOOL ok = ReadFile(
        f,
        texto,
        sizeof(texto) - 1,
        &lidos,
        NULL
    );

    CloseHandle(f);

    if (!ok)
        return;

    texto[lidos] = '\0';

    if (strcmp(texto, "L:1") == 0)
        idioma = 1;

    else if (strcmp(texto, "L:2") == 0)
        idioma = 2;

    else if (strcmp(texto, "L:3") == 0)
        idioma = 3;

    else
        idioma = 1;
}

// ============================================================
// GRAVAR LANG.DAT
// ============================================================

bool GravarIdioma(int novoIdioma) {

    const char* texto = NULL;

    if (novoIdioma == 1)
        texto = "L:1";

    else if (novoIdioma == 2)
        texto = "L:2";

    else if (novoIdioma == 3)
        texto = "L:3";

    else
        return false;

    HANDLE f = CreateFileW(
        CaminhoLang().c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (f == INVALID_HANDLE_VALUE)
        return false;

    DWORD escritos = 0;

    BOOL ok = WriteFile(
        f,
        texto,
        3,
        &escritos,
        NULL
    );

    CloseHandle(f);

    return ok && escritos == 3;
}

// ============================================================
// FILTRO DE ARQUIVOS
// ============================================================

std::wstring FiltroAbrir() {

    std::wstring f;

    f += T().filtroTexto;
    f.push_back(L'\0');
    f += L"*.txt";
    f.push_back(L'\0');

    f += T().filtroTodos;
    f.push_back(L'\0');
    f += L"*.*";
    f.push_back(L'\0');

    f.push_back(L'\0');

    return f;
}

std::wstring FiltroSalvar() {

    std::wstring f;

    f += T().filtroTodos;
    f.push_back(L'\0');
    f += L"*.*";
    f.push_back(L'\0');

    f += T().filtroTexto;
    f.push_back(L'\0');
    f += L"*.txt";
    f.push_back(L'\0');

    f.push_back(L'\0');

    return f;
}

// ============================================================
// FONTE
// ============================================================

void AplicarFonte() {

    if (hFonte)
        DeleteObject(hFonte);

    hFonte = CreateFontW(
        (int)(tamFonte * 1.5),
        0, 0, 0,
        400,
        0, 0, 0,
        1, 0, 0, 0, 0,
        L"Consolas"
    );

    SendMessageW(
        hTexto,
        WM_SETFONT,
        (WPARAM)hFonte,
        TRUE
    );
}

// ============================================================
// ABRIR
// ============================================================

void Abrir(HWND hw) {

    OPENFILENAMEW ofn = {};
    wchar_t arq[MAX_PATH] = L"";

    std::wstring filtro = FiltroAbrir();

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hw;
    ofn.lpstrFile = arq;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = filtro.c_str();
    ofn.Flags = OFN_FILEMUSTEXIST;

    if (!GetOpenFileNameW(&ofn))
        return;

    HANDLE f = CreateFileW(
        arq,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (f == INVALID_HANDLE_VALUE)
        return;

    DWORD tam = GetFileSize(f, NULL);

    if (tam == INVALID_FILE_SIZE && GetLastError() != NO_ERROR) {
        CloseHandle(f);
        return;
    }

    std::vector<char> b(tam + 1);

    DWORD lidos = 0;

    BOOL ok = ReadFile(
        f,
        b.data(),
        tam,
        &lidos,
        NULL
    );

    CloseHandle(f);

    if (!ok)
        return;

    b[lidos] = '\0';

    int wTam = MultiByteToWideChar(
        CP_UTF8,
        0,
        b.data(),
        lidos,
        NULL,
        0
    );

    if (wTam <= 0)
        return;

    std::vector<wchar_t> wb(wTam + 1);

    MultiByteToWideChar(
        CP_UTF8,
        0,
        b.data(),
        lidos,
        wb.data(),
        wTam
    );

    wb[wTam] = L'\0';

    SetWindowTextW(
        hTexto,
        wb.data()
    );

    modificado = false;

    std::wstring titulo =
        std::wstring(T().titulo) +
        L" - " +
        arq;

    SetWindowTextW(
        hw,
        titulo.c_str()
    );
}

// ============================================================
// SALVAR
// ============================================================

void Salvar(HWND hw) {

    OPENFILENAMEW ofn = {};
    wchar_t ca[MAX_PATH] = L"";

    std::wstring filtro = FiltroSalvar();

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hw;
    ofn.lpstrFile = ca;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = filtro.c_str();

    if (!GetSaveFileNameW(&ofn))
        return;

    int t = GetWindowTextLengthW(hTexto);

    std::vector<wchar_t> b(t + 1);

    GetWindowTextW(
        hTexto,
        b.data(),
        t + 1
    );

    int uTam = WideCharToMultiByte(
        CP_UTF8,
        0,
        b.data(),
        -1,
        NULL,
        0,
        NULL,
        NULL
    );

    if (uTam <= 0)
        return;

    std::vector<char> ub(uTam);

    WideCharToMultiByte(
        CP_UTF8,
        0,
        b.data(),
        -1,
        ub.data(),
        uTam,
        NULL,
        NULL
    );

    HANDLE f = CreateFileW(
        ca,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (f == INVALID_HANDLE_VALUE)
        return;

    DWORD escritos = 0;

    BOOL ok = WriteFile(
        f,
        ub.data(),
        uTam - 1,
        &escritos,
        NULL
    );

    CloseHandle(f);

    if (ok && escritos == (DWORD)(uTam - 1))
        modificado = false;
}

// ============================================================
// ESCOLHER FONTE
// ============================================================

void EscolherFonte(HWND hw) {

    CHOOSEFONTW cf = {};
    LOGFONTW lf = {};

    cf.lStructSize = sizeof(cf);
    cf.hwndOwner = hw;
    cf.lpLogFont = &lf;
    cf.Flags =
        CF_SCREENFONTS |
        CF_INITTOLOGFONTSTRUCT;

    if (ChooseFontW(&cf)) {

        if (hFonte)
            DeleteObject(hFonte);

        hFonte = CreateFontIndirectW(&lf);

        SendMessageW(
            hTexto,
            WM_SETFONT,
            (WPARAM)hFonte,
            TRUE
        );
    }
}

// ============================================================
// PROCEDIMENTO DO EDIT
// ============================================================

LRESULT CALLBACK EditProc(
    HWND hw,
    UINT m,
    WPARAM wp,
    LPARAM lp
) {

    if (m == WM_CHAR) {

        wchar_t ch = (wchar_t)wp;

        if (
            ch != 8 &&
            ch != 127 &&
            ch != 13 &&
            GetAsyncKeyState(VK_CONTROL) >= 0
        ) {

            DWORD inicio = 0;
            DWORD fim = 0;

            SendMessageW(
                hw,
                EM_GETSEL,
                (WPARAM)&inicio,
                (LPARAM)&fim
            );

            int tl = (int)SendMessageW(
                hw,
                EM_LINELENGTH,
                inicio,
                0
            );

            if (tl >= 1024) {

                if (qAutomatica) {

                    SendMessageW(
                        hw,
                        EM_REPLACESEL,
                        TRUE,
                        (LPARAM)L"\r\n"
                    );
                }

                else {
                    return 0;
                }
            }
        }
    }

    return CallWindowProcW(
        oldEdit,
        hw,
        m,
        wp,
        lp
    );
}

// ============================================================
// DADOS DAS JANELAS AUXILIARES
// ============================================================

struct DadosJanela {
    int* resultado;
};

// ============================================================
// PROCEDIMENTO DAS JANELAS AUXILIARES
// ============================================================

LRESULT CALLBACK AuxWindowProc(
    HWND hw,
    UINT m,
    WPARAM wp,
    LPARAM lp
) {

    switch (m) {

        case WM_NCCREATE: {

            CREATESTRUCTW* cs =
                (CREATESTRUCTW*)lp;

            SetWindowLongPtrW(
                hw,
                GWLP_USERDATA,
                (LONG_PTR)cs->lpCreateParams
            );

            return TRUE;
        }

        case WM_COMMAND: {

            int id = LOWORD(wp);

            DadosJanela* dados =
                (DadosJanela*)GetWindowLongPtrW(
                    hw,
                    GWLP_USERDATA
                );

            if (!dados)
                break;

            if (id == ID_LANG_EN) {
                *dados->resultado = 1;
                DestroyWindow(hw);
                return 0;
            }

            if (id == ID_LANG_PT) {
                *dados->resultado = 2;
                DestroyWindow(hw);
                return 0;
            }

            if (id == ID_LANG_ES) {
                *dados->resultado = 3;
                DestroyWindow(hw);
                return 0;
            }

            if (id == ID_RESTART) {
                *dados->resultado = 1;
                DestroyWindow(hw);
                return 0;
            }

            if (id == ID_CANCEL) {
                *dados->resultado = 0;
                DestroyWindow(hw);
                return 0;
            }

            break;
        }

        case WM_CLOSE:
            DestroyWindow(hw);
            return 0;

        case WM_DESTROY:
            return 0;
    }

    return DefWindowProcW(
        hw,
        m,
        wp,
        lp
    );
}

// ============================================================
// REGISTRAR JANELAS AUXILIARES
// ============================================================

bool RegistrarJanelaAuxiliar(
    HINSTANCE hI,
    const wchar_t* nome
) {

    WNDCLASSW c = {};

    c.lpfnWndProc = AuxWindowProc;
    c.hInstance = hI;
    c.lpszClassName = nome;
    c.hCursor = LoadCursor(NULL, IDC_ARROW);
    c.hbrBackground =
        (HBRUSH)(COLOR_BTNFACE + 1);

    return RegisterClassW(&c) != 0 ||
           GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

// ============================================================
// JANELA DE IDIOMAS
// ============================================================

int EscolherIdioma(HWND dono) {

    HINSTANCE hI = GetModuleHandleW(NULL);

    RegistrarJanelaAuxiliar(
        hI,
        L"NP_LANG"
    );

    int resultado = 0;

    DadosJanela dados;
    dados.resultado = &resultado;

    HWND janela = CreateWindowExW(
        WS_EX_DLGMODALFRAME,
        L"NP_LANG",
        T().escolherIdioma,
        WS_POPUP |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        330,
        190,
        dono,
        NULL,
        hI,
        &dados
    );

    if (!janela)
        return 0;

    HWND texto = CreateWindowW(
        L"STATIC",
        T().escolherIdioma,
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        20,
        15,
        290,
        25,
        janela,
        NULL,
        hI,
        NULL
    );

    HWND en = CreateWindowW(
        L"BUTTON",
        L"English",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        30,
        55,
        270,
        30,
        janela,
        (HMENU)(INT_PTR)ID_LANG_EN,
        hI,
        NULL
    );

    HWND pt = CreateWindowW(
        L"BUTTON",
        L"Português",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        30,
        90,
        270,
        30,
        janela,
        (HMENU)(INT_PTR)ID_LANG_PT,
        hI,
        NULL
    );

    HWND es = CreateWindowW(
        L"BUTTON",
        L"Español",
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        30,
        125,
        270,
        30,
        janela,
        (HMENU)(INT_PTR)ID_LANG_ES,
        hI,
        NULL
    );

    SendMessageW(
        texto,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    SendMessageW(
        en,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    SendMessageW(
        pt,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    SendMessageW(
        es,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    EnableWindow(dono, FALSE);

    ShowWindow(janela, SW_SHOW);
    UpdateWindow(janela);

    MSG msg;

    while (IsWindow(janela)) {

        BOOL r = GetMessageW(
            &msg,
            NULL,
            0,
            0
        );

        if (r <= 0)
            break;

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    EnableWindow(dono, TRUE);
    SetForegroundWindow(dono);

    return resultado;
}

// ============================================================
// JANELA DE REINÍCIO
// ============================================================

int JanelaReiniciar(HWND dono) {

    HINSTANCE hI = GetModuleHandleW(NULL);

    RegistrarJanelaAuxiliar(
        hI,
        L"NP_RESTART"
    );

    int resultado = 0;

    DadosJanela dados;
    dados.resultado = &resultado;

    HWND janela = CreateWindowExW(
        WS_EX_DLGMODALFRAME,
        L"NP_RESTART",
        T().restartTitulo,
        WS_POPUP |
        WS_CAPTION |
        WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        430,
        180,
        dono,
        NULL,
        hI,
        &dados
    );

    if (!janela)
        return 0;

    HWND texto = CreateWindowW(
        L"STATIC",
        T().restartTexto,
        WS_CHILD |
        WS_VISIBLE |
        SS_CENTER,
        20,
        25,
        390,
        70,
        janela,
        NULL,
        hI,
        NULL
    );

    HWND restart = CreateWindowW(
        L"BUTTON",
        T().restart,
        WS_CHILD |
        WS_VISIBLE |
        BS_DEFPUSHBUTTON,
        80,
        110,
        120,
        30,
        janela,
        (HMENU)(INT_PTR)ID_RESTART,
        hI,
        NULL
    );

    HWND cancelar = CreateWindowW(
        L"BUTTON",
        T().cancelar,
        WS_CHILD |
        WS_VISIBLE |
        BS_PUSHBUTTON,
        230,
        110,
        120,
        30,
        janela,
        (HMENU)(INT_PTR)ID_CANCEL,
        hI,
        NULL
    );

    SendMessageW(
        texto,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    SendMessageW(
        restart,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    SendMessageW(
        cancelar,
        WM_SETFONT,
        (WPARAM)hFonteBotoes,
        TRUE
    );

    EnableWindow(dono, FALSE);

    ShowWindow(janela, SW_SHOW);
    UpdateWindow(janela);

    MSG msg;

    while (IsWindow(janela)) {

        BOOL r = GetMessageW(
            &msg,
            NULL,
            0,
            0
        );

        if (r <= 0)
            break;

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    EnableWindow(dono, TRUE);
    SetForegroundWindow(dono);

    return resultado;
}

// ============================================================
// REINICIAR PROGRAMA
// ============================================================

void ReiniciarPrograma(HWND hw) {

    wchar_t exe[MAX_PATH] = {};

    GetModuleFileNameW(
        NULL,
        exe,
        MAX_PATH
    );

    ShellExecuteW(
        NULL,
        L"open",
        exe,
        NULL,
        NULL,
        SW_SHOWNORMAL
    );

    DestroyWindow(hw);
}

// ============================================================
// JANELA PRINCIPAL
// ============================================================

LRESULT CALLBACK WindowProc(
    HWND hw,
    UINT m,
    WPARAM wp,
    LPARAM lp
) {

    switch (m) {

        case WM_CREATE: {

            hFonteBotoes =
                CreateFontW(
                    15,
                    0,
                    0,
                    0,
                    400,
                    0,
                    0,
                    0,
                    1,
                    0,
                    0,
                    0,
                    0,
                    L"Segoe UI"
                );

            int ids[] = {
                ID_SALVAR_COMO,
                ID_SALVAR_TXT,
                ID_ABRIR,
                ID_FORMATAR,
                ID_AJUDA,
                ID_IDIOMAS
            };

            int px[] = {
                5,
                120,
                225,
                390,
                485,
                575
            };

            int la[] = {
                110,
                100,
                160,
                90,
                80,
                100
            };

            const wchar_t* lbls[] = {
                T().salvarComo,
                T().salvarTxt,
                T().abrir,
                T().formatar,
                T().ajuda,
                T().idiomas
            };

            for (int i = 0; i < 6; i++) {

                HWND b =
                    CreateWindowExW(
                        0,
                        L"BUTTON",
                        lbls[i],
                        WS_CHILD |
                        WS_VISIBLE,
                        px[i],
                        5,
                        la[i],
                        30,
                        hw,
                        (HMENU)(INT_PTR)ids[i],
                        NULL,
                        NULL
                    );

                SendMessageW(
                    b,
                    WM_SETFONT,
                    (WPARAM)hFonteBotoes,
                    TRUE
                );
            }

            hTexto =
                CreateWindowExW(
                    WS_EX_CLIENTEDGE,
                    L"EDIT",
                    L"",
                    WS_CHILD |
                    WS_VISIBLE |
                    WS_VSCROLL |
                    WS_HSCROLL |
                    ES_MULTILINE |
                    ES_AUTOVSCROLL |
                    ES_AUTOHSCROLL,
                    5,
                    40,
                    875,
                    515,
                    hw,
                    (HMENU)(INT_PTR)ID_AREA_TEXTO,
                    NULL,
                    NULL
                );

            oldEdit =
                (WNDPROC)SetWindowLongPtrW(
                    hTexto,
                    GWLP_WNDPROC,
                    (LONG_PTR)EditProc
                );

            AplicarFonte();

            return 0;
        }

        case WM_SIZE:

            MoveWindow(
                hTexto,
                5,
                40,
                LOWORD(lp) - 10,
                HIWORD(lp) - 45,
                TRUE
            );

            return 0;

        case WM_COMMAND: {

            if (
                HIWORD(wp) == EN_CHANGE &&
                LOWORD(wp) == ID_AREA_TEXTO
            )
                modificado = true;

            switch (LOWORD(wp)) {

                case ID_SALVAR_COMO:
                    Salvar(hw);
                    break;

                case ID_SALVAR_TXT:
                    Salvar(hw);
                    break;

                case ID_ABRIR:
                    Abrir(hw);
                    break;

                case ID_FORMATAR: {

                    HMENU hMenu =
                        CreatePopupMenu();

                    std::wstring txtQuebra =
                        qAutomatica
                        ? T().quebraAutomatica
                        : T().quebraManual;

                    AppendMenuW(
                        hMenu,
                        MF_STRING,
                        901,
                        txtQuebra.c_str()
                    );

                    AppendMenuW(
                        hMenu,
                        MF_STRING,
                        902,
                        T().fontes
                    );

                    RECT rc;

                    GetWindowRect(
                        GetDlgItem(
                            hw,
                            ID_FORMATAR
                        ),
                        &rc
                    );

                    int selecao =
                        TrackPopupMenu(
                            hMenu,
                            TPM_LEFTALIGN |
                            TPM_TOPALIGN |
                            TPM_RETURNCMD |
                            TPM_RIGHTBUTTON,
                            rc.left,
                            rc.bottom,
                            0,
                            hw,
                            NULL
                        );

                    DestroyMenu(hMenu);

                    if (selecao == 901) {

                        qAutomatica =
                            !qAutomatica;

                        MessageBoxW(
                            hw,
                            qAutomatica
                            ? T().avisoQuebraAuto
                            : T().avisoQuebraManual,
                            T().tituloQuebra,
                            MB_OK |
                            MB_ICONINFORMATION
                        );
                    }

                    else if (selecao == 902) {

                        EscolherFonte(hw);
                    }

                    break;
                }

                case ID_AJUDA:

                    MessageBoxW(
                        hw,
                        T().ajudaTexto,
                        T().ajudaTitulo,
                        MB_OK |
                        MB_ICONINFORMATION
                    );

                    break;

                case ID_IDIOMAS: {

                    int novoIdioma =
                        EscolherIdioma(hw);

                    if (
                        novoIdioma >= 1 &&
                        novoIdioma <= 3 &&
                        novoIdioma != idioma
                    ) {

                        bool gravou =
                            GravarIdioma(
                                novoIdioma
                            );

                        if (gravou) {

                            int resposta =
                                JanelaReiniciar(hw);

                            if (resposta == 1)
                                ReiniciarPrograma(hw);
                        }
                    }

                    break;
                }
            }

            return 0;
        }

        case WM_CLOSE:

            if (modificado) {

                int r =
                    MessageBoxW(
                        hw,
                        T().salvarAntes,
                        T().aviso,
                        MB_YESNOCANCEL |
                        MB_ICONWARNING
                    );

                if (r == IDYES)
                    Salvar(hw);

                else if (r == IDCANCEL)
                    return 0;
            }

            DestroyWindow(hw);

            return 0;

        case WM_DESTROY:

            if (hFonte)
                DeleteObject(hFonte);

            if (hFonteBotoes)
                DeleteObject(hFonteBotoes);

            PostQuitMessage(0);

            return 0;
    }

    return DefWindowProcW(
        hw,
        m,
        wp,
        lp
    );
}

// ============================================================
// WINMAIN
// ============================================================

int WINAPI WinMain(
    HINSTANCE hI,
    HINSTANCE hP,
    LPSTR lpC,
    int nS
) {

    LerIdioma();

    InitCommonControls();

    WNDCLASSW c = {};

    c.lpfnWndProc = WindowProc;
    c.hInstance = hI;
    c.lpszClassName = L"NP";
    c.hCursor = LoadCursor(NULL, IDC_ARROW);
    c.hbrBackground =
        (HBRUSH)(COLOR_BTNFACE + 1);

    RegisterClassW(&c);

    std::wstring titulo =
        std::wstring(T().titulo) +
        L" - " +
        T().semTitulo;

    HWND hw =
        CreateWindowExW(
            0,
            L"NP",
            titulo.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            900,
            600,
            NULL,
            NULL,
            hI,
            NULL
        );

    if (!hw)
        return 0;

    ShowWindow(hw, nS);
    UpdateWindow(hw);

    MSG msg;

    while (
        GetMessageW(
            &msg,
            NULL,
            0,
            0
        )
    ) {

        if (
            GetAsyncKeyState(VK_CONTROL) < 0
        ) {

            if (
                GetAsyncKeyState('S') < 0
            ) {

                Salvar(hw);
                Sleep(150);
            }

            else if (
                GetAsyncKeyState('O') < 0
            ) {

                Abrir(hw);
                Sleep(150);
            }

            else if (
                GetAsyncKeyState('N') < 0
            ) {

                qAutomatica =
                    !qAutomatica;

                Sleep(150);
            }
        }

        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
