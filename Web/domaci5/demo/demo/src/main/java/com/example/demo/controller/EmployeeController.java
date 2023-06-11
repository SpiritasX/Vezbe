package com.example.demo.controller;

import com.example.demo.entity.Employee;
import com.example.demo.entity.dto.EmployeeDTO;
import com.example.demo.service.EmployeeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

/*
 * Klasa je anotirana sa @RestController čime se govori MVC framework-u
 * da se radi o kontroleru, koji funkcioniše kao endpoint RESTful servisa.
 * Rezultat svake funkcije treba da se vrati kao JSON zapis u telu poruke.
 */
@RestController

// Bazni url koji klasa obradjuje
@RequestMapping(value = "/api/employees")
public class EmployeeController {

    private final EmployeeService employeeService;

    // constructor-based dependency injection
    @Autowired
    public EmployeeController(EmployeeService employeeService) {
        this.employeeService = employeeService;
    }


    /*
     Prikaz jednog zaposlenog
     @PathVariable omogućava da se iz URL-a ekstrahuju podaci koji su namapirani na pozicione parametre.

     Primer putanje:  http://localhost:8080/api/employees/1
 */
    @GetMapping(
            value = "/{id}",
            produces = MediaType.APPLICATION_JSON_VALUE)  // tip odgovora
    public ResponseEntity<EmployeeDTO> getEmployee(@PathVariable(name = "id") Long id) {
        // Dobavljamo zaposlenog po ID-u
        Employee employee = this.employeeService.findOne(id);

        if (employee == null)
            return new ResponseEntity<>(new EmployeeDTO(), HttpStatus.OK);

        // Kreiramo objekat klase EmployeeDTO
        EmployeeDTO employeeDTO = new EmployeeDTO();
        employeeDTO.setFirstName(employee.getFirstName());
        employeeDTO.setLastName(employee.getLastName());
        employeeDTO.setPosition(employee.getPosition());

        // Vraćamo ResponseEntity
        // ResponseEntity predstavlja ceo HTTP odgovor: status kod, zaglavlja i body.
        // Možemo u potpunosti da kontrolišemo šta će se nalaziti u odgovoru koji želimo da vratimo.
        // Ako je došlo do greške postavljamo drugi HttpStatus npr. HttpStatus.BAD_REQUEST
        return new ResponseEntity<>(employeeDTO, HttpStatus.OK);
    }

    /*
        Prikaz svih zaposlenih

        Putanja: http://localhost:8080/api/employees
    */
    @GetMapping(                                               // value nije naveden, jer koristimo bazni url
            produces = MediaType.APPLICATION_JSON_VALUE)       // tip odgovora
    public ResponseEntity<List<EmployeeDTO>> getEmployees() {
        // Dobavljamo sve zaposlene
        List<Employee> employeeList = this.employeeService.findAll();

        // Kreiramo listu DTO objekata
        List<EmployeeDTO> employeeDTOS = new ArrayList<>();

        for (Employee employee : employeeList) {
            // Kreiramo EmployeeDTO za svakog zaposlenog, kojeg je vratila metoda findAll() i ubacujemo ga u listu
            EmployeeDTO employeeDTO = new EmployeeDTO(employee.getId(), employee.getFirstName(), employee.getLastName(),
                    employee.getPosition());
            employeeDTOS.add(employeeDTO);
        }
        return new ResponseEntity<>(employeeDTOS, HttpStatus.OK);
    }

    /*
        Kreiranje novog zaposlenog
    */

    @PostMapping(
            consumes = MediaType.APPLICATION_JSON_VALUE,     // tip podataka koje metoda može da primi
            produces = MediaType.APPLICATION_JSON_VALUE)     // tip odgovora
    public ResponseEntity<EmployeeDTO> createEmployee(@RequestBody EmployeeDTO employeeDTO) throws Exception {
        // Kreiramo objekat klase Employee, tako što setujemo vrednosti atributa
        // Vrednosti atributa uzimamo iz pristiglog DTO
        Employee employee = new Employee(employeeDTO.getFirstName(), employeeDTO.getLastName(), employeeDTO.getPosition());

        // Pozivanje metode servisa koja kreira novog zaposlenog
        Employee newEmployee = employeeService.create(employee);

        // Mapiranje novog zaposlenog na DTO objekat, koji će biti vraćen u sklopu odgovora
        EmployeeDTO newEmployeeDTO = new EmployeeDTO(newEmployee.getId(), newEmployee.getFirstName(),
                newEmployee.getLastName(), newEmployee.getPosition());

        return new ResponseEntity<>(newEmployeeDTO, HttpStatus.OK);
    }

    @DeleteMapping(
            value = "/{id}"
    )
    public ResponseEntity deleteEmployee(@PathVariable(name = "id") long id){
        employeeService.delete(id);

        return new ResponseEntity(HttpStatus.OK);
    }
}
