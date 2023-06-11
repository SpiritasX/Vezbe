package com.example.demo.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/*
  @Entity anotacija naznačava da je klasa perzistentni entitet.
  U bazi će se kreirati tabela sa nazivom klase.

  Ukoliko želimo da se tabela u bazi drugačije zove, možemo eksplicitno da zadamo naziv tabele dodavanjem anotacije:
  @Table("naziv_tabele_u_bazi") kojom se specificira tačan naziv tabele u bazi,
 */
@Entity
public class Employee implements Serializable {
    /*
      Svaki entitet ima svoj ključ. To je najčešće id, koji se generiše na određen način.
      Potrebno je da stavimo anotaciju @Id.

      Možemo da izaberemo strategiju generisanja ključeva.
      - IDENTITY - inkrementalno generisanje ključeva prilikom čuvanja novog objekta u bazi.
     */
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;


    /*
       Iznad atributa klase stavljamo anotaciju @Column.
       Ova anotacija označava da će se za atribut kreirati kolona u tabeli.
       Naziv ove kolone je isti kao i naziv atributa.
       Kolona može da ima naziv koji se razlikuje od naziva atributa: @Column(name = "novo_ime_kolone")

       Kolona first_name će se kreirati u tabeli employee.
     */
    @Column(name = "first_name")
    private String firstName;

    @Column(nullable = false)
    private String lastName;

    @Column
    private String position;

    /*
        Druga strana bidirekcione veze 1:n
     */
    @ManyToOne(fetch = FetchType.LAZY)
    private Department department;

    /*
        Jedan radnik može da radi na više projekata, a jedan projekat može da sadrži više radnika
        koji rade na njemu. Stavljamo anotaciju @ManyToMany.

        Anotacija @JoinTable pravi odvojenu tabelu koja će čuvati veze izmedju projekata i radnika.
        Sa name = "working" postavljamo naziv te tabele.
    */
    @ManyToMany
    @JoinTable(name = "working",
            joinColumns = @JoinColumn(name = "employee_id", referencedColumnName = "id"),
            inverseJoinColumns = @JoinColumn(name = "project_id", referencedColumnName = "id"))
    private Set<Project> projects = new HashSet<>();

    public Employee(String firstName, String lastName, String position) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.position = position;
    }

    public Employee() {
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getPosition() {
        return position;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public Department getDepartment() {
        return department;
    }

    public void setDepartment(Department department) {
        this.department = department;
    }

    @Override
    public String toString() {
        return "Employee{" +
                "id=" + id +
                ", firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", position='" + position + '\'' +
                ", department=" + department +
                '}';
    }
}
