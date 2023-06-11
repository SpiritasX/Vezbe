package com.example.demo.service;

import com.example.demo.entity.Employee;
import com.example.demo.entity.dto.EmployeeDTO;

import java.util.List;

public interface EmployeeService {

    Employee create(Employee employee) throws Exception;

    Employee findOne(Long id);

    Employee update(Employee employee) throws Exception;

    void delete(Long id);

    List<Employee> findAll();

    void edit(long id, EmployeeDTO employeeDTO);
}