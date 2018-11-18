#include "medico.h"

std::ostream& operator<<(std::ostream &out, const Doctor &doc)
{
    unsigned int length = doc.m_patient.size();
    out << doc.m_name << "[ ";
    for (unsigned int count = 0; count < length; ++count)
            out << doc.m_patient[count]->getName() << ' ';
    out << "]";
    return out;
}

void Doctor::addPatient(Patient *pat){
    for(auto *p : m_patient){
        if(p->getName() == pat->getName())
            throw std::string("fail: paciente ja existe");
    }
    m_patient.push_back(pat);
}

void Doctor::rmPatient(std::string nome){
    for(size_t i = 0; i < m_patient.size(); i++){
        if(Doctor::m_patient[i]->getName() == nome)
            m_patient.erase(m_patient.begin() + i);
    }
}