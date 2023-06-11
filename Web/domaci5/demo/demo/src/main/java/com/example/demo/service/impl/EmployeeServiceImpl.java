package com.example.demo.service.impl;

import com.example.demo.entity.Employee;
import com.example.demo.entity.dto.EmployeeDTO;
import com.example.demo.repository.EmployeeRepository;
import com.example.demo.service.EmployeeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;


/*
 * Klasa je anotirana sa @Service što treba da naznači Springu da je klasa
 * Spring Bean i da treba da bude u nadležnosti Spring kontejnera.
 * U ovoj klasi se nalazi biznis logika aplikacije.
 */
@Service
public class EmployeeServiceImpl implements EmployeeService {
    @Autowired
    private EmployeeRepository employeeRepository;

    /*
        Kreiranje novog zaposlenog i čuvanje u bazi pozivanjem metode save.
        Metoda vraća kreiranog zaposlenog.
    */
    @Override
    public Employee create(Employee employee) throws Exception {
        if (employee.getId() != null) {
            throw new Exception("ID must be null!");
        }
        Employee newEmployee = this.employeeRepository.save(employee);
        return newEmployee;
    }

    /*
        Dobavljanje zaposlenog po ID-iju.
        Metoda vraća pronađenog zaposlenog, ako postoji.
    */
    @Override
    public Employee findOne(Long id) {
        Optional<Employee> employee = this.employeeRepository.findById(id);

        return employee.orElse(null);
    }

    /*
        Promena imena zaposlenog.
        Metoda vraća zaposlenog, koji ima postavljeno novo ime.
    */
    @Override
    public Employee update(Employee employee) throws Exception {
        Employee employeeToUpdate = this.employeeRepository.getOne(employee.getId());
        if (employeeToUpdate == null) {
            throw new Exception("Employee doesnt exist!");
        }

        // postavljanje novog imena
        employeeToUpdate.setFirstName(employee.getFirstName());

        // čuvanje u bazi
        Employee savedEm = this.employeeRepository.save(employeeToUpdate);
        return savedEm;
    }

    /*
        Brisanje zaposlenog.
    */
    @Override
    public void delete(Long id) {
        this.employeeRepository.deleteById(id);
    }

    /*
        Prikaz svih zaposlenih
        Poziva se metoda repozitorijuma findAll().
        Metoda vraća listu, koja sadrži pronađene zaposlene.
    */
    @Override
    public List<Employee> findAll() {
        List<Employee> employees = this.employeeRepository.findAll();
        return employees;
    }

    public void edit(long id, EmployeeDTO employeeDTO) {
        Employee employee = findOne(id);
        employee.setPosition(employeeDTO.getPosition());
        employee.setFirstName(employeeDTO.getFirstName());
        employee.setLastName(employeeDTO.getLastName());
        employeeRepository.save(employee);
    }
}
