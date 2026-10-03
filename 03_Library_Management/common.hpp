#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>
#include <filesystem>
#include <cmath>
inline std::string ask(const std::string& prompt) { std::string s; std::cout<<prompt; if(!std::getline(std::cin,s)) throw std::runtime_error("Input closed"); return s; }
inline std::string required(const std::string& p) { for(;;) { auto s=ask(p); if(s.find_first_not_of(" \t")!=std::string::npos) return s; std::cout<<"Cannot be empty.\n"; } }
inline int number(const std::string& p,int lo,int hi) { for(;;) { std::istringstream in(ask(p)); int n; char extra; if(in>>n && !(in>>extra) && n>=lo && n<=hi) return n; std::cout<<"Enter a valid number.\n"; } }
inline long long money(const std::string& p) { for(;;) { auto s=ask(p); auto dot=s.find('.'); auto whole=s.substr(0,dot); auto fraction=dot==std::string::npos?std::string():s.substr(dot+1); if(!whole.empty() && whole.size()<=10 && fraction.size()<=2 && whole.find_first_not_of("0123456789")==std::string::npos && fraction.find_first_not_of("0123456789")==std::string::npos) { while(fraction.size()<2) fraction+='0'; auto n=std::stoll(whole)*100+std::stoll(fraction); if(n>0) return n; } std::cout<<"Enter a positive amount with at most 2 decimal places.\n"; } }
inline void amount(long long n) { std::cout<<n/100<<'.'<<std::setw(2)<<std::setfill('0')<<n%100<<std::setfill(' '); }
inline void commit(std::ofstream& out,const std::string& file) { out.flush(); if(!out) throw std::runtime_error("Save failed"); out.close(); std::filesystem::copy_file(file+".tmp",file,std::filesystem::copy_options::overwrite_existing); std::filesystem::remove(file+".tmp"); }
