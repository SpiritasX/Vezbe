package com.example.demo.repository;

import com.example.demo.entity.Employee;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

/*
    Repository je interfejs koji služi za komunikaciju sa bazom iz koje izvlači podatke.

    Metode za pretragu počinju sa findBy, dok u nastavku sadrže nazive atributa iz modela
    koji mogu da se konkateniraju sa And, Or, Between, LessThan, GreaterThan, Like, itd.
    uz dodavanje pomoćnih uslova poput Containing, AllIgnoringCase, itd.
 */
public interface EmployeeRepository extends JpaRepository<Employee, Long> {
    /*
        Spring na osnovu imena metode kreira upit za bazu.

        Traži sve zaposlene (employee) koji imaju poziciju koja se prosledjuje ovoj metodi kao string (String position).
        Sortira sve koje je pronašao po imenu i vraća kolekciju zaposlenih.
     */
    List<Employee> findAllByPositionOrderByFirstName(String position);

    /*
        Traži sve zaposlene po imenu ili prezimenu.
     */
    List<Employee> findByFirstNameOrLastName(String firstName, String lastName);

    /*
        Traži sve zaposlene po imenu, ignorišu se mala i velika slova.
     */
    List<Employee> findByFirstNameIgnoreCase(String firstName);

    /*
        Traži sve zaposlene po nazivu departmana.
     */
    List<Employee> findByDepartmentName(String departmentName);

}
