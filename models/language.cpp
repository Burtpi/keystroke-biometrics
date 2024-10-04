#include <models/language.h>

std::map<int, std::string> hidToAscii = {
    {53, "`"},        {30, "1"},          {31, "2"},         {32, "3"},
    {33, "4"},        {34, "5"},          {35, "6"},         {36, "7"},
    {37, "8"},        {38, "9"},          {39, "0"},         {45, "-"},
    {46, "="},        {42, "Backspace"},  {43, "Tab"},       {20, "q"},
    {26, "w"},        {8, "e"},           {21, "r"},         {23, "t"},
    {28, "y"},        {24, "u"},          {12, "i"},         {18, "o"},
    {19, "p"},        {47, "["},          {48, "]"},         {49, "\\"},
    {57, "CapsLock"}, {4, "a"},           {22, "s"},         {7, "d"},
    {9, "f"},         {10, "g"},          {11, "h"},         {13, "j"},
    {14, "k"},        {15, "l"},          {51, ";"},         {52, "'"},
    {40, "Enter"},    {225, "LShift"},    {29, "z"},         {27, "x"},
    {6, "c"},         {25, "v"},          {5, "b"},          {17, "n"},
    {16, "m"},        {54, ","},          {55, "."},         {56, "/"},
    {229, "RShift"},  {224, "LCtrl"},     {226, "LAlt"},     {44, "Space"},
    {230, "RAlt"},    {228, "RCtrl"},     {73, "Insert"},    {76, "Delete"},
    {74, "Home"},     {77, "End"},        {75, "PgUp"},      {78, "PgDn"},
    {80, "Left"},     {82, "Up"},         {81, "Down"},      {79, "Right"},
    {83, "NumLock"},  {41, "Esc"},        {58, "F1"},        {59, "F2"},
    {60, "F3"},       {61, "F4"},         {62, "F5"},        {63, "F6"},
    {64, "F7"},       {65, "F8"},         {66, "F9"},        {67, "F10"},
    {68, "F11"},      {69, "F12"},        {70, "PrtScr"},    {71, "ScrollLock"},
    {72, "Pause"},    {227, "LWin"},      {231, "Rwin"},     {229, "RShift"},
    {224, "LCtrl"},   {226, "LAlt"},      {230, "RAlt"},     {228, "RCtrl"},
    {73, "Insert"},   {76, "Delete"},     {74, "Home"},      {77, "End"},
    {75, "PgUp"},     {78, "PgDn"},       {80, "Left"},      {82, "Up"},
    {81, "Down"},     {79, "Right"},      {83, "NumLock"},   {41, "Esc"},
    {58, "F1"},       {59, "F2"},         {60, "F3"},        {61, "F4"},
    {62, "F5"},       {63, "F6"},         {64, "F7"},        {65, "F8"},
    {66, "F9"},       {67, "F10"},        {68, "F11"},       {69, "F12"},
    {70, "PrtScr"},   {71, "ScrollLock"}, {72, "Pause"},     {227, "LWin"},
    {231, "Rwin"},    {57, "CapsLock"},   {42, "Backspace"}, {43, "Tab"},
    {40, "Enter"},    {225, "LShift"},    {1033, "Fn"},      {101, "Menu"}};