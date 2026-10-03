#include "common.hpp"
#include <algorithm>
struct Book {std::string id,title,author,borrower;};
struct Member {std::string id,name;};
std::string lower(std::string s){for(char&c:s)c=static_cast<char>(std::tolower(static_cast<unsigned char>(c)));return s;}
int main(){try {std::vector<Book> books;std::vector<Member> members;Book b;Member m;std::ifstream in("library.txt");char type;
 while(in>>type){if(type=='B'){in>>std::quoted(b.id)>>std::quoted(b.title)>>std::quoted(b.author)>>std::quoted(b.borrower);if(in)books.push_back(b);}else if(type=='M'){in>>std::quoted(m.id)>>std::quoted(m.name);if(in)members.push_back(m);}else throw std::runtime_error("Invalid data file");}
 auto save=[&](){std::ofstream out("library.txt.tmp");for(auto&r:books)out<<"B "<<std::quoted(r.id)<<' '<<std::quoted(r.title)<<' '<<std::quoted(r.author)<<' '<<std::quoted(r.borrower)<<'\n';for(auto&r:members)out<<"M "<<std::quoted(r.id)<<' '<<std::quoted(r.name)<<'\n';commit(out,"library.txt");};
 auto show=[](const Book&r){std::cout<<r.id<<" | "<<r.title<<" | "<<r.author<<" | "<<(r.borrower.empty()?"Available":"Issued to "+r.borrower)<<'\n';};
 for(;;){std::cout<<"\nLIBRARY MANAGEMENT\n1 Add book\n2 Add member\n3 Issue book\n4 Return book\n5 Search title/author\n6 Display books\n7 Display members\n0 Exit\n";int c=number("Choice: ",0,7);if(!c)break;
 if(c==6){for(auto&r:books)show(r);if(books.empty())std::cout<<"No books.\n";continue;}
 if(c==7){for(auto&r:members)std::cout<<r.id<<" | "<<r.name<<'\n';if(members.empty())std::cout<<"No members.\n";continue;}
 if(c==5){auto q=lower(required("Search: "));bool found=false;for(auto&r:books)if(lower(r.title).find(q)!=std::string::npos||lower(r.author).find(q)!=std::string::npos){show(r);found=true;}if(!found)std::cout<<"No matches.\n";continue;}
 if(c==2){auto id=required("Member ID: ");if(std::any_of(members.begin(),members.end(),[&](auto&r){return r.id==id;})){std::cout<<"Member already exists.\n";continue;}members.push_back({id,required("Name: ")});save();std::cout<<"Member saved.\n";continue;}
 auto id=required("Book ID: ");auto it=std::find_if(books.begin(),books.end(),[&](auto&r){return r.id==id;});
 if(c==1){if(it!=books.end()){std::cout<<"Book already exists.\n";continue;}books.push_back({id,required("Title: "),required("Author: "),""});}
 else{if(it==books.end()){std::cout<<"Book not found.\n";continue;}if(c==3){if(!it->borrower.empty()){std::cout<<"Already issued.\n";continue;}auto member=required("Member ID: ");if(!std::any_of(members.begin(),members.end(),[&](auto&r){return r.id==member;})){std::cout<<"Member not found.\n";continue;}it->borrower=member;}else{if(it->borrower.empty()){std::cout<<"Book is not issued.\n";continue;}it->borrower.clear();}}
 save();std::cout<<"Saved successfully.\n";
 }
 }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;} }
