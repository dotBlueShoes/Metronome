/*
 * mstd - Maipa's Standard Library
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mstd/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "terminal_libs.hpp"

// TODO: doda� kolorowanie

namespace mstd {
    static void get_terminal_size(int& width, int& height) {
#if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
        height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__) || defined(__APPLE__)
        struct winsize w;
        ioctl(fileno(stdout), TIOCGWINSZ, &w);
        width = (int)(w.ws_col);
        height = (int)(w.ws_row);
#endif
    }
    
    static void clear_terminal() {
#ifdef _WIN32
        system("cls");  // Windows: czy�ci ekran i histori�
#else
        system("clear && printf '\\e[3J'");  // Linux/macOS: czy�ci ekran i usuwa histori�
#endif
    }
}