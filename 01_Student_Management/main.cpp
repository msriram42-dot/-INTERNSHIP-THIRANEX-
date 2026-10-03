#include "common.hpp"
struct Student { std::string id,name,course; int age; };
int main() { try {
 std::vector<Student> records; Student s; std::ifstream in("students.txt"); while(in>>std::quoted(s.id)>>std::quoted(s.name)>>s.age>>std::quoted(s.course)) records.push_back(s);
 auto save=[&](){std::ofstream out("students.txt.tmp"); for(auto& r:records) out<<std::quoted(r.id)<<' '<<std::quoted(r.name)<<' '<<r.age<<' '<<std::quoted(r.course)<<'\n'; commit(out,"students.txt");};
 for(;;) { std::cout<<"\nSTUDENT MANAGEMENT\n1 Add\n2 Update\n3 Delete\n4 Display\n0 Exit\n"; int c=number("Choice: ",0,4); if(!c) break;
 if(c==4) { if(records.empty()) std::cout<<"No students.\n"; for(auto&r:records) std::cout<<r.id<<" | "<<r.name<<" | "<<r.age<<" | "<<r.course<<'\n'; continue; }
 auto id=required("Student ID: "); auto it=records.begin(); while(it!=records.end() && it->id!=id) ++it;
 if(c==1) { if(it!=records.end()) {std::cout<<"ID already exists.\n";continue;} Student n{id,required("Name: "),"",number("Age: ",1,120)}; n.course=required("Course: "); records.push_back(n); }
 else { if(it==records.end()) {std::cout<<"Student not found.\n";continue;} if(c==3) records.erase(it); else {it->name=required("Name: ");it->age=number("Age: ",1,120);it->course=required("Course: ");} }
 save(); std::cout<<"Saved successfully.\n";
 }
 } catch(const std::exception&e) {std::cerr<<e.what()<<'\n';return 1;} }
