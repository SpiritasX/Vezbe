<template>
  <div id="allEmployees">
    <h1>Employees</h1>
    <button v-on:click="addEmployee">Add new employee</button>
    <br /><br />
    <div class="container-employees">
      <table id="employees">
        <tr>
          <th>Ime</th>
          <th>Prezime</th>
          <th>Pozicija</th>
          <th>About</th>
          <th>Delete</th>
        </tr>
        <!--<tr v-for="employee in employees" :key="employee.id">
          <td>{{ employee.firstName }}</td>
          <td>{{ employee.lastName }}</td>
          <td>{{ employee.position }}</td>
          <td>
            <button class="btnSeeMore" v-on:click="seeMore(employee)">
              See more
            </button>
          </td>
          <td>
            <button class="delete" v-on:click="deleteEmployee(employee.id)">
              Delete
            </button>
          </td>
        </tr>-->
        <employees-comp
          v-for="employee in employees"
          :key="employee.id"
          :employee="employee"
        >
        </employees-comp>
      </table>
    </div>
  </div>
</template>

<script>
//import axios from "axios";
import EmployeesComp from "../components/EmployeesComp.vue";
export default {
  name: "EmployeesView",
  components: { EmployeesComp },
  data: function () {
    return {
      employees: [],
    };
  },
  mounted: function () {

    //primer axios poziva
    /*axios
      .get("http://localhost:8081/api/employees")
      .then((res) => {
        this.employees = res.data
      })
      .catch((err) =>{
        console.log(err)
      })*/

      fetch('http://localhost:8081/api/employees')
        .then(response => response.json())
        .then(data => {console.log("Success:", data); this.employees = data})
        .catch((error) => {
          console.error("Error:", error);
        });
  },
  methods: {
    addEmployee: function() {
      this.$router.push("/add-employee");
    },
    seeMore: function (employee) {
      this.$router.push("/employee?id=" + employee.id);
    },
    deleteEmployee: function (id) {
      fetch("http://localhost:8081/api/employees/" + id, {
        method: "DELETE",
      }).then((res) => {
        if (res.ok) {
          window.location.reload();
        }
      });
    },
  },
};
</script>

<style>
h1 {
  color: #4caf50;
}

h3 {
  color: #4caf50;
}

.container-employees {
  display: flex;
  justify-content: center;
}

#employees th {
  padding-top: 12px;
  padding-bottom: 12px;
  text-align: left;
  background-color: #4caf50;
  color: white;
}

#employees td,
#employees th {
  border: 1px solid #ddd;
  padding: 8px;
}

#employees tr:nth-child(even) {
  background-color: #f2f2f2;
}

#employees tr:hover {
  background-color: #ddd;
}

.card {
  box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2);
  max-width: 300px;
  margin: auto;
  text-align: center;
}

.title {
  color: grey;
  font-size: 18px;
}
</style>

