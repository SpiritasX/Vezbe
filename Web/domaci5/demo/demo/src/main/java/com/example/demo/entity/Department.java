package com.example.demo.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
public class Department implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column
    private String name;

    /*
       Primer veze 1:n.

       Departman sadrži kolekciju zaposlenih (employees).
       Jedna strana veze je anotirana sa @OneToMany, dok je druga (u klasi Employee) anotirana sa @ManyToOne.


      **************  ATRIBUT mappedBy **************

       Atribut mappedBy označava da je vlasnik veze departman.
       U bazi će se u tabeli Employee kreirati dodatna kolona DEPARTMENT_ID, koja će sadržati id objekata
       klase Departman kao strani ključ.

       Primer:
            Tabela: Employee

            |ID|FIRST_NAME|LAST_NAME |POSITION  |DEPARTMENT_ID|
            ---------------------------------------------------
            |1 |"Janko"   |"Jankic   |"radnik"  |1            |
            |2 |"Marko"   |"Markovic"|"menadzer"|1            |
            |3 |"Zdravko" |"Zdravkic"|"menadzer"|2            |

       Janko i Marko su povezani sa departmanom 1, dok je Zdravko povezan sa departmanom 2.

       Ako se izostavi mappedBy kreiraće se medjutabela koja će sadržati 2 kolone:
            |EMPLOYEE_ID | DEPARTMENT_ID|


       **************  ATRIBUT fetch **************

       Od atributa fetch zavisi da li će se učitatiti i sve veze sa odgovarajućim objektom čim se inicijalno
       učita sam objekat.

       Opcije su EAGER i LAZY.
             - EAGER - učitaće se sve veze sa objektom odmah
             - LAZY -  učitaće se tek kada eksplicitno tražimo povezane objekte npr. pozivanje metode getEmployees().


       **************  ATRIBUT cascade **************

       Atribut cascade:
           - ALL: prilikom svakog čuvanja, izmene ili brisanja departmana, čuvaju, menjaju ili se brišu
                   i zaposleni (employees).
                   To znači da ne moraju unapred da se čuvaju employees, pa da se povezuju sa departmanom.


       **************  ATRIBUT orphanRemoval **************
            - true - obezbedjuje da se employee izbriše iz baze kada se izbriše iz kolekcije employees
                    u objektu departman.

                    Primer: Post na društvenim mrežama ima kolekciju komentara koji se nalaze na njemu.
                             Kada se obriše komentar sa posta, treba ga obrisati i iz sistema.
     */

    @OneToMany(mappedBy = "department", fetch = FetchType.LAZY, cascade = CascadeType.ALL)
    private Set<Employee> employees = new HashSet<>();


    @ManyToOne(fetch = FetchType.EAGER, cascade = CascadeType.ALL)
    private Company company;


    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Company getCompany() {
        return company;
    }

    public void setCompany(Company company) {
        this.company = company;
    }

    public Set<Employee> getEmployees() {
        return employees;
    }

    public void setEmployees(Set<Employee> employees) {
        this.employees = employees;
    }

    @Override
    public String toString() {
        return "Department{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", company=" + company +
                '}';
    }
}
