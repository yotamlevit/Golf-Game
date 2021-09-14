#pragma once
#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);
#endif