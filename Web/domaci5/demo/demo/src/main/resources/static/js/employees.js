$(document).ready(function () {    // Čeka se trenutak kada je DOM(Document Object Model) učitan da bi JS mogao sa njim da manipuliše.
    // ajax poziv
    $.ajax({
        type: "GET",                                                // HTTP metoda
        url: "http://localhost:8080/api/employees",                 // URL koji se gađa
        dataType: "json",                                           // tip povratne vrednosti
        success: function (data) {
            console.log("SUCCESS : ", data);                        // ispisujemo u konzoli povratnu vrednost
            for (i = 0; i < data.length; i++) {                     // prolazimo kroz listu svih zaposlenih
                var row = "<tr>";                                   // kreiramo red za tabelu
                row += "<td>" + data[i]['firstName'] + "</td>";     // ubacujemo podatke jednog zaposlenog u polja
                row += "<td>" + data[i]['lastName'] + "</td>";
                row += "<td>" + data[i]['position'] + "</td>";

                // kreiramo button i stavljamo idButton = idZaposlenog
                var btn = "<button class='btnSeeMore' id = " + data[i]['id'] + ">See more</button>";
                row += "<td>" + btn + "</td>";                      // ubacujemo button u poslednje polje reda

                $('#employees').append(row);                        // ubacujemo kreirani red u tabelu čiji je id = employees
            }
        },
        error: function (data) {
            console.log("ERROR : ", data);
        }
    });
});

$(document).on('click', '.btnSeeMore', function () {            // kada je button (čija je class = btnSeeMore) kliknut
    var employeesDiv = $("#allEmployees");                      // dobavi element čiji je id = allEmployees  (pogledati html)
    employeesDiv.hide();                                        // sakrij taj element

    // nakon što korisnik klikne button See more možemo i samo da se prebacimo na employee.html
    // tada ajax poziv za dobavljanje jednog zaposlenog moze da bude u fajlu employee.js
    $.ajax({
        type: "GET",
        url: "http://localhost:8080/api/employees/" + this.id,  // this.id je button id, a kao button id je postavljen id zaposlenog
        dataType: "json",
        success: function (data) {
            console.log("SUCCESS : ", data);
            $('#firstName').append(data['firstName']);
            $('#lastName').append(data['lastName']);
            $('#position').append(data['position']);
            var employeesDiv = $("#oneEmployee");              // dobavi element čiji je id = oneEmployee
            employeesDiv.show();                               // prikaži taj element
        },
        error: function (data) {
            console.log("ERROR : ", data);
        }
    });
});

$(document).on("submit", "form", function (event) {           // kada je submitovana forma za kreiranje novog zaposlenog
    event.preventDefault();

    var firstName = $("#firstName").val();
    var lastName = $("#lastName").val();
    var jobPosition = $("#position").val();

    var newEmployeeJSON = formToJSON(firstName, lastName, jobPosition);  // pozivamo pomoćnu metodu da kreira JSON

    $.ajax({
        type: "POST",                                               // HTTP metoda je POST
        url: "http://localhost:8080/api/employees",                 // URL na koji se šalju podaci
        dataType: "json",                                           // tip povratne vrednosti
        contentType: "application/json",                            // tip podataka koje šaljemo
        data: newEmployeeJSON,                                      // Šaljemo novog zaposlenog
        success: function () {
            alert(firstName + " " + lastName + " je uspešno kreiran kao " + jobPosition);
            window.location.href = "employees.html"; //localhost:8080/employees.html
        },
        error: function (data) {
            alert("Greška!");
        }
    });
});

// Pomoćna funkcija koja serijalizuje polja iz forme i od njih kreira JSON
function formToJSON(first, last, position) {
    return JSON.stringify({
        "firstName": first,
        "lastName": last,
        "position": position
    });
}
