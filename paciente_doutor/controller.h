#include "medico.h"
#include "paciente.h"
#include "repositorio.h"
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

class Controller{
	/* map<string, Doctor> rDoc;
	map<string, Patient> rPat; */
	Repositorio<Doctor> rDoc;
	Repositorio<Patient> rPat;
	
public:
	Controller():
		rDoc("Doctor"), rPat("Patiente")
	{
	}

	string shell(string line){
		stringstream ss(line);
        stringstream out;
		string op;
		ss >> op;
		if(op == "addDoc"){//_dot1 _dot2 _dot3 ...
			string name;
			while(ss >> name){
				rDoc.add(name, Doctor(name));
			}
		} else if(op == "addPat"){//_dot1 _dot2 _dot3 ...
			string name;
			while(ss >> name){
				rPat.add(name, Patient(name));
			}
		} else if(op == "show"){
			out << "Doctors: " << endl;
			for(auto user : rDoc.getValues())
				out << user << " ";
			out << "Patients: " << endl;
			for(auto user : rPat.getValues())
				out << user << " ";
		}else if(op == "rmPac"){
			string name;
			ss >> name;
			Patient *pat = rPat.get(name);
            vector<Doctor*> vd = pat->getDoctors();
			for(auto &doctor : vd){
                pat->rmDoctor(doctor->getName());
            }
			rPat.rm(name);
		}
        else if(op == "rmDoc"){
			string name;
			ss >> name;
			Patient *p = rPat.get(name);
			while(ss >> name){
				Doctor *doctor = rDoc.get(name);
				p->rmDoctor(doctor->getName());
			}
			//rDoc.rm(name);
		}else if(op == "tie"){// _med _pac _pac ...
			string medName;
			ss >> medName;

            Patient *p = rPat.get(medName);
			while(ss >> medName){
				Doctor *doctor = rDoc.get(medName);
				p->addDoctor(doctor);   
			}               
		}
		/*
		untie //_med _pac _pac _pac

		 rmPac //_pac{
			para cada medico desse paciente
			 	medico.rmpac(pac)
			rPac.erase(pac)
		}
		rmDoc 
			para cada paciente desse medico 
				medico.rmPac(pac)
			rDoc.erase(doc) */
		 else {
			cout << "comando invalido" << endl;
		}
		return out.str();
	}
	void exec(){
		string line;
		while(true){
			getline(cin, line);
			if(line == "end")
				return;
			try{ 
				cout << shell(line);
			}catch(string e){
				
			}catch(const char* e){
				cout << e << endl;
			}
		}
	}
};