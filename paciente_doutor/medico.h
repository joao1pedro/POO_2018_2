#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <string>
#include <vector>
#include "paciente.h"


class Doctor
{
private:
	std::string m_name;
	std::vector<Patient *> m_patient;
 
public:
	Doctor(std::string name = ""):
		m_name(name)
	{
	}
 
	void addPatient(Patient *pat);

	void rmPatient(std::string patId);
 
	friend std::ostream& operator<<(std::ostream &out, const Doctor& doc);
	friend class Patient;

	std::string getName() const { return m_name; }
};











#endif