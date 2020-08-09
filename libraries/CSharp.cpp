#define CSharp
#define Csharp
#define csharp

#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>

#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__)

#include<Windows.h>

string CSCompilerPath;




#elif defined(__linux) || defined(__linux__) || defined(linux)

#include <sys/types.h>  
#include <sys/stat.h>

